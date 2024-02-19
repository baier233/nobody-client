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
		Load1181ForgeMap();
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

	//Render System Class (1.18.1
	inline static jclass renderSystem_class;
	inline static jfieldID renderSystem_shader;

	//ShaderInstance Class (1.18.1
	inline static jclass shaderInstance_class;
	inline static jfieldID shaderInstance_MODEL_VIEW_MATRIX;
	inline static jfieldID shaderInstance_PROJECTION_MATRIX;

	//Uniform Class (1.18.1
	inline static jclass uniform_class;
	inline static jfieldID uniform_floatValues;

	//Game Settings
	inline static jclass gamesettings_class;
	inline static jmethodID gamesettings_setOptionKeyBinding;
	inline static jfieldID gamesettings_cameraType;//this is for 1.18.1
	inline static jfieldID gamesettings_thirdPersonView;
	inline static jfieldID gamesettings_fovSetting;
	inline static jfieldID gamesettings_gammaSetting;
	inline static jfieldID gamesettings_keyBindFullscreen;
	inline static jfieldID gamesettings_keyBindSneak;

	//CameraType Class (1.18.1
	inline static jclass cameraType_class;
	inline static jmethodID cameraType_isFirstPerson;

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
	//ONLY FOR 1.18.1 BEGIN
	inline static jmethodID entity_getX;
	inline static jmethodID entity_getY;
	inline static jmethodID entity_getZ;
	//END
	inline static jmethodID entity_getName;
	inline static jmethodID entity_isSneaking;
	inline static jmethodID entity_setSneaking;
	inline static jmethodID entity_setPosition;
	inline static jmethodID entity_setSprint;
	inline static jmethodID entity_isInvisible;
	inline static jmethodID entity_inWater;
	inline static jmethodID entity_getUniqueID;
	inline static jmethodID entity_getBBHeight;//this is for 1.18.1
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
	inline static jfieldID entity_deltaMovement;
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
	inline static jmethodID entityPlayer_getInventory; // this is for 1.18.1
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
	inline static jfieldID renderManager_Instance;//1,7.10 forge only
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
	inline static jmethodID world_getBlock; //for 1.7.10
	inline static jmethodID world_rayTraceBlocks;
	inline static jmethodID world_getChunkFromChunkCoords;
	inline static jmethodID world_isAirBlock;
	inline static jfieldID world_playerEntities;
	inline static jfieldID world_loadedEntityList;
	inline static jfieldID world_loadedTileEntityList;//TODO:only 1.12.2


	//ClientLevel Class(this is for 1.18.1)
	inline static jclass clientLevel_class;
	inline static jfieldID clientLevel_players;
	inline static jmethodID clientLevel_entitiesForRendering;



	//tileEntity
	inline static jclass tileEntity_class;
	inline static jmethodID tileEntity_getPos;

	//TileEntityBed
	inline static jclass tileEntityBed_class;

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
	inline static jfieldID movingObjectPosition_blockX;//3 fields below is for 1.7.10
	inline static jfieldID movingObjectPosition_blockY;
	inline static jfieldID movingObjectPosition_blockZ;
	inline static jfieldID movingObjectPosition_hitVec;
	inline static jfieldID movingObjectPosition_typeOfHit;
	inline static jmethodID hitResult_getType; // this is for 1.18.1
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
	inline static jmethodID block_isAir;  // this is for 1.18.1

	//BlockState Class
	inline static jclass blockState_class;
	inline static jfieldID blockState_block;
	//inline static jmethodID blockState_getBlock; // this is for 1.18.1

	//blockStateBase Class(PS:this is for 1.18.1)
	inline static jclass blockStateBase_class;
	inline static jmethodID blockStateBase_getBlock;

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

	//DyeableLeatherItem Class(this is for 1.18.1)
	inline static jclass dyeableLeatherItem_class;
	inline static jmethodID dyeableLeatherItem_getColor;

	//NonNullList Class
	inline static jclass nonNullList_class;
	inline static jfieldID nonNullList_List;

	//EntityItem Class
	inline static jclass entityItem_class;

	inline static jclass hitResult_class;



	static void Load112ForgeMap();
	static void Load189ForgeMap();
	static void Load1710ForgeMap();
	static void Load112MCPMap();
	static void Load189MCPMap();
	static void Load189VanillaMap();
	static void Load1181ForgeMap();



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
		initialized = true;
	}
	static void DeleteRefs() {
		if (IsLunar || Base::version == BADLION)
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
		Java::Env->DeleteGlobalRef(tileEntity_class);
		Java::Env->DeleteGlobalRef(tileEntityBed_class);

	}

};