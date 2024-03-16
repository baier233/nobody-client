#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <vector>
#include <string>
class Esp :public AbstractModule {
public:
    static Esp* getInstance();
    void onEnable();
    void onDisable();
    void onUpdate(const EventUpdate e);
    void RenderUpdate();
    void RenderMenu();

    struct Data {
        std::vector<Vector3> boxVerticies;
        std::string name;
        std::string distText;
        float dist;
        float opacityFadeFactor;
        float health;
        float maxHealth;
    };


    std::vector<Data> renderData;
    std::vector<AxisAlignedBB_t> renderData3D;

    FloatValue* TextSizeValue = new FloatValue("Text Size", 18, 12, 24);
    FloatValue* FadeDistanceValue = new FloatValue("Fade Distance", 3.0f, 0.f, 10.0f);

    ModeValue* espMode = new ModeValue("ESP Mode",{ESP2D,ESP3D}, modes,ESP2D);
    ModeValue* esp3DMode = new ModeValue("ESP 3D Mode",{OUTLINE,FILLED}, modes3D,ESP2D);
    


    BoolValue* BoxValue = new BoolValue("Box", true);
    ColorValue* BoxColorValue = new ColorValue("Box Color", BoxColor);

    BoolValue* OutlineValue = new BoolValue("Outline", true);
    ColorValue* OutlineColorValue = new ColorValue("Outline Color", OutlineColor); 

    BoolValue* FilledBoxValue = new BoolValue("FilledBox", true);
    ColorValue* FilledBoxColorValue = new ColorValue("FilledBox Color", FilledBoxColor);

    BoolValue* TextOutlineValue = new BoolValue("TextOutline", false);
    ColorValue* TextOutlineColorValue = new ColorValue("TextOutline Color", TextOutlineColor);

    ColorValue* TestCirclesColorValue = new ColorValue("TestCircles Color", TestCirclesColor);
    ColorValue* TextColorValue = new ColorValue("Text Color", TextColor);
    ColorValue* SecondFilledBoxColorValue = new ColorValue("SecondFilledBox Color", SecondFilledBoxColor);


    BoolValue* HealthBarValue = new BoolValue("Health Bar", true);
    BoolValue* TextValue = new BoolValue("Text", false);
   




private:

    const char* modes[2]{ "ESP2D", "ESP3D" };
    const char* modes3D[2]{ "Outline Box", "Filled Box" };

    enum ESPMODE
    {
        ESP2D,
        ESP3D
    };

    enum ESP3DMODE {
        OUTLINE,
        FILLED
    };

    float FilledBoxOpacity = 0.15f;
    bool TestCircles = false;
    float TextUnrenderDistance = 14.0f;

    float TestCirclesColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
    float TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
    float SecondFilledBoxColor[3]{ 0, 0, 0 };
    float TextOutlineColor[4]{ 0, 0, 0, 1.0f };
    float FilledBoxColor[3]{ 0, 0, 0 };
    float OutlineColor[4]{ 0, 0, 0, 0.25 };
    float BoxColor[4]{ 255, 255, 255, 1 };
    Esp();
};