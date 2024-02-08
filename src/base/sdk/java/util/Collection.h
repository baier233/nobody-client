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
	jobjectArray array = (jobjectArray)Java::Env->NewGlobalRef(Java::Env->CallObjectMethod(instance, StrayCache::conllection_toArray));
	if (!array) return {};
	jsize size = Java::Env->GetArrayLength(array);
	if (size == 0) return {};
	std::vector<T> vector(size);
	for (jsize i = 0; i < size; ++i) {
		vector.push_back(T(Java::Env->GetObjectArrayElement(array, i)));
	}
	Java::Env->DeleteGlobalRef(array);
	return vector;
}
