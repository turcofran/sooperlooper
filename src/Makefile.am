SUBDIRS = @SL_DIRS@

bin_PROGRAMS =  sooperlooper slconsole slregister

slpresetdir  = $(datadir)/sooperlooper/presets
slpreset_DATA =  midiwizard.slb oxy8.slb edp4.slb bcf2000.slb

AM_CXXFLAGS =  @JACK_CFLAGS@ @LOSC_CFLAGS@ @SIGCPP_CFLAGS@ @SNDFILE_CFLAGS@ @SAMPLERATE_CFLAGS@ @XML_CFLAGS@ @ICU_CFLAGS@  @RUBBERBAND_CFLAGS@ @FFTW_CFLAGS@

#SYSDEP_SRCS=
#if WITH_ALSA
#SYSDEP_SRCS += alsa_midi_bridge.cpp
#endif

#if WITH_COREMIDI
#SYSDEP_SRCS += coremidi_bridge.cpp
#endif

noinst_LIBRARIES           = libslcore.a libsldrivers.a

libslcore_a_SOURCES      = \
	engine.cpp \
	control_osc.cpp \
	looper.cpp \
	plugin.cc \
	event.cpp \
	midi_bridge.cpp \
	midi_bind.cpp \
	audio_driver.cpp \
	command_map.cpp \
	filter.cpp \
	panner.cpp \
	utils.cpp \
	$(SYSDEP_SRCS)

libsldrivers_a_SOURCES      = \
	jack_audio_driver.cpp


sooperlooper_SOURCES = \
	sooperlooper.cpp

sooperlooper_LDADD =  libsldrivers.a libslcore.a @BASE_LIBS@ @JACK_LIBS@ @LOSC_LIBS@ @SIGCPP_LIBS@ @RUBBERBAND_LIBS@ @FFTW_LIBS@ @SNDFILE_LIBS@ @SAMPLERATE_LIBS@ @AUDIO_LIBS@ @XML_LIBS@
sooperlooper_LDFLAGS = 

slconsole_SOURCES = slconsole.cpp
slconsole_LDADD = @LOSC_LIBS@ @NCURSES_LIBS@ -lpthread

slregister_SOURCES = register_tool.cpp
slregister_LDADD = @LOSC_LIBS@ -lpthread

noinst_HEADERS = $(wildcard *.hpp *.h)

EXTRA_DIST = oxy8.slb midiwizard.slb bcf2000.slb edp4.slb
