//
// Created by Administrator on 2024/3/15.
//

#ifndef JVM_INTERNAL_H
#define JVM_INTERNAL_H

#include "../include_header.h"


enum Flags
{
    _caller_sensitive = 1 << 0,
    _force_inline = 1 << 1,
    _dont_inline = 1 << 2,
    _hidden = 1 << 3,
    _has_injected_profile = 1 << 4,
    _intrinsic_candidate = 1 << 5,
    _reserved_stack_access = 1 << 6,
    _scoped = 1 << 7
};


enum {
    JVM_ACC_PUBLIC        = 0x0001,
    JVM_ACC_PRIVATE       = 0x0002,
    JVM_ACC_PROTECTED     = 0x0004,
    JVM_ACC_STATIC        = 0x0008,
    JVM_ACC_FINAL         = 0x0010,
    JVM_ACC_SYNCHRONIZED  = 0x0020,
    JVM_ACC_SUPER         = 0x0020,
    JVM_ACC_VOLATILE      = 0x0040,
    JVM_ACC_BRIDGE        = 0x0040,
    JVM_ACC_TRANSIENT     = 0x0080,
    JVM_ACC_VARARGS       = 0x0080,
    JVM_ACC_NATIVE        = 0x0100,
    JVM_ACC_INTERFACE     = 0x0200,
    JVM_ACC_ABSTRACT      = 0x0400,
    JVM_ACC_STRICT        = 0x0800,
    JVM_ACC_SYNTHETIC     = 0x1000,
    JVM_ACC_ANNOTATION    = 0x2000,
    JVM_ACC_ENUM          = 0x4000
};


#define JVM_RECOGNIZED_CLASS_MODIFIERS (JVM_ACC_PUBLIC | \
JVM_ACC_FINAL | \
JVM_ACC_SUPER | \
JVM_ACC_INTERFACE | \
JVM_ACC_ABSTRACT | \
JVM_ACC_ANNOTATION | \
JVM_ACC_ENUM | \
JVM_ACC_SYNTHETIC)

#define JVM_RECOGNIZED_FIELD_MODIFIERS (JVM_ACC_PUBLIC | \
JVM_ACC_PRIVATE | \
JVM_ACC_PROTECTED | \
JVM_ACC_STATIC | \
JVM_ACC_FINAL | \
JVM_ACC_VOLATILE | \
JVM_ACC_TRANSIENT | \
JVM_ACC_ENUM | \
JVM_ACC_SYNTHETIC)

#define JVM_RECOGNIZED_METHOD_MODIFIERS (JVM_ACC_PUBLIC | \
JVM_ACC_PRIVATE | \
JVM_ACC_PROTECTED | \
JVM_ACC_STATIC | \
JVM_ACC_FINAL | \
JVM_ACC_SYNCHRONIZED | \
JVM_ACC_BRIDGE | \
JVM_ACC_VARARGS | \
JVM_ACC_NATIVE | \
JVM_ACC_ABSTRACT | \
JVM_ACC_STRICT | \
JVM_ACC_SYNTHETIC)

namespace jvm_internal {


    enum {
        // See jvm.h for shared JVM_ACC_XXX access flags

        // HotSpot-specific access flags

        // flags actually put in .class file
        JVM_ACC_WRITTEN_FLAGS = 0x00007FFF,

        // Method* flags
        JVM_ACC_MONITOR_MATCH = 0x10000000, // True if we know that monitorenter/monitorexit bytecodes match
        JVM_ACC_HAS_MONITOR_BYTECODES = 0x20000000, // Method contains monitorenter/monitorexit bytecodes
        JVM_ACC_HAS_LOOPS = 0x40000000, // Method has loops
        JVM_ACC_LOOPS_FLAG_INIT = (int) 0x80000000, // The loop flag has been initialized
        JVM_ACC_QUEUED = 0x01000000, // Queued for compilation
        JVM_ACC_NOT_C2_COMPILABLE = 0x02000000,
        JVM_ACC_NOT_C1_COMPILABLE = 0x04000000,
        JVM_ACC_NOT_C2_OSR_COMPILABLE = 0x08000000,
        JVM_ACC_HAS_LINE_NUMBER_TABLE = 0x00100000,
        JVM_ACC_HAS_CHECKED_EXCEPTIONS = 0x00400000,
        JVM_ACC_HAS_JSRS = 0x00800000,
        JVM_ACC_IS_OLD = 0x00010000, // RedefineClasses() has replaced this method
        JVM_ACC_IS_OBSOLETE = 0x00020000, // RedefineClasses() has made method obsolete
        JVM_ACC_IS_PREFIXED_NATIVE = 0x00040000, // JVMTI has prefixed this native method
        JVM_ACC_ON_STACK = 0x00080000, // RedefinedClasses() is used on the stack

        // Klass* flags
        JVM_ACC_HAS_MIRANDA_METHODS = 0x10000000, // True if this class has miranda methods in it's vtable
        JVM_ACC_HAS_VANILLA_CONSTRUCTOR = 0x20000000, // True if klass has a vanilla default constructor
        JVM_ACC_HAS_FINALIZER = 0x40000000, // True if klass has a non-empty finalize() method
        JVM_ACC_IS_CLONEABLE = (int) 0x80000000, // True if klass supports the Clonable interface
        JVM_ACC_HAS_FINAL_METHOD = 0x01000000, // True if klass has final method

        // Klass* and Method* flags
        JVM_ACC_HAS_LOCAL_VARIABLE_TABLE = 0x00200000,

        JVM_ACC_PROMOTED_FLAGS = 0x00200000, // flags promoted from methods to the holding klass

        // field flags
        // Note: these flags must be defined in the low order 16 bits because
        // InstanceKlass only stores a ushort worth of information from the
        // AccessFlags value.
        // These bits must not conflict with any other field-related access flags
        // (e.g., ACC_ENUM).
        // Note that the class-related ACC_ANNOTATION bit conflicts with these flags.
        JVM_ACC_FIELD_ACCESS_WATCHED = 0x00002000, // field access is watched by JVMTI
        JVM_ACC_FIELD_MODIFICATION_WATCHED = 0x00008000, // field modification is watched by JVMTI
        JVM_ACC_FIELD_INTERNAL = 0x00000400, // internal field, same as JVM_ACC_ABSTRACT
        JVM_ACC_FIELD_STABLE = 0x00000020, // @Stable field, same as JVM_ACC_SYNCHRONIZED
        JVM_ACC_FIELD_HAS_GENERIC_SIGNATURE = 0x00000800, // field has generic signature

        JVM_ACC_FIELD_INTERNAL_FLAGS = JVM_ACC_FIELD_ACCESS_WATCHED |
                                       JVM_ACC_FIELD_MODIFICATION_WATCHED |
                                       JVM_ACC_FIELD_INTERNAL |
                                       JVM_ACC_FIELD_STABLE |
                                       JVM_ACC_FIELD_HAS_GENERIC_SIGNATURE,

        // flags accepted by set_field_flags()
        JVM_ACC_FIELD_FLAGS = JVM_RECOGNIZED_FIELD_MODIFIERS | JVM_ACC_FIELD_INTERNAL_FLAGS
    };
}

inline int build_int_from_shorts(const uint16_t low, const uint16_t high) {
    return high << 16 | low;
}

/* JVM definitions */
typedef struct {
    const char *typeName;
    const char *fieldName;
    const char *typeString;
    int32_t isStatic;
    uint64_t offset;
    void *address;
} VMStructEntry;

typedef struct {
    const char *typeName;
    const char *superclassName;
    int32_t isOopType;
    int32_t isIntegerType;
    int32_t isUnsigned;
    uint64_t size;
} VMTypeEntry;

typedef struct {
    const char *name;
    int32_t value;
} VMIntConstantEntry;

typedef struct {
    const char *name;
    uint64_t value;
} VMLongConstantEntry;

/* AccessFlags */
enum {
    JVM_ACC_NOT_C2_COMPILABLE = 0x02000000,
    JVM_ACC_NOT_C1_COMPILABLE = 0x04000000,
    JVM_ACC_NOT_C2_OSR_COMPILABLE = 0x08000000
};

/* VTable Index */
enum VtableIndexFlag {
    itable_index_max = -10,
    pending_itable_index = -9,
    invalid_vtable_index = -4,
    garbage_vtable_index = -3,
    nonvirtual_vtable_index = -2
};

/* Wrappers */
class JVMWrappers {
public:
    typedef std::unordered_map<std::string, VMStructEntry *> struct_entry_t;
    typedef std::unordered_map<std::string, struct_entry_t> struct_entries_t;
    typedef std::unordered_map<std::string, VMTypeEntry *> type_entries_t;
    typedef std::unordered_map<std::string, VMIntConstantEntry *> int_entries_t;
    typedef std::unordered_map<std::string, VMLongConstantEntry *> long_entries_t;

private:
    static struct_entries_t struct_entries;
    static type_entries_t type_entries;
    static int_entries_t int_entries;
    static long_entries_t long_entries;

public:
    static void init(VMStructEntry *vmstructs, VMTypeEntry *vmtypes, VMIntConstantEntry *vmints,
                     VMLongConstantEntry *vmlongs);

    static std::optional<std::reference_wrapper<struct_entry_t> > find_type_fields(const char *typeName);

    static std::optional<VMTypeEntry *> find_type(const char *typeName);
};

class JVMWrapper {
public:
    // the following function will lookup the type in the
    // JVMWrappers. If it is found, return successful std::optional
    static std::optional<JVMWrapper> from_instance(const char *typeName, void *instance);

    template<typename T>
    std::optional<T *> get_field(const char *fieldName) {
        auto fieldAddress = find_field_address(fieldName);
        if (!fieldAddress.has_value())
            return std::nullopt;

        return static_cast<T *>(fieldAddress.value());
    }

    [[nodiscard]] void *get_instance() const {
        return this->instance;
    }

    [[nodiscard]] uint64_t size() const {
        return this->type_entry->size;
    }

private:
    VMTypeEntry *type_entry = nullptr;
    std::optional<std::reference_wrapper<JVMWrappers::struct_entry_t> > fields;
    void *instance = nullptr; // pointer to instantiated VM type

    std::optional<void *> find_field_address(const char *fieldName) {
        auto tbl = fields.value().get();
        const auto entry = tbl.find(fieldName);
        if (entry == tbl.end())
            return std::nullopt;

        const auto field = entry->second;
        void *fieldAddress;
        if (field->isStatic)
            fieldAddress = field->address;
        else
            fieldAddress = reinterpret_cast<void *>(reinterpret_cast<uint64_t>(this->instance) + field->offset);

        return fieldAddress;
    }
};

namespace global_offsets {
    inline uintptr_t klass_offset = 0;
}

#endif //JVM_INTERNAL_H
