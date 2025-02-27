/*  
 *  This file is part of libEmuSC, a Sound Canvas emulator library
 *  Copyright (C) 2022  Håkon Skjelten
 *
 *  libEmuSC is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libEmuSC is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libEmuSC. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __NOTE_PARTIAL_H__
#define __NOTE_PARTIAL_H__


#include "control_rom.h"
#include "tva.h"
#include "tvf.h"
#include "tvp.h"

#include <stdint.h>


namespace EmuSC {

class NotePartial
{
private:
  uint8_t _key;           // MIDI key number for note on
  float _keyDiff;         // Difference in number of keys from original tone
                          // If pitchKeyFollow is used, keyDiff is adjusted
  int _drumSet;           // < 0 => not drums (normal instrument)

  struct ControlRom::InstPartial &_instPartial;
  struct ControlRom::Sample &_ctrlSample;

  std::vector<float> &_pcmSamples;

  float _samplePos;       // Sample position in number of samples from start
  bool _sampleDir;        // 0 = backward & 1 = foreward

  ControlRom &_ctrlRom;

  float _sampleFactor;    // => 32000 / sample rate

  double _instPitchTune;  // Instrument pitch offset factor

  TVP *_tvp;
  TVF *_tvf;
  TVA *_tva;

  double _convert_volume(uint8_t volume);

public:
  NotePartial(uint8_t key, int8_t keyDiff, int drumSet,
	      struct ControlRom::InstPartial &instPartial,
	      struct ControlRom::Sample &sample, std::vector<float> &pcmSamples,
	      ControlRom &ctrlRom, uint32_t sampleRate);
  ~NotePartial();

  void stop(void);
  bool get_next_sample(float *sampleOut, float pitchBend);

};

}

#endif  // __NOTE_PARTIAL_H__
