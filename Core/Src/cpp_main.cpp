/*
 * cpp_main.cpp
 *
 *  Created on: May 4, 2020
 *      Author: vincent
 */

#include "cpp_main.h"
#include "gpio.h"
#include "usbd_midi_if.h"

void cpp_main()
{
	  uint8_t pressNote[] = {0x08, 0x90, 0x3c, 0x64};
	  uint8_t releaseNote[] = {0x08, 0x80, 0x3c, 0x64};
	while(true)
	{
		  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		  HAL_Delay(500);
		  MIDI_Transmit(pressNote, 4);
		  HAL_Delay(500);
		  MIDI_Transmit(releaseNote, 4);
	}
}
