#include "BlockESP.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdint>
#include <unordered_set>

BlockESP::BlockESP() : AbstractModule("BlockESP", Category::VISUAL, "BlockESP") {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
	this->addValue(IntType, m_Radius);
}

//BlockESP::r_chunk BlockESP::getChunk(double xCoord, double yCoord, double zCoord)
//{
//	std::unordered_set<int> blocksToFind = { 56, 14, 21, 129, 54, 130, 146 };
//	BlockESP::r_chunk result;
//	//TODO: value Delay
//	if (GetTickCount64() - timer >= espSettings.m_Delay) {
//		int radius = espSettings.m_Radius;
//		for (int x = -radius; x < radius; x++)
//		{
//			for (int y = -radius; y < radius; y++)
//			{
//				for (int z = -radius; z < radius; z++)
//				{
//					if ((yCoord + y) < 0 || (yCoord + y) > 255)
//						continue;
//
//					const int newX = xCoord + x;
//					const int newY = yCoord + y;
//					const int newZ = zCoord + z;
//					const auto blockObject = (Block*)BlockPos::GetBlock(Vec3D{ (double)newX, (double)newY, (double)newZ }, (jobject)theWorld, env);
//					const auto blockId = blockObject->GetID(env);
//					if (blockId == 0)
//						continue;
//
//					if (IsValidBlock(blockId, espSettings.blockList)) {
//						tmpList.push_back(std::make_pair(blockId, Vec3D{ myPos.x + x, myPos.y + y, myPos.z + z }));
//					}
//				}
//			}
//		}
//	}
//
//	//xCoord = (int)(xCoord / 16) * 16;
//	//zCoord = (int)(zCoord / 16) * 16;
//
//	//for (int x = xCoord; x < xCoord + 16; x++) {
//	//	for (int z = zCoord; z < zCoord + 16; z++) {
//	//		for (int y = 0; y < 255; y++) {
//	//			int block = SDK::Minecraft->theWorld->getBlock(x, y, z);
//	//			if (blocksToFind.count(block) > 0) {
//	//				r_block b;
//	//				b.posX = x;
//	//				b.posY = y;
//	//				b.posZ = z;
//	//				b.blockID = block;
//
//	//				getBlockColor(b.red, b.green, b.blue, block); // colors are passed by reference
//
//	//				result.blocks.push_back(b);
//	//			}
//	//		}
//	//	}
//	//}
//
//	return result;
//}

std::vector<float> BlockESP::structToVector(const Matrix& matrix)
{
	std::vector<float> result;
	result.reserve(16); // 预留足够的空间以容纳结构体的成员

	result.push_back(matrix.m00);
	result.push_back(matrix.m01);
	result.push_back(matrix.m02);
	result.push_back(matrix.m03);

	result.push_back(matrix.m10);
	result.push_back(matrix.m11);
	result.push_back(matrix.m12);
	result.push_back(matrix.m13);

	result.push_back(matrix.m20);
	result.push_back(matrix.m21);
	result.push_back(matrix.m22);
	result.push_back(matrix.m23);

	result.push_back(matrix.m30);
	result.push_back(matrix.m31);
	result.push_back(matrix.m32);
	result.push_back(matrix.m33);

	return result;
}

void BlockESP::getBlockColor(double& red, double& green, double& blue, int blockID) {
	switch (blockID) {
	case 1: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//stone				done
	}
	case 2: {
		{ red = 0.59f; green = 0.29f; blue = 0.00f; break; };//grass			done
	}
	case 3: {
		{ red = 0.59f; green = 0.29f; blue = 0.00f; break; };//dirt				done
	}
	case 4: {
		{ red = 0.30f; green = 0.30f; blue = 0.30f; break; };//cobblestone		done
	}
	case 5: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//planks			done
	}
	case 6: {
		{ red = 0.81f; green = 0.45f; blue = 0.00f; break; };//sapling			done
	}
	case 7: {
		{ red = 0.00f; green = 0.00f; blue = 0.00f; break; };//bedrock			done
	}
	case 8: {
		{ red = 0.00f; green = 0.00f; blue = 0.90f; break; };//water flowing	done
	}
	case 9: {
		{ red = 0.00f; green = 0.00f; blue = 0.90f; break; };//water still		done
	}
	case 10: {
		{ red = 1.0f; green = 0.00f; blue = 0.00f; break; };//lava				done
	}
	case 11: {
		{ red = 1.0f; green = 0.00f; blue = 0.00f; break; };//lava				done
	}
	case 12: {
		{ red = 0.4f; green = 0.4f; blue = 0.00f; break; };//sand				done
	}
	case 13: {
		{ red = 0.2f; green = 0.18f; blue = 0.15f; break; };//gravel			done
	}
	case 14: {
		{ red = 1.0f; green = 1.0f; blue = 0.0f; break; };//gold ore			done
	}
	case 15: {
		{ red = 1.0f; green = 0.7f; blue = 0.7f; break; };//iron ore 		done
	}
	case 16: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//coal ore			done
	}
	case 17: {
		{ red = 0.65f; green = 0.33f; blue = 0.00f; break; };//wood block		done
	}
	case 18: {
		{ red = 0.00f; green = 0.7f; blue = 0.00f; break; };//leaves			done
	}
	case 19: {
		{ red = 0.86f; green = 0.86f; blue = 0.07f; break; };//sponge			done
	}
	case 20: {
		{ red = 1.0f; green = 1.0f; blue = 1.0f; break; };//glass			done
	}
	case 21: {
		{ red = 0.0f; green = 0.4f; blue = 1.0f; break; };//lapis ore			done
	}
	case 22: {
		{ red = 0.0f; green = 0.4f; blue = 1.0f; break; };//lapis block 		done
	}
	case 23: {
		{ red = 0.31f; green = 0.27f; blue = 0.18f; break; };//dispenser		done
	}
	case 24: {
		{ red = 0.7f; green = 0.7f; blue = 0.00f; break; };//sandstone			done
	}
	case 25: {
		{ red = 0.52f; green = 0.41f; blue = 0.06f; break; };//note block		done
	}
	case 26: {
		{ red = 1.00f; green = 0.1f; blue = 0.1f; break; };//bed				done
	}
	case 27: {
		{ red = 0.5f; green = 0.00f; blue = 0.00f; break; };//powered rail		done
	}
	case 28: {
		{ red = 0.5f; green = 0.00f; blue = 0.00f; break; };//detector rail		done
	}
	case 29: {
		{ red = 0.5f; green = 0.5f; blue = 0.40f; break; };//sticky pison		done
	}
	case 30: {
		{ red = 1.0f; green = 1.0f; blue = 1.00f; break; };//cobweb				done
	}
	case 31: {
		{ red = 0.2f; green = 0.7f; blue = 0.2f; break; };//grass/fern			done
	}
	case 32: {
		{ red = 0.7f; green = 0.7f; blue = 0.30f; break; };//dead bush			done
	}
	case 33: {
		{ red = 0.5f; green = 0.5f; blue = 0.40f; break; };//piston				done
	}
	case 34: {
		{ red = 0.5f; green = 0.5f; blue = 0.40f; break; };//piston head		done
	}
	case 35: {
		{ red = 1.0f; green = 1.0f; blue = 1.00f; break; };//wool				done
	}
	case 36: {
		{ red = 0.9f; green = 0.9f; blue = 0.00f; break; };//there is no 36?
	}
	case 37: {
		{ red = 0.9f; green = 0.9f; blue = 0.00f; break; };//yellow flower		done
	}
	case 38: {
		{ red = 0.9f; green = 0.9f; blue = 0.9f; break; };//other flowers		done
	}
	case 39: {
		{ red = 0.4f; green = 0.3f; blue = 0.3f; break; };//brown mushroom		done
	}
	case 40: {
		{ red = 0.9f; green = 0.9f; blue = 0.00f; break; };//red mushroom		done
	}
	case 41: {
		{ red = 1.0f; green = 1.0f; blue = 0.0f; break; }; //gold block		done
	}
	case 42: {
		{ red = 1.0f; green = 0.5f; blue = 0.5f; break; }; //iron block		done
	}
	case 43: {
		{ red = 0.7f; green = 0.7f; blue = 0.7f; break; };//slab				done
	}
	case 44: {
		{ red = 0.7f; green = 0.7f; blue = 0.00f; break; };//sandstone slab		done
	}
	case 45: {
		{ red = 0.7f; green = 0.0f; blue = 0.00f; break; };//bricks				done
	}
	case 46: {
		{ red = 1.00f; green = 0.3f; blue = 0.00f; break; };//tnt				done
	}
	case 47: {
		{ red = 0.65f; green = 0.33f; blue = 0.00f; break; };//bookshelf		done
	}
	case 48: {
		{ red = 0.2f; green = 0.8f; blue = 0.20f; break; };//moss stone			done
	}
	case 49: {
		{ red = 0.17f; green = 0.1f; blue = 0.15f; break; };//obsidian			done
	}
	case 50: {
		{ red = 0.9f; green = 0.9f; blue = 0.6f; break; };//torch				done
	}
	case 51: {
		{ red = 1.0f; green = 0.00f; blue = 0.00f; break; };//fire				done
	}
	case 52: {
		{ red = 0.0f; green = 1.f; blue = 0.00f; break; };//spawner				done
	}
	case 53: {
		{ red = 0.7f; green = 0.3f; blue = 0.0f; break; };//oak stairs		done
	}
	case 54: {
		{ red = 1.0f; green = 1.f; blue = 0.0f; break; };// chest				done
	}
	case 55: {
		{ red = 0.7f; green = 0.0f; blue = 0.00f; break; };//redstone dust		done
	}
	case 56: {
		{ red = 0.0f; green = 1.0f; blue = 1.0f; break; };//diamond ore 		done
	}
	case 57: {
		{ red = 0.0f; green = 0.7f; blue = 0.7f; break; }; //diamond block	done
	}
	case 58: {
		{ red = 0.6f; green = 0.4f; blue = 0.0f; break; };//crafting table	done
	}
	case 59: {
		{ red = 1.00f; green = 1.00f; blue = 1.00f; break; };//wheat crops		done
	}
	case 60: {
		{ red = 0.59f; green = 0.29f; blue = 0.00f; break; };//farmland			done
	}
	case 61: {
		{ red = 0.17f; green = 0.14f; blue = 0.10f; break; };//furnace			done
	}
	case 62: {
		{ red = 0.17f; green = 0.14f; blue = 0.10f; break; };//furnace			done
	}
	case 63: {
		{ red = 0.8f; green = 0.6f; blue = 0.0f; break; };//sign				done
	}
	case 64: {
		{ red = 0.8f; green = 0.6f; blue = 0.0f; break; };//oak wood door		done
	}
	case 65: {
		{ red = 0.8f; green = 0.6f; blue = 0.0f; break; };//ladder			done
	}
	case 66: {
		{ red = 0.5f; green = 0.00f; blue = 0.00f; break; };//rail				done
	}
	case 67: {
		{ red = 0.30f; green = 0.30f; blue = 0.30f; break; };//cobble stairs	done
	}
	case 68: {
		{ red = 0.8f; green = 0.6f; blue = 0.0f; break; };//sign				done
	}
	case 69: {
		{ red = 0.4f; green = 0.3f; blue = 0.0f; break; };//lever				done
	}
	case 70: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//stone plate		done
	}
	case 71: {
		{ red = 1.0f; green = 0.5f; blue = 0.5f; break; };//iron door			done
	}
	case 72: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood plate		done
	}
	case 73: {
		{ red = 1.0f; green = 0.3f; blue = 0.2f; break; };//redstone ore 	done
	}
	case 74: {
		{ red = 1.0f; green = 0.3f; blue = 0.2f; break; };//redstone ore 	done
	}
	case 75: {
		{ red = 0.7f; green = 0.0f; blue = 0.00f; break; };//redstone torch		done
	}
	case 76: {
		{ red = 0.7f; green = 0.0f; blue = 0.00f; break; };//redstone torch		done
	}
	case 77: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//stone button		done
	}
	case 78: {
		{ red = 1.0f; green = 1.0f; blue = 1.00f; break; };//snow layer				done
	}
	case 79: {
		{ red = 0.0f; green = 0.0f; blue = 1.00f; break; };//ice				done
	}
	case 80: {
		{ red = 1.0f; green = 1.0f; blue = 1.00f; break; };//snow block				done
	}
	case 81: {
		{ red = 0.0f; green = 0.7f; blue = 0.00f; break; };//cactus				done
	}
	case 82: {
		{ red = 0.34f; green = 0.19f; blue = 0.06f; break; };//clay				done
	}
	case 83: {
		{ red = 0.0f; green = 1.0f; blue = 0.00f; break; };//sugar cane			done
	}
	case 84: {
		{ red = 0.52f; green = 0.41f; blue = 0.06f; break; };//take his jukebox, fuck this kid.
	}
	case 85: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//oak fence		done
	}
	case 86: {
		{ red = 1.0f; green = 0.6f; blue = 0.00f; break; };//pumpkin			done
	}
	case 87: {
		{ red = 0.9f; green = 0.1f; blue = 0.00f; break; };//netherrack			done
	}
	case 88: {
		{ red = 0.21f; green = 0.15f; blue = 0.10f; break; };//soul sand		done
	}
	case 89: {
		{ red = 0.0f; green = 1.00f; blue = 0.00f; break; };//glowstone			done
	}
	case 90: {
		{ red = 0.20f; green = 0.05f; blue = 0.20f; break; };//nether portal	done
	}
	case 91: {
		{ red = 1.0f; green = 0.6f; blue = 0.00f; break; };//jack o lantern		done
	}
	case 92: {
		{ red = 1.0f; green = 1.0f; blue = 1.0f; break; };//cake						done
	}
	case 93: {
		{ red = 0.70f; green = 0.17f; blue = 0.06f; break; };//repeater			done
	}
	case 94: {
		{ red = 0.70f; green = 0.17f; blue = 0.06f; break; };//repeater			done
	}
	case 95: {
		{ red = 1.0f; green = 1.0f; blue = 1.00f; break; };//stained glass			done
	}
	case 96: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood trapdoor	done
	}
	case 97: {
		{ red = 0.3f; green = 0.3f; blue = 0.30f; break; };//silverfish-stone   done
	}
	case 98: {
		{ red = 0.3f; green = 0.3f; blue = 0.30f; break; };//stone bricks		done
	}
	case 99: {
		{ red = 0.7f; green = 0.7f; blue = 0.00f; break; };//mushroom block		done
	}
	case 100: {
		{ red = 0.7f; green = 0.7f; blue = 0.00f; break; };//mushroom block		done
	}
	case 101: {
		{ red = 0.8f; green = 0.8f; blue = 0.80f; break; };//iron bars			done
	}
	case 102: {
		{ red = 1.0f; green = 1.0f; blue = 1.00f; break; };//glass pane				done
	}
	case 103: {
		{ red = 0.1f; green = 1.0f; blue = 0.10f; break; };//melon block		done
	}
	case 104: {
		{ red = 0.2f; green = 0.2f; blue = 0.00f; break; };//pumpkin stem		done
	}
	case 105: {
		{ red = 0.2f; green = 0.2f; blue = 0.00f; break; };//melon stem			done
	}
	case 106: {
		{ red = 0.0f; green = 0.0f; blue = 0.50f; break; };//vines					done
	}
	case 107: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//oak fence gate	done
	}
	case 108: {
		{ red = 0.7f; green = 0.0f; blue = 0.00f; break; };//brick stairs		done
	}
	case 109: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//stone brick stairs done
	}
	case 110: {
		{ red = 0.4f; green = 0.4f; blue = 0.00f; break; };//Mycelium			done
	}
	case 111: {
		{ red = 0.0f; green = 0.0f; blue = 0.70f; break; };//lily pad				done
	}
	case 112: {
		{ red = 0.33f; green = 0.08f; blue = 0.03f; break; };//nether brick		done
	}
	case 113: {
		{ red = 0.33f; green = 0.08f; blue = 0.03f; break; };//nether fence		done
	}
	case 114: {
		{ red = 0.33f; green = 0.08f; blue = 0.03f; break; };//nether stairs	done
	}
	case 115: {
		{ red = 0.8f; green = 0.0f; blue = 0.00f; break; };//nether wart		done
	}
	case 116: {
		{ red = 0.0f; green = 0.0f; blue = 0.20f; break; };//enchant table		done
	}
	case 117: {
		{ red = 0.8f; green = 0.8f; blue = 0.00f; break; };//brewing stand		done
	}
	case 119: {
		{ red = 0.2f; green = 0.2f; blue = 0.20f; break; };//cauldron			done
	}
	case 120: {
		{ red = 0.7f; green = 0.7f; blue = 0.3f; break; };//end portal frame	done
	}
	case 121: {
		{ red = 0.7f; green = 0.7f; blue = 0.0f; break; };//end stone			done
	}
	case 122: {
		{ red = 0.0f; green = 0.0f; blue = 0.0f; break; };//dragon egg				done
	}
	case 123: {
		{ red = 0.7f; green = 0.1f; blue = 0.1f; break; };//redstone lamp		done
	}
	case 124: {
		{ red = 0.7f; green = 0.1f; blue = 0.1f; break; };//redstone lamp		done
	}
	case 125: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood slab		done
	}
	case 126: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood slab		done
	}
	case 127: {
		{ red = 0.5f; green = 0.5f; blue = 0.f; break; };//cocoa beans			done
	}
	case 128: {
		{ red = 0.7f; green = 0.7f; blue = 0.00f; break; };//sand stairs		done
	}
	case 129: {
		{ red = 0.2f; green = 1.0f; blue = 0.2f; break; };//emerald ore		done
	}
	case 130: {
		{ red = 0.33f; green = 0.f; blue = 0.33f; break; };//ender chest		done
	}
	case 131: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//tripwire hook	done
	}
	case 132: {
		{ red = 1.0f; green = 1.0f; blue = 1.0f; break; };//string					done
	}
	case 133: {
		{ red = 0.2f; green = 0.5f; blue = 0.2f; break; };//emerald block		done
	}
	case 134: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood stairs		done
	}
	case 135: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood stairs		done
	}
	case 136: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood stairs		done
	}
	case 137: {
		{ red = 1.0f; green = 1.0f; blue = 1.0f; break; };//command block				done
	}
	case 138: {
		{ red = 0.6f; green = 0.6f; blue = 1.0f; break; };//beacon				done
	}
	case 139: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//cobblestone wall	done
	}
	case 140: {
		{ red = 0.7f; green = 0.2f; blue = 0.2f; break; };//flower pot			done	
	}
	case 141: {
		{ red = 0.f; green = 1.f; blue = 0.f; break; };//carrots				done
	}
	case 142: {
		{ red = 0.f; green = 1.f; blue = 0.f; break; };//potatos				done
	}
	case 143: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//wood button		done
	}
	case 144: {
		{ red = 0.5f; green = 0.5f; blue = 0.5f; break; };//skull				done
	}
	case 145: {
		{ red = 0.1f; green = 0.1f; blue = 0.1f; break; };//anvil				done
	}
	case 146: {
		{ red = 1.0f; green = 0.f; blue = 0.0f; break; };//trapped chest		done
	}
	case 147: {
		{ red = 1.0f; green = 1.0f; blue = 0.f; break; };//gold plate				done
	}
	case 148: {
		{ red = 0.7f; green = 0.7f; blue = 0.7f; break; };//iron plate			done
	}
	case 149: {
		{ red = 0.4f; green = 0.4f; blue = 0.4f; break; };//comparator			done
	}
	case 150: {
		{ red = 0.4f; green = 0.4f; blue = 0.4f; break; };//comparator			done
	}
	case 151: {
		{ red = 0.5f; green = 0.1f; blue = 0.4f; break; };//daylight sensor		done
	}
	case 152: {
		{ red = 1.0f; green = 0.3f; blue = 0.2f; break; };//redstone block	done
	}
	case 153: {
		{ red = 1.0f; green = 0.5f; blue = 0.5f; break; };//quartz ore		done
	}
	case 154: {
		{ red = 0.2f; green = 0.2f; blue = 0.2f; break; };//hopper				done
	}
	case 155: {
		{ red = 1.f; green = 1.f; blue = 1.f; break; };//quartz block			done
	}
	case 156: {
		{ red = 1.f; green = 1.f; blue = 1.f; break; };//quartz stairs			done
	}
	case 157: {
		{ red = 05.f; green = 0.f; blue = 0.f; break; };//activator rail		done
	}
	case 158: {
		{ red = 0.31f; green = 0.27f; blue = 0.18f; break; };//dropper			done
	}
	case 159: {
		{ red = 1.f; green = 0.6f; blue = 0.1f; break; };//hardened clay		done
	}
	case 160: {
		{ red = 1.f; green = 1.f; blue = 1.f; break; };//stained glass pane		done
	}
	case 161: {
		{ red = 1.f; green = 0.7f; blue = 0.2f; break; };//acacia leaves		done
	}
	case 162: {
		{ red = 1.f; green = 0.7f; blue = 0.2f; break; };//acacia wood			done
	}
	case 163: {
		{ red = 1.f; green = 0.7f; blue = 0.2f; break; };//acacia stairs		done
	}
	case 164: {
		{ red = 0.f; green = 0.7f; blue = 0.f; break; };//oak wood stairs		done
	}
	case 165: {
		{ red = 0.f; green = 0.7f; blue = 0.f; break; };//slime block			done
	}
	case 166: {
		{ red = 0.7f; green = 0.0f; blue = 0.0f; break; };//barrier				done
	}
	case 167: {
		{ red = 0.9f; green = 0.9f; blue = 0.9f; break; };//iron trap door		done
	}
	case 168: {
		{ red = 0.05f; green = 0.1f; blue = 1.f; break; };//prismarine			done
	}
	case 169: {
		{ red = 0.7f; green = 0.7f; blue = 1.f; break; };//sea lantern			done
	}
	case 170: {
		{ red = 0.8f; green = 0.8f; blue = 0.f; break; };//hay bale				done
	}
	case 171: {
		{ red = 01.f; green = 01.f; blue = 01.f; break; };//carpet				done
	}
	case 172: {
		{ red = 0.7f; green = 0.7f; blue = 0.3f; break; };//hard clay			done
	}
	case 173: {
		{ red = 0.3f; green = 0.3f; blue = 0.3f; break; };//coal block		done
	}
	case 174: {
		{ red = 0.f; green = 0.f; blue = 01.f; break; };//packed ice			done
	}
	case 175: {
		{ red = 01.f; green = 01.f; blue = 01.f; break; };//double plant		done
	}
	case 176: {
		{ red = 01.f; green = 01.f; blue = 01.f; break; };//banner				done
	}
	case 177: {
		{ red = 01.f; green = 01.f; blue = 01.f; break; };//banner on block		done
	}
	case 178: {
		{ red = 01.f; green = 01.f; blue = 01.f; break; };//daylight sensor		done
	}
	case 179: {
		{ red = 01.f; green = 0.6f; blue = 0.f; break; };//red sandstone		done
	}
	case 180: {
		{ red = 1.f; green = 0.6f; blue = 0.f; break; };//red sandstone			done
	}
	case 181: {
		{ red = 1.f; green = 0.6f; blue = 0.f; break; };//red sandstone			done
	}
	case 182: {
		{ red = 1.f; green = 0.6f; blue = 0.f; break; };//red sandstone			done
	}
	case 183: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence gate		done
	}
	case 184: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence gate		done
	}
	case 186: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence gate		done
	}
	case 187: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence gate		done
	}
	case 188: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence			done
	}
	case 189: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence			done
	}
	case 190: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence			done
	}
	case 191: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence			done
	}
	case 192: {
		{ red = 0.91f; green = 0.45f; blue = 0.00f; break; };//fence			done
	}
	default: {
		{ red = 1.0f; green = 1.0f; blue = 1.0f; };
	}
	}
}

void BlockESP::GLRenderBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(red, green, blue, alpha);

	glBegin(GL_QUADS);//tell opengl your beginning to draw verticies


	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ);

	glVertex3f(minX, minY, maxZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);

	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);

	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, maxY, minZ);

	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ);

	glVertex3f(minX, maxY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);


	glEnd();//tell opengl your done drawing verticies

	glDisable(GL_BLEND);//turn the blending off 
}


BlockESP* BlockESP::getInstance() {
	static auto* inst = new BlockESP();
	return inst;
}

void BlockESP::onDisable() {
}

void BlockESP::render(HDC hdc)
{
	if (!this->getToggle())return;
	auto drawOutlinedBox = [](BoundingBox boundingBox)
		{
			glBegin(3);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
			glEnd();

			glBegin(3);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
			glEnd();

			glBegin(1);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
			glEnd();
		};
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->projection).data());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->modelView).data());

	glPushMatrix();
	glEnable(GL_LINE_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(false);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(1.f);

	auto GetColorFromId = [this](int id) {
		int idx = 0;
		while (this->blockList[idx] != 0x0) {
			unsigned char blockId = this->blockList[idx];
			if (id == blockId) {
				unsigned char r = this->blockList[idx] >> 24;
				unsigned char g = this->blockList[idx] >> 16;
				unsigned char b = this->blockList[idx] >> 8;
				return Vector3D((r * 1.f) / 255.f, (g * 1.f) / 255.f, (b * 1.f) / 255.f);
			}

			idx++;
		}

		return Vector3D(-1.f, -1.f, -1.f);
		};

	//const auto renderManager = SDK;
	for (const auto& bb : blockLists)
	{
		const auto blockId = bb.first;
		//const auto blockColor = GetColorFromId(blockId);
		//if (blockColor.x == -1.f)
		//	continue;

		Vector3D color{};
		this->getBlockColor(color.x, color.y, color.z, blockId);
		const auto renderPos = CommonData::getInstance()->renderPos;
		const auto xPos = (int)(bb.second.x) - renderPos.x;
		const auto yPos = (int)(bb.second.y) - renderPos.y + 3.4f;
		const auto zPos = (int)(bb.second.z) - renderPos.z;
		GLRenderBox(xPos, yPos, zPos, xPos + 1, yPos + 1, zPos + 1, color.x, color.y, color.z, 0.2f);
		//glColor4f(blockColor.x, blockColor.y, blockColor.z, 1.f);
	//drawOutlinedBox(BoundingBox{ static_cast<float>(xPos), static_cast<float>(yPos), static_cast<float>(zPos), static_cast<float>(xPos + 1), static_cast<float>(yPos + 1), static_cast<float>(zPos + 1) });
	}

	glDisable(GL_BLEND);
	glDepthMask(true);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glPopMatrix();

	glPopMatrix();
	/*RECT rcCli;
	GetClientRect(WindowFromDC(hdc), &rcCli);
	long nWidth = rcCli.right - rcCli.left;
	long nHeight = rcCli.bottom - rcCli.top;
	glViewport(0, 0, nWidth, nHeight);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->projection).data());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->modelView).data());

	for (const auto& pair : r_chunks) {
		const r_chunk& ch = pair.second;
		for (const r_block& bldm : ch.blocks) {
			GLRenderBox(bldm.posX - CommonData::getInstance()->renderPos.x, bldm.posY - CommonData::getInstance()->renderPos.y + 3.4f, bldm.posZ - CommonData::getInstance()->renderPos.z, bldm.posX - CommonData::getInstance()->renderPos.x + 1, bldm.posY - CommonData::getInstance()->renderPos.y + 4.4f, bldm.posZ - CommonData::getInstance()->renderPos.z + 1, bldm.red, bldm.green, bldm.blue, 0.2);
		}
	}

	glPopMatrix(); */
}

void BlockESP::RenderMenu()
{
	ImGui::BeginChild("BlockESP", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(46541, "Toggle BlockESP", this);
		ImGui::SliderInt("Radius", (int*)this->m_Radius->getPtr(), this->m_Radius->getMin(), this->m_Radius->getMax());
		//Menu::DoSliderStuff(45732343408, ", this->m_Radius->getPtr(), 0.1f, 15.f);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("BlockESP2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}

void BlockESP::onUpdate(EventUpdate e)
{
	if (!this->getToggle())return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	auto IsValidBlock = [](int id, const int* allowedBlocks)
		{
			int idx = 0;
			while (allowedBlocks[idx] != 0x0) {
				unsigned char blockId = allowedBlocks[idx];
				if (id == blockId)
					return true;

				idx++;
			}

			return false;
		};

	std::vector<std::pair<int, Vector3D>> tmpList;
	int radius = this->m_Radius->getValue();
	for (int x = -radius; x < radius; x++)
	{
		for (int y = -radius; y < radius; y++)
		{
			for (int z = -radius; z < radius; z++)
			{
				if ((SDK::Minecraft->thePlayer->GetPos().y + y) < 0 || (SDK::Minecraft->thePlayer->GetPos().y + y) > 255)
					continue;

				const int newX = SDK::Minecraft->thePlayer->GetPos().x + x;
				const int newY = SDK::Minecraft->thePlayer->GetPos().y + y;
				const int newZ = SDK::Minecraft->thePlayer->GetPos().z + z;
				const auto blockId = SDK::Minecraft->theWorld->getBlock((double)newX, (double)newY, (double)newZ);
				if (blockId == 0)
					continue;

				if (IsValidBlock(blockId, this->blockList)) {
					tmpList.push_back(std::make_pair(blockId, Vector3D{ SDK::Minecraft->thePlayer->GetPos().x + x, SDK::Minecraft->thePlayer->GetPos().y + y, SDK::Minecraft->thePlayer->GetPos().z + z }));
				}
			}
		}
	}
	blockLists = tmpList;
}

void BlockESP::onEnable() {
}