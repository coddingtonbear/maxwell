EESchema Schematic File Version 4
LIBS:maxwell-polarity-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
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
L Connector:Conn_01x02 J?
U 1 1 5A822226
P 1350 900
F 0 "J?" V 1316 712 50  0000 R CNN
F 1 "Output" V 1225 712 50  0000 R CNN
F 2 "monostable/CommonPartsLibrary.pretty:JST_XHP-2" H 1350 900 50  0001 C CNN
F 3 "~" H 1350 900 50  0001 C CNN
	1    1350 900 
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02 J?
U 1 1 5A82222D
P 2600 900
F 0 "J?" V 2566 712 50  0000 R CNN
F 1 "Battery" V 2475 712 50  0000 R CNN
F 2 "monostable/CommonPartsLibrary.pretty:JST_XHP-2" H 2600 900 50  0001 C CNN
F 3 "~" H 2600 900 50  0001 C CNN
	1    2600 900 
	0    -1   -1   0   
$EndComp
$Comp
L coddingtonbear:STT3P2UH7 U?
U 1 1 5A822234
P 1950 1750
F 0 "U?" H 1950 1313 60  0000 C CNN
F 1 "STT3P2UH7" H 1950 1419 60  0000 C CNN
F 2 "freetronics/freetronics_kicad_library/freetronics_footprints.pretty:SOT23-6" H 1950 1750 60  0001 C CNN
F 3 "" H 1950 1750 60  0001 C CNN
	1    1950 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 1800 1500 1800
Wire Wire Line
	2400 1600 2700 1600
Wire Wire Line
	2700 1600 2700 1100
Wire Wire Line
	2400 1700 2700 1700
Wire Wire Line
	2700 1700 2700 1600
Connection ~ 2700 1600
Wire Wire Line
	2400 1800 2700 1800
Wire Wire Line
	2700 1800 2700 1700
Connection ~ 2700 1700
Wire Wire Line
	2400 1900 2700 1900
Wire Wire Line
	2700 1900 2700 1800
Connection ~ 2700 1800
$Comp
L power:GND #PWR?
U 1 1 5A822247
P 950 2500
F 0 "#PWR?" H 950 2250 50  0001 C CNN
F 1 "GND" H 955 2327 50  0000 C CNN
F 2 "" H 950 2500 50  0001 C CNN
F 3 "" H 950 2500 50  0001 C CNN
	1    950  2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1250 1350 1150
Wire Wire Line
	1350 1150 2600 1150
Wire Wire Line
	2600 1150 2600 1100
Connection ~ 1350 1150
Wire Wire Line
	1350 1150 1350 1100
$Comp
L device:R R?
U 1 1 5A822252
P 1100 2250
F 0 "R?" V 893 2250 50  0000 C CNN
F 1 "100k" V 984 2250 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1030 2250 50  0001 C CNN
F 3 "" H 1100 2250 50  0001 C CNN
	1    1100 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	950  2250 950  2500
Wire Wire Line
	1250 2250 1450 2250
Wire Wire Line
	1450 2250 1450 1900
Wire Wire Line
	1450 1900 1500 1900
Wire Wire Line
	1350 1250 950  1250
Wire Wire Line
	950  1250 950  2250
Connection ~ 950  2250
Wire Wire Line
	1450 1100 1450 1800
$EndSCHEMATC
