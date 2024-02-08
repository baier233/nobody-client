#pragma once
#include "AbstractModule.h"
#include <vector>

#define ToBaseModule(__MOD) reinterpret_cast<AbstractModule*>(__MOD)
#define ToDirectModule(__Impl, __Mod) reinterpret_cast<__Impl*>(__Mod)
typedef void *HMOD;

class ModuleManager {
private:
    std::vector<HMOD> modules;
    ModuleManager();

    ~ModuleManager() = default;

public:
    static ModuleManager &getInstance();

    template<class MODCLASS>
    void addModule(MODCLASS* mod);
     
    template<typename MODCLASS>
    MODCLASS *getModule(std::string name);

    void getModule(Category c, std::vector<HMOD> *out_module);

    void getModule(bool isenable, std::vector<HMOD> *out_module);

    AbstractModule* getModule(std::string name);

    void ProcessKeyEvent(int key);

    ModuleManager(ModuleManager &&) = delete;

    ModuleManager(const ModuleManager &) = delete;

    ModuleManager &operator=(const ModuleManager &) = delete;
    std::vector<HMOD> getMods();
    void clean() { modules.clear(); }
};

template<class MODCLASS>
void ModuleManager::addModule(MODCLASS* mod) {
    this->modules.push_back(reinterpret_cast<HMOD>(mod));
}

template<typename MODCLASS>
MODCLASS *ModuleManager::getModule(std::string name) {
    for (auto iter = this->modules.cbegin(); iter < this->modules.cend(); iter++) {
        if (::Utils::compareStringIgnoreCase(ToBaseModule(*iter)->getName(), name)) {
            return ToDirectModule(MODCLASS, *iter);
        }
    }
    return nullptr;
}
