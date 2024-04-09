#include "../StrayCache.h"

void StrayCache::Load112MCPMap() {
	{
		Java::GetInstance()->AssignClass("net.minecraft.client.Minecraft", minecraft_class);
		minecraft_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(minecraft_class);

		minecraft_getNetHandler = Java::GetInstance()->Env->GetMethodID(minecraft_class, "getConnection", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
		minecraft_getMinecraft = Java::GetInstance()->Env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
		minecraft_getRenderViewEntity = Java::GetInstance()->Env->GetMethodID(minecraft_class, "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
		minecraft_clickMouse = Java::GetInstance()->Env->GetMethodID(minecraft_class, "clickMouse", "()V");
		minecraft_getDebugFPS = Java::GetInstance()->Env->GetMethodID(minecraft_class, "getDebugFPS", "()I");

		minecraft_thePlayer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "player", "Lnet/minecraft/client/entity/EntityPlayerSP;");
		minecraft_theWorld = Java::GetInstance()->Env->GetFieldID(minecraft_class, "world", "Lnet/minecraft/client/multiplayer/WorldClient;");
		minecraft_playerController = Java::GetInstance()->Env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
		minecraft_renderManager = Java::GetInstance()->Env->GetFieldID(minecraft_class, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
		minecraft_timer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
		minecraft_gameSettings = Java::GetInstance()->Env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
		minecraft_ingameGUI = Java::GetInstance()->Env->GetFieldID(minecraft_class, "ingameGUI", "Lnet/minecraft/client/gui/GuiIngame;");
		minecraft_currentScreen = Java::GetInstance()->Env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
		minecraft_objectMouseOver = Java::GetInstance()->Env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/math/RayTraceResult;");
		minecraft_rightClickDelayTimer = Java::GetInstance()->Env->GetFieldID(minecraft_class, "rightClickDelayTimer", "I");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
		gamesettings_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(gamesettings_class);

		gamesettings_setOptionKeyBinding = Java::GetInstance()->Env->GetMethodID(gamesettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
		gamesettings_thirdPersonView = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "thirdPersonView", "I");
		gamesettings_fovSetting = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "fovSetting", "F");
		gamesettings_gammaSetting = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "gammaSetting", "F");
		gamesettings_keyBindFullscreen = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->gamesettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
		gamesettings_keyBindSneak = Java::GetInstance()->Env->GetFieldID(gamesettings_class, "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");

	}
	{
		Java::GetInstance()->AssignClass("net.minecraft.client.settings.KeyBinding", keybind_class);
		keybind_pressed = Java::GetInstance()->Env->GetFieldID(keybind_class, "pressed", "Z");
	}
	{
		Java::GetInstance()->AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
		netHandlerPlayClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(netHandlerPlayClient_class);

		netHandlerPlayClient_getPlayerInfo = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "getPlayerInfo", "(Ljava/util/UUID;)Lnet/minecraft/client/network/NetworkPlayerInfo;");

		netHandlerPlayClient_addToSendQueue = Java::GetInstance()->Env->GetMethodID(netHandlerPlayClient_class, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.gui.GuiIngame", guiIngame_class);
		guiIngame_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiIngame_class);

		guiIngame_getTabList = Java::GetInstance()->Env->GetMethodID(guiIngame_class, "getTabList", "()Lnet/minecraft/client/gui/GuiPlayerTabOverlay;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.gui.GuiPlayerTabOverlay", guiPlayerTabOverlay_class);
		guiPlayerTabOverlay_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(guiPlayerTabOverlay_class);

		guiPlayerTabOverlay_getPlayerName = Java::GetInstance()->Env->GetMethodID(guiPlayerTabOverlay_class, "getPlayerName", "(Lnet/minecraft/client/network/NetworkPlayerInfo;)Ljava/lang/String;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.Entity", entity_class);
		entity_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entity_class);

		entity_getName = Java::GetInstance()->Env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
		entity_isSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "isSneaking", "()Z");
		entity_setPosition = Java::GetInstance()->Env->GetMethodID(entity_class, "setPosition", "(DDD)V");
		entity_setSneaking = Java::GetInstance()->Env->GetMethodID(entity_class, "setSneaking", "(Z)V");
		entity_isInvisible = Java::GetInstance()->Env->GetMethodID(entity_class, "isInvisible", "()Z");
		entity_inWater = Java::GetInstance()->Env->GetMethodID(entity_class, "isInWater", "()Z");
		entity_getUniqueID = Java::GetInstance()->Env->GetMethodID(entity_class, "getUniqueID", "()Ljava/util/UUID;");

		entity_posX = Java::GetInstance()->Env->GetFieldID(entity_class, "posX", "D");
		entity_posY = Java::GetInstance()->Env->GetFieldID(entity_class, "posY", "D");
		entity_posZ = Java::GetInstance()->Env->GetFieldID(entity_class, "posZ", "D");
		entity_lastTickPosX = Java::GetInstance()->Env->GetFieldID(entity_class, "lastTickPosX", "D");
		entity_lastTickPosY = Java::GetInstance()->Env->GetFieldID(entity_class, "lastTickPosY", "D");
		entity_lastTickPosZ = Java::GetInstance()->Env->GetFieldID(entity_class, "lastTickPosZ", "D");
		entity_width = Java::GetInstance()->Env->GetFieldID(entity_class, "width", "F");
		entity_height = Java::GetInstance()->Env->GetFieldID(entity_class, "height", "F");
		entity_distanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "distanceWalkedModified", "F");
		entity_prevDistanceWalkedModified = Java::GetInstance()->Env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
		entity_rotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "rotationYaw", "F");
		entity_rotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "rotationPitch", "F");
		entity_prevRotationYaw = Java::GetInstance()->Env->GetFieldID(entity_class, "prevRotationYaw", "F");
		entity_prevRotationPitch = Java::GetInstance()->Env->GetFieldID(entity_class, "prevRotationPitch", "F");
		entity_boundingBox = Java::GetInstance()->Env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/math/AxisAlignedBB;");
		entity_motionX = Java::GetInstance()->Env->GetFieldID(entity_class, "motionX", "D");
		entity_motionY = Java::GetInstance()->Env->GetFieldID(entity_class, "motionY", "D");
		entity_motionZ = Java::GetInstance()->Env->GetFieldID(entity_class, "motionZ", "D");
		entity_onGround = Java::GetInstance()->Env->GetFieldID(entity_class, "onGround", "Z");
		entity_fallDistance = Java::GetInstance()->Env->GetFieldID(entity_class, "fallDistance", "F");
		entity_isDead = Java::GetInstance()->Env->GetFieldID(entity_class, "isDead", "Z");
		entity_ticksExisted = Java::GetInstance()->Env->GetFieldID(entity_class, "ticksExisted", "I");//nullptr

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
		playerControllerMP_attackEntity = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
		playerControllerMP_sendUseItem = Java::GetInstance()->Env->GetMethodID(playerControllerMP_class, "sendUseItem", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");//nullptr
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
		entityLivingBase_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityLivingBase_class);

		entityLivingBase_getHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
		entityLivingBase_getMaxHealth = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
		entityLivingBase_canEntityBeSeen = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
		entityLivingBase_isPlayerSleeping = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "isPlayerSleeping", "()Z");
		entityLivingBase_hurttime = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "hurtTime", "I");
		entityLivingBase_moveForward = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "moveForward", "F");
		entityLivingBase_moveStrafe = Java::GetInstance()->Env->GetFieldID(entityLivingBase_class, "moveStrafing", "F");
		entityLivingBase_swingItem = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");//nullptr
		entityLivingBase_jump = Java::GetInstance()->Env->GetMethodID(entityLivingBase_class, "jump", "()V");
	}



	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
		entityPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayer_class);

		entityPlayer_isBlocking = Java::GetInstance()->Env->GetMethodID(entityPlayer_class, "getItemInUseCount", "()I");//nullptr

		entityPlayer_inventory = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityPlayerSP_class);
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
		activeRenderInfo_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(activeRenderInfo_class);
		activeRenderInfo_VIEWPORT = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "VIEWPORT", "Ljava/nio/IntBuffer;");
		activeRenderInfo_PROJECTION = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "PROJECTION", "Ljava/nio/FloatBuffer;");
		activeRenderInfo_MODELVIEW = Java::GetInstance()->Env->GetStaticFieldID(activeRenderInfo_class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
		renderManager_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(renderManager_class);


		renderManager_renderPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "renderPosX", "D");
		renderManager_renderPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "renderPosY", "D");
		renderManager_renderPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "renderPosZ", "D");
		renderManager_viewerPosX = Java::GetInstance()->Env->GetFieldID(renderManager_class, "viewerPosX", "D");
		renderManager_viewerPosY = Java::GetInstance()->Env->GetFieldID(renderManager_class, "viewerPosY", "D");
		renderManager_viewerPosZ = Java::GetInstance()->Env->GetFieldID(renderManager_class, "viewerPosZ", "D");
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
		worldClient_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(worldClient_class);

		worldClient_entityList = Java::GetInstance()->Env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.world.World", world_class);
		world_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(world_class);

		world_rayTraceBlocks = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "rayTraceBlocks", "(Lnet/minecraft/util/math/Vec3d;Lnet/minecraft/util/math/Vec3d;ZZZ)Lnet/minecraft/util/math/RayTraceResult;");
		world_getChunkFromChunkCoords = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "getChunkFromChunkCoords", "(II)Lnet/minecraft/world/chunk/Chunk;");//nullptr
		world_getBlockState = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "getBlockState", "(Lnet/minecraft/util/math/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
		world_isAirBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->world_class, "isAirBlock", "(Lnet/minecraft/util/math/BlockPos;)Z");

		world_playerEntities = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "playerEntities", "Ljava/util/List;");
		world_loadedEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "loadedEntityList", "Ljava/util/List;");
		world_loadedTileEntityList = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->world_class, "loadedTileEntityList", "Ljava/util/List;");
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
		chunk_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(chunk_class);

		//chunk_getBlock = Java::GetInstance()->Env->GetMethodID(StrayCache::GetInstance()->chunk_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.util.Timer", timer_class);
		timer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(timer_class);

		timer_timerSpeed = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "tickLength", "F");
		timer_renderPartialTicks = Java::GetInstance()->Env->GetFieldID(StrayCache::GetInstance()->timer_class, "renderPartialTicks", "F");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.AxisAlignedBB", axisAlignedBB_class);
		axisAlignedBB_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(axisAlignedBB_class);

		axisAlignedBB_minX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "minX", "D");
		axisAlignedBB_minY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "minY", "D");
		axisAlignedBB_minZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "minZ", "D");
		axisAlignedBB_maxX = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "maxX", "D");
		axisAlignedBB_maxY = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "maxY", "D");
		axisAlignedBB_maxZ = Java::GetInstance()->Env->GetFieldID(axisAlignedBB_class, "maxZ", "D");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.RayTraceResult", movingObjectPosition_class);
		movingObjectPosition_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(movingObjectPosition_class);

		movingObjectPosition_hitVec = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/math/Vec3d;");
		movingObjectPosition_typeOfHit = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/math/RayTraceResult$Type;");
		movingObjectPosition_blockPos = Java::GetInstance()->Env->GetFieldID(movingObjectPosition_class, "blockPos", "Lnet/minecraft/util/math/BlockPos;");
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.Vec3d", vec3_class);
		vec3_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(vec3_class);

		//nullptr below 3 fields
		vec3_xCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "xCoord", "D");
		vec3_yCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "yCoord", "D");
		vec3_zCoord = Java::GetInstance()->Env->GetFieldID(vec3_class, "zCoord", "D");
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
		inventoryPlayer_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(inventoryPlayer_class);

		inventoryPlayer_getCurrentItem = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
		inventoryPlayer_getStackInSlot = Java::GetInstance()->Env->GetMethodID(inventoryPlayer_class, "getStackInSlot", "(I)Lnet/minecraft/item/ItemStack;");

		inventoryPlayer_mainInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "mainInventory", "Lnet/minecraft/util/NonNullList;");

		inventoryPlayer_armorInv = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "armorInventory", "Lnet/minecraft/util/NonNullList;");
		inventoryPlayer_currentItem = Java::GetInstance()->Env->GetFieldID(inventoryPlayer_class, "currentItem", "I");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemStack", itemStack_class);
		itemStack_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemStack_class);

		itemStack_getItem = Java::GetInstance()->Env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
		itemStack_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemStack_class, "getDestroySpeed", "(Lnet/minecraft/block/state/IBlockState;)F");
	}
	{
		Java::GetInstance()->AssignClass("net.minecraft.item.Item", item_class);
		item_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(item_class);

		item_getIdFromItem = Java::GetInstance()->Env->GetMethodID(item_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I"); // nullptr
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
		itemArmor_Class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemArmor_Class);

		itemArmor_getColor = Java::GetInstance()->Env->GetMethodID(itemArmor_Class, "getColor", "(Lnet/minecraft/item/ItemStack;)I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemTool", itemTool_class);
		itemTool_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(itemTool_class);

		itemTool_getStrVsBlock = Java::GetInstance()->Env->GetMethodID(itemTool_class, "getDestroySpeed", "(Lnet/minecraft/item/ItemStack;Lnet/minecraft/block/state/IBlockState;)F");
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.util.math.BlockPos", blockPos_class);
		blockPos_constructor = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
		blockPos_constructorI = Java::GetInstance()->Env->GetMethodID(blockPos_class, "<init>", "(III)V");
		blockPos_x = Java::GetInstance()->Env->GetFieldID(blockPos_class, "x", "I");
		blockPos_y = Java::GetInstance()->Env->GetFieldID(blockPos_class, "y", "I");
		blockPos_z = Java::GetInstance()->Env->GetFieldID(blockPos_class, "z", "I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.Block", block_class);
		block_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(block_class);

		block_getIdFromBlock = Java::GetInstance()->Env->GetStaticMethodID(block_class, "getIdFromBlock", "(Lnet/minecraft/block/Block;)I");
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.state.BlockStateContainer", blockState_class);
		blockState_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockState_class);

		blockState_block = Java::GetInstance()->Env->GetFieldID(blockState_class, "block", "Lnet/minecraft/block/Block;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
		iBlockState_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(iBlockState_class);

		iBlockState_getBlock = Java::GetInstance()->Env->GetMethodID(iBlockState_class, "getBlock", "()Lnet/minecraft/block/Block;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.block.BlockAir", blockAir_class);
		blockAir_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(blockAir_class);
	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.entity.item.EntityItem", entityItem_class);
		entityItem_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(entityItem_class);
	}


	{
		Java::GetInstance()->AssignClass("net.minecraft.util.NonNullList", nonNullList_class);
		nonNullList_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(nonNullList_class);

		nonNullList_List = Java::GetInstance()->Env->GetFieldID(nonNullList_class, "delegate", "Ljava/util/List;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.tileentity.TileEntity", tileEntity_class);
		tileEntity_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(tileEntity_class);

		tileEntity_getPos = Java::GetInstance()->Env->GetMethodID(tileEntity_class, "getPos", "()Lnet/minecraft/util/math/BlockPos;");

	}

	{
		Java::GetInstance()->AssignClass("net.minecraft.tileentity.TileEntityBed", tileEntityBed_class);
		tileEntityBed_class = (jclass)Java::GetInstance()->Env->NewGlobalRef(tileEntityBed_class);
	}
}