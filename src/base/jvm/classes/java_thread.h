//
// Created by Administrator on 2024/3/15.
//

#ifndef THREAD_H
#define THREAD_H

#include "../include_header.h"
#include "../utility/vm_helper.h"

namespace java_hotspot {
    class java_thread {
    public:

        uintptr_t* get_operand_stack()
        {
            if (!vm_helper::thread_operand_stack_offset)
                throw std::runtime_error("vm_helper::thread_operand_stack_offset is not initialized");
            return *(uintptr_t**)((uintptr_t)this + vm_helper::thread_operand_stack_offset);
        }


        static java_thread* current()
        {
            /* Get gs 0x58 */
            uintptr_t gs58 = *(uintptr_t*)((uintptr_t)__readgsqword(0x58) + 0x10);
            return *(java_thread**)(gs58 + 0x20);
        }
    };
    
}



#endif //THREAD_H
