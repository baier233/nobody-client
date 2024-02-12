#include "ActiveRenderInfo.h"

#include "../../../../../java/java.h"
#include "../../../../sdk.h"
#include "../../../../java/nio/FloatBuffer.h"
#include "../../../../../util/logger.h"

Matrix CActiveRenderInfo::ProjectionMatrix(JNIEnv* env )
{
	jobject projection = env->GetStaticObjectField(StrayCache::activeRenderInfo_class, StrayCache::activeRenderInfo_PROJECTION);
	if (!projection)
	{
		return Matrix{};
	}
	Matrix m = FloatBuffer(projection).GetMatrix();
	return m;
}

Matrix CActiveRenderInfo::ModelViewMatrix(JNIEnv* env )
{
	jobject modelView = env->GetStaticObjectField(StrayCache::activeRenderInfo_class, StrayCache::activeRenderInfo_MODELVIEW);
	if (!modelView)
	{
		return Matrix{};
	}
	Matrix m = FloatBuffer::FloatBuffer(modelView).GetMatrix();
	return m;
}

int CActiveRenderInfo::Get_VIEWPORT(JNIEnv* env )
{
	return 0;
	//return env.CallFloatMethod();
}

