#pragma once

#include "../../../Object.h"
#include "../../../java/util/List.h"
class CNonNullList : public Object
{
public:
	using Object::Object;
	List getList(JNIEnv* env = Java::GetInstance()->Env);

};