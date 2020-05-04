/*
 * cpp_main.cpp
 *
 *  Created on: May 4, 2020
 *      Author: vincent
 */

#include "cpp_main.h"
#include "gpio.h"
#include "usbd_midi_if.h"
#include "adc.h"
#include "tim.h"

#include "midi/control_change.h"

template<typename T>
void MIDI_SendPacket(T& packet)
{
	MIDI_TransmitData((uint8_t*)&packet, sizeof(T));
}


int32_t map(int32_t value, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint32_t adcValues[50];
volatile bool commandChanged = false;
MIDI::ControlChange command;

constexpr uint32_t ADC_MAX_OFFSET = 3900;
constexpr uint32_t ADC_MIN_OFFSET = 10;
constexpr uint32_t ADC_DELTA = ADC_MAX_OFFSET - ADC_MIN_OFFSET;
constexpr uint32_t MIDI_CC_MIN = 0;
constexpr uint32_t MIDI_CC_MAX = 127;
uint8_t ccOutput = 0;
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//
//}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		uint32_t averages[5];

		for(int i = 0; i < 5; i++)
		{
			averages[i] = 0;
			for(int j = 0; j < 50; j+=10)
			{
				averages[i] += adcValues[i+j];
			}

			averages[i] /=5;

			if(averages[i] > ADC_MAX_OFFSET)
			{
				averages[i] = ADC_MAX_OFFSET;
			}
			else if(averages[i] < ADC_MIN_OFFSET)
			{
				averages[i] = ADC_MIN_OFFSET;
			}
		}

		uint8_t newValue = map(averages[0], ADC_MIN_OFFSET, ADC_MAX_OFFSET, MIDI_CC_MIN, MIDI_CC_MAX);
		ccOutput = newValue;
		if(newValue != command.value())
		{
			command.value(newValue);
			commandChanged = true;
		}
	}
}

void cpp_main()
{
	command.channel(0);
	command.cc(0x0a);
	command.value(0xDE);

	HAL_ADC_Start_DMA(&hadc1, adcValues, 50); // do 10 conversions each. calc averages in the timer callback
	HAL_TIM_Base_Start_IT(&htim1);

	while(true)
	{
		if(!commandChanged)
		{
			continue;
		}

		commandChanged = false;

		MIDI_SendPacket(command);
		HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin, GPIO_PIN_SET);
	}
}
