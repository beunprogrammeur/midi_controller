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
#include "midi/note.h"


template<typename T>
void MIDI_SendPacket(T& packet)
{
	MIDI_TransmitData((uint8_t*)&packet, sizeof(T));
}


int32_t map(int32_t value, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint32_t adcValues[50];

MIDI::ControlChange commands[5] {
	MIDI::ControlChange(),
	MIDI::ControlChange(),
	MIDI::ControlChange(),
	MIDI::ControlChange(),
	MIDI::ControlChange(),
};

bool changedCommands[5] {
	false,
	false,
	false,
	false,
	false
};




constexpr uint32_t ADC_MAX_OFFSET = 3900;
constexpr uint32_t ADC_MIN_OFFSET = 10;
constexpr uint32_t ADC_DELTA = ADC_MAX_OFFSET - ADC_MIN_OFFSET;
constexpr uint32_t MIDI_CC_MIN = 0;
constexpr uint32_t MIDI_CC_MAX = 127;
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

			uint8_t newValue = map(averages[i], ADC_MIN_OFFSET, ADC_MAX_OFFSET, MIDI_CC_MIN, MIDI_CC_MAX);
			if(newValue != commands[i].value())
			{
				commands[i].value(newValue);
				changedCommands[i] = true;
			}
		}
	}
}

void cpp_main()
{
	// initialize the commands that are changed by the potentiometers
	for(int i = 0; i < 5; i++)
	{
		commands[i].channel(0);
		commands[i].cc(i);
		commands[i].value(0);
	}

	HAL_ADC_Start_DMA(&hadc1, adcValues, 50); // do 10 conversions each. calc averages in the timer callback
	HAL_TIM_Base_Start_IT(&htim1);

	MIDI::Note note;
	note.channel(0);
	note.pitch(40);
	note.velocity(127);
	note.press();


	// sending notes demo. uncomment this loop for the other demo
	//while(true)
	//{
	//	for(int i = 40; i < 52; i++)
	//	{
	//		note.pitch(i);
	//		HAL_Delay(500);
	//		MIDI_SendPacket(note);
	//		note.press();
	//		HAL_Delay(500);
	//		MIDI_SendPacket(note);
	//		note.release();
	//	}
	//}


	// CC demo, connect a potentiometer to PORTA0
	while(true)
	{

		for(int i = 0; i < 2; i++)
		{
			if(changedCommands[i])
			{
				changedCommands[i] = false;
				MIDI_SendPacket(commands[i]);
			}
		}
	}
}
