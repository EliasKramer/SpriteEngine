#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <spriteComponents/spriteData.h>
#include <physicalComponents/gameObject.h>
#include <spriteComponents/boxCollider.h>
#include <SFML/Graphics.hpp>
#include <spriteComponents/physicsBody.h>
#include <stdExtension.h>
#include <spriteComponents/animator.h>

namespace s2d
{
	class Sprite
	{
	private:
		int m_childCount;
		int m_parentId;

		sf::Sprite m_sprite;
		sf::Texture m_texture;
		std::string m_path;
		int m_vectorPosition;
		int m_id;

		/// <summary>
		/// This is only used if it is a child. It is the position in the vector
		/// from the parent sprite
		/// </summary>
		int m_childListPos;

		void initVariables(std::string name, s2d::Vector2 spawnPos, std::string path);

	public:
		// General info
		std::string name;
		int sortingLayerIndex;

		// Components
		s2d::BoxCollider collider;
		s2d::PhsysicsBody physicsBody;
		s2d::Transform transform;
		s2d::Animator animator;

		//Parent / child infos
		std::vector<s2d::Sprite*> childs;
		s2d::Sprite* parent;

		Sprite();
		Sprite(std::string name, s2d::Vector2 spawnPosition, std::string path);
		Sprite(std::string name, s2d::Vector2 spawnPosition, std::string path, bool addToWindowByConstruction);
		
		//////////////////////////////////////
		//// ENGINE FUNCTIONS 
		/////////////////////////////////////

		void setChildCount(const int cnt) { this->m_childCount = cnt; }
		void setParentId(const int id) { this->m_parentId = id; }
		void setId(const int id) { this->m_id = id; }
		void setChildListPos(const int pos) { this->m_childListPos = pos; }
		void setVectorPosition(const int vec) { this->m_vectorPosition = vec; }
		sf::Sprite& getSprite() { return this->m_sprite; }
		sf::Texture& getTexture() { return this->m_texture; }

		//////////////////////////////////////
		//// USER FUNCTIONS 
		/////////////////////////////////////

		/// <summary>
		/// Gets the id of the parent
		/// </summary>
		int getParentId() const { return this->m_parentId; }

		/// <summary>
		/// Sets the new texture of the sprite
		/// </summary>
		/// <param name="path">The path of the new texture</param>
		void setSpriteTexture(const std::string& path);

		/// <summary>
		/// Sets the new sprite texture
		/// IT DOES NOT!!! LOAD THE TEXTURE FROM THE FILE
		/// </summary>
		/// <param name="texture">The already loaded texture</param>
		/// <param name="path">The new path which needs to be set</param>
		void setSpriteTexture(const sf::Texture& texture, const std::string& path);


		/// <summary>
		/// LOADS the texture from the file and sets it scale
		/// </summary>
		/// <param name="path">Path to the .png file</param>
		/// <param name="sclae">Scale to set</param>
		void setSpriteTexture(const std::string& path, const s2d::Vector2& sclae);

		/// <summary>
		/// Pushed the sprite to the sprites vector, gets rendered
		/// automaticly
		/// </summary>
		void addSpriteToScene();

		/// <summary>
		/// Gets the original position as a Cartesian coordinate system point (vector).
		/// </summary>
		/// <returns>The position as a vector</returns>
		s2d::Vector2 getOrigininalPosition();

		/// <summary>
		/// Renders the sprite instant to the screen when you create a 
		/// 'new' sprite, do not use this functions if you don't have a reason to 
		/// </summary>
		void renderInstant();

		/// <summary>
		/// Gets the absulute parent
		/// </summary>
		s2d::Sprite* getNode(); 

		/// <summary>
		/// Updates the sprite texture of only 1 sprite (reads the path from the file)
		/// </summary>
		void updateSpriteTexture();

		/// <summary>
		/// Get's the id of the current sprite
		/// </summary>
		/// <returns></returns>
		int getId() const { return this->m_id; }

		/// <summary>
		/// Gets the path to the texture file
		/// </summary>
		const std::string& getPathOfTextureFile() const { return this->m_path; }

		/// <summary>
		/// Gets the position in the s2d::Spirte::activeSprite array
		/// </summary>
		int getVectorPosition() { return this->m_vectorPosition; }

	public:
		static int getMaxNumber(std::vector<s2d::Sprite*>& vec);
		static void updateHightestLayerIndex();
		static s2d::Sprite* getSpriteById(int id);
		static Sprite* getSpriteByName(std::string name);
		static int highestLayerIndex;

		/// <summary>
		/// Deletes the sprite by the given name.
		/// Hint if you get crashes:
		/// 1. Make sure to not have duped names
		/// 2. Make sure u are not deleting a nullptr
		/// </summary>
		/// <param name="name">The name of the sprite which should be deletet</param>
		static void deleteSpriteByName(const std::string& name);


		//Pointers getting deletet in gameWindow.cpp ~
		static std::vector<s2d::Sprite*> s_sprites;
	};
}

