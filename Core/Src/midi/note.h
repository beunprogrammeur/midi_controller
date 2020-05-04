#ifndef INC_MIDI_NOTE_H_
#define INC_MIDI_NOTE_H_

#include "packet.h"

namespace MIDI
{

class Note : public IPacket
{
public:
    explicit Note(CableNumber cable);
	Note();

	void channel(uint8_t ch);
	uint8_t channel() const;

	void velocity(uint8_t ch);
	uint8_t velocity() const;

	void pitch(uint8_t value);
	uint8_t pitch() const;

	void press();
	void release();

private:
	uint8_t _data[3];
};
} // namespace end MIDI


#endif
