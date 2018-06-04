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
Text GLabel 9950 2100 0    60   BiDi ~ 0
WAKE
Text GLabel 1700 4600 0    60   BiDi ~ 0
WAKE
Text GLabel 7500 6100 2    60   Output ~ 0
~ENABLE_SCREEN_BACKLIGHT
Text GLabel 7500 5600 2    60   Input ~ 0
MC_IN
Text GLabel 7500 5500 2    60   Output ~ 0
MC_OUT
Text GLabel 9950 1800 0    60   Output ~ 0
~RIGHT_A
Text GLabel 9950 1700 0    60   Output ~ 0
~RIGHT_B
Text GLabel 7500 5300 2    60   Input ~ 0
~LEFT_A
Text GLabel 7500 5200 2    60   Input ~ 0
~LEFT_B
Text GLabel 7500 5100 2    60   Input ~ 0
~RIGHT_A
Text GLabel 7500 5000 2    60   Input ~ 0
~RIGHT_B
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
Text GLabel 7500 4800 2    60   Output ~ 0
DISBABLE_BLUETOOTH_
Text GLabel 7850 1400 0    60   Input ~ 0
CAN_TX
Text GLabel 1700 5500 0    60   Output ~ 0
CAN_TX
Text GLabel 1700 5400 0    60   Input ~ 0
CAN_RX
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
F 2 "cpavlina/kicad-pcblib/smd-non-ipc.pretty:Abracon-ABM2" H 1450 3950 50  0001 C CNN
F 3 "" H 1450 3950 50  0001 C CNN
	1    1450 3950
	0    -1   -1   0   
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
L power:GND #PWR021
U 1 1 5A6DBBE0
P 650 4100
F 0 "#PWR021" H 650 3850 50  0001 C CNN
F 1 "GND" H 655 3927 50  0000 C CNN
F 2 "" H 650 4100 50  0001 C CNN
F 3 "" H 650 4100 50  0001 C CNN
	1    650  4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3800 1100 3800
Wire Wire Line
	1150 4100 1100 4100
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
Text GLabel 8900 3000 3    60   Output ~ 0
BT_IN
Text GLabel 8800 3000 3    60   Input ~ 0
BT_OUT
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
Text GLabel 8300 4000 1    60   Input ~ 0
DISBABLE_BLUETOOTH_
$Comp
L power:+3V3 #PWR016
U 1 1 5AADA550
P 8600 3950
F 0 "#PWR016" H 8600 3800 50  0001 C CNN
F 1 "+3V3" H 8615 4123 50  0000 C CNN
F 2 "" H 8600 3950 50  0001 C CNN
F 3 "" H 8600 3950 50  0001 C CNN
	1    8600 3950
	1    0    0    -1  
$EndComp
$Comp
L device:C C12
U 1 1 5AADA71D
P 8900 3800
F 0 "C12" V 8648 3800 50  0000 C CNN
F 1 "0.1" V 8739 3800 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 8938 3650 50  0001 C CNN
F 3 "" H 8900 3800 50  0001 C CNN
	1    8900 3800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5AADA96B
P 8650 3600
F 0 "#PWR022" H 8650 3350 50  0001 C CNN
F 1 "GND" H 8655 3427 50  0000 C CNN
F 2 "" H 8650 3600 50  0001 C CNN
F 3 "" H 8650 3600 50  0001 C CNN
	1    8650 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 3950 8900 3950
Wire Wire Line
	9100 3950 8900 3950
Connection ~ 8900 3950
Wire Wire Line
	8650 3600 8900 3600
Wire Wire Line
	8900 3600 8900 3650
$Comp
L device:R R7
U 1 1 5AAEE024
P 11100 4900
F 0 "R7" H 11030 4854 50  0000 R CNN
F 1 "330" H 11030 4945 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 11030 4900 50  0001 C CNN
F 3 "" H 11100 4900 50  0001 C CNN
	1    11100 4900
	0    -1   -1   0   
$EndComp
Text GLabel 11250 4900 2    60   BiDi ~ 0
BOOT0
$Comp
L power:GND #PWR023
U 1 1 5AB08EE1
P 11050 5200
F 0 "#PWR023" H 11050 4950 50  0001 C CNN
F 1 "GND" H 11055 5027 50  0000 C CNN
F 2 "" H 11050 5200 50  0001 C CNN
F 3 "" H 11050 5200 50  0001 C CNN
	1    11050 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10950 5200 11050 5200
Wire Wire Line
	10950 5100 11050 5100
Wire Wire Line
	11050 5100 11050 5200
Connection ~ 11050 5200
$Comp
L power:GND #PWR024
U 1 1 5AB16B1C
P 9100 5650
F 0 "#PWR024" H 9100 5400 50  0001 C CNN
F 1 "GND" H 9105 5477 50  0000 C CNN
F 2 "" H 9100 5650 50  0001 C CNN
F 3 "" H 9100 5650 50  0001 C CNN
	1    9100 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5250 9100 5600
Wire Wire Line
	9600 5600 9100 5600
Connection ~ 9100 5600
Wire Wire Line
	9100 5600 9100 5650
Text GLabel 10950 4100 2    60   Input ~ 0
BT_IN
Text GLabel 10950 4000 2    60   Output ~ 0
BT_OUT
$Comp
L device:R R12
U 1 1 5AB6BF1F
P 8300 4250
F 0 "R12" H 8230 4204 50  0000 R CNN
F 1 "10k" H 8230 4295 50  0000 R CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 8230 4250 50  0001 C CNN
F 3 "" H 8300 4250 50  0001 C CNN
	1    8300 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR025
U 1 1 5AB6BFB4
P 7950 4400
F 0 "#PWR025" H 7950 4250 50  0001 C CNN
F 1 "+3V3" H 7965 4573 50  0000 C CNN
F 2 "" H 7950 4400 50  0001 C CNN
F 3 "" H 7950 4400 50  0001 C CNN
	1    7950 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 4100 8300 4050
Wire Wire Line
	7950 4400 8300 4400
Wire Wire Line
	8300 4050 9100 4050
Connection ~ 8300 4050
Wire Wire Line
	8300 4050 8300 4000
Wire Wire Line
	1100 3800 1100 4100
Connection ~ 1100 4100
$Comp
L Connector:Conn_01x03 J2
U 1 1 5ABF5BFA
P 8900 2800
F 0 "J2" V 8866 2612 50  0000 R CNN
F 1 "UART" V 8775 2612 50  0000 R CNN
F 2 "coddingtonbear:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 8900 2800 50  0001 C CNN
F 3 "~" H 8900 2800 50  0001 C CNN
	1    8900 2800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR029
U 1 1 5ABF6038
P 9000 3000
F 0 "#PWR029" H 9000 2750 50  0001 C CNN
F 1 "GND" H 9005 2827 50  0000 C CNN
F 2 "" H 9000 3000 50  0001 C CNN
F 3 "" H 9000 3000 50  0001 C CNN
	1    9000 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  4100 800  4100
$Comp
L device:Crystal_GND23 Y2
U 1 1 5AD8B52F
P 1200 4450
F 0 "Y2" V 1154 4691 50  0000 L CNN
F 1 "Crystal_GND23" V 1245 4691 50  0000 L CNN
F 2 "coddingtonbear:SM-CRYSTAL-ABS25_LargePads" H 1200 4450 50  0001 C CNN
F 3 "" H 1200 4450 50  0001 C CNN
	1    1200 4450
	0    1    1    0   
$EndComp
$Comp
L device:C C3
U 1 1 5AD8B64B
P 950 4300
F 0 "C3" V 698 4300 50  0000 C CNN
F 1 "22p" V 789 4300 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 988 4150 50  0001 C CNN
F 3 "" H 950 4300 50  0001 C CNN
	1    950  4300
	0    1    1    0   
$EndComp
$Comp
L device:C C4
U 1 1 5AD8B6C1
P 950 4600
F 0 "C4" V 698 4600 50  0000 C CNN
F 1 "22p" V 789 4600 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 988 4450 50  0001 C CNN
F 3 "" H 950 4600 50  0001 C CNN
	1    950  4600
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 4300 1200 4300
Wire Wire Line
	1100 4300 1200 4300
Connection ~ 1200 4300
Wire Wire Line
	1200 4600 1100 4600
Wire Wire Line
	1200 4600 1500 4600
Wire Wire Line
	1500 4600 1500 4400
Wire Wire Line
	1500 4400 1700 4400
Connection ~ 1200 4600
Wire Wire Line
	800  4300 800  4100
Connection ~ 800  4100
Wire Wire Line
	800  4100 1100 4100
Wire Wire Line
	800  4300 800  4600
Connection ~ 800  4300
Text GLabel 10500 5600 3    60   Input ~ 0
MC_OUT
Text GLabel 10400 5600 3    60   Output ~ 0
MC_IN
Text GLabel 1650 3300 1    60   Input ~ 0
NRST
Text GLabel 9100 4450 0    60   Output ~ 0
NRST
NoConn ~ 9800 5600
NoConn ~ 9900 5600
NoConn ~ 10000 5600
NoConn ~ 10100 5600
NoConn ~ 10200 5600
NoConn ~ 10300 5600
Text GLabel 9100 4350 0    60   Input ~ 0
BT_KEY
Text GLabel 7500 4700 2    60   Output ~ 0
BT_KEY
NoConn ~ 9100 5150
$Comp
L Connector:Conn_01x02 J9
U 1 1 5AE04FD4
P 8050 2500
F 0 "J9" H 8130 2492 50  0000 L CNN
F 1 "ESP_BM" H 8130 2401 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 8050 2500 50  0001 C CNN
F 3 "~" H 8050 2500 50  0001 C CNN
	1    8050 2500
	1    0    0    -1  
$EndComp
Text GLabel 7850 2500 0    60   Input ~ 0
ESP_BOOT_MODE
$Comp
L power:GND #PWR031
U 1 1 5AE05237
P 7850 2600
F 0 "#PWR031" H 7850 2350 50  0001 C CNN
F 1 "GND" H 7855 2427 50  0000 C CNN
F 2 "" H 7850 2600 50  0001 C CNN
F 3 "" H 7850 2600 50  0001 C CNN
	1    7850 2600
	1    0    0    -1  
$EndComp
$Comp
L esp32-local:ESP32-WROOM U2
U 1 1 5B0AB178
P 10050 4550
F 0 "U2" H 10025 5937 60  0000 C CNN
F 1 "ESP32-WROOM" H 10025 5831 60  0000 C CNN
F 2 "NorbotNorway/NorBotKiCadFootprints.pretty:ESP32-WROOM" H 10400 5900 60  0001 C CNN
F 3 "" H 9600 5000 60  0001 C CNN
	1    10050 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10 J3
U 1 1 5B0ABCF1
P 8050 1600
F 0 "J3" H 8130 1592 50  0000 L CNN
F 1 "FPC 1" H 8130 1501 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:10P_FPC_1.0mm" H 8050 1600 50  0001 C CNN
F 3 "~" H 8050 1600 50  0001 C CNN
	1    8050 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5B0AC455
P 7850 1200
F 0 "#PWR0102" H 7850 950 50  0001 C CNN
F 1 "GND" H 7855 1027 50  0000 C CNN
F 2 "" H 7850 1200 50  0001 C CNN
F 3 "" H 7850 1200 50  0001 C CNN
	1    7850 1200
	-1   0    0    1   
$EndComp
Text GLabel 1700 5800 0    60   Output ~ 0
~ENABLE_SCREEN
Text GLabel 9950 1200 0    60   Input ~ 0
~SPI_CS_5
Text GLabel 9950 1500 0    60   Input ~ 0
~SCREEN_CS
Text GLabel 1700 6100 0    60   Output ~ 0
~SCREEN_CS
Text GLabel 9950 1400 0    60   Input ~ 0
~SCREEN_RST
Text GLabel 1700 6000 0    60   Output ~ 0
~SCREEN_RST
Text GLabel 9950 1300 0    60   Input ~ 0
SCREEN_A0
Text GLabel 1700 5900 0    60   Output ~ 0
SCREEN_A0
Text GLabel 1700 4900 0    50   Output ~ 0
SPI1_SCK
Text GLabel 7850 2000 0    50   Input ~ 0
SPI1_SCK
Text GLabel 1700 5000 0    50   Input ~ 0
SPI1_MISO
Text GLabel 7850 1900 0    50   Output ~ 0
SPI1_MISO
Text GLabel 1700 5100 0    50   Output ~ 0
SPI1_MOSI
Text GLabel 7850 1800 0    50   Input ~ 0
SPI1_MOSI
$Comp
L Connector:Conn_01x10 J4
U 1 1 5B0AE219
P 10150 1600
F 0 "J4" H 10230 1592 50  0000 L CNN
F 1 "FPC 2" H 10230 1501 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:10P_FPC_1.0mm" H 10150 1600 50  0001 C CNN
F 3 "~" H 10150 1600 50  0001 C CNN
	1    10150 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0103
U 1 1 5B0AE606
P 7550 1200
F 0 "#PWR0103" H 7550 1050 50  0001 C CNN
F 1 "+3V3" H 7565 1373 50  0000 C CNN
F 2 "" H 7550 1200 50  0001 C CNN
F 3 "" H 7550 1200 50  0001 C CNN
	1    7550 1200
	1    0    0    -1  
$EndComp
Text GLabel 7850 2100 0    60   Input ~ 0
~ENABLE_SCREEN_BACKLIGHT
Wire Wire Line
	7550 1200 7550 1300
Wire Wire Line
	7550 1300 7850 1300
Text GLabel 7850 1500 0    60   Output ~ 0
CAN_RX
Text GLabel 9950 2000 0    60   Output ~ 0
~LEFT_A
Text GLabel 9950 1900 0    60   Output ~ 0
~LEFT_B
Text GLabel 1700 5300 0    50   Output ~ 0
~SPI1_CS_2
Text GLabel 1700 5200 0    50   Output ~ 0
~SPI1_CS_3
Text GLabel 7500 5400 2    50   Output ~ 0
~SPI1_CS_4
Text GLabel 7850 1600 0    50   Input ~ 0
~SPI1_CS_2
Text GLabel 7850 1700 0    50   Input ~ 0
~SPI1_CS_3
Text GLabel 9950 1600 0    50   Input ~ 0
~SPI1_CS_4
$EndSCHEMATC
