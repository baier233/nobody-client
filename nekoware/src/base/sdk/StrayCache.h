#pragma once
#include "JNIHelper.h"
#include "../util/logger.h"
#include "../base.h"

inline bool IsLunar = false;
struct StrayCache {


	inline static bool initialized;

	void helper() {
		//这个方法不会被调用，只是用来方便跳转到指定的方法
		Load112ForgeMap();
		Load189ForgeMap();
		Load189MCPMap();
		Load189VanillaMap();
		Load1710ForgeMap();
		Load112MCPMap();
	}


	//Minecraft Class
	inline static jclass minecraft_class;
	inline static jmethodID minecraft_getMinecraft;
	inline static jmethodID minecraft_getNetHandler;
	inline static jmethodID minecraft_getRenderViewEntity;
	inline static jmethodID minecraft_clickMouse;
	inline static jmethodID minecraft_getDebugFPS;
	inline static jfieldID minecraft_mc;
	inline static jfieldID minecraft_thePlayer;
	inline static jfieldID minecraft_theWorld;
	inline static jfieldID minecraft_playerController;
	inline static jfieldID minecraft_renderManager;
	inline static jfieldID minecraft_timer;
	inline static jfieldID minecraft_gameSettings;
	inline static jfieldID minecraft_ingameGUI;
	inline static jfieldID minecraft_currentScreen;
	inline static jfieldID minecraft_objectMouseOver;
	inline static jfieldID minecraft_rightClickDelayTimer;

	//ActiveRenderInfo Class
	inline static jclass activeRenderInfo_class;
	inline static jfieldID activeRenderInfo_VIEWPORT;
	inline static jfieldID activeRenderInfo_MODELVIEW;
	inline static jfieldID activeRenderInfo_PROJECTION;


	//Game Settings
	inline static jclass gamesettings_class;
	inline static jmethodID gamesettings_setOptionKeyBinding;
	inline static jfieldID gamesettings_thirdPersonView;
	inline static jfieldID gamesettings_fovSetting;
	inline static jfieldID gamesettings_gammaSetting;
	inline static jfieldID gamesettings_keyBindFullscreen;
	inline static jfieldID gamesettings_keyBindSneak;

	//CPacketPlayr Class
	inline static jclass cpacketPlayer_class;

	//KeyBind Class
	inline static jclass keybind_class;
	inline static jfieldID keybind_pressed;

	//NetHandlerPlayClient class
	inline static jclass netHandlerPlayClient_class;
	inline static jmethodID netHandlerPlayClient_getPlayerInfo;
	inline static jmethodID netHandlerPlayClient_addToSendQueue;


	//GuiIngame class
	inline static jclass guiIngame_class;
	inline static jmethodID guiIngame_getTabList;

	//GuiPlayerTabOverlay class
	inline static jclass guiPlayerTabOverlay_class;
	inline static jmethodID guiPlayerTabOverlay_getPlayerName;

	//PlayerController Class
	inline static jclass playerControllerMP_class;
	inline static jmethodID playerControllerMP_attackEntity;
	inline static jmethodID playerControllerMP_sendUseItem;

	//NetworkManager Class
	inline static jclass networkManager_class;
	inline static jmethodID networkManager_sendPacket;
	inline static jmethodID networkManager_channelRead0;

	// ENTITY CLASS
	inline static jclass entity_class;
	inline static jmethodID entity_getName;
	inline static jmethodID entity_isSneaking;
	inline static jmethodID entity_setSneaking;
	inline static jmethodID entity_setPosition;
	inline static jmethodID entity_setSprint;
	inline static jmethodID entity_isInvisible;
	inline static jmethodID entity_inWater;
	inline static jmethodID entity_getUniqueID;
	inline static jfieldID entity_posX;
	inline static jfieldID entity_posY;
	inline static jfieldID entity_posZ;
	inline static jfieldID entity_lastTickPosX;
	inline static jfieldID entity_lastTickPosY;
	inline static jfieldID entity_lastTickPosZ;
	inline static jfieldID entity_width;
	inline static jfieldID entity_height;
	inline static jfieldID entity_distanceWalkedModified;
	inline static jfieldID entity_prevDistanceWalkedModified;
	inline static jfieldID entity_rotationYaw;
	inline static jfieldID entity_rotationPitch;
	inline static jfieldID entity_prevRotationYaw;
	inline static jfieldID entity_prevRotationPitch;
	inline static jfieldID entity_boundingBox;
	inline static jfieldID entity_motionX;
	inline static jfieldID entity_motionY;
	inline static jfieldID entity_motionZ;
	inline static jfieldID entity_onGround;
	inline static jfieldID entity_fallDistance;
	inline static jfieldID entity_ticksExisted;
	inline static jfieldID entity_isDead;

	// ENTITY LIVING BASE CLASS
	inline static jclass entityLivingBase_class;
	inline static jmethodID entityLivingBase_getHealth;
	inline static jmethodID entityLivingBase_getMaxHealth;
	inline static jmethodID entityLivingBase_canEntityBeSeen;
	inline static jmethodID entityLivingBase_isPlayerSleeping;
	inline static jmethodID entityLivingBase_swingItem;
	inline static jmethodID entityLivingBase_jump;
	inline static jfieldID entityLivingBase_hurttime;
	inline static jfieldID entityLivingBase_moveForward;
	inline static jfieldID entityLivingBase_moveStrafe;

	//Entity Player
	inline static jclass entityPlayer_class;
	inline static jmethodID entityPlayer_isBlocking;
	inline static jfieldID entityPlayer_inventory;


	//Entity Player SP
	inline static jclass entityPlayerSP_class;
	inline static jfieldID entityPlayerSP_sendQueue;
	inline static jfieldID entityPlayerSP_abilities;

	//World Client
	inline static jclass worldClient_class;
	inline static jfieldID worldClient_entityList;

	//RenderManager
	inline static jclass renderManager_class;
	inline static jfieldID renderManager_renderPosX;
	inline static jfieldID renderManager_renderPosY;
	inline static jfieldID renderManager_renderPosZ;
	inline static jfieldID renderManager_viewerPosX;
	inline static jfieldID renderManager_viewerPosY;
	inline static jfieldID renderManager_viewerPosZ;
	inline static jfieldID renderManager_playerViewX;
	inline static jfieldID renderManager_playerViewY;

	//Timer
	inline static jclass timer_class;
	inline static jfieldID timer_renderPartialTicks;
	inline static jfieldID timer_timerSpeed;


	//World
	inline static jclass world_class;
	inline static jmethodID world_getBlockState;
	inline static jmethodID world_rayTraceBlocks;
	inline static jmethodID world_getChunkFromChunkCoords;
	inline static jmethodID world_isAirBlock;
	inline static jfieldID world_playerEntities;
	inline static jfieldID world_loadedEntityList;//TODO:其他版本

	//Chunk
	inline static jclass chunk_class;
	inline static jmethodID chunk_getBlock;

	//collection
	inline static jclass conllection_class;
	inline static jmethodID conllection_toArray;

	//Set
	inline static jclass set_class;
	inline static jmethodID set_toArray;

	//List
	inline static jclass list_class;
	inline static jmethodID list_toArray;

	//FloatBuffer
	inline static jclass floatBuffer_class;
	inline static jmethodID floatBuffer_get;

	//IntBuffer
	inline static jclass intBuffer_class;
	inline static jmethodID intBuffer_get;


	//String class
	inline static jclass string_class;
	inline static jmethodID string_contains;

	//System class
	inline static jclass system_class;
	inline static jmethodID system_gc;

	// AXIS ALIGNED BB CLASS
	inline static jclass axisAlignedBB_class;
	inline static jfieldID axisAlignedBB_minX;
	inline static jfieldID axisAlignedBB_minY;
	inline static jfieldID axisAlignedBB_minZ;
	inline static jfieldID axisAlignedBB_maxX;
	inline static jfieldID axisAlignedBB_maxY;
	inline static jfieldID axisAlignedBB_maxZ;

	// MOVING OBJECT POSITION CLASS
	inline static jclass movingObjectPosition_class;
	inline static jfieldID movingObjectPosition_hitVec;
	inline static jfieldID movingObjectPosition_typeOfHit;
	inline static jfieldID movingObjectPosition_blockPos;

	inline static jclass vec3_class;
	inline static jfieldID vec3_xCoord;
	inline static jfieldID vec3_yCoord;
	inline static jfieldID vec3_zCoord;

	inline static jclass inventoryPlayer_class;
	inline static jmethodID inventoryPlayer_getCurrentItem;
	inline static jmethodID inventoryPlayer_getStackInSlot;
	inline static jfieldID inventoryPlayer_mainInv;
	inline static jfieldID inventoryPlayer_armorInv;
	inline static jfieldID inventoryPlayer_currentItem;

	inline static jclass itemStack_class;
	inline static jmethodID itemStack_getItem;
	inline static jmethodID itemStack_getStrVsBlock;

	inline static jclass blockPos_class;
	inline static jfieldID blockPos_x;
	inline static jfieldID blockPos_y;
	inline static jfieldID blockPos_z;
	inline static jmethodID blockPos_constructor;
	inline static jmethodID blockPos_constructorI;

	//Block Class
	inline static jclass block_class;
	inline static jmethodID block_getIdFromBlock;

	//BlockState Class
	inline static jclass blockState_class;
	inline static jfieldID blockState_block;

	//IBlockState Class
	inline static jclass iBlockState_class;
	inline static jmethodID iBlockState_getBlock;
	inline static jmethodID iBlockState_getBlockFromBlockState;

	//BlockAir Clss
	inline static jclass blockAir_class;

	//Item Class
	inline static jclass item_class;
	inline static jmethodID item_getIdFromItem;

	//ItemArmor Class
	inline static jclass itemArmor_Class;
	inline static jmethodID itemArmor_getColor;

	//ItemTool Class
	inline static jclass itemTool_class;
	inline static jmethodID itemTool_getStrVsBlock;

	//NonNullList Class
	inline static jclass nonNullList_class;
	inline static jfieldID nonNullList_List;

	//EntityItem Class
	inline static jclass entityItem_class;

	

	static void Load189VanillaMap() {
		{
			Java::AssignClass("ave", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);
			Logger::Init();

			jint count;
			jfieldID* fields;

			Java::Jvmti->GetClassFields(minecraft_class, &count, &fields);
			for (int i = 0; i < count; i++)
			{
				char* sign;
				char* name;
				Java::Jvmti->GetFieldName(minecraft_class, fields[i], &name, &sign, 0);

				std::cout << "Desc:" << sign << " Name:" << name << std::endl;
				if (std::string(sign).find("avh") != -1)
				{
					std::cout << "find1" << std::endl;
					minecraft_gameSettings = fields[i];
				}
			}
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "A", "()Lave;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "ac", "()Lpk;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "aw", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "ai", "()I");

			minecraft_mc = Java::Env->GetStaticFieldID(minecraft_class, "S", "Lave;");
			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "h", "Lbew;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "f", "Lbdb;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "c", "Lbda;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "aa", "Lbiu;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "Y", "Lavl;");

			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "m", "Laxu;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "s", "Lauh;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "ap", "I");

		}

		{
			Java::AssignClass("avh", gamesettings_class);
			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "a", "(Lavb;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(gamesettings_class, "aB", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(gamesettings_class, "aI", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(gamesettings_class, "aJ", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(gamesettings_class, "aq", "Lavb;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "ad", "Lavb;");

		}

		{
			Java::AssignClass("bhw", keybind_class);
			keybind_pressed = Java::Env->GetFieldID(keybind_class, "i", "Z");
		}


		{
			Java::AssignClass("bcy", netHandlerPlayClient_class);
			netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

			netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "a", "(Ljava/util/UUID;)Lbdc;");
			netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "a", "(Lff;)V");

		}

		{
			Java::AssignClass("avo", guiIngame_class);
			guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

			guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "h", "()Lawh;");
		}

		{
			Java::AssignClass("awh", guiPlayerTabOverlay_class);
			guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

			guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "a", "(Lbdc;)Ljava/lang/String;");
		}



		{
			Java::AssignClass("pk", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			{
				jint count;
				jfieldID* fields;

				Java::Jvmti->GetClassFields(entity_class, &count, &fields);

				for (int i = 0; i < count; i++)
				{
					char* sign;
					char* name;
					Java::Jvmti->GetFieldName(entity_class, fields[i], &name, &sign, 0);

					std::cout << "Desc:" << sign << " Name:" << name << std::endl;
					if (std::string(name).find("NaC") != -1)
					{
						std::cout << "find" << std::endl;
						//entity_ticksExisted = fields[i];
					}
				}
			}


			entity_getName = Java::Env->GetMethodID(entity_class, "e_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "av", "()Z");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "c", "(Z)V");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "b", "(DDD)V");
			entity_setSprint = Java::Env->GetMethodID(entity_class, "d", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "ax", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "V", "()Z");
			entity_getUniqueID = Java::Env->GetMethodID(entity_class, "aK", "()Ljava/util/UUID;");
			entity_posX = Java::Env->GetFieldID(entity_class, "s", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "t", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "u", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "P", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "Q", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "R", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "J", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "K", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "M", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "L", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "y", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "z", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "A", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "B", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "f", "Laug;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "v", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "w", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "x", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "C", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "O", "F");
			if (entity_ticksExisted == nullptr)
			{
				entity_ticksExisted = Java::Env->GetFieldID(entity_class, "W", "I");
			}
			//entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "I", "Z");

		}

		{

			Java::AssignClass("bda", playerControllerMP_class);
			playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "a", "(Lwn;Lpk;)V");
			playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "a", "(Lwn;Ladm;Lzx;)Z");
		}


		{
			Java::AssignClass("pr", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "bn", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "bu", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "t", "(Lpk;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "bJ", "()Z");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "bw", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "bF", "()V");

			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "au", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "ba", "F");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "aZ", "F");

		}

		{
			Java::AssignClass("wn", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

			entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "bW", "()Z");

			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "bi", "Lwm;");
		}

		{
			Java::AssignClass("bew", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);

			entityPlayerSP_sendQueue = Java::Env->GetFieldID(entityPlayerSP_class, "bew", "Lbcy;");
		}

		{
			Java::AssignClass("auz", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);

			activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "a", "Ljava/nio/IntBuffer;");
			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "c", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "b", "Ljava/nio/FloatBuffer;");
		}

		{
			Java::AssignClass("biu", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);

			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "o", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "p", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "q", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "h", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "i", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "j", "D");
		}

		{
			Java::AssignClass("bdb", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "c", "Ljava/util/Set;");

		}

		{
			Java::AssignClass("adm", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "a", "(Laui;Laui;ZZZ)Lauh;");
			world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "p", "(Lcj;)Lalz;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "d", "(Lcj;)Z");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "a", "(II)Lamy;");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "j", "Ljava/util/List;");
			world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "f", "Ljava/util/List;");
		}

		{
			Java::AssignClass("amy", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "a", "(III)Lafh;");
		}

		{
			Java::AssignClass("avl", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "d", "F");
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "c", "F");

		}

		{
			Java::AssignClass("aug", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "f", "D");
		}

		{
			Java::AssignClass("auh", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "c", "Laui;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "a", "Lauh$a;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "e", "Lcj;");
		}

		{
			Java::AssignClass("aui", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);
			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "c", "D");
		}

		{
			Java::AssignClass("wm", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "h", "()Lzx;");
			inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "a", "(I)Lzx;");

			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "a", "[Lzx;");
			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "b", "[Lzx;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "c", "I");
		}

		{
			Java::AssignClass("zx", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "b", "()Lzw;");
			itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "a", "(Lafh;)F");
		}

		{
			Java::AssignClass("zw", item_class);

			item_class = (jclass)Java::Env->NewGlobalRef(item_class);
			item_getIdFromItem = Java::Env->GetMethodID(item_class, "b", "(Lzw;)I");
		}

		{
			Java::AssignClass("yj", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "b", "(Lzx;)I");
		}

		{
			Java::AssignClass("za", itemTool_class);
			itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

			itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "a", "(Lzx;Lafh;)F ");
		}

		{
			Java::AssignClass("cj", blockPos_class);
			blockPos_class = (jclass)Java::Env->NewGlobalRef(blockPos_class);
			blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
			blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "a", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "c", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "d", "I");
		}

		{
			Java::AssignClass("afh", block_class);
			block_class = (jclass)Java::Env->NewGlobalRef(block_class);

			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "a", "(Lafh;)I");
		}

		{
			Java::AssignClass("ama", blockState_class);
			blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

			blockState_block = Java::Env->GetFieldID(blockState_class, "c", "Lafh;");

		}

		{
			Java::AssignClass("alz", iBlockState_class);
			iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "c", "()Lafh;");
			//iBlockState_getBlockFromBlockState = Java::Env->GetMethodID(iBlockState_class, "c", "()Lafh;");

		}

		{
			Java::AssignClass("aey", blockAir_class);
			blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
		}

		{
			Java::AssignClass("uz", entityItem_class);
			entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
		}

	}

	static void Load189ForgeMap() {
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);
			if (!Logger::Initialized)
				Logger::Init();


			jint count;
			jfieldID* fields;

			Java::Jvmti->GetClassFields(minecraft_class, &count, &fields);
			for (int i = 0; i < count; i++)
			{
				char* sign;
				char* name;
				Java::Jvmti->GetFieldName(minecraft_class, fields[i], &name, &sign, 0);

				//std::cout << "Desc:" << sign << " Name:" << name << std::endl;

				if (std::string(sign).find("GameSettings") != -1)
				{
					std::cout << "GameSettings" << std::endl;
					minecraft_gameSettings = fields[i];
				}

				if (std::string(sign).find("GuiIngame") != -1)
				{
					std::cout << "GuiIngame" << std::endl;
					minecraft_ingameGUI = fields[i];
				}

				//if (std::string(sign).find("net/minecraft/client/network/NetHandlerPlayClient") != -1)
				//{
				//	std::cout << "NetworkManager: " << name << std::endl;
				//	//minecraft_netManager = fields[i];
				//}

			}
			minecraft_getNetHandler = Java::Env->GetMethodID(minecraft_class, "func_147114_u", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "func_147116_af", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "func_175610_ah", "()I");

			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");

			if (minecraft_gameSettings == nullptr)
			{
				minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
			}

			if (minecraft_ingameGUI == nullptr)
			{
				minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "field_71456_v", "Lnet/minecraft/client/gui/GuiIngame;");
			}

			/*if (minecraft_netManager == nullptr)
			{
				minecraft_netManager = Java::Env->GetFieldID(minecraft_class, "field_147302_e", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
				std::cout << "netManager: " << minecraft_netManager << std::endl;
			}*/
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "field_71467_ac", "I");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
			gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74320_O", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74334_X", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74333_Y", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");

		}

		{
			Java::AssignClass("net.minecraft.network.NetworkManager", networkManager_class);
			networkManager_class = (jclass)Java::Env->NewGlobalRef(networkManager_class);
			networkManager_sendPacket = Java::Env->GetMethodID(networkManager_class, "func_179288_a", "(Lnet/minecraft/network/Packet;Lio/netty/util/concurrent/GenericFutureListener;[Lio/netty/util/concurrent/GenericFutureListener;)V");
			networkManager_channelRead0 = Java::Env->GetMethodID(networkManager_class, "channelRead0", "(Lio/netty/channel/ChannelHandlerContext;Lnet/minecraft/network/Packet;)V");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
			keybind_pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");
		}

		{
			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

			netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "func_175102_a", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");
			netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "func_147297_a", "(Lnet/minecraft/network/Packet;)V");

		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
			guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

			guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "func_175181_h", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
		}


		{
			Java::AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
			guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

			guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "func_175243_a", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
		}


		{
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			{
				jint count;
				jfieldID* fields;

				Java::Jvmti->GetClassFields(entity_class, &count, &fields);

				for (int i = 0; i < count; i++)
				{
					char* sign;
					char* name;
					Java::Jvmti->GetFieldName(entity_class, fields[i], &name, &sign, 0);

					//std::cout << "Desc:" << sign << " Name:" << name << std::endl;
					if (std::string(name).find("NaC") != -1)
					{
						//std::cout << "find" << std::endl;
						//entity_ticksExisted = fields[i];
					}
				}
			}


			entity_getName = Java::Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "func_70093_af", "()Z");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "func_70095_a", "(Z)V");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "func_70107_b", "(DDD)V");
			entity_setSprint = Java::Env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "func_82150_aj", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "func_70090_H", "()Z");
			entity_getUniqueID = Java::Env->GetMethodID(entity_class, "func_110124_au", "()Ljava/util/UUID;");

			entity_posX = Java::Env->GetFieldID(entity_class, "field_70165_t", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "field_70163_u", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "field_70161_v", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "field_70142_S", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "field_70137_T", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "field_70136_U", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "field_70130_N", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "field_70131_O", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70140_Q", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70141_P", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "field_70177_z", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "field_70125_A", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "field_70126_B", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "field_70127_C", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "field_70159_w", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "field_70181_x", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "field_70179_y", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "field_70122_E", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "field_70143_R", "F");
			if (entity_ticksExisted == nullptr)
			{
				entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "I");
			}
			//entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "field_70128_L", "Z");

		}

		{
			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
			playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		}

		{
			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "func_70608_bn", "()Z");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "func_70664_aZ", "()V");

			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "field_70737_aN", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "field_70701_bs", "F");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");

		}

		{
			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

			entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "func_70632_aY", "()Z");

			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
		}

		{
			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);

			entityPlayerSP_sendQueue = Java::Env->GetFieldID(entityPlayerSP_class, "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
		}



		{
			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
			activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178814_a", "Ljava/nio/IntBuffer;");
			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178813_c", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178812_b", "Ljava/nio/FloatBuffer;");
		}


		{
			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);

			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "field_78725_b", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "field_78726_c", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "field_78723_d", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "field_78730_l", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "field_78731_m", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "field_78728_n", "D");
			renderManager_playerViewX = Java::Env->GetFieldID(renderManager_class, "field_78732_j", "D");
			renderManager_playerViewY = Java::Env->GetFieldID(renderManager_class, "field_78735_i", "D");
		}


		{
			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");

		}

		{
			Java::AssignClass("net.minecraft.world.World", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
			world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "func_180495_p", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "field_73010_i", "Ljava/util/List;");
			world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "field_72996_f", "Ljava/util/List;");
		}

		{
			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
		}



		{
			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "field_74278_d", "F");
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "field_74281_c", "F");

		}


		{
			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
		}

		{
			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/Vec3;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/util/BlockPos;");
		}

		{
			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "field_72450_a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "field_72448_b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "field_72449_c", "D");
		}



		{
			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "func_70301_a", "(I)Lnet/minecraft/item/ItemStack;");


			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70462_a", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70460_b", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
			itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "func_150997_a", "(Lnet/minecraft/block/Block;)F");
		}



		{
			Java::AssignClass("net.minecraft.item.Item", item_class);

			item_class = (jclass)Java::Env->NewGlobalRef(item_class);
			item_getIdFromItem = Java::Env->GetMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "func_82814_b", "(Lnet/minecraft/item/ItemStack;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemTool", itemTool_class);
			itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

			itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "func_150893_a", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/Block;)F");
		}

		{
			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_class = (jclass)Java::Env->NewGlobalRef(blockPos_class);
			blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
			blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "field_177962_a", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "field_177960_b", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "field_177961_c", "I");
		}

		{
			Java::AssignClass("net.minecraft.block.Block", block_class);
			block_class = (jclass)Java::Env->NewGlobalRef(block_class);

			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
		}

		{
			Java::AssignClass("net.minecraft.block.state.BlockState", blockState_class);
			blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

			blockState_block = Java::Env->GetFieldID(blockState_class, "field_177627_c", "Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "func_177230_c", "()Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.BlockAir", blockAir_class);
			blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
		}

		{
			Java::AssignClass("net.minecraft.entity.item.EntityItem", entityItem_class);
			entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
		}

	}

	static void Load189MCPMap() {
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

			minecraft_getNetHandler = Java::Env->GetMethodID(minecraft_class, "getNetHandler", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "clickMouse", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "getDebugFPS", "()I");

			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
			minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
			if (minecraft_ingameGUI == nullptr)
			{
				minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "ingameGUI", "Lnet/minecraft/client/gui/GuiIngame;");
			}
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "rightClickDelayTimer", "I");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
			gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "thirdPersonView", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "fovSetting", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "gammaSetting", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");

		}

		{
			Java::AssignClass("net.minecraft.network.NetworkManager", networkManager_class);
			networkManager_class = (jclass)Java::Env->NewGlobalRef(networkManager_class);
			networkManager_sendPacket = Java::Env->GetMethodID(networkManager_class, "sendPacket", "(Lnet/minecraft/network/Packet;Lio/netty/util/concurrent/GenericFutureListener;[Lio/netty/util/concurrent/GenericFutureListener;)V");
			networkManager_channelRead0 = Java::Env->GetMethodID(networkManager_class, "channelRead0", "(Lio/netty/channel/ChannelHandlerContext;Lnet/minecraft/network/Packet;)V");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
			keybind_pressed = Java::Env->GetFieldID(keybind_class, "pressed", "Z");
		}
		{
			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

			netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "getPlayerInfo", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");

			netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
			guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

			guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "getTabList", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
			guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

			guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "getPlayerName", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
		}

		{
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			entity_getName = Java::Env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "isSneaking", "()Z");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "setPosition", "(DDD)V");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "setSneaking", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "isInvisible", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "inWater", "()Z");
			entity_getUniqueID = Java::Env->GetMethodID(entity_class, "getUniqueID", "()Ljava/util/UUID;");

			entity_posX = Java::Env->GetFieldID(entity_class, "posX", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "posY", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "posZ", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "lastTickPosX", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "lastTickPosY", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "lastTickPosZ", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "width", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "height", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "distanceWalkedModified", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "rotationYaw", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "rotationPitch", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "prevRotationYaw", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "prevRotationPitch", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "motionX", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "motionY", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "motionZ", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "onGround", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "fallDistance", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "isDead", "Z");
			entity_ticksExisted = Java::Env->GetFieldID(entity_class, "ticksExisted", "F");

		}

		{
			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
			playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "sendUseItem", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		}

		{
			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "isPlayerSleeping", "()Z");
			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "hurtTime", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "moveForward", "I");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "moveStrafing", "I");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "jump", "()V");
		}



		{
			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

			entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "isBlocking", "()Z");

			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
		}

		{
			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
		}





		{
			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
			activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "VIEWPORT", "Ljava/nio/IntBuffer;");
			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "PROJECTION", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
		}


		{
			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);


			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "renderPosX", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "renderPosY", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "renderPosZ", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "viewerPosX", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "viewerPosY", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "viewerPosZ", "D");
		}


		{
			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");
		}

		{
			Java::AssignClass("net.minecraft.world.World", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "getChunkFromChunkCoords", "(II)Lnet/minecraft/world/chunk/Chunk;");
			world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "getBlockState", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "isAirBlock", "(Lnet/minecraft/util/BlockPos;)Z");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "playerEntities", "Ljava/util/List;");
			world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "loadedEntityList", "Ljava/util/List;");
		}


		{
			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
		}



		{
			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "timerSpeed", "F");
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "renderPartialTicks", "F");

		}

		{
			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "minX", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "minY", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "minZ", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "maxX", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "maxY", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "maxZ", "D");
		}

		{
			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/Vec3;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "blockPos", "Lnet/minecraft/util/BlockPos;");
		}


		{
			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "xCoord", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "yCoord", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "zCoord", "D");
		}


		{
			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "getStackInSlot", "(I)Lnet/minecraft/item/ItemStack;");

			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "mainInventory", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "armorInventory", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "currentItem", "I");

		}

		{
			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
			itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "getStrVsBlock", "(Lnet/minecraft/block/Block;)F");
		}
		{
			Java::AssignClass("net.minecraft.item.Item", item_class);
			item_class = (jclass)Java::Env->NewGlobalRef(item_class);

			item_getIdFromItem = Java::Env->GetMethodID(item_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "getColor", "(Lnet/minecraft/item/ItemStack;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemTool", itemTool_class);
			itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

			itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "getStrVsBlock", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/Block;)F");
		}


		{
			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
			blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "x", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "y", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "z", "I");
		}

		{
			Java::AssignClass("net.minecraft.block.Block", block_class);
			block_class = (jclass)Java::Env->NewGlobalRef(block_class);

			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "getIdFromBlock", "(Lnet/minecraft/block/Block;)I");
		}

		{
			Java::AssignClass("net.minecraft.block.state.BlockState", blockState_class);
			blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

			blockState_block = Java::Env->GetFieldID(blockState_class, "block", "Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "getBlock", "()Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.BlockAir", blockAir_class);
			blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
		}
	}

	static void Load112MCPMap() {
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

			minecraft_getNetHandler = Java::Env->GetMethodID(minecraft_class, "getConnection", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "clickMouse", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "getDebugFPS", "()I");

			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "player", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "world", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
			minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
			minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "ingameGUI", "Lnet/minecraft/client/gui/GuiIngame;");
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/math/RayTraceResult;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "rightClickDelayTimer", "I");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
			gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "thirdPersonView", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "fovSetting", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "gammaSetting", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");

		}
		{
			Java::AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
			keybind_pressed = Java::Env->GetFieldID(keybind_class, "pressed", "Z");
		}
		{
			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

			netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "getPlayerInfo", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");

			netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
			guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

			guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "getTabList", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
			guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

			guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "getPlayerName", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
		}

		{
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			entity_getName = Java::Env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "isSneaking", "()Z");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "setPosition", "(DDD)V");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "setSneaking", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "isInvisible", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "isInWater", "()Z");
			entity_getUniqueID = Java::Env->GetMethodID(entity_class, "getUniqueID", "()Ljava/util/UUID;");

			entity_posX = Java::Env->GetFieldID(entity_class, "posX", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "posY", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "posZ", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "lastTickPosX", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "lastTickPosY", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "lastTickPosZ", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "width", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "height", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "distanceWalkedModified", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "rotationYaw", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "rotationPitch", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "prevRotationYaw", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "prevRotationPitch", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/math/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "motionX", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "motionY", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "motionZ", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "onGround", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "fallDistance", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "isDead", "Z");
			entity_ticksExisted = Java::Env->GetFieldID(entity_class, "ticksExisted", "I");//nullptr

		}

		{
			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
			playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "sendUseItem", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");//nullptr
		}

		{
			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "isPlayerSleeping", "()Z");
			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "hurtTime", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "moveForward", "F"); 
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "moveStrafing", "F");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");//nullptr
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "jump", "()V");
		}



		{
			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

			entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "getItemInUseCount", "()I");//nullptr

			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
		}

		{
			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
		}

		{
			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
			activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "VIEWPORT", "Ljava/nio/IntBuffer;");
			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "PROJECTION", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
		}


		{
			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);


			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "renderPosX", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "renderPosY", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "renderPosZ", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "viewerPosX", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "viewerPosY", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "viewerPosZ", "D");
		}


		{
			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");
		}

		{
			Java::AssignClass("net.minecraft.world.World", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "rayTraceBlocks", "(Lnet/minecraft/util/math/Vec3d;Lnet/minecraft/util/math/Vec3d;ZZZ)Lnet/minecraft/util/math/RayTraceResult;");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "getChunkFromChunkCoords", "(II)Lnet/minecraft/world/chunk/Chunk;");//nullptr
			world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "getBlockState", "(Lnet/minecraft/util/math/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "isAirBlock", "(Lnet/minecraft/util/math/BlockPos;)Z");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "playerEntities", "Ljava/util/List;");
			world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "loadedEntityList", "Ljava/util/List;");
		}


		{
			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			//chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
		}

		{
			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "tickLength", "F");
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "renderPartialTicks", "F");

		}

		{
			Java::AssignClass("net.minecraft.util.math.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "minX", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "minY", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "minZ", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "maxX", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "maxY", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "maxZ", "D");
		}

		{
			Java::AssignClass("net.minecraft.util.math.RayTraceResult", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/math/Vec3d;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/math/RayTraceResult$Type;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "blockPos", "Lnet/minecraft/util/math/BlockPos;");
		}


		{
			Java::AssignClass("net.minecraft.util.math.Vec3d", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

			//nullptr below 3 fields
			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "xCoord", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "yCoord", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "zCoord", "D");
		}


		{
			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "getStackInSlot", "(I)Lnet/minecraft/item/ItemStack;");

			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "mainInventory", "Lnet/minecraft/util/NonNullList;");

			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "armorInventory", "Lnet/minecraft/util/NonNullList;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "currentItem", "I");

		}

		{
			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
			itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "getDestroySpeed", "(Lnet/minecraft/block/state/IBlockState;)F");
		}
		{
			Java::AssignClass("net.minecraft.item.Item", item_class);
			item_class = (jclass)Java::Env->NewGlobalRef(item_class);

			item_getIdFromItem = Java::Env->GetMethodID(item_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I"); // nullptr
		}

		{
			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "getColor", "(Lnet/minecraft/item/ItemStack;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemTool", itemTool_class);
			itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

			itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "getDestroySpeed", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/state/IBlockState;)F");
		}


		{
			Java::AssignClass("net.minecraft.util.math.BlockPos", blockPos_class);
			blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
			blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "x", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "y", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "z", "I");
		}

		{
			Java::AssignClass("net.minecraft.block.Block", block_class);
			block_class = (jclass)Java::Env->NewGlobalRef(block_class);

			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "getIdFromBlock", "(Lnet/minecraft/block/Block;)I");
		}

		{
			Java::AssignClass("net.minecraft.block.state.BlockStateContainer", blockState_class);
			blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

			blockState_block = Java::Env->GetFieldID(blockState_class, "block", "Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "getBlock", "()Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.BlockAir", blockAir_class);
			blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
		}

		{
			Java::AssignClass("net.minecraft.entity.item.EntityItem", entityItem_class);
			entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
		}


		{
			Java::AssignClass("net.minecraft.util.NonNullList", nonNullList_class);
			nonNullList_class = (jclass)Java::Env->NewGlobalRef(nonNullList_class);

			nonNullList_List = Java::Env->GetFieldID(nonNullList_class, "delegate", "Ljava/util/List;");

		}
	}

	static void Load112ForgeMap() {
		std::cout << "1.12.2 Forge" << std::endl;
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

			if (!Logger::Initialized)
				Logger::Init();

			jint count;
			jfieldID* fields;

			Java::Jvmti->GetClassFields(minecraft_class, &count, &fields);
			for (int i = 0; i < count; i++)
			{
				char* sign;
				char* name;
				Java::Jvmti->GetFieldName(minecraft_class, fields[i], &name, &sign, 0);

				//std::cout << "Desc:" << sign << " Name:" << name << std::endl;
				if (std::string(sign).find("GameSettings") != -1)
				{
					std::cout << "GameSettings" << std::endl;
					minecraft_gameSettings = fields[i];
				}

				if (std::string(sign).find("GuiIngame") != -1)
				{
					std::cout << "GuiIngame" << std::endl;
					minecraft_ingameGUI = fields[i];
				}

				//if (std::string(sign).find("net/minecraft/client/network/NetHandlerPlayClient") != -1)
				//{
				//	std::cout << "NetworkManager: " << name << std::endl;
				//	//minecraft_netManager = fields[i];
				//}

			}
			minecraft_getNetHandler = Java::Env->GetMethodID(minecraft_class, "func_147114_u", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "func_147116_af", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "func_175610_ah", "()I");

			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");

			if (minecraft_gameSettings == nullptr)
			{
				minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
			}

			if (minecraft_ingameGUI == nullptr)
			{
				minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "field_71456_v", "Lnet/minecraft/client/gui/GuiIngame;");
			}

			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/math/RayTraceResult;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "field_71467_ac", "I");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
			gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74320_O", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74334_X", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74333_Y", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
			keybind_pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");
		}

		{
			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

			netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "func_175102_a", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");

			netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");

		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
			guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

			guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "func_175181_h", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
			guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

			guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "func_175243_a", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
		}

		{
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			{
				jint count;
				jfieldID* fields;

				Java::Jvmti->GetClassFields(entity_class, &count, &fields);

				for (int i = 0; i < count; i++)
				{
					char* sign;
					char* name;
					Java::Jvmti->GetFieldName(entity_class, fields[i], &name, &sign, 0);

					//std::cout << "Desc:" << sign << " Name:" << name << std::endl;
					if (std::string(name).find("NaC") != -1)
					{
						//std::cout << "find" << std::endl;
						//entity_ticksExisted = fields[i];
					}
				}
			}


			entity_getName = Java::Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "func_70093_af", "()Z");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "func_70095_a", "(Z)V");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "func_70107_b", "(DDD)V");
			entity_setSprint = Java::Env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "func_82150_aj", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "func_70090_H", "()Z");
			entity_getUniqueID = Java::Env->GetMethodID(entity_class, "func_110124_au", "()Ljava/util/UUID;");

			entity_posX = Java::Env->GetFieldID(entity_class, "field_70165_t", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "field_70163_u", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "field_70161_v", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "field_70142_S", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "field_70137_T", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "field_70136_U", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "field_70130_N", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "field_70131_O", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70140_Q", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70141_P", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "field_70177_z", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "field_70125_A", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "field_70126_B", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "field_70127_C", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/math/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "field_70159_w", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "field_70181_x", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "field_70179_y", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "field_70122_E", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "field_70143_R", "F");
			if (entity_ticksExisted == nullptr)
			{
				entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "I");
			}
			//entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "field_70128_L", "Z");

		}

		{
			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
			playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		}

		{
			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "func_70608_bn", "()Z");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "func_70664_aZ", "()V");

			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "field_70737_aN", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "field_70701_bs", "F");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");

		}

		{
			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

			entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "func_184605_cv", "()I");

			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
		}

		{
			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);

			entityPlayerSP_sendQueue = Java::Env->GetFieldID(entityPlayerSP_class, "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
		}

		{
			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
			activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178814_a", "Ljava/nio/IntBuffer;");
			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178813_c", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178812_b", "Ljava/nio/FloatBuffer;");
		}

		{
			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);

			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "field_78725_b", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "field_78726_c", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "field_78723_d", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "field_78730_l", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "field_78731_m", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "field_78728_n", "D");
		}

		{
			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");

		}

		{
			Java::AssignClass("net.minecraft.world.World", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "func_147447_a", "(Lnet/minecraft/util/math/Vec3d;Lnet/minecraft/util/math/Vec3d;ZZZ)Lnet/minecraft/util/math/RayTraceResult;");
			world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "func_180495_p", "(Lnet/minecraft/util/math/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "func_175623_d", "(Lnet/minecraft/util/math/BlockPos;)Z");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "field_73010_i", "Ljava/util/List;");
			world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "field_72996_f", "Ljava/util/List;");
		}

		/*
		不存在
		*/
		{
			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			//chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
		}



		{
			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "field_194149_e", "F");//猜的
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "field_194147_b", "F");

		}

		{
			Java::AssignClass("net.minecraft.util.math.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
		}
		{
			Java::AssignClass("net.minecraft.util.math.RayTraceResult", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/math/Vec3d;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/math/RayTraceResult$Type;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/util/math/BlockPos;");
		}

		{
			Java::AssignClass("net.minecraft.util.math.Vec3d", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "field_72450_a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "field_72448_b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "field_72449_c", "D");
		}

		{
			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "func_70301_a", "(I)Lnet/minecraft/item/ItemStack;");


			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70462_a", "Lnet/minecraft/util/NonNullList;");
			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70460_b", "Lnet/minecraft/util/NonNullList;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
			itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "func_150997_a", "(Lnet/minecraft/block/state/IBlockState;)F");
		}

		{
			Java::AssignClass("net.minecraft.item.Item", item_class);

			item_class = (jclass)Java::Env->NewGlobalRef(item_class);
			item_getIdFromItem = Java::Env->GetMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "func_82814_b", "(Lnet/minecraft/item/ItemStack;)I");
		}

		/*
		* 找不到
		*/
		{
			Java::AssignClass("net.minecraft.item.ItemTool", itemTool_class);
			itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

			//itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "func_150893_a", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/Block;)F");
		}

		{
			//引用
			Java::AssignClass("net.minecraft.util.math.BlockPos", blockPos_class);
			blockPos_class = (jclass)Java::Env->NewGlobalRef(blockPos_class);
			blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
			blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "field_177994_h", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "field_177995_i", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "field_177993_j", "I");
		}

		{
			Java::AssignClass("net.minecraft.block.Block", block_class);
			block_class = (jclass)Java::Env->NewGlobalRef(block_class);

			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
		}

		{
			Java::AssignClass("net.minecraft.block.state.BlockStateContainer", blockState_class);
			blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

			blockState_block = Java::Env->GetFieldID(blockState_class, "field_177627_c", "Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "func_177230_c", "()Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.BlockAir", blockAir_class);
			blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
		}

		{
			Java::AssignClass("net.minecraft.util.NonNullList", nonNullList_class);
			nonNullList_class = (jclass)Java::Env->NewGlobalRef(nonNullList_class);

			nonNullList_List = Java::Env->GetFieldID(nonNullList_class, "field_191198_a", "Ljava/util/List;");
		}

		Java::AssignClass("net.minecraft.entity.item.EntityItem", entityItem_class);
		entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
	}

	static void Load1710ForgeMap() {
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);
			if (!Logger::Initialized)
				Logger::Init();


			jint count;
			jfieldID* fields;

			Java::Jvmti->GetClassFields(minecraft_class, &count, &fields);
			for (int i = 0; i < count; i++)
			{
				char* sign;
				char* name;
				Java::Jvmti->GetFieldName(minecraft_class, fields[i], &name, &sign, 0);

				//std::cout << "Desc:" << sign << " Name:" << name << std::endl;

				if (std::string(sign).find("GameSettings") != -1)
				{
					std::cout << "GameSettings" << std::endl;
					minecraft_gameSettings = fields[i];
				}

				if (std::string(sign).find("GuiIngame") != -1)
				{
					std::cout << "GuiIngame" << std::endl;
					minecraft_ingameGUI = fields[i];
				}

				//if (std::string(sign).find("net/minecraft/client/network/NetHandlerPlayClient") != -1)
				//{
				//	std::cout << "NetworkManager: " << name << std::endl;
				//	//minecraft_netManager = fields[i];
				//}

			}
			minecraft_getNetHandler = Java::Env->GetMethodID(minecraft_class, "func_147114_u", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "func_147116_af", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "func_175610_ah", "()I");

			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");

			if (minecraft_gameSettings == nullptr)
			{
				minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
			}

			if (minecraft_ingameGUI == nullptr)
			{
				minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "field_71456_v", "Lnet/minecraft/client/gui/GuiIngame;");
			}

			/*if (minecraft_netManager == nullptr)
			{
				minecraft_netManager = Java::Env->GetFieldID(minecraft_class, "field_147302_e", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
				std::cout << "netManager: " << minecraft_netManager << std::endl;
			}*/
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "field_71467_ac", "I");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
			gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74320_O", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74334_X", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74333_Y", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
			keybind_pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");
		}

		{
			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

			netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "func_175102_a", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");
			netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "func_147297_a", "(Lnet/minecraft/network/Packet;)V");

		}

		{
			Java::AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
			guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

			guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "func_175181_h", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
		}


		{
			Java::AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
			guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

			guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "func_175243_a", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
		}


		{
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			{
				jint count;
				jfieldID* fields;

				Java::Jvmti->GetClassFields(entity_class, &count, &fields);

				for (int i = 0; i < count; i++)
				{
					char* sign;
					char* name;
					Java::Jvmti->GetFieldName(entity_class, fields[i], &name, &sign, 0);

					//std::cout << "Desc:" << sign << " Name:" << name << std::endl;
					if (std::string(name).find("NaC") != -1)
					{
						//std::cout << "find" << std::endl;
						//entity_ticksExisted = fields[i];
					}
				}
			}


			entity_getName = Java::Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "func_70093_af", "()Z");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "func_70095_a", "(Z)V");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "func_70107_b", "(DDD)V");
			entity_setSprint = Java::Env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "func_82150_aj", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "func_70090_H", "()Z");
			entity_getUniqueID = Java::Env->GetMethodID(entity_class, "func_110124_au", "()Ljava/util/UUID;");

			entity_posX = Java::Env->GetFieldID(entity_class, "field_70165_t", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "field_70163_u", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "field_70161_v", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "field_70142_S", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "field_70137_T", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "field_70136_U", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "field_70130_N", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "field_70131_O", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70140_Q", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70141_P", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "field_70177_z", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "field_70125_A", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "field_70126_B", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "field_70127_C", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "field_70159_w", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "field_70181_x", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "field_70179_y", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "field_70122_E", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "field_70143_R", "F");
			if (entity_ticksExisted == nullptr)
			{
				entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "I");
			}
			//entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "field_70128_L", "Z");

		}

		{
			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
			playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		}

		{
			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "func_70608_bn", "()Z");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "func_70664_aZ", "()V");

			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "field_70737_aN", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "field_70701_bs", "F");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");

		}

		{
			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

			entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "func_70632_aY", "()Z");

			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
		}

		{
			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);

			entityPlayerSP_sendQueue = Java::Env->GetFieldID(entityPlayerSP_class, "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
		}



		{
			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
			activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_74597_i", "Ljava/nio/IntBuffer;");
			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_74595_k", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_74594_j", "Ljava/nio/FloatBuffer;");
		}


		{
			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);

			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "field_78725_b", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "field_78726_c", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "field_78723_d", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "field_78730_l", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "field_78731_m", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "field_78728_n", "D");
		}


		{
			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");

		}

		{
			Java::AssignClass("net.minecraft.world.World", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
			world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "func_180495_p", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "field_73010_i", "Ljava/util/List;");
			world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "field_72996_f", "Ljava/util/List;");
		}

		{
			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
		}



		{
			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "field_74278_d", "F");
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "field_74281_c", "F");

		}


		{
			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
		}

		{
			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/Vec3;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/util/BlockPos;");
		}

		{
			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "field_72450_a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "field_72448_b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "field_72449_c", "D");
		}



		{
			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "func_70301_a", "(I)Lnet/minecraft/item/ItemStack;");


			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70462_a", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70460_b", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
			itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "func_150997_a", "(Lnet/minecraft/block/Block;)F");
		}



		{
			Java::AssignClass("net.minecraft.item.Item", item_class);

			item_class = (jclass)Java::Env->NewGlobalRef(item_class);
			item_getIdFromItem = Java::Env->GetMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "func_82814_b", "(Lnet/minecraft/item/ItemStack;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.ItemTool", itemTool_class);
			itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

			itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "func_150893_a", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/Block;)F");
		}

		{
			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_class = (jclass)Java::Env->NewGlobalRef(blockPos_class);
			blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
			blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "field_177962_a", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "field_177960_b", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "field_177961_c", "I");
		}

		{
			Java::AssignClass("net.minecraft.block.Block", block_class);
			block_class = (jclass)Java::Env->NewGlobalRef(block_class);

			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
		}

		{
			Java::AssignClass("net.minecraft.block.state.BlockState", blockState_class);
			blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

			blockState_block = Java::Env->GetFieldID(blockState_class, "field_177627_c", "Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "func_177230_c", "()Lnet/minecraft/block/Block;");

		}

		{
			Java::AssignClass("net.minecraft.block.BlockAir", blockAir_class);
			blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
		}
		Java::AssignClass("net.minecraft.entity.item.EntityItem", entityItem_class);
		entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
	}

	static void Initialize() {
		IsLunar = false;
		if (Base::version == FORGE_1_12_2) {
			std::cout << "FORGE_1_12_2" << std::endl;
			Load112ForgeMap();
			goto End;
		}
		if (Base::version == LUNAR_1_8_9) {
			std::cout << "LUNAR_1_8_9" << std::endl;
			IsLunar = true;
			//Lunar
			Load189MCPMap();
			goto End;
		}

		if (Base::version == VANILLA_1_8_9) {
			std::cout << "VANILLA_1_8_9" << std::endl;
			Load189VanillaMap();
			goto End;
		}
		if (Base::version == BADLION) {
			std::cout << "BADLION" << std::endl;
			Load189VanillaMap();
			goto End;
		}


		if (Base::version == FORGE_1_8_9) {
			std::cout << "FORGE_1_8_9" << std::endl;
			Load189ForgeMap();
			//Load1710ForgeMap();懒得写判断,有点问题
			goto End;
		}

		if (Base::version == FORGE_1_7_10) {
			std::cout << "FORGE_1_7_10" << std::endl;
			Load1710ForgeMap();
			goto End;
		}

		if (Base::version == LUNAR_1_12_2) {
			std::cout << "Lunar 1.12.2" << std::endl;
			IsLunar = true;
			//Lunar
			Load112MCPMap();
			goto End;
		}

		//Load112MCPMap();
	End:

		conllection_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/util/Collection"));
		conllection_toArray = Java::Env->GetMethodID(conllection_class, "toArray", "()[Ljava/lang/Object;");

		list_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/util/List"));
		list_toArray = Java::Env->GetMethodID(list_class, "toArray", "()[Ljava/lang/Object;");
		set_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/util/Set"));
		set_toArray = Java::Env->GetMethodID(set_class, "toArray", "()[Ljava/lang/Object;");

		system_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/lang/System"));
		system_gc = Java::Env->GetStaticMethodID(system_class, "gc", "()V");

		string_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/lang/String"));
		string_contains = Java::Env->GetMethodID(string_class, "contains", "(Ljava/lang/CharSequence;)Z");

		floatBuffer_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/nio/FloatBuffer"));
		floatBuffer_get = Java::Env->GetMethodID(floatBuffer_class, "get", "(I)F");
		intBuffer_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/nio/IntBuffer"));
		intBuffer_get = Java::Env->GetMethodID(intBuffer_class, "get", "(I)I");
		/*set_class = (jclass)Java::Env->NewGlobalRef(set_class);
		conllection_class = (jclass)Java::Env->NewGlobalRef(conllection_class);
		list_class = (jclass)Java::Env->NewGlobalRef(list_class);
		floatBuffer_class = (jclass)Java::Env->NewGlobalRef(floatBuffer_class);

		activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
		gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);
		entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);
		entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);
		entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
		entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);
		chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);
		axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);
		movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);
		itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);
		inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);
		vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);
		itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);
		item_class= (jclass)Java::Env->NewGlobalRef(item_class);
		renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);*/
		initialized = true;
	}
	static void DeleteRefs() {
		if (IsLunar)
			return;
		Java::Env->DeleteGlobalRef(set_class);
		Java::Env->DeleteGlobalRef(system_class);
		Java::Env->DeleteGlobalRef(list_class);
		Java::Env->DeleteGlobalRef(floatBuffer_class);
		Java::Env->DeleteGlobalRef(intBuffer_class);
		Java::Env->DeleteGlobalRef(string_class);
		Java::Env->DeleteGlobalRef(minecraft_class);
		Java::Env->DeleteGlobalRef(activeRenderInfo_class);
		Java::Env->DeleteGlobalRef(gamesettings_class);
		Java::Env->DeleteGlobalRef(keybind_class);
		Java::Env->DeleteGlobalRef(entity_class);
		Java::Env->DeleteGlobalRef(entityLivingBase_class);
		Java::Env->DeleteGlobalRef(entityPlayerSP_class);
		Java::Env->DeleteGlobalRef(entityPlayer_class);
		Java::Env->DeleteGlobalRef(chunk_class);
		Java::Env->DeleteGlobalRef(axisAlignedBB_class);
		Java::Env->DeleteGlobalRef(movingObjectPosition_class);
		Java::Env->DeleteGlobalRef(itemStack_class);
		Java::Env->DeleteGlobalRef(inventoryPlayer_class);
		Java::Env->DeleteGlobalRef(vec3_class);
		Java::Env->DeleteGlobalRef(itemArmor_Class);
		Java::Env->DeleteGlobalRef(item_class);
		Java::Env->DeleteGlobalRef(renderManager_class);
		Java::Env->DeleteGlobalRef(netHandlerPlayClient_class);
		Java::Env->DeleteGlobalRef(guiIngame_class);
		Java::Env->DeleteGlobalRef(guiPlayerTabOverlay_class);
		Java::Env->DeleteGlobalRef(worldClient_class);
		Java::Env->DeleteGlobalRef(timer_class);
		Java::Env->DeleteGlobalRef(world_class);
		Java::Env->DeleteGlobalRef(conllection_class);
		Java::Env->DeleteGlobalRef(blockPos_class);
		Java::Env->DeleteGlobalRef(block_class);
		Java::Env->DeleteGlobalRef(blockState_class);
		Java::Env->DeleteGlobalRef(iBlockState_class);
		Java::Env->DeleteGlobalRef(blockAir_class);
		Java::Env->DeleteGlobalRef(itemTool_class);
		Java::Env->DeleteGlobalRef(nonNullList_class);
		Java::Env->DeleteGlobalRef(networkManager_class);

	}

};