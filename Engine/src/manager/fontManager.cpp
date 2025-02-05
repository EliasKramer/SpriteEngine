#include "fontManager.h"
#include <iostream>

void s2d::FontManager::displaySmybolAsText(const char* symbol)
{
	ImGui::PopFont();
	ImGui::PushFont(s2d::FontManager::symbolFont);

	ImGui::Text(symbol);

	ImGui::PopFont();
	ImGui::PushFont(s2d::FontManager::defaultFont);
}

bool s2d::FontManager::displaySmybolAsButton(const char* symbol, ImFont* font)
{
	ImGui::PopFont();

	bool clicked = false;

	if (font != nullptr)
	{
		ImGui::PushFont(font);

		clicked = ImGui::Button(symbol, ImVec2(50, 50));
	}
	else
	{
		ImGui::PushFont(s2d::FontManager::symbolFont);

	    clicked = ImGui::Button(symbol);
	}


	ImGui::PopFont();
	ImGui::PushFont(s2d::FontManager::defaultFont);

	return clicked;
}

bool s2d::FontManager::displaySmybolAsButton(const char* symbol, float defaultFontSize)
{
	ImGui::SetWindowFontScale(defaultFontSize);

	bool clicked = false;
	ImGui::PopFont();
	ImGui::PushFont(s2d::FontManager::symbolFont);

	clicked = ImGui::Button(symbol);

	ImGui::PopFont();
	ImGui::PushFont(s2d::FontManager::defaultFont);

	ImGui::SetWindowFontScale(s2d::UIInfo::sdefaultFontSize);
	return clicked;
}

bool s2d::FontManager::displaySmybolAsButton(const char* symbol, ImVec2 cursorPos)
{
	ImGui::SetCursorPos(ImVec2(cursorPos.x, cursorPos.y));
	return displaySmybolAsButton(symbol);
}

void s2d::FontManager::InitFonts(ImGuiIO& io)
{
	ImFontConfig CustomFont;
	ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	io.IniFilename = nullptr;
	CustomFont.FontDataOwnedByAtlas = false;

	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 3;
	icons_config.OversampleV = 3;

	ImFontConfig config;

	static const ImWchar ranges[] =
	{
		0xf0c8, 0xf0c8, // Square
		0xf04b, 0xf04b, // Play
		0xf047, 0xf047, // Arrows
		0xf002, 0xf002, // Search
		0xf067, 0xf067, // Plus
		0xf044, 0xf044, // Edit
		0xf1f8, 0xf1f8, // Trash
		0xf079, 0xf079, // Retweet
		0xf04b, 0xf04b, // Play button
		0xf03e, 0xf03e, // Image
		0,
	};

	config.GlyphRanges = ranges;

	//Add the fonts (remember to fill in the correct path of your font
	s2d::FontManager::defaultFont = io.Fonts->AddFontFromFileTTF("EngineAssets\\Fonts\\Arial.ttf", s2d::FontManager::fontSize);
	s2d::FontManager::symbolFont = io.Fonts->AddFontFromFileTTF("EngineAssets\\Fonts\\fontawesome-webfont.ttf", s2d::FontManager::fontSize - 4, &config);

	//This function is important else the program will crash with an assertion
	ImGui::SFML::UpdateFontTexture();
}


ImFont* s2d::FontManager::defaultFont = nullptr;
ImFont* s2d::FontManager::imGuiDefaultFont = nullptr;
ImFont* s2d::FontManager::symbolFont = nullptr;
float s2d::FontManager::fontSize = 24.0f;
