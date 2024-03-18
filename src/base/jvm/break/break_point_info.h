//
// Created by Administrator on 2024/3/17.
//

#ifndef BREAK_POINT_INFO_H
#define BREAK_POINT_INFO_H
#include <functional>

#include "../classes/java_thread.h"
#include "../classes/bytecode.h"

namespace java_hotspot {
    class method;
}

class break_point_info {
public:
    explicit break_point_info(
        java_hotspot::method *method,
        uintptr_t bytecode_address,
        java_hotspot::java_thread *java_thread,
        uintptr_t parameters
    );

    ~break_point_info();

    [[nodiscard]] auto get_bytecode_address() const -> uintptr_t;

    [[nodiscard]] auto get_bytecode() const -> java_runtime::bytecode *;

private:
    uintptr_t bytecode_address;
    uintptr_t parameters;
    java_runtime::bytecode *bytecode;
    java_hotspot::java_thread *java_thread;
};


using breakpoint_callback_t = void (*)(java_hotspot::java_thread *, java_hotspot::method *, uintptr_t);
using original_bytecode_handler_t = uint8_t (*)(java_hotspot::java_thread *, java_hotspot::method *, uintptr_t);

using native_callback_t = std::function<void(break_point_info *)>;

#endif //BREAK_POINT_INFO_H
