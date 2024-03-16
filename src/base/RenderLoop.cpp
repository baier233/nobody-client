#include "base.h"
#include "sdk/sdk.h"

#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/visual/HUD.h"
#include "moduleManager/modules/combat/aimAssist.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/clicker/LClick.h"
#include "moduleManager/modules/clicker/RClick.h"
#include "moduleManager/modules/player/eagle.h"
#include "moduleManager/modules/player/fastplace.h"
#include "moduleManager/modules/combat/velocity.h"
#include "moduleManager/modules/combat/killaura.h"
#include "moduleManager/modules/player/blink.h"
#include "moduleManager/modules/visual/Xray.h"
#include "moduleManager/modules/visual/fullbright.h"
#include "moduleManager/modules/visual/BlockESP.h"
#include "moduleManager/modules/visual/ChestESP.h"
#include "moduleManager/modules/visual/ItemESP.h"
#include <cmath>
#include "moduleManager/modules/player/blink.h"
//#include "extension/scripting.hpp"

#include "menu/menu.h"
#include "moduleManager/modules/combat/antibot.h"
#include "moduleManager/modules/combat/teams.h"
#include "moduleManager/ModuleManager.h"
#include "moduleManager/modules/player/scaffold.h"
#include "moduleManager/modules/player/autotool.h"

#include "menu/Notification/NotificationManager.h"
#include "moduleManager/modules/visual/BedESP.h"
extern ImVec4 clear_col;
static int y;
void Base::RenderLoop(HDC hdc) // Runs every frame
{
	if (!Base::Running) return;
	const char* watermark = "Nekoware";

	Esp::getInstance()->RenderUpdate();
	AimAssist::getInstance()->RenderUpdate();
	HUD::getInstance()->RenderUpdate();
	NotificationManager::getInstance().render();
	ChestESP::getInstance()->RenderUpdate();
	ItemESP::getInstance()->RenderUpdate();
	BlockESP::getInstance()->render(hdc);
	BedESP::getInstance()->RenderUpdate();
	//EventManager::getInstance().call(EventRender());
	//Blink::getInstance()->RenderUpdate();




}