#pragma once

#include "../EntityLivingBase.h"
#include "InventoryPlayer.h"

class CEntityPlayer : public CEntityLivingBase
{
public:
	bool operator==(const CEntityPlayer& other) const {
		if (getInstance() == nullptr || other.getInstance() == nullptr)
		{
			return false;
		}
		return Java::Env->IsSameObject(getInstance(), other.getInstance());
	}

	using CEntityLivingBase::CEntityLivingBase;
	CInventoryPlayer GetInventory(JNIEnv* env = Java::Env);
	bool isBlocking(JNIEnv* env = Java::Env);
};

namespace std {
	template <>
	struct hash<CEntityPlayer> {
		size_t operator()(const CEntityPlayer& player) const {
			return (size_t)player.getInstance();
		}
	};
}