EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 26 0
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
F 2 "coddingtonbear:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 1500 1100 50  0001 C CNN
F 3 "" H 1500 1100 50  0001 C CNN
	1    1500 1100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:TLP185(SE-RESCUE-maxwell U8
U 1 1 5A1FF25C
P 1650 2050
F 0 "U8" H 1650 2375 50  0000 C CNN
F 1 "TLP188" H 1650 2284 50  0000 C CNN
F 2 "coddingtonbear:SO-4_Optocoupler_Milling" H 1650 1750 50  0001 C CIN
F 3 "" H 1650 2050 50  0001 L CNN
	1    1650 2050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:D-RESCUE-maxwell D1
U 1 1 5A1FF263
P 1350 2600
F 0 "D1" V 1396 2521 50  0000 R CNN
F 1 "GS1M-LTP" V 1305 2521 50  0000 R CNN
F 2 "coddingtonbear:DO-214AC" H 1350 2600 50  0001 C CNN
F 3 "" H 1350 2600 50  0001 C CNN
	1    1350 2600
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR032
U 1 1 5A1FF277
P 1950 1950
F 0 "#PWR032" H 1950 1800 50  0001 C CNN
F 1 "+3V3" H 1965 2123 50  0000 C CNN
F 2 "" H 1950 1950 50  0001 C CNN
F 3 "" H 1950 1950 50  0001 C CNN
	1    1950 1950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:D_Bridge_+-AA-RESCUE-maxwell D4
U 1 1 5A1FF27E
P 3350 1250
F 0 "D4" H 3691 1296 50  0000 L CNN
F 1 "MB24S" H 3691 1205 50  0000 L CNN
F 2 "coddingtonbear:SO-4_Milling" H 3350 1250 50  0001 C CNN
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
P 1350 2300
F 0 "R14" H 1420 2346 50  0000 L CNN
F 1 "200" H 1420 2255 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 1280 2300 50  0001 C CNN
F 3 "" H 1350 2300 50  0001 C CNN
	1    1350 2300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:BOOST_BOARD-RESCUE-maxwell U9
U 1 1 5A1FFDEF
P 4700 1300
F 0 "U9" H 4675 1637 60  0000 C CNN
F 1 "Buck Regulator" H 4675 1531 60  0000 C CNN
F 2 "coddingtonbear:BOOST_LM2596_3A" H 4700 1300 60  0001 C CNN
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
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 6850 1300 60  0001 C CNN
F 3 "" H 6850 1300 60  0000 C CNN
	1    6850 1600
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x02-RESCUE-maxwell J9
U 1 1 5A21040E
P 8750 2900
F 0 "J9" H 8830 2892 50  0000 L CNN
F 1 "Battery" H 8830 2801 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 8750 2900 50  0001 C CNN
F 3 "" H 8750 2900 50  0001 C CNN
	1    8750 2900
	0    1    1    0   
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
L maxwell-rescue:R-RESCUE-maxwell R19
U 1 1 5A210718
P 7450 1650
F 0 "R19" H 7520 1696 50  0000 L CNN
F 1 "2k" H 7520 1605 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 7380 1650 50  0001 C CNN
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
F 2 "coddingtonbear:0805_Milling" H 5938 1300 50  0001 C CNN
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
P 9700 5550
F 0 "R20" H 9770 5596 50  0000 L CNN
F 1 "ANY" H 9770 5505 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 9630 5550 50  0001 C CNN
F 3 "" H 9700 5550 50  0001 C CNN
	1    9700 5550
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R21
U 1 1 5A245A89
P 9700 5950
F 0 "R21" H 9770 5996 50  0000 L CNN
F 1 "ANY" H 9770 5905 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 9630 5950 50  0001 C CNN
F 3 "" H 9700 5950 50  0001 C CNN
	1    9700 5950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R22
U 1 1 5A246038
P 10100 5400
F 0 "R22" V 9893 5400 50  0000 C CNN
F 1 "0.02" V 9984 5400 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 10030 5400 50  0001 C CNN
F 3 "" H 10100 5400 50  0001 C CNN
	1    10100 5400
	0    1    1    0   
$EndComp
Text GLabel 9900 5750 2    60   Output ~ 0
BATT_VOLTAGE
$Comp
L maxwell-rescue:CP-RESCUE-maxwell C17
U 1 1 5A24B0B8
P 5650 1450
F 0 "C17" H 5768 1496 50  0000 L CNN
F 1 "0.1" H 5768 1405 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 5688 1300 50  0001 C CNN
F 3 "" H 5650 1450 50  0001 C CNN
	1    5650 1450
	1    0    0    -1  
$EndComp
Text GLabel 1300 1200 0    60   Input ~ 0
DYNAMO_NEUTRAL
Text GLabel 1200 2850 0    60   Input ~ 0
DYNAMO_NEUTRAL
Wire Wire Line
	3350 900  3350 950 
Wire Wire Line
	5900 1300 5900 1250
Connection ~ 5900 1250
Wire Wire Line
	5650 1300 5650 1250
Wire Wire Line
	6400 1750 6300 1750
Wire Wire Line
	6300 1750 6300 2200
Wire Wire Line
	6300 2200 6400 2200
Wire Wire Line
	9700 5750 9900 5750
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
	1350 2750 1350 2850
Wire Wire Line
	1350 2850 1200 2850
Wire Wire Line
	7300 1500 7450 1500
Wire Wire Line
	7300 1800 7350 1800
Wire Wire Line
	7300 1800 7300 1750
Wire Wire Line
	7350 1900 7350 1800
Connection ~ 7350 1800
Text Label 5250 1250 1    60   ~ 0
+Dynamo_Buck
Text GLabel 1250 1100 0    60   Input ~ 0
DYNAMO_AC
Text GLabel 1350 1950 0    60   Input ~ 0
DYNAMO_AC
Wire Wire Line
	5900 1250 6400 1250
Wire Wire Line
	5650 1250 5900 1250
Wire Wire Line
	9700 5400 9950 5400
Wire Wire Line
	5900 2000 5900 2050
Wire Wire Line
	7350 1800 7450 1800
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR034
U 1 1 5A88AB7A
P 9700 6250
F 0 "#PWR034" H 9700 6000 50  0001 C CNN
F 1 "GND" H 9705 6077 50  0000 C CNN
F 2 "" H 9700 6250 50  0001 C CNN
F 3 "" H 9700 6250 50  0001 C CNN
	1    9700 6250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Q_PMOS_GSD-device Q4
U 1 1 5A85109E
P 7850 1350
F 0 "Q4" V 8193 1350 50  0000 C CNN
F 1 "NTR1P02T1" V 8102 1350 50  0000 C CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 8050 1450 50  0001 C CNN
F 3 "" H 7850 1350 50  0001 C CNN
	1    7850 1350
	0    -1   -1   0   
$EndComp
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
Wire Wire Line
	5600 6350 5350 6350
Wire Wire Line
	5600 6250 5600 6350
Text GLabel 6400 6050 2    60   Input ~ 0
ENABLE_BATT_POWER
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR050
U 1 1 5A2580F1
P 5600 5750
F 0 "#PWR050" H 5600 5500 50  0001 C CNN
F 1 "GND" H 5605 5577 50  0000 C CNN
F 2 "" H 5600 5750 50  0001 C CNN
F 3 "" H 5600 5750 50  0001 C CNN
	1    5600 5750
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR049
U 1 1 5A25809F
P 5350 6350
F 0 "#PWR049" H 5350 6150 50  0001 C CNN
F 1 "GNDPWR" H 5354 6424 50  0000 C CNN
F 2 "" H 5350 6300 50  0001 C CNN
F 3 "" H 5350 6300 50  0001 C CNN
	1    5350 6350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Q_NMOS_SGD-device Q2
U 1 1 5A87E051
P 5700 6050
F 0 "Q2" H 5906 6096 50  0000 L CNN
F 1 "PSMN5R4-25YLD" H 5906 6005 50  0000 L CNN
F 2 "coddingtonbear:PSMN5R4-25YLD" H 5900 6150 50  0001 C CNN
F 3 "" H 5700 6050 50  0001 C CNN
	1    5700 6050
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:MIC39102-coddingtonbear U10
U 1 1 5A881E0A
P 7900 3350
F 0 "U10" H 7925 3837 60  0000 C CNN
F 1 "MIC39102" H 7925 3731 60  0000 C CNN
F 2 "coddingtonbear:SOIC-8_3.9x4.9mm_P1.27mm_LargePads" H 7900 3350 60  0001 C CNN
F 3 "" H 7900 3350 60  0001 C CNN
	1    7900 3350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR037
U 1 1 5A884C49
P 4300 2900
F 0 "#PWR037" H 4300 2750 50  0001 C CNN
F 1 "+BATT" H 4315 3073 50  0000 C CNN
F 2 "" H 4300 2900 50  0001 C CNN
F 3 "" H 4300 2900 50  0001 C CNN
	1    4300 2900
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
P 8350 5100
F 0 "#PWR051" H 8350 4850 50  0001 C CNN
F 1 "GND" H 8355 4927 50  0000 C CNN
F 2 "" H 8350 5100 50  0001 C CNN
F 3 "" H 8350 5100 50  0001 C CNN
	1    8350 5100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R12
U 1 1 5A89570C
P 7200 3500
F 0 "R12" V 7407 3500 50  0000 C CNN
F 1 "16-17k" V 7316 3500 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 7130 3500 50  0001 C CNN
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
F 2 "coddingtonbear:0805_Milling" V 7130 3800 50  0001 C CNN
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
F 2 "coddingtonbear:SOT-23_LargePads" H 9400 1300 50  0001 C CNN
F 3 "" H 9200 1200 50  0001 C CNN
	1    9200 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 5850 5600 5750
Wire Wire Line
	6400 6050 5900 6050
Wire Wire Line
	1300 900  3350 900 
Wire Wire Line
	1300 1550 3350 1550
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
L maxwell-rescue:TPS2113-coddingtonbear U3
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
	5900 3100 6400 3100
Connection ~ 6700 3100
Wire Wire Line
	5900 3450 5900 3650
Wire Wire Line
	5900 3650 5500 3650
Wire Wire Line
	5500 3650 5500 3750
Connection ~ 5500 3650
Wire Wire Line
	5100 3450 4950 3450
Wire Wire Line
	4950 3750 5500 3750
Connection ~ 5500 3750
Wire Wire Line
	5500 3750 5500 3800
Text GLabel 3550 1800 0    60   Output ~ 0
DYNAMO_VOLTAGE
$Comp
L maxwell-rescue:R-RESCUE-maxwell R15
U 1 1 5BCF3736
P 3950 1600
F 0 "R15" H 4020 1646 50  0000 L CNN
F 1 "20k" H 4020 1555 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 3880 1600 50  0001 C CNN
F 3 "" H 3950 1600 50  0001 C CNN
	1    3950 1600
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R17
U 1 1 5BCF4E13
P 3950 2050
F 0 "R17" H 4020 2096 50  0000 L CNN
F 1 "1470" H 4020 2005 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 3880 2050 50  0001 C CNN
F 3 "" H 3950 2050 50  0001 C CNN
	1    3950 2050
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0115
U 1 1 5BCF74EA
P 3950 2200
F 0 "#PWR0115" H 3950 1950 50  0001 C CNN
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
Text GLabel 6100 3450 3    60   Output ~ 0
POWER_SOURCE_INDICATOR
Wire Wire Line
	5900 3350 6100 3350
Wire Wire Line
	6100 3350 6100 3450
Text Label 8700 1100 1    60   ~ 0
BATT+
Text Label 7450 1250 1    60   ~ 0
BATT_CHARGE_PRE_POLARITY
Text GLabel 2700 5100 2    60   Input ~ 0
DYNAMO_VOLTAGE
Text GLabel 2700 5000 2    60   Input ~ 0
BATT_VOLTAGE
$Comp
L Interface_Expansion:PCA9536D U4
U 1 1 5BFC3C08
P 2150 6400
F 0 "U4" H 2500 6650 50  0000 C CNN
F 1 "PCA9536D" H 2650 6750 50  0000 C CNN
F 2 "coddingtonbear:SOIC-8_3.9x4.9mm_P1.27mm_LargePads" H 3150 6050 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCA9536.pdf" H 1950 4700 50  0001 C CNN
	1    2150 6400
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:AD7995-coddingtonbear U6
U 1 1 5BFCA13F
P 2200 5000
AR Path="/5BFCA13F" Ref="U6"  Part="1" 
AR Path="/5A1FEBCF/5BFCA13F" Ref="U6"  Part="1" 
F 0 "U6" H 2500 5300 50  0000 R CNN
F 1 "AD7991" H 2700 5400 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23-8_Handsoldering" H 3200 4650 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCA9536.pdf" H 2000 3300 50  0001 C CNN
	1    2200 5000
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0122
U 1 1 5BFCB042
P 2200 4700
F 0 "#PWR0122" H 2200 4550 50  0001 C CNN
F 1 "+3V3" H 2215 4873 50  0000 C CNN
F 2 "" H 2200 4700 50  0001 C CNN
F 3 "" H 2200 4700 50  0001 C CNN
	1    2200 4700
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C16
U 1 1 5BFCB415
P 2050 4700
F 0 "C16" H 1935 4654 50  0000 R CNN
F 1 "0.1u" H 1935 4745 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 2088 4550 50  0001 C CNN
F 3 "" H 2050 4700 50  0001 C CNN
	1    2050 4700
	0    -1   -1   0   
$EndComp
Connection ~ 2200 4700
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0123
U 1 1 5BFD498D
P 10900 2050
F 0 "#PWR0123" H 10900 1800 50  0001 C CNN
F 1 "GND" H 10905 1877 50  0000 C CNN
F 2 "" H 10900 2050 50  0001 C CNN
F 3 "" H 10900 2050 50  0001 C CNN
	1    10900 2050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C15
U 1 1 5BFD9D9F
P 2000 6100
F 0 "C15" H 1885 6054 50  0000 R CNN
F 1 "0.1u" H 1885 6145 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 2038 5950 50  0001 C CNN
F 3 "" H 2000 6100 50  0001 C CNN
	1    2000 6100
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0125
U 1 1 5BFDA2BC
P 2150 6100
F 0 "#PWR0125" H 2150 5950 50  0001 C CNN
F 1 "+3V3" H 2165 6273 50  0000 C CNN
F 2 "" H 2150 6100 50  0001 C CNN
F 3 "" H 2150 6100 50  0001 C CNN
	1    2150 6100
	1    0    0    -1  
$EndComp
Connection ~ 2150 6100
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0126
U 1 1 5BFDA871
P 1850 6100
F 0 "#PWR0126" H 1850 5850 50  0001 C CNN
F 1 "GND" H 1855 5927 50  0000 C CNN
F 2 "" H 1850 6100 50  0001 C CNN
F 3 "" H 1850 6100 50  0001 C CNN
	1    1850 6100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0127
U 1 1 5BFE146B
P 2150 6800
F 0 "#PWR0127" H 2150 6550 50  0001 C CNN
F 1 "GND" H 2155 6627 50  0000 C CNN
F 2 "" H 2150 6800 50  0001 C CNN
F 3 "" H 2150 6800 50  0001 C CNN
	1    2150 6800
	1    0    0    -1  
$EndComp
Wire Notes Line
	4450 5000 4450 7200
Wire Notes Line
	4450 7200 1350 7200
Text GLabel 1250 6600 0    60   BiDi ~ 0
I2C1_SCL
Text GLabel 1250 6500 0    60   BiDi ~ 0
I2C1_SDA
Wire Wire Line
	1250 6500 1400 6500
Wire Wire Line
	1650 6600 1550 6600
Wire Wire Line
	1700 5100 1400 5100
Wire Wire Line
	1400 5100 1400 6500
Connection ~ 1400 6500
Wire Wire Line
	1400 6500 1650 6500
Wire Wire Line
	1550 6600 1550 5200
Wire Wire Line
	1550 5200 1700 5200
Connection ~ 1550 6600
Wire Wire Line
	1550 6600 1250 6600
Text GLabel 2650 6400 2    60   Input ~ 0
POWER_SOURCE_INDICATOR
Text GLabel 2650 6500 2    60   Input ~ 0
~BATT_CHARGING
Wire Notes Line
	4450 5000 9000 5000
$Comp
L power:VCC #PWR0128
U 1 1 5C01AD05
P 6650 5300
F 0 "#PWR0128" H 6650 5150 50  0001 C CNN
F 1 "VCC" H 6667 5473 50  0000 C CNN
F 2 "" H 6650 5300 50  0001 C CNN
F 3 "" H 6650 5300 50  0001 C CNN
	1    6650 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3100 6400 5300
Wire Wire Line
	6400 5300 6650 5300
Connection ~ 6400 3100
Wire Wire Line
	6400 3100 6700 3100
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0130
U 1 1 5C0241A0
P 6900 5300
F 0 "#PWR0130" H 6900 5150 50  0001 C CNN
F 1 "+3V3" H 6915 5473 50  0000 C CNN
F 2 "" H 6900 5300 50  0001 C CNN
F 3 "" H 6900 5300 50  0001 C CNN
	1    6900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5300 7200 5300
Wire Wire Line
	7200 5300 7200 4700
Wire Wire Line
	7200 4700 6500 4700
Wire Wire Line
	6500 4700 6500 3850
Wire Wire Line
	6500 3850 6700 3850
Text Notes 2650 6900 0    60   ~ 0
Addr: 1000001\n
Text Notes 2650 5500 0    60   ~ 0
Addr: 0101000\n
Wire Wire Line
	2400 3900 2400 3700
Wire Wire Line
	2650 3350 2550 3350
Wire Wire Line
	3550 3550 3700 3550
Wire Wire Line
	3700 3400 3700 3450
Wire Wire Line
	3700 3550 3700 3450
Connection ~ 3700 3450
Wire Wire Line
	3700 3450 3550 3450
Connection ~ 3700 3400
Wire Wire Line
	3700 3350 3700 3400
Wire Wire Line
	3550 3350 3700 3350
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR?
U 1 1 5C0A66DD
P 4350 3700
AR Path="/5A1FA1FC/5C0A66DD" Ref="#PWR?"  Part="1" 
AR Path="/5A1FEBCF/5C0A66DD" Ref="#PWR0135"  Part="1" 
F 0 "#PWR0135" H 4350 3550 50  0001 C CNN
F 1 "+3V3" H 4365 3873 50  0000 C CNN
F 2 "" H 4350 3700 50  0001 C CNN
F 3 "" H 4350 3700 50  0001 C CNN
	1    4350 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3700 2400 3700
$Comp
L maxwell-rescue:MCP1501-coddingtonbear U?
U 1 1 5C0A66E5
P 3150 3550
AR Path="/5A1FA1FC/5C0A66E5" Ref="U?"  Part="1" 
AR Path="/5A1FEBCF/5C0A66E5" Ref="U1"  Part="1" 
F 0 "U1" H 3200 3063 60  0000 C CNN
F 1 "MCP1501" H 3200 3169 60  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-6_HandSoldering" H 3150 3550 60  0001 C CNN
F 3 "" H 3150 3550 60  0001 C CNN
	1    3150 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3650 3900 3150 3900
Connection ~ 5650 1250
Text GLabel 2550 3350 1    60   Input ~ 0
ENABLE_VREF
Text GLabel 2650 6600 2    60   Output ~ 0
ENABLE_VREF
Wire Wire Line
	3550 3700 4050 3700
$Comp
L maxwell-rescue:C-RESCUE-maxwell C1
U 1 1 5C0CA396
P 4050 3550
F 0 "C1" H 3935 3504 50  0000 R CNN
F 1 "0.1u" H 3935 3595 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 4088 3400 50  0001 C CNN
F 3 "" H 4050 3550 50  0001 C CNN
	1    4050 3550
	-1   0    0    1   
$EndComp
Connection ~ 4050 3700
Wire Wire Line
	4050 3700 4350 3700
$Comp
L maxwell-rescue:R-RESCUE-maxwell R11
U 1 1 5C0E4604
P 2650 3200
F 0 "R11" V 2857 3200 50  0000 C CNN
F 1 "10k" V 2766 3200 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 2580 3200 50  0001 C CNN
F 3 "" H 2650 3200 50  0001 C CNN
	1    2650 3200
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0133
U 1 1 5C0E4D55
P 2650 3050
F 0 "#PWR0133" H 2650 2900 50  0001 C CNN
F 1 "+3V3" H 2665 3223 50  0000 C CNN
F 2 "" H 2650 3050 50  0001 C CNN
F 3 "" H 2650 3050 50  0001 C CNN
	1    2650 3050
	1    0    0    -1  
$EndComp
Connection ~ 2650 3350
Wire Wire Line
	3650 5200 2700 5200
Wire Wire Line
	3650 3900 3650 5200
Wire Wire Line
	5100 3100 5100 2500
$Comp
L maxwell-rescue:R-RESCUE-maxwell R26
U 1 1 5C04CF20
P 4950 3600
F 0 "R26" V 5157 3600 50  0000 C CNN
F 1 "250" V 5066 3600 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 4880 3600 50  0001 C CNN
F 3 "" H 4950 3600 50  0001 C CNN
	1    4950 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 2700 8050 2500
Connection ~ 8050 1250
$Comp
L maxwell-rescue:R-RESCUE-maxwell R3
U 1 1 5C261E61
P 8350 2350
F 0 "R3" H 8420 2396 50  0000 L CNN
F 1 "330" H 8420 2305 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 8280 2350 50  0001 C CNN
F 3 "" H 8350 2350 50  0001 C CNN
	1    8350 2350
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C20
U 1 1 5C2674A7
P 8600 2500
F 0 "C20" H 8485 2454 50  0000 R CNN
F 1 "0.1u" H 8485 2545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 8638 2350 50  0001 C CNN
F 3 "" H 8600 2500 50  0001 C CNN
	1    8600 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8650 2350 8500 2350
Wire Wire Line
	8200 2350 8050 2350
Connection ~ 8050 2350
Wire Wire Line
	8050 2350 8050 1250
Wire Wire Line
	8450 2500 8050 2500
Connection ~ 8050 2500
Wire Wire Line
	8050 2500 8050 2350
Wire Wire Line
	8750 2500 8750 2350
Connection ~ 9200 1400
Wire Wire Line
	8650 2700 8050 2700
Wire Wire Line
	8750 2700 8750 2500
Connection ~ 8750 2500
Wire Wire Line
	9350 1600 9350 1400
Wire Wire Line
	9350 1400 9200 1400
Wire Wire Line
	8950 1750 9050 1750
Wire Wire Line
	9050 1750 9050 1800
Wire Wire Line
	8950 1950 9000 1950
Wire Wire Line
	9000 1950 9000 2250
Wire Wire Line
	9000 2250 9050 2250
Wire Wire Line
	9350 2450 9350 2500
$Comp
L maxwell-rescue:C-RESCUE-maxwell C19
U 1 1 5C2D13DD
P 4950 2500
F 0 "C19" H 4835 2454 50  0000 R CNN
F 1 "0.1u" H 4835 2545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 4988 2350 50  0001 C CNN
F 3 "" H 4950 2500 50  0001 C CNN
	1    4950 2500
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C2
U 1 1 5C2D1517
P 4450 2900
F 0 "C2" H 4335 2854 50  0000 R CNN
F 1 "0.1u" H 4335 2945 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 4488 2750 50  0001 C CNN
F 3 "" H 4450 2900 50  0001 C CNN
	1    4450 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 3200 4300 2900
Wire Wire Line
	4300 3200 5100 3200
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0111
U 1 1 5C2D7D28
P 4700 2900
F 0 "#PWR0111" H 4700 2650 50  0001 C CNN
F 1 "GND" H 4705 2727 50  0000 C CNN
F 2 "" H 4700 2900 50  0001 C CNN
F 3 "" H 4700 2900 50  0001 C CNN
	1    4700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2500 4700 2500
Wire Wire Line
	4700 2500 4700 2900
Wire Wire Line
	4600 2900 4700 2900
Connection ~ 4700 2900
Text GLabel 2650 6300 2    60   Output ~ 0
DISABLE_BATTERY_SRC
Text GLabel 4850 4350 0    60   Input ~ 0
DISABLE_BATTERY_SRC
$Comp
L power:GNDA #PWR0112
U 1 1 5C2FDB4D
P 2200 5400
F 0 "#PWR0112" H 2200 5150 50  0001 C CNN
F 1 "GNDA" H 2205 5227 50  0000 C CNN
F 2 "" H 2200 5400 50  0001 C CNN
F 3 "" H 2200 5400 50  0001 C CNN
	1    2200 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0114
U 1 1 5C2FE087
P 10600 2050
F 0 "#PWR0114" H 10600 1800 50  0001 C CNN
F 1 "GNDA" H 10605 1877 50  0000 C CNN
F 2 "" H 10600 2050 50  0001 C CNN
F 3 "" H 10600 2050 50  0001 C CNN
	1    10600 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:Net-Tie_2 NT1
U 1 1 5C2FE47D
P 10750 2000
F 0 "NT1" H 10750 2178 50  0000 C CNN
F 1 "Net-Tie_2" H 10750 2087 50  0000 C CNN
F 2 "NetTie:NetTie-2_SMD_Pad0.5mm" H 10750 2000 50  0001 C CNN
F 3 "~" H 10750 2000 50  0001 C CNN
	1    10750 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 2000 10600 2000
Wire Wire Line
	10600 2000 10600 2050
Wire Wire Line
	10850 2000 10900 2000
Wire Wire Line
	10900 2000 10900 2050
Text Label 8900 2500 3    60   ~ 0
BATT-UNPROT
$Comp
L power:GNDA #PWR0124
U 1 1 5C316BAE
P 1900 4700
F 0 "#PWR0124" H 1900 4450 50  0001 C CNN
F 1 "GNDA" H 1905 4527 50  0000 C CNN
F 2 "" H 1900 4700 50  0001 C CNN
F 3 "" H 1900 4700 50  0001 C CNN
	1    1900 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3400 3850 3400
$Comp
L power:GNDA #PWR0134
U 1 1 5C317901
P 3850 3400
F 0 "#PWR0134" H 3850 3150 50  0001 C CNN
F 1 "GNDA" H 3855 3227 50  0000 C CNN
F 2 "" H 3850 3400 50  0001 C CNN
F 3 "" H 3850 3400 50  0001 C CNN
	1    3850 3400
	1    0    0    -1  
$EndComp
Connection ~ 3850 3400
Wire Wire Line
	3850 3400 4050 3400
$Comp
L maxwell-rescue:R-RESCUE-maxwell R25
U 1 1 5C318114
P 3150 4050
F 0 "R25" V 3357 4050 50  0000 C CNN
F 1 "50" V 3266 4050 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 3080 4050 50  0001 C CNN
F 3 "" H 3150 4050 50  0001 C CNN
	1    3150 4050
	-1   0    0    1   
$EndComp
Connection ~ 3150 3900
Wire Wire Line
	3150 3900 2400 3900
$Comp
L maxwell-rescue:CP-RESCUE-maxwell C21
U 1 1 5C318357
P 3150 4350
F 0 "C21" H 3268 4396 50  0000 L CNN
F 1 "2.2u" H 3268 4305 50  0000 L CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 3188 4200 50  0001 C CNN
F 3 "" H 3150 4350 50  0001 C CNN
	1    3150 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0136
U 1 1 5C3183FF
P 3150 4500
F 0 "#PWR0136" H 3150 4250 50  0001 C CNN
F 1 "GNDA" H 3155 4327 50  0000 C CNN
F 2 "" H 3150 4500 50  0001 C CNN
F 3 "" H 3150 4500 50  0001 C CNN
	1    3150 4500
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:DMG9926UDM Q3
U 2 1 5C348448
P 9250 2250
F 0 "Q3" H 9456 2296 50  0000 L CNN
F 1 "DMG9926UDM" H 9456 2205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 9450 2175 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/FD/FDG1024NZ.pdf" H 9250 2250 50  0001 L CNN
	2    9250 2250
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:DMG9926UDM Q3
U 1 1 5C348534
P 9250 1800
F 0 "Q3" H 9456 1754 50  0000 L CNN
F 1 "DMG9926UDM" H 9456 1845 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 9450 1725 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/FD/FDG1024NZ.pdf" H 9250 1800 50  0001 L CNN
	1    9250 1800
	1    0    0    1   
$EndComp
$Comp
L coddingtonbear:AP9101C-SOT-25 U11
U 1 1 5C360A97
P 8700 1850
F 0 "U11" V 8728 2028 60  0000 L CNN
F 1 "AP9101C-SOT-25" V 8622 2028 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 8700 1850 60  0001 C CNN
F 3 "" H 8700 1850 60  0001 C CNN
	1    8700 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8750 2500 8900 2500
Wire Wire Line
	8650 1400 8900 1400
Wire Wire Line
	8900 1400 8900 2500
Connection ~ 8900 2500
Wire Wire Line
	8900 2500 9350 2500
Text Notes 9400 2050 0    20   ~ 0
Connected\nInternally
Wire Notes Line
	9000 5000 9000 6500
Wire Wire Line
	9700 5700 9700 5750
Connection ~ 9700 5750
Wire Wire Line
	9700 5750 9700 5800
Wire Wire Line
	9700 3350 9850 3350
Text GLabel 10350 3750 3    60   BiDi ~ 0
I2C1_SDA
Text GLabel 10250 3750 3    60   BiDi ~ 0
I2C1_SCL
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0129
U 1 1 5C3C03B7
P 10750 3350
F 0 "#PWR0129" H 10750 3100 50  0001 C CNN
F 1 "GND" H 10755 3177 50  0000 C CNN
F 2 "" H 10750 3350 50  0001 C CNN
F 3 "" H 10750 3350 50  0001 C CNN
	1    10750 3350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C22
U 1 1 5C3E4892
P 9700 3500
F 0 "C22" H 9585 3454 50  0000 R CNN
F 1 "0.1u" H 9585 3545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 9738 3350 50  0001 C CNN
F 3 "" H 9700 3500 50  0001 C CNN
	1    9700 3500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0137
U 1 1 5C3E4B39
P 9700 3650
F 0 "#PWR0137" H 9700 3400 50  0001 C CNN
F 1 "GND" H 9705 3477 50  0000 C CNN
F 2 "" H 9700 3650 50  0001 C CNN
F 3 "" H 9700 3650 50  0001 C CNN
	1    9700 3650
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:INA219AID U12
U 1 1 5C3E5D78
P 10250 3350
F 0 "U12" V 10537 3300 60  0000 C CNN
F 1 "INA219AID" V 10431 3300 60  0000 C CNN
F 2 "coddingtonbear:SOIC-8_3.9x4.9mm_P1.27mm_LargePads" H 10450 3550 60  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina219.pdf" H 10450 3650 60  0001 L CNN
F 4 "296-23770-1-ND" H 10450 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "INA219AIDCNR" H 10450 3850 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 10450 3950 60  0001 L CNN "Category"
F 7 "PMIC - Current Regulation/Management" H 10450 4050 60  0001 L CNN "Family"
F 8 "http://www.ti.com/lit/ds/symlink/ina219.pdf" H 10450 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/INA219AIDCNR/296-23770-1-ND/1952550" H 10450 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "IC CURRENT MONITOR 1% SOT23-8" H 10450 4350 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 10450 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10450 4550 60  0001 L CNN "Status"
	1    10250 3350
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R18
U 1 1 5C3ED286
P 9700 4850
F 0 "R18" V 9493 4850 50  0000 C CNN
F 1 "10" V 9584 4850 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 9630 4850 50  0001 C CNN
F 3 "" H 9700 4850 50  0001 C CNN
	1    9700 4850
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R23
U 1 1 5C3FB8D0
P 10500 4850
F 0 "R23" V 10293 4850 50  0000 C CNN
F 1 "10" V 10384 4850 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 10430 4850 50  0001 C CNN
F 3 "" H 10500 4850 50  0001 C CNN
	1    10500 4850
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C23
U 1 1 5C3FBA72
P 10100 5000
F 0 "C23" H 9985 4954 50  0000 R CNN
F 1 "0.1u" H 9985 5045 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 10138 4850 50  0001 C CNN
F 3 "" H 10100 5000 50  0001 C CNN
	1    10100 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	10250 5400 10500 5400
Wire Wire Line
	10250 5000 10500 5000
Wire Wire Line
	10500 5000 10500 5400
Wire Wire Line
	9950 5000 9700 5000
Wire Wire Line
	9700 5000 9700 5400
Connection ~ 9700 5400
Connection ~ 9700 5000
Connection ~ 10500 5000
Wire Wire Line
	10500 4700 10150 4700
Wire Wire Line
	10150 4700 10150 3750
Wire Wire Line
	10050 3750 10050 4700
Wire Wire Line
	10050 4700 9700 4700
Wire Wire Line
	9700 6100 9700 6250
Wire Wire Line
	10500 5400 10750 5400
Wire Wire Line
	10750 5400 10750 5300
Connection ~ 10500 5400
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR0138
U 1 1 5C43319B
P 10750 5300
F 0 "#PWR0138" H 10750 5150 50  0001 C CNN
F 1 "+BATT" H 10765 5473 50  0000 C CNN
F 2 "" H 10750 5300 50  0001 C CNN
F 3 "" H 10750 5300 50  0001 C CNN
	1    10750 5300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0139
U 1 1 5C43AD55
P 9700 3350
F 0 "#PWR0139" H 9700 3200 50  0001 C CNN
F 1 "+3V3" H 9715 3523 50  0000 C CNN
F 2 "" H 9700 3350 50  0001 C CNN
F 3 "" H 9700 3350 50  0001 C CNN
	1    9700 3350
	1    0    0    -1  
$EndComp
Connection ~ 9700 3350
Text Notes 10250 4450 0    60   ~ 0
Address: 1001010
Wire Wire Line
	10550 3750 10450 3750
Wire Wire Line
	10450 3750 10350 3750
Connection ~ 10450 3750
Wire Notes Line
	1350 7200 1350 6350
Wire Notes Line
	1350 6350 500  6350
$Comp
L coddingtonbear:PCF8593 U13
U 1 1 5C457965
P 1200 3700
F 0 "U13" V 1097 3938 60  0000 L CNN
F 1 "PCF8593" V 1203 3938 60  0000 L CNN
F 2 "coddingtonbear:SOIC-8_3.9x4.9mm_P1.27mm_LargePads" H 1200 3500 60  0001 C CNN
F 3 "" H 1200 3500 60  0001 C CNN
	1    1200 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 3300 1350 3050
Wire Wire Line
	1350 3050 1950 3050
Wire Wire Line
	1950 3050 1950 2150
$Comp
L maxwell-rescue:C-RESCUE-maxwell C24
U 1 1 5C45E133
P 1400 4250
F 0 "C24" H 1285 4204 50  0000 R CNN
F 1 "0.1u" H 1285 4295 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 1438 4100 50  0001 C CNN
F 3 "" H 1400 4250 50  0001 C CNN
	1    1400 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 4000 1250 4250
Wire Wire Line
	1350 4000 1550 4000
Wire Wire Line
	1550 4000 1550 4250
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0140
U 1 1 5C46ADF6
P 1550 4000
F 0 "#PWR0140" H 1550 3850 50  0001 C CNN
F 1 "+3V3" H 1565 4173 50  0000 C CNN
F 2 "" H 1550 4000 50  0001 C CNN
F 3 "" H 1550 4000 50  0001 C CNN
	1    1550 4000
	1    0    0    -1  
$EndComp
Connection ~ 1550 4000
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0141
U 1 1 5C46AE65
P 1250 4250
F 0 "#PWR0141" H 1250 4000 50  0001 C CNN
F 1 "GND" H 1255 4077 50  0000 C CNN
F 2 "" H 1250 4250 50  0001 C CNN
F 3 "" H 1250 4250 50  0001 C CNN
	1    1250 4250
	1    0    0    -1  
$EndComp
Connection ~ 1250 4250
Text GLabel 1000 4000 3    60   BiDi ~ 0
I2C1_SDA
Text GLabel 1100 4000 3    60   BiDi ~ 0
I2C1_SCL
Text Notes 700  4700 0    60   ~ 0
Address: 1010001
Wire Wire Line
	8350 3450 8350 5100
Connection ~ 8350 3450
$Comp
L maxwell-rescue:R-RESCUE-maxwell R24
U 1 1 5C35AB6D
P 4950 4500
F 0 "R24" V 5157 4500 50  0000 C CNN
F 1 "10k" V 5066 4500 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 4880 4500 50  0001 C CNN
F 3 "" H 4950 4500 50  0001 C CNN
	1    4950 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 4350 4850 4350
Wire Wire Line
	4950 4350 4950 3950
Wire Wire Line
	4950 3950 4650 3950
Wire Wire Line
	4650 3950 4650 3350
Wire Wire Line
	4650 3350 5100 3350
Connection ~ 4950 4350
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0142
U 1 1 5C368421
P 4950 4650
F 0 "#PWR0142" H 4950 4400 50  0001 C CNN
F 1 "GND" H 4955 4477 50  0000 C CNN
F 2 "" H 4950 4650 50  0001 C CNN
F 3 "" H 4950 4650 50  0001 C CNN
	1    4950 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1100 10150 1100
Wire Wire Line
	10150 1100 10150 2850
Wire Wire Line
	10150 2850 9200 2850
Wire Wire Line
	9200 2850 9200 5400
Wire Wire Line
	9200 5400 9700 5400
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR0143
U 1 1 5C37AAA7
P 1100 3300
F 0 "#PWR0143" H 1100 3150 50  0001 C CNN
F 1 "+3V3" H 1115 3473 50  0000 C CNN
F 2 "" H 1100 3300 50  0001 C CNN
F 3 "" H 1100 3300 50  0001 C CNN
	1    1100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1250 5400 1250
Wire Wire Line
	4300 1950 5400 1950
Wire Wire Line
	5400 1950 5400 1250
Connection ~ 5400 1250
Wire Wire Line
	5400 1250 5650 1250
Connection ~ 5100 2500
$Comp
L maxwell-rescue:R-RESCUE-maxwell R28
U 1 1 5C56CC7D
P 4100 2650
F 0 "R28" H 4170 2696 50  0000 L CNN
F 1 "ANY" H 4170 2605 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 4030 2650 50  0001 C CNN
F 3 "" H 4100 2650 50  0001 C CNN
	1    4100 2650
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R27
U 1 1 5C56CDED
P 3650 2650
F 0 "R27" H 3720 2696 50  0000 L CNN
F 1 "ANY" H 3720 2605 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 3580 2650 50  0001 C CNN
F 3 "" H 3650 2650 50  0001 C CNN
	1    3650 2650
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0144
U 1 1 5C56CE75
P 3400 2650
F 0 "#PWR0144" H 3400 2400 50  0001 C CNN
F 1 "GND" H 3405 2477 50  0000 C CNN
F 2 "" H 3400 2650 50  0001 C CNN
F 3 "" H 3400 2650 50  0001 C CNN
	1    3400 2650
	1    0    0    -1  
$EndComp
Text GLabel 3850 2950 0    60   Output ~ 0
DYNAMO_REG_VOLTAGE
Wire Wire Line
	3400 2650 3500 2650
Wire Wire Line
	3800 2650 3900 2650
Wire Wire Line
	4250 2650 4300 2650
Wire Wire Line
	4300 2650 4300 1950
Wire Wire Line
	3850 2950 3900 2950
Wire Wire Line
	3900 2950 3900 2650
Connection ~ 3900 2650
Wire Wire Line
	3900 2650 3950 2650
Text GLabel 2700 4900 2    60   Input ~ 0
DYNAMO_REG_VOLTAGE
$Comp
L maxwell-rescue:R-RESCUE-maxwell R29
U 1 1 5C58DE09
P 1950 3200
F 0 "R29" V 2157 3200 50  0000 C CNN
F 1 "10k" V 2066 3200 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 1880 3200 50  0001 C CNN
F 3 "" H 1950 3200 50  0001 C CNN
	1    1950 3200
	-1   0    0    1   
$EndComp
Connection ~ 1950 3050
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0145
U 1 1 5C58DEA9
P 1950 3350
F 0 "#PWR0145" H 1950 3100 50  0001 C CNN
F 1 "GND" H 1955 3177 50  0000 C CNN
F 2 "" H 1950 3350 50  0001 C CNN
F 3 "" H 1950 3350 50  0001 C CNN
	1    1950 3350
	1    0    0    -1  
$EndComp
Connection ~ 4300 2900
Wire Wire Line
	5100 2500 5400 2500
Wire Wire Line
	5400 2500 5400 1950
Connection ~ 5400 1950
$EndSCHEMATC
