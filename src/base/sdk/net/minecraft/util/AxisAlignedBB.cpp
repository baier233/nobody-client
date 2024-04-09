#include "AxisAlignedBB.h"

#include "../../../../java/java.h"
#include "../../../../util/logger.h"
#include "../../../strayCache.h"

//CAxisAlignedBB::CAxisAlignedBB()
//{
//	if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//	this->Class = StrayCache::GetInstance()->axisAlignedBB_class;
//}
//
//CAxisAlignedBB::CAxisAlignedBB(jobject instance) : CAxisAlignedBB()
//{
//	this->Instance = instance;
//}
//
//jclass CAxisAlignedBB::getClass()
//{
//	return this->Class;
//}
//
//jobject CAxisAlignedBB::getInstance()
//{
//	return this->Instance;
//}

BoundingBox CAxisAlignedBB::GetNativeBoundingBox(JNIEnv* env )
{
	return BoundingBox{
		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_minX),
		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_minY),
		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_minZ),

		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_maxX),
		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_maxY),
		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_maxZ),
	};
}

void CAxisAlignedBB::SetBoundingBox(BoundingBox newBoundingBox, JNIEnv* env )
{
	env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_minX, newBoundingBox.minX);
	env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_minY, newBoundingBox.minY);
	env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_minZ, newBoundingBox.minZ);

	env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_maxX, newBoundingBox.maxX);
	env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_maxY, newBoundingBox.maxY);
	env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->axisAlignedBB_maxZ, newBoundingBox.maxZ);
}
