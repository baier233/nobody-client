#include "esp.h"
#include "../../commonData.h"
#include "../../../sdk/sdk.h"
#include "../../../util/logger.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../util/math/math.h"
#include "../../../util/math/worldToScreen.h"
#include "../../../util/render/renderqolf.h"
#include "../../../menu/menu.h"
#include "../combat/antibot.h"
#include <gl/GL.h>



static void drawFilledBox(AxisAlignedBB_t boundingBox)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(255, 255, 255, 0.15f);
	glBegin(7);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glEnd();
	glBegin(7);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glEnd();
	glBegin(7);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glEnd();
	glBegin(7);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glEnd();
	glBegin(7);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glEnd();
	glBegin(7);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glEnd();
	glBegin(7);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glEnd();
	glDisable(GL_BLEND);//turn the blending off 
	glColor4f(255, 255, 255, 1);
}

static void drawOutlinedBox2(AxisAlignedBB_t boundingBox)
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
}
static void drawSelectionBoundingBox(AxisAlignedBB_t boundingBox)
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glEnd();
}



Esp::Esp() : AbstractModule("ESP", Category::VISUAL,"Entity perspective.") {
	this->addValue(FloatType, TextSizeValue);
	this->addValue(FloatType, FadeDistanceValue);
	this->addValue(BoolType, BoxValue);
	this->addValue(ColorType, BoxColorValue);
	this->addValue(BoolType, OutlineValue);
	this->addValue(ColorType, OutlineColorValue); 
	this->addValue(BoolType, FilledBoxValue);
	this->addValue(ColorType, FilledBoxColorValue);
	this->addValue(BoolType, TextOutlineValue);
	this->addValue(ColorType, TextOutlineColorValue);

	this->addValue(ColorType, TestCirclesColorValue);
	this->addValue(ColorType, TextColorValue);
	this->addValue(ColorType, SecondFilledBoxColorValue);

	this->addValue(BoolType, HealthBarValue);
	this->addValue(BoolType, TextValue);

	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Esp* Esp::getInstance() {
	static auto* inst = new Esp();
	return inst;
}

void Esp::onDisable() {
}

void Esp::onEnable() {
}

void Esp::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;


	//CWorld* world = SDK::Minecraft->theWorld;

	

	Vector3 renderPos = CommonData::getInstance()->renderPos;


	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;

	Vector3 pos = player->GetPos();

	// This is to fix the third person issue, there is still one issue with it.
	// When the camera collides in the wall or the ground, or something like that, the calculation fails entirely because the position is obviously not the same.
	if (this->espMode->getValue() == ESP3D) {
		List playerList = CommonData::getInstance()->playerEntities;
		auto list = playerList.toVector<CEntityPlayer>();
		float renderPartialTicks = 1;
		std::vector<AxisAlignedBB_t> newData;
		for (CEntityPlayer entity : list)
		{

			if (!entity.isValid() || entity.isNULL()) continue;

			if (entity.isEqualTo(player->getInstance())) continue;

			if (Antibot::getInstance()->getToggle() && Antibot::getInstance()->isBot(entity)) {
				continue;
			}
			Vector3 entityPos = entity.GetPos();
			Vector3 entityLastPos = entity.GetLastTickPos();
			//std::cout << "entityPos { X:" << entityPos.x << " Y:" << entityPos.y << " Z:" << entityPos.z << " }" << std::endl;
			//std::cout << "entityLastPos { X:" << entityLastPos.x << " Y:" << entityLastPos.y << " Z:" << entityLastPos.z << " }" << std::endl;
			if (this->espMode->getValue() == ESP3D)
			{
				auto playerBoundingBox = AxisAlignedBB_t(
					static_cast<float>((entityPos.x - 0.4f) - renderPos.x + -entityPos.x + entityLastPos.x + (entityPos.x - entityLastPos.x) * renderPartialTicks),
					static_cast<float>((entityPos.y - 0.1f) - renderPos.y + -entityPos.y + entityLastPos.y + (entityPos.y - entityLastPos.y) * renderPartialTicks),
					static_cast<float>((entityPos.z - 0.4f) - renderPos.z + -entityPos.z + entityLastPos.z + (entityPos.z - entityLastPos.z) * renderPartialTicks),
					static_cast<float>((entityPos.x + 0.4f) - renderPos.x + -entityPos.x + entityLastPos.x + (entityPos.x - entityLastPos.x) * renderPartialTicks),
					static_cast<float>((entityPos.y + 1.8f) - renderPos.y + -entityPos.y + entityLastPos.y + (entityPos.y - entityLastPos.y) * renderPartialTicks),
					static_cast<float>((entityPos.z + 0.4f) - renderPos.z + -entityPos.z + entityLastPos.z + (entityPos.z - entityLastPos.z) * renderPartialTicks)
				);
				newData.push_back(playerBoundingBox);
			}
		}
		renderData3D = newData;
		return;
	}


	if (CommonData::getInstance()->thirdPersonView != 0) {
		Vector2 angles = player->GetAngles();
		float distance = 8;
		if (CommonData::getInstance()->thirdPersonView == 2) {
			distance = -distance;
		}

		// This whole calculation came from gaspers source from their reach module, which you can find in this cheat as well
		float cos = std::cos(Math::degToRadiants(angles.x + 90.0f));
		float sin = std::sin(Math::degToRadiants(angles.x + 90.0f));
		float cosPitch = std::cos(Math::degToRadiants(angles.y));
		float sinPitch = std::sin(Math::degToRadiants(angles.y));

		float x = renderPos.x - (cos * distance * cosPitch);
		float y = renderPos.y + (distance * sinPitch);
		float z = renderPos.z - (sin * distance * cosPitch);

		// The raycast that is commented out below does not work that well for some reason, acts weirdly when colliding with chests, and other things.
		// Also might be poor in performance.
		//Vector3 ray = world->rayTraceBlocks(renderPos, Vector3{ x, y, z }, false, false, false);
		//renderPos = ray.x == 0 ? Vector3{ x,y,z } : ray;

		renderPos = Vector3{ x,y,z };
	}

	std::vector<Data> newData;
	List playerList = CommonData::getInstance()->playerEntities;
	auto list = playerList.toVector<CEntityPlayer>();
	float renderPartialTicks = CommonData::getInstance()->renderPartialTicks;
	//std::cout << "renderPartialTicks :" << renderPartialTicks << std::endl;
	//std::cout << "renderPos { X:" << renderPos.x << " Y:" << renderPos.y << " Z:" << renderPos.z << " }" << std::endl;

	for (CEntityPlayer entity : list)
	{

		if (!entity.isValid() || entity.isNULL()) continue;

		if (entity.isEqualTo(player->getInstance())) continue;
		
		if (Antibot::getInstance()->getToggle() && Antibot::getInstance()->isBot(entity)) {
			continue;
		}
		Vector3 entityPos = entity.GetPos();
		Vector3 entityLastPos = entity.GetLastTickPos();
		//std::cout << "entityPos { X:" << entityPos.x << " Y:" << entityPos.y << " Z:" << entityPos.z << " }" << std::endl;
		//std::cout << "entityLastPos { X:" << entityLastPos.x << " Y:" << entityLastPos.y << " Z:" << entityLastPos.z << " }" << std::endl;

		float entityWidth = 0.7f;
		float entityHeight;
		if (Base::version == FORGE_1_18_1)
		{
			entityHeight = (float)(entity.GetEyeHeight() / 2) + 0.2f;
		}
		else {
			entityHeight = (float)(entity.GetHeight() / 2) + 0.2f;
		}

		Vector3 diff = pos - entityPos;
		float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2)); // Sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
		// Regular distance check.
		if (dist > 300) {
			continue;
		}

		// You can't put one vector3 for fixing the jittering and use that to subtract all of them with it
		// it will mess screw up for some weird reason. Try it for yourself if you wish!
		//Vector3 fixedEntityPos{ entityLastPos + (entityLastPos - entityPos) * renderPartialTicks };

		// This stops the jittering, the calculations must be inverted for some reason from the original
		Vector3 origin{ renderPos - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // At the feet

		// Same with the offset of the point, it must be offset from the render position, not the entity position for some weird reason.
		Vector3 top{ (renderPos - Vector3{0, entityHeight * 2, 0}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // Over the head
		Vector3 left{ (renderPos - Vector3{entityWidth, entityHeight, 0}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the left
		Vector3 right{ (renderPos - Vector3{-entityWidth, entityHeight, 0}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the right
		Vector3 back{ (renderPos - Vector3{0, entityHeight, entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the back
		Vector3 front{ (renderPos - Vector3{0, entityHeight, -entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // And in the middle to the front

		entityWidth /= 1.388888;
		Vector3 left2{ (renderPos - Vector3{entityWidth, entityHeight, entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the left
		Vector3 right2{ (renderPos - Vector3{-entityWidth, entityHeight, -entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the right
		Vector3 back2{ (renderPos - Vector3{-entityWidth, entityHeight, entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the back
		Vector3 front2{ (renderPos - Vector3{entityWidth, entityHeight, -entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // And in the middle to the front

		// ^ This shapes a diamond like formation which results in 6 world to screens instead of 8.
		// However if a 3d ESP is desired, 8 world to screens would be required.

		// Another note for this data, is we cannot use the bounding box values because it can be changed by the reach module, so its best we make our own values with the cost
		// of consuming a little bit of resources for a bit of math.
		std::vector<Vector3> boxVerticies{
			origin, top, left, right, back, front, left2, right2,back2, front2
		};

		// For when the player gets close to an entity, a fade factor; a value between 0 and 1, with basic math, can get a cool looking fade effect if the player is too close
		// or inside the FadeDistance radius.
		float fadeFactor = 1.0f;
		if ((dist - 1) <= FadeDistanceValue->getValue())
			fadeFactor = ((dist - 1) / FadeDistanceValue->getValue());

		// To render the distance value under the ESP box.
		char distC[32];
		std::snprintf(distC, sizeof(distC), "%.1f", dist);
		std::string distS(distC);
		
		// Then finally taking all the data we acquired for this loop and pushing it to the data list.
		newData.push_back(Data{
			boxVerticies, // Box data
			entity.GetName(), // Entity name
			distS + "m", // Distance
			dist, // Real distance value (for fade)
			fadeFactor, // Fade factor
			entity.GetHealth(), // Entity health
			entity.GetMaxHealth(), // And max health (for health bar)
			});
	}

	renderData = newData;
}

void Esp::RenderUpdate()
{
	if (!this->getToggle() || !CommonData::getInstance()->dataUpdated) return;

	if (this->espMode->getValue() == ESP3D)
	{
		if (Base::version != FORGE_1_18_1) glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(structToVector(CommonData::getInstance()->projection).data());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(structToVector(CommonData::getInstance()->modelView).data());

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glLineWidth(2.0f);
		glDisable(GL_TEXTURE_2D);

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glEnable(GL_LINE_SMOOTH);

		for (AxisAlignedBB_t &bb : renderData3D)
		{
			if (Base::version != FORGE_1_18_1)
			{
				bb.maxY += 3.5;
				bb.minY += 3.5;
			}
			if (this->esp3DMode->getValue() == FILLED)
			{
				
				drawFilledBox(bb);
			}
			else if (this->esp3DMode->getValue() == OUTLINE)
			{

				glColor4d(102.0, 0.0, 153.0, 0.5);
				drawOutlinedBox2(bb);
			}
		}
		glDisable(GL_LINE_SMOOTH);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		if (Base::version != FORGE_1_18_1) glPopMatrix();
		return;
	}


	for (Data data : renderData)
	{
		ImVec2 screenSize = ImGui::GetWindowSize();

		std::vector<Vector3> bv = data.boxVerticies;

		float left = FLT_MAX;	
		float top = FLT_MAX;
		float right = FLT_MIN;
		float bottom = FLT_MIN;

		bool skip = false;
		for (Vector3 position : bv)
		{
			Vector2 p;

			if (!CWorldToScreen::WorldToScreen(position, CommonData::getInstance()->modelView, CommonData::getInstance()->projection, (int)screenSize.x, (int)screenSize.y, p))
			{
				skip = true;
				break;
			}

			// This is a neat trick to get the top left and bottom right corners of all the box verticies quickly.
			left = fmin(p.x, left);
			top = fmin(p.y, top);
			right = fmax(p.x, right);
			bottom = fmax(p.y, bottom);
		}

		// This is for when the world to screen fails, we just want to ignore rendering the entire box completely.
		// The fade stuff will compensate for it randomly disappearing when you're too close.
		if (skip)
			continue;

		// The rest is just rendering the ESP with the customizable options, self explanitory.

		if (FilledBoxValue->getValue())
		{
			ImColor bottomColor = ImColor(SecondFilledBoxColorValue->getValue()[0], SecondFilledBoxColorValue->getValue()[1], SecondFilledBoxColorValue->getValue()[2], FilledBoxOpacity * data.opacityFadeFactor);
			ImColor topColor = ImColor(FilledBoxColorValue->getValue()[0], FilledBoxColorValue->getValue()[1], FilledBoxColorValue->getValue()[2], FilledBoxOpacity * data.opacityFadeFactor);

			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(left, top), ImVec2(right, bottom), topColor, topColor, bottomColor, bottomColor);
		}

		if (this->BoxValue->getValue())
		{
			ImGui::GetWindowDrawList()->AddRect(ImVec2(left, top), ImVec2(right, bottom), ImColor(BoxColorValue->getValue()[0], BoxColorValue->getValue()[1], BoxColorValue->getValue()[2], BoxColorValue->getValue()[3] * data.opacityFadeFactor));
		}

		if (this->OutlineValue->getValue())
		{
			ImGui::GetWindowDrawList()->AddRect(ImVec2(left - 1, top - 1), ImVec2(right + 1, bottom + 1), ImColor(this->OutlineColorValue->getValue()[0], this->OutlineColorValue->getValue()[1], this->OutlineColorValue->getValue()[2], this->OutlineColorValue->getValue()[3] * data.opacityFadeFactor));
			ImGui::GetWindowDrawList()->AddRect(ImVec2(left + 1, top + 1), ImVec2(right - 1, bottom - 1), ImColor(this->OutlineColorValue->getValue()[0], this->OutlineColorValue->getValue()[1], OutlineColorValue->getValue()[2], this->OutlineColorValue->getValue()[3] * data.opacityFadeFactor));
		}

		if (HealthBarValue->getValue())
		{
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(left - 3, top), ImVec2(left - 1, bottom), ImColor(FilledBoxColorValue->getValue()[0], FilledBoxColorValue->getValue()[1], FilledBoxColorValue->getValue()[2], FilledBoxOpacity * data.opacityFadeFactor));

			if (data.health <= 0)
				data.health = 0.00001f;

			float scaleFactor = data.health / data.maxHealth;
			float diff = bottom - top;

			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(left - 3, bottom - (diff * scaleFactor)), ImVec2(left - 1, bottom), ImColor((int)(255 * (1.0 - scaleFactor)), (int)(255 * scaleFactor), 0, (int)(255 * data.opacityFadeFactor)));
		}

		if (TextValue->getValue() && Menu::Font->IsLoaded())
		{
			const char* name = data.name.c_str();
			ImVec2 textSize = Menu::Font->CalcTextSizeA(TextSizeValue->getValue(), FLT_MAX, 0.0f, name);
			float posX = left + ((right - left) / 2) - (textSize.x / 2);
			float posY = top - textSize.y - 1;

			if (data.dist > TextUnrenderDistance) {
				if (this->TextOutlineValue->getValuePtr())
				{
					RenderQOLF::DrawOutlinedText(Menu::Font, TextSizeValue->getValue(), ImVec2(posX, posY), ImColor(TextColorValue->getValue()[0], TextColorValue->getValue()[1], TextColorValue->getValue()[2], TextColorValue->getValue()[3] * data.opacityFadeFactor), ImColor(this->TextOutlineColorValue->getValue()[0], this->TextOutlineColorValue->getValue()[1], this->TextOutlineColorValue->getValue()[2], this->TextOutlineColorValue->getValue()[3] * data.opacityFadeFactor), name);
				}
				else {

					ImGui::GetWindowDrawList()->AddText(Menu::Font, TextSizeValue->getValue(), ImVec2(posX, posY), ImColor(TextColorValue->getValue()[0], TextColorValue->getValue()[1], TextColorValue->getValue()[2], TextColorValue->getValue()[3] * data.opacityFadeFactor), name);
				}
			}

			const char* dist = data.distText.c_str();
			float distTextSize = TextSizeValue->getValue() / 1.5;
			textSize = Menu::Font->CalcTextSizeA(distTextSize, FLT_MAX, 0.0f, dist);
			posX = left + ((right - left) / 2) - (textSize.x / 2);
			posY = bottom;

			if (TextOutlineValue->getValue())
			{
				RenderQOLF::DrawOutlinedText(Menu::Font, distTextSize, ImVec2(posX, posY), ImColor(TextColorValue->getValue()[0], TextColorValue->getValue()[1], TextColorValue->getValue()[2], TextColorValue->getValue()[3] * data.opacityFadeFactor), ImColor(this->TextOutlineColorValue->getValue()[0], this->TextOutlineColorValue->getValue()[1], this->TextOutlineColorValue->getValue()[2], this->TextOutlineColorValue->getValue()[3] * data.opacityFadeFactor), dist);
			}
			else {
				ImGui::GetWindowDrawList()->AddText(Menu::Font, distTextSize, ImVec2(posX, posY), ImColor(TextColorValue->getValue()[0], TextColorValue->getValue()[1], TextColorValue->getValue()[2], TextColorValue->getValue()[3] * data.opacityFadeFactor), dist);
			}
		}
	}
}

void Esp::RenderMenu()
{
	
	ImGui::BeginChild("ESP", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(28374, "Toggle ESP", this);
		if (this->espMode->getValue() == ESP2D)
		{
			ImGui::Separator();
			Menu::DoToggleButtonStuff(45678, "Box", this->BoxValue->getValuePtr());
			Menu::DoToggleButtonStuff(111123, "Fill Box", this->FilledBoxValue->getValuePtr());
			Menu::DoToggleButtonStuff(7457, "Box Outline", this->OutlineValue->getValuePtr());
			Menu::DoToggleButtonStuff(23445, "Healthbar", this->HealthBarValue->getValuePtr());
			Menu::DoToggleButtonStuff(34576, "Distance", this->TextValue->getValuePtr());
			//Menu::DoToggleButtonStuff(567567, "Test Circles", &this->TestCircles);
			Menu::DoToggleButtonStuff(1337, "Text Outline", this->TextOutlineValue->getValuePtr());
			Menu::DoSliderStuff(34875, "Fade Distance", this->FadeDistanceValue->getValuePtr(), 0, 10);
			Menu::DoSliderStuff(128763, "Distance Size", this->TextSizeValue->getValuePtr(), 12, 24);
		}
		else {
			Menu::DoCombo(this->esp3DMode);
		}
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);
	
	ImGui::BeginChild("ESP2", ImVec2(320, 426), true);
	{
		ImGui::Combo("ESP Mode", espMode->getValuePtr(), espMode->getDescs(), 2);
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);

	}
	ImGui::EndChild();
}