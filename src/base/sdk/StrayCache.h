#pragma once
#include "JNIHelper.h"
#include "../util/logger.h"
#include "../base.h"

#include <unordered_map>
#include <map>

#include "../jvm/classes/java_thread.h"




inline bool IsLunar = false;

class StrayCache {

public:

	bool initialized;
	static StrayCache* GetInstance()
	{
		static auto shared = std::make_unique<StrayCache>();
		return shared.get();
	}
	
	
	
	void helper() {
		//这个方法不会被调用，只是用来方便跳转到指定的方法
		Load112ForgeMap();
		Load189ForgeMap();
		Load189MCPMap();
		Load189VanillaMap();
		Load1710ForgeMap();
		Load112MCPMap();
		Load1181ForgeMap();
	}


	//Minecraft Class
	jclass minecraft_class;
	jmethodID minecraft_getMinecraft;
	jmethodID minecraft_getNetHandler;
	jmethodID minecraft_getRenderViewEntity;
	jmethodID minecraft_clickMouse;
	jmethodID minecraft_getDebugFPS;
	jfieldID minecraft_mc;
	jfieldID minecraft_thePlayer;
	jfieldID minecraft_theWorld;
	jfieldID minecraft_playerController;
	jfieldID minecraft_renderManager;
	jfieldID minecraft_timer;
	jfieldID minecraft_gameSettings;
	jfieldID minecraft_ingameGUI;
	jfieldID minecraft_currentScreen;
	jfieldID minecraft_objectMouseOver;
	jfieldID minecraft_rightClickDelayTimer;

	//ActiveRenderInfo Class
	jclass activeRenderInfo_class;
	jfieldID activeRenderInfo_VIEWPORT;
	jfieldID activeRenderInfo_MODELVIEW;
	jfieldID activeRenderInfo_PROJECTION;

	//Render System Class (1.18.1
	jclass renderSystem_class;
	jfieldID renderSystem_shader;

	//ShaderInstance Class (1.18.1
	jclass shaderInstance_class;
	jfieldID shaderInstance_MODEL_VIEW_MATRIX;
	jfieldID shaderInstance_PROJECTION_MATRIX;

	//Uniform Class (1.18.1
	jclass uniform_class;
	jfieldID uniform_floatValues;

	//Game Settings
	jclass gamesettings_class;
	jmethodID gamesettings_setOptionKeyBinding;
	jfieldID gamesettings_cameraType;//this is for 1.18.1
	jfieldID gamesettings_thirdPersonView;
	jfieldID gamesettings_fovSetting;
	jfieldID gamesettings_gammaSetting;
	jfieldID gamesettings_keyBindFullscreen;
	jfieldID gamesettings_keyBindSneak;

	//CameraType Class (1.18.1
	jclass cameraType_class;
	jmethodID cameraType_isFirstPerson;

	//CPacketPlayr Class
	jclass cpacketPlayer_class;

	//KeyBind Class
	jclass keybind_class;
	jfieldID keybind_pressed;

	//NetHandlerPlayClient class
	jclass netHandlerPlayClient_class;
	jmethodID netHandlerPlayClient_getPlayerInfo;
	jmethodID netHandlerPlayClient_addToSendQueue;


	//GuiIngame class
	jclass guiIngame_class;
	jmethodID guiIngame_getTabList;

	//GuiPlayerTabOverlay class
	jclass guiPlayerTabOverlay_class;
	jmethodID guiPlayerTabOverlay_getPlayerName;

	//PlayerController Class
	jclass playerControllerMP_class;
	jmethodID playerControllerMP_attackEntity;
	jmethodID playerControllerMP_sendUseItem;

	//NetworkManager Class
	jclass networkManager_class;
	jmethodID networkManager_sendPacket;
	jmethodID networkManager_channelRead0;

	// ENTITY CLASS
	jclass entity_class;
	//ONLY FOR 1.18.1 BEGIN
	jmethodID entity_getX;
	jmethodID entity_getY;
	jmethodID entity_getZ;
	//END
	jmethodID entity_getName;
	jmethodID entity_isSneaking;
	jmethodID entity_setSneaking;
	jmethodID entity_setPosition;
	jmethodID entity_setSprint;
	jmethodID entity_isInvisible;
	jmethodID entity_inWater;
	jmethodID entity_getUniqueID;
	jmethodID entity_getBBHeight;//this is for 1.18.1
	jfieldID entity_position;//this is for 1.18.1
	jfieldID entity_eyeHeight;//this is for 1.18.1
	jfieldID entity_posX;
	jfieldID entity_posY;
	jfieldID entity_posZ;
	jfieldID entity_lastTickPosX;
	jfieldID entity_lastTickPosY;
	jfieldID entity_lastTickPosZ;
	jfieldID entity_width;
	jfieldID entity_height;
	jfieldID entity_distanceWalkedModified;
	jfieldID entity_prevDistanceWalkedModified;
	jfieldID entity_rotationYaw;
	jfieldID entity_rotationPitch;
	jfieldID entity_prevRotationYaw;
	jfieldID entity_prevRotationPitch;
	jfieldID entity_boundingBox;
	jfieldID entity_deltaMovement;
	jfieldID entity_motionX;
	jfieldID entity_motionY;
	jfieldID entity_motionZ;
	jfieldID entity_onGround;
	jfieldID entity_fallDistance;
	jfieldID entity_ticksExisted;
	jfieldID entity_isDead;

	// ENTITY LIVING BASE CLASS
	jclass entityLivingBase_class;
	jmethodID entityLivingBase_getHealth;
	jmethodID entityLivingBase_getMaxHealth;
	jmethodID entityLivingBase_canEntityBeSeen;
	jmethodID entityLivingBase_isPlayerSleeping;
	jmethodID entityLivingBase_swingItem;
	jmethodID entityLivingBase_jump;
	jfieldID entityLivingBase_hurttime;
	jfieldID entityLivingBase_moveForward;
	jfieldID entityLivingBase_moveStrafe;

	//Entity Player
	jclass entityPlayer_class;
	jmethodID entityPlayer_isBlocking;
	jmethodID entityPlayer_getInventory; // this is for 1.18.1
	jfieldID entityPlayer_inventory;


	//Entity Player SP
	jclass entityPlayerSP_class;
	jfieldID entityPlayerSP_sendQueue;
	jfieldID entityPlayerSP_abilities;

	jfieldID localPlayer_xLast;
	jfieldID localPlayer_yLast1;
	jfieldID localPlayer_zLast;

	//World Client
	jclass worldClient_class;
	jfieldID worldClient_entityList;

	//RenderManager
	jclass renderManager_class;
	jfieldID renderManager_Instance;//1,7.10 forge only
	jfieldID renderManager_renderPosX;
	jfieldID renderManager_renderPosY;
	jfieldID renderManager_renderPosZ;
	jfieldID renderManager_viewerPosX;
	jfieldID renderManager_viewerPosY;
	jfieldID renderManager_viewerPosZ;
	jfieldID renderManager_playerViewX;
	jfieldID renderManager_playerViewY;

	//Timer
	jclass timer_class;
	jfieldID timer_renderPartialTicks;
	jfieldID timer_timerSpeed;


	//World
	jclass world_class;
	jmethodID world_getBlockState;
	jmethodID world_getBlock; //for 1.7.10
	jmethodID world_rayTraceBlocks;
	jmethodID world_getChunkFromChunkCoords;
	jmethodID world_isAirBlock;
	jfieldID world_playerEntities;
	jfieldID world_loadedEntityList;
	jfieldID world_loadedTileEntityList;//TODO:only 1.12.2


	//ClientLevel Class(this is for 1.18.1)
	jclass clientLevel_class;
	jfieldID clientLevel_players;
	jmethodID clientLevel_entitiesForRendering;



	//tileEntity
	jclass tileEntity_class;
	jmethodID tileEntity_getPos;

	//TileEntityBed
	jclass tileEntityBed_class;

	//Chunk
	jclass chunk_class;
	jmethodID chunk_getBlock;

	//collection
	jclass conllection_class;
	jmethodID conllection_toArray;

	//Set
	jclass set_class;
	jmethodID set_toArray;

	//List
	jclass list_class;
	jmethodID list_toArray;

	//FloatBuffer
	jclass floatBuffer_class;
	jmethodID floatBuffer_get;

	//IntBuffer
	jclass intBuffer_class;
	jmethodID intBuffer_get;


	//String class
	jclass string_class;
	jmethodID string_contains;

	//System class
	jclass system_class;
	jmethodID system_gc;

	// AXIS ALIGNED BB CLASS
	jclass axisAlignedBB_class;
	jfieldID axisAlignedBB_minX;
	jfieldID axisAlignedBB_minY;
	jfieldID axisAlignedBB_minZ;
	jfieldID axisAlignedBB_maxX;
	jfieldID axisAlignedBB_maxY;
	jfieldID axisAlignedBB_maxZ;

	// MOVING OBJECT POSITION CLASS
	jclass movingObjectPosition_class;
	jfieldID movingObjectPosition_blockX;//3 fields below is for 1.7.10
	jfieldID movingObjectPosition_blockY;
	jfieldID movingObjectPosition_blockZ;
	jfieldID movingObjectPosition_hitVec;
	jfieldID movingObjectPosition_typeOfHit;
	jmethodID hitResult_getType; // this is for 1.18.1
	jfieldID movingObjectPosition_blockPos;

	jclass blockHitResult_class;
	jfieldID blockHitResult_blockPos;
	jfieldID blockHitResult_miss;

	jclass vec3_class;
	jfieldID vec3_xCoord;
	jfieldID vec3_yCoord;
	jfieldID vec3_zCoord;

	jclass inventoryPlayer_class;
	jmethodID inventoryPlayer_getCurrentItem;
	jmethodID inventoryPlayer_getStackInSlot;
	jfieldID inventoryPlayer_mainInv;
	jfieldID inventoryPlayer_armorInv;
	jfieldID inventoryPlayer_currentItem;

	jclass itemStack_class;
	jmethodID itemStack_getItem;
	jmethodID itemStack_getStrVsBlock;

	jclass blockPos_class;
	jfieldID blockPos_x;
	jfieldID blockPos_y;
	jfieldID blockPos_z;
	jmethodID blockPos_constructor;
	jmethodID blockPos_constructorI;

	//Block Class
	jclass block_class;
	jmethodID block_getIdFromBlock;
	jmethodID block_isAir;  // this is for 1.18.1

	//BlockState Class
	jclass blockState_class;
	jfieldID blockState_block;
	//jmethodID blockState_getBlock; // this is for 1.18.1

	//blockStateBase Class(PS:this is for 1.18.1)
	jclass blockStateBase_class;
	jmethodID blockStateBase_getBlock;
	jmethodID blockStateBase_isAir;

	//IBlockState Class
	jclass iBlockState_class;
	jmethodID iBlockState_getBlock;
	jmethodID iBlockState_getBlockFromBlockState;

	//BlockAir Clss
	jclass blockAir_class;

	//Item Class
	jclass item_class;
	jmethodID item_getIdFromItem;

	//ItemArmor Class
	jclass itemArmor_Class;
	jmethodID itemArmor_getColor;

	//ItemTool Class
	jclass itemTool_class;
	jmethodID itemTool_getStrVsBlock;

	jclass itemBlock_class;

	//DyeableLeatherItem Class(this is for 1.18.1)
	jclass dyeableLeatherItem_class;
	jmethodID dyeableLeatherItem_getColor;

	//NonNullList Class
	jclass nonNullList_class;
	jfieldID nonNullList_List;

	//EntityItem Class
	jclass entityItem_class;

	jclass hitResult_class;



	void Load112ForgeMap();
	void Load189ForgeMap();
	void Load1710ForgeMap();
	void Load112MCPMap();
	void Load189MCPMap();
	void Load189VanillaMap();
	void Load1181ForgeMap();



	void Initialize() {
		if (this->initialized) return;
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
		if (Base::version == FORGE_1_18_1)
		{
			std::cout << "Forge 1.18.1" << std::endl;
			Load1181ForgeMap();
			goto End;
		}

		//Load112MCPMap();
	End:

		conllection_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/util/Collection"));
		conllection_toArray = Java::GetInstance()->Env->GetMethodID(conllection_class, "toArray", "()[Ljava/lang/Object;");

		list_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/util/List"));
		list_toArray = Java::GetInstance()->Env->GetMethodID(list_class, "toArray", "()[Ljava/lang/Object;");
		set_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/util/Set"));
		set_toArray = Java::GetInstance()->Env->GetMethodID(set_class, "toArray", "()[Ljava/lang/Object;");

		system_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/lang/System"));
		system_gc = Java::GetInstance()->Env->GetStaticMethodID(system_class, "gc", "()V");

		string_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/lang/String"));
		string_contains = Java::GetInstance()->Env->GetMethodID(string_class, "contains", "(Ljava/lang/CharSequence;)Z");

		floatBuffer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/nio/FloatBuffer"));
		floatBuffer_get = Java::GetInstance()->Env->GetMethodID(floatBuffer_class, "get", "(I)F");
		intBuffer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(Java::GetInstance()->Env->FindClass("java/nio/IntBuffer"));
		intBuffer_get = Java::GetInstance()->Env->GetMethodID(intBuffer_class, "get", "(I)I");
		auto thread = GetCurrentThreadId();
		
		initialized = true;
	}
	void DeleteRefs() {
		if (IsLunar || Base::version == BADLION)
			return;
		Java::GetInstance()->Env->DeleteGlobalRef(set_class);
		Java::GetInstance()->Env->DeleteGlobalRef(system_class);
		Java::GetInstance()->Env->DeleteGlobalRef(list_class);
		Java::GetInstance()->Env->DeleteGlobalRef(floatBuffer_class);
		Java::GetInstance()->Env->DeleteGlobalRef(intBuffer_class);
		Java::GetInstance()->Env->DeleteGlobalRef(string_class);
		Java::GetInstance()->Env->DeleteGlobalRef(minecraft_class);
		Java::GetInstance()->Env->DeleteGlobalRef(activeRenderInfo_class);
		Java::GetInstance()->Env->DeleteGlobalRef(gamesettings_class);
		Java::GetInstance()->Env->DeleteGlobalRef(keybind_class);
		Java::GetInstance()->Env->DeleteGlobalRef(entity_class);
		Java::GetInstance()->Env->DeleteGlobalRef(entityLivingBase_class);
		Java::GetInstance()->Env->DeleteGlobalRef(entityPlayerSP_class);
		Java::GetInstance()->Env->DeleteGlobalRef(entityPlayer_class);
		Java::GetInstance()->Env->DeleteGlobalRef(chunk_class);
		Java::GetInstance()->Env->DeleteGlobalRef(axisAlignedBB_class);
		Java::GetInstance()->Env->DeleteGlobalRef(movingObjectPosition_class);
		Java::GetInstance()->Env->DeleteGlobalRef(itemStack_class);
		Java::GetInstance()->Env->DeleteGlobalRef(inventoryPlayer_class);
		Java::GetInstance()->Env->DeleteGlobalRef(vec3_class);
		Java::GetInstance()->Env->DeleteGlobalRef(itemArmor_Class);
		Java::GetInstance()->Env->DeleteGlobalRef(item_class);
		Java::GetInstance()->Env->DeleteGlobalRef(renderManager_class);
		Java::GetInstance()->Env->DeleteGlobalRef(netHandlerPlayClient_class);
		Java::GetInstance()->Env->DeleteGlobalRef(guiIngame_class);
		Java::GetInstance()->Env->DeleteGlobalRef(guiPlayerTabOverlay_class);
		Java::GetInstance()->Env->DeleteGlobalRef(worldClient_class);
		Java::GetInstance()->Env->DeleteGlobalRef(timer_class);
		Java::GetInstance()->Env->DeleteGlobalRef(world_class);
		Java::GetInstance()->Env->DeleteGlobalRef(conllection_class);
		Java::GetInstance()->Env->DeleteGlobalRef(blockPos_class);
		Java::GetInstance()->Env->DeleteGlobalRef(block_class);
		Java::GetInstance()->Env->DeleteGlobalRef(blockState_class);
		Java::GetInstance()->Env->DeleteGlobalRef(iBlockState_class);
		Java::GetInstance()->Env->DeleteGlobalRef(blockAir_class);
		Java::GetInstance()->Env->DeleteGlobalRef(itemTool_class);
		Java::GetInstance()->Env->DeleteGlobalRef(nonNullList_class);
		Java::GetInstance()->Env->DeleteGlobalRef(networkManager_class);
		Java::GetInstance()->Env->DeleteGlobalRef(tileEntity_class);
		Java::GetInstance()->Env->DeleteGlobalRef(tileEntityBed_class);

	}

};

#define CacheInstance StrayCache::GetInstance()