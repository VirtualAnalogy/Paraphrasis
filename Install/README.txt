ABOUT
=====
Paraphrasis is a spectral resynthesis synthesiser which can model any sound only with one sonic sample. You do not have to sample all tones of instrument nor you have to spend time with messing with other synthesisers. Just load a sample to Paraphrasis and enjoy your paraphrased instrument! It is powered by Loris - an Open Source sound modelling and processing software package - and JUCE, Teragon GUI Components + Parameters and dRowAudio toolkit And sse2math saves your CPU.

CHANGE LOG
==========

1.0.3
—————
- Fixed: Crash in MuLab and potentially in other hosts when pressing analyze when processing is running
* Improved: Memory usage optimised
- Fixed: Sound click in FL Studio 11 when notes are tight together
- Fixed: Paraphrasis pay attention to sample rate chages
* Improved: Mac OS compatibility is now 10.7+


1.0.2
—————
- Fixed: Sound glitches when playing note repetitively (partials missing)
- Fixed: When note is finished (sample is done) CPU went high - MainStage
- Fixed: Reverse button position
- Fixed: Reverse button and status LED synchronisation
- Fixed: CPU went high when long sample was loaded and note was triggered

1.0.1
—————
- Fixed: plugin wont load on some Win Hosts
- Fixed: VST3 version did not cleaned buffer before synthesising new samples

1.0.0
——————
Initial Release