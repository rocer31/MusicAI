import sys
import time
import rtmidi
import random

from funcgen import *

notes = ["C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"]

# Midi output setup
midiout = rtmidi.MidiOut()
available_ports = midiout.get_ports()

if available_ports:
    midiout.open_port(0)
else:
    midiout.open_virtual_port("My virtual output")

# Decide key
key = 0

# Tempo declaration
bpm = 80

length = 16

beats = 4

for i in range(len(sys.argv)):
    if(sys.argv[i] == "-k"):
        key = notes.index(sys.argv[i + 1])
    elif(sys.argv[i] == "-t"):
        bpm = int(sys.argv[i + 1])
    elif(sys.argv[i] == "-l"):
        length = int(sys.argv[i + 1])
    elif(sys.argv[i] == "-b"):
        beats = float(sys.argv[i + 1])

# Note durations
q = 60/bpm  # quarter note
h = 2 * q   # half note
w = 2 * h   # whole note
e = q / 2   # eighth note
s = e / 2   # sixteenth note

measure = beats * q # length of measure

def play_note(note, duration): # Plays a single note
    if note == None:
        time.sleep(duration)
        return
    
    note_on = [0x90, note, 127] # Note start, note value, velocity (0-127)
    note_off = [0x80, note, 0] 
    midiout.send_message(note_on)
    time.sleep(duration)
    midiout.send_message(note_off)

def play_chord(voicing, quality, root, duration): # Plays a chord given a tuple of ints
    # Play the root in octaves
    midiout.send_message([0x90, int(root) + 24 + key, 127])
    midiout.send_message([0x90, int(root) + 36 + key, 127])
    for var in voicing: # Send note_on messages for each note
        note = int(var) + 60 + key
        note_on = [0x90, note, 112]
        midiout.send_message(note_on)
    
    # code for playing the melody. plays chord for 1 measure, and randomly chooses quarter and eighth notes from the chord to play over that measure
    
    playtime = 0
    scale = major
    note = 72 + key
    lastnote = 72 + key
    while playtime < measure:
        possible_notes = []

        # Determine by chord quality which notes we can play
        if quality == "dominant":
            possible_notes.extend(scale.tones[1::])
        elif quality == "major":
            possible_notes.extend(scale.tones[0:3])
            possible_notes.extend(scale.tones[4:6])
        elif quality == "phrygian":
            possible_notes.extend(scale.tones[1:3])
            possible_notes.extend(scale.tones[4::])
        elif quality == "dorian":
            possible_notes.extend(scale.tones[0:1])
            possible_notes.extend(scale.tones[3:6])
        elif quality == "aeolian":
            possible_notes.extend(scale.tones[0:3])
            possible_notes.extend(scale.tones[4:6])

        # Bias the possible notes towards chord tones
        for tone in voicing:
            possible_notes.append(tone % 12)
        
        # Adjust by octaves to minimize jumps
        for tone in possible_notes:
            if abs(lastnote - tone) > 7:
                if abs(lastnote - (tone - 12)) <= 7:
                    possible_notes.append(tone - 12)
                    possible_notes.remove(tone)
                elif abs(lastnote - (tone + 12)) <= 7:
                    possible_notes.append(tone + 12)
                    possible_notes.remove(tone)

        # Adjust note to correct octave and key
        note = random.choice(possible_notes) + 72 + key

        # 1 in 7 chance to replace note with a rest
        note = random.choices([note, None], weights = [6, 1], k=1)[0]

        # Possible rhythmic durations
        time = random.choices([w, (h + q), h, (q + e), q, (e + s), e, s], weights=[1, 2, 3, 4, 10, 3, 10, 3], k=1)[0]
        
        # Measure handling
        if ((playtime + time) > measure):
            time = measure - playtime
        playtime = playtime + time
        if note != None:
            lastnote = note
        
        # Play note with given pitch and duration
        play_note(note, time)

        # Handling sixteenth notes to prevent extreme syncopation   
        if(time == s or time == (e + s)):
            note = random.choice(possible_notes) + 72 + key
            play_note(note, s)
            playtime = playtime + s
        
    # Stop the bass note
    midiout.send_message([0x80, int(root) + 24 + key, 0])
    midiout.send_message([0x80, int(root) + 36 + key, 0])

    for var in voicing: # Send note_off messages for each note
        note = int(var) + 60 + key
        note_off = [0x80, note, 0]
        midiout.send_message(note_off)

def closest_voicing(currentVoicing, nextChord):
    best = -1
    min_change = 999
    for i in range(4):
        voicing = nextChord.voicings[i]
        semitones = 0
        for j in range(min(len(currentVoicing), len(voicing))):
            semitones += abs(currentVoicing[j] - voicing[j])
        if semitones < min_change:
            min_change = semitones
            best = i
    if best >= 0:
        return nextChord.voicings[best]
    else:
        return random.choice(nextChord.voicings)

print("Key of " + notes[key])
prog = getProg(length)
lastVoicing = []
for chord in prog:
    print(chord.symbol)
    root = chord.root
    voicing = closest_voicing(lastVoicing, chord)
    quality = chord.quality
    lastVoicing = voicing
    play_chord(voicing, quality, root, h)

time.sleep(0.1)
del midiout
