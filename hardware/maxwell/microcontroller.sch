EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L maxwell-rescue:STM32F103RETx-RESCUE-maxwell U7
U 1 1 5A1FCF5C
P 5700 3850
F 0 "U7" H 5700 6028 50  0000 C CNN
F 1 "STM32F103RETx" H 5700 5937 50  0000 C CNN
F 2 "castellated-breakouts:QFP64-1.27MM-CASTELLATED" H 8400 5725 50  0001 R TNN
F 3 "" H 5700 3850 50  0001 C CNN
	1    5700 3850
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Crystal-RESCUE-maxwell Y2
U 1 1 5A1FCF85
P 2450 3600
F 0 "Y2" V 2404 3731 50  0000 L CNN
F 1 "8M" V 2495 3731 50  0000 L CNN
F 2 "coddingtonbear:Abracon-ABM2_LargePads" H 2450 3600 50  0001 C CNN
F 3 "" H 2450 3600 50  0001 C CNN
	1    2450 3600
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C6
U 1 1 5A1FCF8C
P 2300 3450
F 0 "C6" V 2048 3450 50  0000 C CNN
F 1 "22p" V 2139 3450 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 2338 3300 50  0001 C CNN
F 3 "" H 2300 3450 50  0001 C CNN
	1    2300 3450
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C7
U 1 1 5A1FCF93
P 2300 3750
F 0 "C7" V 2048 3750 50  0000 C CNN
F 1 "22p" V 2139 3750 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 2338 3600 50  0001 C CNN
F 3 "" H 2300 3750 50  0001 C CNN
	1    2300 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 3450 2150 3600
Wire Wire Line
	1950 3650 1950 3600
Wire Wire Line
	1950 3600 2150 3600
Connection ~ 2150 3600
Wire Wire Line
	5500 5850 5500 6050
Wire Wire Line
	5500 6050 5600 6050
Wire Wire Line
	5600 5850 5600 6050
Connection ~ 5600 6050
Wire Wire Line
	5900 6050 5900 5850
Connection ~ 5700 6050
Wire Wire Line
	5800 5850 5800 6050
Connection ~ 5800 6050
Wire Wire Line
	5700 5850 5700 6050
Text GLabel 8500 4150 2    60   BiDi ~ 0
BOOT1
Text GLabel 2900 2450 0    60   BiDi ~ 0
BOOT0
$Comp
L maxwell-rescue:R-RESCUE-maxwell R10
U 1 1 5A1FCFDF
P 2650 2250
F 0 "R10" V 2443 2250 50  0000 C CNN
F 1 "10k" V 2534 2250 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 2580 2250 50  0001 C CNN
F 3 "" H 2650 2250 50  0001 C CNN
	1    2650 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	2800 2250 2850 2250
$Comp
L maxwell-rescue:C-RESCUE-maxwell C10
U 1 1 5A1FCFEE
P 5500 1500
F 0 "C10" H 5385 1454 50  0000 R CNN
F 1 "100n" H 5385 1545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 5538 1350 50  0001 C CNN
F 3 "" H 5500 1500 50  0001 C CNN
	1    5500 1500
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C11
U 1 1 5A1FCFF5
P 5600 1500
F 0 "C11" H 5485 1454 50  0000 R CNN
F 1 "100n" H 5485 1545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 5638 1350 50  0001 C CNN
F 3 "" H 5600 1500 50  0001 C CNN
	1    5600 1500
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C12
U 1 1 5A1FCFFC
P 5700 1500
F 0 "C12" H 5585 1454 50  0000 R CNN
F 1 "100n" H 5585 1545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 5738 1350 50  0001 C CNN
F 3 "" H 5700 1500 50  0001 C CNN
	1    5700 1500
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C13
U 1 1 5A1FD003
P 5800 1500
F 0 "C13" H 5685 1454 50  0000 R CNN
F 1 "100n" H 5685 1545 50  0000 R CNN
F 2 "coddingtonbear:0805_Milling" H 5838 1350 50  0001 C CNN
F 3 "" H 5800 1500 50  0001 C CNN
	1    5800 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 1650 5800 1750
Wire Wire Line
	5700 1650 5700 1750
Wire Wire Line
	5600 1650 5600 1750
Wire Wire Line
	5500 1650 5500 1750
Connection ~ 5500 1750
Connection ~ 5600 1750
Connection ~ 5700 1750
Connection ~ 5800 1750
Wire Wire Line
	5500 1350 5600 1350
Connection ~ 5700 1350
Connection ~ 5600 1350
Text GLabel 8500 3550 2    60   BiDi ~ 0
SWDIO
Text GLabel 8500 3650 2    60   BiDi ~ 0
SWCLK
Text GLabel 8800 4250 2    60   BiDi ~ 0
WAKE_B_SIG
Text GLabel 8500 3150 2    60   Output ~ 0
BT_DI
Text GLabel 8500 3250 2    60   Input ~ 0
BT_DO
Text GLabel 2900 4550 0    60   Output ~ 0
BT_KEY
Text GLabel 8500 2950 2    60   Output ~ 0
NEOPIXEL
Text GLabel 2750 1850 0    60   Input ~ 0
N_RST
Wire Wire Line
	2750 1850 2850 1850
Wire Wire Line
	2850 1850 2850 2250
Connection ~ 2850 2250
Text GLabel 2900 4350 0    60   Output ~ 0
ENABLE_LEDS
$Comp
L maxwell-rescue:R-RESCUE-maxwell R33
U 1 1 5A2732F7
P 2700 3600
F 0 "R33" V 2493 3600 50  0000 C CNN
F 1 "1M" V 2584 3600 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 2630 3600 50  0001 C CNN
F 3 "" H 2700 3600 50  0001 C CNN
	1    2700 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 3450 2700 3450
Wire Wire Line
	2800 3450 2800 3550
Wire Wire Line
	2800 3550 2900 3550
Connection ~ 2700 3450
Wire Wire Line
	2450 3750 2700 3750
Wire Wire Line
	2800 3750 2800 3650
Wire Wire Line
	2800 3650 2900 3650
Connection ~ 2700 3750
Text GLabel 8500 4350 2    60   Output ~ 0
CAN_DISABLE
Wire Wire Line
	2150 3600 2150 3750
Wire Wire Line
	5600 6050 5700 6050
Wire Wire Line
	5700 6050 5750 6050
Wire Wire Line
	5800 6050 5900 6050
Wire Wire Line
	5500 1750 5500 1850
Wire Wire Line
	5500 1750 5600 1750
Wire Wire Line
	5600 1750 5600 1850
Wire Wire Line
	5600 1750 5700 1750
Wire Wire Line
	5700 1750 5700 1850
Wire Wire Line
	5700 1750 5800 1750
Wire Wire Line
	5800 1750 5800 1850
Wire Wire Line
	5700 1350 5800 1350
Wire Wire Line
	5600 1350 5700 1350
Wire Wire Line
	2850 2250 2900 2250
Wire Wire Line
	2700 3450 2800 3450
Wire Wire Line
	2700 3750 2800 3750
Text GLabel 8500 4850 2    60   Output ~ 0
CAN_TX
Text GLabel 8500 4750 2    60   Input ~ 0
CAN_RX
Text GLabel 8500 2450 2    60   Output ~ 0
SPI2_CS_A
Text GLabel 8500 5450 2    60   Output ~ 0
SPI2_MOSI
Text GLabel 8500 5350 2    60   Input ~ 0
SPI2_MISO
Text GLabel 8500 5250 2    60   Output ~ 0
SPI2_SCK
Text GLabel 8500 2350 2    60   Output ~ 0
SPI2_CS_B
Text GLabel 2900 4650 0    60   Output ~ 0
~DISABLE_ESP
Wire Wire Line
	2800 3850 2850 3850
Wire Wire Line
	2850 3850 2850 3750
Wire Wire Line
	2850 3750 2900 3750
Text GLabel 2800 3850 0    60   Input ~ 0
UART5_RX
Text GLabel 2900 5150 0    60   Output ~ 0
UART5_TX
Text GLabel 2900 4950 0    60   Output ~ 0
UART4_TX
Text GLabel 2900 5050 0    60   Input ~ 0
UART4_RX
Text GLabel 8500 4550 2    60   BiDi ~ 0
I2C1_SCL_B
Text GLabel 8500 4650 2    60   BiDi ~ 0
I2C1_SDA_B
Wire Wire Line
	2900 5250 2850 5250
NoConn ~ 8500 3050
NoConn ~ 8500 5150
NoConn ~ 2900 4750
NoConn ~ 2900 4850
NoConn ~ 8500 2850
NoConn ~ 8500 2750
NoConn ~ 8500 2650
Wire Wire Line
	5800 1750 5900 1750
Wire Wire Line
	5900 1750 5900 1850
Text GLabel 8500 2250 2    60   Output ~ 0
SPI2_CS_C
$Comp
L coddingtonbear:GND_B #PWR0135
U 1 1 5C74DBF5
P 5750 6050
F 0 "#PWR0135" H 5750 5800 50  0001 C CNN
F 1 "GND_B" H 5755 5877 50  0000 C CNN
F 2 "" H 5750 6050 50  0001 C CNN
F 3 "" H 5750 6050 50  0001 C CNN
	1    5750 6050
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0137
U 1 1 5C74DC94
P 1950 3650
F 0 "#PWR0137" H 1950 3400 50  0001 C CNN
F 1 "GND_B" H 1955 3477 50  0000 C CNN
F 2 "" H 1950 3650 50  0001 C CNN
F 3 "" H 1950 3650 50  0001 C CNN
	1    1950 3650
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_B #PWR0139
U 1 1 5C74DCB9
P 6350 1400
F 0 "#PWR0139" H 6350 1150 50  0001 C CNN
F 1 "GND_B" H 6355 1227 50  0000 C CNN
F 2 "" H 6350 1400 50  0001 C CNN
F 3 "" H 6350 1400 50  0001 C CNN
	1    6350 1400
	1    0    0    -1  
$EndComp
Connection ~ 5750 6050
Wire Wire Line
	5750 6050 5800 6050
Wire Wire Line
	5800 1350 6350 1350
Wire Wire Line
	6350 1350 6350 1400
Connection ~ 5800 1350
$Comp
L coddingtonbear:+3V3_B #PWR0141
U 1 1 5C74FF98
P 2100 2250
F 0 "#PWR0141" H 2100 2100 50  0001 C CNN
F 1 "+3V3_B" H 2115 2423 50  0000 C CNN
F 2 "" H 2100 2250 50  0001 C CNN
F 3 "" H 2100 2250 50  0001 C CNN
	1    2100 2250
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_B #PWR0142
U 1 1 5C74FFC4
P 4850 1650
F 0 "#PWR0142" H 4850 1500 50  0001 C CNN
F 1 "+3V3_B" H 4865 1823 50  0000 C CNN
F 2 "" H 4850 1650 50  0001 C CNN
F 3 "" H 4850 1650 50  0001 C CNN
	1    4850 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2250 2500 2250
Wire Wire Line
	4850 1650 4850 1750
Wire Wire Line
	4850 1750 5500 1750
Text GLabel 8500 4950 2    60   Input ~ 0
ENABLE_AUX
$Comp
L Device:R R36
U 1 1 5CD6D53B
P 8650 4250
F 0 "R36" V 8443 4250 50  0000 C CNN
F 1 "300" V 8534 4250 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 8580 4250 50  0001 C CNN
F 3 "~" H 8650 4250 50  0001 C CNN
	1    8650 4250
	0    1    1    0   
$EndComp
Text GLabel 8500 4050 2    60   Output ~ 0
~SCREEN_EN
Text GLabel 8500 3950 2    60   Output ~ 0
SCREEN_RST
Text GLabel 2900 4450 0    60   Output ~ 0
SCREEN_A0
Text GLabel 2850 5250 0    60   Input ~ 0
LEFT_A
Text GLabel 2900 5350 0    60   Input ~ 0
LEFT_B
Text GLabel 2900 5450 0    60   Input ~ 0
RIGHT_A
Text GLabel 2900 4250 0    60   Input ~ 0
RIGHT_B
$EndSCHEMATC
