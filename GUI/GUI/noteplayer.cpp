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

vector<chord> get_prog(int length, chord Imaj7, chord ii7, chord iii7, chord IVmaj7, chord V7, chord vi7, chord vii7b5) {
    int next_chord_picker = 0;
    chord next_chord = Imaj7;
    vector<chord> prog = { Imaj7, Imaj7 };
    vector<chord> aSection = {};
    vector<chord> bSection = {};
    vector<chord> cSection = {};
    next_chord_picker = rand() % (Imaj7.precedes.size());
    next_chord = *(Imaj7.precedes)[next_chord_picker];
    aSection.push_back(next_chord);
    while (aSection.size() < length) {
        next_chord_picker = rand() % (aSection.back().precedes.size());
        next_chord = *(aSection.back().precedes)[next_chord_picker];
        aSection.push_back(next_chord);
    }
    next_chord_picker = rand() % (aSection.back().precedes.size());
    next_chord = *(aSection.back().precedes)[next_chord_picker];
    bSection.push_back(next_chord);
    while (bSection.size() < length) {
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
    for (int i = 0; i < length; i++) { prog.push_back(aSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(aSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(aSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(aSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(cSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }
    for (int i = 0; i < length; i++) { prog.push_back(bSection[i]); }

    return prog;
}

void play_chord(chord current_chord, tuple<int, int, int, int> voicing, string quality, int root, float duration, fluid_synth_t* synth, unordered_map<string, int> roots, float measure, unordered_map<string, int> drum_sounds) {

    float h = 2 * duration; // half note
    float w = 2 * h;        // whole note
    float e = duration / 2; // eighth note
    float s = e / 2;        // sixteenth note

    vector<float> note_lengths = { w, h+duration, h, duration + e, duration, e + s, e, s }; // note lengths vector to randomly select note length

    // possible lengths for hi hat notes
    vector<float> hat_poss_notes = { duration + e, duration, e, e};

    // possible lengths for bass notes
    vector<float> bass_poss_notes = { h, h, duration + e, duration, e};

    // vector for the hi hat notes.  Used to randomly generate a hi hat pattern, which will be iterated through and played.
    vector<float> hat_notes = {}; 

    // vector for the bass notes.  Used to randomly generate a bass pattern, which will be iterated through and played.
    vector<float> bass_notes = {};

    // used to keep track of how long the rhythms generated are
    float hat_length = 0;
    float bass_length = 0;
    int chosen_note = 0;
    float chosen_length = 0;

    // fill hat_notes with a randomly generated rhythm
    while (hat_length < measure) {
        chosen_note = rand() % hat_poss_notes.size();
        if ((hat_length + hat_poss_notes.at(chosen_note)) > measure) {
            chosen_length = measure - hat_length;
        }
        else {
            chosen_length = hat_poss_notes.at(chosen_note);
        }
        hat_notes.push_back(chosen_length);
        hat_length += chosen_length;
    }

    //fill bass_notes with a randomly generated rhythm
    while (bass_length < measure) {
        chosen_note = rand() % bass_poss_notes.size();
        if((bass_length + bass_poss_notes.at(chosen_note)) > measure) {
            chosen_length = measure - bass_length;
        }
        else {
            chosen_length = bass_poss_notes.at(chosen_note);
        }
        bass_notes.push_back(chosen_length);
        bass_length += chosen_length;
    }

    // start drum beat thread 
    /*thread drum_thread([&]() {
        //std::cout << "thread function\n";
        float drum_playtime = 0;
        float drum_time = duration;
        while (drum_playtime < measure) {
            if ((drum_playtime + drum_time) > measure) {
                drum_time = measure - drum_playtime;
            }
            drum_playtime = drum_playtime + drum_time;

            /* -- drum note reference --
            { "bass_drum", 36},
            { "side_stick", 37 },
            { "snare", 38 },
            { "low_tom", 45 },
            { "low_mid_tom", 47 },
            { "high_mid_tom", 48 },
            { "high_tom", 50 },
            { "closed_hat", 42 },
            { "pedal_hat", 44 },
            { "open_hat", 46 },
            { "crash", 49 },
            { "ride", 51 },
            { "ride_bell", 52 },
            

            fluid_synth_noteon(synth, 9, drum_sounds["closed_hat"], 80);
            sleep(drum_time);
            fluid_synth_noteoff(synth, 9, drum_sounds["closed_hat"]);
        }
        }); */

    thread hat_thread([&]() {
        //std::cout << "thread function\n";
        float hat_playtime = 0;
        float hat_time = 0;
        int i = 0;
        while (hat_playtime < measure) {
            hat_time = hat_notes.at(i);

            /* -- drum note reference --
            { "bass_drum", 36},
            { "side_stick", 37 },
            { "snare", 38 },
            { "low_tom", 45 },
            { "low_mid_tom", 47 },
            { "high_mid_tom", 48 },
            { "high_tom", 50 },
            { "closed_hat", 42 },
            { "pedal_hat", 44 },
            { "open_hat", 46 },
            { "crash", 49 },
            { "ride", 51 },
            { "ride_bell", 52 },
            */

            fluid_synth_noteon(synth, 9, drum_sounds["closed_hat"], 80);
            sleep(hat_time);
            fluid_synth_noteoff(synth, 9, drum_sounds["closed_hat"]);
            i++;
            hat_playtime += hat_time;
        }
        });

    thread bass_thread([&]() {
        //std::cout << "thread function\n";
        float bass_playtime = 0;
        float bass_time = 0;
        int i = 0;
        while (bass_playtime < measure) {
            bass_time = bass_notes.at(i);

            /* -- drum note reference --
            { "bass_drum", 36},
            { "side_stick", 37 },
            { "snare", 38 },
            { "low_tom", 45 },
            { "low_mid_tom", 47 },
            { "high_mid_tom", 48 },
            { "high_tom", 50 },
            { "closed_hat", 42 },
            { "pedal_hat", 44 },
            { "open_hat", 46 },
            { "crash", 49 },
            { "ride", 51 },
            { "ride_bell", 52 },
            */

            fluid_synth_noteon(synth, 9, drum_sounds["bass_drum"], 80);
            sleep(bass_time);
            fluid_synth_noteoff(synth, 9, drum_sounds["bass_drum"]);
            i++;
            bass_playtime += bass_time;
        }
        });


    /* Play a note */
    int rt_val = root; // root note
    float playtime = 0; // initialize time played so far to 0

    // play the root in octaves
    fluid_synth_noteon(synth, 0, rt_val - 12, 80);
    fluid_synth_noteon(synth, 1, rt_val - 24, 80);

    //play chord with chosen voicing
    fluid_synth_noteon(synth, 2, rt_val + get<0>(voicing), 80);
    fluid_synth_noteon(synth, 3, rt_val + get<1>(voicing), 80);
    fluid_synth_noteon(synth, 4, rt_val + get<2>(voicing), 80);
    fluid_synth_noteon(synth, 5, rt_val + get<3>(voicing), 80);
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
            possible_notes.push_back(4);
            possible_notes.push_back(7);
            possible_notes.push_back(11);
        }

        else if (current_chord.get_quality().compare("minor") == 0) {
            possible_notes.push_back(0);
            possible_notes.push_back(2);
            possible_notes.push_back(5);
            possible_notes.push_back(9);
            possible_notes.push_back(4);
        }

        else if (current_chord.get_quality().compare("dominant") == 0) {
            possible_notes.push_back(11);
            possible_notes.push_back(2);
            possible_notes.push_back(7);
            possible_notes.push_back(5);
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
        //cout << playtime << " " << measure << endl;
        fluid_synth_noteon(synth, 7, note, 80);
        sleep(time);
        fluid_synth_noteoff(synth, 7, note);

    };
    //kill root notes
    fluid_synth_noteoff(synth, 0, rt_val - 12);
    fluid_synth_noteoff(synth, 1, rt_val - 24);
    /* Stop the note */
    fluid_synth_noteoff(synth, 2, rt_val + get<0>(voicing));
    fluid_synth_noteoff(synth, 3, rt_val + get<1>(voicing));
    fluid_synth_noteoff(synth, 4, rt_val + get<2>(voicing));
    fluid_synth_noteoff(synth, 5, rt_val + get<3>(voicing));

    hat_thread.join();
    bass_thread.join();
}