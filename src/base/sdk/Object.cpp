#include "Object.h"

Object::Object(jobject instance)
{
	if (instance) {
		this->instance = Java::Env->NewGlobalRef(instance);
		Java::Env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
}

Object::Object(const Object& other_Object)
{
	if (other_Object.instance) this->instance = Java::Env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
}

Object::Object()
{
}

Object& Object::operator=(const Object& other_Object)
{
	if (this->instance) Java::Env->DeleteGlobalRef(this->instance);
	if (other_Object.instance) this->instance = Java::Env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
	return *this;
}

Object& Object::operator=(jobject instance)
{
	if (this->instance) Java::Env->DeleteGlobalRef(this->instance);
	if (instance) {
		this->instance = Java::Env->NewGlobalRef(instance);
		Java::Env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
	return *this;
}

bool Object::isEqualTo(const Object& other_Object)
{
	if (this->instance == other_Object.instance) {
		return true;
	}
	else if (this->instance && other_Object.instance) {
		return Java::Env->IsSameObject(this->instance, other_Object.instance) == JNI_TRUE;
	}
	return false;
}

bool Object::operator!()
{
	return this->instance == nullptr;
}

bool Object::isValid()
{
	return this->instance != nullptr;
}
bool Object::check() {
	return this->isValid() || !this->isNULL();
}
bool Object::isNULL()
{
	return Java::Env->IsSameObject(this->instance,NULL);
}

Object::~Object()
{
	if (!Java::Env) return;
	if (instance) Java::Env->DeleteGlobalRef(instance);
}

void Object::clear()
{
	if (!Java::Env) return;
	if (this->instance) {
		Java::Env->DeleteGlobalRef(this->instance);
		this->instance = nullptr;
	}
}

jobject Object::getInstance() const
{
	return instance;
}

jclass Object::getClass() const
{
	return Java::Env->GetObjectClass(this->instance);
}
