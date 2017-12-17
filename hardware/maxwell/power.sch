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
F 2 "ChristianLerche/LercheTech_KiCAD/LercheTech.pretty:Lerche_2P_2.54mm_Terminal" H 1500 1100 50  0001 C CNN
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
F 2 "Tinkerforge/kicad-libraries:SO-4" H 1800 2400 50  0001 C CIN
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
L maxwell-rescue:R-RESCUE-maxwell R15
U 1 1 5A1FF270
P 2100 2950
F 0 "R15" H 2170 2996 50  0000 L CNN
F 1 "330" H 2170 2905 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2030 2950 50  0001 C CNN
F 3 "" H 2100 2950 50  0001 C CNN
	1    2100 2950
	1    0    0    -1  
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
F 1 "D_Bridge_+-AA" H 3691 1205 50  0000 L CNN
F 2 "ep092/library_toni.pretty:SO-4" H 3350 1250 50  0001 C CNN
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
F 1 "330" H 1570 2905 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1430 2950 50  0001 C CNN
F 3 "" H 1500 2950 50  0001 C CNN
	1    1500 2950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:D_Zener-RESCUE-maxwell D2
U 1 1 5A1FF2A4
P 2400 1050
F 0 "D2" V 2354 1129 50  0000 L CNN
F 1 "18" V 2445 1129 50  0000 L CNN
F 2 "adamgreig/agg-kicad/agg.pretty:DO-214AA-SMB" H 2400 1050 50  0001 C CNN
F 3 "" H 2400 1050 50  0001 C CNN
	1    2400 1050
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:D_Zener-RESCUE-maxwell D3
U 1 1 5A1FF2AB
P 2400 1400
F 0 "D3" V 2446 1321 50  0000 R CNN
F 1 "18" V 2355 1321 50  0000 R CNN
F 2 "adamgreig/agg-kicad/agg.pretty:DO-214AA-SMB" H 2400 1400 50  0001 C CNN
F 3 "" H 2400 1400 50  0001 C CNN
	1    2400 1400
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR035
U 1 1 5A1FFDA9
P 8200 3100
F 0 "#PWR035" H 8200 2950 50  0001 C CNN
F 1 "+3V3" H 8215 3273 50  0000 C CNN
F 2 "" H 8200 3100 50  0001 C CNN
F 3 "" H 8200 3100 50  0001 C CNN
	1    8200 3100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR036
U 1 1 5A1FFDAF
P 7100 3500
F 0 "#PWR036" H 7100 3250 50  0001 C CNN
F 1 "GND" H 7105 3327 50  0000 C CNN
F 2 "" H 7100 3500 50  0001 C CNN
F 3 "" H 7100 3500 50  0001 C CNN
	1    7100 3500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:USB_OTG-RESCUE-maxwell J8
U 1 1 5A1FFDB5
P 3400 2550
F 0 "J8" H 3455 3017 50  0000 C CNN
F 1 "USB Input" H 3400 2900 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:UJ2-MIBH-4-SMT" H 3550 2500 50  0001 C CNN
F 3 "" H 3550 2500 50  0001 C CNN
	1    3400 2550
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR037
U 1 1 5A1FFDBC
P 3400 2950
F 0 "#PWR037" H 3400 2700 50  0001 C CNN
F 1 "GND" H 3405 2777 50  0000 C CNN
F 2 "" H 3400 2950 50  0001 C CNN
F 3 "" H 3400 2950 50  0001 C CNN
	1    3400 2950
	1    0    0    -1  
$EndComp
Text GLabel 3700 2650 2    60   BiDi ~ 0
USB-
Text GLabel 3700 2550 2    60   BiDi ~ 0
USB+
$Comp
L maxwell-rescue:C-RESCUE-maxwell C20
U 1 1 5A1FFDC5
P 7850 3250
F 0 "C20" H 7735 3204 50  0000 R CNN
F 1 "100n" H 7735 3295 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 7888 3100 50  0001 C CNN
F 3 "" H 7850 3250 50  0001 C CNN
	1    7850 3250
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C16
U 1 1 5A1FFDCC
P 5450 3250
F 0 "C16" H 5335 3204 50  0000 R CNN
F 1 "100nF" H 5335 3295 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5488 3100 50  0001 C CNN
F 3 "" H 5450 3250 50  0001 C CNN
	1    5450 3250
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:CP-RESCUE-maxwell C19
U 1 1 5A1FFDD3
P 7500 3250
F 0 "C19" H 7618 3296 50  0000 L CNN
F 1 "220u" H 7618 3205 50  0000 L CNN
F 2 "xesscorp/xess.pretty:xess-ECAP-SMT-6.3MM" H 7538 3100 50  0001 C CNN
F 3 "" H 7500 3250 50  0001 C CNN
	1    7500 3250
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
L maxwell-rescue:CP-RESCUE-maxwell C15
U 1 1 5A20260D
P 3650 1600
F 0 "C15" H 3768 1646 50  0000 L CNN
F 1 "100u" H 3768 1555 50  0000 L CNN
F 2 "xesscorp/xess.pretty:xess-ECAP-SMT-6.3MM" H 3688 1450 50  0001 C CNN
F 3 "" H 3650 1600 50  0001 C CNN
	1    3650 1600
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR040
U 1 1 5A202661
P 3650 1750
F 0 "#PWR040" H 3650 1500 50  0001 C CNN
F 1 "GND" H 3655 1577 50  0000 C CNN
F 2 "" H 3650 1750 50  0001 C CNN
F 3 "" H 3650 1750 50  0001 C CNN
	1    3650 1750
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:D-RESCUE-maxwell D5
U 1 1 5A202C41
P 4100 2350
F 0 "D5" H 4100 2134 50  0000 C CNN
F 1 "D" H 4100 2225 50  0000 C CNN
F 2 "mcous/kicad-lib/footprints/diode.pretty:DO-214AC" H 4100 2350 50  0001 C CNN
F 3 "" H 4100 2350 50  0001 C CNN
	1    4100 2350
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:LT1529-RESCUE-maxwell U10
U 1 1 5A20F6E0
P 7050 3200
F 0 "U10" H 7050 3565 50  0000 C CNN
F 1 "LT1529" H 7050 3474 50  0000 C CNN
F 2 "KiCad/TO_SOT_Packages_THT.pretty:TO-220-5_Pentawatt_Multiwatt-5_Vertical_StaggeredType2" H 7050 3550 50  0001 C CIN
F 3 "" H 7050 3300 50  0001 C CNN
	1    7050 3200
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
F 2 "ChristianLerche/LercheTech_KiCAD/LercheTech.pretty:Lerche_2P_2.54mm_Terminal" H 8600 1250 50  0001 C CNN
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
P 8400 1350
F 0 "#PWR042" H 8400 1100 50  0001 C CNN
F 1 "GND" H 8405 1177 50  0000 C CNN
F 2 "" H 8400 1350 50  0001 C CNN
F 3 "" H 8400 1350 50  0001 C CNN
	1    8400 1350
	1    0    0    -1  
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
Tune to 4V
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR044
U 1 1 5A2124F4
P 5450 3000
F 0 "#PWR044" H 5450 2850 50  0001 C CNN
F 1 "+BATT" H 5465 3173 50  0000 C CNN
F 2 "" H 5450 3000 50  0001 C CNN
F 3 "" H 5450 3000 50  0001 C CNN
	1    5450 3000
	1    0    0    -1  
$EndComp
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
L maxwell-rescue:R-RESCUE-maxwell R18
U 1 1 5A2253E0
P 6350 3200
F 0 "R18" V 6143 3200 50  0000 C CNN
F 1 "100k" V 6234 3200 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 6280 3200 50  0001 C CNN
F 3 "" H 6350 3200 50  0001 C CNN
	1    6350 3200
	0    1    1    0   
$EndComp
Text GLabel 5950 4150 0    60   Input ~ 0
POWER_ON
Text Notes 5350 4050 0    60   ~ 0
µC should hold\nPOWER_ON high\nupon startup
$Comp
L maxwell-rescue:D-RESCUE-maxwell D6
U 1 1 5A226F08
P 6200 4150
F 0 "D6" H 6200 3934 50  0000 C CNN
F 1 "D" H 6200 4025 50  0000 C CNN
F 2 "mcous/kicad-lib/footprints/diode.pretty:DO-214AC" H 6200 4150 50  0001 C CNN
F 3 "" H 6200 4150 50  0001 C CNN
	1    6200 4150
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R20
U 1 1 5A245A23
P 9300 1250
F 0 "R20" H 9370 1296 50  0000 L CNN
F 1 "4.7k" H 9370 1205 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9230 1250 50  0001 C CNN
F 3 "" H 9300 1250 50  0001 C CNN
	1    9300 1250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R21
U 1 1 5A245A89
P 9300 1650
F 0 "R21" H 9370 1696 50  0000 L CNN
F 1 "10k" H 9370 1605 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9230 1650 50  0001 C CNN
F 3 "" H 9300 1650 50  0001 C CNN
	1    9300 1650
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R23
U 1 1 5A245B4A
P 10100 1250
F 0 "R23" H 10170 1296 50  0000 L CNN
F 1 "4.7k" H 10170 1205 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10030 1250 50  0001 C CNN
F 3 "" H 10100 1250 50  0001 C CNN
	1    10100 1250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R24
U 1 1 5A245B93
P 10100 1650
F 0 "R24" H 10170 1696 50  0000 L CNN
F 1 "10k" H 10170 1605 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10030 1650 50  0001 C CNN
F 3 "" H 10100 1650 50  0001 C CNN
	1    10100 1650
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
Text GLabel 9900 2100 3    60   Output ~ 0
CURRENT_SENSE
Text GLabel 9500 2100 3    60   Output ~ 0
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
$Comp
L maxwell-rescue:Q_NMOS_GDS-RESCUE-maxwell Q2
U 1 1 5A257F55
P 3150 3900
F 0 "Q2" H 3355 3946 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 3355 3855 50  0000 L CNN
F 2 "fruchti/fruchtilib/mod/to.pretty:TO220" H 3350 4000 50  0001 C CNN
F 3 "" H 3150 3900 50  0001 C CNN
	1    3150 3900
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
L maxwell-rescue:R-RESCUE-maxwell R25
U 1 1 5A25869F
P 2850 4150
F 0 "R25" V 3057 4150 50  0000 C CNN
F 1 "100k" V 2966 4150 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2780 4150 50  0001 C CNN
F 3 "" H 2850 4150 50  0001 C CNN
	1    2850 4150
	0    -1   -1   0   
$EndComp
Text GLabel 2450 3900 0    60   Input ~ 0
ENABLE_BATT_POWER
Text GLabel 1300 1200 0    60   Input ~ 0
DYNAMO_NEUTRAL
Text GLabel 1350 3500 0    60   Input ~ 0
DYNAMO_NEUTRAL
$Comp
L maxwell-rescue:R-RESCUE-maxwell R30
U 1 1 5A26A72F
P 6650 2500
F 0 "R30" V 6443 2500 50  0000 C CNN
F 1 "1.5k" V 6534 2500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 6580 2500 50  0001 C CNN
F 3 "" H 6650 2500 50  0001 C CNN
	1    6650 2500
	-1   0    0    1   
$EndComp
Text GLabel 5500 950  2    60   Input ~ 0
~BATT_CHARGE_ENABLE
$Comp
L maxwell-rescue:R-RESCUE-maxwell R34
U 1 1 5A27817C
P 4150 850
F 0 "R34" H 4220 896 50  0000 L CNN
F 1 "10k" H 4220 805 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4080 850 50  0001 C CNN
F 3 "" H 4150 850 50  0001 C CNN
	1    4150 850 
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R35
U 1 1 5A2781E1
P 4500 850
F 0 "R35" H 4570 896 50  0000 L CNN
F 1 "2k" H 4570 805 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4430 850 50  0001 C CNN
F 3 "" H 4500 850 50  0001 C CNN
	1    4500 850 
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR046
U 1 1 5A278243
P 4650 850
F 0 "#PWR046" H 4650 600 50  0001 C CNN
F 1 "GND" H 4655 677 50  0000 C CNN
F 2 "" H 4650 850 50  0001 C CNN
F 3 "" H 4650 850 50  0001 C CNN
	1    4650 850 
	0    -1   -1   0   
$EndComp
Text GLabel 4400 650  2    60   Output ~ 0
DYNAMO_VOLTAGE
$Comp
L maxwell-rescue:R-RESCUE-maxwell R36
U 1 1 5A27BDA2
P 5350 750
F 0 "R36" H 5420 796 50  0000 L CNN
F 1 "10k" H 5420 705 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5280 750 50  0001 C CNN
F 3 "" H 5350 750 50  0001 C CNN
	1    5350 750 
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR043
U 1 1 5A210C7A
P 10250 1100
F 0 "#PWR043" H 10250 950 50  0001 C CNN
F 1 "+BATT" H 10265 1273 50  0000 C CNN
F 2 "" H 10250 1100 50  0001 C CNN
F 3 "" H 10250 1100 50  0001 C CNN
	1    10250 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1250 2400 1200
Wire Wire Line
	3300 2950 3400 2950
Connection ~ 7500 3100
Connection ~ 7850 3100
Connection ~ 7500 3400
Wire Wire Line
	1300 900  3350 900 
Wire Wire Line
	1300 1550 3350 1550
Wire Wire Line
	3350 900  3350 950 
Connection ~ 2400 900 
Connection ~ 2400 1550
Wire Wire Line
	7850 3400 7500 3400
Wire Wire Line
	7500 3400 7500 3500
Connection ~ 7100 3500
Wire Wire Line
	3650 1250 3650 1450
Wire Wire Line
	3700 2350 3950 2350
Wire Wire Line
	3650 1250 4200 1250
Wire Wire Line
	8250 1100 9550 1100
Wire Wire Line
	7400 3200 7500 3200
Wire Wire Line
	7500 3200 7500 3100
Wire Wire Line
	5600 1250 6400 1250
Wire Wire Line
	7500 3500 5450 3500
Wire Wire Line
	5900 1300 5900 1250
Connection ~ 5900 1250
Wire Wire Line
	5650 1300 5650 1250
Connection ~ 5650 1250
Wire Wire Line
	5450 3100 6700 3100
Wire Wire Line
	5450 3500 5450 3400
Wire Wire Line
	6500 3200 6700 3200
Connection ~ 5950 3500
Connection ~ 6650 3200
Wire Wire Line
	5950 3500 5950 3200
Wire Wire Line
	5950 3200 6200 3200
Wire Wire Line
	6650 2650 6650 4150
Wire Wire Line
	6650 4150 6350 4150
Wire Wire Line
	6050 4150 5950 4150
Wire Wire Line
	6400 1750 6300 1750
Wire Wire Line
	6300 1750 6300 2200
Wire Wire Line
	6300 2200 6400 2200
Connection ~ 9300 1100
Wire Wire Line
	9850 1100 10250 1100
Wire Wire Line
	9300 1400 9300 1500
Wire Wire Line
	10100 1400 10100 1500
Connection ~ 10100 1100
Wire Wire Line
	9300 1800 9300 1950
Wire Wire Line
	9300 1850 10100 1850
Wire Wire Line
	10100 1850 10100 1800
Connection ~ 9300 1850
Wire Wire Line
	9300 1450 9500 1450
Wire Wire Line
	9500 1450 9500 2100
Connection ~ 9300 1450
Wire Wire Line
	9900 2100 9900 1450
Wire Wire Line
	9900 1450 10100 1450
Connection ~ 10100 1450
Wire Wire Line
	7300 1250 8400 1250
Wire Wire Line
	5650 1600 5650 2000
Wire Wire Line
	5650 2000 5900 2000
Wire Wire Line
	5900 1600 5900 2050
Connection ~ 5900 2000
Wire Wire Line
	1250 1100 1300 1100
Wire Wire Line
	1300 1100 1300 900 
Wire Wire Line
	1300 1550 1300 1200
Wire Wire Line
	3250 3700 3250 3600
Wire Wire Line
	3250 3600 3500 3600
Wire Wire Line
	3500 3600 3500 3700
Wire Wire Line
	3250 4100 3250 4200
Wire Wire Line
	2450 3900 2950 3900
Connection ~ 2700 3900
Wire Wire Line
	3000 4150 3250 4150
Connection ~ 3250 4150
Wire Wire Line
	2700 4150 2700 3900
Wire Wire Line
	1500 3400 1500 3500
Wire Wire Line
	1500 3500 1350 3500
Wire Wire Line
	4000 850  3800 850 
Wire Wire Line
	3800 850  3800 1250
Connection ~ 3800 1250
Wire Wire Line
	4300 850  4350 850 
Wire Wire Line
	4300 850  4300 650 
Wire Wire Line
	4300 650  4400 650 
Wire Wire Line
	5200 1250 5150 1250
Wire Wire Line
	5350 900  5350 950 
Wire Wire Line
	5350 600  5200 600 
Wire Wire Line
	5200 600  5200 1250
Wire Wire Line
	8250 1100 8250 1250
Connection ~ 8250 1250
Wire Wire Line
	7300 1500 7450 1500
Wire Wire Line
	7300 1800 7450 1800
Wire Wire Line
	7300 1800 7300 1750
Wire Wire Line
	7350 1900 7350 1800
Connection ~ 7350 1800
Wire Wire Line
	4250 2350 6650 2350
Wire Wire Line
	5600 1250 5600 2350
Connection ~ 5600 2350
Wire Wire Line
	5350 950  5500 950 
Connection ~ 5400 950 
$Comp
L maxwell-rescue:Q_PMOS_GDS-RESCUE-maxwell Q3
U 1 1 5A2B17F5
P 5400 1150
F 0 "Q3" V 5650 1150 50  0000 C CNN
F 1 "Q_PMOS_GDS" V 5741 1150 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:NDS8434" H 5600 1250 50  0001 C CNN
F 3 "" H 5400 1150 50  0001 C CNN
	1    5400 1150
	0    1    1    0   
$EndComp
Text Label 5950 1250 0    60   ~ 0
+Dynamo
Connection ~ 7050 3500
Wire Wire Line
	7400 3100 8200 3100
Wire Wire Line
	5450 3000 5450 3100
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR020
U 1 1 5A2C7A67
P 9300 1950
F 0 "#PWR020" H 9300 1750 50  0001 C CNN
F 1 "GNDPWR" H 9304 2024 50  0000 C CNN
F 2 "" H 9300 1900 50  0001 C CNN
F 3 "" H 9300 1900 50  0001 C CNN
	1    9300 1950
	1    0    0    -1  
$EndComp
Text GLabel 1250 1100 0    60   Input ~ 0
DYNAMO_AC
Text GLabel 1500 2600 0    60   Input ~ 0
DYNAMO_AC
$EndSCHEMATC
