#include <CoreMIDI/CoreMIDI.h>
#include  <opencv2/opencv.hpp>
#ifndef Preset_sendMidi_h
#define Preset_sendMidi_h


class sendMidi {
    
public:
    
    sendMidi();
    ~sendMidi(void);
    void sendMessage(int melodie, int drum);

private:

    MIDIEndpointRef midiOut1;
    MIDIEndpointRef midiOut2;

    
    MIDITimeStamp timestamp = 0;
    Byte buffer[1024];
    
    MIDIPacketList *packetlist1 = (MIDIPacketList*)buffer;
    MIDIPacketList *packetlist2 = (MIDIPacketList*)buffer;

    
    MIDIDeviceRef device;
    MIDIEntityRef bus1;
    MIDIEntityRef bus2;

    
};


#endif
