#pragma once

#include "../../Object.h"


class String : public Object
{
public:
	using Object::Object;
	String(std::string text);
	bool operator==(const String& other) const {
		if (getInstance() == nullptr || other.getInstance() == nullptr)
		{
			return false;
		}
		return Java::Env->IsSameObject(getInstance(), other.getInstance());
	}
	std::string ToString();
	bool contains(jstring str);
};

