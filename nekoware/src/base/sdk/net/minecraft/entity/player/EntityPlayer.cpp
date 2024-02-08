#include "EntityPlayer.h"

#include "../../../../../java/java.h"


CInventoryPlayer CEntityPlayer::GetInventory(JNIEnv* env )
{
	if (!this->isValid() || this->isNULL()) return CInventoryPlayer{};
	return CInventoryPlayer(env->GetObjectField(this->getInstance(), StrayCache::entityPlayer_inventory));
}
bool CEntityPlayer::isBlocking(JNIEnv* env )
{
	if (!this->isValid() || this->isNULL()) return false;
	if (Base::version != 1)
		return env->CallBooleanMethod(this->getInstance(), StrayCache::entityPlayer_isBlocking);
	return env->CallIntMethod(this->instance, StrayCache::entityPlayer_isBlocking) > 0;
}