#pragma once
#include "config.h"
#include "noteplayer.h"
#include "chord.h"

void set_tempo(config& params, float tempo);
void set_ts(config& params, float beats);
void set_form(config& params, string form);
void set_key(config& params, int key);
void realize_config(config& params, unordered_map<string, chord> all_chords, unordered_map<string, int> drum_sounds, fluid_synth_t* synth);