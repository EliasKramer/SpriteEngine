#include "UIAssetTools.h"

// Constructor

s2d::UIAssetTools::UIAssetTools()
{
	this->m_isPopUpHoverd = false;
	this->m_ptr_deleteFilePath = nullptr;
	this->m_ptr_currentAssetPath = nullptr;
	this->m_cppFileName[0] = '\0';
	this->m_openFileInput = false;
}

s2d::UIAssetTools::UIAssetTools(const std::string* currentAssetPath, const std::string* deleteItem)
{
	this->m_isPopUpHoverd = false;
	this->m_cppFileName[0] = '\0';
	this->m_openFileInput = false;
	this->m_ptr_currentAssetPath = currentAssetPath;
	this->m_ptr_deleteFilePath = deleteItem;
}

// Public functions

void s2d::UIAssetTools::update(bool& hovered)
{
	this->getFileName();

	if (this->m_cppFileName[0] != '\0' && !this->m_openFileInput)
	{
		this->createFileContent();
		this->m_cppFileName[0] = '\0';
	}

	if (ImGui::IsMouseReleased(1) && hovered)
	{
		ImGui::OpenPopup(INPUT_POPUP_NAME);
	}

	if (ImGui::IsPopupOpen(INPUT_POPUP_NAME))
	{
		hovered = true;
		ImGui::BeginPopup(INPUT_POPUP_NAME);
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("C++ Script"))
			{
				//  Create a scirpt, link it into the user project
				this->m_openFileInput = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::Button("Delete"))
		{
			std::cout << *this->m_ptr_deleteFilePath << std::endl;
		}
		ImGui::EndPopup();
	}
	this->m_isPopUpHoverd = ImGui::IsItemHovered();
}

void s2d::UIAssetTools::getFileName()
{
	if (!this->m_openFileInput)
	{
		return;
	}

	if (ImGui::Begin("##input_file_name", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::SetNextItemWidth(290);
		ImGui::InputTextWithHint("##file_input", "<name>", this->m_cppFileName, CHAR_MAX);
		if (ImGui::Button("Create"))
		{
			this->m_openFileInput = false;
		}

		UI::setWindowScreenMiddle(s2d::Vector2(300, 100));
		ImGui::End();
	}
}

void s2d::UIAssetTools::createFileContent()
{
	std::string header_content =
		"#pragma once\n\n"
		"#include <_header/SpriteEngine.h>\n\n"
		"class " + std::string(this->m_cppFileName) + " : s2d::Base\n"
		"{\n"
		"public:\n"
		"   void update();\n"
		"   void start();\n"
		"};\n";

	std::string cpp_content =
		"#include \"" + std::string(this->m_cppFileName) + ".h\"\n\n"
		"void " + std::string(this->m_cppFileName) + "::start()\n"
		"{\n"
		"\n"
		"}\n"
		"\n"
		"void " + std::string(this->m_cppFileName) + "::update()\n"
		"{\n"
		"\n"
		"}\n"
		"\n";

	std::string path = *this->m_ptr_currentAssetPath + this->m_cppFileName;

	std::string cpp_name = std::string(this->m_cppFileName) + ".cpp";
	std::string header_name = std::string(this->m_cppFileName) + ".h";
	std::createFileWithContent(header_content, header_name, *this->m_ptr_currentAssetPath);
	std::createFileWithContent(cpp_content, cpp_name, *this->m_ptr_currentAssetPath);
}