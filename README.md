# Thetis_MIDI_UI
![EndResult](https://github.com/ldocull/Thetis_MIDI_UI/assets/31085432/b6263253-4467-4325-93f9-0e9c560e040e)

The modification process was to remove the processor chip, crystal, and USB-C connector from the bottom of the gaming controller PCBA.

A layer of Katon tape was added to cover the area where the processor was removed.  A Teensy 4.0 was then hot-glued to te back of the PCBA.

The encoders and buttons were attached to the Teensy directly with wire-wrap wires as shown in the photo.  (The Arduino TEST.ino can be used as a reference for the pinout.)  Please note the attachements of GND and 5V (to the cap that came in from the prior USB connector), and 'R16' to pin-20 of the Teensy that is used to control the LEDs.

![Bottom](https://github.com/ldocull/Thetis_MIDI_UI/assets/31085432/5273817e-1ff8-4304-b60b-58ce9b88e5a8)

There is a STL file in the files-section for a replacement bottom cover that accomodates the modifications and hide the bird's-nest of wiring.

The setup file (WR9R-MIDI.m2c) can be imported into the MIDI setting of Thetis. Adding / moving/ changing functions of the keys and knpbs is a snap. The large-wheel was setup special for VFO and has a hard-coded incremental setup which is tied to 'enc1'.

Hope you found this interesting!

Peace and 73,
WR9R
