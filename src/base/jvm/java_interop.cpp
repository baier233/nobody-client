//
// Created by Administrator on 2024/3/15.
//

#include "java_interop.h"
#include "utility/jvm_internal.h"

#include <stdexcept>

java_interop::java_interop() {
    jint vm_count = 0;
    /* Try to get the first created jvm */
    jint error = JNI_GetCreatedJavaVMs(&vm, 1, &vm_count);

    /* Check error */
    if (error != JNI_OK || vm_count == 0)
        throw std::runtime_error("Failed to get created Java VMs");

    /* Attach thread */
    error = vm->AttachCurrentThreadAsDaemon(reinterpret_cast<void **>(&env), nullptr);

    /* Check error */
    if (error != JNI_OK)
        throw std::runtime_error("Failed to attach thread");

    error = vm->GetEnv(reinterpret_cast<void **>(&jvmti), JVMTI_VERSION_1_2);
    if (error != JNI_OK)
        throw std::runtime_error("Failed to get jvmti environment");
}

java_interop::java_interop(JNIEnv* env)
{
    this->env = env;
    auto error = env->GetJavaVM(&vm);
    if (error != JNI_OK)
        throw std::runtime_error("Failed to attach thread");

    error = vm->GetEnv(reinterpret_cast<void**>(&jvmti), JVMTI_VERSION_1_2);
    if (error != JNI_OK)
        throw std::runtime_error("Failed to get jvmti environment");
}

java_interop::~java_interop() {
    if (!vm)
        return;
    vm->DetachCurrentThread();
}

auto java_interop::find_class(const char *name) const -> jclass {
    /* Find class */
    const auto clazz = env->FindClass(name);

    /* Check error */
    if (!clazz)
        throw std::runtime_error("Failed to find class");

    return clazz;
}

auto java_interop::find_method(const jclass clazz, const char *name, const char *sig) const -> jmethodID {
    /* Find method */
    const auto method = env->GetMethodID(clazz, name, sig);

    /* Check error */
    if (!method)
        throw std::runtime_error("Failed to find method");

    return method;
}

auto java_interop::find_static_method(const jclass clazz, const char *name, const char *sig) const -> jmethodID {
    /* Find method */
    const auto method = env->GetStaticMethodID(clazz, name, sig);

    /* Check error */
    if (!method)
        throw std::runtime_error("Failed to find static method");

    return method;
}

auto java_interop::find_field(_jclass *const clazz, const char *name, const char *sig) const -> jfieldID {
    /* Find field */
    const auto field = env->GetFieldID(clazz, name, sig);

    /* Check error */
    if (!field)
        throw std::runtime_error("Failed to find field");

    return field;
}

auto java_interop::get_env() const -> JNIEnv * {
    return env;
}

auto java_interop::get_vm() const -> JavaVM * {
    return vm;
}

auto java_interop::get_jvmti() const -> jvmtiEnv * {
    return jvmti;
}

java_hotspot::instance_klass *java_interop::get_instance_class(_jclass *const klasas) {
    /* Check if class is null */
    if (klasas == nullptr)
        return nullptr;

    /* Dereference class */
    void *klass_ptr = *reinterpret_cast<void **>(klasas);
    if (klass_ptr == nullptr)
        return nullptr;

    // Get the instance klass
    klass_ptr = *reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(klass_ptr) + global_offsets::klass_offset);
    return static_cast<java_hotspot::instance_klass *>(klass_ptr);
}
