#include "../menu.h"
#include "../../jvm/hook/JavaHook.h"
#include "../../sdk/StrayCache.h"
#include "../../sdk/net/minecraft/client/network/Packet.h"
#include "../../sdk/net/minecraft/client/network/NetworkManger.h"

void PrintClassName(jvmtiEnv* jvmti_env, jclass klass) {
	char* signature = NULL;
	char* generic = NULL;
	jvmtiError error = jvmti_env->GetClassSignature(klass, &signature, &generic);
	if (error != JVMTI_ERROR_NONE) {
		printf("Failed to get class signature\n");
		return;
	}

	printf("Class Signature: %s\n", signature);

	// ÊÍ·Å×Ö·û´®ÄÚ´æ
	jvmti_env->Deallocate((unsigned char*)signature);
}
static void channelRead0_callback(void* sp, bool* should_return, void* rbx, void* thread) {
	if (!Java::Env)return;
	JNIEnv* env = JavaHook::get_env_for_thread(thread);

}
static void sendPacket_callback(void* sp, bool* should_return, void* rbx, void* thread) {
	if (!Java::Env)return;
	JNIEnv* env = JavaHook::get_current_thread_env();
	std::cout << "sendPacket_callback" << std::endl;
	PrintClassName(Java::Jvmti, env->GetObjectClass(JavaHook::get_jobject_arg_at(sp, 0, thread, env)));
	PrintClassName(Java::Jvmti, env->GetObjectClass(JavaHook::get_jobject_arg_at(sp, 1, thread, env)));
	PrintClassName(Java::Jvmti, env->GetObjectClass(JavaHook::get_jobject_arg_at(sp, 2, thread, env)));
	PrintClassName(Java::Jvmti, env->GetObjectClass(JavaHook::get_jobject_arg_at(sp, 3, thread, env)));
	//CNetworkManager sendPacket(JavaHook::get_jobject_arg_at(sp, 3, thread), env);
	//CPacket packet(JavaHook::get_jobject_arg_at(sp, 0, thread), env);
}
void Menu::LoadAllGameHook()
{
	JavaHook::add_to_java_hook(StrayCache::networkManager_sendPacket, sendPacket_callback,StrayCache::networkManager_class);
	JavaHook::add_to_java_hook(StrayCache::networkManager_channelRead0, channelRead0_callback);
}

void Menu::RemoveAllGameHook()
{

}
