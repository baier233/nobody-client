#include "RenderManager.h"

#include "../../../../../../java/java.h"
#include "../../../../../sdk.h"

Vector3 CRenderManager::RenderPos(JNIEnv* env)
{
	return Vector3{
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_renderPosX),
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_renderPosY),
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_renderPosZ)
	};
}

Vector3 CRenderManager::ViewerPos(JNIEnv* env)
{
	return Vector3{
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_viewerPosX),
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_viewerPosY),
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_viewerPosZ)
	};
}

Vector2 CRenderManager::PlayerView(JNIEnv* env)
{
	return Vector2(
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_playerViewX),
		(float)(double)env->GetDoubleField(instance, StrayCache::renderManager_playerViewY)
	);
}
