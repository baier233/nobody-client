#pragma once

#include "../../entity/player/EntityPlayer.h"
#include "../../entity/Entity.h"
#include "../../world/World.h"
class CEntityPlayerSP : public CEntityPlayer
{
public:
	using CEntityPlayer::CEntityPlayer;
	void setSneak(bool state);
	void attackEntity(CEntityPlayerSP* player, jobject entity);
	bool sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item);

	double get_motion_x();

	void set_motion_x(double x);

	double get_motion_y();

	void set_motion_y(double y);

	double get_motion_z();

	void set_motion_z(double z);

	double toRadians(float degrees);

	float get_direction();

	float get_speed();

	bool isStrafing();

	bool isMovingForwardsOrBackwards();

	bool isMovingForwards();

	bool isMovingBackwards();

	void set_speed(const float speed);

	void sendGroundPacket(Object Packet);

	Object C03PacketPlayer(jboolean ground, float yaw, float pitch);

};