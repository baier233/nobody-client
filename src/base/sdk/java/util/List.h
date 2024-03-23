#pragma once

#include "Collection.h"

class List : public Collection
{
public:
	using Collection::Collection;
	jobjectArray toArray(JNIEnv* env = Java::GetInstance()->Env);
};

