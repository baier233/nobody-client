#include "WorldClient.h"

#include "../../../../sdk.h"
#include "../../../../../java/java.h"
#include "../../../../../util/logger.h"

//CWorldClient::CWorldClient()
//{
//	Java::GetInstance()->AssignClass("net.minecraft.client.multiplayer.WorldClient", this->Class);
//	Java::GetInstance()->AssignClass("net.minecraft.entity.player.EntityPlayer", this->EntityPlayer); // doing this because am lazy
//	if (this->EntityPlayer == nullptr)
//	{
//		if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//		this->EntityPlayer = StrayCache::GetInstance()->entityPlayer_class;
//	}
//	
//	if (this->Class == nullptr)
//	{
//		if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//		this->Class = StrayCache::GetInstance()->worldClient_class;
//	}
//
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["entityList"] = env->GetFieldID(this->Class, "field_73032_d", "Ljava/util/Set;");
//		return;
//	}
//	/*
//	if (JNIHelper::IsVanilla()) {
//		this->FieldIDs["entityList"] = env->GetFieldID(this->Class, "c ", "Ljava/util/Set;");
//		return;
//	}
//	*/
//	this->FieldIDs["entityList"] = env->GetFieldID(this->Class, "entityList", "Ljava/util/Set;");
//}
//
//jclass CWorldClient::getClass()
//{
//	return this->Class;
//}
//
//jobject CWorldClient::getInstance()
//{
//	return env->GetObjectField(SDK::GetInstance()->Minecraft->getInstance(), SDK::GetInstance()->Minecraft->FieldIDs["theWorld"]);
//}

Set CWorldClient::GetEntityList(JNIEnv* env )
{
	jfieldID targetField = StrayCache::GetInstance()->worldClient_entityList;

	jobject playerEntitiesList = env->GetObjectField(this->getInstance(), targetField);


	return Set(playerEntitiesList);
}

int CWorldClient::getIDFromBlock(jobject block, JNIEnv* env )
{
	if (this->getInstance() == NULL)return 0;
	int blockID = env->CallIntMethod(StrayCache::GetInstance()->blockPos_class, StrayCache::GetInstance()->block_getIdFromBlock, block);


	//env->DeleteLocalRef(block);
	//mc.env->DeleteLocalRef(blockName);
	return blockID;
}
