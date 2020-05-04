/*
 * packet.h
 *
 *  Created on: May 4, 2020
 *      Author: vincent
 */

#ifndef INC_MIDI_PACKET_H_
#define INC_MIDI_PACKET_H_
#include <stdint.h>
namespace MIDI
{
// for more info: https://www.usb.org/sites/default/files/midi10.pdf page 16
enum class CableNumber : uint8_t
{
	One      = 0x00,
	Two      = 0x10,
	Three    = 0x20,
	Four     = 0x30,
	Five     = 0x40,
	Six      = 0x50,
	Seven    = 0x60,
	Eight    = 0x70,
	Nine     = 0x80,
	Ten      = 0x90,
	Eleven   = 0xa0,
	Twelve   = 0xb0,
	Thirteen = 0xc0,
	Fourtene = 0xd0,
	Fifteen  = 0xe0,
	Sixteen  = 0xf0,
};

// for more info: https://www.usb.org/sites/default/files/midi10.pdf page 16
enum class CodeIndex : uint8_t
{
	// Misc = 0x00,         // Miscellaneous function codes. Reserved for future extensions
	// CableEvents = 0x01,  // Reserved for future expansion. (of the midi standard
	TwoByteCommon   = 0x02, // Two-byte System Common messages like MTC, SongSelect, etc.
	ThreeByteCommon = 0x03, // Three-byte System Common messages like SPP, etc.
	SysEx           = 0x04, // Start or Continue
	SingleByte      = 0x05, // Single-byte System Common Message or SysEx ends with following single byte.
	SysExEnd2       = 0x06, // SysEx ends with following two bytes.
	SysExEnd3       = 0x07, // SysEx ends with following three bytes.
	NoteOff         = 0x08,	// 3 bytes
	NoteOn          = 0x09,	// 3 bytes
	PolyKeypress    = 0x0a, // 3 bytes
	ControlChange   = 0x0b, // 3 bytes
	ProgramChange   = 0x0c, // 2 bytes
	ChannelPressure = 0x0d, // 2 bytes
	PitchBend       = 0x0e, // 3 bytes
	SingleByte2     = 0x0f, // 1 byte  the documentation isn't very clear on this one.
};


class IPacket
{
private:
	uint8_t _cableNumber_codeIndex;

protected:
	void codeIndex(CodeIndex cindex)
	{
		_cableNumber_codeIndex &= ~(0x0F); // remove any possible valie in the code index space
		_cableNumber_codeIndex |= static_cast<uint8_t>(cindex);
	}

public:
	IPacket(CableNumber cable = CableNumber::One)
		: _cableNumber_codeIndex(0)
	{
		cableNumber(cable);
	}

	void cableNumber(CableNumber cable)
	{
		_cableNumber_codeIndex &= ~(0xF0); // remove any possible value in the cable number space;
		_cableNumber_codeIndex |= static_cast<uint8_t>(cable);
	}
};

} // end namespace midi



#endif /* INC_MIDI_PACKET_H_ */
