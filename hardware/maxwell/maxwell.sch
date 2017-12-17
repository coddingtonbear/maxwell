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
$Comp
L maxwell-rescue:Conn_02x03_Odd_Even-RESCUE-maxwell J4
U 1 1 5A175D22
P 9150 4100
F 0 "J4" H 9200 4417 50  0000 C CNN
F 1 "Boot Selection Jumper" H 9250 3800 50  0000 C CNN
F 2 "KiCad/Pin_Headers.pretty:Pin_Header_Straight_2x03_Pitch2.54mm" H 9150 4100 50  0001 C CNN
F 3 "" H 9150 4100 50  0001 C CNN
	1    9150 4100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR01
U 1 1 5A175E99
P 9550 4000
F 0 "#PWR01" H 9550 3850 50  0001 C CNN
F 1 "+3V3" V 9565 4128 50  0000 L CNN
F 2 "" H 9550 4000 50  0001 C CNN
F 3 "" H 9550 4000 50  0001 C CNN
	1    9550 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 4000 9500 4000
Connection ~ 9500 4000
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR02
U 1 1 5A175F31
P 9550 4200
F 0 "#PWR02" H 9550 3950 50  0001 C CNN
F 1 "GND" V 9555 4072 50  0000 R CNN
F 2 "" H 9550 4200 50  0001 C CNN
F 3 "" H 9550 4200 50  0001 C CNN
	1    9550 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9450 4200 9500 4200
Connection ~ 9500 4200
Wire Wire Line
	9500 4000 9500 3900
Wire Wire Line
	9500 3900 8950 3900
Wire Wire Line
	8950 3900 8950 4000
Wire Wire Line
	9500 4200 9500 4300
Wire Wire Line
	9500 4300 8950 4300
Wire Wire Line
	8950 4300 8950 4200
$Comp
L maxwell-rescue:R-RESCUE-maxwell R5
U 1 1 5A1763A1
P 8800 4100
F 0 "R5" H 8870 4146 50  0000 L CNN
F 1 "100k" H 8870 4055 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 8730 4100 50  0001 C CNN
F 3 "" H 8800 4100 50  0001 C CNN
	1    8800 4100
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R9
U 1 1 5A1763F8
P 9600 4100
F 0 "R9" H 9670 4146 50  0000 L CNN
F 1 "100k" H 9670 4055 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9530 4100 50  0001 C CNN
F 3 "" H 9600 4100 50  0001 C CNN
	1    9600 4100
	0    -1   -1   0   
$EndComp
Text GLabel 9750 4100 2    60   BiDi ~ 0
BOOT1
$Comp
L maxwell-rescue:Conn_01x04-RESCUE-maxwell J6
U 1 1 5A178B78
P 10650 5650
F 0 "J6" H 10730 5642 50  0000 L CNN
F 1 "Programmer" H 10730 5551 50  0000 L CNN
F 2 "KiCad/Pin_Headers.pretty:Pin_Header_Straight_1x04_Pitch2.54mm" H 10650 5650 50  0001 C CNN
F 3 "" H 10650 5650 50  0001 C CNN
	1    10650 5650
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR03
U 1 1 5A178E3B
P 9900 5550
F 0 "#PWR03" H 9900 5400 50  0001 C CNN
F 1 "+3V3" H 9915 5723 50  0000 C CNN
F 2 "" H 9900 5550 50  0001 C CNN
F 3 "" H 9900 5550 50  0001 C CNN
	1    9900 5550
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR04
U 1 1 5A178E94
P 9900 5900
F 0 "#PWR04" H 9900 5650 50  0001 C CNN
F 1 "GND" H 9905 5727 50  0000 C CNN
F 2 "" H 9900 5900 50  0001 C CNN
F 3 "" H 9900 5900 50  0001 C CNN
	1    9900 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 5900 9900 5850
Wire Wire Line
	9850 5850 9900 5850
Text GLabel 9450 5650 1    60   BiDi ~ 0
SWDIO
$Comp
L maxwell-rescue:R-RESCUE-maxwell R8
U 1 1 5A179266
P 9700 5850
F 0 "R8" V 9493 5850 50  0000 C CNN
F 1 "10k" V 9584 5850 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9630 5850 50  0001 C CNN
F 3 "" H 9700 5850 50  0001 C CNN
	1    9700 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	10450 5650 9450 5650
Connection ~ 9900 5850
Wire Wire Line
	9550 5850 9450 5850
Wire Wire Line
	9450 5850 9450 5650
Text GLabel 9500 5950 3    60   BiDi ~ 0
SWCLK
$Comp
L maxwell-rescue:R-RESCUE-maxwell R7
U 1 1 5A179C62
P 9700 5550
F 0 "R7" V 9493 5550 50  0000 C CNN
F 1 "10k" V 9584 5550 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 9630 5550 50  0001 C CNN
F 3 "" H 9700 5550 50  0001 C CNN
	1    9700 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	9500 5750 9550 5750
Wire Wire Line
	9500 5750 9500 5950
Wire Wire Line
	9550 5750 9550 5550
Connection ~ 9550 5750
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
L maxwell-rescue:BOOST_BOARD-RESCUE-maxwell U5
U 1 1 5A22128B
P 8050 2350
F 0 "U5" H 8025 2687 60  0000 C CNN
F 1 "BOOST_BOARD" H 8025 2581 60  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:BOOST_LM2596_3A" H 8050 2350 60  0001 C CNN
F 3 "" H 8050 2350 60  0001 C CNN
	1    8050 2350
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR06
U 1 1 5A22154E
P 7500 2300
F 0 "#PWR06" H 7500 2150 50  0001 C CNN
F 1 "+BATT" H 7515 2473 50  0000 C CNN
F 2 "" H 7500 2300 50  0001 C CNN
F 3 "" H 7500 2300 50  0001 C CNN
	1    7500 2300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C5
U 1 1 5A2226D0
P 9450 2450
F 0 "C5" H 9565 2496 50  0000 L CNN
F 1 "0.1u" H 9565 2405 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 9488 2300 50  0001 C CNN
F 3 "" H 9450 2450 50  0001 C CNN
	1    9450 2450
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R6
U 1 1 5A222DEF
P 8750 2050
F 0 "R6" V 8543 2050 50  0000 C CNN
F 1 "100k" V 8634 2050 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 8680 2050 50  0001 C CNN
F 3 "" H 8750 2050 50  0001 C CNN
	1    8750 2050
	-1   0    0    1   
$EndComp
Text GLabel 8750 1750 2    60   Input ~ 0
~ENABLE_USB_OUT
$Comp
L maxwell-rescue:SN65HVD233-RESCUE-maxwell U2
U 1 1 5A227BE3
P 3900 6100
F 0 "U2" H 3900 6578 50  0000 C CNN
F 1 "SN65HVD233" H 3900 6487 50  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOIC-8" H 3900 5600 50  0001 C CNN
F 3 "" H 3800 6500 50  0001 C CNN
	1    3900 6100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR07
U 1 1 5A227CC0
P 3000 5500
F 0 "#PWR07" H 3000 5350 50  0001 C CNN
F 1 "+3V3" H 3015 5673 50  0000 C CNN
F 2 "" H 3000 5500 50  0001 C CNN
F 3 "" H 3000 5500 50  0001 C CNN
	1    3000 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5800 2200 5500
Wire Wire Line
	3900 5500 3900 5800
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR08
U 1 1 5A22802C
P 3000 7500
F 0 "#PWR08" H 3000 7250 50  0001 C CNN
F 1 "GND" H 3005 7327 50  0000 C CNN
F 2 "" H 3000 7500 50  0001 C CNN
F 3 "" H 3000 7500 50  0001 C CNN
	1    3000 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 7400 2200 7500
Wire Wire Line
	750  7500 2200 7500
Wire Wire Line
	3900 7500 3900 6700
Wire Wire Line
	3500 6000 3200 6000
Wire Wire Line
	3200 6000 3200 6100
Wire Wire Line
	3200 6100 2800 6100
Wire Wire Line
	2800 6000 3150 6000
Wire Wire Line
	3150 6000 3150 6150
Wire Wire Line
	3150 6150 3250 6150
Wire Wire Line
	3250 6150 3250 6100
Wire Wire Line
	3250 6100 3500 6100
$Comp
L maxwell-rescue:R-RESCUE-maxwell R1
U 1 1 5A2285B9
P 3350 6450
F 0 "R1" H 3420 6496 50  0000 L CNN
F 1 "10k" H 3420 6405 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 3280 6450 50  0001 C CNN
F 3 "" H 3350 6450 50  0001 C CNN
	1    3350 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6300 3350 6300
Wire Wire Line
	3350 6600 3350 6700
Wire Wire Line
	3350 6700 3900 6700
Connection ~ 3900 6700
Wire Wire Line
	4300 6100 4400 6100
Wire Wire Line
	4300 6200 4350 6200
Wire Wire Line
	4600 6100 4600 6700
Wire Wire Line
	4600 6700 4900 6700
Connection ~ 4600 6100
Wire Wire Line
	4650 6200 4650 6800
Wire Wire Line
	4650 6800 4900 6800
Connection ~ 4650 6200
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR09
U 1 1 5A228E20
P 4700 6900
F 0 "#PWR09" H 4700 6650 50  0001 C CNN
F 1 "GND" H 4705 6727 50  0000 C CNN
F 2 "" H 4700 6900 50  0001 C CNN
F 3 "" H 4700 6900 50  0001 C CNN
	1    4700 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 6900 4700 6900
Wire Wire Line
	4700 6900 4700 6300
Wire Wire Line
	4700 6300 4900 6300
Wire Wire Line
	4900 6000 4500 6000
Wire Wire Line
	4900 6600 4500 6600
Wire Wire Line
	4500 6600 4500 6000
$Comp
L maxwell-rescue:C-RESCUE-maxwell C3
U 1 1 5A2293F2
P 2050 5500
F 0 "C3" V 1798 5500 50  0000 C CNN
F 1 "0.1u" V 1889 5500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 2088 5350 50  0001 C CNN
F 3 "" H 2050 5500 50  0001 C CNN
	1    2050 5500
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR010
U 1 1 5A2294BF
P 1900 5500
F 0 "#PWR010" H 1900 5250 50  0001 C CNN
F 1 "GND" H 1905 5327 50  0000 C CNN
F 2 "" H 1900 5500 50  0001 C CNN
F 3 "" H 1900 5500 50  0001 C CNN
	1    1900 5500
	1    0    0    -1  
$EndComp
Text GLabel 1600 6000 0    60   Input ~ 0
MOSI
Text GLabel 1600 6100 0    60   Output ~ 0
MISO
Text GLabel 1600 6200 0    60   Input ~ 0
~CAN_CS
Text GLabel 1600 6300 0    60   Input ~ 0
SCK
$Comp
L maxwell-rescue:Crystal-RESCUE-maxwell Y1
U 1 1 5A22A948
P 1050 6850
F 0 "Y1" V 1004 6981 50  0000 L CNN
F 1 "16M" V 1095 6981 50  0000 L CNN
F 2 "SchrodingersGat/Components.pretty:crystal_hc-49s" H 1050 6850 50  0001 C CNN
F 3 "" H 1050 6850 50  0001 C CNN
	1    1050 6850
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C1
U 1 1 5A22AAC1
P 900 6700
F 0 "C1" V 1152 6700 50  0000 C CNN
F 1 "22p" V 1061 6700 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 938 6550 50  0001 C CNN
F 3 "" H 900 6700 50  0001 C CNN
	1    900  6700
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:C-RESCUE-maxwell C2
U 1 1 5A22AB55
P 900 7000
F 0 "C2" V 1152 7000 50  0000 C CNN
F 1 "22p" V 1061 7000 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 938 6850 50  0001 C CNN
F 3 "" H 900 7000 50  0001 C CNN
	1    900  7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1600 6800 1350 6800
Wire Wire Line
	1350 6800 1350 6700
Wire Wire Line
	1350 6700 1050 6700
Wire Wire Line
	1350 6900 1600 6900
Wire Wire Line
	1350 6900 1350 7000
Wire Wire Line
	1350 7000 1050 7000
Connection ~ 2200 7500
$Comp
L maxwell-rescue:C-RESCUE-maxwell C4
U 1 1 5A22B0AC
P 4050 5500
F 0 "C4" V 3798 5500 50  0000 C CNN
F 1 "0.1u" V 3889 5500 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" H 4088 5350 50  0001 C CNN
F 3 "" H 4050 5500 50  0001 C CNN
	1    4050 5500
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR011
U 1 1 5A22B0FF
P 4200 5500
F 0 "#PWR011" H 4200 5250 50  0001 C CNN
F 1 "GND" H 4205 5327 50  0000 C CNN
F 2 "" H 4200 5500 50  0001 C CNN
F 3 "" H 4200 5500 50  0001 C CNN
	1    4200 5500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR012
U 1 1 5A22B94C
P 4300 950
F 0 "#PWR012" H 4300 800 50  0001 C CNN
F 1 "+3V3" V 4315 1078 50  0000 L CNN
F 2 "" H 4300 950 50  0001 C CNN
F 3 "" H 4300 950 50  0001 C CNN
	1    4300 950 
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:ITEAD_HC-05-RESCUE-maxwell U3
U 1 1 5A239B9C
P 4800 1950
F 0 "U3" H 4800 3100 60  0000 C CNN
F 1 "ITEAD_HC-05" H 4800 2994 60  0000 C CNN
F 2 "pelrun/libKiCad/footprint/w_rf_modules.pretty:ITEAD_HC-05" H 4800 1950 60  0001 C CNN
F 3 "" H 4800 1950 60  0000 C CNN
	1    4800 1950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR013
U 1 1 5A239C88
P 4800 3000
F 0 "#PWR013" H 4800 2750 50  0001 C CNN
F 1 "GND" H 4805 2827 50  0000 C CNN
F 2 "" H 4800 3000 50  0001 C CNN
F 3 "" H 4800 3000 50  0001 C CNN
	1    4800 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 950  4800 950 
Wire Wire Line
	4800 950  4800 1000
Wire Wire Line
	4700 3000 4800 3000
Wire Wire Line
	4900 3000 4900 2900
Wire Wire Line
	4700 3000 4700 2900
Connection ~ 4800 3000
Wire Wire Line
	4800 3000 4800 2900
Text GLabel 4200 1500 0    60   Input ~ 0
TXD
Text GLabel 4200 1600 0    60   Output ~ 0
RXD
Text GLabel 8650 4100 0    60   BiDi ~ 0
BOOT0
Text GLabel 5900 2450 2    60   BiDi ~ 0
BOOT0
Text GLabel 6100 2650 2    60   Input ~ 0
BT_KEY
$Comp
L maxwell-rescue:SIM800L_5-pin-RESCUE-maxwell U4
U 1 1 5A24430F
P 6300 3950
F 0 "U4" H 6300 4297 60  0000 C CNN
F 1 "SIM800L_5-pin" H 6300 4191 60  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:SIM800L_Breakout" H 6300 3950 60  0001 C CNN
F 3 "" H 6300 3950 60  0001 C CNN
	1    6300 3950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR015
U 1 1 5A2444B4
P 6750 3850
F 0 "#PWR015" H 6750 3700 50  0001 C CNN
F 1 "+BATT" H 6765 4023 50  0000 C CNN
F 2 "" H 6750 3850 50  0001 C CNN
F 3 "" H 6750 3850 50  0001 C CNN
	1    6750 3850
	1    0    0    -1  
$EndComp
Text GLabel 5850 3950 0    60   Input ~ 0
GSM_TXD
Text GLabel 5850 3850 0    60   Output ~ 0
GSM_RXD
Text GLabel 5850 4050 0    60   Input ~ 0
GSM_RST
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
F 2 "adamgreig/agg-kicad/agg.pretty:SOT-23" H 4000 4125 50  0001 L CIN
F 3 "" H 3800 4200 50  0001 L CNN
	1    3800 4200
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR018
U 1 1 5A24954C
P 3900 3800
F 0 "#PWR018" H 3900 3650 50  0001 C CNN
F 1 "+BATT" H 3915 3973 50  0000 C CNN
F 2 "" H 3900 3800 50  0001 C CNN
F 3 "" H 3900 3800 50  0001 C CNN
	1    3900 3800
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R2
U 1 1 5A24990D
P 3700 4750
F 0 "R2" V 3493 4750 50  0000 C CNN
F 1 "10k" V 3584 4750 50  0000 C CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 3630 4750 50  0001 C CNN
F 3 "" H 3700 4750 50  0001 C CNN
	1    3700 4750
	0    1    1    0   
$EndComp
Text GLabel 3350 4200 0    60   Input ~ 0
BUZZER
$Comp
L maxwell-rescue:Conn_01x03-RESCUE-maxwell J3
U 1 1 5A24A6D8
P 6400 4950
F 0 "J3" H 6480 4992 50  0000 L CNN
F 1 "Neopixel" H 6480 4901 50  0000 L CNN
F 2 "pbrook/Parts.pretty:JST-XH-3" H 6400 4950 50  0001 C CNN
F 3 "" H 6400 4950 50  0001 C CNN
	1    6400 4950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR019
U 1 1 5A24A9EC
P 6000 4850
F 0 "#PWR019" H 6000 4700 50  0001 C CNN
F 1 "+BATT" H 6015 5023 50  0000 C CNN
F 2 "" H 6000 4850 50  0001 C CNN
F 3 "" H 6000 4850 50  0001 C CNN
	1    6000 4850
	1    0    0    -1  
$EndComp
Text GLabel 5700 4950 0    60   Input ~ 0
NEOPIXEL
Wire Wire Line
	6000 4850 6200 4850
Wire Wire Line
	6000 5050 6200 5050
$Comp
L maxwell-rescue:R-RESCUE-maxwell R3
U 1 1 5A24C6B7
P 5650 2450
F 0 "R3" H 5720 2496 50  0000 L CNN
F 1 "330" H 5720 2405 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5580 2450 50  0001 C CNN
F 3 "" H 5650 2450 50  0001 C CNN
	1    5650 2450
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:+BATT-RESCUE-maxwell #PWR021
U 1 1 5A24D0EA
P 4500 6000
F 0 "#PWR021" H 4500 5850 50  0001 C CNN
F 1 "+BATT" H 4515 6173 50  0000 C CNN
F 2 "" H 4500 6000 50  0001 C CNN
F 3 "" H 4500 6000 50  0001 C CNN
	1    4500 6000
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x04-RESCUE-maxwell J5
U 1 1 5A24FD23
P 10850 2300
F 0 "J5" H 10929 2292 50  0000 L CNN
F 1 "Charger Output" H 10929 2201 50  0000 L CNN
F 2 "pbrook/Parts.pretty:JST-XH-4" H 10850 2300 50  0001 C CNN
F 3 "" H 10850 2300 50  0001 C CNN
	1    10850 2300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:MCP2515-E_ST-SOIC-RESCUE-maxwell U1
U 1 1 5A24ABF7
P 2200 6600
F 0 "U1" H 2200 7578 50  0000 C CNN
F 1 "MCP2515-E/ST-SOIC" H 2200 7487 50  0000 C CNN
F 2 "Tinkerforge/kicad-libraries:SOIC-18" H 2200 5700 50  0001 C CIN
F 3 "" H 2300 5800 50  0001 C CNN
	1    2200 6600
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR05
U 1 1 5A258FF8
P 6750 3950
F 0 "#PWR05" H 6750 3750 50  0001 C CNN
F 1 "GNDPWR" H 6754 4024 50  0000 C CNN
F 2 "" H 6750 3900 50  0001 C CNN
F 3 "" H 6750 3900 50  0001 C CNN
	1    6750 3950
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR017
U 1 1 5A2590C5
P 6000 5050
F 0 "#PWR017" H 6000 4850 50  0001 C CNN
F 1 "GNDPWR" H 6004 5124 50  0000 C CNN
F 2 "" H 6000 5000 50  0001 C CNN
F 3 "" H 6000 5000 50  0001 C CNN
	1    6000 5050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x05-RESCUE-maxwell J1
U 1 1 5A25E0A2
P 5100 6100
F 0 "J1" H 5180 6142 50  0000 L CNN
F 1 "Canbus 1" H 5180 6051 50  0000 L CNN
F 2 "KiCad/Connectors_JST.pretty:JST_XH_B05B-XH-A_05x2.50mm_Straight" H 5100 6100 50  0001 C CNN
F 3 "" H 5100 6100 50  0001 C CNN
	1    5100 6100
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:Conn_01x05-RESCUE-maxwell J2
U 1 1 5A25E262
P 5100 6700
F 0 "J2" H 5180 6742 50  0000 L CNN
F 1 "Canbus 2" H 5180 6651 50  0000 L CNN
F 2 "KiCad/Connectors_JST.pretty:JST_XH_B05B-XH-A_05x2.50mm_Straight" H 5100 6700 50  0001 C CNN
F 3 "" H 5100 6700 50  0001 C CNN
	1    5100 6700
	1    0    0    -1  
$EndComp
Text GLabel 4800 5900 1    60   Output ~ 0
POWER_ON
Wire Wire Line
	4900 5900 4800 5900
Wire Wire Line
	4800 5900 4800 6500
Wire Wire Line
	4800 6500 4900 6500
Text Label 4350 6100 0    60   ~ 0
CAN+
Text Label 4350 6200 0    60   ~ 0
CAN-
Text Label 2850 6000 0    60   ~ 0
RXCAN
Text Label 2850 6100 0    60   ~ 0
TXCAN
Wire Wire Line
	5800 2450 5900 2450
Text GLabel 5700 2150 2    60   Output ~ 0
POWER_ON
$Comp
L maxwell-rescue:R-RESCUE-maxwell R27
U 1 1 5A263D2E
P 5550 2150
F 0 "R27" H 5620 2196 50  0000 L CNN
F 1 "1k" H 5620 2105 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5480 2150 50  0001 C CNN
F 3 "" H 5550 2150 50  0001 C CNN
	1    5550 2150
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R28
U 1 1 5A265BD2
P 5700 2850
F 0 "R28" H 5770 2896 50  0000 L CNN
F 1 "10k" H 5770 2805 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5630 2850 50  0001 C CNN
F 3 "" H 5700 2850 50  0001 C CNN
	1    5700 2850
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:GND-RESCUE-maxwell #PWR052
U 1 1 5A265CDC
P 5850 2850
F 0 "#PWR052" H 5850 2600 50  0001 C CNN
F 1 "GND" H 5855 2677 50  0000 C CNN
F 2 "" H 5850 2850 50  0001 C CNN
F 3 "" H 5850 2850 50  0001 C CNN
	1    5850 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2650 5500 2650
Wire Wire Line
	5550 2850 5500 2850
Wire Wire Line
	5500 2850 5500 2650
Connection ~ 5500 2650
Wire Wire Line
	5500 2450 5400 2450
$Comp
L maxwell-rescue:R-RESCUE-maxwell R29
U 1 1 5A266BEB
P 5950 2650
F 0 "R29" H 6020 2696 50  0000 L CNN
F 1 "330" H 6020 2605 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5880 2650 50  0001 C CNN
F 3 "" H 5950 2650 50  0001 C CNN
	1    5950 2650
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R31
U 1 1 5A271748
P 5850 4950
F 0 "R31" H 5920 4996 50  0000 L CNN
F 1 "330" H 5920 4905 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 5780 4950 50  0001 C CNN
F 3 "" H 5850 4950 50  0001 C CNN
	1    5850 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 4950 6200 4950
$Comp
L maxwell-rescue:R-RESCUE-maxwell R32
U 1 1 5A271FA2
P 3050 7050
F 0 "R32" H 3120 7096 50  0000 L CNN
F 1 "10k" H 3120 7005 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 2980 7050 50  0001 C CNN
F 3 "" H 3050 7050 50  0001 C CNN
	1    3050 7050
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:+3V3-RESCUE-maxwell #PWR034
U 1 1 5A271FFF
P 3050 6900
F 0 "#PWR034" H 3050 6750 50  0001 C CNN
F 1 "+3V3" H 3065 7073 50  0000 C CNN
F 2 "" H 3050 6900 50  0001 C CNN
F 3 "" H 3050 6900 50  0001 C CNN
	1    3050 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 7200 3050 7200
Text GLabel 2800 6600 2    60   Output ~ 0
CAN_INT
$Comp
L maxwell-rescue:TPS2514-RESCUE-maxwell U11
U 1 1 5A29B51E
P 9750 2500
F 0 "U11" H 9750 2925 50  0000 C CNN
F 1 "TPS2514" H 9750 2834 50  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOT-23-6" H 9750 2100 50  0001 C CNN
F 3 "" H 9750 2550 50  0001 C CNN
	1    9750 2500
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:STT3P2UH7-RESCUE-maxwell U6
U 1 1 5A29BF27
P 9200 1400
F 0 "U6" H 9200 963 60  0000 C CNN
F 1 "STT3P2UH7" H 9200 1069 60  0000 C CNN
F 2 "adamgreig/agg-kicad/agg.pretty:SOT-23-6" H 9200 1400 60  0001 C CNN
F 3 "" H 9200 1400 60  0001 C CNN
	1    9200 1400
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:GNDPWR-RESCUE-maxwell #PWR014
U 1 1 5A29C476
P 8200 2700
F 0 "#PWR014" H 8200 2500 50  0001 C CNN
F 1 "GNDPWR" H 8204 2774 50  0000 C CNN
F 2 "" H 8200 2650 50  0001 C CNN
F 3 "" H 8200 2650 50  0001 C CNN
	1    8200 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 2300 10650 2300
Wire Wire Line
	10650 2500 10650 2800
Wire Wire Line
	10650 2800 9100 2800
Wire Wire Line
	9100 2800 9100 2700
Connection ~ 9100 2700
Wire Wire Line
	9450 2700 9450 2600
Wire Wire Line
	10650 2400 10050 2400
Wire Wire Line
	10650 1350 10650 2200
Wire Wire Line
	7550 2300 7500 2300
Wire Wire Line
	7550 2400 7500 2400
Wire Wire Line
	7500 2400 7500 2700
Wire Wire Line
	8500 2400 8500 2700
Connection ~ 8500 2700
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
	3350 4200 3450 4200
Wire Wire Line
	3550 4750 3450 4750
Wire Wire Line
	3450 4750 3450 4200
Connection ~ 3450 4200
Wire Wire Line
	3900 4400 3900 4450
Wire Wire Line
	3900 4750 3850 4750
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
Wire Wire Line
	10650 1350 9650 1350
Wire Wire Line
	9650 1250 9650 1350
Connection ~ 9650 1350
Wire Wire Line
	8500 2300 8500 1450
Wire Wire Line
	8500 1450 8750 1450
Wire Wire Line
	9450 2300 8750 2300
Wire Wire Line
	8750 1550 8750 1900
Wire Wire Line
	8750 2200 8750 2300
Connection ~ 8750 2300
$Comp
L maxwell-rescue:R-RESCUE-maxwell R37
U 1 1 5A2B653B
P 4350 6750
F 0 "R37" H 4420 6796 50  0000 L CNN
F 1 "120" H 4420 6705 50  0000 L CNN
F 2 "coddingtonbear/coddingtonbear.pretty:0805_Milling" V 4280 6750 50  0001 C CNN
F 3 "" H 4350 6750 50  0001 C CNN
	1    4350 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 6200 4350 6600
Connection ~ 4350 6200
Wire Wire Line
	4400 6100 4400 6900
Wire Wire Line
	4400 6900 4350 6900
Connection ~ 4400 6100
Wire Wire Line
	9500 4000 9550 4000
Wire Wire Line
	9500 4200 9550 4200
Wire Wire Line
	9900 5850 10450 5850
Wire Wire Line
	9550 5750 10450 5750
Wire Wire Line
	3900 6700 3900 6500
Wire Wire Line
	4600 6100 4900 6100
Wire Wire Line
	4650 6200 4900 6200
Wire Wire Line
	4800 3000 4900 3000
Wire Wire Line
	5500 2650 5800 2650
Wire Wire Line
	9100 2700 9450 2700
Wire Wire Line
	8500 2700 9100 2700
Wire Wire Line
	3450 4200 3600 4200
Wire Wire Line
	8750 2300 8500 2300
Wire Wire Line
	4350 6200 4650 6200
Wire Wire Line
	4400 6100 4600 6100
Wire Wire Line
	9850 5550 10450 5550
Wire Wire Line
	2200 5500 3900 5500
Wire Wire Line
	750  6700 750  7500
Wire Wire Line
	7500 2700 8500 2700
Wire Wire Line
	2200 7500 3900 7500
Wire Wire Line
	9650 1350 9650 1550
$EndSCHEMATC
