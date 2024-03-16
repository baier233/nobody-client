#pragma once


#include "../AbstractEvent.h"
#include "../../sdk/net/minecraft/client/network/Packet.h"
class EventPacketSend : public Event<EventPacketSend>, public EventCallback {
public:
	EventPacketSend(JNIEnv* env, CPacket cp) : packet(cp), env(env) {}

	CPacket getPackets() const { return this->packet; }
	JNIEnv* getEnv() const { return this->env; }
private:
	CPacket packet;
	JNIEnv* env;
};