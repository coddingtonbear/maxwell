EESchema Schematic File Version 4
LIBS:maxwell-polarity-cache
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
L coddingtonbear:MIC5209-ADJ U?
U 1 1 5A821CE3
P 4900 1050
F 0 "U?" H 4900 1537 60  0000 C CNN
F 1 "MIC5209-ADJ" H 4900 1431 60  0000 C CNN
F 2 "" H 4900 1050 60  0001 C CNN
F 3 "" H 4900 1050 60  0001 C CNN
	1    4900 1050
	1    0    0    -1  
$EndComp
$Sheet
S 650  600  1200 600 
U 5A822084
F0 "Polarity" 60
F1 "polarity.sch" 60
$EndSheet
$Sheet
S 650  1450 1350 950 
U 5A826A44
F0 "microcontroller" 60
F1 "microcontroller.sch" 60
$EndSheet
$Comp
L device:Q_PMOS_GSD Q?
U 1 1 5A82AD60
P 3700 1050
F 0 "Q?" V 4043 1050 50  0000 C CNN
F 1 "NDS332P" V 3952 1050 50  0000 C CNN
F 2 "" H 3900 1150 50  0001 C CNN
F 3 "" H 3700 1050 50  0001 C CNN
	1    3700 1050
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x05 J?
U 1 1 5A82AE8F
P 2500 1050
F 0 "J?" H 2420 625 50  0000 C CNN
F 1 "INPUT" H 2420 716 50  0000 C CNN
F 2 "" H 2500 1050 50  0001 C CNN
F 3 "~" H 2500 1050 50  0001 C CNN
	1    2500 1050
	-1   0    0    1   
$EndComp
Text GLabel 2700 850  2    60   BiDi ~ 0
WAKE
Text GLabel 2700 1050 2    60   BiDi ~ 0
CAN+
Text GLabel 2700 1150 2    60   BiDi ~ 0
CAN-
$Comp
L power:+BATT #PWR?
U 1 1 5A82AFF0
P 3250 850
F 0 "#PWR?" H 3250 700 50  0001 C CNN
F 1 "+BATT" H 3265 1023 50  0000 C CNN
F 2 "" H 3250 850 50  0001 C CNN
F 3 "" H 3250 850 50  0001 C CNN
	1    3250 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 950  3250 950 
Wire Wire Line
	3250 850  3250 950 
Connection ~ 3250 950 
Wire Wire Line
	3250 950  2700 950 
$Comp
L power:GND #PWR?
U 1 1 5A82B041
P 2850 1250
F 0 "#PWR?" H 2850 1000 50  0001 C CNN
F 1 "GND" H 2855 1077 50  0000 C CNN
F 2 "" H 2850 1250 50  0001 C CNN
F 3 "" H 2850 1250 50  0001 C CNN
	1    2850 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1250 2850 1250
Connection ~ 2850 1250
Wire Wire Line
	2850 1250 3700 1250
$Comp
L device:R R?
U 1 1 5A82B119
P 4200 850
F 0 "R?" V 3993 850 50  0000 C CNN
F 1 "10k" V 4084 850 50  0000 C CNN
F 2 "" V 4130 850 50  0001 C CNN
F 3 "" H 4200 850 50  0001 C CNN
	1    4200 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 950  3950 950 
Wire Wire Line
	4050 850  3950 850 
Wire Wire Line
	3950 850  3950 950 
Connection ~ 3950 950 
Wire Wire Line
	3950 950  3900 950 
Wire Wire Line
	4350 850  4450 850 
$Comp
L device:CP C?
U 1 1 5A82B33B
P 3950 1200
F 0 "C?" H 4068 1246 50  0000 L CNN
F 1 "1u" H 4068 1155 50  0000 L CNN
F 2 "" H 3988 1050 50  0001 C CNN
F 3 "" H 3950 1200 50  0001 C CNN
	1    3950 1200
	1    0    0    -1  
$EndComp
$Comp
L device:CP C?
U 1 1 5A82B394
P 4300 1200
F 0 "C?" H 4418 1246 50  0000 L CNN
F 1 "2.2u" H 4418 1155 50  0000 L CNN
F 2 "" H 4338 1050 50  0001 C CNN
F 3 "" H 4300 1200 50  0001 C CNN
	1    4300 1200
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5A82B40E
P 4100 1450
F 0 "#PWR?" H 4100 1300 50  0001 C CNN
F 1 "+3V3" H 4115 1623 50  0000 C CNN
F 2 "" H 4100 1450 50  0001 C CNN
F 3 "" H 4100 1450 50  0001 C CNN
	1    4100 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 1450 4100 1050
Wire Wire Line
	4100 1050 4300 1050
Wire Wire Line
	4450 1050 4300 1050
Connection ~ 4300 1050
Wire Wire Line
	3950 950  3950 1050
Wire Wire Line
	3950 1350 3700 1350
Wire Wire Line
	3700 1350 3700 1250
Connection ~ 3700 1250
Wire Wire Line
	4300 1350 3950 1350
Connection ~ 3950 1350
$Comp
L device:R R?
U 1 1 5A82B8AC
P 4300 1600
F 0 "R?" H 4230 1554 50  0000 R CNN
F 1 "60k" H 4230 1645 50  0000 R CNN
F 2 "" V 4230 1600 50  0001 C CNN
F 3 "" H 4300 1600 50  0001 C CNN
	1    4300 1600
	-1   0    0    1   
$EndComp
$Comp
L device:R R?
U 1 1 5A82B91F
P 4550 1600
F 0 "R?" H 4480 1554 50  0000 R CNN
F 1 "100k" H 4480 1645 50  0000 R CNN
F 2 "" V 4480 1600 50  0001 C CNN
F 3 "" H 4550 1600 50  0001 C CNN
	1    4550 1600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A82B95A
P 4550 1850
F 0 "#PWR?" H 4550 1600 50  0001 C CNN
F 1 "GND" H 4555 1677 50  0000 C CNN
F 2 "" H 4550 1850 50  0001 C CNN
F 3 "" H 4550 1850 50  0001 C CNN
	1    4550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1750 4550 1800
Wire Wire Line
	4550 1450 4450 1450
Wire Wire Line
	4400 1450 4400 1750
Wire Wire Line
	4400 1750 4300 1750
Wire Wire Line
	4300 1450 4100 1450
Connection ~ 4100 1450
Wire Wire Line
	4450 1150 4450 1450
Connection ~ 4450 1450
Wire Wire Line
	4450 1450 4400 1450
Wire Wire Line
	5350 850  5350 950 
Wire Wire Line
	5350 950  5350 1050
Connection ~ 5350 950 
Wire Wire Line
	5350 1050 5350 1150
Connection ~ 5350 1050
Wire Wire Line
	5350 1150 5350 1800
Wire Wire Line
	5350 1800 4550 1800
Connection ~ 5350 1150
Connection ~ 4550 1800
Wire Wire Line
	4550 1800 4550 1850
$Comp
L interface:SN65HVD235 U?
U 1 1 5A82CB78
P 1650 3450
F 0 "U?" H 1650 3928 50  0000 C CNN
F 1 "SN65HVD235" H 1650 3837 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 1650 2950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn65hvd234.pdf" H 1550 3850 50  0001 C CNN
	1    1650 3450
	1    0    0    -1  
$EndComp
Text GLabel 1250 3350 0    60   Input ~ 0
CAN_TX
Text GLabel 1250 3450 0    60   Output ~ 0
CAN_RX
$Comp
L power:+3V3 #PWR?
U 1 1 5A82CC5F
P 5500 5550
F 0 "#PWR?" H 5500 5400 50  0001 C CNN
F 1 "+3V3" H 5515 5723 50  0000 C CNN
F 2 "" H 5500 5550 50  0001 C CNN
F 3 "" H 5500 5550 50  0001 C CNN
	1    5500 5550
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 5A82CC8E
P 1100 3800
F 0 "R?" H 1030 3754 50  0000 R CNN
F 1 "10k" H 1030 3845 50  0000 R CNN
F 2 "" V 1030 3800 50  0001 C CNN
F 3 "" H 1100 3800 50  0001 C CNN
	1    1100 3800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A82CCE7
P 1650 4100
F 0 "#PWR?" H 1650 3850 50  0001 C CNN
F 1 "GND" H 1655 3927 50  0000 C CNN
F 2 "" H 1650 4100 50  0001 C CNN
F 3 "" H 1650 4100 50  0001 C CNN
	1    1650 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3850 1650 4000
Wire Wire Line
	1650 4000 1100 4000
Wire Wire Line
	1100 4000 1100 3950
Connection ~ 1650 4000
Wire Wire Line
	1650 4000 1650 4100
Wire Wire Line
	1100 3650 1250 3650
$Comp
L device:C C?
U 1 1 5A82D8E9
P 1500 2950
F 0 "C?" V 1248 2950 50  0000 C CNN
F 1 "0.1u" V 1339 2950 50  0000 C CNN
F 2 "" H 1538 2800 50  0001 C CNN
F 3 "" H 1500 2950 50  0001 C CNN
	1    1500 2950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A82D954
P 1250 2950
F 0 "#PWR?" H 1250 2700 50  0001 C CNN
F 1 "GND" H 1255 2777 50  0000 C CNN
F 2 "" H 1250 2950 50  0001 C CNN
F 3 "" H 1250 2950 50  0001 C CNN
	1    1250 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2800 1650 2950
Wire Wire Line
	1650 2950 1650 3150
Connection ~ 1650 2950
Wire Wire Line
	1350 2950 1250 2950
Text GLabel 2050 3450 2    60   BiDi ~ 0
CAN+
Text GLabel 2050 3550 2    60   BiDi ~ 0
CAN-
Text Notes 10000 1150 0    60   ~ 0
* Cellular Radio\n* GPS Module\n* ? WIFI\n* ? Bluetooth
$Comp
L rfcom:ESP-12E U?
U 1 1 5A82F032
P 8500 1850
F 0 "U?" H 8500 3128 50  0000 C CNN
F 1 "ESP-12E" H 8500 3037 50  0000 C CNN
F 2 "RF_Modules:ESP-12E" H 8500 2100 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/docs/aithinker_esp_12f_datasheet_en.pdf" H 8150 2150 50  0001 C CNN
	1    8500 1850
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear-gps:FGPMMOPA6H U?
U 1 1 5A82F4C6
P 9400 4550
F 0 "U?" H 9000 5387 60  0000 C CNN
F 1 "FGPMMOPA6H" H 9000 5281 60  0000 C CNN
F 2 "" H 9000 5150 60  0000 C CNN
F 3 "" H 9000 5150 60  0000 C CNN
	1    9400 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A82F61C
P 7750 4300
F 0 "#PWR?" H 7750 4050 50  0001 C CNN
F 1 "GND" V 7755 4172 50  0000 R CNN
F 2 "" H 7750 4300 50  0001 C CNN
F 3 "" H 7750 4300 50  0001 C CNN
	1    7750 4300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A82F641
P 9750 4200
F 0 "#PWR?" H 9750 3950 50  0001 C CNN
F 1 "GND" V 9755 4072 50  0000 R CNN
F 2 "" H 9750 4200 50  0001 C CNN
F 3 "" H 9750 4200 50  0001 C CNN
	1    9750 4200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A82F697
P 8250 4800
F 0 "#PWR?" H 8250 4550 50  0001 C CNN
F 1 "GND" V 8255 4672 50  0000 R CNN
F 2 "" H 8250 4800 50  0001 C CNN
F 3 "" H 8250 4800 50  0001 C CNN
	1    8250 4800
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5A82F7A5
P 8200 4100
F 0 "#PWR?" H 8200 3950 50  0001 C CNN
F 1 "+3V3" H 8215 4273 50  0000 C CNN
F 2 "" H 8200 4100 50  0001 C CNN
F 3 "" H 8200 4100 50  0001 C CNN
	1    8200 4100
	1    0    0    -1  
$EndComp
$Comp
L device:C C?
U 1 1 5A82F879
P 7950 4100
F 0 "C?" V 7698 4100 50  0000 C CNN
F 1 "0.1u" V 7789 4100 50  0000 C CNN
F 2 "" H 7988 3950 50  0001 C CNN
F 3 "" H 7950 4100 50  0001 C CNN
	1    7950 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 4100 7750 4100
Wire Wire Line
	7750 4100 7750 4300
Wire Wire Line
	8100 4100 8200 4100
Wire Wire Line
	8300 4100 8200 4100
Connection ~ 8200 4100
Wire Wire Line
	8300 4300 7750 4300
Connection ~ 7750 4300
Wire Wire Line
	8300 4800 8250 4800
Wire Wire Line
	9700 4200 9750 4200
$Comp
L device:Battery_Cell BT?
U 1 1 5A83239F
P 3500 2750
F 0 "BT?" H 3618 2846 50  0000 L CNN
F 1 "Battery_Cell" H 3618 2755 50  0000 L CNN
F 2 "" V 3500 2810 50  0001 C CNN
F 3 "" V 3500 2810 50  0001 C CNN
	1    3500 2750
	1    0    0    -1  
$EndComp
$Comp
L device:CP C?
U 1 1 5A832428
P 3800 2700
F 0 "C?" H 3918 2746 50  0000 L CNN
F 1 "1u" H 3918 2655 50  0000 L CNN
F 2 "" H 3838 2550 50  0001 C CNN
F 3 "" H 3800 2700 50  0001 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2550 3650 2550
Wire Wire Line
	3500 2850 3650 2850
$Comp
L power:GND #PWR?
U 1 1 5A833548
P 3650 2850
F 0 "#PWR?" H 3650 2600 50  0001 C CNN
F 1 "GND" H 3655 2677 50  0000 C CNN
F 2 "" H 3650 2850 50  0001 C CNN
F 3 "" H 3650 2850 50  0001 C CNN
	1    3650 2850
	1    0    0    -1  
$EndComp
Connection ~ 3650 2850
Wire Wire Line
	3650 2850 3800 2850
$Comp
L power:+BACKUP #PWR?
U 1 1 5A834BFA
P 3650 2500
F 0 "#PWR?" H 3650 2350 50  0001 C CNN
F 1 "+BACKUP" H 3665 2673 50  0000 C CNN
F 2 "" H 3650 2500 50  0001 C CNN
F 3 "" H 3650 2500 50  0001 C CNN
	1    3650 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+BACKUP #PWR?
U 1 1 5A834C66
P 8000 4500
F 0 "#PWR?" H 8000 4350 50  0001 C CNN
F 1 "+BACKUP" V 8015 4627 50  0000 L CNN
F 2 "" H 8000 4500 50  0001 C CNN
F 3 "" H 8000 4500 50  0001 C CNN
	1    8000 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8000 4500 8100 4500
Wire Wire Line
	8100 4500 8100 4400
Wire Wire Line
	8100 4400 8300 4400
Wire Wire Line
	3650 2500 3650 2550
Connection ~ 3650 2550
Wire Wire Line
	3650 2550 3800 2550
Text GLabel 8300 4900 0    60   Output ~ 0
GPS_OUT
Text GLabel 8300 5000 0    60   Input ~ 0
GPS_IN
$Comp
L coddingtonbear:SIM800L_5-pin U?
U 1 1 5A836AD0
P 9800 6000
F 0 "U?" H 9800 6347 60  0000 C CNN
F 1 "SIM800L_5-pin" H 9800 6241 60  0000 C CNN
F 2 "" H 9800 6000 60  0001 C CNN
F 3 "" H 9800 6000 60  0001 C CNN
	1    9800 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5A836BFA
P 10250 5900
F 0 "#PWR?" H 10250 5750 50  0001 C CNN
F 1 "+BATT" H 10265 6073 50  0000 C CNN
F 2 "" H 10250 5900 50  0001 C CNN
F 3 "" H 10250 5900 50  0001 C CNN
	1    10250 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A836CA9
P 10250 6000
F 0 "#PWR?" H 10250 5750 50  0001 C CNN
F 1 "GND" H 10255 5827 50  0000 C CNN
F 2 "" H 10250 6000 50  0001 C CNN
F 3 "" H 10250 6000 50  0001 C CNN
	1    10250 6000
	1    0    0    -1  
$EndComp
Text GLabel 9350 5900 0    60   Output ~ 0
CELLULAR_OUT
Text GLabel 9350 6000 0    60   Input ~ 0
CELLULAR_IN
Text GLabel 9350 6100 0    60   Input ~ 0
CELLULAR_RST
Text GLabel 8300 4200 0    60   Input ~ 0
GPS_RST
$Comp
L itead:ITEAD_HC-05 U?
U 1 1 5A83937D
P 5500 6500
F 0 "U?" H 5500 7756 60  0000 C CNN
F 1 "ITEAD_HC-05" H 5500 7650 60  0000 C CNN
F 2 "" H 5500 6500 60  0000 C CNN
F 3 "/home/walter/Documenti/Elettronica/DATA_SHEET/Elettronici/Ibridi/ITEAD_HC-05.pdf" H 5500 7544 60  0000 C CNN
	1    5500 6500
	1    0    0    -1  
$EndComp
Text GLabel 4900 6150 0    60   Output ~ 0
BT_OUT
Text GLabel 4900 6050 0    60   Input ~ 0
BT_IN
$Comp
L device:R R?
U 1 1 5A86C3B1
P 6350 7000
F 0 "R?" V 6557 7000 50  0000 C CNN
F 1 "330" V 6466 7000 50  0000 C CNN
F 2 "" V 6280 7000 50  0001 C CNN
F 3 "" H 6350 7000 50  0001 C CNN
	1    6350 7000
	0    -1   -1   0   
$EndComp
$Comp
L device:R R?
U 1 1 5A86C44C
P 6350 7200
F 0 "R?" V 6557 7200 50  0000 C CNN
F 1 "330" V 6466 7200 50  0000 C CNN
F 2 "" V 6280 7200 50  0001 C CNN
F 3 "" H 6350 7200 50  0001 C CNN
	1    6350 7200
	0    -1   -1   0   
$EndComp
$Comp
L device:R R?
U 1 1 5A86C485
P 6350 7450
F 0 "R?" V 6557 7450 50  0000 C CNN
F 1 "10k" V 6466 7450 50  0000 C CNN
F 2 "" V 6280 7450 50  0001 C CNN
F 3 "" H 6350 7450 50  0001 C CNN
	1    6350 7450
	0    -1   -1   0   
$EndComp
Text GLabel 6550 7200 2    60   Input ~ 0
BT_KEY
Text GLabel 6550 7000 2    60   Output ~ 0
BOOT0
Wire Wire Line
	6200 7000 6100 7000
Wire Wire Line
	6200 7200 6150 7200
Wire Wire Line
	6500 7200 6550 7200
Wire Wire Line
	6550 7000 6500 7000
Wire Wire Line
	6200 7450 6150 7450
Wire Wire Line
	6150 7450 6150 7200
Connection ~ 6150 7200
Wire Wire Line
	6150 7200 6100 7200
$Comp
L power:GND #PWR?
U 1 1 5A870600
P 6650 7450
F 0 "#PWR?" H 6650 7200 50  0001 C CNN
F 1 "GND" H 6655 7277 50  0000 C CNN
F 2 "" H 6650 7450 50  0001 C CNN
F 3 "" H 6650 7450 50  0001 C CNN
	1    6650 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 7450 6500 7450
$Comp
L power:GND #PWR?
U 1 1 5A87158C
P 5500 7550
F 0 "#PWR?" H 5500 7300 50  0001 C CNN
F 1 "GND" H 5505 7377 50  0000 C CNN
F 2 "" H 5500 7550 50  0001 C CNN
F 3 "" H 5500 7550 50  0001 C CNN
	1    5500 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 7450 5500 7450
Wire Wire Line
	5600 7450 5500 7450
Connection ~ 5500 7450
Wire Wire Line
	5500 7450 5500 7550
$EndSCHEMATC
