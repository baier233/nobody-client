//
// Created by Administrator on 2024/3/17.
//

#include "jvm_break_points.h"

#include "../classes/java_thread.h"
#include "../classes/method.h"

extern "C" {
uintptr_t __forceinline jhook_get_r14_address();
}

auto jvm_break_points::breakpoint_callback(
    java_hotspot::java_thread *java_thread,
    java_hotspot::method *method,
    const uintptr_t bytecode_address
) -> void {
    const auto parameters = jhook_get_r14_address();
    breakpoint_handler(java_thread, method, bytecode_address, parameters);
}

/* As ASM is used , Add _declspec( noinline ) */
_declspec( noinline )
auto jvm_break_points::breakpoint_handler(
    java_hotspot::java_thread *java_thread,
    java_hotspot::method *method,
    uintptr_t bytecode_address,
    uintptr_t parameters
) -> void {
    const auto callback = breakpoint_callbacks[bytecode_address];
    if (!callback) {
        breakpoint_hook.GetOrignalFunc()(java_thread, method, bytecode_address);
        return;
    }
    const auto breakpoint_info = std::make_unique<break_point_info>(
        method, bytecode_address, java_thread, parameters
    );
    callback(breakpoint_info.get());
}


auto jvm_break_points::original_bytecode_handler(
    java_hotspot::java_thread *java_thread,
    java_hotspot::method *method,
    const uintptr_t bytecode_address
) -> uint8_t {
    if (!original_bytecodes.contains(bytecode_address)) {
        return original_bytecode_hook.GetOrignalFunc()(java_thread, method, bytecode_address);
    }
    const uint8_t original_bytecode = original_bytecodes[bytecode_address];
    return original_bytecode;
}

auto jvm_break_points::set_breakpoint(java_hotspot::method *method, const uintptr_t offset,
                                      const native_callback_t &callback) -> bool {
    uint8_t *bytecode_address = method->get_const_method()->get_bytecode_start() + offset;
    const uint8_t bytecode = *bytecode_address;
    const auto address = reinterpret_cast<uintptr_t>(bytecode_address);
    original_bytecodes[address] = bytecode;
    breakpoint_callbacks[address] = callback;
    // Set breakpoint
    *bytecode_address = static_cast<uint8_t>(java_runtime::bytecodes::breakpoint);
    return true;
}

auto jvm_break_points::remove_breakpoint(java_hotspot::method *method, const uintptr_t offset) -> void {
    uint8_t *bytecode_address = method->get_const_method()->get_bytecode_start() + offset;
    const uint8_t bytecode = original_bytecodes[reinterpret_cast<uintptr_t>(bytecode_address)];
    original_bytecodes.erase(reinterpret_cast<uintptr_t>(bytecode_address));
    breakpoint_callbacks.erase(reinterpret_cast<uintptr_t>(bytecode_address));
    *bytecode_address = bytecode;
}

auto jvm_break_points::remove_all_breakpoints(java_hotspot::method *method) -> void {
    uint8_t *bytecode_start = method->get_const_method()->get_bytecode_start();
    for (uint8_t *bytecode_address = bytecode_start;; bytecode_address++) {
        if (*bytecode_address == 0xFF) {
            break;
        }
        if (original_bytecodes.contains(reinterpret_cast<uintptr_t>(bytecode_address))) {
            const uint8_t bytecode = original_bytecodes[reinterpret_cast<uintptr_t>(bytecode_address)];
            original_bytecodes.erase(reinterpret_cast<uintptr_t>(bytecode_address));
            breakpoint_callbacks.erase(reinterpret_cast<uintptr_t>(bytecode_address));
            *bytecode_address = bytecode;
        }
    }
}
