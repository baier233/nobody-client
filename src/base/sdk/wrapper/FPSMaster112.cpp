#include "../StrayCache.h"

void StrayCache::LoadFPSMaster112Map() {
	{
		Java::GetInstance()->AssignClass("fpsmaster.fm", minecraft_class);
		minecraft_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(minecraft_class);

		minecraft_getNetHandler = Java::GetInstance()->Env->GetMethodID(minecraft_class, "D", "()Lfpsmaster/jY;");
		minecraft_getMinecraft = Java::GetInstance()->Env->GetStaticMethodID(minecraft_class, "d", "()Lfpsmaster/fm;");
		minecraft_getRenderViewEntity = Java::GetInstance()->Env->GetMethodID(minecraft_class, "ab", "()Lfpsmaster/tO;");
		minecraft_clickMouse = Java::GetInstance()->Env->GetMethodID(minecraft_class, "az", "()V");
		minecraft_getDebugFPS = Java::GetInstance()->Env->GetMethodID(minecraft_class, "h", "()I");

		minecraft_thePlayer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "m", "Lfpsmaster/fJ;");
		minecraft_theWorld = Java::GetInstance()->Env->GetFieldID(minecraft_class, "k", "Lfpsmaster/jS;");
		minecraft_playerController = Java::GetInstance()->Env->GetFieldID(minecraft_class, "h", "Lfpsmaster/jN;");
		minecraft_renderManager = Java::GetInstance()->Env->GetFieldID(minecraft_class, "ar", "Lfpsmaster/nN;");
		minecraft_timer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "f", "Lfpsmaster/Ik;");
		minecraft_gameSettings = Java::GetInstance()->Env->GetFieldID(minecraft_class, "y", "Lfpsmaster/qN;");
		minecraft_ingameGUI = Java::GetInstance()->Env->GetFieldID(minecraft_class, "v", "Lfpsmaster/gj;");
		minecraft_currentScreen = Java::GetInstance()->Env->GetFieldID(minecraft_class, "r", "Lfpsmaster/gJ;");
		minecraft_objectMouseOver = Java::GetInstance()->Env->GetFieldID(minecraft_class, "x", "Lfpsmaster/Jr;");
		minecraft_rightClickDelayTimer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "az", "I");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.qN", gamesettings_class);
		gamesettings_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(gamesettings_class);

		gamesettings_setOptionKeyBinding = Java::GetInstance()->Env->GetMethodID(gamesettings_class, "a", "(Lfpsmaster/ri;I)V");
		gamesettings_thirdPersonView = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "aE", "I");
		gamesettings_fovSetting = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "aL", "F");
		gamesettings_gammaSetting = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "aM", "F");
		gamesettings_keyBindFullscreen = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "av", "Lfpsmaster/ri;");
		gamesettings_keyBindSneak = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "ah", "Lfpsmaster/ri;");

	}
	{
		Java::GetInstance()->AssignClass("fpsmaster.ri", keybind_class);
		keybind_pressed = Java::GetInstance()->Env->GetFieldID(keybind_class, "a", "Z");
	}
	{
		Java::GetInstance()->AssignClass("fpsmaster.jY", netHandlerPlayClient_class);
		netHandlerPlayClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(netHandlerPlayClient_class);

		netHandlerPlayClient_getPlayerInfo = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "a", "(Ljava/util/UUID;)Lfpsmaster/jY;");
		//这个好像没用
		//netHandlerPlayClient_addToSendQueue = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.gj", guiIngame_class);
		guiIngame_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiIngame_class);

		guiIngame_getTabList = Java::GetInstance()->Env->GetMethodID(guiIngame_class, "g", "()Lfpsmaster/gX;");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.gX", guiPlayerTabOverlay_class);
		guiPlayerTabOverlay_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiPlayerTabOverlay_class);

		guiPlayerTabOverlay_getPlayerName = Java::GetInstance()->Env->GetMethodID(guiPlayerTabOverlay_class, "a", "(Lfpsmaster/ks;)Ljava/lang/String;");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.tO", entity_class);
		entity_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entity_class);

		entity_getName = Java::GetInstance()->Env->GetMethodID(entity_class, "h_", "()Ljava/lang/String;");
		entity_isSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "Q", "()Z");
		entity_setPosition = Java::GetInstance()->Env->GetMethodID(entity_class, "b", "(DDD)V");
		entity_setSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "f", "(Z)V");
		entity_isInvisible = Java::GetInstance()->Env->GetMethodID(entity_class, "bc", "()Z");
		entity_inWater = Java::GetInstance()->Env->GetMethodID(entity_class, "av", "()Z");
		entity_getUniqueID = Java::GetInstance()->Env->GetMethodID(entity_class, "bq", "()Ljava/util/UUID;");

		entity_posX = Java::GetInstance()->Env->GetFieldID(entity_class, "v", "D");
		entity_posY = Java::GetInstance()->Env->GetFieldID(entity_class, "w", "D");
		entity_posZ = Java::GetInstance()->Env->GetFieldID(entity_class, "x", "D");
		entity_lastTickPosX = Java::GetInstance()->Env->GetFieldID(entity_class, "R", "D");
		entity_lastTickPosY = Java::GetInstance()->Env->GetFieldID(entity_class, "S", "D");
		entity_lastTickPosZ = Java::GetInstance()->Env->GetFieldID(entity_class, "T", "D");
		entity_width = Java::GetInstance()->Env->GetFieldID(entity_class, "L", "F");
		entity_height = Java::GetInstance()->Env->GetFieldID(entity_class, "M", "F");
		entity_distanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "O", "F");
		entity_prevDistanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "N", "F");
		entity_rotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "B", "F");
		entity_rotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "C", "F");
		entity_prevRotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "D", "F");
		entity_prevRotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "E", "F");
		entity_boundingBox = Java::GetInstance()->Env->GetFieldID(entity_class, "bz", "Lfpsmaster/JF;");
		entity_motionX = Java::GetInstance()->Env->GetFieldID(entity_class, "y", "D");
		entity_motionY = Java::GetInstance()->Env->GetFieldID(entity_class, "z", "D");
		entity_motionZ = Java::GetInstance()->Env->GetFieldID(entity_class, "A", "D");
		entity_onGround = Java::GetInstance()->Env->GetFieldID(entity_class, "F", "Z");
		entity_fallDistance = Java::GetInstance()->Env->GetFieldID(entity_class, "Q", "F");
		entity_isDead = Java::GetInstance()->Env->GetFieldID(entity_class, "K", "Z");
		entity_ticksExisted = Java::GetInstance()->Env->GetFieldID(entity_class, "X", "I");//nullptr

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.jN", playerControllerMP_class);
		playerControllerMP_attackEntity = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "attackEntity", "(Lfpsmaster/yp;Lfpsmaster/tO;)V");

		//草泥马能不能别写没调用的
		//playerControllerMP_sendUseItem = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "sendUseItem", "(Lfpsmaster/yp;Lnet/minecraft/world/World;Lfpsmaster/Bi;)Z");//nullptr
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.ur", entityLivingBase_class);
		entityLivingBase_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityLivingBase_class);

		entityLivingBase_getHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "cw", "()F");
		entityLivingBase_getMaxHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "cC", "()F");
		entityLivingBase_canEntityBeSeen = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "z", "(Lfpsmaster/uh;)Z");
		entityLivingBase_isPlayerSleeping = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "b_", "()Z");
		entityLivingBase_hurttime = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "aH", "I");
		entityLivingBase_moveForward = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "bb", "F");
		entityLivingBase_moveStrafe = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "ba", "F");
		//entityLivingBase_swingItem = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");//nullptr
		entityLivingBase_jump = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "cN", "()V");
	}



	{
		Java::GetInstance()->AssignClass("fpsmaster.yp", entityPlayer_class);
		entityPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayer_class);

		//entityPlayer_isBlocking = Java::GetInstance()->Env->GetMethodID(entityPlayer_class, "getItemInUseCount", "()I");//nullptr

		entityPlayer_inventory = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->entityPlayer_class, "bB", "Lfpsmaster/ys;");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.fJ", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayerSP_class);
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.lq", activeRenderInfo_class);
		activeRenderInfo_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(activeRenderInfo_class);
		activeRenderInfo_VIEWPORT = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "a", "Ljava/nio/IntBuffer;");
		activeRenderInfo_PROJECTION = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "b", "Ljava/nio/FloatBuffer;");
		activeRenderInfo_MODELVIEW = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "c", "Ljava/nio/FloatBuffer;");
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.nN", renderManager_class);
		renderManager_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(renderManager_class);


		renderManager_renderPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "m", "D");
		renderManager_renderPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "n", "D");
		renderManager_renderPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "o", "D");
		renderManager_viewerPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "h", "D");
		renderManager_viewerPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "i", "D");
		renderManager_viewerPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "g", "D");
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.jS", worldClient_class);
		worldClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(worldClient_class);

		worldClient_entityList = Java::GetInstance()->Env->GetFieldID(worldClient_class, "d", "Ljava/util/Set;");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.KT", world_class);
		world_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(world_class);

		world_rayTraceBlocks = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "rayTraceBlocks", "(Lfpsmaster/JN;Lfpsmaster/JN;ZZZ)Lfpsmaster/Jr;");
		world_getChunkFromChunkCoords = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "getChunkFromChunkCoords", "(II)Lfpsmaster/LQ;");//nullptr
		world_getBlockState = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "getBlockState", "(Lfpsmaster/JG;)Lfpsmaster/fu;");
		world_isAirBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "isAirBlock", "(Lfpsmaster/JG;)Z");

		world_playerEntities = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "playerEntities", "Ljava/util/List;");
		world_loadedEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "loadedEntityList", "Ljava/util/List;");
		world_loadedTileEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "loadedTileEntityList", "Ljava/util/List;");
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.LQ", chunk_class);
		chunk_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(chunk_class);

		//chunk_getBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->chunk_class, "getBlock", "(III)Lfpsmaster/bF;");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.ID", timer_class);
		timer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(timer_class);

		timer_timerSpeed = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "e", "F");
		timer_renderPartialTicks = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "b", "F");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.JF", axisAlignedBB_class);
		axisAlignedBB_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(axisAlignedBB_class);

		axisAlignedBB_minX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "a", "D");
		axisAlignedBB_minY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "b", "D");
		axisAlignedBB_minZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "c", "D");
		axisAlignedBB_maxX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "d", "D");
		axisAlignedBB_maxY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "e", "D");
		axisAlignedBB_maxZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "f", "D");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.Jr", movingObjectPosition_class);
		movingObjectPosition_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(movingObjectPosition_class);

		movingObjectPosition_hitVec = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "c", "Lfpsmaster/JN;");
		movingObjectPosition_typeOfHit = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "a", "Lfpsmaster/Jr$a;");
		movingObjectPosition_blockPos = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "e", "Lfpsmaster/JG;");
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.JN", vec3_class);
		vec3_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(vec3_class);

		//nullptr below 3 fields
		vec3_xCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "b", "D");
		vec3_yCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "c", "D");
		vec3_zCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "d", "D");
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.ys", inventoryPlayer_class);
		inventoryPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(inventoryPlayer_class);

		inventoryPlayer_getCurrentItem = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "f", "()Lfpsmaster/Bi;");
		inventoryPlayer_getStackInSlot = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "l", "(I)Lfpsmaster/Bi;");

		inventoryPlayer_mainInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "a", "Lfpsmaster/Ir;");

		inventoryPlayer_armorInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "b", "Lfpsmaster/Ir;");
		inventoryPlayer_currentItem = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "d", "I");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.Bi", itemStack_class);
		itemStack_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemStack_class);

		itemStack_getItem = Java::GetInstance()->Env->GetMethodID(itemStack_class, "b", "()Lfpsmaster/zK;");
		itemStack_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemStack_class, "getDestroySpeed", "(Lfpsmaster/fu;)F");//nullptr
	}
	{
		Java::GetInstance()->AssignClass("fpsmaster.zK", item_class);
		item_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(item_class);

		item_getIdFromItem = Java::GetInstance()->Env->GetMethodID(item_class, "a", "(Lfpsmaster/zK;)I"); // nullptr
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.zO", itemArmor_Class);
		itemArmor_Class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemArmor_Class);

		itemArmor_getColor = Java::GetInstance()->Env->GetMethodID(itemArmor_Class, "j", "(Lfpsmaster/Bi;)I");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.Bl", itemTool_class);
		itemTool_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemTool_class);

		itemTool_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemTool_class, "a", "(Lfpsmaster/Bi;Lfpsmaster/fu;)F");
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.JG", blockPos_class);
		blockPos_constructor = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::GetInstance()->Env->GetFieldID(blockPos_class, "x", "I");
		blockPos_y = Java::GetInstance()->Env->GetFieldID(blockPos_class, "y", "I");
		blockPos_z = Java::GetInstance()->Env->GetFieldID(blockPos_class, "z", "I");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.bF", block_class);
		block_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(block_class);

		block_getIdFromBlock = Java::GetInstance()->Env->GetStaticMethodID(block_class, "a", "(Lfpsmaster/bF;)I");
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.fq", blockState_class);
		blockState_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockState_class);

		blockState_block = Java::GetInstance()->Env->GetFieldID(blockState_class, "c", "Lfpsmaster/bF;");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.fu", iBlockState_class);
		iBlockState_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(iBlockState_class);

		iBlockState_getBlock = Java::GetInstance()->Env->GetMethodID(iBlockState_class, "h", "()Lfpsmaster/bF;");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.bG", blockAir_class);
		blockAir_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockAir_class);
	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.wM", entityItem_class);
		entityItem_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityItem_class);
	}


	{
		Java::GetInstance()->AssignClass("fpsmaster.Ir", nonNullList_class);
		nonNullList_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(nonNullList_class);

		nonNullList_List = Java::GetInstance()->Env->GetFieldID(nonNullList_class, "a", "Ljava/util/List;");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.GU", tileEntity_class);
		tileEntity_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(tileEntity_class);

		tileEntity_getPos = Java::GetInstance()->Env->GetMethodID(tileEntity_class, "k", "()Lfpsmaster/JG;");

	}

	{
		Java::GetInstance()->AssignClass("fpsmaster.GX", tileEntityBed_class);
		tileEntityBed_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(tileEntityBed_class);
	}
}