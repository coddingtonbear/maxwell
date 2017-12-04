EESchema Schematic File Version 3
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:stm32
LIBS:coddingtonbear
LIBS:mcp73831t
LIBS:custom
LIBS:w_rtx
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
L STM32F103RETx U7
U 1 1 5A1FCF5C
P 5700 3850
F 0 "U7" H 5700 6028 50  0000 C CNN
F 1 "STM32F103RETx" H 5700 5937 50  0000 C CNN
F 2 "kicad-castellated-breakouts:QFP64-1.27MM-CASTELLATED" H 8400 5725 50  0001 R TNN
F 3 "" H 5700 3850 50  0001 C CNN
	1    5700 3850
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR022
U 1 1 5A1FCF63
P 9400 3450
F 0 "#PWR022" H 9400 3300 50  0001 C CNN
F 1 "+3V3" H 9415 3623 50  0000 C CNN
F 2 "" H 9400 3450 50  0001 C CNN
F 3 "" H 9400 3450 50  0001 C CNN
	1    9400 3450
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 5A1FCF69
P 9150 3450
F 0 "R12" V 8943 3450 50  0000 C CNN
F 1 "1.5k" V 9034 3450 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9080 3450 50  0001 C CNN
F 3 "" H 9150 3450 50  0001 C CNN
	1    9150 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 3450 9000 3450
Wire Wire Line
	9400 3450 9300 3450
Text GLabel 9300 3550 2    60   BiDi ~ 0
USB+
Wire Wire Line
	9000 3550 8900 3550
Wire Wire Line
	8900 3550 8900 3450
Connection ~ 8900 3450
Text GLabel 8800 3350 2    60   BiDi ~ 0
USB-
$Comp
L R R13
U 1 1 5A1FCF77
P 9150 3550
F 0 "R13" V 9357 3550 50  0000 C CNN
F 1 "20" V 9266 3550 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9080 3550 50  0001 C CNN
F 3 "" H 9150 3550 50  0001 C CNN
	1    9150 3550
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 5A1FCF7E
P 8650 3350
F 0 "R11" V 8857 3350 50  0000 C CNN
F 1 "20" V 8766 3350 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 8580 3350 50  0001 C CNN
F 3 "" H 8650 3350 50  0001 C CNN
	1    8650 3350
	0    -1   -1   0   
$EndComp
$Comp
L Crystal Y2
U 1 1 5A1FCF85
P 2450 3600
F 0 "Y2" V 2404 3731 50  0000 L CNN
F 1 "8M" V 2495 3731 50  0000 L CNN
F 2 "SchrodingersGat/Components.pretty:crystal_hc-49s" H 2450 3600 50  0001 C CNN
F 3 "" H 2450 3600 50  0001 C CNN
	1    2450 3600
	0    1    1    0   
$EndComp
$Comp
L C C6
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
L C C7
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
L GND #PWR023
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
	2150 3450 2150 3750
Wire Wire Line
	1950 3650 1950 3600
Wire Wire Line
	1950 3600 2150 3600
Connection ~ 2150 3600
Wire Wire Line
	2450 3450 2700 3450
Wire Wire Line
	2700 3450 2700 3550
Wire Wire Line
	2700 3550 2900 3550
Wire Wire Line
	2450 3750 2700 3750
Wire Wire Line
	2700 3750 2700 3650
Wire Wire Line
	2700 3650 2900 3650
$Comp
L Crystal Y3
U 1 1 5A1FCFAA
P 2450 5400
F 0 "Y3" V 2404 5531 50  0000 L CNN
F 1 "32.768k" V 2495 5531 50  0000 L CNN
F 2 "f4grx/f4libs_th.pretty:XTAL32K" H 2450 5400 50  0001 C CNN
F 3 "" H 2450 5400 50  0001 C CNN
	1    2450 5400
	0    1    1    0   
$EndComp
$Comp
L C C8
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
L C C9
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
L GND #PWR024
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
	2450 5250 2700 5250
Wire Wire Line
	2700 5250 2700 5350
Wire Wire Line
	2700 5350 2900 5350
Wire Wire Line
	2450 5550 2700 5550
Wire Wire Line
	2700 5550 2700 5450
Wire Wire Line
	2700 5450 2900 5450
Wire Wire Line
	2150 5250 2150 5550
Wire Wire Line
	1950 5400 2150 5400
Connection ~ 2150 5400
$Comp
L GND #PWR025
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
	5500 6050 5900 6050
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
L R R10
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
L +3V3 #PWR026
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
	2900 2250 2800 2250
Wire Wire Line
	2500 2250 2350 2250
$Comp
L C C10
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
L C C11
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
L C C12
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
L C C13
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
L C C14
U 1 1 5A1FD00A
P 5900 1500
F 0 "C14" H 5785 1454 50  0000 R CNN
F 1 "100n" H 5785 1545 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 5938 1350 50  0001 C CNN
F 3 "" H 5900 1500 50  0001 C CNN
	1    5900 1500
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR027
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
L +3V3 #PWR028
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
	5900 1650 5900 1850
Wire Wire Line
	5800 1650 5800 1850
Wire Wire Line
	5700 1650 5700 1850
Wire Wire Line
	5600 1650 5600 1850
Wire Wire Line
	5500 1650 5500 1850
Wire Wire Line
	5200 1750 5900 1750
Connection ~ 5500 1750
Connection ~ 5600 1750
Connection ~ 5700 1750
Connection ~ 5800 1750
Connection ~ 5900 1750
Wire Wire Line
	5500 1350 5900 1350
Connection ~ 5800 1350
Connection ~ 5700 1350
Connection ~ 5600 1350
Wire Wire Line
	5700 1200 5700 1350
$Comp
L +3V3 #PWR029
U 1 1 5A1FD02D
P 2700 2650
F 0 "#PWR029" H 2700 2500 50  0001 C CNN
F 1 "+3V3" V 2715 2778 50  0000 L CNN
F 2 "" H 2700 2650 50  0001 C CNN
F 3 "" H 2700 2650 50  0001 C CNN
	1    2700 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 2650 2900 2650
Text GLabel 8500 3550 2    60   BiDi ~ 0
SWDIO
Text GLabel 8500 3650 2    60   BiDi ~ 0
SWCLK
Text GLabel 8500 5250 2    60   Input ~ 0
SPEED
Text GLabel 8500 2450 2    60   Output ~ 0
~DISABLE_USB_OUT
Text GLabel 8500 2550 2    60   Input ~ 0
~BATT_CHARGING
Text GLabel 8500 3950 2    60   Output ~ 0
POWER_ON
Text GLabel 8500 2750 2    60   Output ~ 0
SCK
Text GLabel 8500 2850 2    60   Input ~ 0
MISO
Text GLabel 8500 2950 2    60   Output ~ 0
MOSI
Text GLabel 8500 2350 2    60   Output ~ 0
~CAN_CS
Text GLabel 8500 3150 2    60   Output ~ 0
TXD
Text GLabel 8500 3250 2    60   Input ~ 0
RXD
Text GLabel 8500 4650 2    60   Output ~ 0
BT_KEY
Text GLabel 8500 4950 2    60   Input ~ 0
GSM_TXD
Text GLabel 8500 5050 2    60   Output ~ 0
GSM_RXD
Text GLabel 8500 5150 2    60   Output ~ 0
GSM_RST
Text GLabel 2900 4450 0    60   Input ~ 0
CURRENT_SENSE_1
Text GLabel 2900 4350 0    60   Input ~ 0
CURRENT_SENSE_2
Text GLabel 8500 2650 2    60   Input ~ 0
BATT_VOLTAGE
Text Notes 700  4200 0    60   ~ 0
V=(100*INPUT+47*INPUT)/100
Text GLabel 8500 3750 2    60   Output ~ 0
BUZZER
Text GLabel 2900 4750 0    60   Output ~ 0
NEOPIXEL
Text GLabel 2750 1850 0    60   Input ~ 0
N_RST
Wire Wire Line
	2750 1850 2850 1850
Wire Wire Line
	2850 1850 2850 2250
Connection ~ 2850 2250
Text GLabel 8500 4850 2    60   Output ~ 0
ENABLE_BATT_POWER
$EndSCHEMATC
