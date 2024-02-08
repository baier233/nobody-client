#include "RenderManager.h"

#include "../../../../../../java/java.h"
#include "../../../../../sdk.h"

Vector3 CRenderManager::RenderPos()
{
	return Vector3{
		(float)(double) Java::Env->GetDoubleField(instance, StrayCache::renderManager_renderPosX),
		(float)(double) Java::Env->GetDoubleField(instance, StrayCache::renderManager_renderPosY),
		(float)(double) Java::Env->GetDoubleField(instance, StrayCache::renderManager_renderPosZ)
	};
}

Vector3 CRenderManager::ViewerPos()
{
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(instance, StrayCache::renderManager_viewerPosX),
		(float)(double)Java::Env->GetDoubleField(instance, StrayCache::renderManager_viewerPosY),
		(float)(double)Java::Env->GetDoubleField(instance, StrayCache::renderManager_viewerPosZ)
	};
}
