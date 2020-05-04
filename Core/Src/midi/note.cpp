/*
 * note.cpp
 *
 *  Created on: May 5, 2020
 *      Author: vincent
 */


#include "note.h"
namespace MIDI
{


Note::Note(CableNumber cable)
	: IPacket(cable)
{
	release();
}

Note::Note()
	: Note(CableNumber::One)
{
}

void Note::channel(uint8_t ch)
{
	if(ch > 15)
	{
		ch = 15;
	}

	_data[0] &= ~(0x0F);
	_data[0] |= ch;
}
uint8_t Note::channel() const
{
	return _data[0] & 0x0F;
}

void Note::velocity(uint8_t value)
{
	if(value > 127)
	{
		value = 127;
	}

	_data[2] = value;
}
uint8_t Note::velocity() const
{
	return _data[2];
}

void Note::pitch(uint8_t value)
{
	if(value > 108) // highest note on midi according to: https://newt.phys.unsw.edu.au/jw/notes.html
	{
		value = 108;
	}

	_data[1] = value;
}

uint8_t Note::pitch() const
{
	return _data[1];
}

void Note::press()
{
	codeIndex(CodeIndex::NoteOn);
	_data[0] &= ~(0xF0); // remove press space state
	_data[0] |= 0x90; // add press data
}
void Note::release()
{
	codeIndex(CodeIndex::NoteOff);
	_data[0] &= ~(0xF0);
	_data[0] |= 0x80;
}
} // end namespace MIDI
