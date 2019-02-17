EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
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
F 2 "coddingtonbear:Pin_Header_Straight_1x04_Pitch2.54mm_LargePads" H 2350 3400 50  0001 C CNN
F 3 "" H 2350 3400 50  0001 C CNN
	1    2350 3400
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
F 2 "coddingtonbear:0805_Milling" V 1330 3600 50  0001 C CNN
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
F 2 "coddingtonbear:0805_Milling" V 1330 3300 50  0001 C CNN
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
P 8000 4500
F 0 "U2" H 8000 4978 50  0000 C CNN
F 1 "SN65HVD233" H 8000 4887 50  0000 C CNN
F 2 "coddingtonbear:SOIC-8_3.9x4.9mm_P1.27mm_LargePads" H 8000 4000 50  0001 C CNN
F 3 "" H 7900 4900 50  0001 C CNN
	1    8000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3900 8000 4200
$Comp
L maxwell-rescue:R-RESCUE-maxwell R1
U 1 1 5A2285B9
P 7450 4850
F 0 "R1" H 7520 4896 50  0000 L CNN
F 1 "10k" H 7520 4805 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 7380 4850 50  0001 C CNN
F 3 "" H 7450 4850 50  0001 C CNN
	1    7450 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 4700 7450 4700
Wire Wire Line
	7450 5000 7450 5100
Wire Wire Line
	7450 5100 8000 5100
Wire Wire Line
	8400 4500 8500 4500
Wire Wire Line
	8400 4600 8450 4600
Wire Wire Line
	8800 4700 9000 4700
Wire Wire Line
	9000 4400 8600 4400
$Comp
L maxwell-rescue:C-RESCUE-maxwell C4
U 1 1 5A22B0AC
P 8150 3900
F 0 "C4" V 7898 3900 50  0000 C CNN
F 1 "0.1u" V 7989 3900 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 8188 3750 50  0001 C CNN
F 3 "" H 8150 3900 50  0001 C CNN
	1    8150 3900
	0    1    1    0   
$EndComp
Text GLabel 8150 2800 0    60   Input ~ 0
BT_DI
Text GLabel 8150 2700 0    60   Output ~ 0
BT_DO
Text GLabel 10000 2850 2    60   BiDi ~ 0
BOOT0
Text GLabel 10000 2750 2    60   Input ~ 0
BT_KEY
$Comp
L maxwell-rescue:Conn_01x03-RESCUE-maxwell J3
U 1 1 5A24A6D8
P 10650 5300
F 0 "J3" H 10730 5342 50  0000 L CNN
F 1 "Neopixel" H 10730 5251 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 10650 5300 50  0001 C CNN
F 3 "" H 10650 5300 50  0001 C CNN
	1    10650 5300
	0    -1   -1   0   
$EndComp
Text GLabel 10650 6000 3    60   Input ~ 0
NEOPIXEL
Wire Wire Line
	10750 5700 10750 5500
$Comp
L maxwell-rescue:Conn_01x05-RESCUE-maxwell J1
U 1 1 5A25E0A2
P 9200 4500
F 0 "J1" H 9280 4542 50  0000 L CNN
F 1 "Canbus 1" H 9280 4451 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B05B-XH-A_05x2.50mm_Straight_LargePads" H 9200 4500 50  0001 C CNN
F 3 "" H 9200 4500 50  0001 C CNN
	1    9200 4500
	1    0    0    -1  
$EndComp
Text GLabel 4600 3100 0    60   BiDi ~ 0
WAKE_B
Wire Wire Line
	9000 4300 8900 4300
Text Label 8450 4500 0    60   ~ 0
CAN+
Text Label 8450 4600 0    60   ~ 0
CAN-
$Comp
L maxwell-rescue:R-RESCUE-maxwell R31
U 1 1 5A271748
P 10650 5850
F 0 "R31" H 10720 5896 50  0000 L CNN
F 1 "330" H 10720 5805 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 10580 5850 50  0001 C CNN
F 3 "" H 10650 5850 50  0001 C CNN
	1    10650 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 5700 10650 5500
$Comp
L maxwell-rescue:R-RESCUE-maxwell R37
U 1 1 5A2B653B
P 8450 5150
F 0 "R37" H 8520 5196 50  0000 L CNN
F 1 "120" H 8520 5105 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 8380 5150 50  0001 C CNN
F 3 "" H 8450 5150 50  0001 C CNN
	1    8450 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4600 8450 5000
Connection ~ 8450 4600
Wire Wire Line
	8500 4500 8500 5300
Wire Wire Line
	8500 5300 8450 5300
Connection ~ 8500 4500
Wire Wire Line
	1600 3600 2150 3600
Wire Wire Line
	1250 3500 2150 3500
Wire Wire Line
	8000 5100 8000 4900
Wire Wire Line
	1550 3300 1600 3300
Wire Wire Line
	1600 3250 1600 3300
Connection ~ 1600 3300
Wire Wire Line
	1600 3300 2150 3300
Text GLabel 7600 4400 0    60   Input ~ 0
CAN_TX
Text GLabel 7600 4500 0    60   Output ~ 0
CAN_RX
Connection ~ 8000 5100
Wire Wire Line
	8000 5900 8000 5100
$Comp
L maxwell-rescue:Conn_01x02-conn J4
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
L maxwell-rescue:Conn_01x02-conn J8
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
L maxwell-rescue:R-RESCUE-maxwell R5
U 1 1 5A8A1E56
P 3050 1400
F 0 "R5" H 3120 1446 50  0000 L CNN
F 1 "100k" H 3120 1355 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 2980 1400 50  0001 C CNN
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
F 2 "coddingtonbear:0805_Milling" V 2980 2650 50  0001 C CNN
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
Text GLabel 5350 5300 0    60   Input ~ 0
SPI2_CS_A
Text GLabel 5350 5700 0    60   Input ~ 0
SPI2_MOSI
Text GLabel 5350 5500 0    60   Input ~ 0
SPI2_SCK
Text GLabel 5350 5600 0    60   Output ~ 0
SPI2_MISO
$Comp
L maxwell-rescue:Conn_01x06-conn J5
U 1 1 5A872F71
P 5550 5500
F 0 "J5" H 5629 5492 50  0000 L CNN
F 1 "SPI2_A" H 5629 5401 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B06B-XH-A_06x2.50mm_Straight_LargePads" H 5550 5500 50  0001 C CNN
F 3 "~" H 5550 5500 50  0001 C CNN
	1    5550 5500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x06-conn J10
U 1 1 5A87305D
P 5950 5500
F 0 "J10" H 6030 5492 50  0000 L CNN
F 1 "SPI2_B" H 6030 5401 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B06B-XH-A_06x2.50mm_Straight_LargePads" H 5950 5500 50  0001 C CNN
F 3 "~" H 5950 5500 50  0001 C CNN
	1    5950 5500
	1    0    0    -1  
$EndComp
Text GLabel 5350 5150 0    60   Input ~ 0
SPI2_CS_B
Wire Wire Line
	5350 5150 5750 5150
Wire Wire Line
	5750 5150 5750 5300
Wire Wire Line
	5350 5400 5750 5400
Wire Wire Line
	5750 5500 5350 5500
Wire Wire Line
	5350 5600 5750 5600
Wire Wire Line
	5350 5800 5750 5800
Wire Wire Line
	5750 5700 5350 5700
$Comp
L maxwell-rescue:ESP-32S-esp32 U5
U 1 1 5A881CB5
P 9100 2300
F 0 "U5" V 9022 3528 60  0000 L CNN
F 1 "ESP-32S" V 9128 3528 60  0000 L CNN
F 2 "coddingtonbear:ESP-32S" H 9450 3650 60  0001 C CNN
F 3 "" H 8650 2750 60  0001 C CNN
	1    9100 2300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R6
U 1 1 5A885158
P 7750 1800
F 0 "R6" H 7820 1846 50  0000 L CNN
F 1 "10k" H 7820 1755 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 7680 1800 50  0001 C CNN
F 3 "" H 7750 1800 50  0001 C CNN
	1    7750 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 1700 7600 1700
Wire Wire Line
	8150 1800 7950 1800
Wire Wire Line
	7600 1800 7550 1800
Wire Wire Line
	7550 1800 7550 1700
Connection ~ 7550 1700
Text GLabel 7550 1950 0    60   Input ~ 0
~DISABLE_ESP
Wire Wire Line
	7550 1950 7950 1950
Wire Wire Line
	7950 1950 7950 1800
Connection ~ 7950 1800
Wire Wire Line
	7950 1800 7900 1800
Text GLabel 10050 2950 2    60   Input ~ 0
ESP_BOOT_MODE
Wire Wire Line
	10000 2950 10050 2950
Text GLabel 10000 1950 2    60   Output ~ 0
ESP_DO
Text GLabel 10000 2050 2    60   Input ~ 0
ESP_DI
$Comp
L maxwell-rescue:+BACKUP-power #PWR060
U 1 1 5A89B5E8
P 2400 1800
F 0 "#PWR060" H 2400 1650 50  0001 C CNN
F 1 "+BACKUP" H 2415 1973 50  0000 C CNN
F 2 "" H 2400 1800 50  0001 C CNN
F 3 "" H 2400 1800 50  0001 C CNN
	1    2400 1800
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x02-conn J11
U 1 1 5A8ACC4B
P 2500 2000
F 0 "J11" H 2580 1992 50  0000 L CNN
F 1 "BACKUP" H 2580 1901 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 2500 2000 50  0001 C CNN
F 3 "~" H 2500 2000 50  0001 C CNN
	1    2500 2000
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:Conn_01x04-conn J12
U 1 1 5A8B4267
P 1550 5550
F 0 "J12" H 1630 5542 50  0000 L CNN
F 1 "UART4" H 1630 5451 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B04B-XH-A_04x2.50mm_Straight_LargePads" H 1550 5550 50  0001 C CNN
F 3 "~" H 1550 5550 50  0001 C CNN
	1    1550 5550
	0    1    1    0   
$EndComp
Text GLabel 1350 5350 1    60   Input ~ 0
UART4_TX
Text GLabel 1450 5350 1    60   Output ~ 0
UART4_RX
NoConn ~ 8150 1900
NoConn ~ 8150 2000
NoConn ~ 8150 2100
NoConn ~ 8150 2200
NoConn ~ 8150 2300
NoConn ~ 8150 2400
NoConn ~ 8150 2500
NoConn ~ 8150 2600
NoConn ~ 8150 2900
NoConn ~ 10000 1750
NoConn ~ 10000 1850
NoConn ~ 10000 2150
NoConn ~ 10000 2250
NoConn ~ 10000 2350
NoConn ~ 10000 2450
NoConn ~ 10000 2550
NoConn ~ 8750 3350
NoConn ~ 8850 3350
NoConn ~ 8950 3350
NoConn ~ 9050 3350
NoConn ~ 9150 3350
NoConn ~ 9250 3350
NoConn ~ 9350 3350
NoConn ~ 7600 4600
Text GLabel 10000 2650 2    60   Output ~ 0
N_RST
$Comp
L maxwell-rescue:C-device C5
U 1 1 5B327200
P 7600 1550
F 0 "C5" H 7715 1596 50  0000 L CNN
F 1 "0.1u" H 7715 1505 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 7638 1400 50  0001 C CNN
F 3 "" H 7600 1550 50  0001 C CNN
	1    7600 1550
	1    0    0    -1  
$EndComp
Connection ~ 7600 1700
Wire Wire Line
	7600 1700 7550 1700
Wire Wire Line
	7600 1350 7600 1400
Wire Wire Line
	8150 1600 8150 1350
Wire Wire Line
	8150 1350 7950 1350
Text GLabel 4250 1050 3    60   Input ~ 0
ESP_BOOT_MODE
$Comp
L maxwell-rescue:Conn_01x02-conn J16
U 1 1 5B336731
P 4450 950
F 0 "J16" H 4529 942 50  0000 L CNN
F 1 "ESP_BM" H 4529 851 50  0000 L CNN
F 2 "coddingtonbear:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 4450 950 50  0001 C CNN
F 3 "~" H 4450 950 50  0001 C CNN
	1    4450 950 
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x03-RESCUE-maxwell J17
U 1 1 5B336C11
P 5550 1050
F 0 "J17" H 5630 1092 50  0000 L CNN
F 1 "ESP_PROG" H 5630 1001 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 5550 1050 50  0001 C CNN
F 3 "" H 5550 1050 50  0001 C CNN
	1    5550 1050
	1    0    0    -1  
$EndComp
Text GLabel 5350 1050 0    60   Output ~ 0
ESP_DI
Text GLabel 5350 950  0    60   Input ~ 0
ESP_DO
Wire Wire Line
	5850 2200 6050 2200
Wire Wire Line
	6050 2200 6050 2100
Wire Wire Line
	5850 1900 6050 1900
Wire Wire Line
	5850 2000 6050 2000
Connection ~ 6050 2000
Wire Wire Line
	6050 2000 6050 1900
Wire Wire Line
	5850 2100 6050 2100
Connection ~ 6050 2100
Wire Wire Line
	6050 2100 6050 2000
Wire Wire Line
	5850 2300 6050 2300
Wire Wire Line
	6050 2300 6050 2400
Wire Wire Line
	5850 2500 6050 2500
Wire Wire Line
	5850 2400 6050 2400
Connection ~ 6050 2400
Wire Wire Line
	6050 2400 6050 2500
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J20
U 1 1 5BECFFAD
P 5550 2200
F 0 "J20" H 5600 2717 50  0000 C CNN
F 1 "Interconnect (uC)" H 5600 2626 50  0000 C CNN
F 2 "coddingtonbear:IDC-Header_2x08_P2.54mm_Vertical_Largepads" H 5550 2200 50  0001 C CNN
F 3 "~" H 5550 2200 50  0001 C CNN
	1    5550 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4500 9000 4500
Wire Wire Line
	8450 4600 9000 4600
Text GLabel 5850 2600 2    60   BiDi ~ 0
I2C1_SCL_B
Text GLabel 5350 2600 0    60   BiDi ~ 0
I2C1_SDA_B
Wire Wire Line
	5350 2000 5050 2000
Wire Wire Line
	5050 2000 5050 1900
Wire Wire Line
	5350 2100 5050 2100
Wire Wire Line
	5050 2100 5050 2000
Connection ~ 5050 2000
Wire Wire Line
	5350 2200 5050 2200
Wire Wire Line
	5050 2200 5050 2100
Connection ~ 5050 2100
Wire Wire Line
	5350 2400 5350 2300
Connection ~ 5350 2300
NoConn ~ 9450 3350
NoConn ~ 9550 3350
$Comp
L maxwell-rescue:Conn_01x06-conn J2
U 1 1 5BFB23A5
P 6350 5500
F 0 "J2" H 6430 5492 50  0000 L CNN
F 1 "SPI2_C" H 6430 5401 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B06B-XH-A_06x2.50mm_Straight_LargePads" H 6350 5500 50  0001 C CNN
F 3 "~" H 6350 5500 50  0001 C CNN
	1    6350 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5400 6150 5400
Connection ~ 5750 5400
Wire Wire Line
	6150 5500 5750 5500
Connection ~ 5750 5500
Wire Wire Line
	5750 5600 6150 5600
Connection ~ 5750 5600
Wire Wire Line
	6150 5700 5750 5700
Connection ~ 5750 5700
Wire Wire Line
	5750 5800 6150 5800
Connection ~ 5750 5800
Text GLabel 5350 5000 0    60   Input ~ 0
SPI2_CS_C
Wire Wire Line
	6150 5300 6150 5000
Wire Wire Line
	6150 5000 5350 5000
Text GLabel 9350 6050 0    60   Input ~ 0
ENABLE_LEDS
$Comp
L coddingtonbear:VCC_B #PWR0101
U 1 1 5C93E182
P 6050 1900
F 0 "#PWR0101" H 6050 1750 50  0001 C CNN
F 1 "VCC_B" H 6067 2073 50  0000 C CNN
F 2 "" H 6050 1900 50  0001 C CNN
F 3 "" H 6050 1900 50  0001 C CNN
	1    6050 1900
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_B #PWR0102
U 1 1 5C93E250
P 5050 1900
F 0 "#PWR0102" H 5050 1750 50  0001 C CNN
F 1 "+3V3_B" H 5065 2073 50  0000 C CNN
F 2 "" H 5050 1900 50  0001 C CNN
F 3 "" H 5050 1900 50  0001 C CNN
	1    5050 1900
	1    0    0    -1  
$EndComp
Connection ~ 6050 1900
Connection ~ 5050 1900
$Comp
L coddingtonbear:GND_B #PWR0103
U 1 1 5C93E4C2
P 4350 2450
F 0 "#PWR0103" H 4350 2200 50  0001 C CNN
F 1 "GND_B" H 4355 2277 50  0000 C CNN
F 2 "" H 4350 2450 50  0001 C CNN
F 3 "" H 4350 2450 50  0001 C CNN
	1    4350 2450
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0104
U 1 1 5C93E588
P 6650 2400
F 0 "#PWR0104" H 6650 2150 50  0001 C CNN
F 1 "GND_B" H 6655 2227 50  0000 C CNN
F 2 "" H 6650 2400 50  0001 C CNN
F 3 "" H 6650 2400 50  0001 C CNN
	1    6650 2400
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0105
U 1 1 5C6AFBA6
P 2650 1800
F 0 "#PWR0105" H 2650 1550 50  0001 C CNN
F 1 "GND_B" H 2655 1627 50  0000 C CNN
F 2 "" H 2650 1800 50  0001 C CNN
F 3 "" H 2650 1800 50  0001 C CNN
	1    2650 1800
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0106
U 1 1 5C6AFC8F
P 3050 1550
F 0 "#PWR0106" H 3050 1300 50  0001 C CNN
F 1 "GND_B" H 3055 1377 50  0000 C CNN
F 2 "" H 3050 1550 50  0001 C CNN
F 3 "" H 3050 1550 50  0001 C CNN
	1    3050 1550
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0107
U 1 1 5C6AFD24
P 3050 2800
F 0 "#PWR0107" H 3050 2550 50  0001 C CNN
F 1 "GND_B" H 3055 2627 50  0000 C CNN
F 2 "" H 3050 2800 50  0001 C CNN
F 3 "" H 3050 2800 50  0001 C CNN
	1    3050 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1800 2650 1800
$Comp
L coddingtonbear:GND_B #PWR0108
U 1 1 5C6B48D1
P 4050 950
F 0 "#PWR0108" H 4050 700 50  0001 C CNN
F 1 "GND_B" H 4055 777 50  0000 C CNN
F 2 "" H 4050 950 50  0001 C CNN
F 3 "" H 4050 950 50  0001 C CNN
	1    4050 950 
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0109
U 1 1 5C6B4943
P 5350 1150
F 0 "#PWR0109" H 5350 900 50  0001 C CNN
F 1 "GND_B" H 5355 977 50  0000 C CNN
F 2 "" H 5350 1150 50  0001 C CNN
F 3 "" H 5350 1150 50  0001 C CNN
	1    5350 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 950  4050 950 
$Comp
L coddingtonbear:GND_B #PWR0110
U 1 1 5C6B9740
P 1600 3650
F 0 "#PWR0110" H 1600 3400 50  0001 C CNN
F 1 "GND_B" H 1605 3477 50  0000 C CNN
F 2 "" H 1600 3650 50  0001 C CNN
F 3 "" H 1600 3650 50  0001 C CNN
	1    1600 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 5700 10950 5700
$Comp
L coddingtonbear:GND_B #PWR0113
U 1 1 5C6CD33D
P 8800 4700
F 0 "#PWR0113" H 8800 4450 50  0001 C CNN
F 1 "GND_B" H 8805 4527 50  0000 C CNN
F 2 "" H 8800 4700 50  0001 C CNN
F 3 "" H 8800 4700 50  0001 C CNN
	1    8800 4700
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0114
U 1 1 5C6CD568
P 8000 5900
F 0 "#PWR0114" H 8000 5650 50  0001 C CNN
F 1 "GND_B" H 8005 5727 50  0000 C CNN
F 2 "" H 8000 5900 50  0001 C CNN
F 3 "" H 8000 5900 50  0001 C CNN
	1    8000 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 5350 1650 5300
Wire Wire Line
	1650 5300 1850 5300
$Comp
L coddingtonbear:GND_B #PWR0117
U 1 1 5C73ADED
P 10000 6250
F 0 "#PWR0117" H 10000 6000 50  0001 C CNN
F 1 "GND_B" H 10005 6077 50  0000 C CNN
F 2 "" H 10000 6250 50  0001 C CNN
F 3 "" H 10000 6250 50  0001 C CNN
	1    10000 6250
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0118
U 1 1 5C73E46A
P 8650 3350
F 0 "#PWR0118" H 8650 3100 50  0001 C CNN
F 1 "GND_B" H 8655 3177 50  0000 C CNN
F 2 "" H 8650 3350 50  0001 C CNN
F 3 "" H 8650 3350 50  0001 C CNN
	1    8650 3350
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0119
U 1 1 5C73EE46
P 7950 1350
F 0 "#PWR0119" H 7950 1100 50  0001 C CNN
F 1 "GND_B" H 7955 1177 50  0000 C CNN
F 2 "" H 7950 1350 50  0001 C CNN
F 3 "" H 7950 1350 50  0001 C CNN
	1    7950 1350
	1    0    0    -1  
$EndComp
Connection ~ 7950 1350
Wire Wire Line
	7950 1350 7600 1350
$Comp
L coddingtonbear:GND_B #PWR0120
U 1 1 5C73EFF8
P 5300 6800
F 0 "#PWR0120" H 5300 6550 50  0001 C CNN
F 1 "GND_B" H 5305 6627 50  0000 C CNN
F 2 "" H 5300 6800 50  0001 C CNN
F 3 "" H 5300 6800 50  0001 C CNN
	1    5300 6800
	1    0    0    -1  
$EndComp
Connection ~ 5350 5800
$Comp
L coddingtonbear:VCC_B #PWR0122
U 1 1 5C73FEB7
P 8600 4400
F 0 "#PWR0122" H 8600 4250 50  0001 C CNN
F 1 "VCC_B" H 8617 4573 50  0000 C CNN
F 2 "" H 8600 4400 50  0001 C CNN
F 3 "" H 8600 4400 50  0001 C CNN
	1    8600 4400
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:VCC_B #PWR0123
U 1 1 5C73FF81
P 1550 5350
F 0 "#PWR0123" H 1550 5200 50  0001 C CNN
F 1 "VCC_B" H 1567 5523 50  0000 C CNN
F 2 "" H 1550 5350 50  0001 C CNN
F 3 "" H 1550 5350 50  0001 C CNN
	1    1550 5350
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:VCC_B #PWR0127
U 1 1 5C740834
P 10950 5700
F 0 "#PWR0127" H 10950 5550 50  0001 C CNN
F 1 "VCC_B" H 10967 5873 50  0000 C CNN
F 2 "" H 10950 5700 50  0001 C CNN
F 3 "" H 10950 5700 50  0001 C CNN
	1    10950 5700
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:VCC_B #PWR0128
U 1 1 5C741647
P 4600 5350
F 0 "#PWR0128" H 4600 5200 50  0001 C CNN
F 1 "VCC_B" H 4617 5523 50  0000 C CNN
F 2 "" H 4600 5350 50  0001 C CNN
F 3 "" H 4600 5350 50  0001 C CNN
	1    4600 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5400 4600 5400
Wire Wire Line
	4600 5400 4600 5350
Connection ~ 5350 5400
$Comp
L coddingtonbear:+3V3_B #PWR0129
U 1 1 5C744F52
P 7200 1700
F 0 "#PWR0129" H 7200 1550 50  0001 C CNN
F 1 "+3V3_B" H 7215 1873 50  0000 C CNN
F 2 "" H 7200 1700 50  0001 C CNN
F 3 "" H 7200 1700 50  0001 C CNN
	1    7200 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1700 7550 1700
$Comp
L coddingtonbear:+3V3_B #PWR0130
U 1 1 5C74860F
P 7800 3900
F 0 "#PWR0130" H 7800 3750 50  0001 C CNN
F 1 "+3V3_B" H 7815 4073 50  0000 C CNN
F 2 "" H 7800 3900 50  0001 C CNN
F 3 "" H 7800 3900 50  0001 C CNN
	1    7800 3900
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_B #PWR0131
U 1 1 5C748770
P 1600 3250
F 0 "#PWR0131" H 1600 3100 50  0001 C CNN
F 1 "+3V3_B" H 1615 3423 50  0000 C CNN
F 2 "" H 1600 3250 50  0001 C CNN
F 3 "" H 1600 3250 50  0001 C CNN
	1    1600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3900 7800 3900
Connection ~ 8000 3900
$Comp
L coddingtonbear:+3V3_B #PWR0132
U 1 1 5C74BCEB
P 3050 2300
F 0 "#PWR0132" H 3050 2150 50  0001 C CNN
F 1 "+3V3_B" H 3065 2473 50  0000 C CNN
F 2 "" H 3050 2300 50  0001 C CNN
F 3 "" H 3050 2300 50  0001 C CNN
	1    3050 2300
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_B #PWR0133
U 1 1 5C74BDE7
P 3050 1050
F 0 "#PWR0133" H 3050 900 50  0001 C CNN
F 1 "+3V3_B" H 3065 1223 50  0000 C CNN
F 2 "" H 3050 1050 50  0001 C CNN
F 3 "" H 3050 1050 50  0001 C CNN
	1    3050 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5350 3400 5300
Wire Wire Line
	3500 5350 3400 5350
Wire Wire Line
	3950 5350 3950 5300
Wire Wire Line
	3800 5350 3950 5350
Connection ~ 3400 5350
Wire Wire Line
	3400 5500 3400 5350
Wire Wire Line
	3500 5500 3400 5500
Wire Wire Line
	3850 5500 3850 5300
Wire Wire Line
	3800 5500 3850 5500
Connection ~ 3850 5500
Wire Wire Line
	3850 5550 3850 5500
Connection ~ 3950 5350
Wire Wire Line
	3950 5550 3950 5350
$Comp
L maxwell-rescue:R-RESCUE-maxwell R16
U 1 1 5C7602D5
P 3650 5500
AR Path="/5C7602D5" Ref="R16"  Part="1" 
AR Path="/5A1FEBCF/5C7602D5" Ref="R?"  Part="1" 
F 0 "R16" V 3443 5500 50  0000 C CNN
F 1 "2.2k" V 3534 5500 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 3580 5500 50  0001 C CNN
F 3 "" H 3650 5500 50  0001 C CNN
	1    3650 5500
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R2
U 1 1 5C7602DC
P 3650 5350
AR Path="/5C7602DC" Ref="R2"  Part="1" 
AR Path="/5A1FEBCF/5C7602DC" Ref="R?"  Part="1" 
F 0 "R2" V 3443 5350 50  0000 C CNN
F 1 "2.2k" V 3534 5350 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 3580 5350 50  0001 C CNN
F 3 "" H 3650 5350 50  0001 C CNN
	1    3650 5350
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:Conn_01x04-conn J15
U 1 1 5C7602E9
P 4050 5750
AR Path="/5C7602E9" Ref="J15"  Part="1" 
AR Path="/5A1FEBCF/5C7602E9" Ref="J?"  Part="1" 
F 0 "J15" H 4130 5742 50  0000 L CNN
F 1 "I2C1" H 4130 5651 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B04B-XH-A_04x2.50mm_Straight_LargePads" H 4050 5750 50  0001 C CNN
F 3 "~" H 4050 5750 50  0001 C CNN
	1    4050 5750
	0    1    1    0   
$EndComp
Text GLabel 3950 5300 1    60   BiDi ~ 0
I2C1_SCL_B
Text GLabel 3850 5300 1    60   BiDi ~ 0
I2C1_SDA_B
$Comp
L coddingtonbear:VCC_B #PWR0179
U 1 1 5C763E45
P 4050 5550
F 0 "#PWR0179" H 4050 5400 50  0001 C CNN
F 1 "VCC_B" H 4067 5723 50  0000 C CNN
F 2 "" H 4050 5550 50  0001 C CNN
F 3 "" H 4050 5550 50  0001 C CNN
	1    4050 5550
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_B #PWR0180
U 1 1 5C763EB4
P 3400 5300
F 0 "#PWR0180" H 3400 5150 50  0001 C CNN
F 1 "+3V3_B" H 3415 5473 50  0000 C CNN
F 2 "" H 3400 5300 50  0001 C CNN
F 3 "" H 3400 5300 50  0001 C CNN
	1    3400 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 5550 4350 5550
$Comp
L coddingtonbear:GND_B #PWR0126
U 1 1 5C76927B
P 8300 3900
F 0 "#PWR0126" H 8300 3650 50  0001 C CNN
F 1 "GND_B" H 8305 3727 50  0000 C CNN
F 2 "" H 8300 3900 50  0001 C CNN
F 3 "" H 8300 3900 50  0001 C CNN
	1    8300 3900
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0111
U 1 1 5C7FA792
P 10400 1650
F 0 "#PWR0111" H 10400 1400 50  0001 C CNN
F 1 "GND_B" H 10405 1477 50  0000 C CNN
F 2 "" H 10400 1650 50  0001 C CNN
F 3 "" H 10400 1650 50  0001 C CNN
	1    10400 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1550 10150 1550
Wire Wire Line
	10400 1550 10400 1650
Wire Wire Line
	10000 1650 10150 1650
Wire Wire Line
	10150 1650 10150 1550
Connection ~ 10150 1550
Wire Wire Line
	10150 1550 10400 1550
$Comp
L Device:Q_NMOS_GSD Q2
U 1 1 5C91BF91
P 9900 6050
F 0 "Q2" H 10105 6096 50  0000 L CNN
F 1 "DMG2302UK" H 10105 6005 50  0000 L CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 10100 6150 50  0001 C CNN
F 3 "~" H 9900 6050 50  0001 C CNN
	1    9900 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 5850 10000 5500
Wire Wire Line
	10000 5500 10550 5500
$Comp
L Device:Q_NMOS_GSD Q1
U 1 1 5C92BC66
P 5400 6600
F 0 "Q1" H 5606 6646 50  0000 L CNN
F 1 "DMG2302UK" H 5606 6555 50  0000 L CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 5600 6700 50  0001 C CNN
F 3 "~" H 5400 6600 50  0001 C CNN
	1    5400 6600
	-1   0    0    -1  
$EndComp
Text GLabel 5850 6600 2    60   Input ~ 0
ENABLE_AUX
Wire Wire Line
	5300 5800 5350 5800
Wire Wire Line
	4350 5550 4350 6150
Wire Wire Line
	1850 5300 1850 5400
Wire Wire Line
	4350 2300 4350 2450
Wire Wire Line
	4350 2300 4650 2300
Wire Wire Line
	6050 2400 6650 2400
Wire Wire Line
	5350 2500 4600 2500
$Comp
L Timer:MCP7940N-xSN U9
U 1 1 5C989ADA
P 5850 4050
F 0 "U9" H 5600 3600 50  0000 C CNN
F 1 "MCP79411-I/SN" H 6300 3600 50  0000 C CNN
F 2 "coddingtonbear:SOIC-8_3.9x4.9mm_P1.27mm_LargePads" H 5850 4050 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf" H 5850 4050 50  0001 C CNN
	1    5850 4050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BACKUP-power #PWR0115
U 1 1 5C989C84
P 5950 3650
F 0 "#PWR0115" H 5950 3500 50  0001 C CNN
F 1 "+BACKUP" H 5965 3823 50  0000 C CNN
F 2 "" H 5950 3650 50  0001 C CNN
F 3 "" H 5950 3650 50  0001 C CNN
	1    5950 3650
	1    0    0    -1  
$EndComp
Text GLabel 5450 3850 0    60   BiDi ~ 0
I2C1_SCL_B
Text GLabel 5450 3950 0    60   BiDi ~ 0
I2C1_SDA_B
Text GLabel 9150 4000 2    60   BiDi ~ 0
WAKE_B_SIG
Text GLabel 9650 3750 2    60   BiDi ~ 0
WAKE_B
$Comp
L Device:D_Schottky D2
U 1 1 5C99A760
P 9400 3750
F 0 "D2" H 9400 3534 50  0000 C CNN
F 1 "MBR1020VL" H 9400 3625 50  0000 C CNN
F 2 "coddingtonbear:D_SOD-123_LargePads" H 9400 3750 50  0001 C CNN
F 3 "~" H 9400 3750 50  0001 C CNN
	1    9400 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	9550 3750 9650 3750
Wire Wire Line
	9250 3750 8900 3750
Wire Wire Line
	8900 3750 8900 4000
Wire Wire Line
	9150 4000 8900 4000
Connection ~ 8900 4000
$Comp
L coddingtonbear:GND_B #PWR0116
U 1 1 5C9AFDED
P 5850 4450
F 0 "#PWR0116" H 5850 4200 50  0001 C CNN
F 1 "GND_B" H 5855 4277 50  0000 C CNN
F 2 "" H 5850 4450 50  0001 C CNN
F 3 "" H 5850 4450 50  0001 C CNN
	1    5850 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4150 5450 4150
Wire Wire Line
	4600 2500 4600 4150
$Comp
L coddingtonbear:VCC_B #PWR0121
U 1 1 5C9B5EB8
P 5450 3600
F 0 "#PWR0121" H 5450 3450 50  0001 C CNN
F 1 "VCC_B" H 5467 3773 50  0000 C CNN
F 2 "" H 5450 3600 50  0001 C CNN
F 3 "" H 5450 3600 50  0001 C CNN
	1    5450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3650 5650 3650
Wire Wire Line
	5450 3650 5450 3600
$Comp
L maxwell-rescue:C-RESCUE-maxwell C?
U 1 1 5C9BEC65
P 7100 3900
AR Path="/5A1FA1FC/5C9BEC65" Ref="C?"  Part="1" 
AR Path="/5C9BEC65" Ref="C9"  Part="1" 
F 0 "C9" V 6848 3900 50  0000 C CNN
F 1 "22p" V 6939 3900 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 7138 3750 50  0001 C CNN
F 3 "" H 7100 3900 50  0001 C CNN
	1    7100 3900
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C?
U 1 1 5C9BEC6C
P 7100 3600
AR Path="/5A1FA1FC/5C9BEC6C" Ref="C?"  Part="1" 
AR Path="/5C9BEC6C" Ref="C8"  Part="1" 
F 0 "C8" V 6848 3600 50  0000 C CNN
F 1 "22p" V 6939 3600 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 7138 3450 50  0001 C CNN
F 3 "" H 7100 3600 50  0001 C CNN
	1    7100 3600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7250 3900 7250 3750
Wire Wire Line
	7450 3750 7250 3750
Connection ~ 7250 3750
Wire Wire Line
	6950 3900 6850 3900
Wire Wire Line
	7250 3750 7250 3600
$Comp
L maxwell-rescue:Crystal_GND23_Small-device Y?
U 1 1 5C9BEC7D
P 6850 3750
AR Path="/5A1FA1FC/5C9BEC7D" Ref="Y?"  Part="1" 
AR Path="/5C9BEC7D" Ref="Y1"  Part="1" 
F 0 "Y1" V 6804 3916 50  0000 L CNN
F 1 "32.768k" V 6895 3916 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_SeikoEpson_MC306-4Pin_8.0x3.2mm_HandSoldering" H 6850 3750 50  0001 C CNN
F 3 "" H 6850 3750 50  0001 C CNN
	1    6850 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6850 3850 6850 3900
Connection ~ 6850 3900
Wire Wire Line
	6850 3900 6600 3900
Wire Wire Line
	6850 3650 6850 3600
Connection ~ 6850 3600
Wire Wire Line
	6850 3600 6950 3600
NoConn ~ 6950 3750
NoConn ~ 6750 3750
$Comp
L coddingtonbear:GND_B #PWR?
U 1 1 5C9BEC8C
P 7450 3750
AR Path="/5A1FA1FC/5C9BEC8C" Ref="#PWR?"  Part="1" 
AR Path="/5C9BEC8C" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 7450 3500 50  0001 C CNN
F 1 "GND_B" H 7455 3577 50  0000 C CNN
F 2 "" H 7450 3750 50  0001 C CNN
F 3 "" H 7450 3750 50  0001 C CNN
	1    7450 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	6250 3600 6250 3950
Wire Wire Line
	6250 3600 6850 3600
Wire Wire Line
	6600 3900 6600 4150
Wire Wire Line
	6600 4150 6250 4150
Text Label 5300 6150 0    60   ~ 0
GNDAUX
$Comp
L Switch:SW_Push SW1
U 1 1 5CC42A83
P 10050 4350
F 0 "SW1" H 10050 4635 50  0000 C CNN
F 1 "SW_Push" H 10050 4544 50  0000 C CNN
F 2 "coddingtonbear:SMD_MINI_BLACK_TACTILE_SWITCH" H 10050 4550 50  0001 C CNN
F 3 "" H 10050 4550 50  0001 C CNN
	1    10050 4350
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_B #PWR0190
U 1 1 5CC42E7E
P 10500 4350
F 0 "#PWR0190" H 10500 4200 50  0001 C CNN
F 1 "+3V3_B" H 10515 4523 50  0000 C CNN
F 2 "" H 10500 4350 50  0001 C CNN
F 3 "" H 10500 4350 50  0001 C CNN
	1    10500 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 4350 10250 4350
Wire Wire Line
	8900 4000 8900 4150
$Comp
L maxwell-rescue:R-RESCUE-maxwell R32
U 1 1 5CC502FE
P 9550 4150
F 0 "R32" H 9620 4196 50  0000 L CNN
F 1 "10k" H 9620 4105 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 9480 4150 50  0001 C CNN
F 3 "" H 9550 4150 50  0001 C CNN
	1    9550 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	9400 4150 8900 4150
Connection ~ 8900 4150
Wire Wire Line
	8900 4150 8900 4300
Wire Wire Line
	9700 4150 9850 4150
Wire Wire Line
	9850 4150 9850 4350
$Comp
L maxwell-rescue:R-RESCUE-maxwell R35
U 1 1 5CC5EDC1
P 9400 6200
F 0 "R35" H 9470 6246 50  0000 L CNN
F 1 "10k" H 9470 6155 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 9330 6200 50  0001 C CNN
F 3 "" H 9400 6200 50  0001 C CNN
	1    9400 6200
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R34
U 1 1 5CC5EEEC
P 6000 6800
F 0 "R34" H 6070 6846 50  0000 L CNN
F 1 "10k" H 6070 6755 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 5930 6800 50  0001 C CNN
F 3 "" H 6000 6800 50  0001 C CNN
	1    6000 6800
	0    1    1    0   
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0191
U 1 1 5CC5EFAE
P 6350 6850
F 0 "#PWR0191" H 6350 6600 50  0001 C CNN
F 1 "GND_B" H 6355 6677 50  0000 C CNN
F 2 "" H 6350 6850 50  0001 C CNN
F 3 "" H 6350 6850 50  0001 C CNN
	1    6350 6850
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0192
U 1 1 5CC5F009
P 9050 6300
F 0 "#PWR0192" H 9050 6050 50  0001 C CNN
F 1 "GND_B" H 9055 6127 50  0000 C CNN
F 2 "" H 9050 6300 50  0001 C CNN
F 3 "" H 9050 6300 50  0001 C CNN
	1    9050 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 6050 9550 6050
Wire Wire Line
	9550 6200 9550 6050
Connection ~ 9550 6050
Wire Wire Line
	9550 6050 9700 6050
Wire Wire Line
	9250 6200 9050 6200
Wire Wire Line
	9050 6200 9050 6300
Wire Wire Line
	5600 6600 5700 6600
Wire Wire Line
	5700 6600 5700 6800
Wire Wire Line
	5700 6800 5850 6800
Connection ~ 5700 6600
Wire Wire Line
	5700 6600 5850 6600
Wire Wire Line
	6150 6800 6350 6800
Wire Wire Line
	6350 6800 6350 6850
$Comp
L maxwell-rescue:C-RESCUE-maxwell C30
U 1 1 5CD4E2AB
P 5650 3500
F 0 "C30" V 5398 3500 50  0000 C CNN
F 1 "0.1u" V 5489 3500 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 5688 3350 50  0001 C CNN
F 3 "" H 5650 3500 50  0001 C CNN
	1    5650 3500
	-1   0    0    1   
$EndComp
Connection ~ 5650 3650
Wire Wire Line
	5650 3650 5450 3650
$Comp
L coddingtonbear:GND_B #PWR0193
U 1 1 5CD4E36E
P 5150 3350
F 0 "#PWR0193" H 5150 3100 50  0001 C CNN
F 1 "GND_B" H 5155 3177 50  0000 C CNN
F 2 "" H 5150 3350 50  0001 C CNN
F 3 "" H 5150 3350 50  0001 C CNN
	1    5150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3350 5650 3250
Wire Wire Line
	5650 3250 5150 3250
Wire Wire Line
	5150 3250 5150 3350
Wire Wire Line
	5300 5800 5300 6150
$Comp
L coddingtonbear:GND_B #PWR0125
U 1 1 5CD61554
P 1850 5400
F 0 "#PWR0125" H 1850 5150 50  0001 C CNN
F 1 "GND_B" H 1855 5227 50  0000 C CNN
F 2 "" H 1850 5400 50  0001 C CNN
F 3 "" H 1850 5400 50  0001 C CNN
	1    1850 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C31
U 1 1 5CD6311A
P 4650 2150
F 0 "C31" H 4768 2196 50  0000 L CNN
F 1 "220u" H 4768 2105 50  0000 L CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 4688 2000 50  0001 C CNN
F 3 "~" H 4650 2150 50  0001 C CNN
	1    4650 2150
	1    0    0    -1  
$EndComp
Connection ~ 4650 2300
Wire Wire Line
	4650 2300 5350 2300
Wire Wire Line
	4650 2000 4650 1900
Wire Wire Line
	4650 1900 5050 1900
Connection ~ 5100 1900
Wire Wire Line
	5100 1900 5050 1900
Wire Wire Line
	4350 6150 5300 6150
Wire Wire Line
	5050 1900 5350 1900
Connection ~ 5300 6150
Wire Wire Line
	5300 6150 5300 6400
$EndSCHEMATC
