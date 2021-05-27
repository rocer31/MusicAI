/**
* Team MusicAI
* this is the file where random numbers and lists become music.
* maintainers:
*
* Vinny Taylor
* Andrew Johnson
* Max Perry
* Zoey Xiao
* Reilly Yankovich
*
* Version 0.0.1?  Idk I put this to look more official
*
*/
#include <stdlib.h>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////
                    //class definitions
////////////////////////////////////////////////////////////////

//Chord class, used in chord generation and melody generation
class Chord {
	string name, mode; //idk if mode is the right word, this is the major, dominant, dorian, etc.
    short tones[][]; //this is where the numbers go, idk how to represent them exactly.  I want to do char[][],
    //but idk if that's the best way to implement this.
    Chord proceeds[], follows[]; //need a size, it looks like 4 but I don't want to assume that

    public:
        Chord(string n, string m, short[][] t, Chord[] p, Chord[] f) {  //this may get wonky
            this->name = n;
            this->mode = m;
            this->tones = t;
            this->proceeds = p; //specifically this part
            this->follows = f;
        }
}

//create chords for use in chord gen
//Chord imaj7 = new Chord("Imaj7", "major", [[0], [0, 4, 7, 11], []], NULL, NULL); //fill out rest of the things
//Chord 

//creates a chord progression for length and returns it
Chord[] getProgression(length) {
    //TODO: write this
    return NULL;
}

//scale class, used in melody generation
class Scale {
    string goes_with; //the goes_with I'm assuming should be a string
    short notes[7]; //this can change, I only put it as this for now

    public:
        Scale(string g, short n[]) { //once again, may get wonky
            this->goes_with = g;
            this->notes = n; //mainly this part
        }
}

//create scales for use in melody gen
Scale ionian = new Scale("major", [0, 2, 4, 5, 7, 9, 11]);
Scale dorian = new Scale("minor", [0, 2, 3, 5, 7, 9, 10]);
Scale phrygian = new Scale("minor", [0, 1, 3, 5, 7, 8, 10]);
Scale lydian = new Scale("major", [0, 2, 4, 6, 7, 9, 11])
Scale mixolydian = new Scale("dominant", [0, 2, 4, 5, 7, 9, 10]);
Scale aeolian = new Scale("minor", [0, 2, 3, 5, 7, 8, 10]);
Scale locrian = new Scale("diminished", [0, 1, 3, 5, 6, 8, 10]);

Scale harmonic_minor = new Scale("minor", [0, 2, 3, 5, 7, 8, 11]);
Scale melodic_minor = new Scale("minor", [0, 2, 3, 5, 7, 9, 11]);

Scale altered = new Scale("diminished", [0, 1, 3, 4, 6, 8, 10]

//make the array of scales; add to this as scales are added
Scale scales[] = {ionian, dorian, phrygian, lydian, mixolydian, aeolian, locrian,
		harmonic_minor, melodic_minor, altered};

//class for Instrument
class Instrument {
    short octave;  //default octave
    string name; //name of instrument
    public:
        Instrument(short o, string n) {
            this->octave = o;
            this->name = n;
        }
}
//for these, I made the default octave the one that most musicians will
//only go within one octave difference from the center; for example,
//most trumpet players only go between C4 and C6, so default is 5;
//also, these are all guesses more or less, except the piano one.
Instrument Bass = new Instrument(2, "bass"); //don't know about this one
Instrument Trombone = new Instrument(3, "trombone");
Instrument Piano = new Instrument(4, "piano");
Instrument Trumpet = new Instrument(5, "trumpet");
Instrument Flute = new Instrument(6, "flute");


class Note {
    short midi;
    string name;
    public:
        Note(short m, string n) {
            this->midi = m;
            this->name = n;
        }
}


////////////////////////////////////////////////////////////////
                    //melody generation
////////////////////////////////////////////////////////////////


//main method, where the parameters are interpreted
int main(int argc, char *argv[]) {
    //defining starting parameters, will be changed in main method
    //by getting input from Max's GUI
    //short key = 0;
    short bpm = 80;
    short length = 16;
    short beats = 4;
    //un-comment this if we implement denominator changes
    //short denom = 4;
    int i;
    //read in arguments
    for (i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'k':
                    //key = notes[]; //write this part
                    break;
                case 't':
                    bpm = *(short*)argv[i + 1];
                    break;
                case 'l':
                    length = *(short*)argv[i + 1];
                    break;
                case 'b':
                    beats = *(short*)argv[i+1];
                    break;
                //un-comment this if we implement denominator changes
                //case 'd':
                    //denom = *(short*)argv[i + 1];
                default:
                    //stand in error message, I just needed to put something here
                    cerr << "ERROR: input not recognized: -" << argv[i][1] << ".  input is being ignored" << endl;
                    break;
            }
        }
    }
    
    //if we add in the capacity to change the denominator, this will get uncommented
    /*
    if (denom != 4) {
        switch denom:
        case 1:
            bpm /= 4;
            break;
        case 2:
            bpm /= 2;
            break;
        case 8:
            bpm *= 2;
            break;
        case 16:
            bpm *= 4;
            break;
        case 32:
            bpm *= 8;
            break;
        case 64:
            bpm *= 16;
            break;
        default:
            cerr << "ERROR: denominator not a power of 2 between 1 and 64.  defaulting to 4" << endl;
            break;
    }
    */

    //note durations calculated based on the input
    short quarterNote = 60/bpm;
    short halfNote = 2 * quarterNote;
    short wholeNote = 2 * halfNote;
    short eighthNote = quarterNote / 2;
    short sixteenthNote = eighthNote / 2;
    //commented these out, idk if we'll ever need them but I figured I'd include them
    //short thSecondNote = sixteenthNote / 2;
    //short sixFourthNote = thSecondNote / 2;
    //add the two above variables to this array if we decide to add them
    short lengths[] = {wholeNote, (halfNote + quarterNote), halfNote, (quarterNote + eighthNote), quarterNote, (eighthNote + sixteenthNote), eighthNote, sixteenthNote};

    short measure = beats * quarterNote;

    Chord prog[] = getProgression(length);
    for (currChord : prog) {
    //this is commented out until I figure out everything needed in play_chord
    //also Vinny should probably do this part?
    //play_chord(measure, lengths, quality, ...);
    }
    
}

//plays a single note
void play_note(Instrument instrument, Note note, short duration) {
    //rest
    if (note == NULL) {
        std::sleep(duration);
        return;
    }
    //use fluidsynth stuff
    /*
    short tone = note.midi + (instrument.octave * 12);
    if (!instrument.name.compare("piano")) { play piano from soundfont}
    else if(!instrument.name.compare("trumpet")) { pick trumpet soundfont}
    etc
    play the note with tone, duration, and soundfont
    yay
    */
}

// plays a chord, and then plays melody over it.
// These will probably be separated at some point, but for now, they're together.
void play_chord(short measure, short[] lengths, string quality) {
    //chord making

    //melody time
    short rest_chance = 7;
    short triplet_chance = 4;
    short playtime = 0;
    short time = 0;
    int i;
    //we can change this to allow for other scales, right?
    //assuming we change the chord generator to allow for it as well
    Scale scaleUsed = scales[0];
    while (playtime < measure) {
        Note possible_notes[7];
        /*
        if (!quality.compare("dominant")) {
            for (i = 1; i < scaleUsed.length; i++) {
                possibleNotes[i - 1] = scaleUsed/notes[i];
            }
        }
        */
        Note note = possible_notes[rand() % 7];
        //1/4 chance of there being a rest; can be changed later
        if ((rand() % rest_chance) < 1) { note = NULL; }
        Note lastNote = NULL;
        //pick note
	time = lengths[rand() % 7]; if (playtime + time > measure) { time =
		measure - playtime; }
        //this change is done before any advanced thing to be able to do funky things with time,
        //such as triplets, which require 3 notes at 1/3 time
        playtime += time;

        //triplets randomly chosen
        if ((note != NULL) && (time > eighthNote) && ((rand() % triplet_chance) < 1)) {
            time /= 3;
            play_note(instrument_chosen, note, time);
            note = possible_notes[rand() % 7];
            if (rand() % 4 < 1) { note = NULL; }
            play_note(instrument_chosen, note, time);
            }
        }
        if (note != NULL) { lastNote = note; }
        //play the note regardless of funkiness that happens before.
        //because of this, each funky thing should use one less note than it would
        //if it was all done in that funky thing.  For example, in the triplet block,
        //there should only be two calls of play_note, and the last one is the
        //one below.
        play_note(instrument_chosen, note, time);

        //handling sixteenth notes to avoid extreme syncopation
        //if we add 32nd and 64th notes, this stuff will need to be updated as well
        if ((time == lengths[5]) || (time == lengths[7])) {
            note = possible_notes[rand() % 7];
            play_note(instrument_chosen, note, sixteenthNote);
        }
    }

}
