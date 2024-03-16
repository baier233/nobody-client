#include "ActiveRenderInfo.h"

#include "../../../../../java/java.h"
#include "../../../../sdk.h"
#include "../../../../java/nio/FloatBuffer.h"
#include "../../../../../util/logger.h"

Matrix CActiveRenderInfo::ProjectionMatrix(JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		auto shaderInstance = Java::Env->GetStaticObjectField(StrayCache::renderSystem_class, StrayCache::renderSystem_shader);
		if (!shaderInstance) {
			std::cout << " Cant not get shaderInstance" << std::endl;
			return Matrix{};
		}
		auto projectionUniform = Java::Env->GetObjectField(shaderInstance, StrayCache::shaderInstance_PROJECTION_MATRIX);
		if (!projectionUniform) { std::cout << " Cant not get projectionUniform" << std::endl; return Matrix{}; }
		auto floatValues = Java::Env->GetObjectField(projectionUniform, StrayCache::uniform_floatValues);
		if (!floatValues) { std::cout << " Cant not get floatValues" << std::endl; return Matrix{}; }
		Matrix m = FloatBuffer(floatValues).GetMatrix();
		return m;
	}



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
	if (Base::version == FORGE_1_18_1)
	{
		auto shaderInstance = Java::Env->GetStaticObjectField(StrayCache::renderSystem_class, StrayCache::renderSystem_shader);
		if (!shaderInstance) { std::cout << " Cant not get shaderInstance" << std::endl;  return Matrix{}; }
		auto modleViewUniform = Java::Env->GetObjectField(shaderInstance, StrayCache::shaderInstance_MODEL_VIEW_MATRIX);
		if (!modleViewUniform) { std::cout << " Cant not get modleViewUniform" << std::endl;  return Matrix{}; }
		auto floatValues = Java::Env->GetObjectField(modleViewUniform, StrayCache::uniform_floatValues);
		if (!floatValues) { std::cout << " Cant not get floatValues" << std::endl;  return Matrix{}; }
		Matrix m = FloatBuffer(floatValues).GetMatrix();
		return m;
	}


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

