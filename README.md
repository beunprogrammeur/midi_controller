# midi_controller
midi controller based on the minimal usb midi repository

This project is based on the STM32F103C8Tx minimal development board. (the one with 64k flash).

The idea is to have a device that can send MIDI commands (like key presses and CC commands).

For now, the aim is to have CC commands working using potentiometers on ADC1 (PORTA0-5)

making a new CC commands works as follows:

```
#include "midi/control_change.h"

...

void cpp_main()
{
  MIDI::ControlChange command;
  command.channel(0);
  command.cc(MIDI::ControlChangeId::LegatoFootswitch);
  command.value(64); // 0-127


  MIDI_SendPacket(command);
}

void cpp_main()
{
  MIDI::Note note;
  note.channel(0);
  note.velocity(127);
  note.pitch(44);
  note.press(); // or call release

  MIDI_SendPacket(note);
}

```