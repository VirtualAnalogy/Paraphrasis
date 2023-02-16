# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef PKG_CONFIG
  PKG_CONFIG=pkg-config
endif

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DJUCE_MODAL_LOOPS_PERMITTED=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.3" "-DJUCE_APP_VERSION_HEX=0x10003" $(shell $(PKG_CONFIG) --cflags alsa freetype2 libcurl webkit2gtk-4.0 gtk+-x11-3.0) -pthread -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/lilv/src -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/lilv -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/sratom -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/sord/src -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/sord -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/serd -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/lv2 -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK -I../../JuceLibraryCode -I../../JuceLibraryCode/modules -I/opt/local/include/ -I/usr/include/freetype2 -I/usr/include/gtk-2.0/ -I/usr/include/glib-2.0/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I../../ThirdParty/Loris/src -I../../ThirdParty/Loris/ -I../../ThirdParty/TeragonGuiComponents/Components/Plugin -I../../ThirdParty/TeragonGuiComponents/Components/Plugin/arduino-base64 -I../../ThirdParty/TeragonGuiComponents/Components/Source -I../../ThirdParty/TeragonGuiComponents/Components/PluginParameters/include -I../../ThirdParty/sse2math/ $(CPPFLAGS)

  JUCE_CPPFLAGS_LV2_PLUGIN :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=1"
  JUCE_CFLAGS_LV2_PLUGIN := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_LV2_PLUGIN := -shared -Wl,--no-undefined
  JUCE_LV2DIR := Paraphrasis.lv2
  JUCE_TARGET_LV2_PLUGIN := $(JUCE_LV2DIR)/Paraphrasis.so
  JUCE_LV2_FULL_PATH := $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_PLUGIN)
  JUCE_LV2DESTDIR := $(HOME)/.lv2
  JUCE_COPYCMD_LV2_PLUGIN := $(JUCE_OUTDIR)/$(JUCE_LV2DIR) $(JUCE_LV2DESTDIR)

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=1" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := Paraphrasis.a

  JUCE_CPPFLAGS_LV2_MANIFEST_HELPER :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_LV2_MANIFEST_HELPER := juce_lv2_helper

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs alsa freetype2 libcurl) -fvisibility=hidden -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DJUCE_MODAL_LOOPS_PERMITTED=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.3" "-DJUCE_APP_VERSION_HEX=0x10003" $(shell $(PKG_CONFIG) --cflags alsa freetype2 libcurl webkit2gtk-4.0 gtk+-x11-3.0) -pthread -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/lilv/src -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/lilv -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/sratom -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/sord/src -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/sord -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/serd -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK/lv2 -I../../JuceLibraryCode/modules/juce_audio_processors/format_types/LV2_SDK -I../../JuceLibraryCode -I../../JuceLibraryCode/modules -I/opt/local/include/ -I/usr/include/freetype2 -I/usr/include/gtk-2.0/ -I/usr/include/glib-2.0/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I../../ThirdParty/Loris/src -I../../ThirdParty/Loris/ -I../../ThirdParty/TeragonGuiComponents/Components/Plugin -I../../ThirdParty/TeragonGuiComponents/Components/Plugin/arduino-base64 -I../../ThirdParty/TeragonGuiComponents/Components/Source -I../../ThirdParty/TeragonGuiComponents/Components/PluginParameters/include -I../../ThirdParty/sse2math/ $(CPPFLAGS)

  JUCE_CPPFLAGS_LV2_PLUGIN :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=1"
  JUCE_CFLAGS_LV2_PLUGIN := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_LV2_PLUGIN := -shared -Wl,--no-undefined
  JUCE_LV2DIR := Paraphrasis.lv2
  JUCE_TARGET_LV2_PLUGIN := $(JUCE_LV2DIR)/Paraphrasis.so
  JUCE_LV2_FULL_PATH := $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_PLUGIN)
  JUCE_LV2DESTDIR := $(HOME)/.lv2
  JUCE_COPYCMD_LV2_PLUGIN := $(JUCE_OUTDIR)/$(JUCE_LV2DIR) $(JUCE_LV2DESTDIR)

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=1" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := Paraphrasis.a

  JUCE_CPPFLAGS_LV2_MANIFEST_HELPER :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_LV2_MANIFEST_HELPER := juce_lv2_helper

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell $(PKG_CONFIG) --libs alsa freetype2 libcurl) -fvisibility=hidden -lrt -ldl -lpthread $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_LV2_PLUGIN := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_LV2_7d84e0a5.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/Base64_5d2c67c8.o \
  $(JUCE_OBJDIR)/TeragonPluginBase_eff57048.o \
  $(JUCE_OBJDIR)/ImageKnob_5a3869b7.o \
  $(JUCE_OBJDIR)/ImageSlider_809cb3a2.o \
  $(JUCE_OBJDIR)/IndicatorLight_714c910b.o \
  $(JUCE_OBJDIR)/PushButton_2bf264b0.o \
  $(JUCE_OBJDIR)/ResourceCache_4ca9fd5a.o \
  $(JUCE_OBJDIR)/StatusBar_99ce5207.o \
  $(JUCE_OBJDIR)/ThinButton_c72df16f.o \
  $(JUCE_OBJDIR)/phasefix_2adedc00.o \
  $(JUCE_OBJDIR)/LorisExceptions_b6cc3101.o \
  $(JUCE_OBJDIR)/AiffData_39170618.o \
  $(JUCE_OBJDIR)/AiffFile_a29cd2ea.o \
  $(JUCE_OBJDIR)/Analyzer_692ada0c.o \
  $(JUCE_OBJDIR)/AssociateBandwidth_aab2c8d9.o \
  $(JUCE_OBJDIR)/BigEndian_3820aa5f.o \
  $(JUCE_OBJDIR)/Breakpoint_98c40b97.o \
  $(JUCE_OBJDIR)/BreakpointUtils_12637724.o \
  $(JUCE_OBJDIR)/Channelizer_98793805.o \
  $(JUCE_OBJDIR)/Collator_a32991a8.o \
  $(JUCE_OBJDIR)/Dilator_4e5cd6c1.o \
  $(JUCE_OBJDIR)/Distiller_e8cc8b54.o \
  $(JUCE_OBJDIR)/Envelope_9d2f836.o \
  $(JUCE_OBJDIR)/F0Estimate_3f7edaf8.o \
  $(JUCE_OBJDIR)/fftsg_470458cc.o \
  $(JUCE_OBJDIR)/Filter_7c93581e.o \
  $(JUCE_OBJDIR)/FourierTransform_4ab0cac2.o \
  $(JUCE_OBJDIR)/FrequencyReference_a40788f5.o \
  $(JUCE_OBJDIR)/Fundamental_b5ad8c29.o \
  $(JUCE_OBJDIR)/Harmonifier_af727b0a.o \
  $(JUCE_OBJDIR)/ImportLemur_5bc0c70.o \
  $(JUCE_OBJDIR)/KaiserWindow_f16bc563.o \
  $(JUCE_OBJDIR)/LinearEnvelope_ac25833b.o \
  $(JUCE_OBJDIR)/Marker_1ba0efe0.o \
  $(JUCE_OBJDIR)/Morpher_4810c419.o \
  $(JUCE_OBJDIR)/NoiseGenerator_e88263ff.o \
  $(JUCE_OBJDIR)/Notifier_8dbac70c.o \
  $(JUCE_OBJDIR)/Oscillator_d3b110c6.o \
  $(JUCE_OBJDIR)/Partial_77fdabe5.o \
  $(JUCE_OBJDIR)/PartialBuilder_d512c580.o \
  $(JUCE_OBJDIR)/PartialUtils_5b47d796.o \
  $(JUCE_OBJDIR)/RealtimeOscillator_432c3211.o \
  $(JUCE_OBJDIR)/RealtimeSynthesizer_91275501.o \
  $(JUCE_OBJDIR)/ReassignedSpectrum_758d8218.o \
  $(JUCE_OBJDIR)/Resampler_a4535b19.o \
  $(JUCE_OBJDIR)/SdifFile_217f4930.o \
  $(JUCE_OBJDIR)/Sieve_b9658f62.o \
  $(JUCE_OBJDIR)/SpcFile_3ee37e26.o \
  $(JUCE_OBJDIR)/SpectralPeakSelector_3ed3bb48.o \
  $(JUCE_OBJDIR)/SpectralSurface_9358c60d.o \
  $(JUCE_OBJDIR)/Synthesizer_113e4cec.o \
  $(JUCE_OBJDIR)/Resources_78b0aa10.o \
  $(JUCE_OBJDIR)/LorisSynthesiser_1233ef51.o \
  $(JUCE_OBJDIR)/SampleAnalyzer_6b582ff9.o \
  $(JUCE_OBJDIR)/PluginProcessor_a059e380.o \
  $(JUCE_OBJDIR)/PluginEditor_94d4fb09.o \
  $(JUCE_OBJDIR)/include_dRowAudio_f10914a.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_ARA_31a052ed.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_e32edaee.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_ara_2a4c6ef7.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_lv2_libs_12bdca08.o \
  $(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o \
  $(JUCE_OBJDIR)/include_juce_core_f26d17db.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o \
  $(JUCE_OBJDIR)/include_juce_events_fd7d695.o \
  $(JUCE_OBJDIR)/include_juce_graphics_f817e147.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o \

OBJECTS_LV2_MANIFEST_HELPER := \
  $(JUCE_OBJDIR)/juce_LV2TurtleDumpProgram_f9409b5.o \

.PHONY: clean all strip LV2 LV2_MANIFEST_HELPER

all : LV2 LV2_MANIFEST_HELPER

LV2 : $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_PLUGIN)
LV2_MANIFEST_HELPER : $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_MANIFEST_HELPER)


$(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_PLUGIN) : $(OBJECTS_LV2_PLUGIN) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_MANIFEST_HELPER)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 libcurl
	@echo Linking "Paraphrasis - LV2 Plugin"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)/$(JUCE_LV2DIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_PLUGIN) $(OBJECTS_LV2_PLUGIN) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_LV2_PLUGIN) $(RESOURCES) $(TARGET_ARCH)
	$(V_AT) $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_MANIFEST_HELPER) $(JUCE_LV2_FULL_PATH)
	-$(V_AT)[ ! "$(JUCE_LV2DESTDIR)" ] || (mkdir -p $(JUCE_LV2DESTDIR) && cp -R $(JUCE_COPYCMD_LV2_PLUGIN))

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : $(OBJECTS_SHARED_CODE) $(RESOURCES)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 libcurl
	@echo Linking "Paraphrasis - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_MANIFEST_HELPER) : $(OBJECTS_LV2_MANIFEST_HELPER) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 libcurl
	@echo Linking "Paraphrasis - LV2 Manifest Helper"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_LV2_MANIFEST_HELPER) $(OBJECTS_LV2_MANIFEST_HELPER) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_LV2_7d84e0a5.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_LV2.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_LV2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_LV2_PLUGIN) $(JUCE_CFLAGS_LV2_PLUGIN) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Base64_5d2c67c8.o: ../../ThirdParty/TeragonGuiComponents/Components/Plugin/arduino-base64/Base64.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Base64.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/TeragonPluginBase_eff57048.o: ../../ThirdParty/TeragonGuiComponents/Components/Plugin/TeragonPluginBase.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling TeragonPluginBase.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ImageKnob_5a3869b7.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/ImageKnob.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ImageKnob.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ImageSlider_809cb3a2.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/ImageSlider.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ImageSlider.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IndicatorLight_714c910b.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/IndicatorLight.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling IndicatorLight.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PushButton_2bf264b0.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/PushButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PushButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ResourceCache_4ca9fd5a.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/ResourceCache.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ResourceCache.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/StatusBar_99ce5207.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/StatusBar.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling StatusBar.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ThinButton_c72df16f.o: ../../ThirdParty/TeragonGuiComponents/Components/Source/ThinButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ThinButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/phasefix_2adedc00.o: ../../ThirdParty/Loris/src/phasefix.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling phasefix.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LorisExceptions_b6cc3101.o: ../../ThirdParty/Loris/src/LorisExceptions.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LorisExceptions.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AiffData_39170618.o: ../../ThirdParty/Loris/src/AiffData.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AiffData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AiffFile_a29cd2ea.o: ../../ThirdParty/Loris/src/AiffFile.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AiffFile.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Analyzer_692ada0c.o: ../../ThirdParty/Loris/src/Analyzer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Analyzer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AssociateBandwidth_aab2c8d9.o: ../../ThirdParty/Loris/src/AssociateBandwidth.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AssociateBandwidth.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BigEndian_3820aa5f.o: ../../ThirdParty/Loris/src/BigEndian.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BigEndian.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Breakpoint_98c40b97.o: ../../ThirdParty/Loris/src/Breakpoint.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Breakpoint.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BreakpointUtils_12637724.o: ../../ThirdParty/Loris/src/BreakpointUtils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BreakpointUtils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Channelizer_98793805.o: ../../ThirdParty/Loris/src/Channelizer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Channelizer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Collator_a32991a8.o: ../../ThirdParty/Loris/src/Collator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Collator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Dilator_4e5cd6c1.o: ../../ThirdParty/Loris/src/Dilator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Dilator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Distiller_e8cc8b54.o: ../../ThirdParty/Loris/src/Distiller.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Distiller.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Envelope_9d2f836.o: ../../ThirdParty/Loris/src/Envelope.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Envelope.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/F0Estimate_3f7edaf8.o: ../../ThirdParty/Loris/src/F0Estimate.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling F0Estimate.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fftsg_470458cc.o: ../../ThirdParty/Loris/src/fftsg.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fftsg.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Filter_7c93581e.o: ../../ThirdParty/Loris/src/Filter.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Filter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FourierTransform_4ab0cac2.o: ../../ThirdParty/Loris/src/FourierTransform.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FourierTransform.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FrequencyReference_a40788f5.o: ../../ThirdParty/Loris/src/FrequencyReference.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FrequencyReference.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Fundamental_b5ad8c29.o: ../../ThirdParty/Loris/src/Fundamental.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Fundamental.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Harmonifier_af727b0a.o: ../../ThirdParty/Loris/src/Harmonifier.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Harmonifier.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ImportLemur_5bc0c70.o: ../../ThirdParty/Loris/src/ImportLemur.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ImportLemur.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/KaiserWindow_f16bc563.o: ../../ThirdParty/Loris/src/KaiserWindow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling KaiserWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LinearEnvelope_ac25833b.o: ../../ThirdParty/Loris/src/LinearEnvelope.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LinearEnvelope.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Marker_1ba0efe0.o: ../../ThirdParty/Loris/src/Marker.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Marker.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Morpher_4810c419.o: ../../ThirdParty/Loris/src/Morpher.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Morpher.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/NoiseGenerator_e88263ff.o: ../../ThirdParty/Loris/src/NoiseGenerator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling NoiseGenerator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Notifier_8dbac70c.o: ../../ThirdParty/Loris/src/Notifier.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Notifier.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Oscillator_d3b110c6.o: ../../ThirdParty/Loris/src/Oscillator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Oscillator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Partial_77fdabe5.o: ../../ThirdParty/Loris/src/Partial.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Partial.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PartialBuilder_d512c580.o: ../../ThirdParty/Loris/src/PartialBuilder.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PartialBuilder.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PartialUtils_5b47d796.o: ../../ThirdParty/Loris/src/PartialUtils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PartialUtils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/RealtimeOscillator_432c3211.o: ../../ThirdParty/Loris/src/RealtimeOscillator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling RealtimeOscillator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/RealtimeSynthesizer_91275501.o: ../../ThirdParty/Loris/src/RealtimeSynthesizer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling RealtimeSynthesizer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ReassignedSpectrum_758d8218.o: ../../ThirdParty/Loris/src/ReassignedSpectrum.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ReassignedSpectrum.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Resampler_a4535b19.o: ../../ThirdParty/Loris/src/Resampler.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Resampler.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SdifFile_217f4930.o: ../../ThirdParty/Loris/src/SdifFile.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SdifFile.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Sieve_b9658f62.o: ../../ThirdParty/Loris/src/Sieve.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Sieve.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SpcFile_3ee37e26.o: ../../ThirdParty/Loris/src/SpcFile.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SpcFile.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SpectralPeakSelector_3ed3bb48.o: ../../ThirdParty/Loris/src/SpectralPeakSelector.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SpectralPeakSelector.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SpectralSurface_9358c60d.o: ../../ThirdParty/Loris/src/SpectralSurface.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SpectralSurface.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Synthesizer_113e4cec.o: ../../ThirdParty/Loris/src/Synthesizer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Synthesizer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Resources_78b0aa10.o: ../../Resources/Resources.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Resources.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LorisSynthesiser_1233ef51.o: ../../Source/LorisSynthesiser.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LorisSynthesiser.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SampleAnalyzer_6b582ff9.o: ../../Source/SampleAnalyzer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SampleAnalyzer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_a059e380.o: ../../Source/PluginProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_94d4fb09.o: ../../Source/PluginEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_dRowAudio_f10914a.o: ../../JuceLibraryCode/include_dRowAudio.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_dRowAudio.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o: ../../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o: ../../JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o: ../../JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_ARA_31a052ed.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_ARA.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_ARA.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_e32edaee.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o: ../../JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_ara_2a4c6ef7.o: ../../JuceLibraryCode/include_juce_audio_processors_ara.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors_ara.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_lv2_libs_12bdca08.o: ../../JuceLibraryCode/include_juce_audio_processors_lv2_libs.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors_lv2_libs.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o: ../../JuceLibraryCode/include_juce_audio_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_f26d17db.o: ../../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o: ../../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_fd7d695.o: ../../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_f817e147.o: ../../JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o: ../../JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o: ../../JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_LV2TurtleDumpProgram_f9409b5.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/LV2/juce_LV2TurtleDumpProgram.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_LV2TurtleDumpProgram.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_LV2_MANIFEST_HELPER) $(JUCE_CFLAGS_LV2_MANIFEST_HELPER) -o "$@" -c "$<"

clean:
	@echo Cleaning Paraphrasis
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping Paraphrasis
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_LV2_PLUGIN:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
-include $(OBJECTS_LV2_MANIFEST_HELPER:%.o=%.d)
