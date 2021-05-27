#include "noteplayer.h"

tuple<int, int, int, int> closest_voicing(tuple<int, int, int, int> currentVoicing, chord nextChord) {
    tuple<int, int> best = make_tuple(-1, 999); // voicing #, best value
    tuple<int, int, int, int> voicing = make_tuple(0, 0, 0, 0);

    int cv_tone0 = get<0>(currentVoicing);
    int cv_tone1 = get<1>(currentVoicing);
    int cv_tone2 = get<2>(currentVoicing);
    int cv_tone3 = get<3>(currentVoicing);

    int diff0, diff1, diff2, diff3;
    int diffsum = 0;

    for (int i = 0; i < 4; i++) {
        voicing = nextChord.get_voicings()[i];
        diff0 = abs(cv_tone0 - get<0>(voicing));
        diff1 = abs(cv_tone1 - get<1>(voicing));
        diff2 = abs(cv_tone2 - get<2>(voicing));
        diff3 = abs(cv_tone3 - get<3>(voicing));

        diffsum = diff0 + diff1 + diff2 + diff3;

        if (diffsum < get<1>(best)) { // minimize difference
            best = make_tuple(i, diffsum);
        }
    }
    return nextChord.get_voicings()[get<0>(best)];
}

vector<chord> get_prog(string form, int length, int repeats, chord Imaj7, chord ii7, chord iii7, chord IVmaj7, chord V7, chord vi7, chord vii7b5) {
    int next_chord_picker = 0;
    chord next_chord = Imaj7;
    vector<chord> prog = {};
    vector<chord> aSection = {};
    vector<chord> bSection = {};
    vector<chord> cSection = {};
    //next_chord_picker = rand() % (Imaj7.precedes.size());
    //next_chord = *(Imaj7.precedes)[next_chord_picker];
    aSection.push_back(next_chord);
    while (aSection.size() < (length)) {
        next_chord_picker = rand() % (aSection.back().precedes.size());
        next_chord = *(aSection.back().precedes)[next_chord_picker];
        aSection.push_back(next_chord);
    }
    next_chord_picker = rand() % (aSection.back().precedes.size());
    next_chord = *(aSection.back().precedes)[next_chord_picker];
    bSection.push_back(next_chord);
    while (bSection.size() < length * 2) {
        next_chord_picker = rand() % (bSection.back().precedes.size());
        next_chord = *(bSection.back().precedes)[next_chord_picker];
        bSection.push_back(next_chord);
    }
    next_chord_picker = rand() % (bSection.back().precedes.size());
    next_chord = *(bSection.back().precedes)[next_chord_picker];
    cSection.push_back(next_chord);
    while (cSection.size() < length) {
        next_chord_picker = rand() % (cSection.back().precedes.size());
        next_chord = *(cSection.back().precedes)[next_chord_picker];
        cSection.push_back(next_chord);
    }
    for (int times = 0; times < repeats; times++) {
        for (int j = 0; j < form.length(); j++) {
            switch (form.at(j)) {
            case 'a':
                for (int i = 0; i < length; i++) {
                    prog.push_back(aSection[i]);
                }
                break;
            case 'b':
                for (int i = 0; i < length; i++) {
                    prog.push_back(bSection[i]);
                }
                break;
            case 'c':
                for (int i = 0; i < length; i++) {
                    prog.push_back(aSection[i]);
                }
                break;
            default:
                for (int i = 0; i < length; i++) {
                    prog.push_back(aSection[i]);
                }
                break;
            }
        }
    }

    //for (int i = 0; i < length; i++) { prog.push_back(aSection[i]); }
    //for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }
    //for (int i = 0; i < length; i++) { prog.push_back(cSection[i]); }
    //for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }
    //for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }

    return prog;
}

vector<float> generate_rhythm(vector<float> poss_notes, float measure) {
    //returned vector
    vector<float> gen_rhythm = {};

    // used to make sure we only generate one measure
    float length = 0;

    // index of note length
    int chosen_note = 0;

    // used to get the chosen note length
    float chosen_length = 0;

    // while we haven't generated a measure yet
    while (length < measure) {

        // randomly pick from the notes possible
        chosen_note = rand() % poss_notes.size();
        // if that chosen note is too long, set it to be exactly the remaining length; otherwise, use it
        if ((length + poss_notes.at(chosen_note)) > measure) {
            chosen_length = measure - length;
        }
        else {
            chosen_length = poss_notes.at(chosen_note);
        }
        //add to the vector, increment the length generated
        gen_rhythm.push_back(chosen_length);
        length += chosen_length;
    }
    return gen_rhythm;
}

// Decide whether we should rest or not
boolean decide_rest(bool in_triplet) {
    int rest_chance = 4;
    if (in_triplet) { rest_chance = 6; }
    if (rand() % rest_chance < 1) { return true; }
    return false;
}

// Decide whether we should do a triplet or not
boolean decide_triplet() {
    int trip_chance = 6;
    if (rand() % trip_chance < 1) { return true; }
    return false;
}

void play_chord(chord current_chord, tuple<int, int, int, int> voicing, string quality, int root, float duration, fluid_synth_t* synth, unordered_map<string, int> roots, float measure, unordered_map<string, int> drum_sounds, int beats) {
    
    char what_on = 'a'; // used to determine which chord progression we're on

    float h = 2 * duration; // half note
    float w = 2 * h;        // whole note
    float e = duration / 2; // eighth note
    float s = e / 2;        // sixteenth note

    vector<float> note_lengths = { w, h+duration, h, duration + e, duration, e + s, e, s }; // note lengths vector to randomly select note length


    vector<char> hat_notes = { };
    vector<char> bass_notes = { };
    vector<char> snare_notes = { };

    int i = 0;
    while (i++ < beats) {
        bass_notes.push_back('r');
        hat_notes.push_back('r');
        hat_notes.push_back('r');
        snare_notes.push_back('r');
        snare_notes.push_back('r');
    }

    vector<char> hat_options = { 'r', 'o', 'c', 'c', 'c' };

    for (int i = 0; i < 2 * beats; i++) {
        hat_notes.at(i) = hat_options.at(rand() % 5);
        if (i % 2 == 0 && hat_notes.at(i) == 'r') {
            hat_notes.at(i) = 'c';
        }
    }

    
    for (int i = 0; i < beats; i++) {
        if (!i) {
            bass_notes.at(i) = 'b';
        }
        else {
            bass_notes.at(i) = bass_notes.at(rand() % bass_notes.size());
        }
    }
    if (beats >= 3) { snare_notes.at(4) = 's'; }
    for (int i = 0; i < 2 * beats; i++) {
        if (rand() % 100 < 16 && snare_notes.at(i) == 'r') {
            snare_notes.at(i) = 's';
        }
    }



    thread hat_thread([&]() {
        for (int i = 0; i < 2 * beats; i++) {
            switch (hat_notes.at(i))
            {
            case 'r':
                sleep(e);
                break;
            case 'c':
                fluid_synth_noteon(synth, 9, drum_sounds["closed_hat"], 80);
                sleep(e);
                fluid_synth_noteoff(synth, 9, drum_sounds["closed_hat"]);
                break;
            case 'o':
                fluid_synth_noteon(synth, 9, drum_sounds["open_hat"], 80);
                sleep(e);
                fluid_synth_noteoff(synth, 9, drum_sounds["open_hat"]);
            }
        }
        });

    thread bass_thread([&]() {
        for (int i = 0; i < beats; i++) {
            switch (bass_notes.at(i))
            {
            case 'r':
                sleep(duration);
                break;
            case 'b':
                fluid_synth_noteon(synth, 9, drum_sounds["bass_drum"], 127);
                sleep(duration);
                fluid_synth_noteoff(synth, 9, drum_sounds["bass_drum"]);
                break;
            }
        }
        });

    thread snare_thread([&]() {
        for (int i = 0; i < 2 * beats; i++) {
            switch (snare_notes.at(i))
            {
            case 'r':
                sleep(e);
                break;
            case 's':
                fluid_synth_noteon(synth, 9, drum_sounds["snare"], 90);
                sleep(e);
                fluid_synth_noteoff(synth, 9, drum_sounds["snare"]);
                break;
            }
        }
        });


    /* Play a note */
    int rt_val = root; // root note
    float playtime = 0; // initialize time played so far to 0

    // play the root in octaves
    fluid_synth_noteon(synth, 0, rt_val - 24, 95);
    //fluid_synth_noteon(synth, 1, rt_val - 36, 80);

    //play chord with chosen voicing
    fluid_synth_noteon(synth, 2, rt_val + get<0>(voicing) - 12, 90);
    fluid_synth_noteon(synth, 3, rt_val + get<1>(voicing) - 12, 90);
    fluid_synth_noteon(synth, 4, rt_val + get<2>(voicing) - 12, 90);
    fluid_synth_noteon(synth, 5, rt_val + get<3>(voicing) - 12, 90);
    // chord is now playing

    float time = 0;
    float time_prev = 0;

    while (playtime < measure) {
        //cout << playtime << " " << measure << endl;
        vector<int> possible_notes = {};
        // Determine by chord quality which notes we can play
        // major scale notes: 0, 2, 4, 5, 7, 9, 11

        if (current_chord.get_quality().compare("major") == 0) {
            possible_notes.push_back(0);
            possible_notes.push_back(0);
            possible_notes.push_back(2);
            possible_notes.push_back(4);
            possible_notes.push_back(4);
            possible_notes.push_back(7);
            possible_notes.push_back(7);
            possible_notes.push_back(9);
            possible_notes.push_back(11);
        }

        else if (current_chord.get_quality().compare("minor") == 0) {
            possible_notes.push_back(0);
            possible_notes.push_back(0);
            possible_notes.push_back(3);
            possible_notes.push_back(3);
            possible_notes.push_back(5);
            possible_notes.push_back(7);
            possible_notes.push_back(7);
            possible_notes.push_back(9);
        }

        else if (current_chord.get_quality().compare("dominant") == 0) {
            possible_notes.push_back(2);
            possible_notes.push_back(4);
            possible_notes.push_back(5);
            possible_notes.push_back(7);
            possible_notes.push_back(7);
            possible_notes.push_back(9);
            possible_notes.push_back(10);
            possible_notes.push_back(10);
        }

        int note_picker = rand() % possible_notes.size();
        int note = possible_notes[note_picker] + rt_val;

        vector<float> len_vals = { duration, h, e, s };
        int len_picker = rand() % len_vals.size();


        time = len_vals[len_picker];

        if (time_prev == s) {
            time = s;
        }
        if ((playtime + time) > measure) {
            time = measure - playtime;
        }
        if (time_prev == s && time == s) {
            time_prev = 0;
        }
        else {
            time_prev = time;
        }
        playtime = playtime + time;

        // decide if there should be a rest or not
        if (decide_rest(false)) { sleep(time); }
        //we can only have a triplet if the time is at least a quarter note, to avoid wonkiness
        else if (time >= duration) {
            if (decide_triplet()) {
                //divide the time by 3, to get a triplet
                time /= 3;
                //play the first note
                fluid_synth_noteon(synth, 7, note, 100);
                sleep(time);
                fluid_synth_noteoff(synth, 7, note);

                // pick a second note and play it, with the chance of a rest
                if (decide_rest(true)) { sleep(time); }
                else {
                    note_picker = rand() % possible_notes.size();
                    note = possible_notes[note_picker] + rt_val;
                    fluid_synth_noteon(synth, 7, note, 100);
                    sleep(time);
                    fluid_synth_noteoff(synth, 7, note);
                }
                //pick a third note and play it, with the chance of a rest
                if (decide_rest(true)) { sleep(time); }
                else {
                    note_picker = rand() % possible_notes.size();
                    note = possible_notes[note_picker] + rt_val;
                    fluid_synth_noteon(synth, 7, note, 100);
                    sleep(time);
                    fluid_synth_noteoff(synth, 7, note);
                }
            }
            else {
                fluid_synth_noteon(synth, 7, note, 100);
                sleep(time);
                fluid_synth_noteoff(synth, 7, note);
            }
        }
        // if neither a rest nor a triplet, play the note regularly
        else {
            //cout << playtime << " " << measure << endl;
            fluid_synth_noteon(synth, 7, note, 100);
            sleep(time);
            fluid_synth_noteoff(synth, 7, note);
        }

    };
    //kill root notes
    fluid_synth_noteoff(synth, 0, rt_val - 12);
    fluid_synth_noteoff(synth, 1, rt_val - 24);
    /* Stop the note */
    fluid_synth_noteoff(synth, 2, rt_val + get<0>(voicing) - 12);
    fluid_synth_noteoff(synth, 3, rt_val + get<1>(voicing) - 12);
    fluid_synth_noteoff(synth, 4, rt_val + get<2>(voicing) - 12);
    fluid_synth_noteoff(synth, 5, rt_val + get<3>(voicing) - 12);

    hat_thread.join();
    bass_thread.join();
    snare_thread.join();
}