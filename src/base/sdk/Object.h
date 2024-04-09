#pragma once

#include "strayCache.h"
#include <string>
#include <map>

class Object {
public:
	Object(jobject instance, JNIEnv* env = Java::GetInstance()->Env);
	Object(const Object& other_Object, JNIEnv* env = Java::GetInstance()->Env);
	Object(JNIEnv* env = Java::GetInstance()->Env);
	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	bool isEqualTo(const Object& other_Object, JNIEnv* env = Java::GetInstance()->Env);
	bool operator!();
	bool isValid(JNIEnv* env = Java::GetInstance()->Env);
	bool check(JNIEnv* env = Java::GetInstance()->Env);
	bool isNULL(JNIEnv* env = Java::GetInstance()->Env);
	~Object();
	void clear(JNIEnv* env = Java::GetInstance()->Env);
	jobject getInstance(JNIEnv* env = Java::GetInstance()->Env) const;
	jclass getClass(JNIEnv* env = Java::GetInstance()->Env) const;
protected:
	jobject instance = nullptr;
};