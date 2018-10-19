EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 28 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L maxwell-rescue:Conn_01x02-RESCUE-maxwell J7
U 1 1 5A1FF249
P 1500 1100
F 0 "J7" H 1579 1092 50  0000 L CNN
F 1 "Dynamo Input" H 1579 1001 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 1500 1100 50  0001 C CNN
F 3 "" H 1500 1100 50  0001 C CNN
	1    1500 1100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:TLP185(SE-RESCUE-maxwell U8
U 1 1 5A1FF25C
P 1800 2700
F 0 "U8" H 1800 3025 50  0000 C CNN
F 1 "TLP188" H 1800 2934 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SO-4_Milling" H 1800 2400 50  0001 C CIN
F 3 "" H 1800 2700 50  0001 L CNN
	1    1800 2700
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:D-RESCUE-maxwell D1
U 1 1 5A1FF263
P 1500 3250
F 0 "D1" V 1546 3171 50  0000 R CNN
F 1 "GS1M-LTP" V 1455 3171 50  0000 R CNN
F 2 "mcous/kicad-lib/footprints/diode.pretty:DO-214AC" H 1500 3250 50  0001 C CNN
F 3 "" H 1500 3250 50  0001 C CNN
	1    1500 3250
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR032
U 1 1 5A1FF277
P 2100 2600
F 0 "#PWR032" H 2100 2450 50  0001 C CNN
F 1 "+3V3" H 2115 2773 50  0000 C CNN
F 2 "" H 2100 2600 50  0001 C CNN
F 3 "" H 2100 2600 50  0001 C CNN
	1    2100 2600
	1    0    0    -1  
$EndComp
Text GLabel 2100 3100 3    60   Output ~ 0
SPEED
$Comp
L maxwell-rescue:D_Bridge_+-AA-RESCUE-maxwell D4
U 1 1 5A1FF27E
P 3350 1250
F 0 "D4" H 3691 1296 50  0000 L CNN
F 1 "MB24S" H 3691 1205 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SO-4_Milling" H 3350 1250 50  0001 C CNN
F 3 "" H 3350 1250 50  0001 C CNN
	1    3350 1250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR033
U 1 1 5A1FF28B
P 3050 1250
F 0 "#PWR033" H 3050 1000 50  0001 C CNN
F 1 "GND" V 3055 1122 50  0000 R CNN
F 2 "" H 3050 1250 50  0001 C CNN
F 3 "" H 3050 1250 50  0001 C CNN
	1    3050 1250
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R14
U 1 1 5A1FF297
P 1500 2950
F 0 "R14" H 1570 2996 50  0000 L CNN
F 1 "200" H 1570 2905 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1430 2950 50  0001 C CNN
F 3 "" H 1500 2950 50  0001 C CNN
	1    1500 2950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:BOOST_BOARD-RESCUE-maxwell U9
U 1 1 5A1FFDEF
P 4700 1300
F 0 "U9" H 4675 1637 60  0000 C CNN
F 1 "Buck Regulator" H 4675 1531 60  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:BOOST_LM2596_3A" H 4700 1300 60  0001 C CNN
F 3 "" H 4700 1300 60  0001 C CNN
	1    4700 1300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR038
U 1 1 5A1FFDF6
P 4200 1350
F 0 "#PWR038" H 4200 1100 50  0001 C CNN
F 1 "GND" H 4205 1177 50  0000 C CNN
F 2 "" H 4200 1350 50  0001 C CNN
F 3 "" H 4200 1350 50  0001 C CNN
	1    4200 1350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR039
U 1 1 5A1FFDFC
P 5150 1350
F 0 "#PWR039" H 5150 1100 50  0001 C CNN
F 1 "GND" H 5155 1177 50  0000 C CNN
F 2 "" H 5150 1350 50  0001 C CNN
F 3 "" H 5150 1350 50  0001 C CNN
	1    5150 1350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:MCP73831T-RESCUE-maxwell U*1
U 1 1 5A2102FA
P 6850 1600
F 0 "U*1" H 6850 2197 60  0000 C CNN
F 1 "MCP73831T" H 6850 2091 60  0000 C CNN
F 2 "apexelectrix/apex-smd.pretty:SOT-23-5" H 6850 1300 60  0001 C CNN
F 3 "" H 6850 1300 60  0000 C CNN
	1    6850 1600
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x02-RESCUE-maxwell J9
U 1 1 5A21040E
P 8600 1250
F 0 "J9" H 8680 1242 50  0000 L CNN
F 1 "Battery" H 8680 1151 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 8600 1250 50  0001 C CNN
F 3 "" H 8600 1250 50  0001 C CNN
	1    8600 1250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR041
U 1 1 5A21058A
P 7350 1900
F 0 "#PWR041" H 7350 1650 50  0001 C CNN
F 1 "GND" H 7355 1727 50  0000 C CNN
F 2 "" H 7350 1900 50  0001 C CNN
F 3 "" H 7350 1900 50  0001 C CNN
	1    7350 1900
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR042
U 1 1 5A210626
P 8400 1250
F 0 "#PWR042" H 8400 1000 50  0001 C CNN
F 1 "GND" H 8405 1077 50  0000 C CNN
F 2 "" H 8400 1250 50  0001 C CNN
F 3 "" H 8400 1250 50  0001 C CNN
	1    8400 1250
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R19
U 1 1 5A210718
P 7450 1650
F 0 "R19" H 7520 1696 50  0000 L CNN
F 1 "2k" H 7520 1605 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 7380 1650 50  0001 C CNN
F 3 "" H 7450 1650 50  0001 C CNN
	1    7450 1650
	1    0    0    -1  
$EndComp
Text GLabel 6400 2200 2    60   Output ~ 0
~BATT_CHARGING
Text Notes 4400 1550 0    60   ~ 0
Tune to 4.25
$Comp
L maxwell-rescue:C-RESCUE-maxwell C18
U 1 1 5A22422F
P 5900 1450
F 0 "C18" H 5785 1404 50  0000 R CNN
F 1 "100nF" H 5785 1495 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5938 1300 50  0001 C CNN
F 3 "" H 5900 1450 50  0001 C CNN
	1    5900 1450
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR045
U 1 1 5A2243E8
P 5900 2050
F 0 "#PWR045" H 5900 1800 50  0001 C CNN
F 1 "GND" H 5905 1877 50  0000 C CNN
F 2 "" H 5900 2050 50  0001 C CNN
F 3 "" H 5900 2050 50  0001 C CNN
	1    5900 2050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R20
U 1 1 5A245A23
P 9300 1950
F 0 "R20" H 9370 1996 50  0000 L CNN
F 1 "ANY" H 9370 1905 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9230 1950 50  0001 C CNN
F 3 "" H 9300 1950 50  0001 C CNN
	1    9300 1950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R21
U 1 1 5A245A89
P 9300 2350
F 0 "R21" H 9370 2396 50  0000 L CNN
F 1 "ANY" H 9370 2305 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9230 2350 50  0001 C CNN
F 3 "" H 9300 2350 50  0001 C CNN
	1    9300 2350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R23
U 1 1 5A245B4A
P 10100 1950
F 0 "R23" H 10170 1996 50  0000 L CNN
F 1 "ANY" H 10170 1905 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10030 1950 50  0001 C CNN
F 3 "" H 10100 1950 50  0001 C CNN
	1    10100 1950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R24
U 1 1 5A245B93
P 10100 2350
F 0 "R24" H 10170 2396 50  0000 L CNN
F 1 "ANY" H 10170 2305 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10030 2350 50  0001 C CNN
F 3 "" H 10100 2350 50  0001 C CNN
	1    10100 2350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R22
U 1 1 5A246038
P 9700 1100
F 0 "R22" V 9493 1100 50  0000 C CNN
F 1 "0.02" V 9584 1100 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9630 1100 50  0001 C CNN
F 3 "" H 9700 1100 50  0001 C CNN
	1    9700 1100
	0    1    1    0   
$EndComp
Text GLabel 9900 2800 3    60   Output ~ 0
CURRENT_SENSE
Text GLabel 9500 2800 3    60   Output ~ 0
BATT_VOLTAGE
$Comp
L maxwell-rescue:CP-RESCUE-maxwell C17
U 1 1 5A24B0B8
P 5650 1450
F 0 "C17" H 5768 1496 50  0000 L CNN
F 1 "0.1" H 5768 1405 50  0000 L CNN
F 2 "fruchti/fruchtilib/mod/rcl.pretty:CP_13mm_200" H 5688 1300 50  0001 C CNN
F 3 "" H 5650 1450 50  0001 C CNN
	1    5650 1450
	1    0    0    -1  
$EndComp
Text GLabel 1300 1200 0    60   Input ~ 0
DYNAMO_NEUTRAL
Text GLabel 1350 3500 0    60   Input ~ 0
DYNAMO_NEUTRAL
Text GLabel 5500 950  2    60   Input ~ 0
~BATT_CHARGE_ENABLE
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR043
U 1 1 5A210C7A
P 9950 1100
F 0 "#PWR043" H 9950 950 50  0001 C CNN
F 1 "+BATT" H 9965 1273 50  0000 C CNN
F 2 "" H 9950 1100 50  0001 C CNN
F 3 "" H 9950 1100 50  0001 C CNN
	1    9950 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 900  3350 950 
Wire Wire Line
	5600 1250 5650 1250
Wire Wire Line
	5900 1300 5900 1250
Connection ~ 5900 1250
Wire Wire Line
	5650 1300 5650 1250
Connection ~ 5650 1250
Wire Wire Line
	6400 1750 6300 1750
Wire Wire Line
	6300 1750 6300 2200
Wire Wire Line
	6300 2200 6400 2200
Wire Wire Line
	9300 2100 9300 2150
Wire Wire Line
	10100 2100 10100 2150
Wire Wire Line
	9300 2500 9300 2550
Wire Wire Line
	9300 2550 10100 2550
Wire Wire Line
	10100 2550 10100 2500
Connection ~ 9300 2550
Wire Wire Line
	9300 2150 9500 2150
Wire Wire Line
	9500 2150 9500 2800
Connection ~ 9300 2150
Wire Wire Line
	9900 2800 9900 2150
Wire Wire Line
	9900 2150 10100 2150
Connection ~ 10100 2150
Wire Wire Line
	5650 2000 5900 2000
Wire Wire Line
	5900 1600 5900 2000
Connection ~ 5900 2000
Wire Wire Line
	1250 1100 1300 1100
Wire Wire Line
	1300 1100 1300 900 
Wire Wire Line
	1300 1550 1300 1200
Wire Wire Line
	1500 3400 1500 3500
Wire Wire Line
	1500 3500 1350 3500
Wire Wire Line
	5200 1250 5150 1250
Wire Wire Line
	7300 1500 7450 1500
Wire Wire Line
	7300 1800 7350 1800
Wire Wire Line
	7300 1800 7300 1750
Wire Wire Line
	7350 1900 7350 1800
Connection ~ 7350 1800
Text Label 5200 2350 0    60   ~ 0
+Dynamo_Buck
Text GLabel 1250 1100 0    60   Input ~ 0
DYNAMO_AC
Text GLabel 1500 2600 0    60   Input ~ 0
DYNAMO_AC
Wire Wire Line
	5900 1250 6400 1250
Wire Wire Line
	5650 1250 5900 1250
Wire Wire Line
	9300 1800 9550 1800
Wire Wire Line
	9300 2150 9300 2200
Wire Wire Line
	10100 2150 10100 2200
Wire Wire Line
	5900 2000 5900 2050
Wire Wire Line
	7350 1800 7450 1800
Wire Wire Line
	5400 950  5500 950 
Wire Wire Line
	9950 1100 9900 1100
Connection ~ 9900 1100
Wire Wire Line
	9900 1100 9850 1100
Wire Wire Line
	9550 1800 9550 1100
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR034
U 1 1 5A88AB7A
P 9300 2650
F 0 "#PWR034" H 9300 2400 50  0001 C CNN
F 1 "GND" H 9305 2477 50  0000 C CNN
F 2 "" H 9300 2650 50  0001 C CNN
F 3 "" H 9300 2650 50  0001 C CNN
	1    9300 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 1800 10100 1800
Wire Wire Line
	9300 2550 9300 2650
Wire Wire Line
	9900 1100 9900 1800
$Comp
L maxwell-rescue:Q_PMOS_GSD-device Q4
U 1 1 5A85109E
P 7850 1350
F 0 "Q4" V 8193 1350 50  0000 C CNN
F 1 "NTR1P02T1" V 8102 1350 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SOT-23_LargePads" H 8050 1450 50  0001 C CNN
F 3 "" H 7850 1350 50  0001 C CNN
	1    7850 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9550 1100 9400 1100
Connection ~ 9550 1100
Wire Wire Line
	7650 1250 7300 1250
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR035
U 1 1 5A85AF68
P 7850 1550
F 0 "#PWR035" H 7850 1300 50  0001 C CNN
F 1 "GND" H 7855 1377 50  0000 C CNN
F 2 "" H 7850 1550 50  0001 C CNN
F 3 "" H 7850 1550 50  0001 C CNN
	1    7850 1550
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Q_PMOS_GSD-device Q3
U 1 1 5A876381
P 5400 1150
F 0 "Q3" V 5650 1150 50  0000 C CNN
F 1 "NTR1P02T1" V 5741 1150 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SOT-23_LargePads" H 5600 1250 50  0001 C CNN
F 3 "" H 5400 1150 50  0001 C CNN
	1    5400 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 3600 3500 3600
Wire Wire Line
	3500 3600 3500 3700
Wire Wire Line
	3250 3700 3250 3600
Text GLabel 2450 3900 0    60   Input ~ 0
ENABLE_BATT_POWER
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR050
U 1 1 5A2580F1
P 3250 4200
F 0 "#PWR050" H 3250 3950 50  0001 C CNN
F 1 "GND" H 3255 4027 50  0000 C CNN
F 2 "" H 3250 4200 50  0001 C CNN
F 3 "" H 3250 4200 50  0001 C CNN
	1    3250 4200
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR049
U 1 1 5A25809F
P 3500 3700
F 0 "#PWR049" H 3500 3500 50  0001 C CNN
F 1 "GNDPWR" H 3504 3774 50  0000 C CNN
F 2 "" H 3500 3650 50  0001 C CNN
F 3 "" H 3500 3650 50  0001 C CNN
	1    3500 3700
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Q_NMOS_SGD-device Q2
U 1 1 5A87E051
P 3150 3900
F 0 "Q2" H 3356 3946 50  0000 L CNN
F 1 "PSMN5R4-25YLD" H 3356 3855 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:PSMN5R4-25YLD" H 3350 4000 50  0001 C CNN
F 3 "" H 3150 3900 50  0001 C CNN
	1    3150 3900
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:MIC39102-coddingtonbear U10
U 1 1 5A881E0A
P 7900 3350
F 0 "U10" H 7925 3837 60  0000 C CNN
F 1 "MIC39102" H 7925 3731 60  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOIC-8" H 7900 3350 60  0001 C CNN
F 3 "" H 7900 3350 60  0001 C CNN
	1    7900 3350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR037
U 1 1 5A884C49
P 5000 3100
F 0 "#PWR037" H 5000 2950 50  0001 C CNN
F 1 "+BATT" H 5015 3273 50  0000 C CNN
F 2 "" H 5000 3100 50  0001 C CNN
F 3 "" H 5000 3100 50  0001 C CNN
	1    5000 3100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:CP-RESCUE-maxwell C3
U 1 1 5A884C9A
P 6700 3250
F 0 "C3" H 6818 3296 50  0000 L CNN
F 1 "22u" H 6818 3205 50  0000 L CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 6738 3100 50  0001 C CNN
F 3 "" H 6700 3250 50  0001 C CNN
	1    6700 3250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR044
U 1 1 5A884D7B
P 6700 4150
F 0 "#PWR044" H 6700 3900 50  0001 C CNN
F 1 "GND" H 6705 3977 50  0000 C CNN
F 2 "" H 6700 4150 50  0001 C CNN
F 3 "" H 6700 4150 50  0001 C CNN
	1    6700 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3100 7000 3100
Wire Wire Line
	7000 3100 7000 3250
Wire Wire Line
	7000 3250 7250 3250
$Comp
L maxwell-rescue:CP-RESCUE-maxwell C14
U 1 1 5A8876EB
P 6700 4000
F 0 "C14" H 6818 4046 50  0000 L CNN
F 1 "220u" H 6818 3955 50  0000 L CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 6738 3850 50  0001 C CNN
F 3 "" H 6700 4000 50  0001 C CNN
	1    6700 4000
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR047
U 1 1 5A88774F
P 6700 3850
F 0 "#PWR047" H 6700 3700 50  0001 C CNN
F 1 "+3V3" H 6715 4023 50  0000 C CNN
F 2 "" H 6700 3850 50  0001 C CNN
F 3 "" H 6700 3850 50  0001 C CNN
	1    6700 3850
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR048
U 1 1 5A887A87
P 6700 3400
F 0 "#PWR048" H 6700 3150 50  0001 C CNN
F 1 "GND" H 6705 3227 50  0000 C CNN
F 2 "" H 6700 3400 50  0001 C CNN
F 3 "" H 6700 3400 50  0001 C CNN
	1    6700 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3850 7000 3850
Wire Wire Line
	7000 3850 7000 3350
Wire Wire Line
	7000 3350 7200 3350
Connection ~ 6700 3850
Wire Wire Line
	8350 3150 8350 3250
Wire Wire Line
	8350 3250 8350 3350
Connection ~ 8350 3250
Wire Wire Line
	8350 3350 8350 3450
Connection ~ 8350 3350
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR051
U 1 1 5A892619
P 8350 3600
F 0 "#PWR051" H 8350 3350 50  0001 C CNN
F 1 "GND" H 8355 3427 50  0000 C CNN
F 2 "" H 8350 3600 50  0001 C CNN
F 3 "" H 8350 3600 50  0001 C CNN
	1    8350 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 3600 8350 3450
Connection ~ 8350 3450
$Comp
L maxwell-rescue:R-RESCUE-maxwell R12
U 1 1 5A89570C
P 7200 3500
F 0 "R12" V 7407 3500 50  0000 C CNN
F 1 "16-17k" V 7316 3500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 7130 3500 50  0001 C CNN
F 3 "" H 7200 3500 50  0001 C CNN
	1    7200 3500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R13
U 1 1 5A8957A6
P 7200 3800
F 0 "R13" V 7407 3800 50  0000 C CNN
F 1 "10k" V 7316 3800 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 7130 3800 50  0001 C CNN
F 3 "" H 7200 3800 50  0001 C CNN
	1    7200 3800
	1    0    0    -1  
$EndComp
Connection ~ 7200 3350
Wire Wire Line
	7200 3350 7500 3350
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR053
U 1 1 5A895A83
P 7200 3950
F 0 "#PWR053" H 7200 3700 50  0001 C CNN
F 1 "GND" H 7205 3777 50  0000 C CNN
F 2 "" H 7200 3950 50  0001 C CNN
F 3 "" H 7200 3950 50  0001 C CNN
	1    7200 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3650 7500 3650
Wire Wire Line
	7500 3650 7500 3450
Connection ~ 7200 3650
Wire Wire Line
	7500 3150 7250 3150
Wire Wire Line
	7250 3150 7250 3250
Connection ~ 7250 3250
Wire Wire Line
	7250 3250 7500 3250
Wire Wire Line
	9000 1100 8250 1100
Wire Wire Line
	8050 1250 8250 1250
Wire Wire Line
	8250 1100 8250 1250
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR036
U 1 1 5A85AFB9
P 9200 1400
F 0 "#PWR036" H 9200 1150 50  0001 C CNN
F 1 "GND" H 9205 1227 50  0000 C CNN
F 2 "" H 9200 1400 50  0001 C CNN
F 3 "" H 9200 1400 50  0001 C CNN
	1    9200 1400
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Q_PMOS_GSD-device Q5
U 1 1 5A851232
P 9200 1200
F 0 "Q5" V 9543 1200 50  0000 C CNN
F 1 "NTR1P02T1" V 9452 1200 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SOT-23_LargePads" H 9400 1300 50  0001 C CNN
F 3 "" H 9200 1200 50  0001 C CNN
	1    9200 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2100 2800 2100 3100
Wire Wire Line
	3250 4100 3250 4200
Wire Wire Line
	2450 3900 2950 3900
Wire Wire Line
	8250 1250 8250 1350
Wire Wire Line
	8250 1350 8400 1350
Connection ~ 8250 1250
Connection ~ 5200 1250
Wire Wire Line
	1300 900  3350 900 
Wire Wire Line
	1300 1550 3350 1550
Text GLabel 4550 3500 3    60   Input ~ 0
DYNAMO_SOURCE_DISABLE
$Comp
L power:VCC #PWR0103
U 1 1 5B32131C
P 7000 3100
F 0 "#PWR0103" H 7000 2950 50  0001 C CNN
F 1 "VCC" H 7017 3273 50  0000 C CNN
F 2 "" H 7000 3100 50  0001 C CNN
F 3 "" H 7000 3100 50  0001 C CNN
	1    7000 3100
	1    0    0    -1  
$EndComp
Connection ~ 7000 3100
Wire Wire Line
	3650 1250 3950 1250
$Comp
L maxwell-rescue:Conn_01x02-RESCUE-maxwell J18
U 1 1 5B33B354
P 8000 4400
F 0 "J18" H 8080 4392 50  0000 L CNN
F 1 "Supercap" H 8080 4301 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 8000 4400 50  0001 C CNN
F 3 "" H 8000 4400 50  0001 C CNN
	1    8000 4400
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0111
U 1 1 5B33B419
P 8000 4200
F 0 "#PWR0111" H 8000 3950 50  0001 C CNN
F 1 "GND" H 8005 4027 50  0000 C CNN
F 2 "" H 8000 4200 50  0001 C CNN
F 3 "" H 8000 4200 50  0001 C CNN
	1    8000 4200
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0112
U 1 1 5B33B498
P 7900 4200
F 0 "#PWR0112" H 7900 4050 50  0001 C CNN
F 1 "+3V3" H 7915 4373 50  0000 C CNN
F 2 "" H 7900 4200 50  0001 C CNN
F 3 "" H 7900 4200 50  0001 C CNN
	1    7900 4200
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:TPS2113 U3
U 1 1 5BC931DD
P 5500 3250
F 0 "U3" H 5500 3665 50  0000 C CNN
F 1 "TPS2113" H 5500 3574 50  0000 C CNN
F 2 "Package_SO:TSSOP-8_4.4x3mm_P0.65mm" H 5500 3250 50  0001 C CNN
F 3 "" H 5500 3250 50  0001 C CNN
	1    5500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1600 5650 2000
Wire Wire Line
	5200 2500 4650 2500
Wire Wire Line
	4650 2500 4650 3200
Wire Wire Line
	4650 3200 5100 3200
Wire Wire Line
	5200 1250 5200 2500
Wire Wire Line
	5100 3100 5000 3100
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0113
U 1 1 5BCA7B36
P 5500 3800
F 0 "#PWR0113" H 5500 3550 50  0001 C CNN
F 1 "GND" H 5505 3627 50  0000 C CNN
F 2 "" H 5500 3800 50  0001 C CNN
F 3 "" H 5500 3800 50  0001 C CNN
	1    5500 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3100 6700 3100
Connection ~ 6700 3100
Wire Wire Line
	5900 3450 5900 3650
Wire Wire Line
	5900 3650 5500 3650
Wire Wire Line
	5500 3650 5500 3750
Connection ~ 5500 3650
$Comp
L maxwell-rescue:R-RESCUE-maxwell R3
U 1 1 5BCC6214
P 4950 3600
F 0 "R3" V 5157 3600 50  0000 C CNN
F 1 "500" V 5066 3600 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4880 3600 50  0001 C CNN
F 3 "" H 4950 3600 50  0001 C CNN
	1    4950 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	5100 3450 4950 3450
Wire Wire Line
	4950 3750 5500 3750
Connection ~ 5500 3750
Wire Wire Line
	5500 3750 5500 3800
Wire Wire Line
	5100 3350 4550 3350
Wire Wire Line
	4550 3350 4550 3500
Text GLabel 3550 1800 0    60   Input ~ 0
DYNAMO_VOLTAGE
Text GLabel 3950 2500 0    60   Input ~ 0
DYNAMO_BUCK_VOLTAGE
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5BCDF6C1
P 4150 2300
F 0 "R?" H 4220 2346 50  0000 L CNN
F 1 "ANY" H 4220 2255 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4080 2300 50  0001 C CNN
F 3 "" H 4150 2300 50  0001 C CNN
	1    4150 2300
	1    0    0    -1  
$EndComp
Connection ~ 4650 2500
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5BCE1A8A
P 4150 2700
F 0 "R?" H 4220 2746 50  0000 L CNN
F 1 "ANY" H 4220 2655 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4080 2700 50  0001 C CNN
F 3 "" H 4150 2700 50  0001 C CNN
	1    4150 2700
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR?
U 1 1 5BCE5FA3
P 4150 2950
F 0 "#PWR?" H 4150 2700 50  0001 C CNN
F 1 "GND" H 4155 2777 50  0000 C CNN
F 2 "" H 4150 2950 50  0001 C CNN
F 3 "" H 4150 2950 50  0001 C CNN
	1    4150 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2500 4650 2150
Wire Wire Line
	4650 2150 4150 2150
Wire Wire Line
	4150 2450 4150 2500
Wire Wire Line
	3950 2500 4150 2500
Connection ~ 4150 2500
Wire Wire Line
	4150 2500 4150 2550
Wire Wire Line
	4150 2850 4150 2950
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5BCF3736
P 3950 1600
F 0 "R?" H 4020 1646 50  0000 L CNN
F 1 "20k" H 4020 1555 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 3880 1600 50  0001 C CNN
F 3 "" H 3950 1600 50  0001 C CNN
	1    3950 1600
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5BCF4E13
P 3950 2050
F 0 "R?" H 4020 2096 50  0000 L CNN
F 1 "1470" H 4020 2005 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 3880 2050 50  0001 C CNN
F 3 "" H 3950 2050 50  0001 C CNN
	1    3950 2050
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR?
U 1 1 5BCF74EA
P 3950 2200
F 0 "#PWR?" H 3950 1950 50  0001 C CNN
F 1 "GND" H 3955 2027 50  0000 C CNN
F 2 "" H 3950 2200 50  0001 C CNN
F 3 "" H 3950 2200 50  0001 C CNN
	1    3950 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1450 3950 1250
Connection ~ 3950 1250
Wire Wire Line
	3950 1250 4200 1250
Wire Wire Line
	3550 1800 3950 1800
Wire Wire Line
	3950 1800 3950 1750
Wire Wire Line
	3950 1800 3950 1900
Connection ~ 3950 1800
Text Label 3700 1250 0    60   ~ 0
+Dynamo
Text Label 5750 1250 0    60   ~ 0
Batt_Charge
$EndSCHEMATC
