#pragma once

#include "strayCache.h"
#include <string>
#include <map>

class Object {
public:
	Object(jobject instance);
	Object(const Object& other_Object);
	Object();
	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	bool isEqualTo(const Object& other_Object);
	bool operator!();
	bool isValid();
	bool check();
	bool isNULL();
	~Object();
	void clear();
	jobject getInstance() const; 
	jclass getClass() const;
protected:
	jobject instance = nullptr;
};