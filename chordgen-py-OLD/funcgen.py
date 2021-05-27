import random

class chord:
    def __init__(self, symbol="No Chord", root=-1, chordtones=[], voicings=[], precedes=[], follows=[], quality="none"):
        self.symbol = symbol
        self.root = root
        self.chordtones = chordtones
        self.voicings = voicings
        self.precedes = precedes
        self.follows = follows
        self.quality = quality

'''
Notation so far:
(uppercase_letter)maj7 = major
(lowercase_letter)_7 = minor
(uppercase_letter)7 = dominant

'''

Imaj7 = chord("Imaj7", 0, [0, 4, 7, 11], [[11, 14, 16, 19], [4, 7, 11, 14], [-1, 4, 7, 14], [4, 11, 14, 19]], [], [], "major")
ii7 = chord("ii7", 2, [2, 5, 9, 0], [[0, 4, 5, 9], [5, 9, 12, 16], [0, 5, 9, 16], [5, 12, 16, 21]], [], [], "dorian")
iii7 = chord("iii7", 4, [4, 7, 11, 2], [[2, 6, 7, 11], [7, 11, 14, 18], [2, 7, 11, 18], [7, 14, 18, 23]], [], [], "phrygian")
IVmaj7 = chord("IVmaj7", 5, [5, 9, 0, 4], [[4, 7, 9, 12], [-3, 0, 4, 7], [4, 9, 12, 19], [-3, 4, 7, 12]], [], [], "major")
V7 = chord("V7", 7, [7, 2, 11, 5], [[5, 9, 11, 14], [-1, 2, 5, 9], [5, 11, 14, 21], [-1, 5, 9, 14]], [], [], "dominant")
vi7 = chord("vi7", 9, [9, 0, 4, 7], [[7, 11, 12, 16], [0, 4, 7, 11], [7, 12, 16, 23], [0, 7, 11, 16]], [], [], "aeolian")
vii7b5 = chord("vii7b5", 11, [11, 2, 5, 9], [[2, 5, 9, 13], [9, 13, 14, 17], [-3, 2, 5, 13], [2, 9, 13, 17]], [], [], "dominant")

# Chords I haven't implemented yet
VI7 = chord("VI7", 9, [9, 1, 4, 7], [], [], [])
VII7 = chord("VII7", 11, [11, 3, 6, 9], [], [], [])
I7 = chord("I7", 0, [0, 4, 7, 10], [], [], [])
II7 = chord("II7", 2, [2, 6, 9, 0], [], [], [])
III7 = chord("III7", 4, [4, 8, 11, 2], [], [], [])
bII7 = chord("bII7", 1, [1, 5, 8, 11], [], [], [])
bIII7 = chord("bIII7", 3, [3, 7, 10, 1], [], [], [])
IV7 = chord("IV7", 5, [5, 9, 0, 3], [], [], [])
bVI7 = chord("bVI7", 8, [8, 0, 3, 6], [], [], [])
bVII7 = chord("bVII7", 10, [10, 2, 5, 8], [], [], [])

Imaj7.precedes = [ii7, IVmaj7, V7, vi7]
Imaj7.follows = [ii7, iii7, IVmaj7, V7]

ii7.precedes = [Imaj7, iii7, V7]
ii7.follows = [IVmaj7, vi7]

iii7.precedes = [Imaj7, vi7]
iii7.follows = [ii7, V7]

IVmaj7.precedes = [Imaj7, ii7, V7]
IVmaj7.follows = [V7, vi7]

V7.precedes = [Imaj7, iii7, IVmaj7, vi7]
V7.follows = [ii7, IVmaj7]

vi7.precedes = [Imaj7, ii7, IVmaj7]
vi7.follows = [Imaj7, iii7, V7]

tonic = [Imaj7]
tonic_ext = [vi7, iii7]
dominant = [V7, vii7b5]
subdominant = [ii7, IVmaj7]

secondary_dominant = {Imaj7 : V7,
                      ii7 : VI7,
                      iii7 : VII7,
                      IVmaj7 : I7,
                      V7 : II7,
                      vi7: III7}

tritone_sub = {V7 : bII7,
               VI7 : bIII7,
               VII7 : IV7,
               II7 : bVI7,
               III7 : bVII7,
               IV7 : VII7}

class scale:
    def __init__(self, name="Empty", tones=[], goes_with="N/A"):
        self.name = name
        self.tones = tones
        self.goes_with = goes_with

major = scale("major", [0, 2, 4, 5, 7, 9, 11], goes_with="major")
mixolydian = scale("mixolydian", [0, 2, 4, 5, 7, 9, 10], goes_with="dominant")
minor = scale("minor", [0, 2, 3, 5, 7, 9, 10], goes_with="minor")

scales = [major, mixolydian, minor]

def getProg(length): 
    prog = [Imaj7]
    while len(prog) < length:
        # n = []
        nextChord = random.choice(prog[-1].precedes)
        # n.append(nextChord)
        # n.append(closest_voicing(prog[-1][1], nextChord))
        # prog.append(n)
        prog.append(nextChord)
    return prog
    

