#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include "noteplayer.h" // using namespace std;
#include <thread>
#include "func_gen.h"

using namespace std;
std::thread playing;
void play(int paramBeats, int paramTime, std::string paramKey, int paramSectionLength, int paramRepeats, int paramLeadInstr, int paramChordInstr);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SpeedDial = findChild<QDial*>("SpeedDial");

    ui->SpeedBox = findChild<QSpinBox*>("SpeedBox");

    ui->KeyDrop = findChild<QComboBox*>("KeyDrop");

    ui->KeySlide = findChild<QSlider*>("KeySlide");

    ui->Output = findChild<QLabel*>("Output");

    ui->SectionLengthBox = findChild<QSpinBox*>("SectionLengthBox");

    ui->RepeatsBox = findChild<QSpinBox*>("RepeatsBox");

    ui->LeadBox = findChild<QSpinBox*>("LeadBox");

    ui->ChordBox = findChild<QSpinBox*>("ChordBox");


    setWindowTitle(tr("MusicAI"));

}

void MainWindow::on_SpeedDial_valueChanged(int value)
{
    ui->SpeedBox->setValue(value);
}

void MainWindow::on_SpeedBox_valueChanged(int value)
{
    ui->SpeedDial->setValue(value);
}

void MainWindow::on_KeySlide_valueChanged(int tick)
{
    ui->KeyDrop->setCurrentIndex(tick);
}
void MainWindow::on_KeyDrop_activated(int index)
{
    ui->KeySlide->setValue(index);
}






void MainWindow::on_StartBut_clicked()
{
    int beats = ui->SpeedBox->value();
    int time = ui->TimeBox->value();
    int sectionLength = ui->SectionLengthBox->value();
    int repeats = ui->RepeatsBox->value();
    int leadInstr = ui->LeadBox->value();
    int chordInstr = ui->ChordBox->value();

    QString key = ui->KeyDrop->currentText();

    QString out = key + "\t" + QString::number(0) + "\t" + QString::number(beats) + "\t" + QString::number(time);

    ui->Output->setText(out);

    std::string keystr = key.toStdString();
    std::thread playing(play, beats, time, keystr, sectionLength, repeats, leadInstr, chordInstr);

    playing.detach();


    if (playing.joinable())
    {
        playing.join();
    }
    
}

void MainWindow::on_StopBut_clicked()
{
    ui->Output->setText("");
    if (playing.joinable())
    {
        playing.join();
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}



void play(int paramBeats, int paramTime, std::string paramKey, int paramSectionLength, int paramRepeats, int paramLeadInstr, int paramChordInstr)
{
    cout << "============ START ============" << endl;
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    int sfont_id;
    int key = 0;
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
    fluid_synth_program_change(synth, 2, 1);
    fluid_synth_program_change(synth, 3, 1);
    fluid_synth_program_change(synth, 4, 1);
    fluid_synth_program_change(synth, 5, 1);

    // Melody
    fluid_synth_program_change(synth, 7, 5);

    fluid_synth_program_reset(synth);

    // Chords
    set_instrument(synth, 2, paramChordInstr);
    set_instrument(synth, 3, paramChordInstr);
    set_instrument(synth, 4, paramChordInstr);
    set_instrument(synth, 5, paramChordInstr);

    // Melody
    set_instrument(synth, 7, paramLeadInstr);

    fluid_synth_program_reset(synth);

    //------------------------------------------------------------------------------------------------


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

    unordered_map<string, chord> all_chords = {
    {"Imaj7", Imaj7},
    {"ii7", ii7},
    {"iii7", iii7},
    {"IVmaj7", IVmaj7},
    {"V7", V7},
    {"vi7", vi7},
    {"vii7b5", vii7b5},
    };

    


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

    config params = config();

    set_tempo(params, (float)paramBeats);

    set_ts(params, (float)paramTime);

    //set_form(params, string form);

    set_key(params, roots[paramKey]);

    set_form(params, paramSectionLength, paramRepeats);

    realize_config(params, all_chords, drum_sounds, synth);



    /* -BEGIN ERROR HANDLING/SHUTDOWN- */

    //err:     TODO: reimplemnt this
        /* Clean up */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}