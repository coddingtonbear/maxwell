EESchema Schematic File Version 4
LIBS:maxwell-cache
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
L maxwell-rescue:STM32F103RETx-RESCUE-maxwell U7
U 1 1 5A1FCF5C
P 5700 3850
F 0 "U7" H 5700 6028 50  0000 C CNN
F 1 "STM32F103RETx" H 5700 5937 50  0000 C CNN
F 2 "kicad-castellated-breakouts:QFP64-1.27MM-CASTELLATED-VERS" H 8400 5725 50  0001 R TNN
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
F 2 "cpavlina/kicad-pcblib/smd-non-ipc.pretty:Abracon-ABM2" H 2450 3600 50  0001 C CNN
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
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 2338 3300 50  0001 C CNN
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
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 2338 3600 50  0001 C CNN
F 3 "" H 2300 3750 50  0001 C CNN
	1    2300 3750
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR023
U 1 1 5A1FCF9A
P 1950 3650
F 0 "#PWR023" H 1950 3400 50  0001 C CNN
F 1 "GND" H 1955 3477 50  0000 C CNN
F 2 "" H 1950 3650 50  0001 C CNN
F 3 "" H 1950 3650 50  0001 C CNN
	1    1950 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 3450 2150 3600
Wire Wire Line
	1950 3650 1950 3600
Wire Wire Line
	1950 3600 2150 3600
Connection ~ 2150 3600
$Comp
L maxwell-rescue:C-RESCUE-maxwell C8
U 1 1 5A1FCFB1
P 2300 5250
F 0 "C8" V 2048 5250 50  0000 C CNN
F 1 "22p" V 2139 5250 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 2338 5100 50  0001 C CNN
F 3 "" H 2300 5250 50  0001 C CNN
	1    2300 5250
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C9
U 1 1 5A1FCFB8
P 2300 5550
F 0 "C9" V 2048 5550 50  0000 C CNN
F 1 "22p" V 2139 5550 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 2338 5400 50  0001 C CNN
F 3 "" H 2300 5550 50  0001 C CNN
	1    2300 5550
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR024
U 1 1 5A1FCFBF
P 1950 5400
F 0 "#PWR024" H 1950 5150 50  0001 C CNN
F 1 "GND" H 1955 5227 50  0000 C CNN
F 2 "" H 1950 5400 50  0001 C CNN
F 3 "" H 1950 5400 50  0001 C CNN
	1    1950 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5250 2150 5400
Wire Wire Line
	1950 5400 2150 5400
Connection ~ 2150 5400
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR025
U 1 1 5A1FCFCE
P 5700 6050
F 0 "#PWR025" H 5700 5800 50  0001 C CNN
F 1 "GND" H 5705 5877 50  0000 C CNN
F 2 "" H 5700 6050 50  0001 C CNN
F 3 "" H 5700 6050 50  0001 C CNN
	1    5700 6050
	1    0    0    -1  
$EndComp
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
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2580 2250 50  0001 C CNN
F 3 "" H 2650 2250 50  0001 C CNN
	1    2650 2250
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR026
U 1 1 5A1FCFE6
P 2350 2250
F 0 "#PWR026" H 2350 2100 50  0001 C CNN
F 1 "+3V3" H 2365 2423 50  0000 C CNN
F 2 "" H 2350 2250 50  0001 C CNN
F 3 "" H 2350 2250 50  0001 C CNN
	1    2350 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2250 2850 2250
Wire Wire Line
	2500 2250 2350 2250
$Comp
L maxwell-rescue:C-RESCUE-maxwell C10
U 1 1 5A1FCFEE
P 5500 1500
F 0 "C10" H 5385 1454 50  0000 R CNN
F 1 "100n" H 5385 1545 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5538 1350 50  0001 C CNN
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
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5638 1350 50  0001 C CNN
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
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5738 1350 50  0001 C CNN
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
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5838 1350 50  0001 C CNN
F 3 "" H 5800 1500 50  0001 C CNN
	1    5800 1500
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR027
U 1 1 5A1FD011
P 5700 1200
F 0 "#PWR027" H 5700 950 50  0001 C CNN
F 1 "GND" H 5705 1027 50  0000 C CNN
F 2 "" H 5700 1200 50  0001 C CNN
F 3 "" H 5700 1200 50  0001 C CNN
	1    5700 1200
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR028
U 1 1 5A1FD017
P 5200 1750
F 0 "#PWR028" H 5200 1600 50  0001 C CNN
F 1 "+3V3" H 5215 1923 50  0000 C CNN
F 2 "" H 5200 1750 50  0001 C CNN
F 3 "" H 5200 1750 50  0001 C CNN
	1    5200 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1650 5800 1750
Wire Wire Line
	5700 1650 5700 1750
Wire Wire Line
	5600 1650 5600 1750
Wire Wire Line
	5500 1650 5500 1750
Wire Wire Line
	5200 1750 5500 1750
Connection ~ 5500 1750
Connection ~ 5600 1750
Connection ~ 5700 1750
Connection ~ 5800 1750
Wire Wire Line
	5500 1350 5600 1350
Connection ~ 5800 1350
Connection ~ 5700 1350
Connection ~ 5600 1350
Wire Wire Line
	5700 1200 5700 1350
Text GLabel 8500 3550 2    60   BiDi ~ 0
SWDIO
Text GLabel 8500 3650 2    60   BiDi ~ 0
SWCLK
Text GLabel 8500 2250 2    60   Input ~ 0
SPEED
Text GLabel 2900 4150 0    60   Input ~ 0
~BATT_CHARGING
Text GLabel 8500 3750 2    60   Input ~ 0
POWER_ON
Text GLabel 8500 3150 2    60   Output ~ 0
BT_DI
Text GLabel 8500 3250 2    60   Input ~ 0
BT_DO
Text GLabel 2900 4550 0    60   Output ~ 0
BT_KEY
Text GLabel 2900 4050 0    60   Input ~ 0
CURRENT_SENSE
Text GLabel 2900 3950 0    60   Input ~ 0
BATT_VOLTAGE
Text GLabel 8500 3450 2    60   Output ~ 0
BUZZER
Text GLabel 8500 2950 2    60   Output ~ 0
NEOPIXEL
Text GLabel 2750 1850 0    60   Input ~ 0
N_RST
Wire Wire Line
	2750 1850 2850 1850
Wire Wire Line
	2850 1850 2850 2250
Connection ~ 2850 2250
Text GLabel 8500 3950 2    60   Output ~ 0
ENABLE_BATT_POWER
$Comp
L maxwell-rescue:R-RESCUE-maxwell R33
U 1 1 5A2732F7
P 2700 3600
F 0 "R33" V 2493 3600 50  0000 C CNN
F 1 "1M" V 2584 3600 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2630 3600 50  0001 C CNN
F 3 "" H 2700 3600 50  0001 C CNN
	1    2700 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 5250 2550 5250
Wire Wire Line
	2800 5250 2800 5350
Wire Wire Line
	2800 5350 2900 5350
Wire Wire Line
	2900 5450 2800 5450
Wire Wire Line
	2800 5450 2800 5550
Wire Wire Line
	2800 5550 2550 5550
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
Text GLabel 2900 4250 0    60   Output ~ 0
CAN_DISABLE
Text GLabel 2000 5150 0    60   Output ~ 0
~BATT_CHARGE_ENABLE
Wire Wire Line
	2150 3600 2150 3750
Wire Wire Line
	2150 5400 2150 5550
Wire Wire Line
	5600 6050 5700 6050
Wire Wire Line
	5700 6050 5800 6050
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
$Comp
L maxwell-rescue:MCP1501-coddingtonbear U1
U 1 1 5A83FFBF
P 7000 1500
F 0 "U1" H 7050 1013 60  0000 C CNN
F 1 "MCP1501" H 7050 1119 60  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOT-23-6" H 7000 1500 60  0001 C CNN
F 3 "" H 7000 1500 60  0001 C CNN
	1    7000 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	6550 1650 6250 1650
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR022
U 1 1 5A841B1D
P 8200 1650
F 0 "#PWR022" H 8200 1500 50  0001 C CNN
F 1 "+3V3" H 8215 1823 50  0000 C CNN
F 2 "" H 8200 1650 50  0001 C CNN
F 3 "" H 8200 1650 50  0001 C CNN
	1    8200 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1300 7550 1300
Wire Wire Line
	7550 1300 7550 1350
Wire Wire Line
	7550 1400 7400 1400
Wire Wire Line
	7400 1500 7550 1500
Wire Wire Line
	7550 1500 7550 1400
Connection ~ 7550 1400
Connection ~ 7550 1350
Wire Wire Line
	7550 1350 7550 1400
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR030
U 1 1 5A845E73
P 7800 1350
F 0 "#PWR030" H 7800 1100 50  0001 C CNN
F 1 "GND" H 7805 1177 50  0000 C CNN
F 2 "" H 7800 1350 50  0001 C CNN
F 3 "" H 7800 1350 50  0001 C CNN
	1    7800 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7800 1350 7550 1350
$Comp
L maxwell-rescue:CP-device C2
U 1 1 5A8463F3
P 7900 1500
F 0 "C2" H 7782 1454 50  0000 R CNN
F 1 "2.2u" H 7782 1545 50  0000 R CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 7938 1350 50  0001 C CNN
F 3 "" H 7900 1500 50  0001 C CNN
	1    7900 1500
	-1   0    0    1   
$EndComp
Connection ~ 7900 1650
Wire Wire Line
	7900 1650 8200 1650
Wire Wire Line
	7900 1350 7800 1350
Wire Wire Line
	7400 1650 7900 1650
Connection ~ 7800 1350
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR031
U 1 1 5A847782
P 6400 1300
F 0 "#PWR031" H 6400 1150 50  0001 C CNN
F 1 "+3V3" H 6415 1473 50  0000 C CNN
F 2 "" H 6400 1300 50  0001 C CNN
F 3 "" H 6400 1300 50  0001 C CNN
	1    6400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1300 6400 1300
$Comp
L maxwell-rescue:CP-device C1
U 1 1 5A848A15
P 6250 1500
F 0 "C1" H 6132 1454 50  0000 R CNN
F 1 "2.2u" H 6132 1545 50  0000 R CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 6288 1350 50  0001 C CNN
F 3 "" H 6250 1500 50  0001 C CNN
	1    6250 1500
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R11
U 1 1 5A848A7F
P 6050 1250
F 0 "R11" V 5843 1250 50  0000 C CNN
F 1 "50" V 5934 1250 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5980 1250 50  0001 C CNN
F 3 "" H 6050 1250 50  0001 C CNN
	1    6050 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 1350 6250 1250
Wire Wire Line
	6250 1250 6200 1250
Wire Wire Line
	5900 1250 5800 1250
Wire Wire Line
	5800 1250 5800 1350
Wire Wire Line
	5900 1850 6250 1850
Wire Wire Line
	6250 1850 6250 1650
Connection ~ 6250 1650
$Comp
L maxwell-rescue:Crystal_GND23_Small-device Y1
U 1 1 5A8C64C3
P 2550 5400
F 0 "Y1" V 2504 5566 50  0000 L CNN
F 1 "32.768k" V 2595 5566 50  0000 L CNN
F 2 "KiCad/Crystals.pretty:Crystal_SMD_SeikoEpson_MC306-4pin_8.0x3.2mm" H 2550 5400 50  0001 C CNN
F 3 "" H 2550 5400 50  0001 C CNN
	1    2550 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 5300 2550 5250
Connection ~ 2550 5250
Wire Wire Line
	2550 5250 2800 5250
Wire Wire Line
	2550 5500 2550 5550
Connection ~ 2550 5550
Wire Wire Line
	2550 5550 2450 5550
Text GLabel 8500 2650 2    60   Output ~ 0
SPI2_CS_A
Text GLabel 8500 5450 2    60   Output ~ 0
SPI2_MOSI
Text GLabel 8500 5350 2    60   Input ~ 0
SPI2_MISO
Text GLabel 8500 5250 2    60   Output ~ 0
SPI2_SCK
Text GLabel 8500 2750 2    60   Output ~ 0
SPI2_CS_B
Text GLabel 8500 3350 2    60   Output ~ 0
~DISABLE_ESP
$Comp
L maxwell-rescue:+BACKUP-power #PWR061
U 1 1 5A89D925
P 2700 2650
F 0 "#PWR061" H 2700 2500 50  0001 C CNN
F 1 "+BACKUP" V 2715 2777 50  0000 L CNN
F 2 "" H 2700 2650 50  0001 C CNN
F 3 "" H 2700 2650 50  0001 C CNN
	1    2700 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 2650 2700 2650
Text GLabel 8500 5050 2    60   Input ~ 0
GPS_DO
Text GLabel 8500 4950 2    60   Output ~ 0
GPS_DI
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
I2C1_SCL
Text GLabel 8500 4650 2    60   BiDi ~ 0
I2C1_SDA
Wire Wire Line
	2900 5250 2850 5250
Wire Wire Line
	2850 5250 2850 5150
Wire Wire Line
	2850 5150 2000 5150
$Comp
L maxwell-rescue:Conn_01x03-conn J15
U 1 1 5A8B48F3
P 9450 4350
F 0 "J15" H 9529 4392 50  0000 L CNN
F 1 "GPIO" H 9529 4301 50  0000 L CNN
F 2 "KiCad/Pin_Headers.pretty:Pin_Header_Straight_1x03_Pitch2.54mm" H 9450 4350 50  0001 C CNN
F 3 "~" H 9450 4350 50  0001 C CNN
	1    9450 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4250 9250 4250
Wire Wire Line
	9250 4350 8500 4350
Wire Wire Line
	8500 4450 9250 4450
NoConn ~ 8500 3050
NoConn ~ 8500 5150
NoConn ~ 2900 4350
NoConn ~ 2900 4450
NoConn ~ 2900 4750
NoConn ~ 2900 4850
NoConn ~ 2450 5400
NoConn ~ 2650 5400
Text GLabel 8500 2350 2    60   Output ~ 0
BATT_SOURCE_DISABLE
$EndSCHEMATC
