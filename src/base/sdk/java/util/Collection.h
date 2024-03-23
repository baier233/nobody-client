#pragma once
#include <vector>

#include "../../Object.h"

class Collection : public Object {
public:
	using Object::Object;
	template<class T>
	std::vector<T> toVector();
};

template<class T>
inline std::vector<T> Collection::toVector()
{
	if (!this->instance) return {};
	jobjectArray array = (jobjectArray)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->CallObjectMethod(instance, StrayCache::GetInstance()->conllection_toArray));
	if (!array) return {};
	jsize size = Java::GetInstance()->Env->GetArrayLength(array);
	if (size == 0) return {};
	std::vector<T> vector(size);
	for (jsize i = 0; i < size; ++i) {
		auto obj = Java::GetInstance()->Env->GetObjectArrayElement(array, i);
		if (!obj) continue;
		if (Java::GetInstance()->Env->IsSameObject(obj, NULL)) continue;
		vector.push_back(T(obj));
	}
	Java::GetInstance()->Env->DeleteGlobalRef(array);
	return vector;
}
