#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

#include "../../../../../util/logger.h"
#include "../../../../../moduleManager/commonData.h"



void CEntityPlayerSP::setSneak(bool state)
{
	CGameSettings* settings = SDK::Minecraft->gameSettings;
	jobject sneakObj = Java::Env->GetObjectField(settings->getInstance(), StrayCache::gamesettings_keyBindSneak);
	jclass keybind_class = Java::Env->GetObjectClass(sneakObj);
	jfieldID pressed;

	Java::Env->SetBooleanField(sneakObj, StrayCache::keybind_pressed, state);
}

void CEntityPlayerSP::attackEntity(CEntityPlayerSP* player, jobject entity)
{

	Object playerControllerObj = SDK::Minecraft->getPlayerController();
	return Java::Env->CallVoidMethod(playerControllerObj.getInstance(), StrayCache::playerControllerMP_attackEntity, player->getInstance(), entity);
}

bool CEntityPlayerSP::sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item)
{
	Object playerControllerObj = SDK::Minecraft->getPlayerController();

	return Java::Env->CallBooleanMethod(playerControllerObj.getInstance(), StrayCache::playerControllerMP_sendUseItem, player->getInstance(), world, item.getInstance());
}

double CEntityPlayerSP::get_motion_x()
{
	return this->getMotion().x;
}

void CEntityPlayerSP::set_motion_x(double x)
{
	Java::Env->SetDoubleField(getInstance(), StrayCache::entity_motionX, (jdouble)x);
}

double CEntityPlayerSP::get_motion_y()
{
	double y = (double)Java::Env->GetDoubleField(getInstance(), StrayCache::entity_motionY);
	return y;
}

void CEntityPlayerSP::set_motion_y(double y)
{
	Java::Env->SetDoubleField(getInstance(), StrayCache::entity_motionY, (jdouble)y);
}

double CEntityPlayerSP::get_motion_z()
{
	double z = (double)Java::Env->GetDoubleField(getInstance(), StrayCache::entity_motionZ);
	return z;
}

void CEntityPlayerSP::set_motion_z(double z)
{
	Java::Env->SetDoubleField(getInstance(), StrayCache::entity_motionZ, (jdouble)z);
}

double CEntityPlayerSP::toRadians(float degrees) {
	return degrees * (M_PI / 180);
}

float CEntityPlayerSP::get_direction()
{
	float yaw = SDK::Minecraft->thePlayer->GetRotationYaw();
	float strafe = 45;
	// add 180 to the yaw to strafe backwards
	if (SDK::Minecraft->thePlayer->getMoveForward() < 0) {
		// invert our strafe to -45
		strafe = -45;
		yaw += 180;
	}
	if (SDK::Minecraft->thePlayer->getMoveStrafe() > 0) {
		// subtract 45 to strafe left forward

		yaw -= strafe;
		// subtract an additional 45 if we do not press W in order to get to -90
		if (SDK::Minecraft->thePlayer->getMoveForward() == 0) {
			yaw -= 45;
		}
	}
	else if (SDK::Minecraft->thePlayer->getMoveStrafe() < 0) {
		// add 45 to strafe right forward
		yaw += strafe;
		// add 45 if we do not press W in order to get to 90
		if (SDK::Minecraft->thePlayer->getMoveForward() == 0) {
			yaw += 45;
		}
	}
	return yaw;
}

float CEntityPlayerSP::get_speed()
{
	Vector3 velocity_vector = SDK::Minecraft->thePlayer->getMotion();

	return sqrt(velocity_vector.x * velocity_vector.x + velocity_vector.z * velocity_vector.z);
}

bool CEntityPlayerSP::isStrafing() {
	return SDK::Minecraft->thePlayer->getMoveStrafe() != 0;
}

bool CEntityPlayerSP::isMovingForwardsOrBackwards() {
	return SDK::Minecraft->thePlayer->getMoveForward() != 0;
}

bool CEntityPlayerSP::isMovingForwards()
{
	return SDK::Minecraft->thePlayer->getMoveForward() > 0;

}

bool CEntityPlayerSP::isMovingBackwards()
{
	return SDK::Minecraft->thePlayer->getMoveForward() < 0;

}

void CEntityPlayerSP::set_speed(const float speed)
{
	if (getMotion().x != 0 && getMotion().y != 0) {
		double yaw = toRadians(get_direction());
		float y = SDK::Minecraft->thePlayer->getMotion().y;
		float x = -sin(yaw) * speed;
		float z = cos(yaw) * speed;
		SDK::Minecraft->thePlayer->setMotion(Vector3(x, 100000000000, z));
	}
}

void CEntityPlayerSP::sendGroundPacket(Object Packet)
{
	auto queueObject = SDK::Minecraft->getNetHandler();

	Java::Env->CallVoidMethod(queueObject.getInstance(), StrayCache::netHandlerPlayClient_addToSendQueue, Packet.getInstance());

	return;
}

Object CEntityPlayerSP::C03PacketPlayer(jboolean ground, float yaw, float pitch)
{
	jclass C03;
	Java::AssignClass("net.minecraft.network.play.client.C03PacketPlayer", C03);
	jmethodID c03Constructer = Java::Env->GetMethodID(C03, "<init>", "(Z)V");
	jfieldID yawf, pitchf;
	if (JNIHelper::IsForge()) {
		yawf = Java::Env->GetFieldID(C03, "field_149476_e", "F");
		pitchf = Java::Env->GetFieldID(C03, "field_149473_f", "F");
	}
	else {
		yawf = Java::Env->GetFieldID(C03, "yaw", "F");
		pitchf = Java::Env->GetFieldID(C03, "pitch", "F");
	}
	jobject Packet = Java::Env->NewObject(C03, c03Constructer, ground);
	Java::Env->SetFloatField(Packet, yawf, yaw);
	Java::Env->SetFloatField(Packet, pitchf, pitch);
	return Object(Packet);
}