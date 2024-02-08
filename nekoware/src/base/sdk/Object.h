#pragma once

#include "strayCache.h"
#include <string>
#include <map>

class Object {
public:
	Object(jobject instance, JNIEnv* env = Java::Env);
	Object(const Object& other_Object, JNIEnv* env = Java::Env);
	Object(JNIEnv* env = Java::Env);
	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	bool isEqualTo(const Object& other_Object, JNIEnv* env = Java::Env);
	bool operator!();
	bool isValid(JNIEnv* env = Java::Env);
	bool check(JNIEnv* env = Java::Env);
	bool isNULL(JNIEnv* env = Java::Env);
	~Object();
	void clear(JNIEnv* env = Java::Env);
	jobject getInstance(JNIEnv* env = Java::Env) const;
	jclass getClass(JNIEnv* env = Java::Env) const;
protected:
	jobject instance = nullptr;
};