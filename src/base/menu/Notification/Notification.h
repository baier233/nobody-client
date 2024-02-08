#include <string>
#include "../../util/math/TimerUtil.h"
#include "../../util/render/Animation.h"
#include "../../util/render/SimpleAnimation.h"
#include <gl/GL.h>
#include "../../../../ext/imgui/imgui.h"

enum class Type : unsigned int {
	SUCCESS = 0,
	EXCEPTION,
	WARNNING,
	INFO
};

class Notification {

public:

	Notification(std::string text, Type type);

	void render(ImTextureID icon, int index, float x, float y);
	clock_t getTime();
	bool isRendering();
	Type getType();
	std::string getText();
	float getWidth();
private:
	float GetTextLength(const char* text, ImFont* font, float font_size);
	std::string text;
	Type type;
	clock_t start;
	clock_t end;
	SimpleAnimation xAnimation = SimpleAnimation(0.F);
	SimpleAnimation yAnimation = SimpleAnimation(0.F);
	bool started = false;
	bool finished = false;
	float width;
};