EESchema Schematic File Version 4
LIBS:maxwell-remote-cache
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
L interface:SN65HVD235 U5
U 1 1 5A3AA892
P 6900 1600
F 0 "U5" H 6900 2078 50  0000 C CNN
F 1 "SN65HVD235" H 6900 1987 50  0000 C CNN
F 2 "OLIMEX/KiCAD/KiCAD_Footprints/OLIMEX_IC-FP.pretty:SOIC-8_208mil" H 6900 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn65hvd234.pdf" H 6800 2000 50  0001 C CNN
	1    6900 1600
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:OLED-SSD1306 U8
U 1 1 5A3AAF00
P 9900 1100
F 0 "U8" V 9922 772 60  0000 R CNN
F 1 "OLED-SSD1306" V 9816 772 60  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:128x64_OLED_LCD" H 9750 1100 60  0001 C CNN
F 3 "" H 9750 1100 60  0001 C CNN
	1    9900 1100
	0    -1   -1   0   
$EndComp
$Comp
L coddingtonbear:MIC5209-ADJ U3
U 1 1 5A3AD30C
P 5200 1500
F 0 "U3" H 5200 1987 60  0000 C CNN
F 1 "MIC5209-ADJ" H 5200 1881 60  0000 C CNN
F 2 "OLIMEX/KiCAD/KiCAD_Footprints/OLIMEX_IC-FP.pretty:SOIC-8_208mil" H 5200 1500 60  0001 C CNN
F 3 "" H 5200 1500 60  0001 C CNN
	1    5200 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5A3AD523
P 5750 1700
F 0 "#PWR01" H 5750 1450 50  0001 C CNN
F 1 "GND" H 5755 1527 50  0000 C CNN
F 2 "" H 5750 1700 50  0001 C CNN
F 3 "" H 5750 1700 50  0001 C CNN
	1    5750 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1600 5750 1600
Wire Wire Line
	5750 1600 5750 1700
Wire Wire Line
	5650 1500 5750 1500
Wire Wire Line
	5750 1500 5750 1600
Connection ~ 5750 1600
Wire Wire Line
	5650 1400 5750 1400
Wire Wire Line
	5750 1400 5750 1500
Connection ~ 5750 1500
Wire Wire Line
	5650 1300 5750 1300
Wire Wire Line
	5750 1300 5750 1400
Connection ~ 5750 1400
$Comp
L Connector:Conn_01x05 J1
U 1 1 5A3AD6C4
P 1050 1100
F 0 "J1" H 970 675 50  0000 C CNN
F 1 "INPUT" H 970 766 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_EH_B05B-EH-A_05x2.50mm_Straight_LargePads" H 1050 1100 50  0001 C CNN
F 3 "~" H 1050 1100 50  0001 C CNN
	1    1050 1100
	-1   0    0    1   
$EndComp
Text GLabel 1250 900  2    60   BiDi ~ 0
WAKE
$Comp
L power:GND #PWR02
U 1 1 5A3AD849
P 1350 1300
F 0 "#PWR02" H 1350 1050 50  0001 C CNN
F 1 "GND" H 1355 1127 50  0000 C CNN
F 2 "" H 1350 1300 50  0001 C CNN
F 3 "" H 1350 1300 50  0001 C CNN
	1    1350 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1300 1350 1300
Text GLabel 1250 1200 2    60   BiDi ~ 0
CAN-
Text GLabel 1250 1100 2    60   BiDi ~ 0
CAN+
$Comp
L power:+3V3 #PWR03
U 1 1 5A3ADD2A
P 4250 1500
F 0 "#PWR03" H 4250 1350 50  0001 C CNN
F 1 "+3V3" V 4265 1628 50  0000 L CNN
F 2 "" H 4250 1500 50  0001 C CNN
F 3 "" H 4250 1500 50  0001 C CNN
	1    4250 1500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5A3ADFD3
P 9950 1750
F 0 "#PWR04" H 9950 1500 50  0001 C CNN
F 1 "GND" H 9955 1577 50  0000 C CNN
F 2 "" H 9950 1750 50  0001 C CNN
F 3 "" H 9950 1750 50  0001 C CNN
	1    9950 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR05
U 1 1 5A3AE098
P 9850 2600
F 0 "#PWR05" H 9850 2450 50  0001 C CNN
F 1 "+3V3" H 9865 2773 50  0000 C CNN
F 2 "" H 9850 2600 50  0001 C CNN
F 3 "" H 9850 2600 50  0001 C CNN
	1    9850 2600
	-1   0    0    1   
$EndComp
$Comp
L device:R R2
U 1 1 5A3AE490
P 4550 1300
F 0 "R2" V 4343 1300 50  0000 C CNN
F 1 "10k" V 4434 1300 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4480 1300 50  0001 C CNN
F 3 "" H 4550 1300 50  0001 C CNN
	1    4550 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 1300 4750 1300
$Comp
L device:CP C5
U 1 1 5A3AEBCE
P 3850 1700
F 0 "C5" H 3968 1746 50  0000 L CNN
F 1 "1u" H 3968 1655 50  0000 L CNN
F 2 "usagi1975/kicad_mod.pretty:Capacitor_Electrolytic_D5.0xP2.0" H 3888 1550 50  0001 C CNN
F 3 "" H 3850 1700 50  0001 C CNN
	1    3850 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5A3AEC3C
P 4150 2150
F 0 "#PWR06" H 4150 1900 50  0001 C CNN
F 1 "GND" H 4155 1977 50  0000 C CNN
F 2 "" H 4150 2150 50  0001 C CNN
F 3 "" H 4150 2150 50  0001 C CNN
	1    4150 2150
	1    0    0    -1  
$EndComp
$Comp
L device:CP C6
U 1 1 5A3AF07E
P 4300 1750
F 0 "C6" H 4418 1796 50  0000 L CNN
F 1 "2.2u" H 4418 1705 50  0000 L CNN
F 2 "usagi1975/kicad_mod.pretty:Capacitor_Electrolytic_D5.0xP2.0" H 4338 1600 50  0001 C CNN
F 3 "" H 4300 1750 50  0001 C CNN
	1    4300 1750
	1    0    0    -1  
$EndComp
$Comp
L device:R R3
U 1 1 5A3AF96F
P 4600 1750
F 0 "R3" H 4530 1704 50  0000 R CNN
F 1 "60k" H 4530 1795 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4530 1750 50  0001 C CNN
F 3 "" H 4600 1750 50  0001 C CNN
	1    4600 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3850 1300 4400 1300
Wire Wire Line
	4250 1500 4300 1500
Wire Wire Line
	4300 1600 4300 1500
Connection ~ 4300 1500
Wire Wire Line
	4300 1500 4600 1500
Wire Wire Line
	3850 1850 3850 2150
Wire Wire Line
	3850 2150 4150 2150
Wire Wire Line
	4300 1900 4300 2150
Wire Wire Line
	4300 2150 4150 2150
Connection ~ 4150 2150
$Comp
L device:R R4
U 1 1 5A3B2A1B
P 4600 2100
F 0 "R4" H 4530 2054 50  0000 R CNN
F 1 "100k" H 4530 2145 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4530 2100 50  0001 C CNN
F 3 "" H 4600 2100 50  0001 C CNN
	1    4600 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 1600 4600 1500
Connection ~ 4600 1500
Wire Wire Line
	4600 1500 4750 1500
Wire Wire Line
	4600 1900 4600 1950
Wire Wire Line
	4600 2250 4600 2300
Wire Wire Line
	4600 2300 4300 2300
Wire Wire Line
	4300 2300 4300 2150
Connection ~ 4300 2150
Wire Wire Line
	4600 1950 4750 1950
Wire Wire Line
	4750 1950 4750 1600
Connection ~ 4600 1950
Text GLabel 10050 1450 3    60   BiDi ~ 0
SCL
Text GLabel 10150 1450 3    60   BiDi ~ 0
SDA
Wire Wire Line
	10050 1350 10050 1450
Wire Wire Line
	10150 1450 10150 1350
Wire Wire Line
	1250 1000 3400 1000
$Comp
L device:Q_PMOS_GSD Q2
U 1 1 5A3CC7A0
P 3600 1500
F 0 "Q2" V 3943 1500 50  0000 C CNN
F 1 "NDS332P" V 3852 1500 50  0000 C CNN
F 2 "cvra/kicad-lib/footprints/_std.pretty:SSOT-3" H 3800 1600 50  0001 C CNN
F 3 "" H 3600 1500 50  0001 C CNN
	1    3600 1500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 1000 3400 1400
Wire Wire Line
	4750 1400 3850 1400
Wire Wire Line
	3850 1300 3850 1400
Connection ~ 3850 1400
Wire Wire Line
	3850 1400 3800 1400
Wire Wire Line
	3850 1550 3850 1400
Wire Wire Line
	3600 1700 3600 2150
Wire Wire Line
	3600 2150 3850 2150
Connection ~ 3850 2150
$Comp
L power:GND #PWR017
U 1 1 5A426013
P 6900 2200
F 0 "#PWR017" H 6900 1950 50  0001 C CNN
F 1 "GND" H 6905 2027 50  0000 C CNN
F 2 "" H 6900 2200 50  0001 C CNN
F 3 "" H 6900 2200 50  0001 C CNN
	1    6900 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR018
U 1 1 5A426108
P 6900 850
F 0 "#PWR018" H 6900 700 50  0001 C CNN
F 1 "+3V3" H 6915 1023 50  0000 C CNN
F 2 "" H 6900 850 50  0001 C CNN
F 3 "" H 6900 850 50  0001 C CNN
	1    6900 850 
	1    0    0    -1  
$EndComp
$Comp
L device:C C10
U 1 1 5A426147
P 6600 900
F 0 "C10" V 6348 900 50  0000 C CNN
F 1 "0.1u" V 6439 900 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 6638 750 50  0001 C CNN
F 3 "" H 6600 900 50  0001 C CNN
	1    6600 900 
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5A426342
P 6350 1000
F 0 "#PWR019" H 6350 750 50  0001 C CNN
F 1 "GND" H 6355 827 50  0000 C CNN
F 2 "" H 6350 1000 50  0001 C CNN
F 3 "" H 6350 1000 50  0001 C CNN
	1    6350 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1000 6350 900 
Wire Wire Line
	6350 900  6450 900 
Wire Wire Line
	6750 900  6900 900 
Wire Wire Line
	6900 900  6900 850 
Wire Wire Line
	6900 900  6900 1300
Connection ~ 6900 900 
Text GLabel 7600 1600 2    60   BiDi ~ 0
CAN+
Text GLabel 7600 1700 2    60   BiDi ~ 0
CAN-
Text GLabel 7500 5100 2    60   BiDi ~ 0
WAKE
$Comp
L power:+BATT #PWR026
U 1 1 5A43BAA0
P 3400 950
F 0 "#PWR026" H 3400 800 50  0001 C CNN
F 1 "+BATT" H 3415 1123 50  0000 C CNN
F 2 "" H 3400 950 50  0001 C CNN
F 3 "" H 3400 950 50  0001 C CNN
	1    3400 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 950  3400 1000
Connection ~ 3400 1000
$Comp
L device:Q_PMOS_GSD Q4
U 1 1 5A4405D4
P 9750 2150
F 0 "Q4" H 9956 2196 50  0000 L CNN
F 1 "NDS332P" H 9956 2105 50  0000 L CNN
F 2 "cvra/kicad-lib/footprints/_std.pretty:SSOT-3" H 9950 2250 50  0001 C CNN
F 3 "" H 9750 2150 50  0001 C CNN
	1    9750 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 2350 9850 2550
$Comp
L device:R R8
U 1 1 5A44C126
P 9450 2300
F 0 "R8" H 9380 2254 50  0000 R CNN
F 1 "10k" H 9380 2345 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9380 2300 50  0001 C CNN
F 3 "" H 9450 2300 50  0001 C CNN
	1    9450 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	9450 2150 9550 2150
Text GLabel 9400 2150 0    60   Input ~ 0
~ENABLE_SCREEN
Text GLabel 1700 5000 0    60   Output ~ 0
~ENABLE_SCREEN
Wire Wire Line
	9400 2150 9450 2150
Connection ~ 9450 2150
$Comp
L W_RTX:ITEAD_HC-05 U7
U 1 1 5A479ECC
P 9650 4850
F 0 "U7" H 9650 6000 60  0000 C CNN
F 1 "ITEAD_HC-05" H 9650 5894 60  0000 C CNN
F 2 "pelrun/libKiCad/footprint/w_rf_modules.pretty:ITEAD_HC-05" H 9650 4850 60  0001 C CNN
F 3 "" H 9650 5894 60  0000 C CNN
	1    9650 4850
	1    0    0    -1  
$EndComp
Text GLabel 7500 5600 2    60   Input ~ 0
RX
Text GLabel 7500 5500 2    60   Output ~ 0
TX
Text GLabel 9050 4500 0    60   Output ~ 0
RX
Text GLabel 9050 4400 0    60   Input ~ 0
TX
Text GLabel 10650 5550 2    60   Input ~ 0
BT_KEY
$Comp
L power:GND #PWR029
U 1 1 5A497F55
P 9650 5900
F 0 "#PWR029" H 9650 5650 50  0001 C CNN
F 1 "GND" H 9655 5727 50  0000 C CNN
F 2 "" H 9650 5900 50  0001 C CNN
F 3 "" H 9650 5900 50  0001 C CNN
	1    9650 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5850 9650 5900
Wire Wire Line
	9550 5800 9550 5850
Wire Wire Line
	9550 5850 9650 5850
Connection ~ 9650 5850
Wire Wire Line
	9650 5800 9650 5850
Wire Wire Line
	9750 5800 9750 5850
Wire Wire Line
	9750 5850 9650 5850
$Comp
L device:Q_PMOS_GSD Q3
U 1 1 5A4AA287
P 8800 3500
F 0 "Q3" H 9006 3546 50  0000 L CNN
F 1 "NDS332P" H 9006 3455 50  0000 L CNN
F 2 "cvra/kicad-lib/footprints/_std.pretty:SSOT-3" H 9000 3600 50  0001 C CNN
F 3 "" H 8800 3500 50  0001 C CNN
	1    8800 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	9000 3600 9650 3600
Wire Wire Line
	9650 3600 9650 3900
$Comp
L device:R R7
U 1 1 5A4BD356
P 8400 3300
F 0 "R7" H 8330 3254 50  0000 R CNN
F 1 "10k" H 8330 3345 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 8330 3300 50  0001 C CNN
F 3 "" H 8400 3300 50  0001 C CNN
	1    8400 3300
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR030
U 1 1 5A4BD3F4
P 7800 3600
F 0 "#PWR030" H 7800 3450 50  0001 C CNN
F 1 "+3V3" H 7815 3773 50  0000 C CNN
F 2 "" H 7800 3600 50  0001 C CNN
F 3 "" H 7800 3600 50  0001 C CNN
	1    7800 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3300 8800 3300
Text GLabel 8800 3050 0    60   Input ~ 0
DISBABLE_BLUETOOTH
Wire Wire Line
	8800 3050 8800 3300
Connection ~ 8800 3300
$Comp
L device:R R6
U 1 1 5A54E603
P 7450 1650
F 0 "R6" H 7380 1604 50  0000 R CNN
F 1 "120" H 7380 1695 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 7380 1650 50  0001 C CNN
F 3 "" H 7450 1650 50  0001 C CNN
	1    7450 1650
	1    0    0    -1  
$EndComp
$Comp
L device:R R14
U 1 1 5A560CD1
P 6400 1950
F 0 "R14" H 6330 1904 50  0000 R CNN
F 1 "10k" H 6330 1995 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 6330 1950 50  0001 C CNN
F 3 "" H 6400 1950 50  0001 C CNN
	1    6400 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	6500 1800 6400 1800
Wire Wire Line
	6400 2100 6400 2150
Wire Wire Line
	6400 2150 6900 2150
Wire Wire Line
	6900 2150 6900 2200
Wire Wire Line
	6900 2000 6900 2150
Connection ~ 6900 2150
$Comp
L Connector:Conn_01x03 J3
U 1 1 5A57AA24
P 8350 1000
F 0 "J3" V 8316 812 50  0000 R CNN
F 1 "Left" V 8225 812 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_EH_B03B-EH-A_03x2.50mm_Straight_LargePads" H 8350 1000 50  0001 C CNN
F 3 "~" H 8350 1000 50  0001 C CNN
	1    8350 1000
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03 J4
U 1 1 5A57AB93
P 9150 1000
F 0 "J4" V 9116 812 50  0000 R CNN
F 1 "Right" V 9025 812 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_EH_B03B-EH-A_03x2.50mm_Straight_LargePads" H 9150 1000 50  0001 C CNN
F 3 "~" H 9150 1000 50  0001 C CNN
	1    9150 1000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR033
U 1 1 5A57AF77
P 8250 1200
F 0 "#PWR033" H 8250 950 50  0001 C CNN
F 1 "GND" H 8255 1027 50  0000 C CNN
F 2 "" H 8250 1200 50  0001 C CNN
F 3 "" H 8250 1200 50  0001 C CNN
	1    8250 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 5A57AFD8
P 9050 1200
F 0 "#PWR034" H 9050 950 50  0001 C CNN
F 1 "GND" H 9055 1027 50  0000 C CNN
F 2 "" H 9050 1200 50  0001 C CNN
F 3 "" H 9050 1200 50  0001 C CNN
	1    9050 1200
	1    0    0    -1  
$EndComp
Text GLabel 8350 1200 3    60   Output ~ 0
~LEFT_A
Text GLabel 8450 1200 3    60   Output ~ 0
~LEFT_B
Text GLabel 9150 1200 3    60   Output ~ 0
~RIGHT_A
Text GLabel 9250 1200 3    60   Output ~ 0
~RIGHT_B
Text GLabel 1700 5800 0    60   Input ~ 0
~LEFT_A
Text GLabel 1700 5900 0    60   Input ~ 0
~LEFT_B
Text GLabel 1700 6000 0    60   Input ~ 0
~RIGHT_A
Text GLabel 1700 6100 0    60   Input ~ 0
~RIGHT_B
Wire Wire Line
	9850 1350 9850 1950
Wire Wire Line
	9950 1350 9950 1750
Wire Wire Line
	7300 1600 7300 1500
Wire Wire Line
	7300 1500 7450 1500
Wire Wire Line
	7450 1500 7600 1500
Wire Wire Line
	7600 1500 7600 1600
Connection ~ 7450 1500
Wire Wire Line
	7300 1700 7300 1800
Wire Wire Line
	7300 1800 7450 1800
Wire Wire Line
	7600 1700 7600 1800
Wire Wire Line
	7600 1800 7450 1800
Connection ~ 7450 1800
Text GLabel 1700 5600 0    60   Output ~ 0
BT_KEY
$Comp
L MCU_ST_STM32:STM32F103C8Tx U1
U 1 1 5A65D168
P 4600 4700
F 0 "U1" H 4600 6678 50  0000 C CNN
F 1 "STM32F103C8Tx" H 4600 6587 50  0000 C CNN
F 2 "kicad-castellated-breakouts:QFP48-1.27MM-CASTELLATED" H 7400 6375 50  0001 R TNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 4600 4700 50  0001 C CNN
	1    4600 4700
	1    0    0    -1  
$EndComp
Text GLabel 1700 5700 0    60   Output ~ 0
DISBABLE_BLUETOOTH
Text GLabel 6500 1500 0    60   Input ~ 0
CAN_TX
Text GLabel 6500 1600 0    60   Output ~ 0
CAN_RX
Text GLabel 1700 5500 0    60   Output ~ 0
CAN_TX
Text GLabel 1700 5400 0    60   Input ~ 0
CAN_RX
Text GLabel 1700 5200 0    60   BiDi ~ 0
SCL
Text GLabel 1700 5300 0    60   BiDi ~ 0
SDA
$Comp
L power:+3V3 #PWR07
U 1 1 5A68EB06
P 1250 3300
F 0 "#PWR07" H 1250 3150 50  0001 C CNN
F 1 "+3V3" V 1265 3428 50  0000 L CNN
F 2 "" H 1250 3300 50  0001 C CNN
F 3 "" H 1250 3300 50  0001 C CNN
	1    1250 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04 J5
U 1 1 5A68EC32
P 5900 6950
F 0 "J5" H 5980 6942 50  0000 L CNN
F 1 "Programmer" H 5980 6851 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:Pin_Header_Straight_1x04_Pitch2.54mm_LargePads" H 5900 6950 50  0001 C CNN
F 3 "~" H 5900 6950 50  0001 C CNN
	1    5900 6950
	1    0    0    -1  
$EndComp
$Comp
L device:R R15
U 1 1 5A68ECA0
P 5350 6850
F 0 "R15" H 5280 6804 50  0000 R CNN
F 1 "10k" H 5280 6895 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5280 6850 50  0001 C CNN
F 3 "" H 5350 6850 50  0001 C CNN
	1    5350 6850
	0    1    1    0   
$EndComp
$Comp
L device:R R16
U 1 1 5A68ED67
P 5350 7150
F 0 "R16" H 5280 7104 50  0000 R CNN
F 1 "10k" H 5280 7195 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5280 7150 50  0001 C CNN
F 3 "" H 5350 7150 50  0001 C CNN
	1    5350 7150
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR08
U 1 1 5A68EEA8
P 5600 6750
F 0 "#PWR08" H 5600 6600 50  0001 C CNN
F 1 "+3V3" H 5615 6923 50  0000 C CNN
F 2 "" H 5600 6750 50  0001 C CNN
F 3 "" H 5600 6750 50  0001 C CNN
	1    5600 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5A68EF5A
P 5600 7300
F 0 "#PWR09" H 5600 7050 50  0001 C CNN
F 1 "GND" H 5605 7127 50  0000 C CNN
F 2 "" H 5600 7300 50  0001 C CNN
F 3 "" H 5600 7300 50  0001 C CNN
	1    5600 7300
	1    0    0    -1  
$EndComp
Text GLabel 5050 6950 1    60   BiDi ~ 0
SWDIO
Text GLabel 5100 7250 3    60   BiDi ~ 0
SWCLK
Wire Wire Line
	5050 6950 5700 6950
Wire Wire Line
	5200 7150 5050 7150
Wire Wire Line
	5050 7150 5050 6950
Wire Wire Line
	5500 7150 5600 7150
Wire Wire Line
	5600 7300 5600 7150
Connection ~ 5600 7150
Wire Wire Line
	5600 7150 5700 7150
Wire Wire Line
	5700 7050 5200 7050
Wire Wire Line
	5100 7050 5100 7250
Wire Wire Line
	5200 6850 5200 7050
Connection ~ 5200 7050
Wire Wire Line
	5200 7050 5100 7050
Wire Wire Line
	5500 6850 5600 6850
Wire Wire Line
	5600 6750 5600 6850
Connection ~ 5600 6850
Wire Wire Line
	5600 6850 5700 6850
Text GLabel 7500 5900 2    60   BiDi ~ 0
SWDIO
Text GLabel 7500 6000 2    60   BiDi ~ 0
SWCLK
$Comp
L power:GND #PWR010
U 1 1 5A6A1D31
P 4550 6600
F 0 "#PWR010" H 4550 6350 50  0001 C CNN
F 1 "GND" H 4555 6427 50  0000 C CNN
F 2 "" H 4550 6600 50  0001 C CNN
F 3 "" H 4550 6600 50  0001 C CNN
	1    4550 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 6600 4550 6500
Connection ~ 4550 6500
Text GLabel 2500 7050 1    60   BiDi ~ 0
BOOT0
Text GLabel 1700 3500 0    60   BiDi ~ 0
BOOT0
Text GLabel 2650 7050 1    60   BiDi ~ 0
BOOT1
Text GLabel 1700 4800 0    60   BiDi ~ 0
BOOT1
$Comp
L device:R R1
U 1 1 5A6B09A1
P 2500 7200
F 0 "R1" H 2430 7154 50  0000 R CNN
F 1 "100k" H 2430 7245 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2430 7200 50  0001 C CNN
F 3 "" H 2500 7200 50  0001 C CNN
	1    2500 7200
	1    0    0    -1  
$EndComp
$Comp
L device:R R5
U 1 1 5A6B0A45
P 2650 7200
F 0 "R5" H 2580 7154 50  0000 R CNN
F 1 "100k" H 2580 7245 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2580 7200 50  0001 C CNN
F 3 "" H 2650 7200 50  0001 C CNN
	1    2650 7200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5A6B0C29
P 2650 7350
F 0 "#PWR011" H 2650 7100 50  0001 C CNN
F 1 "GND" H 2655 7177 50  0000 C CNN
F 2 "" H 2650 7350 50  0001 C CNN
F 3 "" H 2650 7350 50  0001 C CNN
	1    2650 7350
	0    -1   -1   0   
$EndComp
$Comp
L device:C C8
U 1 1 5A66F12F
P 4250 2700
F 0 "C8" V 3998 2700 50  0000 C CNN
F 1 "0.1" V 4089 2700 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 4288 2550 50  0001 C CNN
F 3 "" H 4250 2700 50  0001 C CNN
	1    4250 2700
	0    1    1    0   
$EndComp
$Comp
L device:C C7
U 1 1 5A66F2DA
P 4250 2500
F 0 "C7" V 3998 2500 50  0000 C CNN
F 1 "0.1" V 4089 2500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 4288 2350 50  0001 C CNN
F 3 "" H 4250 2500 50  0001 C CNN
	1    4250 2500
	0    1    1    0   
$EndComp
$Comp
L device:C C11
U 1 1 5A66F330
P 4850 2700
F 0 "C11" V 4598 2700 50  0000 C CNN
F 1 "0.1" V 4689 2700 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 4888 2550 50  0001 C CNN
F 3 "" H 4850 2700 50  0001 C CNN
	1    4850 2700
	0    1    1    0   
$EndComp
$Comp
L device:C C9
U 1 1 5A66F39B
P 4850 2500
F 0 "C9" V 4598 2500 50  0000 C CNN
F 1 "0.1" V 4689 2500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 4888 2350 50  0001 C CNN
F 3 "" H 4850 2500 50  0001 C CNN
	1    4850 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 2900 4500 2700
Wire Wire Line
	4500 2500 4400 2500
Wire Wire Line
	4400 2700 4400 2900
Wire Wire Line
	4600 2900 4600 2700
Wire Wire Line
	4600 2500 4700 2500
Wire Wire Line
	4700 2700 4700 2900
$Comp
L power:GND #PWR013
U 1 1 5A681017
P 4000 2700
F 0 "#PWR013" H 4000 2450 50  0001 C CNN
F 1 "GND" H 4005 2527 50  0000 C CNN
F 2 "" H 4000 2700 50  0001 C CNN
F 3 "" H 4000 2700 50  0001 C CNN
	1    4000 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5A68106C
P 5100 2700
F 0 "#PWR014" H 5100 2450 50  0001 C CNN
F 1 "GND" H 5105 2527 50  0000 C CNN
F 2 "" H 5100 2700 50  0001 C CNN
F 3 "" H 5100 2700 50  0001 C CNN
	1    5100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2500 5100 2500
Wire Wire Line
	5100 2500 5100 2700
Wire Wire Line
	5000 2700 5100 2700
Connection ~ 5100 2700
Wire Wire Line
	4100 2700 4000 2700
Wire Wire Line
	4100 2500 4000 2500
Wire Wire Line
	4000 2500 4000 2700
Connection ~ 4000 2700
$Comp
L power:+3V3 #PWR015
U 1 1 5A694B13
P 4550 2500
F 0 "#PWR015" H 4550 2350 50  0001 C CNN
F 1 "+3V3" V 4565 2628 50  0000 L CNN
F 2 "" H 4550 2500 50  0001 C CNN
F 3 "" H 4550 2500 50  0001 C CNN
	1    4550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2500 4550 2500
Connection ~ 4500 2500
Wire Wire Line
	4600 2500 4550 2500
Connection ~ 4600 2500
Connection ~ 4550 2500
Wire Wire Line
	4700 2700 4600 2700
Connection ~ 4700 2700
Connection ~ 4600 2700
Wire Wire Line
	4600 2700 4600 2500
Wire Wire Line
	4400 2700 4500 2700
Connection ~ 4400 2700
Connection ~ 4500 2700
Wire Wire Line
	4500 2700 4500 2500
$Comp
L device:R R11
U 1 1 5A6B44E6
P 10450 5350
F 0 "R11" H 10380 5304 50  0000 R CNN
F 1 "330" H 10380 5395 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10380 5350 50  0001 C CNN
F 3 "" H 10450 5350 50  0001 C CNN
	1    10450 5350
	0    -1   -1   0   
$EndComp
$Comp
L device:R R12
U 1 1 5A6B45CD
P 10450 5550
F 0 "R12" H 10380 5504 50  0000 R CNN
F 1 "330" H 10380 5595 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10380 5550 50  0001 C CNN
F 3 "" H 10450 5550 50  0001 C CNN
	1    10450 5550
	0    -1   -1   0   
$EndComp
$Comp
L device:R R13
U 1 1 5A6B46D1
P 10450 5900
F 0 "R13" H 10380 5854 50  0000 R CNN
F 1 "10k" H 10380 5945 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 10380 5900 50  0001 C CNN
F 3 "" H 10450 5900 50  0001 C CNN
	1    10450 5900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5A6B477E
P 10750 5900
F 0 "#PWR016" H 10750 5650 50  0001 C CNN
F 1 "GND" H 10755 5727 50  0000 C CNN
F 2 "" H 10750 5900 50  0001 C CNN
F 3 "" H 10750 5900 50  0001 C CNN
	1    10750 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 5350 10250 5350
Wire Wire Line
	10600 5550 10650 5550
Wire Wire Line
	10300 5550 10250 5550
Wire Wire Line
	10300 5900 10250 5900
Wire Wire Line
	10250 5900 10250 5550
Connection ~ 10250 5550
Wire Wire Line
	10600 5900 10750 5900
Text GLabel 10600 5350 2    60   BiDi ~ 0
BOOT0
$Comp
L device:R R9
U 1 1 5A6CC7D8
P 1500 3300
F 0 "R9" H 1430 3254 50  0000 R CNN
F 1 "10k" H 1430 3345 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1430 3300 50  0001 C CNN
F 3 "" H 1500 3300 50  0001 C CNN
	1    1500 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1350 3300 1250 3300
Wire Wire Line
	1650 3300 1700 3300
$Comp
L power:+3V3 #PWR020
U 1 1 5A6D6447
P 1250 3700
F 0 "#PWR020" H 1250 3550 50  0001 C CNN
F 1 "+3V3" V 1265 3828 50  0000 L CNN
F 2 "" H 1250 3700 50  0001 C CNN
F 3 "" H 1250 3700 50  0001 C CNN
	1    1250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 3700 1700 3700
$Comp
L device:Crystal Y1
U 1 1 5A6DB766
P 1450 3950
F 0 "Y1" V 1404 4081 50  0000 L CNN
F 1 "Crystal" V 1495 4081 50  0000 L CNN
F 2 "brunoeagle/kicad-open-modules:CRYSTAL_SMD" H 1450 3950 50  0001 C CNN
F 3 "" H 1450 3950 50  0001 C CNN
	1    1450 3950
	0    1    1    0   
$EndComp
$Comp
L device:C C1
U 1 1 5A6DB88E
P 1300 3800
F 0 "C1" V 1048 3800 50  0000 C CNN
F 1 "22p" V 1139 3800 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 1338 3650 50  0001 C CNN
F 3 "" H 1300 3800 50  0001 C CNN
	1    1300 3800
	0    1    1    0   
$EndComp
$Comp
L device:C C2
U 1 1 5A6DB900
P 1300 4100
F 0 "C2" V 1048 4100 50  0000 C CNN
F 1 "22p" V 1139 4100 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 1338 3950 50  0001 C CNN
F 3 "" H 1300 4100 50  0001 C CNN
	1    1300 4100
	0    1    1    0   
$EndComp
$Comp
L device:C C4
U 1 1 5A6DBB7E
P 1300 4550
F 0 "C4" V 1048 4550 50  0000 C CNN
F 1 "22p" V 1139 4550 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 1338 4400 50  0001 C CNN
F 3 "" H 1300 4550 50  0001 C CNN
	1    1300 4550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5A6DBBE0
P 1100 4550
F 0 "#PWR021" H 1100 4300 50  0001 C CNN
F 1 "GND" H 1105 4377 50  0000 C CNN
F 2 "" H 1100 4550 50  0001 C CNN
F 3 "" H 1100 4550 50  0001 C CNN
	1    1100 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3800 1100 3800
Wire Wire Line
	1100 3800 1100 4100
Wire Wire Line
	1150 4550 1100 4550
Connection ~ 1100 4550
Wire Wire Line
	1150 4250 1100 4250
Connection ~ 1100 4250
Wire Wire Line
	1100 4250 1100 4550
Wire Wire Line
	1150 4100 1100 4100
Connection ~ 1100 4100
Wire Wire Line
	1100 4100 1100 4250
Wire Wire Line
	1450 3800 1600 3800
Connection ~ 1450 3800
Wire Wire Line
	1450 4100 1600 4100
Connection ~ 1450 4100
$Comp
L device:R R10
U 1 1 5A70AF0F
P 1600 3950
F 0 "R10" H 1530 3904 50  0000 R CNN
F 1 "1M" H 1530 3995 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1530 3950 50  0001 C CNN
F 3 "" H 1600 3950 50  0001 C CNN
	1    1600 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3800 1700 3800
Wire Wire Line
	1700 3800 1700 3900
Connection ~ 1600 3800
Wire Wire Line
	1700 4000 1700 4100
Wire Wire Line
	1700 4100 1600 4100
Connection ~ 1600 4100
$Comp
L device:Crystal_GND23_Small Y2
U 1 1 5A719247
P 1450 4400
F 0 "Y2" V 1404 4566 50  0000 L CNN
F 1 "Crystal_GND23_Small" V 1495 4566 50  0000 L CNN
F 2 "KiCad/Crystals.pretty:Crystal_SMD_SeikoEpson_MC306-4pin_8.0x3.2mm" H 1450 4400 50  0001 C CNN
F 3 "" H 1450 4400 50  0001 C CNN
	1    1450 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 4500 1450 4550
Connection ~ 1450 4550
Wire Wire Line
	2650 7350 2500 7350
Connection ~ 2650 7350
$Comp
L power:+3V3 #PWR012
U 1 1 5A7447A5
P 2200 7500
F 0 "#PWR012" H 2200 7350 50  0001 C CNN
F 1 "+3V3" H 2215 7673 50  0000 C CNN
F 2 "" H 2200 7500 50  0001 C CNN
F 3 "" H 2200 7500 50  0001 C CNN
	1    2200 7500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2200 7050 2500 7050
Wire Wire Line
	3000 7050 2650 7050
Wire Wire Line
	3000 7500 2200 7500
Connection ~ 2200 7500
$Comp
L device:C C3
U 1 1 5A6DBB18
P 1300 4250
F 0 "C3" V 1048 4250 50  0000 C CNN
F 1 "22p" V 1139 4250 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 1338 4100 50  0001 C CNN
F 3 "" H 1300 4250 50  0001 C CNN
	1    1300 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 4250 1450 4300
Wire Wire Line
	1450 4250 1600 4250
Wire Wire Line
	1600 4250 1600 4300
Wire Wire Line
	1600 4300 1700 4300
Connection ~ 1450 4250
Wire Wire Line
	1650 4550 1650 4400
Wire Wire Line
	1650 4400 1700 4400
Wire Wire Line
	1450 4550 1650 4550
$Comp
L power:GND #PWR022
U 1 1 5A742B39
P 8100 3300
F 0 "#PWR022" H 8100 3050 50  0001 C CNN
F 1 "GND" H 8105 3127 50  0000 C CNN
F 2 "" H 8100 3300 50  0001 C CNN
F 3 "" H 8100 3300 50  0001 C CNN
	1    8100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 3300 8100 3300
Wire Wire Line
	7800 3600 8600 3600
Wire Wire Line
	9450 2550 9850 2550
Wire Wire Line
	9450 2450 9450 2550
Connection ~ 9850 2550
Wire Wire Line
	9850 2550 9850 2600
Text GLabel 7500 4800 2    60   Output ~ 0
TX
Text GLabel 7500 4900 2    60   Input ~ 0
RX
$Comp
L Connector:Conn_01x02 J2
U 1 1 5A743381
P 8400 4750
F 0 "J2" V 8366 4562 50  0000 R CNN
F 1 "UART" V 8275 4562 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_EH_B02B-EH-A_02x2.50mm_Straight_LargePads" H 8400 4750 50  0001 C CNN
F 3 "~" H 8400 4750 50  0001 C CNN
	1    8400 4750
	0    -1   -1   0   
$EndComp
Text GLabel 8400 4950 3    60   Output ~ 0
TX
Text GLabel 8500 4950 3    60   Input ~ 0
RX
$Comp
L Connector:Conn_01x02 J7
U 1 1 5A761DF6
P 3200 7050
F 0 "J7" H 3280 7042 50  0000 L CNN
F 1 "B1_JMP" H 3280 6951 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 3200 7050 50  0001 C CNN
F 3 "~" H 3200 7050 50  0001 C CNN
	1    3200 7050
	1    0    0    -1  
$EndComp
Connection ~ 4600 6500
Wire Wire Line
	4550 6500 4600 6500
Wire Wire Line
	4700 6500 4600 6500
Connection ~ 4500 6500
Wire Wire Line
	4500 6500 4550 6500
Wire Wire Line
	4400 6500 4500 6500
$Comp
L Connector:Conn_01x02 J6
U 1 1 5A77B1E4
P 2000 7150
F 0 "J6" H 1920 6825 50  0000 C CNN
F 1 "B0_JMP" H 1920 6916 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 2000 7150 50  0001 C CNN
F 3 "~" H 2000 7150 50  0001 C CNN
	1    2000 7150
	-1   0    0    1   
$EndComp
Wire Wire Line
	3000 7150 3000 7500
Wire Wire Line
	2200 7150 2200 7500
$EndSCHEMATC
