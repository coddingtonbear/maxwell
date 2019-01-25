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
L Connector_Generic:Conn_01x01 J1
U 1 1 5C4A76AE
P 3350 1950
F 0 "J1" H 3270 1725 50  0000 C CNN
F 1 "INPUT+" H 3270 1816 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3350 1950 50  0001 C CNN
F 3 "~" H 3350 1950 50  0001 C CNN
	1    3350 1950
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5C4A7879
P 3350 2350
F 0 "J2" H 3270 2125 50  0000 C CNN
F 1 "INPUT-" H 3270 2216 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3350 2350 50  0001 C CNN
F 3 "~" H 3350 2350 50  0001 C CNN
	1    3350 2350
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 5C4A78E5
P 8550 1950
F 0 "J3" H 8630 1992 50  0000 L CNN
F 1 "VCC+" H 8630 1901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8550 1950 50  0001 C CNN
F 3 "~" H 8550 1950 50  0001 C CNN
	1    8550 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5C4A7A06
P 8550 2350
F 0 "J4" H 8630 2392 50  0000 L CNN
F 1 "VCC-" H 8630 2301 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8550 2350 50  0001 C CNN
F 3 "~" H 8550 2350 50  0001 C CNN
	1    8550 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5C4A7D34
P 4450 2100
F 0 "C1" H 4568 2146 50  0000 L CNN
F 1 "220u" H 4568 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_Elec_8x10.2" H 4488 1950 50  0001 C CNN
F 3 "~" H 4450 2100 50  0001 C CNN
	1    4450 2100
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:LT3086IR U1
U 1 1 5C4A832A
P 5900 2100
F 0 "U1" H 5825 2515 50  0000 C CNN
F 1 "LT3086IR" H 5825 2424 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-7_TabPin4" H 5900 2100 50  0001 C CNN
F 3 "" H 5900 2100 50  0001 C CNN
	1    5900 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1950 4450 1950
Wire Wire Line
	3550 2350 4450 2350
Wire Wire Line
	4450 2350 4450 2250
Wire Wire Line
	5900 2600 4450 2600
Wire Wire Line
	4450 2600 4450 2350
Connection ~ 4450 2350
Wire Wire Line
	4450 1950 5050 1950
Wire Wire Line
	5300 1950 5300 2000
Connection ~ 4450 1950
Wire Wire Line
	5300 2150 5050 2150
Wire Wire Line
	5050 2150 5050 1950
Connection ~ 5050 1950
Wire Wire Line
	5050 1950 5300 1950
$Comp
L Device:R R1
U 1 1 5C4A853E
P 6550 2100
F 0 "R1" H 6620 2146 50  0000 L CNN
F 1 "82k" H 6620 2055 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 6480 2100 50  0001 C CNN
F 3 "~" H 6550 2100 50  0001 C CNN
	1    6550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2150 6350 2250
Wire Wire Line
	6350 2250 6550 2250
Wire Wire Line
	6350 2000 6350 1950
Wire Wire Line
	6350 1950 6550 1950
Wire Wire Line
	6550 1950 7850 1950
Connection ~ 6550 1950
Wire Wire Line
	5900 2600 7850 2600
Wire Wire Line
	8350 2600 8350 2350
Connection ~ 5900 2600
$Comp
L Device:CP C2
U 1 1 5C4A8D42
P 7850 2250
F 0 "C2" H 7968 2296 50  0000 L CNN
F 1 "0.1" H 7968 2205 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 7888 2100 50  0001 C CNN
F 3 "~" H 7850 2250 50  0001 C CNN
	1    7850 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2100 7850 1950
Connection ~ 7850 1950
Wire Wire Line
	7850 1950 8350 1950
Wire Wire Line
	7850 2400 7850 2600
Connection ~ 7850 2600
Wire Wire Line
	7850 2600 8350 2600
$EndSCHEMATC
