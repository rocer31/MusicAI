#pragma once
#include <string>

class config
{
	public:
	// tempo info
	float bpm;
	float q;
	float h;
	float w;
	float e;
	float s;

	// time signature
	float beats;
	float measure;

	// form
	std::string form;

	// measures per section
	float length;

	// repeats
	int repeats;
	// key

	int key;
	bool chose_key;

	config();
};

