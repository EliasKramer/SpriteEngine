#pragma once

#include <SFML/Graphics.hpp>
#include <calculationComponents/vector3.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <physicalComponents/sprite.h>
#include <data/FileData.h>

namespace s2d
{
	class Renderer
	{
	private:
		float m_timePassedToUpdateLayerIndex;
		float m_timePassedTillNextSpriteTextureUpdate;

		unsigned short  m_timeToUpdateLayerIndex;
		unsigned short m_timeToUpdateSpriteTexture;

		sf::RenderWindow* m_ptr_renderWindow;

		void draw();

		void drawRectangles();
		void drawSprites();
		void updateSriteTextures();

	public:
		Renderer();
		Renderer(sf::RenderWindow* renderWindow);

		void render();

	public:
	};
}

