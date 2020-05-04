/*
 * control_change.cpp
 *
 *  Created on: May 4, 2020
 *      Author: vincent
 */

#include "control_change.h"

namespace MIDI
{

ControlChange::ControlChange(CableNumber cable)
	: IPacket(cable)
	, _data{ControlChangeByte, 0x00, 0x00 }
{
	codeIndex(CodeIndex::ControlChange);
}

ControlChange::ControlChange()
	: ControlChange(CableNumber::One)
{
}

void ControlChange::channel(uint8_t ch)
{
	if(ch > 15)
	{
		ch = 15;
	}

	_data[0] &= ~(0x0f); // remove old channel data
	_data[0] |= ch;
}

void ControlChange::cc(uint8_t id)
{
	_data[1] = id;
}

void ControlChange::cc(ControlChangeId id)
{
	_data[1] = static_cast<uint8_t>(id);
}

void ControlChange::value(uint8_t val)
{
	if(val > 127)
	{
		val = 127;
	}

	_data[2] = val;
}

uint8_t ControlChange::value() const
{
	return _data[2];
}


} // namespace end MIDI
