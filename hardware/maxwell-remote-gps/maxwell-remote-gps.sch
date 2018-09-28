EESchema Schematic File Version 4
LIBS:maxwell-remote-gps-cache
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
L FPGMMOPA6H:FGPMMOPA6C U2
U 1 1 5BA00BAD
P 8350 1600
F 0 "U2" H 7950 2437 60  0000 C CNN
F 1 "FGPMMOPA6C" H 7950 2331 60  0000 C CNN
F 2 "coddingtonbear:FGPMMOPA6C" H 7950 2200 60  0001 C CNN
F 3 "" H 7950 2200 60  0000 C CNN
	1    8350 1600
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:SC16IS752IPW U1
U 1 1 5BA00DD5
P 5000 2750
F 0 "U1" H 5000 3837 60  0000 C CNN
F 1 "SC16IS752IPW" H 5000 3731 60  0000 C CNN
F 2 "Package_SO:TSSOP-28_4.4x9.7mm_P0.65mm" H 5000 3700 60  0001 C CNN
F 3 "" H 5000 3700 60  0000 C CNN
	1    5000 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J1
U 1 1 5BA0101C
P 1300 1450
F 0 "J1" H 1220 925 50  0000 C CNN
F 1 "IO" H 1220 1016 50  0000 C CNN
F 2 "coddingtonbear:JST_XH_B07B-XH-A_07x2.50mm_Straight_LargePads" H 1300 1450 50  0001 C CNN
F 3 "~" H 1300 1450 50  0001 C CNN
	1    1300 1450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5BA01110
P 1600 1150
F 0 "#PWR0101" H 1600 900 50  0001 C CNN
F 1 "GND" H 1605 977 50  0000 C CNN
F 2 "" H 1600 1150 50  0001 C CNN
F 3 "" H 1600 1150 50  0001 C CNN
	1    1600 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 5BA0117A
P 1750 950
F 0 "#PWR0102" H 1750 800 50  0001 C CNN
F 1 "+3V3" H 1765 1123 50  0000 C CNN
F 2 "" H 1750 950 50  0001 C CNN
F 3 "" H 1750 950 50  0001 C CNN
	1    1750 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0103
U 1 1 5BA011F9
P 1900 1350
F 0 "#PWR0103" H 1900 1200 50  0001 C CNN
F 1 "+BATT" H 1915 1523 50  0000 C CNN
F 2 "" H 1900 1350 50  0001 C CNN
F 3 "" H 1900 1350 50  0001 C CNN
	1    1900 1350
	1    0    0    -1  
$EndComp
Text GLabel 1500 1450 2    50   Output ~ 0
MOSI
Text GLabel 1500 1550 2    50   Input ~ 0
MISO
Text GLabel 1500 1650 2    50   Output ~ 0
SCK
Text GLabel 1500 1750 2    50   Output ~ 0
CS
Wire Wire Line
	1500 1150 1600 1150
Wire Wire Line
	1500 1250 1750 1250
Wire Wire Line
	1900 1350 1500 1350
$Comp
L power:+3V3 #PWR0104
U 1 1 5BA012F8
P 3700 1950
F 0 "#PWR0104" H 3700 1800 50  0001 C CNN
F 1 "+3V3" H 3715 2123 50  0000 C CNN
F 2 "" H 3700 1950 50  0001 C CNN
F 3 "" H 3700 1950 50  0001 C CNN
	1    3700 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5BA01389
P 3700 2100
F 0 "C3" H 3815 2146 50  0000 L CNN
F 1 "0.1u" H 3815 2055 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 3738 1950 50  0001 C CNN
F 3 "~" H 3700 2100 50  0001 C CNN
	1    3700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1950 4050 1950
Connection ~ 3700 1950
$Comp
L power:GND #PWR0105
U 1 1 5BA01463
P 3700 2250
F 0 "#PWR0105" H 3700 2000 50  0001 C CNN
F 1 "GND" H 3705 2077 50  0000 C CNN
F 2 "" H 3700 2250 50  0001 C CNN
F 3 "" H 3700 2250 50  0001 C CNN
	1    3700 2250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 5BA01476
P 6450 700
F 0 "#PWR0106" H 6450 550 50  0001 C CNN
F 1 "+3V3" H 6465 873 50  0000 C CNN
F 2 "" H 6450 700 50  0001 C CNN
F 3 "" H 6450 700 50  0001 C CNN
	1    6450 700 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5BA01489
P 7100 1250
F 0 "C4" H 7215 1296 50  0000 L CNN
F 1 "0.1u" H 7215 1205 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 7138 1100 50  0001 C CNN
F 3 "~" H 7100 1250 50  0001 C CNN
	1    7100 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5BA01529
P 6600 1450
F 0 "#PWR0107" H 6600 1200 50  0001 C CNN
F 1 "GND" H 6605 1277 50  0000 C CNN
F 2 "" H 6600 1450 50  0001 C CNN
F 3 "" H 6600 1450 50  0001 C CNN
	1    6600 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5BA015AB
P 4150 3700
F 0 "#PWR0108" H 4150 3450 50  0001 C CNN
F 1 "GND" H 4155 3527 50  0000 C CNN
F 2 "" H 4150 3700 50  0001 C CNN
F 3 "" H 4150 3700 50  0001 C CNN
	1    4150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3650 4150 3650
Wire Wire Line
	4150 3650 4150 3700
Text GLabel 4200 2650 0    50   Input ~ 0
MOSI
Text GLabel 4200 2750 0    50   Output ~ 0
MISO
Text GLabel 4200 2850 0    50   Input ~ 0
SCK
Wire Wire Line
	4200 2150 4050 2150
Wire Wire Line
	4050 2150 4050 1950
Connection ~ 4050 1950
Wire Wire Line
	4050 1950 3950 1950
$Comp
L power:GND #PWR0109
U 1 1 5BA0173C
P 4200 3150
F 0 "#PWR0109" H 4200 2900 50  0001 C CNN
F 1 "GND" H 4205 2977 50  0000 C CNN
F 2 "" H 4200 3150 50  0001 C CNN
F 3 "" H 4200 3150 50  0001 C CNN
	1    4200 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5BA01859
P 3950 2100
F 0 "R1" H 4020 2146 50  0000 L CNN
F 1 "1k" H 4020 2055 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 3880 2100 50  0001 C CNN
F 3 "~" H 3950 2100 50  0001 C CNN
	1    3950 2100
	1    0    0    -1  
$EndComp
Connection ~ 3950 1950
Wire Wire Line
	3950 1950 3700 1950
Wire Wire Line
	4200 2350 3950 2350
Wire Wire Line
	3950 2350 3950 2250
$Comp
L power:GND #PWR0110
U 1 1 5BA02178
P 8700 2050
F 0 "#PWR0110" H 8700 1800 50  0001 C CNN
F 1 "GND" H 8705 1877 50  0000 C CNN
F 2 "" H 8700 2050 50  0001 C CNN
F 3 "" H 8700 2050 50  0001 C CNN
	1    8700 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 2050 8700 2050
$Comp
L Device:Crystal Y1
U 1 1 5BA0276E
P 3750 3450
F 0 "Y1" V 3704 3581 50  0000 L CNN
F 1 "14.7456M" V 3795 3581 50  0000 L CNN
F 2 "coddingtonbear:Crystal_HC49-U_Vertical_LargePads" H 3750 3450 50  0001 C CNN
F 3 "~" H 3750 3450 50  0001 C CNN
	1    3750 3450
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5BA02806
P 3500 3300
F 0 "C1" V 3248 3300 50  0000 C CNN
F 1 "22p" V 3339 3300 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 3538 3150 50  0001 C CNN
F 3 "~" H 3500 3300 50  0001 C CNN
	1    3500 3300
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5BA0285D
P 3500 3600
F 0 "C2" V 3248 3600 50  0000 C CNN
F 1 "22p" V 3339 3600 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 3538 3450 50  0001 C CNN
F 3 "~" H 3500 3600 50  0001 C CNN
	1    3500 3600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5BA02893
P 3200 3600
F 0 "#PWR0112" H 3200 3350 50  0001 C CNN
F 1 "GND" H 3205 3427 50  0000 C CNN
F 2 "" H 3200 3600 50  0001 C CNN
F 3 "" H 3200 3600 50  0001 C CNN
	1    3200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 3300 3750 3300
Wire Wire Line
	3750 3600 3650 3600
Wire Wire Line
	3350 3300 3200 3300
Wire Wire Line
	3200 3300 3200 3600
Wire Wire Line
	3350 3600 3200 3600
Connection ~ 3200 3600
Wire Wire Line
	3750 3600 4000 3600
Wire Wire Line
	4000 3600 4000 3450
Wire Wire Line
	4000 3450 4200 3450
Connection ~ 3750 3600
Wire Wire Line
	4200 3350 3900 3350
Wire Wire Line
	3900 3350 3900 3300
Wire Wire Line
	3900 3300 3750 3300
Connection ~ 3750 3300
Text GLabel 4200 2550 0    50   Input ~ 0
CS
Wire Wire Line
	8650 1950 8700 1950
Wire Wire Line
	8700 1950 8700 2050
Wire Wire Line
	8650 1850 8700 1850
Wire Wire Line
	8700 1850 8700 1950
Connection ~ 8700 1950
$Comp
L Device:Battery_Cell BT1
U 1 1 5BA051E4
P 5750 1350
F 0 "BT1" H 5868 1446 50  0000 L CNN
F 1 "Battery_Cell" H 5868 1355 50  0000 L CNN
F 2 "coddingtonbear:JST_EH_B02B-EH-A_02x2.50mm_Straight_LargePads" V 5750 1410 50  0001 C CNN
F 3 "~" V 5750 1410 50  0001 C CNN
	1    5750 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5BA052F0
P 5750 1450
F 0 "#PWR0113" H 5750 1200 50  0001 C CNN
F 1 "GND" H 5755 1277 50  0000 C CNN
F 2 "" H 5750 1450 50  0001 C CNN
F 3 "" H 5750 1450 50  0001 C CNN
	1    5750 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1700 6350 1150
Wire Wire Line
	6350 1150 5750 1150
Wire Wire Line
	7250 1950 7150 1950
$Comp
L power:GND #PWR0114
U 1 1 5BA0A6E4
P 6300 2250
F 0 "#PWR0114" H 6300 2000 50  0001 C CNN
F 1 "GND" H 6305 2077 50  0000 C CNN
F 2 "" H 6300 2250 50  0001 C CNN
F 3 "" H 6300 2250 50  0001 C CNN
	1    6300 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2050 5850 2050
Wire Wire Line
	5850 2050 5850 1950
Wire Wire Line
	5800 1950 5800 1900
Wire Wire Line
	5800 1900 5900 1900
Wire Wire Line
	5900 1900 5900 2050
Wire Wire Line
	6350 1700 6750 1700
Wire Wire Line
	6750 1700 6750 1500
Wire Wire Line
	6900 1500 6900 1450
Wire Wire Line
	6900 1450 7250 1450
Wire Wire Line
	6750 1500 6900 1500
Wire Wire Line
	6800 2550 5800 2550
Wire Wire Line
	5800 2650 6850 2650
Wire Wire Line
	7250 1550 6850 1550
Wire Wire Line
	6850 1550 6850 2650
Wire Wire Line
	6800 2550 6800 1650
Wire Wire Line
	6800 1650 7250 1650
Wire Wire Line
	7150 2950 5800 2950
Wire Wire Line
	7150 1950 7150 2950
Wire Wire Line
	7250 3050 5800 3050
Wire Wire Line
	7250 2050 7250 3050
$Comp
L power:GND #PWR0111
U 1 1 5BA1AC95
P 4200 2950
F 0 "#PWR0111" H 4200 2700 50  0001 C CNN
F 1 "GND" H 4205 2777 50  0000 C CNN
F 2 "" H 4200 2950 50  0001 C CNN
F 3 "" H 4200 2950 50  0001 C CNN
	1    4200 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1750 7000 1750
$Comp
L power:GND #PWR0115
U 1 1 5BA0218F
P 7000 1750
F 0 "#PWR0115" H 7000 1500 50  0001 C CNN
F 1 "GND" H 7005 1577 50  0000 C CNN
F 2 "" H 7000 1750 50  0001 C CNN
F 3 "" H 7000 1750 50  0001 C CNN
	1    7000 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1850 7100 1750
Wire Wire Line
	7250 1850 7100 1850
Connection ~ 8700 2050
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 5BADD758
P 6800 1000
F 0 "Q1" V 7050 1000 50  0000 C CNN
F 1 "NTR1P02T1" V 7141 1000 50  0000 C CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 7000 1100 50  0001 C CNN
F 3 "~" H 6800 1000 50  0001 C CNN
	1    6800 1000
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5BADF797
P 6650 800
F 0 "R3" V 6443 800 50  0000 C CNN
F 1 "10k" V 6534 800 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 6580 800 50  0001 C CNN
F 3 "~" H 6650 800 50  0001 C CNN
	1    6650 800 
	0    1    1    0   
$EndComp
Text GLabel 6800 800  2    50   Input ~ 0
~EN_GPS
Text GLabel 5800 2450 2    50   Output ~ 0
~EN_GPS
$Comp
L Device:R R2
U 1 1 5BAE2014
P 1750 1100
F 0 "R2" H 1820 1146 50  0000 L CNN
F 1 "0" H 1820 1055 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 1680 1100 50  0001 C CNN
F 3 "~" H 1750 1100 50  0001 C CNN
	1    1750 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1450 6600 1400
Wire Wire Line
	6600 1400 7100 1400
Wire Wire Line
	7250 1350 7250 1400
Wire Wire Line
	7250 1400 7100 1400
Connection ~ 7100 1400
Wire Wire Line
	7250 1150 7250 1100
Wire Wire Line
	7250 1100 7100 1100
Wire Wire Line
	7000 1100 7100 1100
Connection ~ 7100 1100
Wire Wire Line
	6600 1100 6450 1100
Wire Wire Line
	6450 1100 6450 800 
Wire Wire Line
	6500 800  6450 800 
Connection ~ 6450 800 
Wire Wire Line
	6450 800  6450 700 
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 5BAE9B28
P 6500 2050
F 0 "J2" H 6600 2250 50  0000 L CNN
F 1 "UART-A" V 6650 1850 50  0000 L CNN
F 2 "coddingtonbear:JST_EH_B05B-EH-A_05x2.50mm_Straight_LargePads" H 6500 2050 50  0001 C CNN
F 3 "~" H 6500 2050 50  0001 C CNN
	1    6500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2350 5850 2350
Wire Wire Line
	5850 2350 5850 2150
$Comp
L power:+3V3 #PWR0116
U 1 1 5BAEB0A1
P 6200 1850
F 0 "#PWR0116" H 6200 1700 50  0001 C CNN
F 1 "+3V3" H 6215 2023 50  0000 C CNN
F 2 "" H 6200 1850 50  0001 C CNN
F 3 "" H 6200 1850 50  0001 C CNN
	1    6200 1850
	1    0    0    -1  
$EndComp
Text Label 6200 2550 0    50   ~ 0
3DFIX(GPIO6)
Text Label 6200 2650 0    50   ~ 0
1PPS(GPIO7)
Text Label 6300 2950 0    50   ~ 0
RX-B
Text Label 6300 3050 0    50   ~ 0
TX-B
Text Label 6000 1950 0    50   ~ 0
TX-A
Text Label 6000 2050 0    50   ~ 0
RX-A
Text Label 6000 2150 0    50   ~ 0
GPIO5
Wire Wire Line
	5850 2150 6300 2150
Wire Wire Line
	5900 2050 6300 2050
Wire Wire Line
	5850 1950 6300 1950
Wire Wire Line
	6300 1850 6200 1850
Text Label 5800 1150 0    50   ~ 0
VBACKUP
$EndSCHEMATC
