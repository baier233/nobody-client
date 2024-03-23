#include "blink.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../commonData.h"

Blink::Blink() : AbstractModule("Blink", Category::PLAYER, "Blink.") {
	//EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
	EventManager::getInstance().reg<EventPacketSend>([this](auto&& PH1) { onPacket(std::forward<decltype(PH1)>(PH1)); });
}

void Blink::sendPackets(JNIEnv* env)
{
}

Blink* Blink::getInstance() {
	static auto* inst = new Blink();
	return inst;
}

void Blink::onDisable() {
	sendPackets(Java::GetInstance()->Env);
}

void Blink::onEnable() {
}


void Blink::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;


}
void Blink::onPacket(EventPacketSend e)
{
	if (!this->getToggle()) {
		if (!packets.empty())
			sendPackets(e.getEnv());
		return;
	}
	if (!CommonData::getInstance()->SanityCheck()) return;
	e.SetCancel(true);
	packets.push_back(CPacket(e.getPackets()));
}
void Blink::RenderMenu()
{

	ImGui::BeginChild("Blink", ImVec2(320, 426), true);
	{
		ImGui::Checkboxx("Toggle Blink", image::check, this);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("Blink2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}

void Blink::OnReceiveData()
{

	if (!this->getToggle())
		return;

	//while (IsKeyBeingDown(this->getKey()) && (GetTickCount64() - timer < Milliseonds * 1000)) {
	//	Sleep(1);
	//}
}