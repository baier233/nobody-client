#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

#include "../../../../../util/logger.h"
#include "../../../../../moduleManager/commonData.h"



void CEntityPlayerSP::setSneak(bool state, JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		this->setSneaking(true,env);
;		return;
	}
	CGameSettings* settings = SDK::GetInstance()->Minecraft->gameSettings;
	jobject sneakObj = env->GetObjectField(settings->getInstance(), StrayCache::GetInstance()->gamesettings_keyBindSneak);
	jclass keybind_class = env->GetObjectClass(sneakObj);
	jfieldID pressed;

	env->SetBooleanField(sneakObj, StrayCache::GetInstance()->keybind_pressed, state);
}

Vector3D CEntityPlayerSP::GetLastTickPos2(JNIEnv* env) {
	return Vector3D{
		(double)env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->localPlayer_xLast),
		(double)env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->localPlayer_yLast1),
		(double)env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->localPlayer_zLast)
	};
}


void CEntityPlayerSP::attackEntity(CEntityPlayerSP* player, jobject entity, JNIEnv* env )
{

	Object playerControllerObj = SDK::GetInstance()->Minecraft->getPlayerController();
	return env->CallVoidMethod(playerControllerObj.getInstance(), StrayCache::GetInstance()->playerControllerMP_attackEntity, player->getInstance(), entity);
}

bool CEntityPlayerSP::sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item, JNIEnv* env )
{
	Object playerControllerObj = SDK::GetInstance()->Minecraft->getPlayerController();

	return env->CallBooleanMethod(playerControllerObj.getInstance(), StrayCache::GetInstance()->playerControllerMP_sendUseItem, player->getInstance(), world, item.getInstance());
}

double CEntityPlayerSP::get_motion_x(JNIEnv* env )
{
	return this->getMotion().x;
}

void CEntityPlayerSP::set_motion_x(double x, JNIEnv* env )
{
	env->SetDoubleField(getInstance(), StrayCache::GetInstance()->entity_motionX, (jdouble)x);
}

double CEntityPlayerSP::get_motion_y(JNIEnv* env )
{
	double y = (double)env->GetDoubleField(getInstance(), StrayCache::GetInstance()->entity_motionY);
	return y;
}

void CEntityPlayerSP::set_motion_y(double y, JNIEnv* env )
{
	env->SetDoubleField(getInstance(), StrayCache::GetInstance()->entity_motionY, (jdouble)y);
}

double CEntityPlayerSP::get_motion_z(JNIEnv* env )
{
	double z = (double)env->GetDoubleField(getInstance(), StrayCache::GetInstance()->entity_motionZ);
	return z;
}

void CEntityPlayerSP::set_motion_z(double z, JNIEnv* env )
{
	env->SetDoubleField(getInstance(), StrayCache::GetInstance()->entity_motionZ, (jdouble)z);
}

double CEntityPlayerSP::toRadians(float degrees, JNIEnv* env ) {
	return degrees * (M_PI / 180);
}

float CEntityPlayerSP::get_direction(JNIEnv* env )
{
	float yaw = SDK::GetInstance()->Minecraft->thePlayer->GetRotationYaw();
	float strafe = 45;
	// add 180 to the yaw to strafe backwards
	if (SDK::GetInstance()->Minecraft->thePlayer->getMoveForward() < 0) {
		// invert our strafe to -45
		strafe = -45;
		yaw += 180;
	}
	if (SDK::GetInstance()->Minecraft->thePlayer->getMoveStrafe() > 0) {
		// subtract 45 to strafe left forward

		yaw -= strafe;
		// subtract an additional 45 if we do not press W in order to get to -90
		if (SDK::GetInstance()->Minecraft->thePlayer->getMoveForward() == 0) {
			yaw -= 45;
		}
	}
	else if (SDK::GetInstance()->Minecraft->thePlayer->getMoveStrafe() < 0) {
		// add 45 to strafe right forward
		yaw += strafe;
		// add 45 if we do not press W in order to get to 90
		if (SDK::GetInstance()->Minecraft->thePlayer->getMoveForward() == 0) {
			yaw += 45;
		}
	}
	return yaw;
}

float CEntityPlayerSP::get_speed(JNIEnv* env )
{
	Vector3 velocity_vector = SDK::GetInstance()->Minecraft->thePlayer->getMotion();

	return sqrt(velocity_vector.x * velocity_vector.x + velocity_vector.z * velocity_vector.z);
}

bool CEntityPlayerSP::isStrafing(JNIEnv* env ) {
	return SDK::GetInstance()->Minecraft->thePlayer->getMoveStrafe() != 0;
}

bool CEntityPlayerSP::isMovingForwardsOrBackwards(JNIEnv* env ) {
	return SDK::GetInstance()->Minecraft->thePlayer->getMoveForward() != 0;
}

bool CEntityPlayerSP::isMovingForwards(JNIEnv* env )
{
	return SDK::GetInstance()->Minecraft->thePlayer->getMoveForward() > 0;

}

bool CEntityPlayerSP::isMovingBackwards(JNIEnv* env )
{
	return SDK::GetInstance()->Minecraft->thePlayer->getMoveForward() < 0;

}

void CEntityPlayerSP::set_speed(const float speed, JNIEnv* env )
{
	if (getMotion().x != 0 && getMotion().y != 0) {
		double yaw = toRadians(get_direction());
		float y = SDK::GetInstance()->Minecraft->thePlayer->getMotion().y;
		float x = -sin(yaw) * speed;
		float z = cos(yaw) * speed;
		SDK::GetInstance()->Minecraft->thePlayer->setMotion(Vector3(x, 100000000000, z));
	}
}

void CEntityPlayerSP::sendGroundPacket(Object Packet, JNIEnv* env )
{
	auto queueObject = SDK::GetInstance()->Minecraft->getNetHandler();

	env->CallVoidMethod(queueObject.getInstance(), StrayCache::GetInstance()->netHandlerPlayClient_addToSendQueue, Packet.getInstance());

	return;
}

Object CEntityPlayerSP::C03PacketPlayer(jboolean ground, float yaw, float pitch, JNIEnv* env )
{
	jclass C03;
	Java::GetInstance()->AssignClass("net.minecraft.network.play.client.C03PacketPlayer", C03);
	jmethodID c03Constructer = env->GetMethodID(C03, "<init>", "(Z)V");
	jfieldID yawf, pitchf;
	if (JNIHelper::IsForge()) {
		yawf = env->GetFieldID(C03, "field_149476_e", "F");
		pitchf = env->GetFieldID(C03, "field_149473_f", "F");
	}
	else {
		yawf = env->GetFieldID(C03, "yaw", "F");
		pitchf = env->GetFieldID(C03, "pitch", "F");
	}
	jobject Packet = env->NewObject(C03, c03Constructer, ground);
	env->SetFloatField(Packet, yawf, yaw);
	env->SetFloatField(Packet, pitchf, pitch);
	return Object(Packet);
}