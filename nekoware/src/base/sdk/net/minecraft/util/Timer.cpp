#include "Timer.h"

#include "../../../../java/java.h"
#include "../../../sdk.h"

//CTimer::CTimer()
//{
//	Java::AssignClass("net.minecraft.util.Timer", StrayCache::timer_class);
//	if (StrayCache::timer_class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		StrayCache::timer_class = StrayCache::timer_class;
//	}
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["renderPartialTicks"] = Java::Env->GetFieldID(StrayCache::timer_class, "field_74281_c", "F");
//		StrayCache::timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "field_74278_d", "F");
//		return;
//	}
//	this->FieldIDs["renderPartialTicks"] = Java::Env->GetFieldID(StrayCache::timer_class, "renderPartialTicks", "F");
//	StrayCache::timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "timerSpeed", "F");
//
//}

float CTimer::GetRenderPartialTicks()
{
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::timer_renderPartialTicks);
}

//jclass CTimer::getClass()
//{
//	return StrayCache::timer_class;
//}
//
//jobject CTimer::getInstance()
//{
//	return Java::Env->GetObjectField(SDK::Minecraft->getInstance(), SDK::Minecraft->FieldIDs["timer"]);
//}

float CTimer::GetTimerSpeed()
{
	return Java::Env->GetFloatField(getInstance(), StrayCache::timer_timerSpeed);

}

void CTimer::SetTimerSpeed(float speed)
{
	return Java::Env->SetFloatField(getInstance(), StrayCache::timer_timerSpeed, speed);

}