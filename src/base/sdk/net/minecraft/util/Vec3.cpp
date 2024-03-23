#include "Vec3.h"

#include "../../../../java/java.h"
#include "../../../../util/logger.h"
#include "../../../strayCache.h"


Vector3 CVec3::GetNativeVector3(JNIEnv* env )
{
	// ERROR AFTER THIS LINE
	float x = (float)env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->vec3_xCoord);
	float y = (float)env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->vec3_yCoord);
	float z = (float)env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->vec3_zCoord);
	return Vector3{
		x,y,z
	};
}
Vector3D CVec3::GetNativeVector3D(JNIEnv* env )
{
	// ERROR AFTER THIS LINE
	auto x = env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->vec3_xCoord);
	auto y = env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->vec3_yCoord);
	auto z = env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->vec3_zCoord);
	return Vector3D{
		x,y,z
	};
}