#include "NotificationManager.h"


NotificationManager::NotificationManager() : cleanInterval(6000) {
	//RECT rect;
	//GetWindowRect(FindWindow("LWJGL", nullptr), &rect);
	//this->startX = rect.right - 250;
	//this->startY = rect.bottom - 250;
	this->notifications.clear();
	this->cleanTimer.reset();
	//EventManager::getInstance().reg<EventRender>([this](auto&& PH1) { render(std::forward<decltype(PH1)>(PH1)); });
	//EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &NotificationManager::render));
}

NotificationManager& NotificationManager::getInstance() {
	static NotificationManager inst;
	return inst;
}

void NotificationManager::makeNotification(std::string text, Type type) {
	Notification n(text, type);
	this->addNotification(n);
}

void NotificationManager::addNotification(Notification n) {
	this->notifications.push_back(n);
	this->cleanTimer.reset();
}

void NotificationManager::render() {

	if (this->notifications.empty()) return;
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 windowPos = ImGui::GetWindowPos();

	this->startX = windowPos.x + windowSize.x - 250;
	this->startY = windowPos.y + windowSize.y - 100;
	int i = 0;
	ImTextureID icon = 0;
	for (Notification& n : this->notifications) {

		switch (n.getType()) {

		case Type::INFO:
			icon = image::iconInfo;
			break;

		case Type::EXCEPTION:
			icon = image::iconErr;
			break;

		case Type::SUCCESS:
			icon = image::iconSucc;
			break;

		case Type::WARNNING:
			icon = image::iconWarn;
			break;
		}

		if (n.isRendering()) {
			n.render(icon, i, windowPos.x + windowSize.x - n.getWidth(), this->startY);
			++i;
		}
	}

	if (this->cleanTimer.elapsed(this->cleanInterval)) {
		this->clearNotifications();
		this->cleanTimer.reset();
	}
}

void NotificationManager::clearNotifications() {
	this->notifications.clear();
}
