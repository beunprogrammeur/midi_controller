/*
 * control_change.h
 *
 *  Created on: May 4, 2020
 *      Author: vincent
 */

#ifndef INC_MIDI_CONTROL_CHANGE_H_
#define INC_MIDI_CONTROL_CHANGE_H_

#include "packet.h"

namespace MIDI
{

enum class ControlChangeId : uint8_t
{
	BankSelectMSB                   = 0,
	ModulationWheelMSB              = 1,
	BreathControllerMSB             = 2,
	FootControllerMSB               = 4,
	PortamentoTimeMSB               = 5,
	DataEntryMSB                    = 6,
	ChannelVolumeMSB                = 7,
	BalanceMSB                      = 8,
	PanMSB                          = 10,
	ExpressionControllerMSB         = 11,
	EffectControl1MSB               = 12,
	EffectControl2MSB               = 13,
	GeneralPurposeController1MSB    = 16,
	GeneralPurposeController2MSB    = 17,
	GeneralPurposeController3MSB    = 18,
	GeneralPurposeController4MSB    = 19,
	BankSelectLSB                   = 32,
	ModulationWheelLSB              = 33,
	BreathControllerLSB             = 34,
	FootControllerLSB               = 36,
	PortamentoTimeLSB               = 37,
	DataEntryLSB                    = 38,
	ChannelVolumeLSB                = 39,
	BalanceLSB                      = 40,
	PanLSB                          = 42,
	ExpressionControllerLSB         = 43,
	EffectControl1LSB               = 44,
	EffectControl2LSB               = 45,
	GeneralPurposeController1LSB    = 48,
	GeneralPurposeController2LSB    = 49,
	GeneralPurposeController3LSB    = 50,
	GeneralPurposeController4LSB    = 51,
	DamperPedalOnOff                = 64,
	PortamentoOnOff                 = 65,
	SostenutoOnOff                  = 66,
	SoftPedalOnOff                  = 67,
	LegatoFootswitch                = 68,
	SoundController1                = 70,
	SoundController2                = 71,
	SoundController3                = 72,
	SoundController4                = 73,
	SoundController5                = 74,
	SoundController6                = 75,
	SoundController7                = 76,
	SoundController8                = 77,
	SoundController9                = 78,
	SoundController10               = 79,
	GeneralPurposeController5LSB    = 80,
	GeneralPurposeController6LSB    = 81,
	GeneralPurposeController7LSB    = 82,
	GeneralPurposeController8LSB    = 83,
	PortamentoControlLSB            = 84,
	HighResolutionVelocityPrefixLSB = 88,
	Effects1Depth                   = 91,
	Effects2Depth                   = 92,
	Effects3Depth                   = 93,
	Effects4Depth                   = 94,
	Effects5Depth                   = 95,
	DataIncrement                   = 96,
	DataDecrement                   = 97,
	NonRegisteredParameterNumberLSB = 98,
	NonRegisteredParameterNumberMSB = 99,
	RegisteredParameterNumberLSB    = 100,
	RegisteredParameterNumberMSB    = 101,
	AllSoundOff                     = 120,
	ResetAllControllers             = 121,
	LocalControlOnOff               = 122,
	AllNotesOff                     = 123,
	OmniModeOff                     = 124,
	OmniModeOn                      = 125,
	MonoModeOn                      = 126,
	PolyModeOn                      = 127,
};

class ControlChange : public IPacket
{
private:
	static constexpr uint8_t ControlChangeByte = 0xb0;

	/* data layout
	 * [0] = 'control change byte' as per midi standard (like a header / announcement)
	 *        the channel is the Lower nibble
	 * [1] = cc code
	 * [2] = value
	 * */
	uint8_t _data[3];

public:
	explicit ControlChange(CableNumber cable);
	ControlChange();

	void channel(uint8_t ch);
	uint8_t channel() const;
	// cc is the control change id, there are 127 id's
	void cc(uint8_t id);
	void cc(ControlChangeId id);
	uint8_t cc() const;
	void value(uint8_t val);
	uint8_t value() const;
};

} // end namespace midi



#endif /* INC_MIDI_CONTROL_CHANGE_H_ */
