##
## WR9R  MIDI Controller Prototype
## Test Utility
## November 11, 2023
## 
## 

import rtmidi

class MidiMessage:
    def __init__(self, channel, control, value):
        self.channel = channel
        self.control = control
        self.value = value

def list_midi_ports():
    midi_in = rtmidi.RtMidiIn()

    print("Available MIDI input ports:")
    for i in range(midi_in.getPortCount()):
        port_name = midi_in.getPortName(i)
        print(f"{i}: {port_name}")

def open_first_midi_port():
    midi_in = rtmidi.RtMidiIn()

    if midi_in.getPortCount() > 0:
        midi_in.openPort(0)
        return midi_in, midi_in.getPortName(0)  # Return the midi_in object along with the port name
    else:
        print("Error: No MIDI input ports available.")
        return None, None

def main():
    midi_in, port_name = open_first_midi_port()

    if port_name != "Teensy MIDI 0":
        print("Not my controller!!")
        return
    
    if midi_in and port_name:
        print(f"Opening MIDI input port: {port_name}")
        print("Reading MIDI input. Press Ctrl+C to exit.")
    else:
        return

    try:
        while True:
            message = midi_in.getMessage()

            if message:
                channel = (message.getChannel() & 0xF) + 1
                control = message.getControllerNumber()
                value = message.getControllerValue()

                midi_message = MidiMessage(channel=channel, control=control, value=value)

##                if (control == 24) and (channel == 6) and (value == 1):
##                    print("Freq  up ^")
##                if (control == 24) and (channel == 6) and (value == 127):
##                    print("Freq  dn v")
                
                print(f"Received MIDI message: {midi_message.__dict__}")

    except KeyboardInterrupt:
        print("\nExiting.")
    finally:
        if midi_in:
            midi_in.closePort()

if __name__ == "__main__":
    main()
