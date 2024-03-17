//Forge 1.18.1

#include "../StrayCache.h"

void StrayCache::Load1181ForgeMap() {
	std::cout << "1.18.1 Forge" << std::endl;
	{
		Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
		minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

		if (!Logger::Initialized)
			Logger::Init();

		minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "m_91087_", "()Lnet/minecraft/client/Minecraft;"); //getInstance
		//minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
		//minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "func_147116_af", "()V");
		//minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "func_175610_ah", "()I");

		minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "f_91074_", "Lnet/minecraft/client/player/LocalPlayer;"); //player
		minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "f_91073_", "Lnet/minecraft/client/multiplayer/ClientLevel;"); // level
		//minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
		//minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
		minecraft_timer = Java::Env->GetFieldID(minecraft_class, "f_90991_", "Lnet/minecraft/client/Timer;");
		minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "f_91066_", "Lnet/minecraft/client/Options;");

		/*
		if (minecraft_ingameGUI == nullptr)
		{
			minecraft_ingameGUI = Java::Env->GetFieldID(minecraft_class, "field_71456_v", "Lnet/minecraft/client/gui/GuiIngame;");
		}*/

		minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "f_91080_", "Lnet/minecraft/client/gui/screens/Screen;");
		minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "f_91077_", "Lnet/minecraft/world/phys/HitResult;");
		minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "f_91011_", "I");

	}

	{
		Java::AssignClass("net.minecraft.client.CameraType", cameraType_class);
		cameraType_class = (jclass)Java::Env->NewGlobalRef(cameraType_class);

		cameraType_isFirstPerson = Java::Env->GetMethodID(cameraType_class, "m_90612_", "()Z");
	}

	{
		Java::AssignClass("net.minecraft.client.Options", gamesettings_class);
		gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

		//gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
		//gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74320_O", "I");
		gamesettings_cameraType = Java::Env->GetFieldID(gamesettings_class, "f_92111_", "Lnet/minecraft/client/CameraType;");
		gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "f_92068_", "D");
		gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "f_92071_", "D");
		//gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
		//gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");

	}

	/*{
		Java::AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
		keybind_pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");
	}*/

	/*{
		Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
		netHandlerPlayClient_class = (jclass)Java::Env->NewGlobalRef(netHandlerPlayClient_class);

		netHandlerPlayClient_getPlayerInfo = Java::Env->GetMethodID(netHandlerPlayClient_class, "func_175102_a", "(Ljava/core/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");

		netHandlerPlayClient_addToSendQueue = Java::Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");

	}*/

	/*{
		Java::AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
		guiIngame_class = (jclass)Java::Env->NewGlobalRef(guiIngame_class);

		guiIngame_getTabList = Java::Env->GetMethodID(guiIngame_class, "func_175181_h", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
	}*/

	/*{
		Java::AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
		guiPlayerTabOverlay_class = (jclass)Java::Env->NewGlobalRef(guiPlayerTabOverlay_class);

		guiPlayerTabOverlay_getPlayerName = Java::Env->GetMethodID(guiPlayerTabOverlay_class, "func_175243_a", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
	}*/

	{
		Java::AssignClass("net.minecraft.world.entity.Entity", entity_class);
		entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);



		entity_getBBHeight = Java::Env->GetMethodID(entity_class, "m_20206_", "()F");
		//entity_getName = Java::Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
		entity_isSneaking = Java::Env->GetMethodID(entity_class, "m_6144_", "()Z");
		entity_setSneaking = Java::Env->GetMethodID(entity_class, "m_20260_", "(Z)V");
		entity_setPosition = Java::Env->GetMethodID(entity_class, "m_20343_", "(DDD)V"); //setPosRaw 
		entity_setSprint = Java::Env->GetMethodID(entity_class, "m_6858_", "(Z)V");
		entity_isInvisible = Java::Env->GetMethodID(entity_class, "m_20145_", "()Z");
		entity_inWater = Java::Env->GetMethodID(entity_class, "m_20069_", "()Z");
		//entity_getUniqueID = Java::Env->GetMethodID(entity_class, "func_110124_au", "()Ljava/core/UUID;");

		entity_position = Java::Env->GetFieldID(entity_class, "f_19825_", "Lnet/minecraft/world/phys/Vec3;");
		entity_eyeHeight = Java::Env->GetFieldID(entity_class, "f_19816_", "F");

		entity_posX = Java::Env->GetFieldID(entity_class, "f_19854_", "D");
		entity_posY = Java::Env->GetFieldID(entity_class, "f_19854_", "D");
		entity_posZ = Java::Env->GetFieldID(entity_class, "f_19854_", "D");
		entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "f_19790_", "D");
		entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "f_19791_", "D");
		entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "f_19792_", "D");
		//entity_width = Java::Env->GetFieldID(entity_class, "field_70130_N", "F");
		///entity_height = Java::Env->GetFieldID(entity_class, "field_70131_O", "F");
		//entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70140_Q", "F");
		//entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70141_P", "F");
		entity_rotationYaw = Java::Env->GetFieldID(entity_class, "f_19857_", "F");
		entity_rotationPitch = Java::Env->GetFieldID(entity_class, "f_19858_", "F");
		//entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "field_70126_B", "F");
		//entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "field_70127_C", "F");
		entity_boundingBox = Java::Env->GetFieldID(entity_class, "f_19828_", "Lnet/minecraft/world/phys/AABB;");
		entity_deltaMovement = Java::Env->GetFieldID(entity_class, "f_19827_", "Lnet/minecraft/world/phys/Vec3;");
		/*entity_motionX = Java::Env->GetFieldID(entity_class, "field_70159_w", "D");
		entity_motionY = Java::Env->GetFieldID(entity_class, "field_70181_x", "D");
		entity_motionZ = Java::Env->GetFieldID(entity_class, "field_70179_y", "D");*/
		entity_onGround = Java::Env->GetFieldID(entity_class, "f_19861_", "Z");
		//entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "F");
		//entity_isDead = Java::Env->GetFieldID(entity_class, "field_70128_L", "Z");

	}

	/*{
		Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
		playerControllerMP_attackEntity = Java::Env->GetMethodID(playerControllerMP_class, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
		playerControllerMP_sendUseItem = Java::Env->GetMethodID(playerControllerMP_class, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/world/item/ItemStack;)Z");
	}*/

	{
		Java::AssignClass("net.minecraft.world.entity.LivingEntity", entityLivingBase_class);
		entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

		entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "m_21223_", "()F");
		entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "m_21233_", "()F");
		entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "m_6779_", "(Lnet/minecraft/world/entity/LivingEntity;)Z");
		entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "m_5803_", "()Z");
		// entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
		entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "m_6135_", "()V");

		entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "f_20916_", "I");
		entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "f_20953_", "F");
		// entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");

	}

	{
		Java::AssignClass("net.minecraft.world.entity.player.Player", entityPlayer_class);
		entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

		//entityPlayer_isBlocking = Java::Env->GetMethodID(entityPlayer_class, "func_184605_cv", "()I");
		entityPlayer_getInventory = Java::Env->GetMethodID(entityPlayer_class, "m_150109_", "()Lnet/minecraft/world/entity/player/Inventory;");
	}

	{
		Java::AssignClass("net.minecraft.client.player.LocalPlayer", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
		localPlayer_xLast = Java::Env->GetFieldID(entityPlayerSP_class, "f_108595_", "D");
		localPlayer_yLast1 = Java::Env->GetFieldID(entityPlayerSP_class, "f_108596_", "D");
		localPlayer_zLast = Java::Env->GetFieldID(entityPlayerSP_class, "f_108597_", "D");
		
		
	}

	{
		Java::AssignClass("com.mojang.blaze3d.systems.RenderSystem", renderSystem_class);
		renderSystem_class = (jclass)Java::Env->NewGlobalRef(renderSystem_class);
		renderSystem_shader = Java::Env->GetStaticFieldID(renderSystem_class, "f_157144_", "Lnet/minecraft/client/renderer/ShaderInstance;");

	}

	{
		Java::AssignClass("net.minecraft.client.renderer.ShaderInstance", shaderInstance_class);
		shaderInstance_class = (jclass)Java::Env->NewGlobalRef(shaderInstance_class);
		shaderInstance_MODEL_VIEW_MATRIX = Java::Env->GetFieldID(shaderInstance_class, "f_173308_", "Lcom/mojang/blaze3d/shaders/Uniform;");
		shaderInstance_PROJECTION_MATRIX = Java::Env->GetFieldID(shaderInstance_class, "f_173309_", "Lcom/mojang/blaze3d/shaders/Uniform;");
	}


	{
		Java::AssignClass("com.mojang.blaze3d.shaders.Uniform", uniform_class);
		uniform_class = (jclass)Java::Env->NewGlobalRef(uniform_class);
		uniform_floatValues = Java::Env->GetFieldID(uniform_class, "f_85589_", "Ljava/nio/FloatBuffer;");
	}



	/*{
		Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
		activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
		activeRenderInfo_VIEWPORT = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178814_a", "Ljava/nio/IntBuffer;");
		activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178813_c", "Ljava/nio/FloatBuffer;");
		activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178812_b", "Ljava/nio/FloatBuffer;");
	}*/

	/*{
		Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
		renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);

		renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "field_78725_b", "D");
		renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "field_78726_c", "D");
		renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "field_78723_d", "D");
		renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "field_78730_l", "D");
		renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "field_78731_m", "D");
		renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "field_78728_n", "D");
	}*/

	{
		Java::AssignClass("net.minecraft.client.multiplayer.ClientLevel", clientLevel_class);
		clientLevel_class = (jclass)Java::Env->NewGlobalRef(clientLevel_class);
		clientLevel_players = Java::Env->GetFieldID(clientLevel_class, "f_104566_", "Ljava/util/List;");
		clientLevel_entitiesForRendering = Java::Env->GetMethodID(clientLevel_class, "m_104735_", "()Ljava/lang/Iterable;");
	}

	{
		Java::AssignClass("net.minecraft.world.level.Level", world_class);
		world_class = (jclass)Java::Env->NewGlobalRef(world_class);

		//world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "func_147447_a", "(Lnet/minecraft/core/math/Vec3d;Lnet/minecraft/core/math/Vec3d;ZZZ)Lnet/minecraft/core/math/RayTraceResult;");
		world_getBlockState = Java::Env->GetMethodID(StrayCache::world_class, "m_8055_", "(Lnet/minecraft/core/BlockPos;)Lnet/minecraft/world/level/block/state/BlockState;");
		//world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "func_175623_d", "(Lnet/minecraft/core/math/BlockPos;)Z");

	}






	{
		Java::AssignClass("net.minecraft.client.Timer", timer_class);
		timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

		timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "f_92518_", "F");

	}

	{
		Java::AssignClass("net.minecraft.world.phys.AABB", axisAlignedBB_class);
		axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

		axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "f_82288_", "D");
		axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "f_82289_", "D");
		axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "f_82290_", "D");
		axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "f_82291_", "D");
		axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "f_82292_", "D");
		axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "f_82293_", "D");
	}
	{
		Java::AssignClass("net.minecraft.world.phys.HitResult", movingObjectPosition_class);
		movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

		//movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/core/math/Vec3d;");
		hitResult_getType = Java::Env->GetMethodID(movingObjectPosition_class, "m_6662_", "()Lnet/minecraft/world/phys/HitResult$Type;");
		//movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/core/math/BlockPos;");
	}

	{
		Java::AssignClass("net.minecraft.world.phys.Vec3", vec3_class);
		vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

		vec3_xCoord = Java::Env->GetFieldID(vec3_class, "f_82479_", "D");
		vec3_yCoord = Java::Env->GetFieldID(vec3_class, "f_82480_", "D");
		vec3_zCoord = Java::Env->GetFieldID(vec3_class, "f_82481_", "D");
	}

	{
		Java::AssignClass("net.minecraft.world.entity.player.Inventory", inventoryPlayer_class);
		inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

		inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "m_36056_", "()Lnet/minecraft/world/item/ItemStack;");
		inventoryPlayer_getStackInSlot = Java::Env->GetMethodID(inventoryPlayer_class, "m_8020_", "(I)Lnet/minecraft/world/item/ItemStack;");


		inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "f_35974_", "Lnet/minecraft/core/NonNullList;");
		inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "f_35975_", "Lnet/minecraft/core/NonNullList;");
		inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "f_35977_", "I");
	}

	{
		Java::AssignClass("net.minecraft.world.item.ItemStack", itemStack_class);
		itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

		itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "m_41720_", "()Lnet/minecraft/world/item/Item;");
		itemStack_getStrVsBlock = Java::Env->GetMethodID(itemStack_class, "m_41691_", "(Lnet/minecraft/world/level/block/state/BlockState;)F");
	}

	{
		Java::AssignClass("net.minecraft.world.item.Item", item_class);

		item_class = (jclass)Java::Env->NewGlobalRef(item_class);
		//item_getIdFromItem = Java::Env->GetMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
	}

	{
		Java::AssignClass("net.minecraft.world.item.ArmorItem", itemArmor_Class);
		itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

		//itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "func_82814_b", "(Lnet/minecraft/world/item/ItemStack;)I");
	}
	{
		Java::AssignClass("net.minecraft.world.item.BlockItem", itemBlock_class);
		itemBlock_class = (jclass)Java::Env->NewGlobalRef(itemBlock_class);
	}

	{
		//ÒýÓÃ
		Java::AssignClass("net.minecraft.core.BlockPos", blockPos_class);
		blockPos_class = (jclass)Java::Env->NewGlobalRef(blockPos_class);
		blockPos_constructor = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::Env->GetFieldID(blockPos_class, "f_123285_", "I");
		blockPos_y = Java::Env->GetFieldID(blockPos_class, "f_123286_", "I");
		blockPos_z = Java::Env->GetFieldID(blockPos_class, "f_123289_", "I");
	}

	{
		Java::AssignClass("net.minecraft.world.level.block.Block", block_class);
		block_class = (jclass)Java::Env->NewGlobalRef(block_class);

		//block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
	}
	{
		Java::AssignClass("net.minecraft.world.level.block.state.BlockBehaviour$BlockStateBase", blockStateBase_class);
		blockStateBase_class = (jclass)Java::Env->NewGlobalRef(blockStateBase_class);

		blockStateBase_getBlock = Java::Env->GetMethodID(blockStateBase_class, "m_60734_", "()Lnet/minecraft/world/level/block/Block;");
		blockStateBase_isAir = Java::Env->GetMethodID(blockStateBase_class, "m_60795_", "()Z");
	}



	{
		Java::AssignClass("net.minecraft.world.level.block.state.BlockState", blockState_class);
		blockState_class = (jclass)Java::Env->NewGlobalRef(blockState_class);
	}

	//{
	//	Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
	//	iBlockState_class = (jclass)Java::Env->NewGlobalRef(iBlockState_class);

	//	iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "func_177230_c", "()Lnet/minecraft/block/Block;");

	//}

	{
		Java::AssignClass("net.minecraft.world.level.block.AirBlock", blockAir_class);
		blockAir_class = (jclass)Java::Env->NewGlobalRef(blockAir_class);
	}

	{
		Java::AssignClass("net.minecraft.core.NonNullList", nonNullList_class);
		nonNullList_class = (jclass)Java::Env->NewGlobalRef(nonNullList_class);

		nonNullList_List = Java::Env->GetFieldID(nonNullList_class, "f_122773_", "Ljava/core/List;");
	}

	Java::AssignClass("net.minecraft.world.entity.item.ItemEntity", entityItem_class);
	entityItem_class = (jclass)Java::Env->NewGlobalRef(entityItem_class);
}
