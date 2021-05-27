#include "chord.h"

chord::chord(std::string sym, int rt, std::tuple<int, int, int, int> tone, fxf voice, std::vector<chord*> precede, std::vector<chord*> follow, std::string qual) {
	symbol = sym;
	root = rt;
	tones = tone;
	voicings = voice;
	precedes = precede;
	follows = follow;
	quality = qual;
}

std::string chord::get_symbol() {
	return symbol;
}

int chord::get_root() {
	return root;
}

std::tuple<int, int, int, int> chord::get_tones() {
	return tones;
}

fxf chord::get_voicings() {
	return voicings;
}

std::string chord::get_quality() {
	return quality;
}



/* --TODO: Define chords in here instead of main code-- 
* 
chord Imaj7 = chord("Imaj7", 0, std::make_tuple(0, 4, 7, 11) , std::make_tuple(std::make_tuple(11, 14, 16, 19), std::make_tuple(4, 7, 11, 14), std::make_tuple(-1, 4, 7, 14), std::make_tuple(4, 11, 14, 19)), "", "", "major");
chord ii7 = chord("ii7", 2, std::make_tuple(2, 5, 9, 0), std::make_tuple(std::make_tuple(0, 4, 5, 9), std::make_tuple(5, 9, 12, 16), std::make_tuple(0, 5, 9, 16), std::make_tuple(5, 12, 16, 21)), "", "", "dorian");
chord iii7 = chord("iii7", 4, std::make_tuple(4, 7, 11, 2), std::make_tuple(std::make_tuple(2, 6, 7, 11), std::make_tuple(7, 11, 14, 18), std::make_tuple(2, 7, 11, 18), std::make_tuple(7, 14, 18, 23)), "", "", "phrygian");
chord IVmaj7 = chord("IVmaj7", 5, std::make_tuple(5, 9, 0, 4), std::make_tuple(std::make_tuple(4, 7, 9, 12), std::make_tuple(-3, 0, 4, 7), std::make_tuple(4, 9, 12, 19), std::make_tuple(-3, 4, 7, 12)), "", "", "major");
chord V7 = chord("V7", 7, std::make_tuple(7, 2, 11, 5), std::make_tuple(std::make_tuple(5, 9, 11, 14), std::make_tuple(-1, 2, 5, 9), std::make_tuple(5, 11, 14, 21), std::make_tuple(-1, 5, 9, 14)), "", "", "dominant");
chord vi7 = chord("vi7", 9, std::make_tuple(9, 0, 4, 7), std::make_tuple(std::make_tuple(7, 11, 12, 16), std::make_tuple(0, 4, 7, 11), std::make_tuple(7, 12, 16, 23), std::make_tuple(0, 7, 11, 16)), "", "", "aeolian");
chord vii7b5 = chord("vii7b5", 11, std::make_tuple(11, 2, 5, 9), std::make_tuple(std::make_tuple(2, 5, 9, 13), std::make_tuple(9, 13, 14, 17), std::make_tuple(-3, 2, 5, 13), std::make_tuple(2, 9, 13, 17)), "", "", "dominant");
*
*/


