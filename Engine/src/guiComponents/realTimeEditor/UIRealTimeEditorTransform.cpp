#include "UIRealTimeEditorTransform.h"

// Constructor


s2d::UIRealTimeEditorTransform::UIRealTimeEditorTransform()
{
    this->m_windowEvent = nullptr;
    this->m_isAnyUIWindowHovered = nullptr;
    this->m_cursorRangeToClick = -1;
    this->m_ptr_Window = nullptr;
    this->m_clickedSprite = nullptr;
    this->m_ptr_Inspectorstate = nullptr;
    this->m_realeasedCursorOnSprite = false;
    this->m_clickedSpriteId = -1;
}

s2d::UIRealTimeEditorTransform::UIRealTimeEditorTransform(sf::RenderWindow* window, s2d::InspectorState* ptr_Inspectorstate, bool* isAnyUIWindowHovered, s2d::Event* windowEvent)
{
    this->m_windowEvent = windowEvent;
    this->m_isAnyUIWindowHovered = isAnyUIWindowHovered;
    this->m_ptr_Inspectorstate = ptr_Inspectorstate;
    this->m_cursorRangeToClick = 25;
    this->m_ptr_Window = window;
    this->m_clickedSprite = nullptr;
    this->m_realeasedCursorOnSprite = false;
    this->m_clickedSpriteId = -1;
}

// Public functions

void s2d::UIRealTimeEditorTransform::update()
{
    if (*this->m_isAnyUIWindowHovered)
    {
        return;
    }
    // Check if we click on a sprite in the editor
    s2d::Sprite* clickedSprite = this->checkIfMouseClickedOnSprite();

    sf::Vector2i cursorPos = sf::Mouse::getPosition(*this->m_ptr_Window);
    this->m_cursorWorldPos = this->m_ptr_Window->mapPixelToCoords(cursorPos);
    this->m_cursor.position = s2d::Vector2(this->m_cursorWorldPos.x, this->m_cursorWorldPos.y);
    this->m_cursor.setLastPosition();

    if (clickedSprite != nullptr)
    {
        this->m_clickedSprite = clickedSprite;
        s2d::UIHirachy::selectedSprite = this->m_clickedSprite;

        this->moveComponent();
    }
    else
    {
        this->m_clickedSprite = nullptr;
    }

}

// Private functions

void s2d::UIRealTimeEditorTransform::moveComponent()
{
    float x = this->m_cursorWorldPos.x - 960;
    float y = -(this->m_cursorWorldPos.y - 540);

    s2d::Vector2 pos = s2d::Vector2(this->m_cursorWorldPos.x - 960, -(this->m_cursorWorldPos.y - 540));

    float m = x - this->m_clickedSprite->transform.position.x;
    float my = y - this->m_clickedSprite->transform.position.y;

    if (this->m_cursor.posiitonChanged)
    {
        s2d::Vector2 moved = this->m_cursor.lastPos - this->m_cursor.position;
        m += moved.x;
        my -= moved.y;
    }

    s2d::Vector2 newPosition = s2d::Vector2(x - m, y - my);

    this->m_clickedSprite->transform.position = newPosition;

}

// Check if clicked on a sprite

bool s2d::UIRealTimeEditorTransform::checkClick(s2d::Sprite& sprite)
{
    sf::Vector2i cursorPos = sf::Mouse::getPosition(*this->m_ptr_Window);
    this->m_cursorWorldPos = this->m_ptr_Window->mapPixelToCoords(cursorPos);

    float getPosX = sprite.getSprite().getPosition().x;
    float getPosY = sprite.getSprite().getPosition().y;

    float otherGetPosX = this->m_cursorWorldPos.x;
    float otherGetPosY = this->m_cursorWorldPos.y;

    bool collided = (getPosX + sprite.transform.scale.x >= otherGetPosX
        && getPosX <= otherGetPosX + this->m_cursorRangeToClick
        && getPosY + sprite.transform.scale.y >= otherGetPosY
        && getPosY <= otherGetPosY + this->m_cursorRangeToClick);

    
    if (collided && this->m_windowEvent->type == s2d::Event::Type::MousePressedLeft)
    {
        std::cout << sprite.name << std::endl;
        this->m_windowEvent->type = s2d::Event::Type::None;
        this->m_realeasedCursorOnSprite = true;
        this->m_clickedSpriteId = sprite.getId();
        return true;
    }
    if (this->m_windowEvent->type == s2d::Event::MouseReleasedLeft)
    {
        this->m_windowEvent->type = s2d::Event::None;
        this->m_realeasedCursorOnSprite = false;
        return false;
    }

    // Checking if we have the same ID. If we wouldnt do that check it could just return
    // The next sprite in the list which would be wrong
    if (this->m_realeasedCursorOnSprite && sf::Mouse::isButtonPressed(sf::Mouse::Left) && sprite.getId() == this->m_clickedSpriteId)
    {
        return true;
    }
   
    return false;
}

s2d::Sprite* s2d::UIRealTimeEditorTransform::checkIfMouseClickedOnSprite()
{
    for (int i = 0; i < s2d::Sprite::activeSprites.size(); i++)
    {    
        if(checkClick(*s2d::Sprite::activeSprites[i]))
        {
            return s2d::Sprite::activeSprites[i];
        }
    }

    return nullptr;
}