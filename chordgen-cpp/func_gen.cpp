#include "func_gen.h"

void set_tempo(config &params, float tempo) {
    params.bpm = tempo;
    params.q = 60 / tempo;
    params.h = params.q * 2;
    params.w = params.h * 2;
    params.e = params.q / 2;
    params.s = params.e / 2;
}

void set_ts(config &params, float beats) {
    params.beats = beats;
    params.measure = beats * params.q;
}

void set_form(config &params, string form) {
    params.form = form;
}

void set_key(config &params, int key) {
    if (key > 11) {
        key = key % 12;
    }
    params.key = key;
    params.chose_key = true;
}

//std::tuple<int, int, int, int> to_play = Imaj7.get_tones();

void realize_config(config &params, unordered_map<string, chord> all_chords, unordered_map<string, int> drum_sounds, fluid_synth_t* synth) {
    vector<string> keys = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B" }; // 11
    unordered_map<string, int> roots = {
        {"C", 60}, // middle C
        {"C#", 61},
        {"Db", 61},
        {"D", 62},
        {"D#", 63},
        {"Eb", 63},
        {"E", 64 - 12}, // -12 drops the octave
        {"F", 65 - 12},
        {"F#", 66 - 12},
        {"Gb", 66 - 12},
        {"G", 67 - 12},
        {"G#", 68 - 12},
        {"Ab", 68 - 12},
        {"A", 69 - 12},
        {"A#", 70 - 12},
        {"Bb", 70 - 12},
        {"B", 71 - 12}, // B above middle C
    };
    // int keynum = rand() % 12;
    string keyname = keys.at(params.key);
    int key = roots[keyname];

    cout << "Key of " << keyname << endl;
    vector<chord> prog = get_prog(params.form, params.length, params.repeats, all_chords["Imaj7"], all_chords["ii7"], all_chords["iii"], all_chords["IVmaj7"], all_chords["V7"], all_chords["vi7"], all_chords["vii7b5"]);

    tuple<int, int, int, int> voicing_init = all_chords["Imaj7"].get_voicings()[0];
    tuple<int, int, int, int> voicing_choice = closest_voicing(voicing_init, prog[0]);

    int ctr = 0;
    int past_key = 0;
    int form_place = 0;
    
    // pick a random A key
    if (!params.chose_key) { params.key = rand() % 12; }
    
    // pick a B key, that is modulated from the A key
    int b_key;
    if (params.key + 5 > 11) {
        b_key = (params.key + 5) % 12;
    }
    else {
        b_key = params.key + 5;
    }
    // pick a C key, which right now is un-used because I didn't know what to do with that
    int c_key = 0;

    // this vector is used to get the keys in the order they're supposed to play at
    vector<int> form_nums = {};

    // iterate through the form, and populate our form_nums vector with the correct key;
    for (int j = 0; j < params.repeats; j++) {
        for (int i = 0; i < params.form.size(); i++) {
            switch (params.form.at(i)) {
            case 'a':
                form_nums.push_back(params.key);
                break;
            case 'b':
                form_nums.push_back(b_key);
                break;
            case 'c':
                form_nums.push_back(c_key);
                break;
            default:
                form_nums.push_back(params.key);
                break;
            }
        }
    }
    // form_place is used to keep track of where we are in the form
    form_place = 0;
    // current_key is used to keep track of which key we should be in
    int current_key = form_nums.at(form_place);
    

    for (auto it = prog.begin(); it != prog.end(); it++) {
        cout << it->get_symbol() << endl;
        voicing_choice = closest_voicing(voicing_choice, *it);
        play_chord(*it, voicing_choice, it->get_quality(), it->get_root() + key, params.q, synth, roots, params.measure, drum_sounds, params.beats);
        ctr++;
        if ((fmod((float)ctr, params.length) == 0.0) && ((it + 1) != prog.end())) {
            form_place++;
            past_key = current_key;
            current_key = form_nums.at(form_place);

            // check if the key is supposed to change
            if (past_key != current_key) {
                // modulate
                keyname = keys[current_key];
                key = roots[keys[current_key]];
                cout << "Modulated to " << keys[current_key] << endl;
            }
        }
    }
    play_chord(all_chords["Imaj7"], all_chords["Imaj7"].get_voicings()[0], all_chords["Imaj7"].get_quality(), all_chords["Imaj7"].get_root(), params.q, synth, roots, params.measure, drum_sounds, params.beats);
}




/* -END MUSIC GENERATION- */