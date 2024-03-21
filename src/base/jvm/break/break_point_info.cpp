//
// Created by Administrator on 2024/3/17.
//

#include "break_point_info.h"

#include "../classes/method.h"


break_point_info::break_point_info(
    java_hotspot::method *method,
    const uintptr_t bytecode_address,
    java_hotspot::java_thread *java_thread,
    const uintptr_t parameters
) {
    this->bytecode_address = bytecode_address;
    this->bytecode = new java_runtime::bytecode(method->get_const_method()->get_bytecode_start(),
                                                reinterpret_cast<uint8_t *>(bytecode_address));
    this->java_thread = java_thread;
    this->parameters = parameters;
    this->method = method;
}

break_point_info::~break_point_info() {
    delete this->bytecode;
}

auto break_point_info::get_bytecode_address() const -> uintptr_t {
    return bytecode_address;
}

auto break_point_info::get_bytecode() const -> java_runtime::bytecode * {
    return bytecode;
}
