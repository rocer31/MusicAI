QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source.cpp \
    chord.cpp \
    main.cpp \
    mainwindow.cpp \
    noteplayer.cpp

HEADERS += \
    chord.h \
    fluidsynth.h \
    fluidsynth/audio.h \
    fluidsynth/event.h \
    fluidsynth/gen.h \
    fluidsynth/ladspa.h \
    fluidsynth/log.h \
    fluidsynth/midi.h \
    fluidsynth/misc.h \
    fluidsynth/mod.h \
    fluidsynth/seq.h \
    fluidsynth/seqbind.h \
    fluidsynth/settings.h \
    fluidsynth/sfont.h \
    fluidsynth/shell.h \
    fluidsynth/synth.h \
    fluidsynth/types.h \
    fluidsynth/version.h \
    fluidsynth/voice.h \
    mainwindow.h \
    noteplayer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
