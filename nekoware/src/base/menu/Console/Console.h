#pragma once
#include "../../../../ext/imgui/imgui.h"
#include "../../../../ext/imgui/imgui_internal.h"
#include <string>
#include <vector>
#include <map>

enum class TextStyles : uint8_t
{
	Regular,
	Italic,
	Bold,
	END
};

enum class TextColors : uint32_t
{
	Black,
	Grey,
	White,
	Red,
	Orange,
	Yellow,
	Green,
	Blue,
	Aqua,
	Purple,
	Pink,
	END
};

enum class ImArgumentIds : uint8_t
{
	IM_None,
	IM_Interfaces,
	IM_Example
};
std::map<TextStyles, ImFont*> ImFontMap = {
   { TextStyles::Regular, nullptr },
   { TextStyles::Italic, nullptr },
   { TextStyles::Bold, nullptr }
};
std::map<TextColors, ImVec4> ImColorMap = {
	{ TextColors::Black, ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },							// #000000
	{ TextColors::Grey, ImVec4(0.72549f, 0.72549f, 0.72549f, 1.0f) },				// #B9B9B9
	{ TextColors::White, ImVec4(1.0f, 1.0f, 1.0f, 1.0f) },							// #FFFFFF
	{ TextColors::Red, ImVec4(0.95686f, 0.10196f, 0.18431f, 1.0f) },				// #F41A2F
	{ TextColors::Orange, ImVec4(1.0f, 0.55686f, 0.0f, 1.0f) },						// #FF8E00
	{ TextColors::Yellow, ImVec4(0.99215f, 0.96078f, 0.0f, 1.0f) },					// #FDF500
	{ TextColors::Green, ImVec4(0.16470f, 0.99215f, 0.18039f, 1.0f) },				// #2AFD2E
	{ TextColors::Blue, ImVec4(0.12549f, 0.41568f, 1.0f, 1.0f) },					// #206AFF
	{ TextColors::Aqua, ImVec4(0.09019f, 0.90980f, 1.0f, 1.0f) },					// #17E8FF
	{ TextColors::Purple, ImVec4(0.64705f, 0.12941f, 1.0f, 1.0f) },					// #A521FF
	{ TextColors::Pink, ImVec4(1.0f, 0.12941, 1.0f, 1.0f) },						// #FF21FF
};

namespace ImClasses
{
	class TextData
	{
	public:
		std::string Text;
		ImVec4 Color;
		TextStyles Style;

	public:
		TextData(const std::string& text, TextColors textColor, TextStyles textStyle);
		~TextData();

	public:
		TextData& operator=(const TextData& textData);
	};

	class QueueData : public TextData
	{
	public:
		TextColors Id;

	public:
		QueueData(const std::string& text, TextColors textColor, TextStyles textStyle);
		~QueueData();

	public:
		QueueData& operator=(const QueueData& queueData);
	};

	class FunctionCount
	{
	public:
		size_t Calls;

	public:
		FunctionCount();
		~FunctionCount();
	};

	class FunctionData : public FunctionCount
	{
	public:
		std::string FullName;
		std::string Package;
		std::string Caller;
		std::string Function;
		int32_t Index;

	public:
		FunctionData();
		FunctionData(const FunctionData& functionData);
		FunctionData(class UObject* caller, class UFunction* function);
		FunctionData(const std::string& fullName, const std::string& package, const std::string& caller, const std::string& function, int32_t index);
		~FunctionData();

	public:
		FunctionData& operator=(const FunctionData& functionData);
	};
}


class Console
{
public:
	static Console& getInstance();
	void Render();
	void AddCommand(const std::string& str);
	void ExecuteCommand(const std::string& command, TextStyles textStyle = TextStyles::Regular);
	void ResetAutoComplete();
	void AddDisplayText(const std::string& text, TextColors textColor, TextStyles textStyle);
	void AddDisplayText(const ImClasses::QueueData& queueData);
	int32_t TextEditCallback(struct ImGuiInputTextCallbackData* data);
private:
	size_t MaxUserHistory;
	size_t MaxConsoleHistory;
	std::vector<ImClasses::TextData> ConsoleText;
	std::vector<ImClasses::QueueData> ConsoleQueue;
	std::vector<std::string> UserHistory;
	std::vector<char*> CommandCompletes;
	std::map<ImArgumentIds, std::vector<std::string>> ArgumentCompletes;
	char* StrCpy(const char* s);
	void TextStyled(const char* text, const ImVec4& textColor, ImFont* textFont);
	ImGuiTextFilter Filter;
	bool AutoScroll;
	bool ScrollToBottom;
	char InputBuffer[512];
	int32_t HistoryPos;
	ImGuiInputTextFlags InputFlags;
	int32_t CandidatePos;
	ImArgumentIds ArgumentType;
	std::vector<std::pair<std::string, bool>> Candidates;
	void Strtrim(char* s);
	int32_t Strnicmp(const char* s1, const char* s2, int32_t n);
};
