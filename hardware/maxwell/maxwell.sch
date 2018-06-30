EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2900 2500 3    60   BiDi ~ 0
BOOT1
$Comp
L maxwell-rescue:Conn_01x04-RESCUE-maxwell J6
U 1 1 5A178B78
P 2350 3400
F 0 "J6" H 2430 3392 50  0000 L CNN
F 1 "Programmer" H 2430 3301 50  0000 L CNN
F 2 "KiCad/Pin_Headers.pretty:Pin_Header_Straight_1x04_Pitch2.54mm" H 2350 3400 50  0001 C CNN
F 3 "" H 2350 3400 50  0001 C CNN
	1    2350 3400
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR03
U 1 1 5A178E3B
P 1600 3250
F 0 "#PWR03" H 1600 3100 50  0001 C CNN
F 1 "+3V3" H 1615 3423 50  0000 C CNN
F 2 "" H 1600 3250 50  0001 C CNN
F 3 "" H 1600 3250 50  0001 C CNN
	1    1600 3250
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR04
U 1 1 5A178E94
P 1600 3650
F 0 "#PWR04" H 1600 3400 50  0001 C CNN
F 1 "GND" H 1605 3477 50  0000 C CNN
F 2 "" H 1600 3650 50  0001 C CNN
F 3 "" H 1600 3650 50  0001 C CNN
	1    1600 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3650 1600 3600
Wire Wire Line
	1550 3600 1600 3600
Text GLabel 1150 3400 1    60   BiDi ~ 0
SWDIO
$Comp
L maxwell-rescue:R-RESCUE-maxwell R8
U 1 1 5A179266
P 1400 3600
F 0 "R8" V 1193 3600 50  0000 C CNN
F 1 "10k" V 1284 3600 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1330 3600 50  0001 C CNN
F 3 "" H 1400 3600 50  0001 C CNN
	1    1400 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 3400 1150 3400
Connection ~ 1600 3600
Wire Wire Line
	1250 3600 1150 3600
Wire Wire Line
	1150 3600 1150 3400
Text GLabel 1200 3700 3    60   BiDi ~ 0
SWCLK
$Comp
L maxwell-rescue:R-RESCUE-maxwell R7
U 1 1 5A179C62
P 1400 3300
F 0 "R7" V 1193 3300 50  0000 C CNN
F 1 "10k" V 1284 3300 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1330 3300 50  0001 C CNN
F 3 "" H 1400 3300 50  0001 C CNN
	1    1400 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 3500 1250 3500
Wire Wire Line
	1200 3500 1200 3700
Wire Wire Line
	1250 3500 1250 3300
Connection ~ 1250 3500
$Sheet
S 800  750  1250 700 
U 5A1FA1FC
F0 "Microcontroller" 60
F1 "microcontroller.sch" 60
$EndSheet
$Sheet
S 800  1750 1250 700 
U 5A1FEBCF
F0 "Power" 60
F1 "power.sch" 60
$EndSheet
$Comp
L maxwell-rescue:SN65HVD233-RESCUE-maxwell U2
U 1 1 5A227BE3
P 1550 5950
F 0 "U2" H 1550 6428 50  0000 C CNN
F 1 "SN65HVD233" H 1550 6337 50  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOIC-8" H 1550 5450 50  0001 C CNN
F 3 "" H 1450 6350 50  0001 C CNN
	1    1550 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 5350 1550 5650
$Comp
L maxwell-rescue:R-RESCUE-maxwell R1
U 1 1 5A2285B9
P 1000 6300
F 0 "R1" H 1070 6346 50  0000 L CNN
F 1 "10k" H 1070 6255 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 930 6300 50  0001 C CNN
F 3 "" H 1000 6300 50  0001 C CNN
	1    1000 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 6150 1000 6150
Wire Wire Line
	1000 6450 1000 6550
Wire Wire Line
	1000 6550 1550 6550
Wire Wire Line
	1950 5950 2050 5950
Wire Wire Line
	1950 6050 2000 6050
Wire Wire Line
	2250 5950 2250 6550
Wire Wire Line
	2250 6550 2550 6550
Connection ~ 2250 5950
Wire Wire Line
	2300 6050 2300 6650
Wire Wire Line
	2300 6650 2550 6650
Connection ~ 2300 6050
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR09
U 1 1 5A228E20
P 2350 6750
F 0 "#PWR09" H 2350 6500 50  0001 C CNN
F 1 "GND" H 2355 6577 50  0000 C CNN
F 2 "" H 2350 6750 50  0001 C CNN
F 3 "" H 2350 6750 50  0001 C CNN
	1    2350 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 6750 2350 6750
Wire Wire Line
	2350 6750 2350 6150
Wire Wire Line
	2350 6150 2550 6150
Wire Wire Line
	2550 5850 2150 5850
Wire Wire Line
	2550 6450 2150 6450
Wire Wire Line
	2150 6450 2150 5850
$Comp
L maxwell-rescue:C-RESCUE-maxwell C4
U 1 1 5A22B0AC
P 1700 5350
F 0 "C4" V 1448 5350 50  0000 C CNN
F 1 "0.1u" V 1539 5350 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 1738 5200 50  0001 C CNN
F 3 "" H 1700 5350 50  0001 C CNN
	1    1700 5350
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR011
U 1 1 5A22B0FF
P 1850 5350
F 0 "#PWR011" H 1850 5100 50  0001 C CNN
F 1 "GND" H 1855 5177 50  0000 C CNN
F 2 "" H 1850 5350 50  0001 C CNN
F 3 "" H 1850 5350 50  0001 C CNN
	1    1850 5350
	1    0    0    -1  
$EndComp
Text GLabel 9850 4550 3    60   Input ~ 0
BT_DI
Text GLabel 9750 4550 3    60   Output ~ 0
BT_DO
Text GLabel 10300 4050 2    60   BiDi ~ 0
BOOT0
Text GLabel 10300 3950 2    60   Input ~ 0
BT_KEY
$Comp
L maxwell-rescue:Buzzer-RESCUE-maxwell BZ1
U 1 1 5A249244
P 4000 3900
F 0 "BZ1" H 4153 3929 50  0000 L CNN
F 1 "Buzzer" H 4153 3838 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:12mm_buzzer" V 3975 4000 50  0001 C CNN
F 3 "" V 3975 4000 50  0001 C CNN
	1    4000 3900
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:BSS138-RESCUE-maxwell Q1
U 1 1 5A249471
P 3800 4200
F 0 "Q1" V 4143 4200 50  0000 C CNN
F 1 "BSS138" V 4052 4200 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SOT-23_LargePads" H 4000 4125 50  0001 L CIN
F 3 "" H 3800 4200 50  0001 L CNN
	1    3800 4200
	1    0    0    -1  
$EndComp
Text GLabel 3350 4200 0    60   Input ~ 0
BUZZER
$Comp
L maxwell-rescue:Conn_01x03-RESCUE-maxwell J3
U 1 1 5A24A6D8
P 2150 4550
F 0 "J3" H 2230 4592 50  0000 L CNN
F 1 "Neopixel" H 2230 4501 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 2150 4550 50  0001 C CNN
F 3 "" H 2150 4550 50  0001 C CNN
	1    2150 4550
	1    0    0    -1  
$EndComp
Text GLabel 1450 4550 0    60   Input ~ 0
NEOPIXEL
Wire Wire Line
	1750 4450 1950 4450
Wire Wire Line
	1750 4650 1950 4650
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR017
U 1 1 5A2590C5
P 1750 4450
F 0 "#PWR017" H 1750 4250 50  0001 C CNN
F 1 "GNDPWR" H 1754 4524 50  0000 C CNN
F 2 "" H 1750 4400 50  0001 C CNN
F 3 "" H 1750 4400 50  0001 C CNN
	1    1750 4450
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:Conn_01x05-RESCUE-maxwell J1
U 1 1 5A25E0A2
P 2750 5950
F 0 "J1" H 2830 5992 50  0000 L CNN
F 1 "Canbus 1" H 2830 5901 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B05B-XH-A_05x2.50mm_Straight_LargePads" H 2750 5950 50  0001 C CNN
F 3 "" H 2750 5950 50  0001 C CNN
	1    2750 5950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x05-RESCUE-maxwell J2
U 1 1 5A25E262
P 2750 6550
F 0 "J2" H 2830 6592 50  0000 L CNN
F 1 "Canbus 2" H 2830 6501 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B05B-XH-A_05x2.50mm_Straight_LargePads" H 2750 6550 50  0001 C CNN
F 3 "" H 2750 6550 50  0001 C CNN
	1    2750 6550
	1    0    0    -1  
$EndComp
Text GLabel 2450 5750 1    60   Output ~ 0
POWER_ON
Wire Wire Line
	2550 5750 2450 5750
Wire Wire Line
	2450 5750 2450 6350
Wire Wire Line
	2450 6350 2550 6350
Text Label 2000 5950 0    60   ~ 0
CAN+
Text Label 2000 6050 0    60   ~ 0
CAN-
$Comp
L maxwell-rescue:R-RESCUE-maxwell R31
U 1 1 5A271748
P 1600 4550
F 0 "R31" H 1670 4596 50  0000 L CNN
F 1 "330" H 1670 4505 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1530 4550 50  0001 C CNN
F 3 "" H 1600 4550 50  0001 C CNN
	1    1600 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 4550 1950 4550
$Comp
L maxwell-rescue:R-RESCUE-maxwell R4
U 1 1 5A2AAAD0
P 3900 4600
F 0 "R4" V 3693 4600 50  0000 C CNN
F 1 ">35" V 3784 4600 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 3830 4600 50  0001 C CNN
F 3 "" H 3900 4600 50  0001 C CNN
	1    3900 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 4400 3900 4450
Wire Wire Line
	3900 4750 3900 4900
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR016
U 1 1 5A2AB94D
P 3900 4900
F 0 "#PWR016" H 3900 4650 50  0001 C CNN
F 1 "GND" H 3905 4727 50  0000 C CNN
F 2 "" H 3900 4900 50  0001 C CNN
F 3 "" H 3900 4900 50  0001 C CNN
	1    3900 4900
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R37
U 1 1 5A2B653B
P 2000 6600
F 0 "R37" H 2070 6646 50  0000 L CNN
F 1 "120" H 2070 6555 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 1930 6600 50  0001 C CNN
F 3 "" H 2000 6600 50  0001 C CNN
	1    2000 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 6050 2000 6450
Connection ~ 2000 6050
Wire Wire Line
	2050 5950 2050 6750
Wire Wire Line
	2050 6750 2000 6750
Connection ~ 2050 5950
Wire Wire Line
	1600 3600 2150 3600
Wire Wire Line
	1250 3500 2150 3500
Wire Wire Line
	1550 6550 1550 6350
Wire Wire Line
	2250 5950 2550 5950
Wire Wire Line
	2300 6050 2550 6050
Wire Wire Line
	2000 6050 2300 6050
Wire Wire Line
	2050 5950 2250 5950
Wire Wire Line
	1550 3300 1600 3300
Wire Wire Line
	1600 3250 1600 3300
Connection ~ 1600 3300
Wire Wire Line
	1600 3300 2150 3300
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR01
U 1 1 5A897B5A
P 1550 5350
F 0 "#PWR01" H 1550 5200 50  0001 C CNN
F 1 "+3V3" H 1565 5523 50  0000 C CNN
F 2 "" H 1550 5350 50  0001 C CNN
F 3 "" H 1550 5350 50  0001 C CNN
	1    1550 5350
	1    0    0    -1  
$EndComp
Connection ~ 1550 5350
Text GLabel 1150 5850 0    60   Input ~ 0
CAN_TX
Text GLabel 1150 5950 0    60   Output ~ 0
CAN_RX
Connection ~ 1550 6550
Wire Wire Line
	1550 7350 1550 6550
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR02
U 1 1 5A898046
P 1550 7350
F 0 "#PWR02" H 1550 7100 50  0001 C CNN
F 1 "GND" H 1555 7177 50  0000 C CNN
F 2 "" H 1550 7350 50  0001 C CNN
F 3 "" H 1550 7350 50  0001 C CNN
	1    1550 7350
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x02 J4
U 1 1 5A8A1BD4
P 3250 1100
F 0 "J4" H 3329 1092 50  0000 L CNN
F 1 "BOOT0" H 3329 1001 50  0000 L CNN
F 2 "coddingtonbear:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 3250 1100 50  0001 C CNN
F 3 "~" H 3250 1100 50  0001 C CNN
	1    3250 1100
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x02 J8
U 1 1 5A8A1C87
P 3250 2350
F 0 "J8" H 3329 2342 50  0000 L CNN
F 1 "BOOT1" H 3329 2251 50  0000 L CNN
F 2 "coddingtonbear:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 3250 2350 50  0001 C CNN
F 3 "~" H 3250 2350 50  0001 C CNN
	1    3250 2350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR07
U 1 1 5A8A1D67
P 3050 2300
F 0 "#PWR07" H 3050 2150 50  0001 C CNN
F 1 "+3V3" V 3065 2428 50  0000 L CNN
F 2 "" H 3050 2300 50  0001 C CNN
F 3 "" H 3050 2300 50  0001 C CNN
	1    3050 2300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR08
U 1 1 5A8A1E0D
P 3050 1050
F 0 "#PWR08" H 3050 900 50  0001 C CNN
F 1 "+3V3" V 3065 1178 50  0000 L CNN
F 2 "" H 3050 1050 50  0001 C CNN
F 3 "" H 3050 1050 50  0001 C CNN
	1    3050 1050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R5
U 1 1 5A8A1E56
P 3050 1400
F 0 "R5" H 3120 1446 50  0000 L CNN
F 1 "100k" H 3120 1355 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2980 1400 50  0001 C CNN
F 3 "" H 3050 1400 50  0001 C CNN
	1    3050 1400
	1    0    0    -1  
$EndComp
Text GLabel 2900 1250 3    60   BiDi ~ 0
BOOT0
$Comp
L maxwell-rescue:R-RESCUE-maxwell R9
U 1 1 5A8A1F0C
P 3050 2650
F 0 "R9" H 3120 2696 50  0000 L CNN
F 1 "100k" H 3120 2605 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2980 2650 50  0001 C CNN
F 3 "" H 3050 2650 50  0001 C CNN
	1    3050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1050 3050 1100
Wire Wire Line
	3050 1200 3050 1250
Wire Wire Line
	3050 1200 2900 1200
Wire Wire Line
	2900 1200 2900 1250
Connection ~ 3050 1200
Wire Wire Line
	3050 2450 2900 2450
Wire Wire Line
	2900 2450 2900 2500
Wire Wire Line
	3050 2500 3050 2450
Connection ~ 3050 2450
Wire Wire Line
	3050 2350 3050 2300
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR010
U 1 1 5A8B24E7
P 3050 2800
F 0 "#PWR010" H 3050 2550 50  0001 C CNN
F 1 "GND" H 3055 2627 50  0000 C CNN
F 2 "" H 3050 2800 50  0001 C CNN
F 3 "" H 3050 2800 50  0001 C CNN
	1    3050 2800
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR020
U 1 1 5A8B252E
P 3050 1550
F 0 "#PWR020" H 3050 1300 50  0001 C CNN
F 1 "GND" H 3055 1377 50  0000 C CNN
F 2 "" H 3050 1550 50  0001 C CNN
F 3 "" H 3050 1550 50  0001 C CNN
	1    3050 1550
	1    0    0    -1  
$EndComp
Connection ~ 2350 6750
Text GLabel 7750 1350 0    60   Input ~ 0
SPI2_CS_A
Text GLabel 7750 1750 0    60   Input ~ 0
SPI2_MOSI
Text GLabel 7750 1550 0    60   Input ~ 0
SPI2_SCK
Text GLabel 7750 1650 0    60   Output ~ 0
SPI2_MISO
$Comp
L conn:Conn_01x06 J5
U 1 1 5A872F71
P 7950 1550
F 0 "J5" H 8029 1542 50  0000 L CNN
F 1 "SPI2_A" H 8029 1451 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B06B-XH-A_06x2.50mm_Straight_LargePads" H 7950 1550 50  0001 C CNN
F 3 "~" H 7950 1550 50  0001 C CNN
	1    7950 1550
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x06 J10
U 1 1 5A87305D
P 8350 1550
F 0 "J10" H 8430 1542 50  0000 L CNN
F 1 "SPI2_B" H 8430 1451 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B06B-XH-A_06x2.50mm_Straight_LargePads" H 8350 1550 50  0001 C CNN
F 3 "~" H 8350 1550 50  0001 C CNN
	1    8350 1550
	1    0    0    -1  
$EndComp
Text GLabel 7750 1200 0    60   Input ~ 0
SPI2_CS_B
Wire Wire Line
	7750 1200 8150 1200
Wire Wire Line
	8150 1200 8150 1350
Wire Wire Line
	7750 1450 8150 1450
Wire Wire Line
	8150 1550 7750 1550
Wire Wire Line
	7750 1650 8150 1650
Wire Wire Line
	7750 1850 8150 1850
Wire Wire Line
	8150 1750 7750 1750
$Comp
L maxwell-rescue:ESP-32S-esp32 U5
U 1 1 5A881CB5
P 9400 3500
F 0 "U5" V 9322 4728 60  0000 L CNN
F 1 "ESP-32S" V 9428 4728 60  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:ESP-32S" H 9750 4850 60  0001 C CNN
F 3 "" H 8950 3950 60  0001 C CNN
	1    9400 3500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR06
U 1 1 5A881E1F
P 7800 2900
F 0 "#PWR06" H 7800 2750 50  0001 C CNN
F 1 "+3V3" V 7815 3028 50  0000 L CNN
F 2 "" H 7800 2900 50  0001 C CNN
F 3 "" H 7800 2900 50  0001 C CNN
	1    7800 2900
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R6
U 1 1 5A885158
P 8050 3000
F 0 "R6" H 8120 3046 50  0000 L CNN
F 1 "10k" H 8120 2955 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 7980 3000 50  0001 C CNN
F 3 "" H 8050 3000 50  0001 C CNN
	1    8050 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	8450 2900 7900 2900
Wire Wire Line
	8450 3000 8250 3000
Wire Wire Line
	7900 3000 7850 3000
Wire Wire Line
	7850 3000 7850 2900
Connection ~ 7850 2900
Wire Wire Line
	7850 2900 7800 2900
Text GLabel 7850 3150 0    60   Input ~ 0
~DISABLE_ESP
Wire Wire Line
	7850 3150 8250 3150
Wire Wire Line
	8250 3150 8250 3000
Connection ~ 8250 3000
Wire Wire Line
	8250 3000 8200 3000
Text GLabel 10350 4150 2    60   Input ~ 0
ESP_BOOT_MODE
Wire Wire Line
	10300 4150 10350 4150
Text GLabel 10300 3150 2    60   Output ~ 0
ESP_DO
Text GLabel 10300 3250 2    60   Input ~ 0
ESP_DI
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR029
U 1 1 5A8994F7
P 2350 2050
F 0 "#PWR029" H 2350 1800 50  0001 C CNN
F 1 "GND" H 2355 1877 50  0000 C CNN
F 2 "" H 2350 2050 50  0001 C CNN
F 3 "" H 2350 2050 50  0001 C CNN
	1    2350 2050
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:+BACKUP-power #PWR060
U 1 1 5A89B5E8
P 2350 2150
F 0 "#PWR060" H 2350 2000 50  0001 C CNN
F 1 "+BACKUP" H 2365 2323 50  0000 C CNN
F 2 "" H 2350 2150 50  0001 C CNN
F 3 "" H 2350 2150 50  0001 C CNN
	1    2350 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3350 4200 3600 4200
$Comp
L conn:Conn_01x02 J11
U 1 1 5A8ACC4B
P 2550 2050
F 0 "J11" H 2630 2042 50  0000 L CNN
F 1 "BACKUP" H 2630 1951 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 2550 2050 50  0001 C CNN
F 3 "~" H 2550 2050 50  0001 C CNN
	1    2550 2050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR058
U 1 1 5A8AF340
P 7750 1850
F 0 "#PWR058" H 7750 1600 50  0001 C CNN
F 1 "GND" H 7755 1677 50  0000 C CNN
F 2 "" H 7750 1850 50  0001 C CNN
F 3 "" H 7750 1850 50  0001 C CNN
	1    7750 1850
	0    1    1    0   
$EndComp
Connection ~ 7750 1850
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR062
U 1 1 5A8AF3C3
P 8400 2800
F 0 "#PWR062" H 8400 2550 50  0001 C CNN
F 1 "GND" H 8405 2627 50  0000 C CNN
F 2 "" H 8400 2800 50  0001 C CNN
F 3 "" H 8400 2800 50  0001 C CNN
	1    8400 2800
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR063
U 1 1 5A8AF40A
P 10300 2750
F 0 "#PWR063" H 10300 2500 50  0001 C CNN
F 1 "GND" H 10305 2577 50  0000 C CNN
F 2 "" H 10300 2750 50  0001 C CNN
F 3 "" H 10300 2750 50  0001 C CNN
	1    10300 2750
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR064
U 1 1 5A8AF48D
P 10300 2850
F 0 "#PWR064" H 10300 2600 50  0001 C CNN
F 1 "GND" H 10305 2677 50  0000 C CNN
F 2 "" H 10300 2850 50  0001 C CNN
F 3 "" H 10300 2850 50  0001 C CNN
	1    10300 2850
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR065
U 1 1 5A8AF4D4
P 8950 4550
F 0 "#PWR065" H 8950 4300 50  0001 C CNN
F 1 "GND" H 8955 4377 50  0000 C CNN
F 2 "" H 8950 4550 50  0001 C CNN
F 3 "" H 8950 4550 50  0001 C CNN
	1    8950 4550
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x04 J12
U 1 1 5A8B4267
P 4450 5700
F 0 "J12" H 4530 5692 50  0000 L CNN
F 1 "UART4" H 4530 5601 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B04B-XH-A_04x2.50mm_Straight_LargePads" H 4450 5700 50  0001 C CNN
F 3 "~" H 4450 5700 50  0001 C CNN
	1    4450 5700
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x04 J13
U 1 1 5A8B42C9
P 4450 6200
F 0 "J13" H 4530 6192 50  0000 L CNN
F 1 "UART5" H 4530 6101 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B04B-XH-A_04x2.50mm_Straight_LargePads" H 4450 6200 50  0001 C CNN
F 3 "~" H 4450 6200 50  0001 C CNN
	1    4450 6200
	1    0    0    -1  
$EndComp
Text GLabel 4250 5900 0    60   Input ~ 0
UART4_TX
Text GLabel 4250 6400 0    60   Input ~ 0
UART5_TX
Text GLabel 4250 6300 0    60   Output ~ 0
UART5_RX
Text GLabel 4250 5800 0    60   Output ~ 0
UART4_RX
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR015
U 1 1 5A8B4870
P 4250 6100
F 0 "#PWR015" H 4250 5850 50  0001 C CNN
F 1 "GND" H 4255 5927 50  0000 C CNN
F 2 "" H 4250 6100 50  0001 C CNN
F 3 "" H 4250 6100 50  0001 C CNN
	1    4250 6100
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR066
U 1 1 5A8B48D8
P 4250 5600
F 0 "#PWR066" H 4250 5350 50  0001 C CNN
F 1 "GND" H 4255 5427 50  0000 C CNN
F 2 "" H 4250 5600 50  0001 C CNN
F 3 "" H 4250 5600 50  0001 C CNN
	1    4250 5600
	0    1    1    0   
$EndComp
Text GLabel 5350 5950 0    60   BiDi ~ 0
I2C1_SDA
Text GLabel 5350 5850 0    60   BiDi ~ 0
I2C1_SCL
$Comp
L conn:Conn_01x04 J14
U 1 1 5A8B5837
P 5800 5750
F 0 "J14" H 5880 5742 50  0000 L CNN
F 1 "I2C1" H 5880 5651 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B04B-XH-A_04x2.50mm_Straight_LargePads" H 5800 5750 50  0001 C CNN
F 3 "~" H 5800 5750 50  0001 C CNN
	1    5800 5750
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR071
U 1 1 5A8B596F
P 5600 5650
F 0 "#PWR071" H 5600 5400 50  0001 C CNN
F 1 "GND" H 5605 5477 50  0000 C CNN
F 2 "" H 5600 5650 50  0001 C CNN
F 3 "" H 5600 5650 50  0001 C CNN
	1    5600 5650
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R2
U 1 1 5A8B5F63
P 5400 6150
F 0 "R2" V 5193 6150 50  0000 C CNN
F 1 "2.2k" V 5284 6150 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5330 6150 50  0001 C CNN
F 3 "" H 5400 6150 50  0001 C CNN
	1    5400 6150
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R16
U 1 1 5A8B5FC6
P 5550 6150
F 0 "R16" V 5343 6150 50  0000 C CNN
F 1 "2.2k" V 5434 6150 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5480 6150 50  0001 C CNN
F 3 "" H 5550 6150 50  0001 C CNN
	1    5550 6150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5600 5850 5400 5850
Wire Wire Line
	5600 5950 5550 5950
Wire Wire Line
	5550 6000 5550 5950
Connection ~ 5550 5950
Wire Wire Line
	5550 5950 5350 5950
Wire Wire Line
	5550 6300 5550 6400
Wire Wire Line
	5550 6400 5400 6400
Wire Wire Line
	5400 6000 5400 5850
Connection ~ 5400 5850
Wire Wire Line
	5400 5850 5350 5850
Wire Wire Line
	5400 6300 5400 6400
Connection ~ 5400 6400
Wire Wire Line
	5400 6400 5350 6400
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR073
U 1 1 5A8C4083
P 5350 6400
F 0 "#PWR073" H 5350 6250 50  0001 C CNN
F 1 "+3V3" V 5365 6528 50  0000 L CNN
F 2 "" H 5350 6400 50  0001 C CNN
F 3 "" H 5350 6400 50  0001 C CNN
	1    5350 6400
	0    -1   -1   0   
$EndComp
NoConn ~ 8450 3100
NoConn ~ 8450 3200
NoConn ~ 8450 3300
NoConn ~ 8450 3400
NoConn ~ 8450 3500
NoConn ~ 8450 3600
NoConn ~ 8450 3700
NoConn ~ 8450 3800
NoConn ~ 8450 3900
NoConn ~ 8450 4000
NoConn ~ 8450 4100
NoConn ~ 10300 2950
NoConn ~ 10300 3050
NoConn ~ 10300 3350
NoConn ~ 10300 3450
NoConn ~ 10300 3550
NoConn ~ 10300 3650
NoConn ~ 10300 3750
NoConn ~ 9050 4550
NoConn ~ 9150 4550
NoConn ~ 9250 4550
NoConn ~ 9350 4550
NoConn ~ 9450 4550
NoConn ~ 9550 4550
NoConn ~ 9650 4550
NoConn ~ 1150 6050
$Comp
L power:VCC #PWR0101
U 1 1 5B32181C
P 3900 3800
F 0 "#PWR0101" H 3900 3650 50  0001 C CNN
F 1 "VCC" H 3917 3973 50  0000 C CNN
F 2 "" H 3900 3800 50  0001 C CNN
F 3 "" H 3900 3800 50  0001 C CNN
	1    3900 3800
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 5B321B92
P 1750 4650
F 0 "#PWR0102" H 1750 4500 50  0001 C CNN
F 1 "VCC" H 1768 4823 50  0000 C CNN
F 2 "" H 1750 4650 50  0001 C CNN
F 3 "" H 1750 4650 50  0001 C CNN
	1    1750 4650
	-1   0    0    1   
$EndComp
Text GLabel 10300 3850 2    60   Output ~ 0
N_RST
$Comp
L device:C C5
U 1 1 5B327200
P 7900 2750
F 0 "C5" H 8015 2796 50  0000 L CNN
F 1 "0.1u" H 8015 2705 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 7938 2600 50  0001 C CNN
F 3 "" H 7900 2750 50  0001 C CNN
	1    7900 2750
	1    0    0    -1  
$EndComp
Connection ~ 7900 2900
Wire Wire Line
	7900 2900 7850 2900
Wire Wire Line
	7900 2550 7900 2600
Wire Wire Line
	8450 2800 8450 2550
Wire Wire Line
	8450 2550 7900 2550
Wire Wire Line
	8400 2800 8450 2800
Connection ~ 8450 2800
$Comp
L power:VCC #PWR0104
U 1 1 5B331D2E
P 5600 5750
F 0 "#PWR0104" H 5600 5600 50  0001 C CNN
F 1 "VCC" V 5618 5877 50  0000 L CNN
F 2 "" H 5600 5750 50  0001 C CNN
F 3 "" H 5600 5750 50  0001 C CNN
	1    5600 5750
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR0105
U 1 1 5B331DD1
P 4250 5700
F 0 "#PWR0105" H 4250 5550 50  0001 C CNN
F 1 "VCC" V 4268 5827 50  0000 L CNN
F 2 "" H 4250 5700 50  0001 C CNN
F 3 "" H 4250 5700 50  0001 C CNN
	1    4250 5700
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR0106
U 1 1 5B331E16
P 4250 6200
F 0 "#PWR0106" H 4250 6050 50  0001 C CNN
F 1 "VCC" V 4268 6327 50  0000 L CNN
F 2 "" H 4250 6200 50  0001 C CNN
F 3 "" H 4250 6200 50  0001 C CNN
	1    4250 6200
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR0107
U 1 1 5B332287
P 2150 5850
F 0 "#PWR0107" H 2150 5700 50  0001 C CNN
F 1 "VCC" H 2167 6023 50  0000 C CNN
F 2 "" H 2150 5850 50  0001 C CNN
F 3 "" H 2150 5850 50  0001 C CNN
	1    2150 5850
	1    0    0    -1  
$EndComp
Connection ~ 2150 5850
Text GLabel 800  6200 3    60   Input ~ 0
CAN_DISABLE
Wire Wire Line
	1000 6150 800  6150
Wire Wire Line
	800  6150 800  6200
Connection ~ 1000 6150
$Comp
L power:VCC #PWR0108
U 1 1 5B33545B
P 7750 1450
F 0 "#PWR0108" H 7750 1300 50  0001 C CNN
F 1 "VCC" V 7768 1577 50  0000 L CNN
F 2 "" H 7750 1450 50  0001 C CNN
F 3 "" H 7750 1450 50  0001 C CNN
	1    7750 1450
	0    -1   -1   0   
$EndComp
Connection ~ 7750 1450
Text GLabel 5300 2200 3    60   Input ~ 0
ESP_BOOT_MODE
$Comp
L conn:Conn_01x02 J16
U 1 1 5B336731
P 5500 2100
F 0 "J16" H 5579 2092 50  0000 L CNN
F 1 "ESP_BM" H 5579 2001 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 5500 2100 50  0001 C CNN
F 3 "~" H 5500 2100 50  0001 C CNN
	1    5500 2100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0109
U 1 1 5B3368E4
P 5300 2100
F 0 "#PWR0109" H 5300 1850 50  0001 C CNN
F 1 "GND" H 5305 1927 50  0000 C CNN
F 2 "" H 5300 2100 50  0001 C CNN
F 3 "" H 5300 2100 50  0001 C CNN
	1    5300 2100
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:Conn_01x03-RESCUE-maxwell J17
U 1 1 5B336C11
P 6600 2200
F 0 "J17" H 6680 2242 50  0000 L CNN
F 1 "ESP_PROG" H 6680 2151 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 6600 2200 50  0001 C CNN
F 3 "" H 6600 2200 50  0001 C CNN
	1    6600 2200
	1    0    0    -1  
$EndComp
Text GLabel 6400 2200 0    60   Output ~ 0
ESP_DI
Text GLabel 6400 2100 0    60   Input ~ 0
ESP_DO
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR0110
U 1 1 5B336E2F
P 6400 2300
F 0 "#PWR0110" H 6400 2050 50  0001 C CNN
F 1 "GND" H 6405 2127 50  0000 C CNN
F 2 "" H 6400 2300 50  0001 C CNN
F 3 "" H 6400 2300 50  0001 C CNN
	1    6400 2300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
