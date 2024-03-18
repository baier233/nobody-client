//
// Created by Administrator on 2024/3/15.
//

#ifndef JAVAINTEROP_H
#define JAVAINTEROP_H

#include "include_header.h"
#include "classes/klass.h"

class java_interop {
public:
    java_interop();
    java_interop(JNIEnv* env);

    ~java_interop();

    auto find_class(const char *name) const -> jclass;

    auto find_method(jclass clazz, const char *name, const char *sig) const -> jmethodID;

    auto find_static_method(jclass clazz, const char *name, const char *sig) const -> jmethodID;

    auto find_field(jclass clazz, const char *name, const char *sig) const -> jfieldID;

    static java_hotspot::instance_klass *get_instance_class(jclass klasas);

    [[nodiscard]] auto get_env() const -> JNIEnv *;

    [[nodiscard]] auto get_vm() const -> JavaVM *;

    [[nodiscard]] auto get_jvmti() const -> jvmtiEnv *;

private:
    JavaVM *vm = nullptr;
    JNIEnv *env = nullptr;
    jvmtiEnv *jvmti = nullptr;
};


#endif //JAVAINTEROP_H
