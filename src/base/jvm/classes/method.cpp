//
// Created by Administrator on 2024/3/15.
//

#include "method.h"

#include "symbol.h"
#include "bytecode.h"
#include "../break/jvm_break_points.h"

auto java_hotspot::const_method::get_constants() -> const_pool * {
    static VMStructEntry *_constants_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_constants"];
    if (!_constants_entry) return nullptr;
    return *reinterpret_cast<const_pool **>(reinterpret_cast<uint8_t *>(this) + _constants_entry->offset);
}

unsigned short java_hotspot::const_method::get_code_size() {
    static VMStructEntry *_code_size_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_code_size"];
    if (!_code_size_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _code_size_entry->offset);
}

unsigned short java_hotspot::const_method::get_name_index() {
    static VMStructEntry *_name_index_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_name_index"];
    if (!_name_index_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _name_index_entry->offset);
}

unsigned short java_hotspot::const_method::get_signature_index() {
    static VMStructEntry *_signature_index_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()[
        "_signature_index"];
    if (!_signature_index_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _signature_index_entry->offset);
}

auto java_hotspot::const_method::get_const_method_size() -> unsigned short {
    static VMStructEntry *_const_method_size_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()[
        "_const_method_size"];
    if (!_const_method_size_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _const_method_size_entry->offset);
}

auto java_hotspot::const_method::get_max_stack() -> unsigned short {
    static VMStructEntry *_max_stack_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_max_stack"];
    if (!_max_stack_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _max_stack_entry->offset);
}

auto java_hotspot::const_method::set_max_stack(const unsigned short max_stack) -> void {
    static VMStructEntry *_max_stack_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_max_stack"];
    if (!_max_stack_entry) return;
    *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _max_stack_entry->offset) = max_stack;
}

auto java_hotspot::const_method::get_max_locals() -> unsigned short {
    static VMStructEntry *_max_locals_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_max_locals"];
    if (!_max_locals_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _max_locals_entry->offset);
}

auto java_hotspot::const_method::set_max_locals(const unsigned short max_locals) -> void {
    static VMStructEntry *_max_locals_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()["_max_locals"];
    if (!_max_locals_entry) return;
    *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _max_locals_entry->offset) = max_locals;
}

auto java_hotspot::const_method::get_size_of_parameters() -> unsigned short {
    static VMStructEntry *_size_of_parameters_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()[
        "_size_of_parameters"];
    if (!_size_of_parameters_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _size_of_parameters_entry->offset);
}

auto java_hotspot::const_method::get_method_idnum() -> unsigned short {
    static VMStructEntry *_method_idnum_entry = JVMWrappers::find_type_fields("ConstMethod").value().get()[
        "_method_idnum"];
    if (!_method_idnum_entry) return 0;
    return *reinterpret_cast<unsigned short *>(reinterpret_cast<uint8_t *>(this) + _method_idnum_entry->offset);
}

auto java_hotspot::const_method::get_bytecode_start() -> uint8_t * {
    return reinterpret_cast<uint8_t *>(reinterpret_cast<uintptr_t>(this) + bytecode_start_offset);
}

auto java_hotspot::const_method::get_bytecode_size() -> int {
    /* This is a more efficient way to get the bytecode size */
    return get_code_size();
    /*uint8_t *start = get_bytecode_start();
    auto bytecode = std::make_unique<java_runtime::bytecode>(start);
    while (bytecode->get_opcode() != java_runtime::bytecodes::invalid) {
        const int length = bytecode->get_length();
        start += length;
        bytecode = std::make_unique<java_runtime::bytecode>(start);
    }
    return static_cast<int>(start - get_bytecode_start());*/
}

auto java_hotspot::const_method::set_bytecode(const std::vector<uint8_t> &bytecode) -> void {
    const int bytecode_size = get_bytecode_size();
    if (bytecode_size < bytecode.size()) {
        std::cerr << "New bytecode is larger than the original" << std::endl;
        return;
    }
    memcpy(get_bytecode_start(), bytecode.data(), bytecode.size());
    /* if the new bytecode is smaller than the original, fill the rest with nops */
    memset(get_bytecode_start() + bytecode.size(), static_cast<uint8_t>(java_runtime::bytecodes::_nop),
           bytecode_size - bytecode.size());
}

auto java_hotspot::const_method::get_bytecode() -> std::vector<uint8_t> {
    const int bytecode_size = get_bytecode_size();
    std::vector<uint8_t> bytecode(bytecode_size);
    memcpy(bytecode.data(), get_bytecode_start(), bytecode_size);
    return bytecode;
}

auto java_hotspot::const_method::get_const_method_length() -> size_t {
    static VMTypeEntry *_constMethod_entry = JVMWrappers::find_type("ConstMethod").value();
    if (!_constMethod_entry)return 0;
    return _constMethod_entry->size;
}

auto java_hotspot::method::get_const_method() -> const_method * {
    static VMStructEntry *_constMethod_entry = JVMWrappers::find_type_fields("Method").value().get()["_constMethod"];
    if (!_constMethod_entry) return nullptr;
    return *reinterpret_cast<const_method **>(reinterpret_cast<uint8_t *>(this) + _constMethod_entry->offset);
}

auto java_hotspot::method::get_signature() -> std::string {
    const auto const_method = this->get_const_method();
    const auto signature_index = const_method->get_signature_index();
    const auto const_pool = const_method->get_constants();
    const auto base = reinterpret_cast<symbol **>(const_pool->get_base());
    return base[signature_index]->to_string();
}

auto java_hotspot::method::get_name() -> std::string {
    const auto const_method = this->get_const_method();
    const auto name_index = const_method->get_name_index();
    const auto const_pool = const_method->get_constants();
    const auto base = reinterpret_cast<symbol **>(const_pool->get_base());
    return base[name_index]->to_string();
}

auto java_hotspot::method::get_i2i_entry() -> interpreter_entry * {
    static VMStructEntry *_i2i_entry = JVMWrappers::find_type_fields("Method").value().get()["_i2i_entry"];
    if (!_i2i_entry) return nullptr;
    return *reinterpret_cast<interpreter_entry **>(reinterpret_cast<uint8_t *>(this) + _i2i_entry->offset);
}

auto java_hotspot::method::set_break_point(const uintptr_t offset, const native_callback_t &callback) -> void {
    jvm_break_points::set_breakpoint(this, offset, callback);
}

auto java_hotspot::method::remove_break_point(const uintptr_t offset) -> void {
    jvm_break_points::remove_breakpoint(this, offset);
}

auto java_hotspot::method::remove_all_break_points() -> void {
    jvm_break_points::remove_all_breakpoints(this);
}

auto java_hotspot::method::get_access_flags() -> int*
{
    if (!this) return nullptr;
    static VMStructEntry* vm_entry = JVMWrappers::find_type_fields("Method").value().get()["_access_flags"];
    if (!vm_entry)
        return nullptr;
    return (int*)((uint8_t*)this + vm_entry->offset);
}

auto java_hotspot::method::get_flags() -> unsigned short*
{
    if (!this) return nullptr;
    static VMStructEntry* vm_entry = JVMWrappers::find_type_fields("Method").value().get()["_flags"];
    if (!vm_entry)
        return nullptr;
    return (unsigned short*)((uint8_t*)this + vm_entry->offset);
}



auto java_hotspot::method::set_dont_inline(bool enabled) -> void
{
    unsigned short* _flags = get_flags();
    if (!_flags)
    {
        static VMStructEntry* vm_entry = JVMWrappers::find_type_fields("Method").value().get()["_intrinsic_id"];
        if (!vm_entry) return;
        constexpr uintptr_t relative_offset_from_intrinsic_id = 1;
        unsigned char* flags = ((uint8_t*)this + vm_entry->offset + relative_offset_from_intrinsic_id);
        if (enabled)
            *flags |= (1 << 3);
        else
            *flags &= ~(1 << 3);
        return;
    }

    if (enabled)
        *_flags |= _dont_inline;
    else
        *_flags &= ~_dont_inline;
}


