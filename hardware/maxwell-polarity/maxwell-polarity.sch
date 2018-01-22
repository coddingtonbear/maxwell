EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x02 J1
U 1 1 5A373B31
P 3450 2100
F 0 "J1" V 3416 1912 50  0000 R CNN
F 1 "Battery" V 3325 1912 50  0000 R CNN
F 2 "monostable/CommonPartsLibrary.pretty:JST_XHP-2" H 3450 2100 50  0001 C CNN
F 3 "~" H 3450 2100 50  0001 C CNN
	1    3450 2100
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02 J2
U 1 1 5A373B83
P 4700 2100
F 0 "J2" V 4666 1912 50  0000 R CNN
F 1 "Output" V 4575 1912 50  0000 R CNN
F 2 "monostable/CommonPartsLibrary.pretty:JST_XHP-2" H 4700 2100 50  0001 C CNN
F 3 "~" H 4700 2100 50  0001 C CNN
	1    4700 2100
	0    -1   -1   0   
$EndComp
$Comp
L coddingtonbear:STT3P2UH7 U1
U 1 1 5A373FFB
P 4050 2950
F 0 "U1" H 4050 2513 60  0000 C CNN
F 1 "STT3P2UH7" H 4050 2619 60  0000 C CNN
F 2 "freetronics/freetronics_kicad_library/freetronics_footprints.pretty:SOT23-6" H 4050 2950 60  0001 C CNN
F 3 "" H 4050 2950 60  0001 C CNN
	1    4050 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	3550 2300 3550 2700
Wire Wire Line
	3550 3000 3600 3000
Wire Wire Line
	4500 2800 4800 2800
Wire Wire Line
	4800 2800 4800 2300
Wire Wire Line
	4500 2900 4800 2900
Wire Wire Line
	4800 2900 4800 2800
Connection ~ 4800 2800
Wire Wire Line
	4500 3000 4800 3000
Wire Wire Line
	4800 3000 4800 2900
Connection ~ 4800 2900
Wire Wire Line
	4500 3100 4800 3100
Wire Wire Line
	4800 3100 4800 3000
Connection ~ 4800 3000
$Comp
L power:GND #PWR01
U 1 1 5A374253
P 3050 3700
F 0 "#PWR01" H 3050 3450 50  0001 C CNN
F 1 "GND" H 3055 3527 50  0000 C CNN
F 2 "" H 3050 3700 50  0001 C CNN
F 3 "" H 3050 3700 50  0001 C CNN
	1    3050 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 2450 3450 2350
Wire Wire Line
	3450 2350 4700 2350
Wire Wire Line
	4700 2350 4700 2300
Connection ~ 3450 2350
Wire Wire Line
	3450 2350 3450 2300
$Comp
L Switch:SW_Push SW1
U 1 1 5A3744CC
P 3250 2900
F 0 "SW1" V 3296 2852 50  0000 R CNN
F 1 "SW_Push" V 3205 2852 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SMD_RED_TACTILE_SWITCH" H 3250 3100 50  0001 C CNN
F 3 "" H 3250 3100 50  0001 C CNN
	1    3250 2900
	0    -1   -1   0   
$EndComp
$Comp
L device:R R1
U 1 1 5A3745EC
P 3200 3450
F 0 "R1" V 2993 3450 50  0000 C CNN
F 1 "100k" V 3084 3450 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 3130 3450 50  0001 C CNN
F 3 "" H 3200 3450 50  0001 C CNN
	1    3200 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 3450 3050 3700
Wire Wire Line
	3350 3450 3550 3450
Wire Wire Line
	3550 3450 3550 3100
Wire Wire Line
	3550 3100 3600 3100
Connection ~ 3550 3100
Wire Wire Line
	3250 3100 3550 3100
Wire Wire Line
	3250 2700 3550 2700
Connection ~ 3550 2700
Wire Wire Line
	3550 2700 3550 3000
Wire Wire Line
	3450 2450 3050 2450
Wire Wire Line
	3050 2450 3050 3450
Connection ~ 3050 3450
$EndSCHEMATC