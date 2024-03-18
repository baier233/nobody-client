#include "bytecode.h"

#include "../break/break_point_info.h"
#include "../break/byte_code_info.h"

namespace java_runtime {
    bytecodes bytecode::get_opcode() const {
        return static_cast<bytecodes>(*this->opcode);
    }

    int bytecode::get_length() const {
        switch (this->get_opcode()) {
            case bytecodes::wide: {
                if (const auto wide_opcode = static_cast<bytecodes>(opcode[1]); wide_opcode == bytecodes::iinc) {
                    return 6;
                }
                return 4;
            }
            case bytecodes::lookupswitch: {
                const int position = bytecode_offsets[this->opcode];
                const int padding = (4 - (position % 4)) % 4;
                int length = 1 /* opcode */
                             + padding /* padding */
                             + 4 /* default */
                             + 4 /* npairs */;
                const int npairs = *reinterpret_cast<int32_t *>(this->opcode + 1 + padding + 4 + 4);
                length += 8 * npairs;
                return length;
            }
            case bytecodes::tableswitch: {
                const int position = bytecode_offsets[this->opcode];
                const int padding = (4 - (position % 4)) % 4;
                const int high = *reinterpret_cast<int32_t *>(this->opcode + 1 + padding + 4);
                const int low = *reinterpret_cast<int32_t *>(this->opcode + 1 + padding + 4 + 4);
                const int length = 1 /* opcode */
                                   + padding /* padding */
                                   + 4 /* default */
                                   + 4 /* high */
                                   + 4 /* low */
                                   + 4 * (high - low + 1);
                return length;
            }
            default: {
                return jvm_byte_code::bytecode_lengths[static_cast<int8_t>(this->get_opcode())] + 1;
            }
        }
        // Should never happen
        return 0;
    }

    int bytecode::get_stack_consumption() const {
        return jvm_byte_code::bytecode_operand_consumption[static_cast<uint8_t>(this->get_opcode())];
    }
}

/* Static bytecode map */
std::map<uint8_t *, uint16_t> java_runtime::bytecode::bytecode_offsets;
