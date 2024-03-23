#include "../StrayCache.h"

void StrayCache::Load189VanillaMap() {
	{
		Java::GetInstance()->AssignClass("ave", minecraft_class);
		minecraft_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(minecraft_class);
		Logger::Init();


		minecraft_gameSettings = Java::GetInstance()->Env->GetFieldID(minecraft_class, "t", "Lavh;");
		minecraft_getMinecraft = Java::GetInstance()->Env->GetStaticMethodID(minecraft_class, "A", "()Lave;");
		minecraft_getRenderViewEntity = Java::GetInstance()->Env->GetMethodID(minecraft_class, "ac", "()Lpk;");
		minecraft_clickMouse = Java::GetInstance()->Env->GetMethodID(minecraft_class, "aw", "()V");
		minecraft_getDebugFPS = Java::GetInstance()->Env->GetMethodID(minecraft_class, "ai", "()I");

		minecraft_mc = Java::GetInstance()->Env->GetStaticFieldID(minecraft_class, "S", "Lave;");
		minecraft_thePlayer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "h", "Lbew;");
		minecraft_theWorld = Java::GetInstance()->Env->GetFieldID(minecraft_class, "f", "Lbdb;");
		minecraft_playerController = Java::GetInstance()->Env->GetFieldID(minecraft_class, "c", "Lbda;");
		minecraft_renderManager = Java::GetInstance()->Env->GetFieldID(minecraft_class, "aa", "Lbiu;");
		minecraft_timer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "Y", "Lavl;");

		minecraft_currentScreen = Java::GetInstance()->Env->GetFieldID(minecraft_class, "m", "Laxu;");
		minecraft_objectMouseOver = Java::GetInstance()->Env->GetFieldID(minecraft_class, "s", "Lauh;");
		minecraft_rightClickDelayTimer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "ap", "I");

	}

	{
		Java::GetInstance()->AssignClass("avh", gamesettings_class);
		gamesettings_setOptionKeyBinding = Java::GetInstance()->Env->GetMethodID(gamesettings_class, "a", "(Lavb;I)V");
		gamesettings_thirdPersonView = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "aB", "I");
		gamesettings_fovSetting = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "aI", "F");
		gamesettings_gammaSetting = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "aJ", "F");
		gamesettings_keyBindFullscreen = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "aq", "Lavb;");
		gamesettings_keyBindSneak = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "ad", "Lavb;");

	}

	{
		Java::GetInstance()->AssignClass("bhw", keybind_class);
		keybind_pressed = Java::GetInstance()->Env->GetFieldID(keybind_class, "i", "Z");
	}


	{
		Java::GetInstance()->AssignClass("bcy", netHandlerPlayClient_class);
		netHandlerPlayClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(netHandlerPlayClient_class);

		netHandlerPlayClient_getPlayerInfo = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "a", "(Ljava/util/UUID;)Lbdc;");
		netHandlerPlayClient_addToSendQueue = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "a", "(Lff;)V");

	}

	{
		Java::GetInstance()->AssignClass("avo", guiIngame_class);
		guiIngame_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiIngame_class);

		guiIngame_getTabList = Java::GetInstance()->Env->GetMethodID(guiIngame_class, "h", "()Lawh;");
	}

	{
		Java::GetInstance()->AssignClass("awh", guiPlayerTabOverlay_class);
		guiPlayerTabOverlay_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiPlayerTabOverlay_class);

		guiPlayerTabOverlay_getPlayerName = Java::GetInstance()->Env->GetMethodID(guiPlayerTabOverlay_class, "a", "(Lbdc;)Ljava/lang/String;");
	}



	{
		Java::GetInstance()->AssignClass("pk", entity_class);
		entity_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entity_class);

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


		entity_getName = Java::GetInstance()->Env->GetMethodID(entity_class, "e_", "()Ljava/lang/String;");
		entity_isSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "av", "()Z");
		entity_setSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "c", "(Z)V");
		entity_setPosition = Java::GetInstance()->Env->GetMethodID(entity_class, "b", "(DDD)V");
		entity_setSprint = Java::GetInstance()->Env->GetMethodID(entity_class, "d", "(Z)V");
		entity_isInvisible = Java::GetInstance()->Env->GetMethodID(entity_class, "ax", "()Z");
		entity_inWater = Java::GetInstance()->Env->GetMethodID(entity_class, "V", "()Z");
		entity_getUniqueID = Java::GetInstance()->Env->GetMethodID(entity_class, "aK", "()Ljava/util/UUID;");
		entity_posX = Java::GetInstance()->Env->GetFieldID(entity_class, "s", "D");
		entity_posY = Java::GetInstance()->Env->GetFieldID(entity_class, "t", "D");
		entity_posZ = Java::GetInstance()->Env->GetFieldID(entity_class, "u", "D");
		entity_lastTickPosX = Java::GetInstance()->Env->GetFieldID(entity_class, "P", "D");
		entity_lastTickPosY = Java::GetInstance()->Env->GetFieldID(entity_class, "Q", "D");
		entity_lastTickPosZ = Java::GetInstance()->Env->GetFieldID(entity_class, "R", "D");
		entity_width = Java::GetInstance()->Env->GetFieldID(entity_class, "J", "F");
		entity_height = Java::GetInstance()->Env->GetFieldID(entity_class, "K", "F");
		entity_distanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "M", "F");
		entity_prevDistanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "L", "F");
		entity_rotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "y", "F");
		entity_rotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "z", "F");
		entity_prevRotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "A", "F");
		entity_prevRotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "B", "F");
		entity_boundingBox = Java::GetInstance()->Env->GetFieldID(entity_class, "f", "Laug;");
		entity_motionX = Java::GetInstance()->Env->GetFieldID(entity_class, "v", "D");
		entity_motionY = Java::GetInstance()->Env->GetFieldID(entity_class, "w", "D");
		entity_motionZ = Java::GetInstance()->Env->GetFieldID(entity_class, "x", "D");
		entity_onGround = Java::GetInstance()->Env->GetFieldID(entity_class, "C", "Z");
		entity_fallDistance = Java::GetInstance()->Env->GetFieldID(entity_class, "O", "F");
		if (entity_ticksExisted == nullptr)
		{
			entity_ticksExisted = Java::GetInstance()->Env->GetFieldID(entity_class, "W", "I");
		}
		//entity_ticksExisted = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70173_aa", "F");
		entity_isDead = Java::GetInstance()->Env->GetFieldID(entity_class, "I", "Z");

	}

	{

		Java::GetInstance()->AssignClass("bda", playerControllerMP_class);
		playerControllerMP_attackEntity = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "a", "(Lwn;Lpk;)V");
		playerControllerMP_sendUseItem = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "a", "(Lwn;Ladm;Lzx;)Z");
	}


	{
		Java::GetInstance()->AssignClass("pr", entityLivingBase_class);
		entityLivingBase_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityLivingBase_class);

		entityLivingBase_getHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "bn", "()F");
		entityLivingBase_getMaxHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "bu", "()F");
		entityLivingBase_canEntityBeSeen = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "t", "(Lpk;)Z");
		entityLivingBase_isPlayerSleeping = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "bJ", "()Z");
		entityLivingBase_swingItem = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "bw", "()V");
		entityLivingBase_jump = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "bF", "()V");

		entityLivingBase_hurttime = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "au", "I");
		entityLivingBase_moveForward = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "ba", "F");
		entityLivingBase_moveStrafe = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "aZ", "F");

	}

	{
		Java::GetInstance()->AssignClass("wn", entityPlayer_class);
		entityPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayer_class);

		entityPlayer_isBlocking = Java::GetInstance()->Env->GetMethodID(entityPlayer_class, "bW", "()Z");

		entityPlayer_inventory = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->entityPlayer_class, "bi", "Lwm;");
	}

	{
		Java::GetInstance()->AssignClass("bew", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayerSP_class);

		entityPlayerSP_sendQueue = Java::GetInstance()->Env->GetFieldID(entityPlayerSP_class, "bew", "Lbcy;");
	}

	{
		Java::GetInstance()->AssignClass("auz", activeRenderInfo_class);
		activeRenderInfo_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(activeRenderInfo_class);

		activeRenderInfo_VIEWPORT = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "a", "Ljava/nio/IntBuffer;");
		activeRenderInfo_PROJECTION = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "c", "Ljava/nio/FloatBuffer;");
		activeRenderInfo_MODELVIEW = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "b", "Ljava/nio/FloatBuffer;");
	}

	{
		Java::GetInstance()->AssignClass("biu", renderManager_class);
		renderManager_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(renderManager_class);

		renderManager_renderPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "o", "D");
		renderManager_renderPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "p", "D");
		renderManager_renderPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "q", "D");
		renderManager_viewerPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "h", "D");
		renderManager_viewerPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "i", "D");
		renderManager_viewerPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "j", "D");
	}

	{
		Java::GetInstance()->AssignClass("bdb", worldClient_class);
		worldClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(worldClient_class);

		worldClient_entityList = Java::GetInstance()->Env->GetFieldID(worldClient_class, "c", "Ljava/util/Set;");

	}

	{
		Java::GetInstance()->AssignClass("adm", world_class);
		world_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(world_class);

		world_rayTraceBlocks = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "a", "(Laui;Laui;ZZZ)Lauh;");
		world_getBlockState = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "p", "(Lcj;)Lalz;");
		world_isAirBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "d", "(Lcj;)Z");
		world_getChunkFromChunkCoords = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "a", "(II)Lamy;");

		world_playerEntities = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "j", "Ljava/util/List;");
		world_loadedEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "f", "Ljava/util/List;");
	}

	{
		Java::GetInstance()->AssignClass("amy", chunk_class);
		chunk_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(chunk_class);

		chunk_getBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->chunk_class, "a", "(III)Lafh;");
	}

	{
		Java::GetInstance()->AssignClass("avl", timer_class);
		timer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(timer_class);

		timer_timerSpeed = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "d", "F");
		timer_renderPartialTicks = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "c", "F");

	}

	{
		Java::GetInstance()->AssignClass("aug", axisAlignedBB_class);
		axisAlignedBB_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(axisAlignedBB_class);

		axisAlignedBB_minX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "a", "D");
		axisAlignedBB_minY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "b", "D");
		axisAlignedBB_minZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "c", "D");
		axisAlignedBB_maxX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "d", "D");
		axisAlignedBB_maxY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "e", "D");
		axisAlignedBB_maxZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "f", "D");
	}

	{
		Java::GetInstance()->AssignClass("auh", movingObjectPosition_class);
		movingObjectPosition_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(movingObjectPosition_class));

		movingObjectPosition_hitVec = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "c", "Laui;");
		movingObjectPosition_typeOfHit = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "a", "Lauh$a;");
		movingObjectPosition_blockPos = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "e", "Lcj;");
	}

	{
		Java::GetInstance()->AssignClass("aui", vec3_class);
		vec3_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(vec3_class));
		vec3_xCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "a", "D");
		vec3_yCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "b", "D");
		vec3_zCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "c", "D");
	}

	{
		Java::GetInstance()->AssignClass("wm", inventoryPlayer_class);
		inventoryPlayer_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(inventoryPlayer_class));

		inventoryPlayer_getCurrentItem = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "h", "()Lzx;");
		inventoryPlayer_getStackInSlot = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "a", "(I)Lzx;");

		inventoryPlayer_mainInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "a", "[Lzx;");
		inventoryPlayer_armorInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "b", "[Lzx;");
		inventoryPlayer_currentItem = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "c", "I");
	}

	{
		Java::GetInstance()->AssignClass("zx", itemStack_class);
		itemStack_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(itemStack_class));

		itemStack_getItem = Java::GetInstance()->Env->GetMethodID(itemStack_class, "b", "()Lzw;");
		itemStack_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemStack_class, "a", "(Lafh;)F");
	}

	{
		Java::GetInstance()->AssignClass("zw", item_class);

		item_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(item_class));
		item_getIdFromItem = Java::GetInstance()->Env->GetMethodID(item_class, "b", "(Lzw;)I");
	}

	{
		Java::GetInstance()->AssignClass("yj", itemArmor_Class);
		itemArmor_Class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(itemArmor_Class));

		itemArmor_getColor = Java::GetInstance()->Env->GetMethodID(itemArmor_Class, "b", "(Lzx;)I");
	}

	{
		Java::GetInstance()->AssignClass("za", itemTool_class);
		itemTool_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(itemTool_class));

		itemTool_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemTool_class, "a", "(Lzx;Lafh;)F ");
	}

	{
		Java::GetInstance()->AssignClass("cj", blockPos_class);
		blockPos_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(blockPos_class));
		blockPos_constructor = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::GetInstance()->Env->GetFieldID(blockPos_class, "a", "I");
		blockPos_y = Java::GetInstance()->Env->GetFieldID(blockPos_class, "c", "I");
		blockPos_z = Java::GetInstance()->Env->GetFieldID(blockPos_class, "d", "I");
	}

	{
		Java::GetInstance()->AssignClass("afh", block_class);
		block_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(block_class));

		block_getIdFromBlock = Java::GetInstance()->Env->GetStaticMethodID(block_class, "a", "(Lafh;)I");
	}

	{
		Java::GetInstance()->AssignClass("ama", blockState_class);
		blockState_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(blockState_class));

		blockState_block = Java::GetInstance()->Env->GetFieldID(blockState_class, "c", "Lafh;");

	}

	{
		Java::GetInstance()->AssignClass("alz", iBlockState_class);
		iBlockState_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(iBlockState_class));

		iBlockState_getBlock = Java::GetInstance()->Env->GetMethodID(iBlockState_class, "c", "()Lafh;");
		//iBlockState_getBlockFromBlockState = Java::GetInstance()->Env->GetMethodID(iBlockState_class, "c", "()Lafh;");

	}

	{
		Java::GetInstance()->AssignClass("aey", blockAir_class);
		blockAir_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(blockAir_class));
	}

	{
		Java::GetInstance()->AssignClass("uz", entityItem_class);
		entityItem_class = static_cast<jclass>(Java::GetInstance()->Env->NewGlobalRef(entityItem_class));
	}

}
