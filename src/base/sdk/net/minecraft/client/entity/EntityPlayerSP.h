#pragma once

#include "../../entity/player/EntityPlayer.h"
#include "../../entity/Entity.h"
#include "../../world/World.h"
class CEntityPlayerSP : public CEntityPlayer
{
public:
	using CEntityPlayer::CEntityPlayer;
	void setSneak(bool state, JNIEnv* env = Java::Env);
	Vector3D GetLastTickPos2(JNIEnv* env = Java::Env);
	void attackEntity(CEntityPlayerSP* player, jobject entity, JNIEnv* env = Java::Env);
	bool sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item, JNIEnv* env = Java::Env);

	double get_motion_x(JNIEnv* env = Java::Env);

	bool isSneaking(JNIEnv* env = Java::Env);

	void set_motion_x(double x, JNIEnv* env = Java::Env);

	double get_motion_y(JNIEnv* env = Java::Env);

	void set_motion_y(double y, JNIEnv* env = Java::Env);

	double get_motion_z(JNIEnv* env = Java::Env);

	void set_motion_z(double z, JNIEnv* env = Java::Env);

	double toRadians(float degrees, JNIEnv* env = Java::Env);

	float get_direction(JNIEnv* env = Java::Env);

	float get_speed(JNIEnv* env = Java::Env);

	bool isStrafing(JNIEnv* env = Java::Env);

	bool isMovingForwardsOrBackwards(JNIEnv* env = Java::Env);

	bool isMovingForwards(JNIEnv* env = Java::Env);

	bool isMovingBackwards(JNIEnv* env = Java::Env);

	void set_speed(const float speed, JNIEnv* env = Java::Env);

	void sendGroundPacket(Object Packet, JNIEnv* env = Java::Env);

	Object C03PacketPlayer(jboolean ground, float yaw, float pitch, JNIEnv* env = Java::Env);

};