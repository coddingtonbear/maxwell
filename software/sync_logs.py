import argparse
import logging
import os
import sys
import time

import serial
from typing import Iterable, List


logger = logging.getLogger(__name__)


def send_command(connection, cmd, *args) -> Iterable[str]:
    full_command = ' '.join([
        cmd,
        *args
    ])
    connection.write(full_command.encode('utf-8'))
    connection.write('\n'.encode('utf-8'))

    is_first_line = True
    while True:
        line = connection.readline()
        if is_first_line:
            is_first_line = False
            continue
        if(not line):
            break

        if line.decode('utf-8').strip().startswith('>>'):
            return

        yield line.decode('utf-8').rstrip()


def list_logs(connection) -> List[str]:
    indentations = {}
    logs = []

    for line in send_command(connection, 'log_list'):
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
    for line in send_command(connection, 'log_print', path):
        yield line


def log_size(connection, filename) -> int:
    lines = ' '.join(send_command(
        connection,
        'log_size',
        filename,
    ))
    if 'Error' in lines:
        return 0
    return int(lines)


def main(*args):
    parser = argparse.ArgumentParser()
    parser.add_argument('port')
    parser.add_argument('destination')
    parser.add_argument('--log-level', default='INFO')
    parser.add_argument('--date')
    args = parser.parse_args()

    logging.basicConfig(
        level=logging.getLevelName(args.log_level)
    )

    connection = serial.Serial(args.port, baudrate=115200, timeout=0.25)

    logs = list(list_logs(connection))
    for filename in logs:
        logger.info('Filename: %s', filename)
        remote_size = log_size(connection, filename)
        local_size = 0
        local_path = os.path.join(
            args.destination,
            filename
        )

        if os.path.exists(local_path):
            local_size = os.stat(local_path).st_size

        logger.debug('Local %sb ?= Remote %sb', local_size, remote_size)
        if local_size >= remote_size:
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
