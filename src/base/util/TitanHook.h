#pragma once
#include <Windows.h>
#include "../../../ext/detours/include/detours.h"

#pragma comment(lib, "detours.lib")

template <typename T>
class TitanHook {
public:
	void InitHook(void* targetFunc, void* myFunc) {
		hooked = false;
		targetFunc_ = targetFunc;
		myFunc_ = myFunc;
	}

	void SetHook() {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(LPVOID&)targetFunc_, myFunc_);
		DetourTransactionCommit();
		hooked = true;
	}

	T GetOrignalFunc() {
		return (T)targetFunc_;
	}

	void RemoveHook() {
		if (!hooked) return;
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(LPVOID&)targetFunc_, myFunc_);
		DetourTransactionCommit();
		hooked = false;
	}

	~TitanHook() {
		RemoveHook();
	}

private:
	bool hooked;
	void* targetFunc_;
	void* myFunc_;
};