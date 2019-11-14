import argparse
import binascii
import contextlib
import datetime
import logging
import os
import sys
import time

import serial
from typing import Iterable, List


logger = logging.getLogger(__name__)


def send_command(connection, cmd, *args):
    full_command = ' '.join([
        cmd,
        *(str(arg) for arg in args)
    ])
    connection.write(full_command.encode('utf-8'))
    connection.write(b'\n')

    logger.debug("Sending command: %s", full_command)

    # Consume the echo'd back command
    connection.readline()


def get_response_for_command(connection, cmd, *args) -> Iterable[str]:
    send_command(connection, cmd, *args)

    while True:
        line = connection.readline()
        if(not line.strip()):
            break

        if line.decode('utf-8').strip().startswith('>>'):
            return

        yield line.decode('utf-8').rstrip()


@contextlib.contextmanager
def timeout(connection, timeout):
    original_timeout = connection.timeout
    connection.timeout = timeout

    yield

    connection.timeout = original_timeout


def get_verified_response_for_command(
    connection,
    cmd,
    *args,
    max_attempts=10
) -> Iterable[str]:
    last = []

    attempts = 0

    while attempts < max_attempts:
        current = list(get_response_for_command(connection, cmd, *args))

        if current == last:
            for line in current:
                yield line

            return

        last = current
        attempts += 1

    raise ValueError("Failed to get verified response")


def list_logs(connection) -> List[str]:
    indentations = {}
    logs = []

    for line in get_response_for_command(
        connection,
        'log_list',
    ):
        indentation_level = len(line) - len(line.lstrip())
        indentations[indentation_level] = line.strip()

        if not line.endswith('.log'):
            continue

        logs.append(
            ''.join([
                v for k, v in sorted(
                    indentations.items(), key=lambda row: row[0]
                )
            ])
        )

    return logs


def get_log(connection, path) -> Iterable[str]:
    send_command(
        connection,
        'log_print_chk',
        path
    )
    started = time.time()
    line_count = 0
    error_count = 0
    byte_count = 0
    while True:
        line = connection.readline()
        line_count += 1
        if not line.strip():
            break

        if line.decode('utf-8').strip().startswith('>>'):
            return

        try:
            data, checksum = line.split(b'\t::::\t')
        except ValueError:
            # We probably lost a character in our delimiter
            connection.write(b'0')
            error_count += 1
            continue

        if binascii.crc32(data) == int(checksum):
            connection.write(b'1')
        else:
            connection.write(b'0')
            error_count += 1

        byte_count += len(data) + 1

        yield data.decode('utf-8').strip()

    logger.info(
        'Successfully received (%.1f%% error; %.1fkB at %.3fkBps)',
        error_count / line_count * 100,
        (byte_count / 1000),
        (byte_count / 1000) / (time.time() - started)
    )


def log_checksum(connection, filename) -> int:
    with timeout(connection, 60):
        lines = ' '.join(get_verified_response_for_command(
            connection,
            'log_crc32',
            filename,
        ))
        if 'Error' in lines:
            return 0
        return int(lines)


def log_size(connection, filename) -> int:
    lines = ' '.join(get_verified_response_for_command(
        connection,
        'log_size',
        filename,
    ))
    if 'Error' in lines:
        return 0
    return int(lines)


def parse_date(date_str):
    return datetime.datetime.strptime(
        date_str,
        "%Y-%m-%d"
    )


def get_local_file_checksum(filename) -> int:
    with open(filename, 'rb') as inf:
        data = inf.read()

    return binascii.crc32(data)


def main(*args):
    parser = argparse.ArgumentParser()
    parser.add_argument('port')
    parser.add_argument('destination')
    parser.add_argument('--log-level', default='INFO')
    parser.add_argument('--date', type=parse_date)
    args = parser.parse_args()

    logging.basicConfig(
        level=logging.getLevelName(args.log_level)
    )

    connection = serial.Serial(args.port, baudrate=115200, timeout=0.25)

    logs = list(list_logs(connection))
    for filename in logs:
        logger.info('Filename: %s', filename)

        try:
            filename_date = datetime.datetime.strptime(
                filename,
                "%Y/%m/%d/%H%M%S.log"
            )
        except ValueError:
            logger.warning("Unable to parse date.")
            filename_date = datetime.datetime(1970, 1, 1)

        if (
            args.date and
            (
                filename_date < args.date or
                filename_date > args.date + datetime.timedelta(days=1)
            )
        ):
            logger.info("Skipped; date not in requested range")
            continue

        checksum = log_checksum(connection, filename)
        local_checksum = 0
        local_path = os.path.join(
            args.destination,
            filename
        )

        if os.path.exists(local_path):
            local_checksum = get_local_file_checksum(local_path)

        if local_checksum == checksum:
            logger.info('Already downloaded')
            continue

        logger.info('Downloading...')
        os.makedirs(os.path.dirname(local_path), exist_ok=True)
        with open(local_path, 'w') as outf:
            for line in get_log(connection, filename):
                outf.write(line)
                outf.write('\n')


if __name__ == '__main__':
    main(*sys.argv[1:])
