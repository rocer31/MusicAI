#include "noteplayer.h" // using namespace std;

int get_key(char letter, char indicator) {

    //  0    1     2    3     4    5    6     7    8     9    10    11
    //  C    C#    D    Eb    E    F    F#    G    G#    A    Bb    B
    bool is_sharp = false;
    bool is_flat = false;
    if (indicator == '#') { is_sharp = true; }
    if (indicator == 'b') { is_flat = true; }
    switch (letter) {
    case 'C':
        if (is_sharp) {
            return 1;
        }
        if (is_flat) {
            return 11;
        }
        return 0;
    case 'D':
        if (is_sharp) {
            return 3;
        }
        if (is_flat) {
            return 1;
        }
        return 2;
    case 'E':
        if (is_sharp) {
            return 5;
        }
        if (is_flat) {
            return 3;
        }
        return 4;
    case 'F':
        if (is_sharp) {
            return 6;
        }
        if (is_flat) {
            return 4;
        }
        return 5;
    case 'G':
        if (is_sharp) {
            return 8;
        }
        if (is_flat) {
            return 6;
        }
        return 7;
    case 'A':
        if (is_sharp) {
            return 10;
        }
        if (is_flat) {
            return 8;
        }
        return 9;
    case 'B':
        if (is_sharp) {
            return 0;
        }
        if (is_flat) {
            return 10;
        }
        return 11;
    default:
        return rand() % 12;
    }
}

int main(int argc, char** argv)
{
    cout << "============ START ============" << endl;
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    int sfont_id;
    int key;
    string keyname;
    /* Create the settings. */
    settings = new_fluid_settings();
    /* Change the settings if necessary*/
    /* Create the synthesizer. */
    synth = new_fluid_synth(settings);
    /* Create the audio driver. The synthesizer starts playing as soon
       as the driver is created. */
    adriver = new_fluid_audio_driver(settings, synth);
    /* Load a SoundFont and reset presets (so that new instruments
     * get used from the SoundFont) */
    sfont_id = fluid_synth_sfload(synth, "arachno.sf2", 1);
    /* Initialize the random number generator */

    // Set Instruments. Bass is on chn 0 and 1, chords are channels 2, 3, 4, 5, and melody is on channel 7. Drums on channel 9 ---------------------------------------

    // Bass
    fluid_synth_program_change(synth, 0, 33);
    fluid_synth_program_change(synth, 1, 33);

    // Chords
    fluid_synth_program_change(synth, 2, 4);
    fluid_synth_program_change(synth, 3, 4);
    fluid_synth_program_change(synth, 4, 4);
    fluid_synth_program_change(synth, 5, 4);

    // Melody
    fluid_synth_program_change(synth, 7, 66);

    fluid_synth_program_reset(synth);

    //------------------------------------------------------------------------------------------------

    // for basic testing. remove this later
    unordered_map<string, tuple<int, int, int, int>> chords = {
        {"major", make_tuple(0, 4, 7, 11)},
        {"minor", make_tuple(0, 3, 7, 10)},
        {"diminished", make_tuple(0, 3, 6, 9)}
    };

    // TODO: define these in header and not here
    chord Imaj7 = chord("Imaj7", 0, std::make_tuple(0, 4, 7, 11), { std::make_tuple(11, 14, 16, 19), std::make_tuple(4, 7, 11, 14), std::make_tuple(-1, 4, 7, 14), std::make_tuple(4, 11, 14, 19) }, {}, {}, "major");
    chord ii7 = chord("ii7", 2, std::make_tuple(2, 5, 9, 0), { std::make_tuple(0, 4, 5, 9), std::make_tuple(5, 9, 12, 16), std::make_tuple(0, 5, 9, 16), std::make_tuple(5, 12, 16, 21) }, {}, {}, "minor");
    chord iii7 = chord("iii7", 4, std::make_tuple(4, 7, 11, 2), { std::make_tuple(2, 6, 7, 11), std::make_tuple(7, 11, 14, 18), std::make_tuple(2, 7, 11, 18), std::make_tuple(7, 14, 18, 23) }, {}, {}, "minor");
    chord IVmaj7 = chord("IVmaj7", 5, std::make_tuple(5, 9, 0, 4), { std::make_tuple(4, 7, 9, 12), std::make_tuple(-3, 0, 4, 7), std::make_tuple(4, 9, 12, 19), std::make_tuple(-3, 4, 7, 12) }, {}, {}, "major");
    chord V7 = chord("V7", 7, std::make_tuple(7, 2, 11, 5), { std::make_tuple(5, 9, 11, 14), std::make_tuple(-1, 2, 5, 9), std::make_tuple(5, 11, 14, 21), std::make_tuple(-1, 5, 9, 14) }, {}, {}, "dominant");
    chord vi7 = chord("vi7", 9, std::make_tuple(9, 0, 4, 7), { std::make_tuple(7, 11, 12, 16), std::make_tuple(0, 4, 7, 11), std::make_tuple(7, 12, 16, 23), std::make_tuple(0, 7, 11, 16) }, {}, {}, "minor");
    chord vii7b5 = chord("vii7b5", 11, std::make_tuple(11, 2, 5, 9), { std::make_tuple(2, 5, 9, 13), std::make_tuple(9, 13, 14, 17), std::make_tuple(-3, 2, 5, 13), std::make_tuple(2, 9, 13, 17) }, {}, {}, "dominant");

    Imaj7.precedes.push_back(&ii7);
    Imaj7.precedes.push_back(&iii7);
    Imaj7.precedes.push_back(&IVmaj7);
    //Imaj7.precedes.push_back(&V7);
    Imaj7.precedes.push_back(&vi7);

    Imaj7.follows.push_back(&ii7);
    Imaj7.follows.push_back(&iii7);
    Imaj7.follows.push_back(&IVmaj7);
    Imaj7.follows.push_back(&V7);

    //----

    ii7.precedes.push_back(&Imaj7);
    //ii7.precedes.push_back(&iii7);
    ii7.precedes.push_back(&V7);

    ii7.follows.push_back(&IVmaj7);
    ii7.follows.push_back(&vi7);

    //----

    iii7.precedes.push_back(&Imaj7);
    iii7.precedes.push_back(&vi7);

    //iii7.follows.push_back(&ii7);
    iii7.follows.push_back(&V7);

    //----

    //IVmaj7.precedes.push_back(&Imaj7);
    IVmaj7.precedes.push_back(&ii7);
    IVmaj7.precedes.push_back(&V7);

    IVmaj7.follows.push_back(&V7);
    IVmaj7.follows.push_back(&vi7);

    //----

    V7.precedes.push_back(&Imaj7);
    //V7.precedes.push_back(&iii7);
    //V7.precedes.push_back(&IVmaj7);
    V7.precedes.push_back(&vi7);

    V7.follows.push_back(&ii7);
    V7.follows.push_back(&IVmaj7);

    //----

    vi7.precedes.push_back(&Imaj7);
    vi7.precedes.push_back(&ii7);
    vi7.precedes.push_back(&IVmaj7);

    vi7.follows.push_back(&Imaj7);
    vi7.follows.push_back(&iii7);
    vi7.follows.push_back(&V7);

    //----

    vii7b5.precedes.push_back(&Imaj7);
    vii7b5.precedes.push_back(&iii7);
    vii7b5.precedes.push_back(&IVmaj7);
    vii7b5.precedes.push_back(&vi7);

    vii7b5.follows.push_back(&ii7);
    vii7b5.follows.push_back(&IVmaj7);

    //----
    // TODO: save all chords in a vector
    //vector<chord> all_chords;





    // define list of root notes (possibly move this somewhere else)
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

    unordered_map<string, int> drum_sounds = {
        {"bass_drum", 36},
        {"side_stick", 37},
        {"snare", 38},
        {"low_tom", 45},
        {"low_mid_tom", 47},
        {"high_mid_tom", 48},
        {"high_tom", 50},
        {"closed_hat", 42},
        {"pedal_hat", 44},
        {"open_hat", 46},
        {"crash", 49},
        {"ride", 51},
        {"ride_bell", 52},
    };

    int octave = 12; // add or subtract by this to shift notes by octaves

    srand((int)time(NULL));



    if (sfont_id == FLUID_FAILED)
    {
        puts("Loading the SoundFont failed!");
        //goto err;
    }


    /* argument processing */

    ///////////////////////////////////////////////////////////////
    //                          defaults                         //
    ///////////////////////////////////////////////////////////////

    // choose key -k

    /*
    if (argc == 0) {
        key = roots["E"];
        keyname = "E";
    }
    else {
        key = roots[string(argv[0])];
        keyname = string(argv[0]);
    }
    */

    // choose tempo -t
    float bpm = 97;
    float q = 60 / bpm; // quarter note

    // choose time signature
    float beats = 4;
    float measure = beats * q;

    // choose form -f
    // -form is currently AABA

    // form vector to be able to read in the form
    vector<char> form = {};

    //form given by the command line, defaulted to "aaba"
    string form_input = "aaba";

    // used for reading the form input
    char current_letter;

    // form length -fl
    float length = 4; // measures per section
    /*
    if (bpm / 160 > 0) {
        beats *= (bpm / 160);
    }
    */

    // repeat form -r
    int repeats = 1; // 1 = AABA, 2 = AABAAABA, etc

    ///////////////////////////////////////////////////////////////
    //                     argument processing                   //
    ///////////////////////////////////////////////////////////////

    int a_key = 0;
    bool chose_key = false;
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                switch (argv[i][1]) {
                case 'k': {
                    /*
                    string got_key = get_key(argv[i + 1][0], argv[i + 1][1]);
                    key = roots[got_key];
                    keyname = got_key;
                    */
                    // set a_key using a method written for literally this purpose
                    a_key = get_key(argv[i + 1][0], argv[i + 1][1]);
                    // sets a flag so that we don't randomly re-generate the a_key
                    chose_key = true;
                    break;
                }
                case 't':
                    bpm = *(float*)argv[i + 1];
                    break;
                case 'b':
                    beats = *(float*)argv[i + 1];
                    break;

                case 'f':

                    if (argv[i][2] == 'l') {
                        length = *(float*)argv[i + 1];
                        break;
                    }
                    form_input = string(argv[i + 1]);
                    break;
                case 'r':
                    repeats = *(int*)argv[i + 1];
                }
            }
        }
    }
    ///////////////////////////////////////////////////////////////
    //                done argument processing                   //
    ///////////////////////////////////////////////////////////////

    int i = 0;
    // take in form
    while (i < form_input.length()) {
        current_letter = form_input.at(i);
        form.push_back(current_letter);
        i++;
    }

    // pick a random A key
    if (!chose_key) { a_key = rand() % 12; }

    // pick a B key, that is modulated from the A key
    int b_key;
    if (a_key + 5 > 11) {
        b_key = (a_key + 5) % 12;
    }
    else {
        b_key = a_key + 5;
    }
    // pick a C key, which right now is un-used because I didn't know what to do with that
    int c_key = 0;

    // this vector is used to get the keys in the order they're supposed to play at
    vector<int> form_nums = {};

    // iterate through the form, and populate our form_nums vector with the correct key;
    for (int j = 0; j < repeats; j++) {
        for (i = 0; i < form.size(); i++) {
            switch (form.at(i)) {
            case 'a':
                form_nums.push_back(a_key);
                break;
            case 'b':
                form_nums.push_back(b_key);
                break;
            case 'c':
                form_nums.push_back(c_key);
                break;
            default:
                form_nums.push_back(a_key);
                break;
            }
        }
    }
    // form_place is used to keep track of where we are in the form
    int form_place = 0;
    // current_key is used to keep track of which key we should be in
    int current_key = form_nums.at(form_place);

    //Key center in major, TODO: implemnt minor
    vector<string> keys = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B" }; // 11
    // int keynum = rand() % 12;
    keyname = keys.at(current_key);
    key = roots[keyname];
    // int key_begin = keynum;

    std::tuple<int, int, int, int> to_play = Imaj7.get_tones();


    /* -END CONFIGURATION- */

    /* -BEGIN MUSIC GENERATION- */

    cout << "Key of " << keyname << endl;
    vector<chord> prog = get_prog(form_input, length, repeats, Imaj7, ii7, iii7, IVmaj7, V7, vi7, vii7b5);
    /*cout << "Prog: " << endl; -------------- prints entire progression right away. for debugging
    for (int i = 0; i < prog.size(); i++) {
        cout << prog[i].get_symbol() << endl;
    }*/

    tuple<int, int, int, int> voicing_init = Imaj7.get_voicings()[0];
    tuple<int, int, int, int> voicing_choice = closest_voicing(voicing_init, prog[0]);


    int ctr = 0;
    int past_key = 0;
    ////////////////////////////////////////////
    int repeat_chance = 1; //for testing
    ////////////////////////////////////////////

    for (auto it = prog.begin(); it != prog.end(); it++) {
        cout << it->get_symbol() << endl;
        voicing_choice = closest_voicing(voicing_choice, *it);
        if ((ctr != 0) && (rand() % repeat_chance < 1)) {
            if ((fmod((float)ctr, length) == 0.0) && ((it + 1) != prog.end())) {
                if (current_key == form_nums.at(form_place + 1)) {
                    repeat(drum_sounds);
                }
            }
        }
        else {
            play_chord(*it, voicing_choice, it->get_quality(), it->get_root() + key, q, synth, roots, measure, drum_sounds, beats);
        }
        ctr++;
        if ((fmod((float)ctr, length) == 0.0) && ((it + 1) != prog.end())) {
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
        /*
        if ((ctr % 8 == 0) && (keynum + 5 <= 11)) {
            keynum = keynum + 5;
            keyname = keys[keynum];
            key = roots[keys[keynum]];
            cout << "Modulated to " << keys[keynum] << endl;
        }
        else if ((ctr % 8 == 0) && (keynum + 5 > 11)) {
            keynum = (keynum + 5) % 12;
            keyname = keys[keynum];
            key = roots[keys[keynum]];
            cout << "Modulated to " << keys[keynum] << endl;
        }
        if ((ctr == 12)) {
            keynum = key_begin;
            keyname = keys[keynum];
            key = roots[keys[keynum]];
            cout << "Modulated to " << keys[keynum] << endl;
        }
        */
    }
    play_chord(Imaj7, Imaj7.get_voicings()[0], Imaj7.get_quality(), Imaj7.get_root(), q, synth, roots, measure, drum_sounds, beats);

    /* -END MUSIC GENERATION- */


    /* -BEGIN ERROR HANDLING/SHUTDOWN- */

    //err:     TODO: reimplemnt this
        /* Clean up */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
    return 0;
}

