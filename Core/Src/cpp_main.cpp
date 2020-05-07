/*
 * cpp_main.cpp
 *
 *  Created on: May 4, 2020
 *      Author: vincent
 */


#include "cpp_main.h"

// peripherals
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "i2c.h"

// midi
#include "usbd_midi_if.h"
#include "midi/control_change.h"
#include "midi/note.h"

// display
#include <string>
#include "128x32/oled.h"
#include "128x32/gfx.h"
#include "128x32/fonts.h"
#include "point.h"

namespace {
	struct PotWrapper {
		MIDI::ControlChange command;
		bool changed;
		uint8_t pot_index; // order from left to right, which potentiometer is this?
	};

	constexpr uint8_t pot_count = 5;
	constexpr uint8_t measurements_per_pot_count = 10;
	constexpr uint8_t measurements_count =  pot_count * measurements_per_pot_count;
	uint32_t adcValues[measurements_count];

	// the potmeter definition, the numbers are the position on the screen x,y
	PotWrapper potmeters[pot_count] {
		{ MIDI::ControlChange(), false, 0, },
		{ MIDI::ControlChange(), false, 1, },
		{ MIDI::ControlChange(), false, 2, },
		{ MIDI::ControlChange(), false, 3, },
		{ MIDI::ControlChange(), false, 4, }
	};

	constexpr uint8_t pot_box_top_line_y_pos = 19;
	constexpr uint8_t pot_box_bot_line_y_pos = 30;
	constexpr uint8_t pot_box_line_thickness = 2;

	constexpr uint8_t box_border_width = 2;
	constexpr uint8_t pot_val_width = 24;
	constexpr uint8_t pot_val_margin = 2;

	struct draw_box
	{
		uint8_t x;
		uint8_t width;
	};

	constexpr draw_box boxes[5] = {
		{2,   22},
		{26,  24},
		{52,  24},
		{78,  24},
		{104, 21},
	};

	void draw_horizontal_line(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color = WHITE)
	{
		for(uint8_t yy = y; yy < (y + height); yy++)
		{
			for(uint8_t xx = x; xx < (x + width); xx++)
			{
				OLED::draw_pixel(xx, yy, color);
			}
		}
	}

	void draw_pot_value(PotWrapper& potentiometer)
	{

		constexpr uint8_t y = 22;
		uint8_t x = box_border_width + (pot_val_width + pot_val_margin) * potentiometer.pot_index;

		constexpr uint8_t height = pot_box_bot_line_y_pos - pot_box_top_line_y_pos - pot_box_line_thickness - 1;
		draw_horizontal_line(boxes[potentiometer.pot_index].x, y, boxes[potentiometer.pot_index].width, height, BLACK); // resets the pot value box to black
		OLED::graphics_text(x, y, FONT_BASE::FONT_SEVEN_DOT, std::to_string(potentiometer.command.value()).c_str());
	}

	void draw_cc_codes()
	{
		constexpr uint8_t y = 12;
		constexpr uint8_t box_height = 6;
		draw_horizontal_line(1, y, 126, box_height, BLACK); // resets the cc code text spaces to black


		for(int i = 0; i < pot_count; i++)
		{
			uint8_t x = box_border_width + (pot_val_width + pot_val_margin) * i;
			OLED::graphics_text(x, y, FONT_BASE::FONT_FIVE_DOT, std::to_string(potmeters[i].command.cc()).c_str());
		}

	}

	void draw_channel()
	{
		constexpr uint8_t x = 46;
		constexpr uint8_t y = 1;

		draw_horizontal_line(x, 0, 25, 7, BLACK); // resets the channel code text space
		OLED::graphics_text(x, y, FONT_BASE::FONT_FIVE_DOT, std::to_string(potmeters[0].command.channel() + 1).c_str());
	}

	void init_display()
	{
        // design:
		/*
		 *  CC: ###              mode: chan
		 *  ===============================
		 *  = num = num = num = num = num =
		 *  ===============================
		 *
		 * */

		constexpr FONT_BASE detail_font = FONT_BASE::FONT_FIVE_DOT;

		OLED::init();

		OLED::graphics_text(3,  1, detail_font, "cc");
		OLED::graphics_text(14, 1, detail_font, "channel");


		// box around cc
		draw_horizontal_line(0, 0, 1, pot_box_top_line_y_pos);
		draw_horizontal_line(0, 0, 12, 1);
		draw_horizontal_line(12, 0, 1, 8);
		draw_horizontal_line(12, 8, 116, 1);
		draw_horizontal_line(127, 8, 1, 8 - pot_box_top_line_y_pos);

		draw_horizontal_line(0, pot_box_top_line_y_pos, 127, 2);
		draw_horizontal_line(0, pot_box_bot_line_y_pos, 127, 2);

		for(int i = 0; i < 6; i++)
		{
			int16_t x = (26 * i) - 2;
			if(x < 0)
			{
				x = 0;
			}
			else if (x > 125)
			{
				x = 125;
			}

			draw_horizontal_line(x, 21, 2, 9);
		}

		draw_cc_codes();
		draw_channel();

		OLED::update();
	}

	template<typename T>
	void MIDI_SendPacket(T& packet)
	{
		MIDI_TransmitData((uint8_t*)&packet, sizeof(T));
	}

	int32_t map(int32_t value, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
	  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim1)
	{
		constexpr uint32_t adc_max_offset = 3900;
		constexpr uint32_t adc_min_offset = 10;
		constexpr uint32_t midi_cc_min = 0;
		constexpr uint32_t midi_cc_max = 127;



		for (int i = 0; i < pot_count; i++)
		{
            uint32_t average = 0;

            for (int j = 0; j < measurements_per_pot_count; j++)
            {
            	average += adcValues[i+(j*pot_count)];
            }

            average /= measurements_per_pot_count;

            if (average > adc_max_offset)
            {
            	average = adc_max_offset;
            }
            else if (average < adc_min_offset)
            {
            	average = adc_min_offset;
            }

			uint8_t cc_value = map(average, adc_min_offset, adc_max_offset, midi_cc_min, midi_cc_max);
			if (cc_value != potmeters[i].command.value())
			{
				potmeters[i].command.value(cc_value);
				potmeters[i].changed = true;
			}
		}

	}
}

void cpp_main()
{
	// initialize the commands that are changed by the potentiometers
	// TODO: move to dedicated function that will be called when the rotary encoder turns
	for (int i = 0; i < 5; i++)
	{
		potmeters[i].command.channel(0);
		potmeters[i].command.cc(i);

	}

	HAL_ADC_Start_DMA(&hadc1, adcValues, measurements_count); // do n conversions each. calc averages in the timer callback
	HAL_TIM_Base_Start_IT(&htim1);
	// TODO: implement encoder
	//HAL_TIM_Encoder_Start_IT(&, Channel)

	// sending notes demo. uncomment this loop for the other demo
	//MIDI::Note note;
	//note.channel(0);
	//note.pitch(40);
	//note.velocity(127);
	//note.press();
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

	HAL_Delay(10); // wait for the timer to be fired at least once

	init_display();


	// CC demo, connect a potentiometer to PORTA0
	while (true)
	{
		bool updateScreen = false;

		for (auto& potmeter : potmeters)
		{
			if (potmeter.changed)
			{
				potmeter.changed = false;
				updateScreen = true;
				MIDI_SendPacket(potmeter.command);
				draw_pot_value(potmeter);
			}
		}

		if (updateScreen) {
			updateScreen = false;
			OLED::update();
		}
	}
}




