#pragma once
#include <cstdint>
#include <vector>
#include <wtypes.h>
#include <Psapi.h>
class Module
{
public:
	Module(const char* module_name);
	Module(HMODULE a_module);

	uint8_t* pattern_scan(uint8_t pattern[], int size, int access = PAGE_EXECUTE_READ) const;
	std::vector<uint8_t*> pattern_scan_all(uint8_t pattern[], int size, int access = PAGE_EXECUTE_READ) const;
	void* getProcAddress(const char* name);

	operator bool() const;
private:
	MODULEINFO moduleInfo{};
	HMODULE module = nullptr;
};
