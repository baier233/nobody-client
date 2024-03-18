//
// Created by Administrator on 2024/3/15.
//

#include "vm_helper.h"
#include "memory_utility.h"

auto vm_helper::find_vm_calls(PVOID start) -> std::vector<PVOID> {
    std::vector<PVOID> calls;
    constexpr size_t max_len = 0x500;

    const auto start_addr = reinterpret_cast<uintptr_t>(start);
    const uintptr_t end_addr = start_addr + max_len;
    auto call_pattern = const_cast<char *>(vm_call_pattern.c_str());


    uintptr_t vm_call_addr = scan(call_pattern, start_addr, end_addr);
    if (!vm_call_addr) {
        std::cout << "Failed to find vm_call_addr using pattern 1" << std::endl;
        call_pattern = const_cast<char *>(vm_call_pattern2.c_str());
        vm_call_addr = scan(call_pattern, start_addr, end_addr);
    }


    if (vm_call_addr && !thread_frame_offset) {
        const auto preserve_frame_mov = vm_call_addr;
        /*
                49:89AF F0030000         | mov qword ptr ds:[r15+3F0],rbp
            */
        thread_frame_offset = *reinterpret_cast<uint32_t *>(preserve_frame_mov + 3);
        const uintptr_t operand_stack_mov = preserve_frame_mov + 7;
        /*
                49:8987 E0030000         | mov qword ptr ds:[r15+3E0],rax
            */
        thread_operand_stack_offset = *reinterpret_cast<uint32_t *>(operand_stack_mov + 3);
    }

    if (!vm_call_addr) {
        std::cout << "Failed to find vm_call_addr using pattern 2" << std::endl;
    }

    // TODO: Wait fix finded address
    std::cout << "vm_call_addr: " << reinterpret_cast<void *>(vm_call_addr) << std::endl;

    while (vm_call_addr) {
        const uintptr_t vm_call_address = scan(vm_call_address_pattern.c_str(), vm_call_addr, vm_call_addr + 0x64);
        calls.push_back(*reinterpret_cast<PVOID *>(vm_call_address + 6));
        vm_call_addr = scan(call_pattern, vm_call_addr + 1, end_addr);
    }

    return calls;
}
