import numpy
import pyaudio
def main():
    NOTE_MIN = 21
    NOTE_MAX = 108
    SAMPLING_FRAME = 22050 #Sampling frequency in Hz
    FRAME_SIZE = 2048
    FRAMES_PER_FFT = 16 #Average across how many frames

    SAMPLES_PER_FFT = FRAME_SIZE*FRAMES_PER_FFT
    FREQ_STEP = float(SAMPLING_FRAME)/SAMPLES_PER_FFT

    NOTE_NAMES = 'A A# B C C# D D# E F F# G G#'.split()

    #from https://newt.phys.unsw.edu.au/jw/notes.html

    def freq_to_midi(f): return NOTE_MAX + 12*numpy.log2(f/440.0)
    def midi_to_freq(m): return 440 * 2.0**((m-NOTE_MAX)/12.0)
    def note_name(m): return NOTE_NAMES[m % 12] + str(m/12 - 1)

    def note_to_fftbin(m): return midi_to_freq(m)/FREQ_STEP
    imin = max(0, int(numpy.floor(note_to_fftbin(NOTE_MIN-1))))
    imax = min(SAMPLES_PER_FFT, int(numpy.ceil(note_to_fftbin(NOTE_MAX+1))))

    buf = numpy.zeros(SAMPLES_PER_FFT, dtype=numpy.float32)
    num_frames = 0

    stream = pyaudio.PyAudio().open(format=pyaudio.paInt16,
                                    channels=1,
                                    rate=SAMPLING_FRAME,
                                    input=True,
                                    frames_per_buffer=FRAME_SIZE)
    stream.start_stream()

    window = 0.5 * (1 - numpy.cos(numpy.linspace(0, 2*numpy.pi, SAMPLES_PER_FFT, False)))

    print('sampling at', SAMPLING_FRAME, 'Hz with a max resolution of', FREQ_STEP, 'Hz')

    while stream.is_active():
        buf[:-FRAME_SIZE] = buf[FRAME_SIZE:]
        buf[-FRAME_SIZE:] = numpy.frombuffer(stream.read(FRAME_SIZE), numpy.int16)

        fft = numpy.fft.rfft(buf*window)

        freq = (numpy.abs(fft[imin:imax]).argmax() + imin) * FREQ_STEP
        #print(numpy.abs(fft[imin:imax]).argmax())
        #print(numpy.abs(fft[imin:imax]).argmax() + imin)
        #print((numpy.abs(fft[imin:imax]).argmax() + imin) * FREQ_STEP)
        #print(numpy.abs(fft[numpy.abs(fft[imin:imax]).argmax()]))
        #input()
        n = freq_to_midi(freq)
        n0 = int(round(n))

        num_frames += 1

        if num_frames >= FRAMES_PER_FFT:
            print('freq: {:7.2f} Hz\tnote: {:>3s} {:+.2f}'.format(freq, note_name(n0), n-n0))

if(__name__ == "__main__"):
    main()