#include "Console.h"

Console& Console::getInstance()
{
	static Console instance;
	return instance;
}

void Console::Render()
{
	ImGui::SetNextWindowSize(ImVec2(765.0f, 455.0f), ImGuiCond_Once);

	if (ImGui::Begin("Nobody_Terminal ", 0, ImGuiWindowFlags_NoNav))
	{
		//SetIsFocused(ImGui::IsWindowFocused());

		bool copy_to_clipboard = false;
		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

		if (ImGui::BeginChild("###Terminal_ScrollRegion", ImVec2(0.0f, -footer_height_to_reserve), false))
		{
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::BeginMenu("Filter Text###Terminal_FilterMenu"))
				{
					Filter.Draw("Filter: (\"incl,-excl\") (\"error\")###Terminal_Filter", (ImGui::GetWindowSize().x / 4.0f));
					ImGui::EndMenu();
				}

				ImGui::MenuItem("Auto Scroll", "", &AutoScroll);
				copy_to_clipboard = ImGui::Selectable("Copy to Clipboard");
				if (ImGui::Selectable("Clear Terminal###Terminal_ClearText")) { ConsoleText.clear(); }
				if (ImGui::Selectable("Clear History###Terminal_ClearHistory")) { UserHistory.clear(); }

				ImGui::EndPopup();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 1.0f));
			if (copy_to_clipboard) { ImGui::LogToClipboard(); }

			for (size_t i = 0; i < ConsoleText.size(); i++)
			{
				const ImClasses::TextData& textData = ConsoleText[i];
				const char* itemText = textData.Text.c_str();
				if (!Filter.PassFilter(itemText)) { continue; }

				float fontSize = 1.0f;
				ImFont* font = ImFontMap[textData.Style];
				if (font) { fontSize = font->FontSize; }

				ImGui::PushTextWrapPos(ImGui::GetWindowWidth() - fontSize);
				TextStyled(itemText, textData.Color, font);
				ImGui::PopTextWrapPos();
			}

			if (copy_to_clipboard) { ImGui::LogFinish(); }
			if (ScrollToBottom || (AutoScroll && (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))) { ImGui::SetScrollHereY(1.0f); }

			ScrollToBottom = false;

			ImGui::PopStyleVar();
			ImGui::EndChild();

			bool reclaim_focus = false;

			ImGui::PushItemWidth((ImGui::GetWindowSize().x - (ImGui::GetStyle().WindowPadding.x * 2.0f)) - 55.0f);

			if (ImGui::InputText("###Terminal_InputText", InputBuffer, IM_ARRAYSIZE(InputBuffer), InputFlags, [](ImGuiInputTextCallbackData* data) -> int32_t { return reinterpret_cast<Console*>(data->UserData)->TextEditCallback(data); }, reinterpret_cast<void*>(this)))
			{
				char* bufferText = InputBuffer;
				Strtrim(bufferText);

				if (bufferText[0]) { ExecuteCommand(bufferText); }

				strcpy_s(bufferText, sizeof(bufferText), "");
				reclaim_focus = true;
			}

			ImGui::SameLine(); if (ImGui::Button("Enter###Terminal_EnterButton"))
			{
				char* bufferText = InputBuffer;
				Strtrim(bufferText);
				if (bufferText[0]) { ExecuteCommand(bufferText); }
				strcpy_s(bufferText, sizeof(bufferText), "");
				reclaim_focus = true;
			}

			ImGui::PopItemWidth();

			if (std::strlen(InputBuffer) == 0) { ResetAutoComplete(); }

			if (!Candidates.empty() && ImGui::IsWindowFocused())
			{
				ImVec2 consolePos = ImGui::GetWindowPos();
				consolePos.y += ImGui::GetWindowHeight() + 5.0f;

				if (ArgumentType == ImArgumentIds::IM_Interfaces) { consolePos.x += 85.0f; }
				else if (ArgumentType == ImArgumentIds::IM_Example) { consolePos.x += 0.0f; } // Example, purpose of different commands having different auto-complete positions.

				ImGui::SetNextWindowPos(consolePos);

				if (!Candidates.empty())
				{
					ImGui::OpenPopup("###Terminal_CandidatesPopup");

					if (ImGui::BeginPopup("###Terminal_CandidatesPopup", ImGuiWindowFlags_NoFocusOnAppearing))
					{
						ImVec2 childSize(175.0f, 0.0f);

						for (size_t i = 0; i < Candidates.size(); i++)
						{
							childSize.y += 18.25f;

							if (childSize.y > 130.0f) // Cutoff point, if there are more than "i" candidates it will no longer grow in size.
							{
								childSize.y = 130.0f;
								break;
							}
						}

						if (ImGui::BeginChild("###Terminal_CandidatesChild", childSize))
						{
							for (size_t i = 0; i < Candidates.size(); i++)
							{
								const std::pair<std::string, bool>& candidate = Candidates[i];

								TextStyled(
									Candidates[i].first.c_str(),
									(candidate.second ? ImColorMap[TextColors::White] : ImColorMap[TextColors::Grey]),
									(candidate.second ? ImFontMap[TextStyles::Italic] : nullptr
										));
							}

							ImGui::EndChild();
						}

						ImGui::EndPopup();
					}
				}
			}

			ImGui::SetItemDefaultFocus();
			if (reclaim_focus) { ImGui::SetKeyboardFocusHere(-1); }
		}
	}

	ImGui::End();
}

void Console::AddCommand(const std::string& str)
{
	CommandCompletes.push_back(StrCpy(str.c_str()));
}

void Console::ExecuteCommand(const std::string& command, TextStyles textStyle)
{
	ResetAutoComplete();
	AddDisplayText("# " + command, TextColors::Yellow, textStyle);

	HistoryPos = -1;

	if (UserHistory.size() >= MaxUserHistory)
	{
		for (size_t i = 0; i < UserHistory.size(); i++)
		{
			if (i == 0)
			{
				continue;
			}

			UserHistory[i - 1] = UserHistory[i];
		}

		UserHistory[ConsoleText.size() - 1] = command;
	}
	else
	{
		UserHistory.push_back(command);
	}

	// Here is where you would execute the command on a separate thread, as calling anything in the render thread will crash your game.
	// ExampleClass::ExecuteCommand(command);
	ScrollToBottom = true;
}
void Console::ResetAutoComplete()
{
	CandidatePos = 0;
	ArgumentType = ImArgumentIds::IM_None;
	Candidates.clear();
}

void Console::AddDisplayText(const std::string& text, TextColors textColor, TextStyles textStyle)
{
	ImClasses::TextData newData(text, textColor, textStyle);

	if (ConsoleText.size() >= MaxConsoleHistory)
	{
		for (size_t i = 0; i < ConsoleText.size(); i++)
		{
			if (i == 0)
			{
				continue;
			}

			ConsoleText[i - 1] = ConsoleText[i];
		}

		ConsoleText[ConsoleText.size() - 1] = newData;
	}
	else
	{
		ConsoleText.push_back(newData);
	}
}

void Console::AddDisplayText(const ImClasses::QueueData& queueData)
{
	AddDisplayText(queueData.Text, queueData.Id, queueData.Style);
}


int32_t Console::TextEditCallback(ImGuiInputTextCallbackData* data)
{
	switch (data->EventFlag)
	{
	case ImGuiInputTextFlags_CallbackHistory:
	{
		if (Candidates.empty())
		{
			int32_t prev_history_pos = HistoryPos;

			if (data->EventKey == ImGuiKey_UpArrow)
			{
				if (HistoryPos == -1)
				{
					HistoryPos = UserHistory.size() - 1;
				}
				else if (HistoryPos > 0)
				{
					HistoryPos--;
				}
			}
			else if (data->EventKey == ImGuiKey_DownArrow)
			{
				if (HistoryPos != -1)
				{
					if (++HistoryPos >= UserHistory.size())
					{
						HistoryPos = -1;
					}
				}
			}

			if (prev_history_pos != HistoryPos)
			{
				const char* history_str = (HistoryPos >= 0) ? UserHistory[HistoryPos].c_str() : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);
			}
		}
		else
		{
			int32_t prev_can_pos = CandidatePos;

			if (data->EventKey == ImGuiKey_UpArrow)
			{
				if (CandidatePos == 0)
				{
					CandidatePos = Candidates.size() - 1;
				}
				else if (CandidatePos > 0)
				{
					CandidatePos--;
				}
			}
			else if (data->EventKey == ImGuiKey_DownArrow)
			{
				if (CandidatePos == Candidates.size() - 1)
				{
					CandidatePos = 0;
				}
				else if (CandidatePos < Candidates.size())
				{
					CandidatePos++;
				}
			}

			for (auto& candidate : Candidates)
			{
				candidate.second = false;
			}

			Candidates[CandidatePos].second = true;
		}

		break;
	}
	case ImGuiInputTextFlags_CallbackCompletion:
	{
		if (!Candidates.empty())
		{
			int32_t completePos = CandidatePos;

			if (completePos < 0 || completePos > Candidates.size())
			{
				completePos = 0;
			}

			const char* word_end = data->Buf + data->CursorPos;
			const char* word_start = word_end;

			while (word_start > data->Buf)
			{
				const char c = word_start[-1];

				if (c == ' ' || c == '\t' || c == ',' || c == ';')
				{
					break;
				}

				word_start--;
			}

			data->DeleteChars((int32_t)(word_start - data->Buf), (int32_t)(word_end - word_start));
			data->InsertChars(data->CursorPos, Candidates[completePos].first.c_str());
			data->InsertChars(data->CursorPos, " ");
			ResetAutoComplete();
		}

		break;
	}
	case ImGuiInputTextFlags_CallbackEdit:
	{
		if (strnlen_s(data->Buf, sizeof(InputBuffer)) > 0)
		{
			const char* word_end = data->Buf + data->CursorPos;
			const char* word_start = word_end;
			bool isArgument = false;

			while (word_start > data->Buf)
			{
				const char c = word_start[-1];

				if (c == ' ')
				{
					isArgument = true;
					break;
				}
				else if (c == '\t' || c == ',' || c == ';')
				{
					break;
				}

				word_start--;
			}

			ResetAutoComplete();

			if (strnlen_s(word_start, sizeof(InputBuffer)) > 0 || isArgument)
			{
				if (!isArgument)
				{
					bool first = true;

					for (size_t i = 0; i < CommandCompletes.size(); i++)
					{
						if (CommandCompletes[i])
						{
							if (Strnicmp(CommandCompletes[i], word_start, (int32_t)(word_end - word_start)) == 0)
							{
								Candidates.push_back(std::make_pair(CommandCompletes[i], first));
								first = false;
							}
						}
					}
				}
				else
				{
					const char* argument_end = data->Buf + data->CursorPos;
					const char* argument_start = argument_end;

					while (argument_start > data->Buf)
					{
						if (argument_start[-1] == ' ')
						{
							break;
						}

						argument_start--;
					}

					std::string inputStr = data->Buf;
					int32_t foundSpaces = 0;

					for (const char& c : inputStr)
					{
						if (c == ' ')
						{
							foundSpaces++;
						}

						if (foundSpaces > 1)
						{
							return 0;
						}
					}

					if (inputStr.find("imgui_toggle") == 0)
					{
						ArgumentType = ImArgumentIds::IM_Interfaces;
					}
					else
					{
						ArgumentType = ImArgumentIds::IM_None;
						break;
					}

					if (ArgumentCompletes.find(ArgumentType) != ArgumentCompletes.end())
					{
						bool first = true;

						const std::vector<std::string>& completes = ArgumentCompletes[ArgumentType];

						for (size_t i = 0; i < completes.size(); i++)
						{
							if (Strnicmp(completes[i].c_str(), argument_start, (int32_t)(argument_end - argument_start)) == 0)
							{
								Candidates.push_back(std::make_pair(completes[i].c_str(), first));
								first = false;
							}
						}
					}
				}
			}
		}
		else
		{
			ResetAutoComplete();
		}

		break;
	}
	}

	return 0;
}

char* Console::StrCpy(const char* s)
{
	IM_ASSERT(s);
	size_t length = strlen(s) + 1;
	void* buffer = malloc(length);
	IM_ASSERT(buffer);
	memcpy_s(buffer, length, s, length);
	return reinterpret_cast<char*>(buffer);
}

void Console::TextStyled(const char* text, const ImVec4& textColor, ImFont* textFont)
{
	if (textFont) { ImGui::PushFont(textFont); }
	ImGui::PushStyleColor(ImGuiCol_Text, textColor);
	ImGui::TextEx(text);
	ImGui::PopStyleColor();
	if (textFont) { ImGui::PopFont(); }
}

void Console::Strtrim(char* s)
{
	char* strEnd = s + strlen(s);

	while (strEnd > s && strEnd[-1] == ' ')
	{
		strEnd--;
		*strEnd = 0;
	}
}

int32_t Console::Strnicmp(const char* s1, const char* s2, int32_t n)
{
	int32_t d = 0;

	while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
	{
		s1++;
		s2++;
		n--;
	}

	return d;
}


namespace ImClasses
{
	TextData::TextData(const std::string& text, TextColors textColor, TextStyles textStyle) : Text(text), Color(ImColorMap[textColor]), Style(textStyle) {}

	TextData::~TextData() {}

	TextData& TextData::operator=(const TextData& textData)
	{
		Text = textData.Text;
		Color = textData.Color;
		Style = textData.Style;
		return *this;
	}

	QueueData::QueueData(const std::string& text, TextColors textColor, TextStyles textStyle) : TextData(text, textColor, textStyle), Id(textColor) {}

	QueueData::~QueueData() {}

	QueueData& QueueData::operator=(const QueueData& queueData)
	{
		Text = queueData.Text;
		Color = queueData.Color;
		Style = queueData.Style;
		Id = queueData.Id;
		return *this;
	}

	FunctionCount::FunctionCount() : Calls(0) {}

	FunctionCount::~FunctionCount() {}

	FunctionData::FunctionData() :
		FullName("null"),
		Package("null"),
		Caller("null"),
		Function("null"),
		Index(0)
	{

	}

	FunctionData::FunctionData(const FunctionData& functionData) :
		FullName(functionData.FullName),
		Package(functionData.Package),
		Caller(functionData.Caller),
		Function(functionData.Function),
		Index(functionData.Index)
	{

	}

	FunctionData::FunctionData(class UObject* caller, class UFunction* function) :
		FullName("null"),
		Package("null"),
		Caller("null"),
		Function("null"),
		Index(0)
	{
		// Requires and actual SDK for your game, so that's why this is commented out.

		//if (caller && function)
		//{
		//	FullName = function->GetFullName();
		//	Package = function->GetPackageObj()->GetName();
		//	Caller = caller->GetName();
		//	Function = function->GetName();
		//	Index = function->ObjectInternalInteger;
		//}
	}

	FunctionData::FunctionData(const std::string& fullName, const std::string& package, const std::string& caller, const std::string& function, int32_t index) :
		FullName(fullName),
		Package(package),
		Caller(caller),
		Function(function),
		Index(index)
	{

	}

	FunctionData::~FunctionData() {}

	FunctionData& FunctionData::operator=(const FunctionData& functionData)
	{
		FullName = functionData.FullName;
		Package = functionData.Package;
		Caller = functionData.Caller;
		Function = functionData.Function;
		Index = functionData.Index;
		return *this;
	}
}