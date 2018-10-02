EESchema Schematic File Version 4
LIBS:maxwell-remote-2-cache
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
L maxwell-remote-2-rescue:Conn_01x10-Connector J5
U 1 1 5B145F18
P 10250 1450
F 0 "J5" H 10330 1442 50  0000 L CNN
F 1 "FPC-1" H 10330 1351 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:10P_FPC_1.0mm" H 10250 1450 50  0001 C CNN
F 3 "~" H 10250 1450 50  0001 C CNN
	1    10250 1450
	1    0    0    -1  
$EndComp
$Comp
L maxwell-remote-2-rescue:Conn_01x10-Connector J6
U 1 1 5B145F48
P 10250 2700
F 0 "J6" H 10330 2692 50  0000 L CNN
F 1 "FPC-2" H 10330 2601 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:10P_FPC_1.0mm" H 10250 2700 50  0001 C CNN
F 3 "~" H 10250 2700 50  0001 C CNN
	1    10250 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5B146099
P 10050 1950
F 0 "#PWR0101" H 10050 1700 50  0001 C CNN
F 1 "GND" V 10055 1822 50  0000 R CNN
F 2 "" H 10050 1950 50  0001 C CNN
F 3 "" H 10050 1950 50  0001 C CNN
	1    10050 1950
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 5B14611E
P 10050 1850
F 0 "#PWR0102" H 10050 1700 50  0001 C CNN
F 1 "+3V3" V 10065 1978 50  0000 L CNN
F 2 "" H 10050 1850 50  0001 C CNN
F 3 "" H 10050 1850 50  0001 C CNN
	1    10050 1850
	0    -1   -1   0   
$EndComp
Text GLabel 10050 1750 0    50   Output ~ 0
CAN_TX
Text GLabel 10050 1650 0    50   Input ~ 0
CAN_RX
Text GLabel 10050 1550 0    50   Output ~ 0
~SPI1_CS_2
Text GLabel 10050 1450 0    50   Output ~ 0
~SPI1_CS_3
Text GLabel 10050 1350 0    50   Output ~ 0
SPI1_MOSI
Text GLabel 10050 1250 0    50   Input ~ 0
SPI1_MISO
Text GLabel 10050 1150 0    50   Output ~ 0
SPI1_SCK
Text GLabel 10050 2800 0    50   Output ~ 0
~ENABLE_CAN
Text GLabel 10050 3100 0    50   Output ~ 0
SCREEN_A0
Text GLabel 10050 3000 0    50   Output ~ 0
~SCREEN_RST
Text GLabel 10050 2900 0    50   Output ~ 0
~SCREEN_CS
Text GLabel 10050 3200 0    50   Output ~ 0
~SPI_CS_4
Text GLabel 10050 2700 0    50   Output ~ 0
~RIGHT_B
Text GLabel 10050 2600 0    50   Output ~ 0
~RIGHT_A
Text GLabel 10050 2500 0    50   Output ~ 0
~LEFT_B
Text GLabel 10050 2400 0    50   Output ~ 0
~LEFT_A
Text GLabel 10050 2300 0    50   BiDi ~ 0
WAKE
Text GLabel 10050 1050 0    50   Output ~ 0
ENABLE_SCREEN
Text GLabel 6450 1350 0    50   Input ~ 0
ENABLE_SCREEN
$Comp
L maxwell-remote-2-rescue:Conn_01x08-Connector J4
U 1 1 5B148703
P 7400 1350
F 0 "J4" H 7479 1342 50  0000 L CNN
F 1 "DISPLAY" H 7479 1251 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B08B-XH-A_08x2.50mm_Straight_LargePads" H 7400 1350 50  0001 C CNN
F 3 "~" H 7400 1350 50  0001 C CNN
	1    7400 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0103
U 1 1 5B148AAB
P 5950 1050
F 0 "#PWR0103" H 5950 900 50  0001 C CNN
F 1 "+BATT" H 5965 1223 50  0000 C CNN
F 2 "" H 5950 1050 50  0001 C CNN
F 3 "" H 5950 1050 50  0001 C CNN
	1    5950 1050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-remote-2-rescue:Conn_01x05-Connector J1
U 1 1 5B148BDD
P 1250 1250
F 0 "J1" H 1170 825 50  0000 C CNN
F 1 "INPUT" H 1170 916 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B05B-XH-A_05x2.50mm_Straight_LargePads" H 1250 1250 50  0001 C CNN
F 3 "~" H 1250 1250 50  0001 C CNN
	1    1250 1250
	-1   0    0    1   
$EndComp
Text GLabel 1450 1050 2    50   BiDi ~ 0
WAKE
$Comp
L power:+BATT #PWR0104
U 1 1 5B148C88
P 2100 800
F 0 "#PWR0104" H 2100 650 50  0001 C CNN
F 1 "+BATT" H 2115 973 50  0000 C CNN
F 2 "" H 2100 800 50  0001 C CNN
F 3 "" H 2100 800 50  0001 C CNN
	1    2100 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5B148CBB
P 1450 1450
F 0 "#PWR0105" H 1450 1200 50  0001 C CNN
F 1 "GND" V 1455 1322 50  0000 R CNN
F 2 "" H 1450 1450 50  0001 C CNN
F 3 "" H 1450 1450 50  0001 C CNN
	1    1450 1450
	1    0    0    -1  
$EndComp
$Comp
L maxwell-remote-2-rescue:MIC5209-ADJ-coddingtonbear U2
U 1 1 5B148E82
P 3350 1250
F 0 "U2" H 3350 1737 60  0000 C CNN
F 1 "MIC5209-ADJ" H 3350 1631 60  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOIC-8" H 3350 1250 60  0001 C CNN
F 3 "" H 3350 1250 60  0001 C CNN
	1    3350 1250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-remote-2-rescue:R-device R2
U 1 1 5B148F2F
P 2550 1050
F 0 "R2" V 2343 1050 50  0000 C CNN
F 1 "10k" V 2434 1050 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2480 1050 50  0001 C CNN
F 3 "" H 2550 1050 50  0001 C CNN
	1    2550 1050
	0    1    1    0   
$EndComp
$Comp
L maxwell-remote-2-rescue:Q_PMOS_GSD-device Q1
U 1 1 5B148F9A
P 1850 1250
F 0 "Q1" V 2193 1250 50  0000 C CNN
F 1 "NDS332P" V 2102 1250 50  0000 C CNN
F 2 "re-innovation/kicad_reinnovation/KiCAD PRETTY/TO_SOT_Packages_SMD.pretty:SOT-23_Handsoldering" H 2050 1350 50  0001 C CNN
F 3 "" H 1850 1250 50  0001 C CNN
	1    1850 1250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 1150 1650 1150
Wire Wire Line
	2050 1150 2100 1150
Wire Wire Line
	2100 1150 2100 1050
$Comp
L power:GND #PWR0106
U 1 1 5B14906D
P 2400 2000
F 0 "#PWR0106" H 2400 1750 50  0001 C CNN
F 1 "GND" V 2405 1872 50  0000 R CNN
F 2 "" H 2400 2000 50  0001 C CNN
F 3 "" H 2400 2000 50  0001 C CNN
	1    2400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1050 2900 1050
Wire Wire Line
	2400 1050 2100 1050
Connection ~ 2100 1050
Wire Wire Line
	2100 1050 2100 800 
Wire Wire Line
	2100 1150 2150 1150
Connection ~ 2100 1150
$Comp
L power:+3V3 #PWR0107
U 1 1 5B149140
P 2500 1250
F 0 "#PWR0107" H 2500 1100 50  0001 C CNN
F 1 "+3V3" V 2515 1378 50  0000 L CNN
F 2 "" H 2500 1250 50  0001 C CNN
F 3 "" H 2500 1250 50  0001 C CNN
	1    2500 1250
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-remote-2-rescue:CP-device C1
U 1 1 5B1491D3
P 2150 1300
F 0 "C1" H 2268 1346 50  0000 L CNN
F 1 "100u" H 2268 1255 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:CP_Tantalum_Case-D_EIA-7343-31_Milling" H 2188 1150 50  0001 C CNN
F 3 "" H 2150 1300 50  0001 C CNN
	1    2150 1300
	1    0    0    -1  
$EndComp
Connection ~ 2150 1150
Wire Wire Line
	2150 1150 2900 1150
$Comp
L maxwell-remote-2-rescue:CP-device C3
U 1 1 5B149293
P 2550 1400
F 0 "C3" H 2668 1446 50  0000 L CNN
F 1 "2.2u" H 2668 1355 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 2588 1250 50  0001 C CNN
F 3 "" H 2550 1400 50  0001 C CNN
	1    2550 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1250 2550 1250
Wire Wire Line
	2900 1250 2750 1250
Connection ~ 2550 1250
$Comp
L maxwell-remote-2-rescue:R-device R3
U 1 1 5B149456
P 2750 1400
F 0 "R3" H 2680 1354 50  0000 R CNN
F 1 "60k" H 2680 1445 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2680 1400 50  0001 C CNN
F 3 "" H 2750 1400 50  0001 C CNN
	1    2750 1400
	-1   0    0    1   
$EndComp
Connection ~ 2750 1250
Wire Wire Line
	2750 1250 2550 1250
$Comp
L maxwell-remote-2-rescue:R-device R4
U 1 1 5B149498
P 2750 1750
F 0 "R4" H 2680 1704 50  0000 R CNN
F 1 "100k" H 2680 1795 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2680 1750 50  0001 C CNN
F 3 "" H 2750 1750 50  0001 C CNN
	1    2750 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 1350 2900 1550
Wire Wire Line
	2900 1550 2750 1550
Wire Wire Line
	2750 1550 2750 1600
Connection ~ 2750 1550
Wire Wire Line
	1850 1450 1850 2000
Wire Wire Line
	1850 2000 2150 2000
Wire Wire Line
	2150 1450 2150 2000
Connection ~ 2150 2000
Wire Wire Line
	2150 2000 2400 2000
Wire Wire Line
	2750 1900 2750 2000
Wire Wire Line
	2750 2000 2550 2000
Connection ~ 2400 2000
Wire Wire Line
	2550 1550 2550 2000
Connection ~ 2550 2000
Wire Wire Line
	2550 2000 2400 2000
$Comp
L power:GND #PWR0108
U 1 1 5B149DAA
P 3800 1400
F 0 "#PWR0108" H 3800 1150 50  0001 C CNN
F 1 "GND" V 3805 1272 50  0000 R CNN
F 2 "" H 3800 1400 50  0001 C CNN
F 3 "" H 3800 1400 50  0001 C CNN
	1    3800 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1050 3800 1150
Wire Wire Line
	3800 1150 3800 1250
Connection ~ 3800 1150
Wire Wire Line
	3800 1250 3800 1350
Connection ~ 3800 1250
Wire Wire Line
	3800 1350 3800 1400
Connection ~ 3800 1350
$Comp
L maxwell-remote-2-rescue:SN65HVD235-interface U1
U 1 1 5B14A98D
P 2350 3050
F 0 "U1" H 2350 3528 50  0000 C CNN
F 1 "SN65HVD235" H 2350 3437 50  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOIC-8" H 2350 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn65hvd234.pdf" H 2250 3450 50  0001 C CNN
	1    2350 3050
	-1   0    0    1   
$EndComp
$Comp
L maxwell-remote-2-rescue:C-device C2
U 1 1 5B14AA77
P 2200 3500
F 0 "C2" V 1948 3500 50  0000 C CNN
F 1 "0.1u" V 2039 3500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 2238 3350 50  0001 C CNN
F 3 "" H 2200 3500 50  0001 C CNN
	1    2200 3500
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR0109
U 1 1 5B14AAD0
P 2350 3650
F 0 "#PWR0109" H 2350 3500 50  0001 C CNN
F 1 "+3V3" V 2365 3778 50  0000 L CNN
F 2 "" H 2350 3650 50  0001 C CNN
F 3 "" H 2350 3650 50  0001 C CNN
	1    2350 3650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5B14AB05
P 2000 3500
F 0 "#PWR0110" H 2000 3250 50  0001 C CNN
F 1 "GND" V 2005 3372 50  0000 R CNN
F 2 "" H 2000 3500 50  0001 C CNN
F 3 "" H 2000 3500 50  0001 C CNN
	1    2000 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 3650 2350 3500
Wire Wire Line
	2350 3500 2350 3350
Connection ~ 2350 3500
Wire Wire Line
	2050 3500 2000 3500
Wire Wire Line
	1450 1350 1750 1350
Wire Wire Line
	1750 1350 1750 2950
Wire Wire Line
	1750 2950 1950 2950
Wire Wire Line
	1450 1250 1700 1250
Wire Wire Line
	1700 1250 1700 2400
Wire Wire Line
	1700 3050 1950 3050
$Comp
L power:GND #PWR0111
U 1 1 5B14C68F
P 2350 2550
F 0 "#PWR0111" H 2350 2300 50  0001 C CNN
F 1 "GND" V 2355 2422 50  0000 R CNN
F 2 "" H 2350 2550 50  0001 C CNN
F 3 "" H 2350 2550 50  0001 C CNN
	1    2350 2550
	-1   0    0    1   
$EndComp
Text GLabel 2900 2850 2    50   Input ~ 0
~ENABLE_CAN
$Comp
L maxwell-remote-2-rescue:R-device R5
U 1 1 5B14C80B
P 2800 2700
F 0 "R5" H 2730 2654 50  0000 R CNN
F 1 "10k" H 2730 2745 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2730 2700 50  0001 C CNN
F 3 "" H 2800 2700 50  0001 C CNN
	1    2800 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 2550 2800 2550
Wire Wire Line
	2350 2550 2350 2650
Connection ~ 2350 2550
Wire Wire Line
	2750 2850 2800 2850
Wire Wire Line
	2800 2850 2900 2850
Connection ~ 2800 2850
$Comp
L maxwell-remote-2-rescue:R-device R1
U 1 1 5B14E249
P 1500 2600
F 0 "R1" H 1430 2554 50  0000 R CNN
F 1 "120" H 1430 2645 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1430 2600 50  0001 C CNN
F 3 "" H 1500 2600 50  0001 C CNN
	1    1500 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1500 2450 1500 2400
Wire Wire Line
	1500 2400 1700 2400
Connection ~ 1700 2400
Wire Wire Line
	1700 2400 1700 3050
Wire Wire Line
	1500 2750 1500 2950
Wire Wire Line
	1500 2950 1750 2950
Connection ~ 1750 2950
Text GLabel 2750 3150 2    50   Input ~ 0
CAN_TX
Text GLabel 2750 3050 2    50   Output ~ 0
CAN_RX
$Comp
L power:GND #PWR0112
U 1 1 5B14F63A
P 7200 1150
F 0 "#PWR0112" H 7200 900 50  0001 C CNN
F 1 "GND" V 7205 1022 50  0000 R CNN
F 2 "" H 7200 1150 50  0001 C CNN
F 3 "" H 7200 1150 50  0001 C CNN
	1    7200 1150
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0113
U 1 1 5B14F695
P 7200 1250
F 0 "#PWR0113" H 7200 1100 50  0001 C CNN
F 1 "+3V3" V 7215 1378 50  0000 L CNN
F 2 "" H 7200 1250 50  0001 C CNN
F 3 "" H 7200 1250 50  0001 C CNN
	1    7200 1250
	0    -1   -1   0   
$EndComp
Text GLabel 7200 1350 0    50   Input ~ 0
~SCREEN_CS
Text GLabel 7200 1450 0    50   Input ~ 0
~SCREEN_RST
Text GLabel 7200 1550 0    50   Input ~ 0
SCREEN_A0
Text GLabel 7200 1650 0    50   Input ~ 0
SPI1_SCK
Text GLabel 7200 1750 0    50   Input ~ 0
SPI1_MOSI
$Comp
L maxwell-remote-2-rescue:Conn_01x03-Connector J2
U 1 1 5B14FA4E
P 5300 2700
F 0 "J2" V 5266 2512 50  0000 R CNN
F 1 "Left" V 5175 2512 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 5300 2700 50  0001 C CNN
F 3 "~" H 5300 2700 50  0001 C CNN
	1    5300 2700
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-remote-2-rescue:Conn_01x03-Connector J3
U 1 1 5B14FAD5
P 6750 2700
F 0 "J3" V 6716 2512 50  0000 R CNN
F 1 "Right" V 6625 2512 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 6750 2700 50  0001 C CNN
F 3 "~" H 6750 2700 50  0001 C CNN
	1    6750 2700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5B14FB6D
P 5200 2900
F 0 "#PWR0114" H 5200 2650 50  0001 C CNN
F 1 "GND" V 5205 2772 50  0000 R CNN
F 2 "" H 5200 2900 50  0001 C CNN
F 3 "" H 5200 2900 50  0001 C CNN
	1    5200 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5B14FB9C
P 6650 2900
F 0 "#PWR0115" H 6650 2650 50  0001 C CNN
F 1 "GND" V 6655 2772 50  0000 R CNN
F 2 "" H 6650 2900 50  0001 C CNN
F 3 "" H 6650 2900 50  0001 C CNN
	1    6650 2900
	1    0    0    -1  
$EndComp
Text GLabel 5300 2900 3    50   Input ~ 0
~LEFT_A
Text GLabel 5400 2900 3    50   Input ~ 0
~LEFT_B
Text GLabel 6750 2900 3    50   Input ~ 0
~RIGHT_A
Text GLabel 6850 2900 3    50   Input ~ 0
~RIGHT_B
$Comp
L maxwell-remote-2-rescue:Q_NMOS_GSD-device Q2
U 1 1 5B1502DD
P 6450 1150
F 0 "Q2" V 6793 1150 50  0000 C CNN
F 1 "NDS332P" V 6702 1150 50  0000 C CNN
F 2 "re-innovation/kicad_reinnovation/KiCAD PRETTY/TO_SOT_Packages_SMD.pretty:SOT-23_Handsoldering" H 6650 1250 50  0001 C CNN
F 3 "" H 6450 1150 50  0001 C CNN
	1    6450 1150
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-remote-2-rescue:Conn_01x07-Connector J7
U 1 1 5B152945
P 7950 3400
F 0 "J7" V 7916 3012 50  0000 R CNN
F 1 "SPI1_A" V 7825 3012 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B07B-XH-A_07x2.50mm_Straight_LargePads" H 7950 3400 50  0001 C CNN
F 3 "~" H 7950 3400 50  0001 C CNN
	1    7950 3400
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-remote-2-rescue:Conn_01x07-Connector J8
U 1 1 5B1529E8
P 7950 3850
F 0 "J8" V 7916 3462 50  0000 R CNN
F 1 "SPI1_B" V 7825 3462 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B07B-XH-A_07x2.50mm_Straight_LargePads" H 7950 3850 50  0001 C CNN
F 3 "~" H 7950 3850 50  0001 C CNN
	1    7950 3850
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-remote-2-rescue:Conn_01x07-Connector J9
U 1 1 5B152A24
P 7950 4350
F 0 "J9" V 7916 3962 50  0000 R CNN
F 1 "SPI1_C" V 7825 3962 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B07B-XH-A_07x2.50mm_Straight_LargePads" H 7950 4350 50  0001 C CNN
F 3 "~" H 7950 4350 50  0001 C CNN
	1    7950 4350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5B152B7C
P 7650 4700
F 0 "#PWR0116" H 7650 4450 50  0001 C CNN
F 1 "GND" V 7655 4572 50  0000 R CNN
F 2 "" H 7650 4700 50  0001 C CNN
F 3 "" H 7650 4700 50  0001 C CNN
	1    7650 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0117
U 1 1 5B152BF0
P 7750 4700
F 0 "#PWR0117" H 7750 4550 50  0001 C CNN
F 1 "+3V3" V 7765 4828 50  0000 L CNN
F 2 "" H 7750 4700 50  0001 C CNN
F 3 "" H 7750 4700 50  0001 C CNN
	1    7750 4700
	-1   0    0    1   
$EndComp
$Comp
L power:+BATT #PWR0118
U 1 1 5B152CB8
P 7850 4700
F 0 "#PWR0118" H 7850 4550 50  0001 C CNN
F 1 "+BATT" H 7865 4873 50  0000 C CNN
F 2 "" H 7850 4700 50  0001 C CNN
F 3 "" H 7850 4700 50  0001 C CNN
	1    7850 4700
	-1   0    0    1   
$EndComp
Text GLabel 7950 4700 3    50   Input ~ 0
SPI1_MOSI
Text GLabel 8050 4700 3    50   Output ~ 0
SPI1_MISO
Text GLabel 8150 4700 3    50   Input ~ 0
SPI1_SCK
Wire Wire Line
	7650 4700 7650 4550
Wire Wire Line
	7650 4550 7650 4050
Connection ~ 7650 4550
Wire Wire Line
	7650 4050 7650 3600
Connection ~ 7650 4050
Wire Wire Line
	7750 4700 7750 4550
Wire Wire Line
	7750 4550 7750 4050
Connection ~ 7750 4550
Wire Wire Line
	7750 4050 7750 3600
Connection ~ 7750 4050
Wire Wire Line
	7850 4700 7850 4550
Wire Wire Line
	7850 4550 7850 4050
Connection ~ 7850 4550
Wire Wire Line
	7850 4050 7850 3600
Connection ~ 7850 4050
Wire Wire Line
	7950 4700 7950 4550
Wire Wire Line
	8050 4700 8050 4550
Wire Wire Line
	8150 4700 8150 4550
Wire Wire Line
	7950 4550 7950 4050
Connection ~ 7950 4550
Wire Wire Line
	7950 4050 7950 3600
Connection ~ 7950 4050
Wire Wire Line
	8050 4550 8050 4050
Connection ~ 8050 4550
Wire Wire Line
	8050 4050 8050 3600
Connection ~ 8050 4050
Wire Wire Line
	8150 4550 8150 4050
Connection ~ 8150 4550
Wire Wire Line
	8150 4050 8150 3600
Connection ~ 8150 4050
Text GLabel 8350 3650 2    50   Input ~ 0
~SPI1_CS_2
Text GLabel 8350 4100 2    50   Input ~ 0
~SPI1_CS_3
Text GLabel 8350 4600 2    50   Input ~ 0
~SPI_CS_4
Wire Wire Line
	8250 3600 8250 3650
Wire Wire Line
	8250 3650 8350 3650
Wire Wire Line
	8350 4100 8250 4100
Wire Wire Line
	8250 4100 8250 4050
Wire Wire Line
	8350 4600 8250 4600
Wire Wire Line
	8250 4600 8250 4550
Text GLabel 1750 2100 2    50   BiDi ~ 0
CAN-
Text GLabel 1700 2100 0    50   BiDi ~ 0
CAN+
Wire Wire Line
	6650 1050 7200 1050
Wire Wire Line
	6250 1050 5950 1050
$EndSCHEMATC
