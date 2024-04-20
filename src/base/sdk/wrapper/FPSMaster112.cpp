#include "../StrayCache.h"

void StrayCache::LoadFPSMaster112Map() {
	{
		Java::AssignClass("fpsmaster.fm", minecraft_class);
		minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

		minecraft_getNetHandler = Java::Env->GetMethodID(minecraft_class, "D", "()Lfpsmaster/jY;");
		minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "d", "()Lfpsmaster/fm;");
		minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "ab", "()Lfpsmaster/tO;");
		minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "az", "()V");
		minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "h", "()I");

		minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "m", "Lfpsmaster/fJ;");
		minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "k", "Lfpsmaster/jS;");
		minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "h", "Lfpsmaster/jN;");
		minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "ar", "Lfpsmaster/nN;");
		minecraft_timer = Java::Env->GetFieldID(minecraft_class, "f", "Lfpsmaster/Ik;");
		minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "y", "Lfpsmaster/qN;");
		minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "v", "Lfpsmaster/gj;");
		minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "r", "Lfpsmaster/gJ;");
		minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "x", "Lfpsmaster/Jr;");
		minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "az", "I");

	}

	{
		Java::AssignClass("fpsmaster.qN", gamesettings_class);
		gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

		gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "a", "(Lfpsmaster/ri;I)V");
		gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "aE", "I");
		gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "aL", "F");
		gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "aM", "F");
		gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "av", "Lfpsmaster/ri;");
		gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "ah", "Lfpsmaster/ri;");

	}
	{
		Java::AssignClass("fpsmaster.ri", keybind_class);
		keybind_pressed = Java::Env->GetFieldID(keybind_class, "a", "Z");
	}
	{
		Java::AssignClass("fpsmaster.jY", netHandlerPlayClient_class);
		netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

		netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "a", "(Ljava/util/UUID;)Lfpsmaster/jY;");
		//这个好像没用
		//netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
	}

	{
		Java::AssignClass("fpsmaster.gj", guiIngame_class);
		guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

		guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "g", "()Lfpsmaster/gX;");
	}

	{
		Java::AssignClass("fpsmaster.gX", guiPlayerTabOverlay_class);
		guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

		guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "a", "(Lfpsmaster/ks;)Ljava/lang/String;");
	}

	{
		Java::AssignClass("fpsmaster.tO", entity_class);
		entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

		entity_getName = Java::Env->GetMethodID(entity_class, "h_", "()Ljava/lang/String;");
		entity_isSneaking = Java::Env->GetMethodID(entity_class, "Q", "()Z");
		entity_setPosition = Java::Env->GetMethodID(entity_class, "b", "(DDD)V");
		entity_setSneaking = Java::Env->GetMethodID(entity_class, "f", "(Z)V");
		entity_isInvisible = Java::Env->GetMethodID(entity_class, "bc", "()Z");
		entity_inWater = Java::Env->GetMethodID(entity_class, "av", "()Z");
		entity_getUniqueID = Java::Env->GetMethodID(entity_class, "bq", "()Ljava/util/UUID;");

		entity_posX = Java::Env->GetFieldID(entity_class, "v", "D");
		entity_posY = Java::Env->GetFieldID(entity_class, "w", "D");
		entity_posZ = Java::Env->GetFieldID(entity_class, "x", "D");
		entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "R", "D");
		entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "S", "D");
		entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "T", "D");
		entity_width = Java::Env->GetFieldID(entity_class, "L", "F");
		entity_height = Java::Env->GetFieldID(entity_class, "M", "F");
		entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "O", "F");
		entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "N", "F");
		entity_rotationYaw = Java::Env->GetFieldID(entity_class, "B", "F");
		entity_rotationPitch = Java::Env->GetFieldID(entity_class, "C", "F");
		entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "D", "F");
		entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "E", "F");
		entity_boundingBox = Java::Env->GetFieldID(entity_class, "bz", "Lfpsmaster/JF;");
		entity_motionX = Java::Env->GetFieldID(entity_class, "y", "D");
		entity_motionY = Java::Env->GetFieldID(entity_class, "z", "D");
		entity_motionZ = Java::Env->GetFieldID(entity_class, "A", "D");
		entity_onGround = Java::Env->GetFieldID(entity_class, "F", "Z");
		entity_fallDistance = Java::Env->GetFieldID(entity_class, "Q", "F");
		entity_isDead = Java::Env->GetFieldID(entity_class, "K", "Z");
		entity_ticksExisted = Java::Env->GetFieldID(entity_class, "X", "I");//nullptr

	}

	{
		Java::AssignClass("fpsmaster.jN", playerControllerMP_class);
		playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "attackEntity", "(Lfpsmaster/yp;Lfpsmaster/tO;)V");

		//草泥马能不能别写没调用的
		//playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "sendUseItem", "(Lfpsmaster/yp;Lnet/minecraft/world/World;Lfpsmaster/Bi;)Z");//nullptr
	}

	{
		Java::AssignClass("fpsmaster.ur", entityLivingBase_class);
		entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

		entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "cw", "()F");
		entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "cC", "()F");
		entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "z", "(Lfpsmaster/uh;)Z");
		entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "b_", "()Z");
		entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "aH", "I");
		entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "bb", "F");
		entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "ba", "F");
		//entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");//nullptr
		entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "cN", "()V");
	}



	{
		Java::AssignClass("fpsmaster.yp", entityPlayer_class);
		entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

		//entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "getItemInUseCount", "()I");//nullptr

		entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "bB", "Lfpsmaster/ys;");
	}

	{
		Java::AssignClass("fpsmaster.fJ", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
	}

	{
		Java::AssignClass("fpsmaster.lq", activeRenderInfo_class);
		activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
		activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "a", "Ljava/nio/IntBuffer;");
		activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "b", "Ljava/nio/FloatBuffer;");
		activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "c", "Ljava/nio/FloatBuffer;");
	}


	{
		Java::AssignClass("fpsmaster.nN", renderManager_class);
		renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);


		renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "m", "D");
		renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "n", "D");
		renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "o", "D");
		renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "h", "D");
		renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "i", "D");
		renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "g", "D");
	}


	{
		Java::AssignClass("fpsmaster.jS", worldClient_class);
		worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

		worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "d", "Ljava/util/Set;");
	}

	{
		Java::AssignClass("fpsmaster.KT", world_class);
		world_class = (jclass)Java::Env->NewGlobalRef(world_class);

		world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "rayTraceBlocks", "(Lfpsmaster/JN;Lfpsmaster/JN;ZZZ)Lfpsmaster/Jr;");
		world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "getChunkFromChunkCoords", "(II)Lfpsmaster/LQ;");//nullptr
		world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "getBlockState", "(Lfpsmaster/JG;)Lfpsmaster/fu;");
		world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "isAirBlock", "(Lfpsmaster/JG;)Z");

		world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "playerEntities", "Ljava/util/List;");
		world_loadedEntityList = Java::Env->GetFieldID(StrayCache::world_class, "loadedEntityList", "Ljava/util/List;");
		world_loadedTileEntityList = Java::Env->GetFieldID(StrayCache::world_class, "loadedTileEntityList", "Ljava/util/List;");
	}


	{
		Java::AssignClass("fpsmaster.LQ", chunk_class);
		chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

		//chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "getBlock", "(III)Lfpsmaster/bF;");
	}

	{
		Java::AssignClass("fpsmaster.ID", timer_class);
		timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

		timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "e", "F");
		timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "b", "F");

	}

	{
		Java::AssignClass("fpsmaster.JF", axisAlignedBB_class);
		axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

		axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "a", "D");
		axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "b", "D");
		axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "c", "D");
		axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "d", "D");
		axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "e", "D");
		axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "f", "D");
	}

	{
		Java::AssignClass("fpsmaster.Jr", movingObjectPosition_class);
		movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

		movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "c", "Lfpsmaster/JN;");
		movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "a", "Lfpsmaster/Jr$a;");
		movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "e", "Lfpsmaster/JG;");
	}


	{
		Java::AssignClass("fpsmaster.JN", vec3_class);
		vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

		//nullptr below 3 fields
		vec3_xCoord = Java::Env->GetFieldID(vec3_class, "b", "D");
		vec3_yCoord = Java::Env->GetFieldID(vec3_class, "c", "D");
		vec3_zCoord = Java::Env->GetFieldID(vec3_class, "d", "D");
	}


	{
		Java::AssignClass("fpsmaster.ys", inventoryPlayer_class);
		inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

		inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "f", "()Lfpsmaster/Bi;");
		inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "l", "(I)Lfpsmaster/Bi;");

		inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "a", "Lfpsmaster/Ir;");

		inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "b", "Lfpsmaster/Ir;");
		inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "d", "I");

	}

	{
		Java::AssignClass("fpsmaster.Bi", itemStack_class);
		itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

		itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "b", "()Lfpsmaster/zK;");
		itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "getDestroySpeed", "(Lfpsmaster/fu;)F");//nullptr
	}
	{
		Java::AssignClass("fpsmaster.zK", item_class);
		item_class = (jclass)Java::Env->NewGlobalRef(item_class);

		item_getIdFromItem = Java::Env->GetMethodID(item_class, "a", "(Lfpsmaster/zK;)I"); // nullptr
	}

	{
		Java::AssignClass("fpsmaster.zO", itemArmor_Class);
		itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

		itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "j", "(Lfpsmaster/Bi;)I");
	}

	{
		Java::AssignClass("fpsmaster.Bl", itemTool_class);
		itemTool_class = (jclass)Java::Env->NewGlobalRef(itemTool_class);

		itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "a", "(Lfpsmaster/Bi;Lfpsmaster/fu;)F");
	}


	{
		Java::AssignClass("fpsmaster.JG", blockPos_class);
		blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::Env->GetFieldID(blockPos_class, "x", "I");
		blockPos_y = Java::Env->GetFieldID(blockPos_class, "y", "I");
		blockPos_z = Java::Env->GetFieldID(blockPos_class, "z", "I");
	}

	{
		Java::AssignClass("fpsmaster.bF", block_class);
		block_class = (jclass)Java::Env->NewGlobalRef(block_class);

		block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "a", "(Lfpsmaster/bF;)I");
	}

	{
		Java::AssignClass("fpsmaster.fq", blockState_class);
		blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);

		blockState_block = Java::Env->GetFieldID(blockState_class, "c", "Lfpsmaster/bF;");

	}

	{
		Java::AssignClass("fpsmaster.fu", iBlockState_class);
		iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

		iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "h", "()Lfpsmaster/bF;");

	}

	{
		Java::AssignClass("fpsmaster.bG", blockAir_class);
		blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
	}

	{
		Java::AssignClass("fpsmaster.wM", entityItem_class);
		entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
	}


	{
		Java::AssignClass("fpsmaster.Ir", nonNullList_class);
		nonNullList_class = (jclass)Java::Env->NewGlobalRef(nonNullList_class);

		nonNullList_List = Java::Env->GetFieldID(nonNullList_class, "a", "Ljava/util/List;");

	}

	{
		Java::AssignClass("fpsmaster.GU", tileEntity_class);
		tileEntity_class = (jclass)Java::Env->NewGlobalRef(tileEntity_class);

		tileEntity_getPos = Java::Env->GetMethodID(tileEntity_class, "k", "()Lfpsmaster/JG;");

	}

	{
		Java::AssignClass("fpsmaster.GX", tileEntityBed_class);
		tileEntityBed_class = (jclass)Java::Env->NewGlobalRef(tileEntityBed_class);
	}
}