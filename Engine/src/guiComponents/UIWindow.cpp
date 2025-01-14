#include "UIWindow.h"

//Constructor

s2d::UIWindow::UIWindow()
{
	//Default SFML WINDOW background color
	this->m_UIInspector.backgroundColor = getWindowBackgroundColorFromFile();
	this->isAnyUIWindowHovered = false;
}

//Private functions

s2d::Vector3 s2d::UIWindow::getWindowBackgroundColorFromFile()
{
	Vector3 vec;
	std::fstream backgroundFile;

	//opening the file where all sprite data is
	backgroundFile.open(PATH_TO_BACKGROUND_FILE, std::ios::in);
	if (backgroundFile.is_open())
	{
		std::string line;
		int cnt = 0;
		while (std::getline(backgroundFile, line))
		{
			cnt++;
			//First line is the header so we dont need to check for it
			if (cnt == 1)
			{
				continue;
			}

			//Splitting line
			std::string delimiter = ";";
			std::vector<std::string> propertys = std::splitString(line, delimiter);

			//INITIIALIZING PROPS
			vec.x = std::stof(propertys[0].c_str());
			vec.y = std::stof(propertys[1].c_str());
			vec.z = std::stof(propertys[2].c_str());
		}
		backgroundFile.close();

		return vec;
	}
	return vec;
}

// Static functions

void s2d::UIWindow::renderStyle(ImGuiStyle* style)
{
	ImVec4 shadow_color = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);

	//Setting it centered
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->FramePadding = ImVec2(8, 6);

	style->Colors[ImGuiCol_TitleBg] = ImColor(49, 49, 76);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(49, 49, 76);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(217, 101, 53, 255);

	//the sprite selected
	style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(100, 90, 100, 100);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);

	style->Colors[ImGuiCol_Button] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(15, 15, 25);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(100, 90, 100, 100);

	//The background of (input) 
	style->Colors[ImGuiCol_FrameBg] = shadow_color;
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(45, 45, 45);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(50, 50, 50);

	style->Colors[ImGuiCol_WindowBg] = ImColor(22, 22, 32, 255);

	style->Colors[ImGuiCol_TextSelectedBg] = ImColor(30, 30, 30);

	style->Colors[ImGuiCol_SliderGrab] = ImColor(30, 30, 30);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(25, 25, 25);

	style->Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);

	style->FrameRounding = 4.0f;
	style->GrabRounding = 4.0f;

}

//Public functions

void s2d::UIWindow::update()
{
	//When we press play we need to save our data again, lol
	this->m_UIToolButtons.setBackgroundColorToSave(this->m_UIInspector.backgroundColor);

	s2d::UIWindow::renderStyle(&ImGui::GetStyle());
	this->m_UIHirachy.createHirachyWindow();
	this->m_UIToolButtons.createToolsAndButtons();
	this->m_UIInspector.createUIInspector();
	this->m_UIAnimation.createUIAnimationWindow();
	this->m_UIAssetFolder.createAssetLinkerWindow();

	if (this->m_UIHirachy.isHovered || this->m_UIToolButtons.isHovered || this->m_UIInspector.isHovered || this->m_UIAssetFolder.isHovered || this->m_UIAnimation.isHovered)
	{
		this->isAnyUIWindowHovered = true;
	}
	else
	{
		this->isAnyUIWindowHovered = false;
	}
}

