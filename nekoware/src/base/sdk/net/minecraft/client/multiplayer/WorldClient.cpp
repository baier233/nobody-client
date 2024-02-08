#include "WorldClient.h"

#include "../../../../sdk.h"
#include "../../../../../java/java.h"
#include "../../../../../util/logger.h"

//CWorldClient::CWorldClient()
//{
//	Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", this->Class);
//	Java::AssignClass("net.minecraft.entity.player.EntityPlayer", this->EntityPlayer); // doing this because am lazy
//	if (this->EntityPlayer == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		this->EntityPlayer = StrayCache::entityPlayer_class;
//	}
//	
//	if (this->Class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		this->Class = StrayCache::worldClient_class;
//	}
//
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["entityList"] = Java::Env->GetFieldID(this->Class, "field_73032_d", "Ljava/util/Set;");
//		return;
//	}
//	/*
//	if (JNIHelper::IsVanilla()) {
//		this->FieldIDs["entityList"] = Java::Env->GetFieldID(this->Class, "c ", "Ljava/util/Set;");
//		return;
//	}
//	*/
//	this->FieldIDs["entityList"] = Java::Env->GetFieldID(this->Class, "entityList", "Ljava/util/Set;");
//}
//
//jclass CWorldClient::getClass()
//{
//	return this->Class;
//}
//
//jobject CWorldClient::getInstance()
//{
//	return Java::Env->GetObjectField(SDK::Minecraft->getInstance(), SDK::Minecraft->FieldIDs["theWorld"]);
//}

Set CWorldClient::GetEntityList()
{
	jfieldID targetField = StrayCache::worldClient_entityList;

	jobject playerEntitiesList = Java::Env->GetObjectField(this->getInstance(), targetField);

	
	return Set(playerEntitiesList);
}

int CWorldClient::getIDFromBlock(jobject block)
{
	if (this->getInstance() == NULL)return 0;
	int blockID = Java::Env->CallIntMethod(StrayCache::blockPos_class, StrayCache::block_getIdFromBlock, block);


	//Java::Env->DeleteLocalRef(block);
	//mc.env->DeleteLocalRef(blockName);
	return blockID;
}
