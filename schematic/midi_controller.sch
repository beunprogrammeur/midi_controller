EESchema Schematic File Version 4
EELAYER 30 0
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
$Comp
L Device:R_POT RV?
U 1 1 5EB68074
P 8000 3850
F 0 "RV?" H 7900 4100 50  0000 R CNN
F 1 "R_POT" H 7900 3600 50  0000 R CNN
F 2 "" H 8000 3850 50  0001 C CNN
F 3 "~" H 8000 3850 50  0001 C CNN
	1    8000 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV?
U 1 1 5EB691D3
P 7500 3850
F 0 "RV?" H 7400 4100 50  0000 R CNN
F 1 "R_POT" H 7400 3600 50  0000 R CNN
F 2 "" H 7500 3850 50  0001 C CNN
F 3 "~" H 7500 3850 50  0001 C CNN
	1    7500 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV?
U 1 1 5EB6932C
P 7000 3850
F 0 "RV?" H 6900 4100 50  0000 R CNN
F 1 "R_POT" H 6900 3600 50  0000 R CNN
F 2 "" H 7000 3850 50  0001 C CNN
F 3 "~" H 7000 3850 50  0001 C CNN
	1    7000 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV?
U 1 1 5EB69488
P 8500 3850
F 0 "RV?" H 8400 4100 50  0000 R CNN
F 1 "R_POT" H 8400 3600 50  0000 R CNN
F 2 "" H 8500 3850 50  0001 C CNN
F 3 "~" H 8500 3850 50  0001 C CNN
	1    8500 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV?
U 1 1 5EB69670
P 9000 3850
F 0 "RV?" H 8900 4100 50  0000 R CNN
F 1 "R_POT" H 8950 3600 50  0000 R CNN
F 2 "" H 9000 3850 50  0001 C CNN
F 3 "~" H 9000 3850 50  0001 C CNN
	1    9000 3850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 5EB6AE39
P 2150 1850
F 0 "J?" H 2258 2131 50  0000 C CNN
F 1 "OLED_CONN" H 2258 2040 50  0000 C CNN
F 2 "" H 2150 1850 50  0001 C CNN
F 3 "~" H 2150 1850 50  0001 C CNN
	1    2150 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J?
U 1 1 5EB6F7D6
P 4400 3250
F 0 "J?" H 4480 3242 50  0000 L CNN
F 1 "stm32_header_L" H 4150 2100 50  0000 L CNN
F 2 "" H 4400 3250 50  0001 C CNN
F 3 "~" H 4400 3250 50  0001 C CNN
	1    4400 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J?
U 1 1 5EB73A0C
P 5500 3250
F 0 "J?" H 5580 3242 50  0000 L CNN
F 1 "stm32_header_R" H 5250 2100 50  0000 L CNN
F 2 "" H 5500 3250 50  0001 C CNN
F 3 "~" H 5500 3250 50  0001 C CNN
	1    5500 3250
	1    0    0    -1  
$EndComp
Wire Notes Line
	6350 1850 6350 4750
Wire Notes Line
	6350 4750 3350 4750
Wire Notes Line
	3350 4750 3350 1850
Wire Notes Line
	3350 1850 6350 1850
Text GLabel 5300 2350 0    50   Input ~ 0
GND
Text GLabel 5300 2550 0    50   Input ~ 0
3V3
Text GLabel 5300 2450 0    50   Input ~ 0
GND
Text GLabel 5300 3850 0    50   Input ~ 0
POT1
Text GLabel 5300 3750 0    50   Input ~ 0
POT2
Text GLabel 5300 3650 0    50   Input ~ 0
POT3
Text GLabel 5300 3550 0    50   Input ~ 0
POT4
Text GLabel 5300 3450 0    50   Input ~ 0
POT5
Text GLabel 7150 3850 2    50   Input ~ 0
POT1
Text GLabel 7650 3850 2    50   Input ~ 0
POT2
Text GLabel 8150 3850 2    50   Input ~ 0
POT3
Text GLabel 8650 3850 2    50   Input ~ 0
POT4
Text GLabel 9150 3850 2    50   Input ~ 0
POT5
Wire Wire Line
	9000 3700 8500 3700
Wire Wire Line
	8000 3700 8500 3700
Connection ~ 8500 3700
Wire Wire Line
	8000 3700 7500 3700
Connection ~ 8000 3700
Wire Wire Line
	7000 3700 7500 3700
Connection ~ 7500 3700
Wire Wire Line
	7000 4000 7500 4000
Wire Wire Line
	7500 4000 8000 4000
Connection ~ 7500 4000
Wire Wire Line
	8000 4000 8500 4000
Connection ~ 8000 4000
Wire Wire Line
	8500 4000 9000 4000
Connection ~ 8500 4000
Text GLabel 8000 3550 1    50   Input ~ 0
3V3
Text GLabel 8000 4150 3    50   Input ~ 0
GND
Wire Wire Line
	8000 3550 8000 3700
Wire Wire Line
	8000 4000 8000 4150
Text GLabel 2350 1950 2    50   Input ~ 0
3V3
Text GLabel 2350 2050 2    50   Input ~ 0
GND
Text GLabel 2350 1750 2    50   Input ~ 0
OLED_SDA
Text GLabel 2350 1850 2    50   Input ~ 0
OLED_SCK
Text GLabel 4200 3750 0    50   Input ~ 0
OLED_SDA
Text GLabel 4200 3650 0    50   Input ~ 0
OLED_SCK
Text GLabel 4200 2350 0    50   Input ~ 0
BUT_CC_UP
Text GLabel 4200 2450 0    50   Input ~ 0
BUT_CC_DOWN
Text GLabel 4200 2550 0    50   Input ~ 0
BUT_CH_UP
Text GLabel 4200 2650 0    50   Input ~ 0
BUT_CC_DOWN
$Comp
L Switch:SW_Push SW?
U 1 1 5EC06172
P 8600 2700
F 0 "SW?" V 8554 2848 50  0000 L CNN
F 1 "SW_Push" V 8645 2848 50  0000 L CNN
F 2 "" H 8600 2900 50  0001 C CNN
F 3 "~" H 8600 2900 50  0001 C CNN
	1    8600 2700
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5EC08B64
P 7000 2700
F 0 "SW?" V 6954 2848 50  0000 L CNN
F 1 "SW_Push" V 7045 2848 50  0000 L CNN
F 2 "" H 7000 2900 50  0001 C CNN
F 3 "~" H 7000 2900 50  0001 C CNN
	1    7000 2700
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5EC09100
P 8050 2700
F 0 "SW?" V 8004 2848 50  0000 L CNN
F 1 "SW_Push" V 8095 2848 50  0000 L CNN
F 2 "" H 8050 2900 50  0001 C CNN
F 3 "~" H 8050 2900 50  0001 C CNN
	1    8050 2700
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5EC0F888
P 7500 2700
F 0 "SW?" V 7454 2848 50  0000 L CNN
F 1 "SW_Push" V 7545 2848 50  0000 L CNN
F 2 "" H 7500 2900 50  0001 C CNN
F 3 "~" H 7500 2900 50  0001 C CNN
	1    7500 2700
	0    1    1    0   
$EndComp
Text GLabel 7000 2500 1    50   Input ~ 0
BUT_CC_UP
Text GLabel 7500 2500 1    50   Input ~ 0
BUT_CC_DOWN
Text GLabel 8050 2500 1    50   Input ~ 0
BUT_CH_UP
Text GLabel 8600 2500 1    50   Input ~ 0
BUT_CC_DOWN
Wire Wire Line
	7000 2900 7000 3000
Wire Wire Line
	7000 3000 7500 3000
Wire Wire Line
	7500 3000 7500 2900
Wire Wire Line
	8600 2900 8600 3000
Wire Wire Line
	8600 3000 8050 3000
Wire Wire Line
	8050 2900 8050 3000
Wire Wire Line
	8050 3000 7800 3000
Connection ~ 8050 3000
Connection ~ 7500 3000
Text GLabel 7800 3100 3    50   Input ~ 0
GND
Wire Wire Line
	7800 3000 7800 3100
Connection ~ 7800 3000
Wire Wire Line
	7800 3000 7500 3000
Wire Notes Line
	6550 1850 6550 4750
Wire Notes Line
	6550 4750 9500 4750
Wire Notes Line
	9500 4750 9500 1850
Wire Notes Line
	9500 1850 6550 1850
Text Notes 6600 4700 0    50   ~ 0
inputs
Text Notes 3400 4700 0    50   ~ 0
microcontroller headers
$EndSCHEMATC
