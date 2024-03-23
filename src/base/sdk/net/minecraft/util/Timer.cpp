#include "Timer.h"

#include "../../../../java/java.h"
#include "../../../sdk.h"

//CTimer::CTimer()
//{
//	Java::GetInstance()->AssignClass("net.minecraft.util.Timer", StrayCache::GetInstance()->timer_class);
//	if (StrayCache::GetInstance()->timer_class == nullptr)
//	{
//		if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//		StrayCache::GetInstance()->timer_class = StrayCache::GetInstance()->timer_class;
//	}
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["renderPartialTicks"] ->GetFieldID(StrayCache::GetInstance()->timer_class, "field_74281_c", "F");
//		StrayCache::GetInstance()->timer_timerSpeed ->GetFieldID(StrayCache::GetInstance()->timer_class, "field_74278_d", "F");
//		return;
//	}
//	this->FieldIDs["renderPartialTicks"] ->GetFieldID(StrayCache::GetInstance()->timer_class, "renderPartialTicks", "F");
//	StrayCache::GetInstance()->timer_timerSpeed ->GetFieldID(StrayCache::GetInstance()->timer_class, "timerSpeed", "F");
//
//}

float CTimer::GetRenderPartialTicks(JNIEnv* env )
{
	return env->GetFloatField(this->getInstance(), StrayCache::GetInstance()->timer_renderPartialTicks);
}

//jclass CTimer::getClass()
//{
//	return StrayCache::GetInstance()->timer_class;
//}
//
//jobject CTimer::getInstance()
//{
//	return Java::GetInstance()->Env->GetObjectField(SDK::Minecraft->getInstance(), SDK::Minecraft->FieldIDs["timer"]);
//}

float CTimer::GetTimerSpeed(JNIEnv* env )
{
	return env->GetFloatField(getInstance(), StrayCache::GetInstance()->timer_timerSpeed);

}

void CTimer::SetTimerSpeed(float speed, JNIEnv* env )
{
	return env->SetFloatField(getInstance(), StrayCache::GetInstance()->timer_timerSpeed, speed);

}