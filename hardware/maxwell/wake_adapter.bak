EESchema Schematic File Version 4
LIBS:maxwell-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L Connector_Generic:Conn_01x03 J?
U 1 1 5CD407B0
P 1650 2500
AR Path="/5CD407B0" Ref="J?"  Part="1" 
AR Path="/5CD4044C/5CD407B0" Ref="J22"  Part="1" 
F 0 "J22" H 1729 2542 50  0000 L CNN
F 1 "To Board" H 1729 2451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1650 2500 50  0001 C CNN
F 3 "~" H 1650 2500 50  0001 C CNN
	1    1650 2500
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5CD407CA
P 3000 2500
AR Path="/5CD407CA" Ref="J?"  Part="1" 
AR Path="/5CD4044C/5CD407CA" Ref="J24"  Part="1" 
F 0 "J24" H 3079 2542 50  0000 L CNN
F 1 "From Button" H 3079 2451 50  0000 L CNN
F 2 "coddingtonbear:JST_XH_B03B-XH-A_03x2.50mm_Straight_LargePads" H 3000 2500 50  0001 C CNN
F 3 "~" H 3000 2500 50  0001 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2400 2800 2400
Wire Wire Line
	1850 2500 2350 2500
Wire Wire Line
	1850 2600 2750 2600
Text Notes 1850 2400 0    60   ~ 0
W_GND
Text Notes 1850 2500 0    60   ~ 0
W_LA
Text Notes 1850 2600 0    60   ~ 0
W_LB
$Comp
L Device:Q_PMOS_GSD Q12
U 1 1 5CD4D1B6
P 2750 1500
F 0 "Q12" V 3093 1500 50  0000 C CNN
F 1 "NTR1P02T1" V 3002 1500 50  0000 C CNN
F 2 "coddingtonbear:SOT-23_LargePads" H 2950 1600 50  0001 C CNN
F 3 "~" H 2750 1500 50  0001 C CNN
	1    2750 1500
	0    1    -1   0   
$EndComp
$Comp
L Device:R_Small R24
U 1 1 5CD4D36A
P 2350 1600
F 0 "R24" H 2409 1646 50  0000 L CNN
F 1 "10k" H 2409 1555 50  0000 L CNN
F 2 "coddingtonbear:0805_Milling" H 2350 1600 50  0001 C CNN
F 3 "~" H 2350 1600 50  0001 C CNN
	1    2350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1400 2350 1400
Wire Wire Line
	2350 1500 2350 1400
Wire Wire Line
	2750 1700 2350 1700
$Comp
L Connector_Generic:Conn_01x02 J23
U 1 1 5CD4DC29
P 950 1400
F 0 "J23" H 870 1075 50  0000 C CNN
F 1 "CAN" H 870 1166 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 950 1400 50  0001 C CNN
F 3 "~" H 950 1400 50  0001 C CNN
	1    950  1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 1900 2350 1700
Connection ~ 2350 1700
Wire Wire Line
	2750 1900 2750 1700
Connection ~ 2750 1700
Wire Wire Line
	2750 2100 2750 2600
Connection ~ 2750 2600
Wire Wire Line
	2750 2600 2800 2600
Wire Wire Line
	2350 2100 2350 2500
Connection ~ 2350 2500
Wire Wire Line
	2350 2500 2800 2500
$Comp
L Device:D D5
U 1 1 5CD4E951
P 2200 1400
F 0 "D5" H 2200 1184 50  0000 C CNN
F 1 "1N4148WS" H 2200 1275 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 2200 1400 50  0001 C CNN
F 3 "~" H 2200 1400 50  0001 C CNN
	1    2200 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	2950 1400 3150 1400
Wire Wire Line
	3150 1400 3150 1000
$Comp
L Device:Jumper_NC_Small JP2
U 1 1 5CD4F7F0
P 2350 2000
F 0 "JP2" V 2300 1750 50  0000 L CNN
F 1 "JMP_A" V 2400 1700 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_Pad1.0x1.5mm" H 2350 2000 50  0001 C CNN
F 3 "~" H 2350 2000 50  0001 C CNN
	1    2350 2000
	0    1    1    0   
$EndComp
$Comp
L Device:Jumper_NO_Small JP3
U 1 1 5CD4F982
P 2750 2000
F 0 "JP3" V 2704 2048 50  0000 L CNN
F 1 "JMP_B" V 2795 2048 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 2750 2000 50  0001 C CNN
F 3 "~" H 2750 2000 50  0001 C CNN
	1    2750 2000
	0    1    1    0   
$EndComp
$Comp
L Device:D D8
U 1 1 5CD5CCD8
P 1750 1400
F 0 "D8" H 1750 1184 50  0000 C CNN
F 1 "1N4148WS" H 1750 1275 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 1750 1400 50  0001 C CNN
F 3 "~" H 1750 1400 50  0001 C CNN
	1    1750 1400
	-1   0    0    1   
$EndComp
Connection ~ 2350 1400
Wire Wire Line
	1150 1400 1600 1400
Wire Wire Line
	1900 1400 2050 1400
Wire Wire Line
	3150 1000 1150 1000
Wire Wire Line
	1150 1000 1150 1300
$EndSCHEMATC
