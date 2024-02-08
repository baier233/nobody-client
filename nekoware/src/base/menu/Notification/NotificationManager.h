#pragma once
#include <vector>
#include "Notification.h"
#include "../../eventManager/EventManager.hpp"
#include "../../eventManager/events/EventRender.hpp"
#include "../../../../ext/imgui/main.h"
class NotificationManager {

public:

	static NotificationManager& getInstance();

	void makeNotification(std::string text, Type type);
	void addNotification(Notification n);
	void render();

	//void setIcon(GLuint info, GLuint err, GLuint succ, GLuint warn);

	NotificationManager(const NotificationManager&) = delete;
	NotificationManager(NotificationManager&&) = delete;
	NotificationManager& operator=(NotificationManager&) = delete;

private:

	clock_t cleanInterval;

	float startX;
	float startY;

	std::vector<Notification> notifications;
	TimerUtil cleanTimer;

	void clearNotifications();

	NotificationManager();
	~NotificationManager() = default;

};