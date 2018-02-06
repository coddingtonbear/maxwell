EESchema Schematic File Version 4
LIBS:maxwell-polarity-cache
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
P 1550 900
F 0 "J1" V 1516 712 50  0000 R CNN
F 1 "Output" V 1425 712 50  0000 R CNN
F 2 "monostable/CommonPartsLibrary.pretty:JST_XHP-2" H 1550 900 50  0001 C CNN
F 3 "~" H 1550 900 50  0001 C CNN
	1    1550 900 
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02 J2
U 1 1 5A373B83
P 2800 900
F 0 "J2" V 2766 712 50  0000 R CNN
F 1 "Battery" V 2675 712 50  0000 R CNN
F 2 "monostable/CommonPartsLibrary.pretty:JST_XHP-2" H 2800 900 50  0001 C CNN
F 3 "~" H 2800 900 50  0001 C CNN
	1    2800 900 
	0    -1   -1   0   
$EndComp
$Comp
L coddingtonbear:STT3P2UH7 U1
U 1 1 5A373FFB
P 2150 1750
F 0 "U1" H 2150 1313 60  0000 C CNN
F 1 "STT3P2UH7" H 2150 1419 60  0000 C CNN
F 2 "freetronics/freetronics_kicad_library/freetronics_footprints.pretty:SOT23-6" H 2150 1750 60  0001 C CNN
F 3 "" H 2150 1750 60  0001 C CNN
	1    2150 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	1650 1800 1700 1800
Wire Wire Line
	2600 1600 2900 1600
Wire Wire Line
	2900 1600 2900 1100
Wire Wire Line
	2600 1700 2900 1700
Wire Wire Line
	2900 1700 2900 1600
Connection ~ 2900 1600
Wire Wire Line
	2600 1800 2900 1800
Wire Wire Line
	2900 1800 2900 1700
Connection ~ 2900 1700
Wire Wire Line
	2600 1900 2900 1900
Wire Wire Line
	2900 1900 2900 1800
Connection ~ 2900 1800
$Comp
L power:GND #PWR01
U 1 1 5A374253
P 1150 2500
F 0 "#PWR01" H 1150 2250 50  0001 C CNN
F 1 "GND" H 1155 2327 50  0000 C CNN
F 2 "" H 1150 2500 50  0001 C CNN
F 3 "" H 1150 2500 50  0001 C CNN
	1    1150 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1250 1550 1150
Wire Wire Line
	1550 1150 2800 1150
Wire Wire Line
	2800 1150 2800 1100
Connection ~ 1550 1150
Wire Wire Line
	1550 1150 1550 1100
$Comp
L Switch:SW_Push SW1
U 1 1 5A3744CC
P 2050 2250
F 0 "SW1" V 2096 2202 50  0000 R CNN
F 1 "SW_Push" V 2005 2202 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SMD_RED_TACTILE_SWITCH" H 2050 2450 50  0001 C CNN
F 3 "" H 2050 2450 50  0001 C CNN
	1    2050 2250
	1    0    0    -1  
$EndComp
$Comp
L device:R R1
U 1 1 5A3745EC
P 1300 2250
F 0 "R1" V 1093 2250 50  0000 C CNN
F 1 "100k" V 1184 2250 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1230 2250 50  0001 C CNN
F 3 "" H 1300 2250 50  0001 C CNN
	1    1300 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	1150 2250 1150 2500
Wire Wire Line
	1450 2250 1650 2250
Wire Wire Line
	1650 2250 1650 1900
Wire Wire Line
	1650 1900 1700 1900
Wire Wire Line
	1550 1250 1150 1250
Wire Wire Line
	1150 1250 1150 2250
Connection ~ 1150 2250
Wire Wire Line
	1650 1100 1650 1800
Wire Wire Line
	1850 2250 1650 2250
Connection ~ 1650 2250
Wire Wire Line
	2250 2250 2900 2250
Wire Wire Line
	2900 2250 2900 1900
Connection ~ 2900 1900
$Comp
L MCU_ST_STM32:STM32F103C8Tx U?
U 1 1 5A76A5A2
P 7750 2750
F 0 "U?" H 7750 4728 50  0000 C CNN
F 1 "STM32F103C8Tx" H 7750 4637 50  0000 C CNN
F 2 "Housings_QFP:LQFP-48_7x7mm_Pitch0.5mm" H 10550 4425 50  0001 R TNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 7750 2750 50  0001 C CNN
	1    7750 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04 J?
U 1 1 5A76A704
P 1150 3200
F 0 "J?" H 1070 2775 50  0000 C CNN
F 1 "Conn_01x04" H 1070 2866 50  0000 C CNN
F 2 "" H 1150 3200 50  0001 C CNN
F 3 "~" H 1150 3200 50  0001 C CNN
	1    1150 3200
	-1   0    0    1   
$EndComp
$EndSCHEMATC
