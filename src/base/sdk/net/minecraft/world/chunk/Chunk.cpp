#include "Chunk.h"


//CChunk::CChunk(jobject instance)
//{
//	Java::AssignClass("net.minecraft.world.chunk.Chunk", StrayCache::chunk_class);
//	if (StrayCache::chunk_class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		StrayCache::chunk_class = StrayCache::chunk_class;
//	}
//	if (JNIHelper::IsForge()) {
//
//		StrayCache::chunk_getBlock ->GetMethodID(StrayCache::chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
//		return;
//	}
//
//	
//	StrayCache::chunk_getBlock ->GetMethodID(StrayCache::chunk_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
//	
//	this->Instance = instance;
//}

CBlock CChunk::getBlock(jint x, jint y, jint z, JNIEnv* env )
{
	return CBlock(env->CallObjectMethod(this->getInstance(), StrayCache::chunk_getBlock, x, y, z));
}
