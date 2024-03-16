#include "../StrayCache.h"

void StrayCache::Load189VanillaMap() {
	{
		Java::AssignClass("ave", minecraft_class);
		minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);
		Logger::Init();


		minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "t", "Lavh;");
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
		movingObjectPosition_class = static_cast<jclass>(Java::Env->NewGlobalRef(movingObjectPosition_class));

		movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "c", "Laui;");
		movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "a", "Lauh$a;");
		movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "e", "Lcj;");
	}

	{
		Java::AssignClass("aui", vec3_class);
		vec3_class = static_cast<jclass>(Java::Env->NewGlobalRef(vec3_class));
		vec3_xCoord = Java::Env->GetFieldID(vec3_class, "a", "D");
		vec3_yCoord = Java::Env->GetFieldID(vec3_class, "b", "D");
		vec3_zCoord = Java::Env->GetFieldID(vec3_class, "c", "D");
	}

	{
		Java::AssignClass("wm", inventoryPlayer_class);
		inventoryPlayer_class = static_cast<jclass>(Java::Env->NewGlobalRef(inventoryPlayer_class));

		inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "h", "()Lzx;");
		inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "a", "(I)Lzx;");

		inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "a", "[Lzx;");
		inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "b", "[Lzx;");
		inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "c", "I");
	}

	{
		Java::AssignClass("zx", itemStack_class);
		itemStack_class = static_cast<jclass>(Java::Env->NewGlobalRef(itemStack_class));

		itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "b", "()Lzw;");
		itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "a", "(Lafh;)F");
	}

	{
		Java::AssignClass("zw", item_class);

		item_class = static_cast<jclass>(Java::Env->NewGlobalRef(item_class));
		item_getIdFromItem = Java::Env->GetMethodID(item_class, "b", "(Lzw;)I");
	}

	{
		Java::AssignClass("yj", itemArmor_Class);
		itemArmor_Class = static_cast<jclass>(Java::Env->NewGlobalRef(itemArmor_Class));

		itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "b", "(Lzx;)I");
	}

	{
		Java::AssignClass("za", itemTool_class);
		itemTool_class = static_cast<jclass>(Java::Env->NewGlobalRef(itemTool_class));

		itemTool_getStrVsBlock = Java::Env->GetMethodID(itemTool_class, "a", "(Lzx;Lafh;)F ");
	}

	{
		Java::AssignClass("cj", blockPos_class);
		blockPos_class = static_cast<jclass>(Java::Env->NewGlobalRef(blockPos_class));
		blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::Env->GetFieldID(blockPos_class, "a", "I");
		blockPos_y = Java::Env->GetFieldID(blockPos_class, "c", "I");
		blockPos_z = Java::Env->GetFieldID(blockPos_class, "d", "I");
	}

	{
		Java::AssignClass("afh", block_class);
		block_class = static_cast<jclass>(Java::Env->NewGlobalRef(block_class));

		block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "a", "(Lafh;)I");
	}

	{
		Java::AssignClass("ama", blockState_class);
		blockState_class = static_cast<jclass>(Java::Env->NewGlobalRef(blockState_class));

		blockState_block = Java::Env->GetFieldID(blockState_class, "c", "Lafh;");

	}

	{
		Java::AssignClass("alz", iBlockState_class);
		iBlockState_class = static_cast<jclass>(Java::Env->NewGlobalRef(iBlockState_class));

		iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "c", "()Lafh;");
		//iBlockState_getBlockFromBlockState = Java::Env->GetMethodID(iBlockState_class, "c", "()Lafh;");

	}

	{
		Java::AssignClass("aey", blockAir_class);
		blockAir_class = static_cast<jclass>(Java::Env->NewGlobalRef(blockAir_class));
	}

	{
		Java::AssignClass("uz", entityItem_class);
		entityItem_class = static_cast<jclass>(Java::Env->NewGlobalRef(entityItem_class));
	}

}
