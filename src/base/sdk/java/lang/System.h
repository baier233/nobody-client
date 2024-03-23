#pragma once
#pragma once

#include "../../Object.h"


class System
{
public:
	static void gc(JNIEnv* env = Java::GetInstance()->Env);
};

