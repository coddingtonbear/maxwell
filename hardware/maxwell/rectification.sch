EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L Device:D_Zener D?
U 1 1 5C78DDF7
P 2650 2300
AR Path="/5A1FEBCF/5C78DDF7" Ref="D?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5C78DDF7" Ref="D3"  Part="1" 
F 0 "D3" V 2604 2379 50  0000 L CNN
F 1 "18V" V 2695 2379 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AE_P15.24mm_Horizontal" H 2650 2300 50  0001 C CNN
F 3 "~" H 2650 2300 50  0001 C CNN
	1    2650 2300
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D?
U 1 1 5C78DDFE
P 2650 2600
AR Path="/5A1FEBCF/5C78DDFE" Ref="D?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5C78DDFE" Ref="D4"  Part="1" 
F 0 "D4" V 2696 2521 50  0000 R CNN
F 1 "18V" V 2605 2521 50  0000 R CNN
F 2 "Diode_THT:D_DO-201AE_P15.24mm_Horizontal" H 2650 2600 50  0001 C CNN
F 3 "~" H 2650 2600 50  0001 C CNN
	1    2650 2600
	0    -1   -1   0   
$EndComp
Text GLabel 8400 3650 3    60   Output ~ 0
DYNAMO_VOLTAGE_C
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5C7ACBC0
P 8150 3300
AR Path="/5A1FEBCF/5C7ACBC0" Ref="R?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5C7ACBC0" Ref="R15"  Part="1" 
F 0 "R15" H 8220 3346 50  0000 L CNN
F 1 "20k" H 8220 3255 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 8080 3300 50  0001 C CNN
F 3 "" H 8150 3300 50  0001 C CNN
	1    8150 3300
	1    0    0    -1  
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5C7ACBC7
P 8150 3750
AR Path="/5A1FEBCF/5C7ACBC7" Ref="R?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5C7ACBC7" Ref="R17"  Part="1" 
F 0 "R17" H 8220 3796 50  0000 L CNN
F 1 "1470" H 8220 3705 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 8080 3750 50  0001 C CNN
F 3 "" H 8150 3750 50  0001 C CNN
	1    8150 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q6
U 1 1 5C7AD5F6
P 3900 2200
F 0 "Q6" H 4106 2246 50  0000 L CNN
F 1 "DMG2302UK" H 4106 2155 50  0000 L CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 4100 2300 50  0001 C CNN
F 3 "~" H 3900 2200 50  0001 C CNN
	1    3900 2200
	-1   0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q7
U 1 1 5C7AE100
P 3900 3500
F 0 "Q7" H 4106 3454 50  0000 L CNN
F 1 "DMG2302UK" H 4106 3545 50  0000 L CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 4100 3600 50  0001 C CNN
F 3 "~" H 3900 3500 50  0001 C CNN
	1    3900 3500
	-1   0    0    1   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q8
U 1 1 5C7AE13A
P 6950 2200
F 0 "Q8" H 7155 2154 50  0000 L CNN
F 1 "DMG2302UK" H 7155 2245 50  0000 L CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 7150 2300 50  0001 C CNN
F 3 "~" H 6950 2200 50  0001 C CNN
	1    6950 2200
	1    0    0    1   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q9
U 1 1 5C7AE1BC
P 6950 3550
F 0 "Q9" H 7155 3596 50  0000 L CNN
F 1 "DMG2302UK" H 7155 3505 50  0000 L CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 7150 3650 50  0001 C CNN
F 3 "~" H 6950 3550 50  0001 C CNN
	1    6950 3550
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:LM74670-Q1 U15
U 1 1 5C7AEFF9
P 4600 2250
F 0 "U15" V 5400 2250 60  0000 C CNN
F 1 "LM74670-Q1" V 5294 2250 60  0000 C CNN
F 2 "Package_SO:VSSOP-8_3.0x3.0mm_P0.65mm" H 4200 2600 60  0001 C CNN
F 3 "" H 4200 2600 60  0001 C CNN
	1    4600 2250
	0    -1   -1   0   
$EndComp
$Comp
L coddingtonbear:LM74670-Q1 U17
U 1 1 5C7AF2D4
P 6250 2200
F 0 "U17" V 5500 2200 60  0000 C CNN
F 1 "LM74670-Q1" V 5606 2200 60  0000 C CNN
F 2 "Package_SO:VSSOP-8_3.0x3.0mm_P0.65mm" H 5850 2550 60  0001 C CNN
F 3 "" H 5850 2550 60  0001 C CNN
	1    6250 2200
	0    1    1    0   
$EndComp
$Comp
L coddingtonbear:LM74670-Q1 U16
U 1 1 5C7AF7BD
P 4600 3700
F 0 "U16" V 3850 3700 60  0000 C CNN
F 1 "LM74670-Q1" V 3956 3700 60  0000 C CNN
F 2 "Package_SO:VSSOP-8_3.0x3.0mm_P0.65mm" H 4200 4050 60  0001 C CNN
F 3 "" H 4200 4050 60  0001 C CNN
	1    4600 3700
	0    -1   1    0   
$EndComp
$Comp
L coddingtonbear:LM74670-Q1 U18
U 1 1 5C7AF837
P 6250 3750
F 0 "U18" V 7050 3750 60  0000 C CNN
F 1 "LM74670-Q1" V 6944 3750 60  0000 C CNN
F 2 "Package_SO:VSSOP-8_3.0x3.0mm_P0.65mm" H 5850 4100 60  0001 C CNN
F 3 "" H 5850 4100 60  0001 C CNN
	1    6250 3750
	0    1    -1   0   
$EndComp
Wire Wire Line
	3800 1650 3800 2000
Wire Wire Line
	7050 1650 6100 1650
Wire Wire Line
	7050 1650 7050 2000
Wire Wire Line
	3800 1650 4750 1650
Connection ~ 6100 1650
Connection ~ 4750 1650
Wire Wire Line
	3800 2400 3800 2950
Wire Wire Line
	4100 2200 4100 2050
Wire Wire Line
	4100 2050 4250 2050
Wire Wire Line
	4100 2200 4100 2450
Wire Wire Line
	4100 2450 4250 2450
Connection ~ 4100 2200
Wire Wire Line
	6600 2000 6750 2000
Wire Wire Line
	6750 2000 6750 2200
Wire Wire Line
	6750 2200 6750 2400
Wire Wire Line
	6750 2400 6600 2400
Connection ~ 6750 2200
Wire Wire Line
	6100 2800 6100 2950
Wire Wire Line
	6100 2950 7050 2950
Connection ~ 6100 2950
Connection ~ 7050 2950
Wire Wire Line
	7050 2950 7050 2400
Wire Wire Line
	4750 2800 4750 2950
Wire Wire Line
	4750 2950 3800 2950
Connection ~ 4750 2950
Wire Wire Line
	4750 2950 4750 3150
Connection ~ 3800 2950
Wire Wire Line
	3800 2950 3800 3300
Wire Wire Line
	3800 4300 4750 4300
Wire Wire Line
	7050 2950 7050 3350
Wire Wire Line
	6750 3550 6700 3550
Wire Wire Line
	6600 3950 6700 3950
Wire Wire Line
	6700 3950 6700 3550
Connection ~ 6700 3550
Wire Wire Line
	6700 3550 6600 3550
Wire Wire Line
	7050 3750 7050 4300
Wire Wire Line
	7050 4300 6100 4300
Connection ~ 6100 4300
Wire Wire Line
	4250 3500 4150 3500
Wire Wire Line
	4150 3500 4150 3900
Wire Wire Line
	4150 3900 4250 3900
Connection ~ 4150 3500
Wire Wire Line
	4150 3500 4100 3500
Wire Wire Line
	4750 4300 6100 4300
Connection ~ 4750 4300
$Comp
L Device:C_Small C26
U 1 1 5C7B9295
P 5200 2250
F 0 "C26" H 5292 2296 50  0000 L CNN
F 1 "1u" H 5292 2205 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 5200 2250 50  0001 C CNN
F 3 "~" H 5200 2250 50  0001 C CNN
	1    5200 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C27
U 1 1 5C7B939F
P 5600 2200
F 0 "C27" H 5692 2246 50  0000 L CNN
F 1 "1u" H 5692 2155 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 5600 2200 50  0001 C CNN
F 3 "~" H 5600 2200 50  0001 C CNN
	1    5600 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C25
U 1 1 5C7B93DF
P 5150 3700
F 0 "C25" H 5242 3746 50  0000 L CNN
F 1 "1u" H 5242 3655 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 5150 3700 50  0001 C CNN
F 3 "~" H 5150 3700 50  0001 C CNN
	1    5150 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C28
U 1 1 5C7B9445
P 5700 3750
F 0 "C28" H 5792 3796 50  0000 L CNN
F 1 "1u" H 5792 3705 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 5700 3750 50  0001 C CNN
F 3 "~" H 5700 3750 50  0001 C CNN
	1    5700 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2150 4950 2150
Wire Wire Line
	5200 2350 4950 2350
Wire Wire Line
	5600 2100 5900 2100
Wire Wire Line
	5900 2300 5600 2300
Wire Wire Line
	5900 3650 5700 3650
Wire Wire Line
	5900 3850 5700 3850
Wire Wire Line
	4950 3800 5150 3800
Wire Wire Line
	5150 3600 4950 3600
Wire Wire Line
	3800 2950 3500 2950
Wire Wire Line
	4750 1650 6100 1650
Wire Wire Line
	3800 3700 3800 4300
Wire Wire Line
	3800 1650 2650 1650
Wire Wire Line
	2650 1650 2650 2150
Connection ~ 3800 1650
Wire Wire Line
	2650 2750 2650 4300
Wire Wire Line
	2650 4300 3800 4300
Connection ~ 3800 4300
Text Notes 5250 3000 0    60   ~ 0
MOSFET\nRectifier
$Comp
L Device:CP_Small C29
U 1 1 5C7CB665
P 7700 3050
F 0 "C29" H 7788 3096 50  0000 L CNN
F 1 "6000uF" H 7788 3005 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B02B-XH-A_02x2.50mm_Straight_LargePads" H 7700 3050 50  0001 C CNN
F 3 "~" H 7700 3050 50  0001 C CNN
	1    7700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3450 8150 3500
Wire Wire Line
	8150 3500 8400 3500
Wire Wire Line
	8400 3500 8400 3650
Connection ~ 8150 3500
Wire Wire Line
	8150 3500 8150 3600
$Comp
L coddingtonbear:LT3086IR U19
U 1 1 5C7D1315
P 9150 3050
F 0 "U19" H 9075 3465 50  0000 C CNN
F 1 "LT3086IR" H 9075 3374 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-7_TabPin4" H 9150 3050 50  0001 C CNN
F 3 "" H 9150 3050 50  0001 C CNN
	1    9150 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2950 8300 2950
Wire Wire Line
	8550 3100 8300 3100
Wire Wire Line
	8300 3100 8300 2950
Connection ~ 8300 2950
Wire Wire Line
	8550 3300 8550 3550
$Comp
L Device:R R30
U 1 1 5C7D44B0
P 9850 3100
F 0 "R30" H 9920 3146 50  0000 L CNN
F 1 "92k" H 9920 3055 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 9780 3100 50  0001 C CNN
F 3 "~" H 9850 3100 50  0001 C CNN
	1    9850 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 2950 9850 2950
Wire Wire Line
	9850 3250 9600 3250
Wire Wire Line
	9600 3250 9600 3100
Text GLabel 1000 2750 3    60   Output ~ 0
V_AC+
Text GLabel 1100 2750 3    60   Output ~ 0
V_AC-
Text GLabel 2650 2150 0    60   Input ~ 0
V_AC+
Text GLabel 2650 2750 0    60   Input ~ 0
V_AC-
$Comp
L coddingtonbear:GND_C #PWR0166
U 1 1 5CA9C407
P 8150 3900
F 0 "#PWR0166" H 8150 3650 50  0001 C CNN
F 1 "GND_C" H 8155 3727 50  0000 C CNN
F 2 "" H 8150 3900 50  0001 C CNN
F 3 "" H 8150 3900 50  0001 C CNN
	1    8150 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3550 8950 3550
$Comp
L coddingtonbear:GND_C #PWR0168
U 1 1 5CA9C484
P 3500 2950
F 0 "#PWR0168" H 3500 2700 50  0001 C CNN
F 1 "GND_C" H 3505 2777 50  0000 C CNN
F 2 "" H 3500 2950 50  0001 C CNN
F 3 "" H 3500 2950 50  0001 C CNN
	1    3500 2950
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_C #PWR0170
U 1 1 5CA9C4FD
P 8950 3550
F 0 "#PWR0170" H 8950 3300 50  0001 C CNN
F 1 "GND_C" H 8955 3377 50  0000 C CNN
F 2 "" H 8950 3550 50  0001 C CNN
F 3 "" H 8950 3550 50  0001 C CNN
	1    8950 3550
	1    0    0    -1  
$EndComp
Connection ~ 8950 3550
Wire Wire Line
	8950 3550 9150 3550
Text GLabel 1500 2750 3    60   Input ~ 0
DYNAMO_VOLTAGE_C
Wire Wire Line
	3550 6000 3550 6150
Wire Wire Line
	3450 6000 3550 6000
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5CB5DBE8
P 3000 6000
AR Path="/5A1FEBCF/5CB5DBE8" Ref="R?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5CB5DBE8" Ref="R14"  Part="1" 
F 0 "R14" H 3070 6046 50  0000 L CNN
F 1 "1k" H 3070 5955 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 2930 6000 50  0001 C CNN
F 3 "" H 3000 6000 50  0001 C CNN
	1    3000 6000
	0    -1   -1   0   
$EndComp
$Comp
L maxwell-rescue:D-RESCUE-maxwell D?
U 1 1 5CB5DBEF
P 3300 6000
AR Path="/5A1FEBCF/5CB5DBEF" Ref="D?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5CB5DBEF" Ref="D1"  Part="1" 
F 0 "D1" V 3346 5921 50  0000 R CNN
F 1 "1N4148WS" V 3255 5921 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 3300 6000 50  0001 C CNN
F 3 "" H 3300 6000 50  0001 C CNN
	1    3300 6000
	-1   0    0    1   
$EndComp
$Comp
L maxwell-rescue:TLP185(SE-RESCUE-maxwell U?
U 1 1 5CB5DBF6
P 2750 5700
AR Path="/5A1FEBCF/5CB5DBF6" Ref="U?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5CB5DBF6" Ref="U8"  Part="1" 
F 0 "U8" H 2750 6025 50  0000 C CNN
F 1 "TLP188" H 2750 5934 50  0000 C CNN
F 2 "coddingtonbear:SO-4_Optocoupler_Milling" H 2750 5400 50  0001 C CIN
F 3 "" H 2750 5700 50  0001 L CNN
	1    2750 5700
	0    -1   -1   0   
$EndComp
Text GLabel 2650 6000 3    60   Input ~ 0
V_AC+
Text GLabel 3550 6150 3    60   Input ~ 0
V_AC-
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J?
U 1 1 5CA95D13
P 1300 2550
AR Path="/5CA95D13" Ref="J?"  Part="1" 
AR Path="/5A1FEBCF/5CA95D13" Ref="J?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5CA95D13" Ref="J19"  Part="1" 
F 0 "J19" H 1350 3067 50  0000 C CNN
F 1 "Interconnect (Rect)" H 1350 2976 50  0000 C CNN
F 2 "coddingtonbear:PinHeader_2x08_P2.54mm_Vertical_LargePads" H 1300 2550 50  0001 C CNN
F 3 "~" H 1300 2550 50  0001 C CNN
	1    1300 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1300 2750 1300 2250
Wire Wire Line
	1400 2250 1400 2750
Text GLabel 1300 2750 3    60   Input ~ 0
DYNAMO_POLE_SIG_C
Text GLabel 3750 5400 2    60   Output ~ 0
DYNAMO_POLE_SIG_C
Wire Wire Line
	1000 2750 1000 2250
Wire Wire Line
	1100 2250 1100 2750
Wire Wire Line
	1700 2750 1700 2250
$Comp
L coddingtonbear:GND_C #PWR0187
U 1 1 5CBBF81A
P 1700 2750
F 0 "#PWR0187" H 1700 2500 50  0001 C CNN
F 1 "GND_C" H 1705 2577 50  0000 C CNN
F 2 "" H 1700 2750 50  0001 C CNN
F 3 "" H 1700 2750 50  0001 C CNN
	1    1700 2750
	1    0    0    -1  
$EndComp
Connection ~ 1700 2750
Wire Wire Line
	1600 2750 1600 2250
$Comp
L coddingtonbear:+3V3_C #PWR0188
U 1 1 5CBFC9D6
P 1200 3850
F 0 "#PWR0188" H 1200 3700 50  0001 C CNN
F 1 "+3V3_C" H 1215 4023 50  0000 C CNN
F 2 "" H 1200 3850 50  0001 C CNN
F 3 "" H 1200 3850 50  0001 C CNN
	1    1200 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2750 1500 2250
$Comp
L coddingtonbear:+3V3_C #PWR0189
U 1 1 5CC028AD
P 2650 5400
F 0 "#PWR0189" H 2650 5250 50  0001 C CNN
F 1 "+3V3_C" H 2665 5573 50  0000 C CNN
F 2 "" H 2650 5400 50  0001 C CNN
F 3 "" H 2650 5400 50  0001 C CNN
	1    2650 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2750 1400 3850
Wire Wire Line
	1400 3850 1200 3850
Connection ~ 1400 2750
Wire Wire Line
	2850 5400 3750 5400
$Comp
L coddingtonbear:GND_C #PWR0178
U 1 1 5CC23766
P 7700 3150
F 0 "#PWR0178" H 7700 2900 50  0001 C CNN
F 1 "GND_C" H 7705 2977 50  0000 C CNN
F 2 "" H 7700 3150 50  0001 C CNN
F 3 "" H 7700 3150 50  0001 C CNN
	1    7700 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2950 6100 3150
Wire Wire Line
	7700 2950 8150 2950
Wire Wire Line
	8150 3150 8150 2950
Connection ~ 8150 2950
Wire Wire Line
	8150 2950 8300 2950
$Comp
L Device:Q_PMOS_GDSD Q11
U 1 1 5CA84A4C
P 7250 2850
F 0 "Q11" V 7582 2850 50  0000 C CNN
F 1 "Q_PMOS_GDSD" V 7673 2850 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 7450 2950 50  0001 C CNN
F 3 "~" H 7250 2850 50  0001 C CNN
	1    7250 2850
	0    1    1    0   
$EndComp
$Comp
L maxwell-rescue:R-RESCUE-maxwell R?
U 1 1 5CA8831A
P 7600 2600
AR Path="/5A1FEBCF/5CA8831A" Ref="R?"  Part="1" 
AR Path="/5A1FEBCF/5C7831A2/5CA8831A" Ref="R41"  Part="1" 
F 0 "R41" H 7670 2646 50  0000 L CNN
F 1 "10k" H 7670 2555 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" V 7530 2600 50  0001 C CNN
F 3 "" H 7600 2600 50  0001 C CNN
	1    7600 2600
	0    1    1    0   
$EndComp
$Comp
L coddingtonbear:GND_C #PWR0194
U 1 1 5CA8840C
P 7900 2650
F 0 "#PWR0194" H 7900 2400 50  0001 C CNN
F 1 "GND_C" H 7905 2477 50  0000 C CNN
F 2 "" H 7900 2650 50  0001 C CNN
F 3 "" H 7900 2650 50  0001 C CNN
	1    7900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2650 7250 2600
Wire Wire Line
	7250 2600 7450 2600
Wire Wire Line
	7750 2600 7900 2600
Wire Wire Line
	7900 2600 7900 2650
Text GLabel 1600 2750 3    60   Output ~ 0
DISABLE_DYNAMO
Wire Wire Line
	1200 2250 1200 2750
Text GLabel 7350 2450 2    60   Input ~ 0
DISABLE_DYNAMO
Wire Wire Line
	7350 2450 7250 2450
Wire Wire Line
	7250 2450 7250 2600
Connection ~ 7250 2600
Wire Wire Line
	7450 3050 7500 3050
Wire Wire Line
	7500 3050 7500 2950
Wire Wire Line
	7500 2950 7700 2950
Connection ~ 7700 2950
Wire Wire Line
	7450 2950 7500 2950
Connection ~ 7500 2950
$EndSCHEMATC
