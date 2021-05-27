import numpy
import pyaudio
import time
from cmath import exp, pi


def fft(a):
    N = len(a)
    if N <= 1: return a
    even = fft(a[0::2])
    odd = fft(a[1::2])
    T = [exp(-2j * pi * k / N) * odd[k] for k in range(N // 2)]
    return [even[k] + T[k] for k in range(N // 2)] + [even[k] - T[k] for k in range(N // 2)]


def main():
    NOTE_MIN = 21
    NOTE_MAX = 108
    SAMPLING_FRAME = 22050  # Sampling frequency in Hz       ORIGINAL: 22050
    FRAME_SIZE = 2048  #                                    ORIGINAL: 2048
    FRAMES_PER_FFT = 16  # Average across how many frames    ORIGINAL: 16
    SAMPLES_PER_FFT = FRAME_SIZE * FRAMES_PER_FFT
    FREQ_STEP = float(SAMPLING_FRAME) / SAMPLES_PER_FFT
    NOTE_NAMES = 'A A# B C C# D D# E F F# G G#'.split()

    # from https://newt.phys.unsw.edu.au/jw/notes.html

    def freq_to_midi(f):
        #Needs to be hardcoded to 69(A4) because that is 440 and it measures how far
        #from 440 the note is
        return 69 + 12 * numpy.log2(f / 440.0)

    def midi_to_freq(m):
        return 440 * 2.0 ** ((m - NOTE_MAX) / 12.0)

    def note_name(m):
        #+3 so that I can keep NOTE_NAMES starting at A
        return NOTE_NAMES[(m+3) % 12] + str(m//12 - 1)

    def note_to_fftbin(m):
        return midi_to_freq(m) / FREQ_STEP

    imin = max(0, int(numpy.floor(note_to_fftbin(NOTE_MIN - 1))))
    # 4 and 693
    imax = min(SAMPLES_PER_FFT, int(numpy.ceil(note_to_fftbin(NOTE_MAX + 1))))

    buf = numpy.zeros(SAMPLES_PER_FFT, dtype=numpy.float32)
    num_frames = 0

    stream = pyaudio.PyAudio().open(format=pyaudio.paInt16,
                                    channels=1,
                                    rate=SAMPLING_FRAME,
                                    input=True,
                                    frames_per_buffer=FRAME_SIZE)
    stream.start_stream()

    window = 0.5 * (1 - numpy.cos(numpy.linspace(0, 2 * numpy.pi, SAMPLES_PER_FFT, False)))

    print('sampling at', SAMPLING_FRAME, 'Hz with a max resolution of', FREQ_STEP, 'Hz')
    currentNote = 0;

    prevNote = 0;
    while stream.is_active():
        #shifts the buffer down by whatever the framesize is
        buf[:-FRAME_SIZE] = buf[FRAME_SIZE:]
        #reads in the stream in a rolling buffer
        buf[-FRAME_SIZE:] = numpy.frombuffer(stream.read(FRAME_SIZE), numpy.int16)

        fftval = fft(buf * window)
        #location of the maximum indicates the frequency
        #uses the location of the max, not the max value because FFTs are funKIE
        freq = (numpy.abs(fftval[imin:imax]).argmax() + imin) * FREQ_STEP
        if(freq > 27.5 and freq < 4186):
            n0 = freq_to_midi(freq)
            #can't round in the function because it tells cents
            n0x = int(round(n0))
            if(prevNote == n0):
                currentNote += 1
            else:
                currentNote = 0
            prevNote = n0
            #num_frames += 1

            #if num_frames >= FRAMES_PER_FFT:
            if(currentNote == 4):
            #took this out to try and increase the speed so it doesn't need to check
            #every loop, might unroll to make it irrelevant

                print('freq: {:7.2f} Hz\tnote: {:>3s} {:+.2f}\t\tmidi: {}'.format(freq, note_name(n0x), n0 - n0x, n0x))



    #print(fft_handle([1, 1, 1, 1, 0, 0, 0, 0]))


if (__name__ == "__main__"):
    main()
