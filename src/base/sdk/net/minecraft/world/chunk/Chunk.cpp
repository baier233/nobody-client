#include "Chunk.h"


//CChunk::CChunk(jobject instance)
//{
//	Java::GetInstance()->AssignClass("net.minecraft.world.chunk.Chunk", StrayCache::GetInstance()->chunk_class);
//	if (StrayCache::GetInstance()->chunk_class == nullptr)
//	{
//		if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//		StrayCache::GetInstance()->chunk_class = StrayCache::GetInstance()->chunk_class;
//	}
//	if (JNIHelper::IsForge()) {
//
//		StrayCache::GetInstance()->chunk_getBlock ->GetMethodID(StrayCache::GetInstance()->chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
//		return;
//	}
//
//	
//	StrayCache::GetInstance()->chunk_getBlock ->GetMethodID(StrayCache::GetInstance()->chunk_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
//	
//	this->Instance = instance;
//}

CBlock CChunk::getBlock(jint x, jint y, jint z, JNIEnv* env )
{
	return CBlock(env->CallObjectMethod(this->getInstance(), StrayCache::GetInstance()->chunk_getBlock, x, y, z));
}
