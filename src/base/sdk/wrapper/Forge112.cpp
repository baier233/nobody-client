#include "../StrayCache.h"


void StrayCache::Load112ForgeMap() {
	std::cout << "1.12.2 Forge" << std::endl;
	{
		Java::GetInstance()->AssignClass("net.minecraft.client.Minecraft", minecraft_class);
		minecraft_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(minecraft_class);

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
		minecraft_getNetHandler = Java::GetInstance()->Env->GetMethodID(minecraft_class, "func_147114_u", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
		minecraft_getMinecraft = Java::GetInstance()->Env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
		minecraft_getRenderViewEntity = Java::GetInstance()->Env->GetMethodID(minecraft_class, "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
		minecraft_clickMouse = Java::GetInstance()->Env->GetMethodID(minecraft_class, "func_147116_af", "()V");
		minecraft_getDebugFPS = Java::GetInstance()->Env->GetMethodID(minecraft_class, "func_175610_ah", "()I");

		minecraft_thePlayer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
		minecraft_theWorld = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
		minecraft_playerController = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
		minecraft_renderManager = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
		minecraft_timer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");

		if (minecraft_gameSettings == nullptr)
		{
			minecraft_gameSettings = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
		}

		if (minecraft_ingameGUI == nullptr)
		{
			minecraft_ingameGUI = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71456_v", "Lnet/minecraft/client/gui/GuiIngame;");
		}

		minecraft_currentScreen = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
		minecraft_objectMouseOver = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/math/RayTraceResult;");
		minecraft_rightClickDelayTimer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "field_71467_ac", "I");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
		gamesettings_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(gamesettings_class);

		gamesettings_setOptionKeyBinding = Java::GetInstance()->Env->GetMethodID(gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
		gamesettings_thirdPersonView = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "field_74320_O", "I");
		gamesettings_fovSetting = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "field_74334_X", "F");
		gamesettings_gammaSetting = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "field_74333_Y", "F");
		gamesettings_keyBindFullscreen = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
		gamesettings_keyBindSneak = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
		keybind_pressed = Java::GetInstance()->Env->GetFieldID(keybind_class, "field_74513_e", "Z");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
		netHandlerPlayClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(netHandlerPlayClient_class);

		netHandlerPlayClient_getPlayerInfo = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "func_175102_a", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");

		netHandlerPlayClient_addToSendQueue = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
		guiIngame_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiIngame_class);

		guiIngame_getTabList = Java::GetInstance()->Env->GetMethodID(guiIngame_class, "func_175181_h", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
		guiPlayerTabOverlay_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiPlayerTabOverlay_class);

		guiPlayerTabOverlay_getPlayerName = Java::GetInstance()->Env->GetMethodID(guiPlayerTabOverlay_class, "func_175243_a", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.Entity", entity_class);
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

				//std::cout << "Desc:" << sign << " Name:" << name << std::endl;
				if (std::string(name).find("NaC") != -1)
				{
					//std::cout << "find" << std::endl;
					//entity_ticksExisted = fields[i];
				}
			}
		}


		entity_getName = Java::GetInstance()->Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
		entity_isSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "func_70093_af", "()Z");
		entity_setSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "func_70095_a", "(Z)V");
		entity_setPosition = Java::GetInstance()->Env->GetMethodID(entity_class, "func_70107_b", "(DDD)V");
		entity_setSprint = Java::GetInstance()->Env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
		entity_isInvisible = Java::GetInstance()->Env->GetMethodID(entity_class, "func_82150_aj", "()Z");
		entity_inWater = Java::GetInstance()->Env->GetMethodID(entity_class, "func_70090_H", "()Z");
		entity_getUniqueID = Java::GetInstance()->Env->GetMethodID(entity_class, "func_110124_au", "()Ljava/util/UUID;");

		entity_posX = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70165_t", "D");
		entity_posY = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70163_u", "D");
		entity_posZ = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70161_v", "D");
		entity_lastTickPosX = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70142_S", "D");
		entity_lastTickPosY = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70137_T", "D");
		entity_lastTickPosZ = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70136_U", "D");
		entity_width = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70130_N", "F");
		entity_height = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70131_O", "F");
		entity_distanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70140_Q", "F");
		entity_prevDistanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70141_P", "F");
		entity_rotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70177_z", "F");
		entity_rotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70125_A", "F");
		entity_prevRotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70126_B", "F");
		entity_prevRotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70127_C", "F");
		entity_boundingBox = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/math/AxisAlignedBB;");
		entity_motionX = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70159_w", "D");
		entity_motionY = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70181_x", "D");
		entity_motionZ = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70179_y", "D");
		entity_onGround = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70122_E", "Z");
		entity_fallDistance = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70143_R", "F");
		if (entity_ticksExisted == nullptr)
		{
			entity_ticksExisted = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70173_aa", "I");
		}
		//entity_ticksExisted = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70173_aa", "F");
		entity_isDead = Java::GetInstance()->Env->GetFieldID(entity_class, "field_70128_L", "Z");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
		playerControllerMP_attackEntity = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
		playerControllerMP_sendUseItem = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
		entityLivingBase_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityLivingBase_class);

		entityLivingBase_getHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
		entityLivingBase_getMaxHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
		entityLivingBase_canEntityBeSeen = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
		entityLivingBase_isPlayerSleeping = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "func_70608_bn", "()Z");
		entityLivingBase_swingItem = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
		entityLivingBase_jump = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "func_70664_aZ", "()V");

		entityLivingBase_hurttime = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "field_70737_aN", "I");
		entityLivingBase_moveForward = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "field_70701_bs", "F");
		entityLivingBase_moveStrafe = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
		entityPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayer_class);

		entityPlayer_isBlocking = Java::GetInstance()->Env->GetMethodID(entityPlayer_class, "func_184605_cv", "()I");

		entityPlayer_inventory = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayerSP_class);

		entityPlayerSP_sendQueue = Java::GetInstance()->Env->GetFieldID(entityPlayerSP_class, "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
		activeRenderInfo_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(activeRenderInfo_class);
		activeRenderInfo_VIEWPORT = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "field_178814_a", "Ljava/nio/IntBuffer;");
		activeRenderInfo_PROJECTION = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "field_178813_c", "Ljava/nio/FloatBuffer;");
		activeRenderInfo_MODELVIEW = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "field_178812_b", "Ljava/nio/FloatBuffer;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
		renderManager_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(renderManager_class);

		renderManager_renderPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "field_78725_b", "D");
		renderManager_renderPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "field_78726_c", "D");
		renderManager_renderPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "field_78723_d", "D");
		renderManager_viewerPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "field_78730_l", "D");
		renderManager_viewerPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "field_78731_m", "D");
		renderManager_viewerPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "field_78728_n", "D");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
		worldClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(worldClient_class);

		worldClient_entityList = Java::GetInstance()->Env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.world.World", world_class);
		world_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(world_class);

		world_rayTraceBlocks = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "func_147447_a", "(Lnet/minecraft/util/math/Vec3d;Lnet/minecraft/util/math/Vec3d;ZZZ)Lnet/minecraft/util/math/RayTraceResult;");
		world_getBlockState = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "func_180495_p", "(Lnet/minecraft/util/math/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
		world_isAirBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "func_175623_d", "(Lnet/minecraft/util/math/BlockPos;)Z");
		world_getChunkFromChunkCoords = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");

		world_playerEntities = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "field_73010_i", "Ljava/util/List;");
		world_loadedEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "field_72996_f", "Ljava/util/List;");
		world_loadedTileEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "field_147482_g", "Ljava/util/List;");
	}

	/*
	不存在
	*/
	{
		Java::GetInstance()->AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
		chunk_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(chunk_class);

		//chunk_getBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
	}



	{
		Java::GetInstance()->AssignClass("net.minecraft.util.Timer", timer_class);
		timer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(timer_class);

		timer_timerSpeed = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "field_194149_e", "F");//猜的
		timer_renderPartialTicks = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "field_194147_b", "F");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.AxisAlignedBB", axisAlignedBB_class);
		axisAlignedBB_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(axisAlignedBB_class);

		axisAlignedBB_minX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
		axisAlignedBB_minY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
		axisAlignedBB_minZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
		axisAlignedBB_maxX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
		axisAlignedBB_maxY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
		axisAlignedBB_maxZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
	}
	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.RayTraceResult", movingObjectPosition_class);
		movingObjectPosition_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(movingObjectPosition_class);

		movingObjectPosition_hitVec = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/math/Vec3d;");
		movingObjectPosition_typeOfHit = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/math/RayTraceResult$Type;");
		movingObjectPosition_blockPos = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/util/math/BlockPos;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.Vec3d", vec3_class);
		vec3_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(vec3_class);

		vec3_xCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "field_72450_a", "D");
		vec3_yCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "field_72448_b", "D");
		vec3_zCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "field_72449_c", "D");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
		inventoryPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(inventoryPlayer_class);

		inventoryPlayer_getCurrentItem = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
		inventoryPlayer_getStackInSlot = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "func_70301_a", "(I)Lnet/minecraft/item/ItemStack;");


		inventoryPlayer_mainInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "field_70462_a", "Lnet/minecraft/util/NonNullList;");
		inventoryPlayer_armorInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "field_70460_b", "Lnet/minecraft/util/NonNullList;");
		inventoryPlayer_currentItem = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemStack", itemStack_class);
		itemStack_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemStack_class);

		itemStack_getItem = Java::GetInstance()->Env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
		itemStack_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemStack_class, "func_150997_a", "(Lnet/minecraft/block/state/IBlockState;)F");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.item.Item", item_class);

		item_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(item_class);
		item_getIdFromItem = Java::GetInstance()->Env->GetMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
		itemArmor_Class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemArmor_Class);

		itemArmor_getColor = Java::GetInstance()->Env->GetMethodID(itemArmor_Class, "func_82814_b", "(Lnet/minecraft/item/ItemStack;)I");
	}

	/*
	* 找不到
	*/
	{
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemTool", itemTool_class);
		itemTool_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemTool_class);

		//itemTool_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemTool_class, "func_150893_a", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/Block;)F");
	}

	{
		//引用
		Java::GetInstance()->AssignClass("net.minecraft.util.math.BlockPos", blockPos_class);
		blockPos_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockPos_class);
		blockPos_constructor = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::GetInstance()->Env->GetFieldID(blockPos_class, "field_177962_a", "I");
		blockPos_y = Java::GetInstance()->Env->GetFieldID(blockPos_class, "field_177960_b", "I");
		blockPos_z = Java::GetInstance()->Env->GetFieldID(blockPos_class, "field_177961_c", "I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.Block", block_class);
		block_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(block_class);

		block_getIdFromBlock = Java::GetInstance()->Env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.state.BlockStateContainer", blockState_class);
		blockState_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockState_class);

		blockState_block = Java::GetInstance()->Env->GetFieldID(blockState_class, "field_177627_c", "Lnet/minecraft/block/Block;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
		iBlockState_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(iBlockState_class);

		iBlockState_getBlock = Java::GetInstance()->Env->GetMethodID(iBlockState_class, "func_177230_c", "()Lnet/minecraft/block/Block;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.BlockAir", blockAir_class);
		blockAir_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockAir_class);
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.util.NonNullList", nonNullList_class);
		nonNullList_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(nonNullList_class);

		nonNullList_List = Java::GetInstance()->Env->GetFieldID(nonNullList_class, "field_191198_a", "Ljava/util/List;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.item.EntityItem", entityItem_class);
		entityItem_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityItem_class);
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.tileentity.TileEntity", tileEntity_class);
		tileEntity_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(tileEntity_class);

		tileEntity_getPos = Java::GetInstance()->Env->GetMethodID(tileEntity_class, "func_174877_v", "()Lnet/minecraft/util/math/BlockPos;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.tileentity.TileEntityBed", tileEntityBed_class);
		tileEntityBed_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(tileEntityBed_class);
	}
}