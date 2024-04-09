#include "EntityPlayer.h"

#include "../../../../../java/java.h"


CInventoryPlayer CEntityPlayer::GetInventory(JNIEnv* env )
{
	if (!this->isValid() || this->isNULL()) return CInventoryPlayer{};
	if (Base::version == FORGE_1_18_1)
	{
		return CInventoryPlayer(env->CallObjectMethod(this->instance, StrayCache::GetInstance()->entityPlayer_getInventory));
	}
	return CInventoryPlayer(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->entityPlayer_inventory));
}
bool CEntityPlayer::isBlocking(JNIEnv* env )
{
	if (!this->isValid() || this->isNULL()) return false;
	
	if (Base::version != FORGE_1_12_2 && Base::version != LUNAR_1_12_2)
		return env->CallBooleanMethod(this->getInstance(), StrayCache::GetInstance()->entityPlayer_isBlocking);
	return env->CallIntMethod(this->instance, StrayCache::GetInstance()->entityPlayer_isBlocking) > 0;
}