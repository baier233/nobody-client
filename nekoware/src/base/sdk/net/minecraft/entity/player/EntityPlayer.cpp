#include "EntityPlayer.h"

#include "../../../../../java/java.h"


CInventoryPlayer CEntityPlayer::GetInventory()
{
	if (!this->isValid() || this->isNULL()) return CInventoryPlayer{};
	return CInventoryPlayer(Java::Env->GetObjectField(this->getInstance(), StrayCache::entityPlayer_inventory));
}
bool CEntityPlayer::isBlocking()
{
	if (!this->isValid() || this->isNULL()) return false;
	if (Base::version != 1)
		return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entityPlayer_isBlocking);
	return Java::Env->CallIntMethod(this->instance, StrayCache::entityPlayer_isBlocking) > 0;
}