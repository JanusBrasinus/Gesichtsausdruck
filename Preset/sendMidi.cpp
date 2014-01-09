#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <CoreMIDI/CoreMIDI.h>

#include <iostream>
#include <stdio.h>
#include <algorithm>

#include "sendMidi.h"



sendMidi::sendMidi()

{
    device = MIDIGetDevice(0);
    
    bus1 = MIDIDeviceGetEntity(device, 0);
    bus2 = MIDIDeviceGetEntity(device, 1);
    
    midiOut1 = MIDIEntityGetSource(bus1, 0);
    midiOut2 = MIDIEntityGetSource(bus2, 0);
    
}

sendMidi::~sendMidi(void){}

void sendMidi::sendMessage(int melodie, int drum){
    
    
    if(melodie == 1){
        MIDIPacket *currentpacket1 = MIDIPacketListInit(packetlist1);
        Byte msgs1[6] = {0xB0, 0, (Byte)123, 0xB1, 0, (Byte)0};
        currentpacket1 = MIDIPacketListAdd(packetlist1, sizeof(buffer), currentpacket1, timestamp, (Byte)(6), msgs1);
        MIDIReceived(midiOut1, packetlist1);
    }
    
    if(melodie == 2){
        MIDIPacket *currentpacket1 = MIDIPacketListInit(packetlist1);
        Byte msgs1[6] = {0xB0, 0, (Byte)0, 0xB1, 0, (Byte)123};
        currentpacket1 = MIDIPacketListAdd(packetlist1, sizeof(buffer), currentpacket1, timestamp, (Byte)(6), msgs1);
        MIDIReceived(midiOut1, packetlist1);
    }
    
    if(drum == 1){
        
        MIDIPacket *currentpacket2 = MIDIPacketListInit(packetlist2);
        Byte msgs2[12] = {0xB0, 0, (Byte)123, 0xB1, 0, (Byte)0, 0xB2, 0, (Byte)0, 0xB3, 0, (Byte)0};
        currentpacket2 = MIDIPacketListAdd(packetlist2, sizeof(buffer),currentpacket2, timestamp, (Byte)(12), msgs2);
        MIDIReceived(midiOut2, packetlist2);
    }
    
    if(drum == 2){
        MIDIPacket *currentpacket2 = MIDIPacketListInit(packetlist2);
        Byte msgs2[12] = {0xB0, 0, (Byte)123, 0xB1, 0, (Byte)123, 0xB2, 0, (Byte)0, 0xB3, 0, (Byte)0};
        currentpacket2 = MIDIPacketListAdd(packetlist2, sizeof(buffer),currentpacket2, timestamp, (Byte)(12), msgs2);
        MIDIReceived(midiOut2, packetlist2);
    }
    
    if(drum == 3){
        MIDIPacket *currentpacket2 = MIDIPacketListInit(packetlist2);
        Byte msgs2[12] = {0xB0, 0, (Byte)123, 0xB1, 0, (Byte)123, 0xB2, 0, (Byte)123, 0xB3, 0, (Byte)0};
        currentpacket2 = MIDIPacketListAdd(packetlist2, sizeof(buffer),currentpacket2, timestamp, (Byte)(12), msgs2);
        MIDIReceived(midiOut2, packetlist2);
    }
    
    if(drum == 4){
        MIDIPacket *currentpacket2 = MIDIPacketListInit(packetlist2);
        Byte msgs2[12] = {0xB0, 0, (Byte)123, 0xB1, 0, (Byte)123, 0xB2, 0, (Byte)123, 0xB3, 0, (Byte)123};
        currentpacket2 = MIDIPacketListAdd(packetlist2, sizeof(buffer),currentpacket2, timestamp, (Byte)(12), msgs2);
        MIDIReceived(midiOut2, packetlist2);
    }

    
    
    
    
}
