import random
from enum import Enum

notes = ("C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B")

chords = {'I': (0, 4, 7),
          'ii': (2, 5, 9),
          'iii': (4, 7, 11),
          'IV': (5, 9, 0),
          'V': (7, 11, 2),
          'vi': (9, 0, 4),
          #'vii': (11, 2, 5),
          'IV/I': (0, 5, 9),
          'V/I': (0, 7, 11, 2),
          'I/V': (7, 0, 4),
          'VI': (9, 1, 4),
          'iii7b5': (4, 7, 10, 2),
          'II': (2, 6, 9),
          'i6': (0, 3, 7, 9),
          'vi7b5/b3': (0, 9, 3, 7)
          }

graph = {'I': ['IV/I','V/I'],
         'ii': ['I','iii','V','I/V'],
         'iii': ['I','vi','IV'],
         'IV': ['I','V','ii'],
         'V': ['I','iii'],
         'vi': ['IV','ii'],
         #'vii': ['I'],
         'IV/I': ['I'],
         'V/I': ['I'],
         'I/V': ['I'],
         'VI': ['ii'],
         'iii7b5': ['VI'],
         'II': ['V'],
         'i6': ['II'],
         'vi7b5/b3': ['II']}


def getChord(romanNumeral, key):
    chord_tones = []
    x = chords[romanNumeral]
    for tone in x:
        tone += notes.index(key)
        if tone > 11:
            tone -= 12
        chord_tones.append(tone)

    i = 0
    for note in chord_tones:
        chord_tones[i] = notes[note]
        i += 1
    return chord_tones

def nextChord(chord):
    if(chord == 'I'):
        return random.choice((list(chords))[1:])
    
    return random.choice(graph[chord])

def getProgFromChord(start):
    prog = []
    prog.append(start)
    currentChord = nextChord(start)
    while(currentChord != 'I'):
        prog.append(nextChord(currentChord))
        currentChord = prog[-1]
    print(prog)
    midiNotes = []
    for chord in prog:
        midiNotes.append(chords[chord])
    return midiNotes

def getProgWithNum(num):
    prog = ['I']
    currentChord = nextChord('I')
    while(len(prog) < num):
        prog.append(currentChord)
        currentChord = nextChord(currentChord)
    midiNotes = []
    for chord in prog:
        midiNotes.append(chords[chord])
    return midiNotes

#progression = getProgWithNum(4)
#for chord in progression:
    #print(chords[chord])
