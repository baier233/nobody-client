#include "Object.h"

Object::Object(jobject instance, JNIEnv* env)
{
	if (instance) {
		this->instance = env->NewGlobalRef(instance);
		env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
}

Object::Object(const Object& other_Object, JNIEnv* env)
{
	if (other_Object.instance) this->instance = env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
}

Object::Object(JNIEnv* env)
{
}

Object& Object::operator=(const Object& other_Object)
{
	if (this->instance) Java::GetInstance()->Env->DeleteGlobalRef(this->instance);
	if (other_Object.instance) this->instance = Java::GetInstance()->Env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
	return *this;
}

Object& Object::operator=(jobject instance)
{
	if (this->instance) Java::GetInstance()->Env->DeleteGlobalRef(this->instance);
	if (instance) {
		this->instance = Java::GetInstance()->Env->NewGlobalRef(instance);
		Java::GetInstance()->Env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
	return *this;
}

bool Object::isEqualTo(const Object& other_Object, JNIEnv* env)
{
	if (this->instance == other_Object.instance) {
		return true;
	}
	else if (this->instance && other_Object.instance) {
		return env->IsSameObject(this->instance, other_Object.instance) == JNI_TRUE;
	}
	return false;
}

bool Object::operator!()
{
	return this->instance == nullptr;
}

bool Object::isValid(JNIEnv* env)
{
	return this->instance != nullptr;
}
bool Object::check(JNIEnv* env) {
	return this->isValid() || !this->isNULL();
}
bool Object::isNULL(JNIEnv* env)
{
	return env->IsSameObject(this->instance, NULL);
}

Object::~Object()
{
	if (!Java::GetInstance()->Env) return;
	if (instance) Java::GetInstance()->Env->DeleteGlobalRef(instance);
}

void Object::clear(JNIEnv* env)
{
	if (!env) return;
	if (this->instance) {
		env->DeleteGlobalRef(this->instance);
		this->instance = nullptr;
	}
}

jobject Object::getInstance(JNIEnv* env) const
{
	return instance;
}

jclass Object::getClass(JNIEnv* env) const
{
	return env->GetObjectClass(this->instance);
}
