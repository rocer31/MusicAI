#pragma once
#include "config.h"
#include "noteplayer.h"

void set_tempo(config& params, float tempo);
void set_ts(config& params, float beats);
void set_form(config& params, int length, int repeats);
void set_key(config& params, int key);
void set_instrument(fluid_synth_t*& synth, int channel, int instrument);
void realize_config(config& params, unordered_map<string, chord> all_chords, unordered_map<string, int> drum_sounds, fluid_synth_t* synth);