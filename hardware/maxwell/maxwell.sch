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
L Conn_02x03_Odd_Even J?
U 1 1 5A175D22
P 9150 4100
F 0 "J?" H 9200 4417 50  0000 C CNN
F 1 "Boot Selection Jumper" H 9250 3800 50  0000 C CNN
F 2 "" H 9150 4100 50  0001 C CNN
F 3 "" H 9150 4100 50  0001 C CNN
	1    9150 4100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5A175E99
P 9550 4000
F 0 "#PWR?" H 9550 3850 50  0001 C CNN
F 1 "+3V3" V 9565 4128 50  0000 L CNN
F 2 "" H 9550 4000 50  0001 C CNN
F 3 "" H 9550 4000 50  0001 C CNN
	1    9550 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 4000 9550 4000
Connection ~ 9500 4000
$Comp
L GND #PWR?
U 1 1 5A175F31
P 9550 4200
F 0 "#PWR?" H 9550 3950 50  0001 C CNN
F 1 "GND" V 9555 4072 50  0000 R CNN
F 2 "" H 9550 4200 50  0001 C CNN
F 3 "" H 9550 4200 50  0001 C CNN
	1    9550 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9450 4200 9550 4200
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
L R R?
U 1 1 5A1763A1
P 8800 3950
F 0 "R?" H 8870 3996 50  0000 L CNN
F 1 "100k" H 8870 3905 50  0000 L CNN
F 2 "" V 8730 3950 50  0001 C CNN
F 3 "" H 8800 3950 50  0001 C CNN
	1    8800 3950
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5A1763F8
P 10000 3950
F 0 "R?" H 10070 3996 50  0000 L CNN
F 1 "100k" H 10070 3905 50  0000 L CNN
F 2 "" V 9930 3950 50  0001 C CNN
F 3 "" H 10000 3950 50  0001 C CNN
	1    10000 3950
	1    0    0    -1  
$EndComp
Text GLabel 10300 4100 2    60   BiDi ~ 0
BOOT1
Wire Wire Line
	10000 3650 10000 3800
Wire Wire Line
	9450 4100 10300 4100
Wire Wire Line
	8600 4100 8950 4100
Wire Wire Line
	8800 3800 8800 3650
$Comp
L Conn_01x04 J?
U 1 1 5A178B78
P 10650 5650
F 0 "J?" H 10730 5642 50  0000 L CNN
F 1 "Programmer" H 10730 5551 50  0000 L CNN
F 2 "" H 10650 5650 50  0001 C CNN
F 3 "" H 10650 5650 50  0001 C CNN
	1    10650 5650
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5A178E3B
P 9900 5550
F 0 "#PWR?" H 9900 5400 50  0001 C CNN
F 1 "+3V3" H 9915 5723 50  0000 C CNN
F 2 "" H 9900 5550 50  0001 C CNN
F 3 "" H 9900 5550 50  0001 C CNN
	1    9900 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A178E94
P 9900 5900
F 0 "#PWR?" H 9900 5650 50  0001 C CNN
F 1 "GND" H 9905 5727 50  0000 C CNN
F 2 "" H 9900 5900 50  0001 C CNN
F 3 "" H 9900 5900 50  0001 C CNN
	1    9900 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 5900 9900 5850
Wire Wire Line
	9850 5850 10450 5850
Wire Wire Line
	9850 5550 10450 5550
Text GLabel 9450 5650 1    60   BiDi ~ 0
SWDIO
$Comp
L R R?
U 1 1 5A179266
P 9700 5850
F 0 "R?" V 9493 5850 50  0000 C CNN
F 1 "10k" V 9584 5850 50  0000 C CNN
F 2 "" V 9630 5850 50  0001 C CNN
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
L R R?
U 1 1 5A179C62
P 9700 5550
F 0 "R?" V 9493 5550 50  0000 C CNN
F 1 "10k" V 9584 5550 50  0000 C CNN
F 2 "" V 9630 5550 50  0001 C CNN
F 3 "" H 9700 5550 50  0001 C CNN
	1    9700 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	9500 5750 10450 5750
Wire Wire Line
	9500 5750 9500 5950
Wire Wire Line
	9550 5750 9550 5550
Connection ~ 9550 5750
Connection ~ 9900 5550
$Comp
L USB_A J?
U 1 1 5A18CBBC
P 10400 2250
F 0 "J?" H 10455 2717 50  0000 C CNN
F 1 "Charger Output" H 10300 2600 50  0000 C CNN
F 2 "" H 10550 2200 50  0001 C CNN
F 3 "" H 10550 2200 50  0001 C CNN
	1    10400 2250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 5A18D511
P 9600 2900
F 0 "#PWR?" H 9600 2650 50  0001 C CNN
F 1 "GND" H 9605 2727 50  0000 C CNN
F 2 "" H 9600 2900 50  0001 C CNN
F 3 "" H 9600 2900 50  0001 C CNN
	1    9600 2900
	1    0    0    -1  
$EndComp
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
L BOOST_BOARD U?
U 1 1 5A22128B
P 9100 2500
F 0 "U?" H 9075 2837 60  0000 C CNN
F 1 "BOOST_BOARD" H 9075 2731 60  0000 C CNN
F 2 "" H 9100 2500 60  0001 C CNN
F 3 "" H 9100 2500 60  0001 C CNN
	1    9100 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 2550 9700 2550
Wire Wire Line
	9600 2550 9600 2900
Wire Wire Line
	10400 1850 10850 1850
Wire Wire Line
	10850 1850 10850 2800
Wire Wire Line
	10850 2800 7850 2800
Connection ~ 9600 2800
Connection ~ 10500 1850
$Comp
L +BATT #PWR?
U 1 1 5A22154E
P 8350 2400
F 0 "#PWR?" H 8350 2250 50  0001 C CNN
F 1 "+BATT" H 8365 2573 50  0000 C CNN
F 2 "" H 8350 2400 50  0001 C CNN
F 3 "" H 8350 2400 50  0001 C CNN
	1    8350 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 2450 8350 2450
Wire Wire Line
	8350 2450 8350 2400
Wire Wire Line
	8600 2800 8600 2550
Text Notes 8800 2750 0    60   ~ 0
Tune to 5V
$Comp
L TPS2511 U?
U 1 1 5A221F46
P 9300 1400
F 0 "U?" H 9275 1797 60  0000 C CNN
F 1 "TPS2511" H 9275 1691 60  0000 C CNN
F 2 "" H 9300 1400 60  0001 C CNN
F 3 "" H 9300 1400 60  0001 C CNN
	1    9300 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2150 10100 1350
Wire Wire Line
	10100 1350 9750 1350
Wire Wire Line
	9750 1450 10000 1450
Wire Wire Line
	10000 1450 10000 2250
Wire Wire Line
	10000 2250 10100 2250
Wire Wire Line
	9750 1250 9900 1250
Wire Wire Line
	9900 1250 9900 2450
Wire Wire Line
	9900 2450 10100 2450
Wire Wire Line
	9550 2450 9550 2050
Wire Wire Line
	8600 2050 9700 2050
Wire Wire Line
	8600 850  8600 2050
Wire Wire Line
	8600 1450 8800 1450
Wire Wire Line
	7850 2800 7850 1250
Wire Wire Line
	7850 1250 8800 1250
Connection ~ 8600 2800
$Comp
L R R?
U 1 1 5A22238C
P 8100 1600
F 0 "R?" V 7893 1600 50  0000 C CNN
F 1 "25k" V 7984 1600 50  0000 C CNN
F 2 "" V 8030 1600 50  0001 C CNN
F 3 "" H 8100 1600 50  0001 C CNN
	1    8100 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 1600 7850 1600
Connection ~ 7850 1600
Wire Wire Line
	8250 1600 8350 1600
Wire Wire Line
	8350 1600 8350 1350
Wire Wire Line
	8350 1350 8800 1350
$Comp
L C C?
U 1 1 5A2226D0
P 9700 2400
F 0 "C?" H 9815 2446 50  0000 L CNN
F 1 "0.1u" H 9815 2355 50  0000 L CNN
F 2 "" H 9738 2250 50  0001 C CNN
F 3 "" H 9700 2400 50  0001 C CNN
	1    9700 2400
	1    0    0    -1  
$EndComp
Connection ~ 9600 2550
Wire Wire Line
	9700 2050 9700 2250
Connection ~ 9550 2050
Wire Wire Line
	9750 1700 9850 1700
Wire Wire Line
	9850 1700 9850 2800
Connection ~ 9850 2800
$Comp
L R R?
U 1 1 5A222DEF
P 9300 850
F 0 "R?" V 9093 850 50  0000 C CNN
F 1 "100k" V 9184 850 50  0000 C CNN
F 2 "" V 9230 850 50  0001 C CNN
F 3 "" H 9300 850 50  0001 C CNN
	1    9300 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	9750 1550 9800 1550
Wire Wire Line
	9800 1550 9800 850 
Wire Wire Line
	9450 850  9850 850 
Wire Wire Line
	9150 850  8600 850 
Connection ~ 8600 1450
Text GLabel 9850 850  2    60   Input ~ 0
~DISABLE_USB_OUT
Connection ~ 9800 850 
$Comp
L MCP2515-I/ST U?
U 1 1 5A2277DA
P 2200 6600
F 0 "U?" H 2200 7578 50  0000 C CNN
F 1 "MCP2515-I/ST" H 2200 7487 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 2200 5700 50  0001 C CIN
F 3 "" H 2300 5800 50  0001 C CNN
	1    2200 6600
	1    0    0    -1  
$EndComp
$Comp
L SN65HVD233 U?
U 1 1 5A227BE3
P 3900 6100
F 0 "U?" H 3900 6578 50  0000 C CNN
F 1 "SN65HVD233" H 3900 6487 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3900 5600 50  0001 C CNN
F 3 "" H 3800 6500 50  0001 C CNN
	1    3900 6100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5A227CC0
P 3000 5500
F 0 "#PWR?" H 3000 5350 50  0001 C CNN
F 1 "+3V3" H 3015 5673 50  0000 C CNN
F 2 "" H 3000 5500 50  0001 C CNN
F 3 "" H 3000 5500 50  0001 C CNN
	1    3000 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5800 2200 5500
Wire Wire Line
	2200 5500 3900 5500
Wire Wire Line
	3900 5500 3900 5800
Connection ~ 3000 5500
$Comp
L GND #PWR?
U 1 1 5A22802C
P 3000 7500
F 0 "#PWR?" H 3000 7250 50  0001 C CNN
F 1 "GND" H 3005 7327 50  0000 C CNN
F 2 "" H 3000 7500 50  0001 C CNN
F 3 "" H 3000 7500 50  0001 C CNN
	1    3000 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 7400 2200 7500
Wire Wire Line
	750  7500 3900 7500
Wire Wire Line
	3900 7500 3900 6500
Connection ~ 3000 7500
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
L R R?
U 1 1 5A2285B9
P 3350 6450
F 0 "R?" H 3420 6496 50  0000 L CNN
F 1 "10k" H 3420 6405 50  0000 L CNN
F 2 "" V 3280 6450 50  0001 C CNN
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
$Comp
L Conn_01x04 J?
U 1 1 5A228A9B
P 5100 6100
F 0 "J?" H 5180 6092 50  0000 L CNN
F 1 "Canbus 1" H 5180 6001 50  0000 L CNN
F 2 "" H 5100 6100 50  0001 C CNN
F 3 "" H 5100 6100 50  0001 C CNN
	1    5100 6100
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J?
U 1 1 5A228ADF
P 5100 6700
F 0 "J?" H 5180 6692 50  0000 L CNN
F 1 "Canbus 2" H 5180 6601 50  0000 L CNN
F 2 "" H 5100 6700 50  0001 C CNN
F 3 "" H 5100 6700 50  0001 C CNN
	1    5100 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 6100 4900 6100
Wire Wire Line
	4300 6200 4900 6200
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
L GND #PWR?
U 1 1 5A228E20
P 4700 6900
F 0 "#PWR?" H 4700 6650 50  0001 C CNN
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
L C C?
U 1 1 5A2293F2
P 2050 5500
F 0 "C?" V 1798 5500 50  0000 C CNN
F 1 "0.1u" V 1889 5500 50  0000 C CNN
F 2 "" H 2088 5350 50  0001 C CNN
F 3 "" H 2050 5500 50  0001 C CNN
	1    2050 5500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5A2294BF
P 1900 5500
F 0 "#PWR?" H 1900 5250 50  0001 C CNN
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
L Crystal Y?
U 1 1 5A22A948
P 1050 6850
F 0 "Y?" V 1004 6981 50  0000 L CNN
F 1 "16M" V 1095 6981 50  0000 L CNN
F 2 "" H 1050 6850 50  0001 C CNN
F 3 "" H 1050 6850 50  0001 C CNN
	1    1050 6850
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 5A22AAC1
P 900 6700
F 0 "C?" V 1152 6700 50  0000 C CNN
F 1 "22p" V 1061 6700 50  0000 C CNN
F 2 "" H 938 6550 50  0001 C CNN
F 3 "" H 900 6700 50  0001 C CNN
	1    900  6700
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5A22AB55
P 900 7000
F 0 "C?" V 1152 7000 50  0000 C CNN
F 1 "22p" V 1061 7000 50  0000 C CNN
F 2 "" H 938 6850 50  0001 C CNN
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
	1550 6900 1350 6900
Wire Wire Line
	1350 6900 1350 7000
Wire Wire Line
	1350 7000 1050 7000
Wire Wire Line
	750  6700 750  7500
Connection ~ 2200 7500
Connection ~ 750  7000
$Comp
L C C?
U 1 1 5A22B0AC
P 4050 5500
F 0 "C?" V 3798 5500 50  0000 C CNN
F 1 "0.1u" V 3889 5500 50  0000 C CNN
F 2 "" H 4088 5350 50  0001 C CNN
F 3 "" H 4050 5500 50  0001 C CNN
	1    4050 5500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5A22B0FF
P 4200 5500
F 0 "#PWR?" H 4200 5250 50  0001 C CNN
F 1 "GND" H 4205 5327 50  0000 C CNN
F 2 "" H 4200 5500 50  0001 C CNN
F 3 "" H 4200 5500 50  0001 C CNN
	1    4200 5500
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5A22B94C
P 4300 950
F 0 "#PWR?" H 4300 800 50  0001 C CNN
F 1 "+3V3" V 4315 1078 50  0000 L CNN
F 2 "" H 4300 950 50  0001 C CNN
F 3 "" H 4300 950 50  0001 C CNN
	1    4300 950 
	0    -1   -1   0   
$EndComp
$Comp
L ITEAD_HC-05 U?
U 1 1 5A239B9C
P 4800 1950
F 0 "U?" H 4800 3100 60  0000 C CNN
F 1 "ITEAD_HC-05" H 4800 2994 60  0000 C CNN
F 2 "" H 4800 1950 60  0000 C CNN
F 3 "" H 4800 1950 60  0000 C CNN
	1    4800 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A239C88
P 4800 3000
F 0 "#PWR?" H 4800 2750 50  0001 C CNN
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
	4700 3000 4900 3000
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
Text GLabel 8600 4100 0    60   BiDi ~ 0
BOOT0
Connection ~ 10000 4100
Connection ~ 8800 4100
$Comp
L GND #PWR?
U 1 1 5A23B2EB
P 10000 3650
F 0 "#PWR?" H 10000 3400 50  0001 C CNN
F 1 "GND" V 10005 3522 50  0000 R CNN
F 2 "" H 10000 3650 50  0001 C CNN
F 3 "" H 10000 3650 50  0001 C CNN
	1    10000 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8800 3650 10000 3650
Text GLabel 5950 2450 2    60   BiDi ~ 0
BOOT0
Text GLabel 5400 1850 2    60   Input ~ 0
BT_KEY
$Comp
L SIM800L_5-pin U?
U 1 1 5A24430F
P 6300 3950
F 0 "U?" H 6300 4297 60  0000 C CNN
F 1 "SIM800L_5-pin" H 6300 4191 60  0000 C CNN
F 2 "" H 6300 3950 60  0001 C CNN
F 3 "" H 6300 3950 60  0001 C CNN
	1    6300 3950
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR?
U 1 1 5A2444B4
P 6750 3850
F 0 "#PWR?" H 6750 3700 50  0001 C CNN
F 1 "+BATT" H 6765 4023 50  0000 C CNN
F 2 "" H 6750 3850 50  0001 C CNN
F 3 "" H 6750 3850 50  0001 C CNN
	1    6750 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A2444F6
P 6750 3950
F 0 "#PWR?" H 6750 3700 50  0001 C CNN
F 1 "GND" H 6755 3777 50  0000 C CNN
F 2 "" H 6750 3950 50  0001 C CNN
F 3 "" H 6750 3950 50  0001 C CNN
	1    6750 3950
	1    0    0    -1  
$EndComp
Text GLabel 5850 3950 0    60   Input ~ 0
GSM_TXD
Text GLabel 5850 3850 0    60   Output ~ 0
GSM_RXD
Text GLabel 5850 4050 0    60   Input ~ 0
GSM_RST
$Comp
L Buzzer BZ?
U 1 1 5A249244
P 4000 3900
F 0 "BZ?" H 4153 3929 50  0000 L CNN
F 1 "Buzzer" H 4153 3838 50  0000 L CNN
F 2 "" V 3975 4000 50  0001 C CNN
F 3 "" V 3975 4000 50  0001 C CNN
	1    4000 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A2492AA
P 3950 4650
F 0 "#PWR?" H 3950 4400 50  0001 C CNN
F 1 "GND" H 3955 4477 50  0000 C CNN
F 2 "" H 3950 4650 50  0001 C CNN
F 3 "" H 3950 4650 50  0001 C CNN
	1    3950 4650
	1    0    0    -1  
$EndComp
$Comp
L BSS138 Q?
U 1 1 5A249471
P 3700 3900
F 0 "Q?" V 4043 3900 50  0000 C CNN
F 1 "BSS138" V 3952 3900 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3900 3825 50  0001 L CIN
F 3 "" H 3700 3900 50  0001 L CNN
	1    3700 3900
	0    -1   -1   0   
$EndComp
$Comp
L +BATT #PWR?
U 1 1 5A24954C
P 3200 3800
F 0 "#PWR?" H 3200 3650 50  0001 C CNN
F 1 "+BATT" H 3215 3973 50  0000 C CNN
F 2 "" H 3200 3800 50  0001 C CNN
F 3 "" H 3200 3800 50  0001 C CNN
	1    3200 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3800 3200 3800
$Comp
L R R?
U 1 1 5A24990D
P 3750 4500
F 0 "R?" V 3543 4500 50  0000 C CNN
F 1 "10k" V 3634 4500 50  0000 C CNN
F 2 "" V 3680 4500 50  0001 C CNN
F 3 "" H 3750 4500 50  0001 C CNN
	1    3750 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	3900 4500 3950 4500
Wire Wire Line
	3950 4100 3950 4650
Wire Wire Line
	3900 4000 3900 4100
Wire Wire Line
	3900 4100 3950 4100
Connection ~ 3950 4500
Wire Wire Line
	3700 4100 3700 4150
Wire Wire Line
	3700 4150 3600 4150
Wire Wire Line
	3600 4150 3600 4500
Text GLabel 3400 4350 0    60   Input ~ 0
BUZZER
Wire Wire Line
	3400 4350 3600 4350
Connection ~ 3600 4350
$Comp
L Conn_01x03 J?
U 1 1 5A24A6D8
P 6400 4950
F 0 "J?" H 6480 4992 50  0000 L CNN
F 1 "Neopixel" H 6480 4901 50  0000 L CNN
F 2 "" H 6400 4950 50  0001 C CNN
F 3 "" H 6400 4950 50  0001 C CNN
	1    6400 4950
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR?
U 1 1 5A24A9EC
P 6000 4850
F 0 "#PWR?" H 6000 4700 50  0001 C CNN
F 1 "+BATT" H 6015 5023 50  0000 C CNN
F 2 "" H 6000 4850 50  0001 C CNN
F 3 "" H 6000 4850 50  0001 C CNN
	1    6000 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A24AA2F
P 6000 5050
F 0 "#PWR?" H 6000 4800 50  0001 C CNN
F 1 "GND" H 6005 4877 50  0000 C CNN
F 2 "" H 6000 5050 50  0001 C CNN
F 3 "" H 6000 5050 50  0001 C CNN
	1    6000 5050
	1    0    0    -1  
$EndComp
Text GLabel 6000 4950 0    60   Input ~ 0
NEOPIXEL
Wire Wire Line
	6000 4850 6200 4850
Wire Wire Line
	6200 4950 6000 4950
Wire Wire Line
	6000 5050 6200 5050
$Comp
L R R?
U 1 1 5A24C6B7
P 5650 2450
F 0 "R?" H 5720 2496 50  0000 L CNN
F 1 "330" H 5720 2405 50  0000 L CNN
F 2 "" V 5580 2450 50  0001 C CNN
F 3 "" H 5650 2450 50  0001 C CNN
	1    5650 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 2450 5400 2450
Wire Wire Line
	5800 2450 5950 2450
$Comp
L +BATT #PWR?
U 1 1 5A24D0EA
P 4500 6000
F 0 "#PWR?" H 4500 5850 50  0001 C CNN
F 1 "+BATT" H 4515 6173 50  0000 C CNN
F 2 "" H 4500 6000 50  0001 C CNN
F 3 "" H 4500 6000 50  0001 C CNN
	1    4500 6000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
