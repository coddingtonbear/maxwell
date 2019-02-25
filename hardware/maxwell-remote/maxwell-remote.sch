EESchema Schematic File Version 4
LIBS:maxwell-remote-cache
LIBS:maxwell-remote-2-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 8800 2550 2    60   BiDi ~ 0
WAKE
Text GLabel 1900 4400 0    60   BiDi ~ 0
WAKE
Text GLabel 7800 2250 3    60   Output ~ 0
~RIGHT_A
Text GLabel 7900 2250 3    60   Output ~ 0
~RIGHT_B
Text GLabel 6150 1800 2    60   Input ~ 0
CAN_TX
Text GLabel 2500 7050 1    60   BiDi ~ 0
BOOT0
Text GLabel 2200 3500 0    60   BiDi ~ 0
BOOT0
Text GLabel 2650 7050 1    60   BiDi ~ 0
BOOT1
Wire Wire Line
	1900 3300 1800 3300
Wire Wire Line
	2650 7350 2500 7350
Wire Wire Line
	2200 7050 2250 7050
Wire Wire Line
	3000 7050 2650 7050
Text GLabel 8300 1750 1    60   Output ~ 0
ESP_DI
Text GLabel 8300 2250 3    60   Input ~ 0
ESP_DO
Wire Wire Line
	3000 7150 3000 7500
Text GLabel 10500 4050 2    60   BiDi ~ 0
BOOT0
Text GLabel 10550 3850 2    60   Input ~ 0
ESP_DI
Text GLabel 10200 3750 2    60   Output ~ 0
ESP_DO
Wire Wire Line
	1200 3600 1200 3900
Connection ~ 1200 3900
Text GLabel 10200 4450 2    60   Input ~ 0
BT_DI
Text GLabel 10200 5550 2    60   Output ~ 0
BT_DO
Text GLabel 2200 3300 1    60   Input ~ 0
NRST
Text GLabel 10200 4750 2    60   Output ~ 0
NRST
Text GLabel 10200 4650 2    60   Input ~ 0
BT_KEY
Text GLabel 7600 1750 1    60   Input ~ 0
~SPI_CS_4
Text GLabel 7900 1750 1    60   Input ~ 0
~SCREEN_CS
Text GLabel 7800 1750 1    60   Input ~ 0
~SCREEN_RST
Text GLabel 7700 1750 1    60   Input ~ 0
SCREEN_A0
Text GLabel 5650 1700 0    50   Input ~ 0
SPI1_SCK
Text GLabel 5650 1600 0    50   Output ~ 0
SPI1_MISO
Text GLabel 5650 1500 0    50   Input ~ 0
SPI1_MOSI
Text GLabel 5650 1800 0    60   Input ~ 0
~ENABLE_SCREEN
Text GLabel 6150 1700 2    60   Output ~ 0
CAN_RX
Text GLabel 7600 2250 3    60   Output ~ 0
~LEFT_A
Text GLabel 7700 2250 3    60   Output ~ 0
~LEFT_B
Text GLabel 6150 1600 2    50   Input ~ 0
~SPI1_CS_2
Text GLabel 6150 1500 2    50   Input ~ 0
~SPI1_CS_3
Text GLabel 10200 3650 2    60   Input ~ 0
ESP_BOOT_MODE
$Comp
L MCU_ST_STM32F1:STM32F103CBTx U1
U 1 1 5C7641F0
P 2900 4600
F 0 "U1" H 2250 3000 50  0000 C CNN
F 1 "STM32F103CBTx" H 2150 2850 50  0000 C CNN
F 2 "castellated-breakouts:QFP48-1.27MM-CASTELLATED" H 2300 3200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 2900 4600 50  0001 C CNN
	1    2900 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  3900 1200 3900
Wire Wire Line
	2200 3700 1800 3700
Wire Wire Line
	1800 3700 1800 3600
Wire Wire Line
	2200 3800 1800 3800
Wire Wire Line
	1800 3800 1800 3900
Text GLabel 2200 5300 0    60   Output ~ 0
CAN_TX
Text GLabel 2200 5200 0    60   Input ~ 0
CAN_RX
Text GLabel 2200 4600 0    60   BiDi ~ 0
BOOT1
Text GLabel 2200 5600 0    60   Output ~ 0
~SPI_CS_4
Text GLabel 2200 5900 0    60   Output ~ 0
~SCREEN_CS
Text GLabel 2200 5800 0    60   Output ~ 0
~SCREEN_RST
Text GLabel 2200 5700 0    60   Output ~ 0
SCREEN_A0
Text GLabel 2200 4700 0    50   Output ~ 0
SPI1_SCK
Text GLabel 2200 4800 0    50   Input ~ 0
SPI1_MISO
Text GLabel 2200 4900 0    50   Output ~ 0
SPI1_MOSI
Text GLabel 2200 5100 0    50   Output ~ 0
~SPI1_CS_2
Text GLabel 2200 5000 0    50   Output ~ 0
~SPI1_CS_3
Wire Wire Line
	2700 6100 2800 6100
Wire Wire Line
	2800 6100 2900 6100
Connection ~ 2800 6100
Wire Wire Line
	3000 6100 2900 6100
Connection ~ 2900 6100
Wire Wire Line
	2800 6100 2800 6250
Wire Wire Line
	2900 3100 2900 2900
Wire Wire Line
	2800 2900 2800 3000
Wire Wire Line
	3000 3100 3000 2900
Wire Wire Line
	3100 2900 3100 3100
Wire Wire Line
	3500 2700 3500 2900
Wire Wire Line
	2400 2700 2400 2900
Connection ~ 2900 2700
Connection ~ 3000 2700
Wire Wire Line
	3100 2900 3000 2900
Connection ~ 3000 2900
Wire Wire Line
	3000 2900 3000 2700
Wire Wire Line
	2800 2900 2900 2900
Connection ~ 2900 2900
Wire Wire Line
	2900 2900 2900 2700
Wire Wire Line
	2700 3100 2700 3000
Wire Wire Line
	2700 3000 2800 3000
Connection ~ 2800 3000
Wire Wire Line
	2800 3000 2800 3100
Text GLabel 3500 5200 2    60   Output ~ 0
BT_KEY
Text GLabel 3500 5800 2    60   BiDi ~ 0
SWCLK
Text GLabel 3500 5700 2    60   BiDi ~ 0
SWDIO
Text GLabel 3500 5500 2    60   Output ~ 0
DISBABLE_BLUETOOTH_
Text GLabel 3500 4800 2    60   Input ~ 0
~RIGHT_B
Text GLabel 3500 4900 2    60   Input ~ 0
~RIGHT_A
Text GLabel 3500 5000 2    60   Input ~ 0
~LEFT_B
Text GLabel 3500 5100 2    60   Input ~ 0
~LEFT_A
Text GLabel 3500 5300 2    60   Output ~ 0
BT_DI
Text GLabel 3500 5400 2    60   Input ~ 0
BT_DO
Text GLabel 3500 5900 2    60   Output ~ 0
~ENABLE_SCREEN
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5C7A9724
P 2050 7150
F 0 "J1" H 1970 6825 50  0000 C CNN
F 1 "BOOT0" H 1970 6916 50  0000 C CNN
F 2 "coddingtonbear:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 2050 7150 50  0001 C CNN
F 3 "~" H 2050 7150 50  0001 C CNN
	1    2050 7150
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5C7A9816
P 3200 7050
F 0 "J2" H 3279 7042 50  0000 L CNN
F 1 "BOOT1" H 3279 6951 50  0000 L CNN
F 2 "coddingtonbear:Pin_Header_Straight_1x02_Pitch1.27mm_JMP" H 3200 7050 50  0001 C CNN
F 3 "~" H 3200 7050 50  0001 C CNN
	1    3200 7050
	1    0    0    -1  
$EndComp
Connection ~ 2250 7050
Wire Wire Line
	2250 7050 2500 7050
$Comp
L RF_Module:ESP32-WROOM-32 U2
U 1 1 5C7AD3DF
P 9600 4850
F 0 "U2" H 10250 6450 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 10500 6300 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 9600 3350 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 9300 4900 50  0001 C CNN
	1    9600 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5C7ADA61
P 10350 4050
F 0 "R8" V 10250 4300 50  0000 C CNN
F 1 "300" V 10250 4150 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 10280 4050 50  0001 C CNN
F 3 "~" H 10350 4050 50  0001 C CNN
	1    10350 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5C7AE2C0
P 8600 3650
F 0 "R7" V 8700 3650 50  0000 C CNN
F 1 "10k" V 8700 3800 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 8530 3650 50  0001 C CNN
F 3 "~" H 8600 3650 50  0001 C CNN
	1    8600 3650
	0    1    1    0   
$EndComp
$Comp
L coddingtonbear:+3V3_A #PWR0108
U 1 1 5C7AE6A6
P 8200 3650
F 0 "#PWR0108" H 8200 3500 50  0001 C CNN
F 1 "+3V3_A" H 8215 3823 50  0000 C CNN
F 2 "" H 8200 3650 50  0001 C CNN
F 3 "" H 8200 3650 50  0001 C CNN
	1    8200 3650
	1    0    0    -1  
$EndComp
Text GLabel 8750 3900 0    60   Input ~ 0
DISBABLE_BLUETOOTH_
Wire Wire Line
	8200 3650 8450 3650
Wire Wire Line
	8750 3900 8750 3650
Wire Wire Line
	9000 3650 8750 3650
Connection ~ 8750 3650
$Comp
L Device:C_Small C7
U 1 1 5C7B4726
P 9500 3350
F 0 "C7" V 9271 3350 50  0000 C CNN
F 1 "0.1u" V 9362 3350 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 9500 3350 50  0001 C CNN
F 3 "~" H 9500 3350 50  0001 C CNN
	1    9500 3350
	0    1    1    0   
$EndComp
$Comp
L coddingtonbear:+3V3_A #PWR0109
U 1 1 5C7B49D3
P 9600 3150
F 0 "#PWR0109" H 9600 3000 50  0001 C CNN
F 1 "+3V3_A" H 9615 3323 50  0000 C CNN
F 2 "" H 9600 3150 50  0001 C CNN
F 3 "" H 9600 3150 50  0001 C CNN
	1    9600 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 3150 9600 3350
Wire Wire Line
	9600 3450 9600 3350
Connection ~ 9600 3350
Wire Wire Line
	9400 3350 9300 3350
$Comp
L Device:R R4
U 1 1 5C7C0F20
P 2650 7200
F 0 "R4" V 2750 7200 50  0000 C CNN
F 1 "100k" V 2750 7350 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 2580 7200 50  0001 C CNN
F 3 "~" H 2650 7200 50  0001 C CNN
	1    2650 7200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 5C7C124C
P 2500 7200
F 0 "R3" V 2600 7200 50  0000 C CNN
F 1 "100k" V 2600 7350 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 2430 7200 50  0001 C CNN
F 3 "~" H 2500 7200 50  0001 C CNN
	1    2500 7200
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5C7C4366
P 1400 3600
F 0 "C1" V 1171 3600 50  0000 C CNN
F 1 "22p" V 1262 3600 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 1400 3600 50  0001 C CNN
F 3 "~" H 1400 3600 50  0001 C CNN
	1    1400 3600
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5C7C44EC
P 1400 3900
F 0 "C2" V 1171 3900 50  0000 C CNN
F 1 "22p" V 1262 3900 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 1400 3900 50  0001 C CNN
F 3 "~" H 1400 3900 50  0001 C CNN
	1    1400 3900
	0    1    1    0   
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5C7C45F4
P 1550 3750
F 0 "Y1" V 1504 3881 50  0000 L CNN
F 1 "8M" V 1595 3881 50  0000 L CNN
F 2 "coddingtonbear:Abracon-ABM2_LargePads" H 1550 3750 50  0001 C CNN
F 3 "~" H 1550 3750 50  0001 C CNN
	1    1550 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 3600 1550 3600
Connection ~ 1550 3600
Wire Wire Line
	1500 3900 1550 3900
Connection ~ 1550 3900
Wire Wire Line
	1200 3900 1300 3900
Wire Wire Line
	1200 3600 1300 3600
$Comp
L Device:R R1
U 1 1 5C7C9D16
P 1700 3750
F 0 "R1" V 1800 3750 50  0000 C CNN
F 1 "1M" V 1800 3900 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 1630 3750 50  0001 C CNN
F 3 "~" H 1700 3750 50  0001 C CNN
	1    1700 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	1550 3600 1700 3600
Wire Wire Line
	1550 3900 1700 3900
Connection ~ 1700 3900
Wire Wire Line
	1700 3900 1800 3900
Connection ~ 1700 3600
Wire Wire Line
	1700 3600 1800 3600
$Comp
L Device:R R2
U 1 1 5C7CA045
P 2050 3300
F 0 "R2" V 2150 3300 50  0000 C CNN
F 1 "10k" V 2150 3450 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 1980 3300 50  0001 C CNN
F 3 "~" H 2050 3300 50  0001 C CNN
	1    2050 3300
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5C7CA282
P 2650 2700
F 0 "C3" V 2421 2700 50  0000 C CNN
F 1 "0.1u" V 2512 2700 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 2650 2700 50  0001 C CNN
F 3 "~" H 2650 2700 50  0001 C CNN
	1    2650 2700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5C7CA3FA
P 2650 2900
F 0 "C4" V 2850 2850 50  0000 C CNN
F 1 "0.1u" V 2750 2850 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 2650 2900 50  0001 C CNN
F 3 "~" H 2650 2900 50  0001 C CNN
	1    2650 2900
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5C7CA43C
P 3250 2700
F 0 "C5" V 3021 2700 50  0000 C CNN
F 1 "0.1u" V 3112 2700 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 3250 2700 50  0001 C CNN
F 3 "~" H 3250 2700 50  0001 C CNN
	1    3250 2700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5C7CA496
P 3250 2900
F 0 "C6" V 3450 2900 50  0000 C CNN
F 1 "0.1u" V 3350 2900 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" H 3250 2900 50  0001 C CNN
F 3 "~" H 3250 2900 50  0001 C CNN
	1    3250 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 2700 3150 2700
Wire Wire Line
	3350 2700 3500 2700
Wire Wire Line
	3350 2900 3500 2900
Wire Wire Line
	3150 2900 3100 2900
Connection ~ 3100 2900
Wire Wire Line
	2800 2900 2750 2900
Connection ~ 2800 2900
Wire Wire Line
	2400 2900 2550 2900
Wire Wire Line
	2400 2700 2550 2700
Wire Wire Line
	2750 2700 2900 2700
$Comp
L Device:R R9
U 1 1 5C7D9065
P 10350 4150
F 0 "R9" V 10450 4150 50  0000 C CNN
F 1 "300" V 10450 4300 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 10280 4150 50  0001 C CNN
F 3 "~" H 10350 4150 50  0001 C CNN
	1    10350 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	10200 3950 10300 3950
Wire Wire Line
	10300 3950 10300 3850
Wire Wire Line
	10300 3850 10550 3850
Text GLabel 10500 4150 2    60   Output ~ 0
ESP_AVAILABLE
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J5
U 1 1 5C7DC06F
P 5850 1800
F 0 "J5" H 5900 2317 50  0000 C CNN
F 1 "Lower-Left" H 5900 2226 50  0000 C CNN
F 2 "coddingtonbear:PinHeader_2x08_P2.54mm_Vertical_LargePads" H 5850 1800 50  0001 C CNN
F 3 "~" H 5850 1800 50  0001 C CNN
	1    5850 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J7
U 1 1 5C7DC1BB
P 7900 2050
F 0 "J7" V 7996 1562 50  0000 R CNN
F 1 "Lower-Right" V 7905 1562 50  0000 R CNN
F 2 "coddingtonbear:PinHeader_2x08_P2.54mm_Vertical_LargePads" H 7900 2050 50  0001 C CNN
F 3 "~" H 7900 2050 50  0001 C CNN
	1    7900 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 2700 2950 2700
$Comp
L coddingtonbear:+3V3_A #PWR0101
U 1 1 5C7E1601
P 2950 2700
F 0 "#PWR0101" H 2950 2550 50  0001 C CNN
F 1 "+3V3_A" H 2965 2873 50  0000 C CNN
F 2 "" H 2950 2700 50  0001 C CNN
F 3 "" H 2950 2700 50  0001 C CNN
	1    2950 2700
	1    0    0    -1  
$EndComp
Connection ~ 2950 2700
Wire Wire Line
	2950 2700 3000 2700
$Comp
L coddingtonbear:+3V3_A #PWR0104
U 1 1 5C7E1642
P 1800 3300
F 0 "#PWR0104" H 1800 3150 50  0001 C CNN
F 1 "+3V3_A" H 1815 3473 50  0000 C CNN
F 2 "" H 1800 3300 50  0001 C CNN
F 3 "" H 1800 3300 50  0001 C CNN
	1    1800 3300
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_A #PWR0106
U 1 1 5C7E4D34
P 1650 7450
F 0 "#PWR0106" H 1650 7300 50  0001 C CNN
F 1 "+3V3_A" H 1665 7623 50  0000 C CNN
F 2 "" H 1650 7450 50  0001 C CNN
F 3 "" H 1650 7450 50  0001 C CNN
	1    1650 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 7500 2250 7500
Wire Wire Line
	2250 7500 2250 7150
Wire Wire Line
	1650 7450 1650 7500
Wire Wire Line
	1650 7500 2250 7500
Connection ~ 2250 7500
$Comp
L coddingtonbear:GND_A #PWR0107
U 1 1 5C7EA44F
P 9600 6250
F 0 "#PWR0107" H 9600 6000 50  0001 C CNN
F 1 "GND_A" H 9605 6077 50  0000 C CNN
F 2 "" H 9600 6250 50  0001 C CNN
F 3 "" H 9600 6250 50  0001 C CNN
	1    9600 6250
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0112
U 1 1 5C7EA586
P 9300 3350
F 0 "#PWR0112" H 9300 3100 50  0001 C CNN
F 1 "GND_A" H 9305 3177 50  0000 C CNN
F 2 "" H 9300 3350 50  0001 C CNN
F 3 "" H 9300 3350 50  0001 C CNN
	1    9300 3350
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0114
U 1 1 5C7EA8E5
P 2650 7350
F 0 "#PWR0114" H 2650 7100 50  0001 C CNN
F 1 "GND_A" H 2655 7177 50  0000 C CNN
F 2 "" H 2650 7350 50  0001 C CNN
F 3 "" H 2650 7350 50  0001 C CNN
	1    2650 7350
	1    0    0    -1  
$EndComp
Connection ~ 2650 7350
$Comp
L coddingtonbear:GND_A #PWR0115
U 1 1 5C7EAA33
P 2800 6250
F 0 "#PWR0115" H 2800 6000 50  0001 C CNN
F 1 "GND_A" H 2805 6077 50  0000 C CNN
F 2 "" H 2800 6250 50  0001 C CNN
F 3 "" H 2800 6250 50  0001 C CNN
	1    2800 6250
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0116
U 1 1 5C7EAC2D
P 750 3900
F 0 "#PWR0116" H 750 3650 50  0001 C CNN
F 1 "GND_A" H 755 3727 50  0000 C CNN
F 2 "" H 750 3900 50  0001 C CNN
F 3 "" H 750 3900 50  0001 C CNN
	1    750  3900
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0117
U 1 1 5C7EAC6C
P 2400 2900
F 0 "#PWR0117" H 2400 2650 50  0001 C CNN
F 1 "GND_A" H 2405 2727 50  0000 C CNN
F 2 "" H 2400 2900 50  0001 C CNN
F 3 "" H 2400 2900 50  0001 C CNN
	1    2400 2900
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0118
U 1 1 5C7EACAB
P 3500 2900
F 0 "#PWR0118" H 3500 2650 50  0001 C CNN
F 1 "GND_A" H 3505 2727 50  0000 C CNN
F 2 "" H 3500 2900 50  0001 C CNN
F 3 "" H 3500 2900 50  0001 C CNN
	1    3500 2900
	1    0    0    -1  
$EndComp
Connection ~ 2400 2900
Connection ~ 3500 2900
$Sheet
S 1000 600  1100 700 
U 5C7FBF3C
F0 "upper" 50
F1 "upper.sch" 50
$EndSheet
Text GLabel 5650 1900 0    50   Output ~ 0
SWCLK
Text GLabel 5650 2000 0    50   BiDi ~ 0
SWDIO
$Comp
L coddingtonbear:GND_A #PWR0119
U 1 1 5C812203
P 8000 2250
F 0 "#PWR0119" H 8000 2000 50  0001 C CNN
F 1 "GND_A" H 8005 2077 50  0000 C CNN
F 2 "" H 8000 2250 50  0001 C CNN
F 3 "" H 8000 2250 50  0001 C CNN
	1    8000 2250
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0120
U 1 1 5C812241
P 7950 900
F 0 "#PWR0120" H 7950 650 50  0001 C CNN
F 1 "GND_A" H 7955 727 50  0000 C CNN
F 2 "" H 7950 900 50  0001 C CNN
F 3 "" H 7950 900 50  0001 C CNN
	1    7950 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 1750 8000 900 
Wire Wire Line
	8000 900  7950 900 
$Comp
L coddingtonbear:+3V3_A #PWR0121
U 1 1 5C813492
P 8200 2850
F 0 "#PWR0121" H 8200 2700 50  0001 C CNN
F 1 "+3V3_A" H 8215 3023 50  0000 C CNN
F 2 "" H 8200 2850 50  0001 C CNN
F 3 "" H 8200 2850 50  0001 C CNN
	1    8200 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2250 8100 2850
Wire Wire Line
	8100 2850 8200 2850
$Comp
L coddingtonbear:GND_A #PWR0123
U 1 1 5C8161D8
P 6500 2100
F 0 "#PWR0123" H 6500 1850 50  0001 C CNN
F 1 "GND_A" H 6505 1927 50  0000 C CNN
F 2 "" H 6500 2100 50  0001 C CNN
F 3 "" H 6500 2100 50  0001 C CNN
	1    6500 2100
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:+3V3_A #PWR0124
U 1 1 5C81620F
P 5100 2350
F 0 "#PWR0124" H 5100 2200 50  0001 C CNN
F 1 "+3V3_A" H 5115 2523 50  0000 C CNN
F 2 "" H 5100 2350 50  0001 C CNN
F 3 "" H 5100 2350 50  0001 C CNN
	1    5100 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1900 6500 1900
Wire Wire Line
	6500 1900 6500 2000
Wire Wire Line
	6150 2100 6500 2100
Connection ~ 6500 2100
Wire Wire Line
	6150 2000 6500 2000
Connection ~ 6500 2000
Wire Wire Line
	6500 2000 6500 2100
Wire Wire Line
	6150 2200 6150 2350
Wire Wire Line
	6150 2350 5650 2350
Wire Wire Line
	5650 2200 5650 2350
Connection ~ 5650 2350
Wire Wire Line
	5650 2350 5500 2350
Wire Wire Line
	5650 2100 5500 2100
Wire Wire Line
	5500 2100 5500 2350
Connection ~ 5500 2350
Wire Wire Line
	5500 2350 5100 2350
$Comp
L Device:CP C8
U 1 1 5C820FDB
P 7250 3900
F 0 "C8" H 7368 3946 50  0000 L CNN
F 1 "220u" H 7368 3855 50  0000 L CNN
F 2 "coddingtonbear:CP_Tantalum_Case-C_EIA-6032-28_Milling" H 7288 3750 50  0001 C CNN
F 3 "~" H 7250 3900 50  0001 C CNN
	1    7250 3900
	1    0    0    -1  
$EndComp
$Comp
L coddingtonbear:GND_A #PWR0102
U 1 1 5C82111D
P 7250 4050
F 0 "#PWR0102" H 7250 3800 50  0001 C CNN
F 1 "GND_A" H 7255 3877 50  0000 C CNN
F 2 "" H 7250 4050 50  0001 C CNN
F 3 "" H 7250 4050 50  0001 C CNN
	1    7250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3650 7250 3650
Wire Wire Line
	7250 3650 7250 3750
Connection ~ 8200 3650
$Comp
L coddingtonbear:+3V3_A #PWR0103
U 1 1 5C82355D
P 8100 1750
F 0 "#PWR0103" H 8100 1600 50  0001 C CNN
F 1 "+3V3_A" H 8115 1923 50  0000 C CNN
F 2 "" H 8100 1750 50  0001 C CNN
F 3 "" H 8100 1750 50  0001 C CNN
	1    8100 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5C83D186
P 2050 4400
F 0 "R10" V 1950 4450 50  0000 C CNN
F 1 "300" V 1950 4300 50  0000 C CNN
F 2 "coddingtonbear:0805_Milling" V 1980 4400 50  0001 C CNN
F 3 "~" H 2050 4400 50  0001 C CNN
	1    2050 4400
	0    1    1    0   
$EndComp
Text GLabel 8800 2450 2    60   Input ~ 0
ESP_AVAILABLE
Wire Wire Line
	8200 2250 8200 2700
Wire Wire Line
	8200 2700 8600 2700
Wire Wire Line
	8600 2700 8600 2550
Wire Wire Line
	8600 2550 8800 2550
Wire Wire Line
	8800 2450 8600 2450
Wire Wire Line
	8600 2450 8600 2550
Connection ~ 8600 2550
Text GLabel 8200 1750 1    50   Output ~ 0
ESP_BOOT_MODE
$EndSCHEMATC
