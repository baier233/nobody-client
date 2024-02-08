#include "Notification.h"
#include <math.h>

#include "../menu.h"
Notification::Notification(std::string message, Type msgType) : text(message), type(msgType), start(clock()), end(3500) {}

void Notification::render(ImTextureID icon, int index, float x, float y) {
	ImDrawList* dl = ImGui::GetForegroundDrawList();

	float yOffset = index * 70;

	// 起始位置
	float startX = x + getWidth();
	float startY = y - yOffset + 16;
	// 目标位置
	float targetX = x; 
	float targetY = y - yOffset;

	if (!started) {
		xAnimation.setValue(startX);
		yAnimation.setValue(startY);
		started = true;
	}
	
	bool wentOut = this->getTime() <= this->end;

	if (wentOut) {
		xAnimation.setAnimation(targetX, 22);
		yAnimation.setAnimation(targetY, 23);
	}
	else {
		xAnimation.setAnimation(startX, 24);
		yAnimation.setAnimation(startY, 25);
	}

	float currentX = xAnimation.getValue(); // 当前位置
	
	if (currentX == targetX && !wentOut) {
		finished = true;
	}
	
	float currentY = yAnimation.getValue();

	float bgX = currentX;
	float bgY = currentY;
	float bgX1 = currentX + getWidth();
	float bgY1 = currentY + 50;

	float iconX = currentX + 15.5f;
	float iconY = currentY + 13;
	float iconX1 = currentX + 41;
	float iconY1 = currentY + 38.5f;

	float titleX = currentX + 55;
	float titleY = currentY + 17;

	dl->AddRectFilled(ImVec2(bgX, bgY), ImVec2(bgX1, bgY1), IM_COL32(18, 20, 18, 255), 5);
	// dl->AddText(Menu::iconFont, 16, ImVec2(iconX, iconY), IM_COL32(18, 20, 18, 255), icon);
	dl->AddImage((void*)(intptr_t)icon, ImVec2(iconX, iconY), ImVec2(iconX1, iconY1));
	dl->AddText(nullptr, 15, ImVec2(titleX, titleY), IM_COL32(250, 250, 250, 250), this->text.c_str());
}

float Notification::getWidth() {
	return GetTextLength(this->text.c_str(), nullptr, 15) + 40;
	//return ImGui::CalcTextSize(this->text.c_str()).x;
}

float Notification::GetTextLength(const char* text, ImFont* font, float font_size)
{
	ImGui::PushFont(font);
	float textLength = ImGui::CalcTextSize(text).x;
	ImGui::PopFont();
	return textLength;
}

clock_t Notification::getTime() {
	return clock() - this->start;
}

bool Notification::isRendering() {
	//return this->getTime() <= this->end;
	return !this->finished;
}

Type Notification::getType() {
	return this->type;
}

std::string Notification::getText() {
	return this->text;
}