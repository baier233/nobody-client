#include "ActiveRenderInfo.h"

#include "../../../../../java/java.h"
#include "../../../../sdk.h"
#include "../../../../java/nio/FloatBuffer.h"
#include "../../../../../util/logger.h"

Matrix CActiveRenderInfo::ProjectionMatrix()
{
	jobject projection = Java::Env->GetStaticObjectField(StrayCache::activeRenderInfo_class, StrayCache::activeRenderInfo_PROJECTION);
	Matrix m = FloatBuffer(projection).GetMatrix();
	return m;
}

Matrix CActiveRenderInfo::ModelViewMatrix()
{
	jobject modelView = Java::Env->GetStaticObjectField(StrayCache::activeRenderInfo_class, StrayCache::activeRenderInfo_MODELVIEW);
	Matrix m = FloatBuffer::FloatBuffer(modelView).GetMatrix();
	return m;
}

int CActiveRenderInfo::Get_VIEWPORT()
{
	return 0;
	//return Java::Env.CallFloatMethod();
}

