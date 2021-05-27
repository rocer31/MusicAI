#pragma once

#include <fluidsynth.h>
#include "chord.h"
#include <iostream>
#include <thread>
#include <unordered_map>
#include <string>
#include <tuple>
#include <exception>
#include <time.h>

#if defined(WIN32)
#include <windows.h>
#define sleep(_t) Sleep(_t * 1000)
#else
#include <stdlib.h>
#include <unistd.h>
#endif

using namespace std;

tuple<int, int, int, int> closest_voicing(tuple<int, int, int, int>, chord);
vector<chord> get_prog(string, int, int, chord, chord, chord, chord, chord, chord, chord);
void play_chord(chord current_chord, tuple<int, int, int, int>, string, int, float, fluid_synth_t*, unordered_map<string, int>, float, unordered_map<string, int>, int);