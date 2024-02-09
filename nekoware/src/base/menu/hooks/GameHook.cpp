#include "../menu.h"
#include "../../jvm/hook/JavaHook.h"
#include "../../sdk/StrayCache.h"
#include "../../sdk/net/minecraft/client/network/Packet.h"
#include "../../sdk/net/minecraft/client/network/NetHandlerPlayClient.h"
#include "../../eventManager/EventManager.hpp"
#include "../../eventManager/events/EventPacketSend.h"
void PrintClassName(JNIEnv* env, jobject obj) {
	jclass cls = env->GetObjectClass(obj);
	if (cls == nullptr) {
		std::cerr << "Failed to get class object" << std::endl;
		return;
	}

	// 获取类名
	jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
	if (mid == nullptr) {
		std::cerr << "Failed to get getClass method" << std::endl;
		return;
	}

	jobject classObj = env->CallObjectMethod(obj, mid);
	if (classObj == nullptr) {
		std::cerr << "Failed to get class object" << std::endl;
		return;
	}

	jclass classCls = env->GetObjectClass(classObj);
	if (classCls == nullptr) {
		std::cerr << "Failed to get class object class" << std::endl;
		return;
	}

	jmethodID getNameMid = env->GetMethodID(classCls, "getName", "()Ljava/lang/String;");
	if (getNameMid == nullptr) {
		std::cerr << "Failed to get getName method" << std::endl;
		return;
	}

	jstring classNameStr = (jstring)env->CallObjectMethod(classObj, getNameMid);
	const char* className = env->GetStringUTFChars(classNameStr, nullptr);
	if (className == nullptr) {
		std::cerr << "Failed to get class name" << std::endl;
		return;
	}

	// 打印类名
	std::cout << "Class Name: " << className << std::endl;

	// 释放资源
	env->ReleaseStringUTFChars(classNameStr, className);
	env->DeleteLocalRef(classObj);
	env->DeleteLocalRef(cls);
}
static void channelRead0_callback(void* sp, bool* should_return, void* rbx, void* thread) {
	if (!Java::Env)return;
	JNIEnv* env = JavaHook::get_env_for_thread(thread);
	std::cout << "channelRead0_callback" << std::endl;
	PrintClassName(env, JavaHook::get_jobject_arg_at(sp, 1, thread, env));
	//CNetworkManager sendPacket(JavaHook::get_jobject_arg_at(sp, 3, thread), env);
	//CPacket packet(JavaHook::get_jobject_arg_at(sp, 0, thread), env);
}
static void addToSendQueue_callback(void* sp, bool* should_return, void* rbx, void* thread) {
	if (!Java::Env)return;
	JNIEnv* env = JavaHook::get_current_thread_env();
	CNetHandlerPlayClient sendQueue(JavaHook::get_jobject_arg_at(sp, 1, thread, env), env);
	CPacket packet(JavaHook::get_jobject_arg_at(sp, 0, thread, env), env);
	EventPacketSend e = EventPacketSend(env, packet);
	EventManager::getInstance().call(e);
	*should_return = (e.isCancel());
}
void Menu::LoadAllGameHook()
{
	//JavaHook::add_to_java_hook(StrayCache::netHandlerPlayClient_addToSendQueue, addToSendQueue_callback);
	//JavaHook::add_to_java_hook(StrayCache::networkManager_channelRead0, channelRead0_callback);
}

void Menu::RemoveAllGameHook()
{

}
