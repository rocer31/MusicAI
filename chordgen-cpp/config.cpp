#include "config.h"

config::config() {
	bpm = 120; // tempo
	q = 60 / bpm; // q
	h = q * 2; // half
	w = h * 2; // whole
	e = q / 2; // eighth
	s = e / 2; // sixteenth

	// time signature
	beats = 4;
	measure = beats * q;

	// form
	form = "aaba";

	// measures per section
	length = 4;

	// repeats
	repeats = 1;
	// key

	key = rand() % 12;
	chose_key = false;
}