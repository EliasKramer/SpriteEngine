#include "boxCollider.h"

//Includint sprite.h here because we cant in the.h file because we include boxcollider.h already in the sprite.h file
#include <physicalComponents/sprite.h>

//Its always important to give everything a "default value"

s2d::BoxCollider::BoxCollider()
    : isSolid(false), canCollide(false), exists(false), isInCollision(false), sprite(nullptr), collidingSprite(nullptr), collisionCnt(0) { }

s2d::BoxCollider::BoxCollider(s2d::Sprite* sprite)
   : exists(false), isInCollision(false), collidingSprite(nullptr), sprite(sprite), canCollide(false), isSolid(false), collisionCnt(0) { }


bool s2d::BoxCollider::checkCollision(s2d::BoxCollider& other, const int jIndex)
{
    //Already got collision detection working

    if (!this->exists || !other.exists)
    {
        return false;
    }

    //May need to do better sprite pos detection!
    //Using for example this->boxColliderWidthLeftOrRight.y when we getPosX and add sprite size because we can adjust the right widtg in the inspector and the right width is y

    float getPosX = sprite->getSprite().getPosition().x;
    float getPosY = sprite->getSprite().getPosition().y;

    float otherGetPosX = other.sprite->getSprite().getPosition().x;
    float otherGetPosY = other.sprite->getSprite().getPosition().y;

    if (getPosX + sprite->transform.size.x + this->boxColliderWidthLeftOrRight.y >= otherGetPosX + other.boxColliderWidthLeftOrRight.x
        && getPosX + this->boxColliderWidthLeftOrRight.x <= otherGetPosX + other.boxColliderWidthLeftOrRight.y + other.sprite->transform.size.x
        && getPosY + sprite->transform.size.y + this->boxColliderHeightUpOrDown.y >= otherGetPosY + other.boxColliderHeightUpOrDown.x
        && getPosY + this->boxColliderHeightUpOrDown.x <= otherGetPosY + other.boxColliderHeightUpOrDown.y + other.sprite->transform.size.y)
    {
        if (other.isSolid && this->isSolid)
            checkPositions(other, jIndex);
        return true;
    }
    return false;
}

//Private functions

#pragma region  Checking_positions_(setting sprite relative position for collisions (well no shit collision.cpp))

bool s2d::BoxCollider::checkIAndJPCollisions(int i, int j)
{
    bool collided = false;
    if (s2d::Sprite::activeSprites[i]->collider.checkCollision(s2d::Sprite::activeSprites[j]->collider, j))
    {
        collided = true;
    }
    if (s2d::Sprite::activeSprites[j]->collider.checkCollision(s2d::Sprite::activeSprites[i]->collider, j))
    {
        collided = true;
    }
    return collided;
}

void s2d::BoxCollider::checkPositions(const BoxCollider& other, const int jIndex)
{
    short range = 10;

    // Right
    if (this->sprite->getOrigininalPosition().x + this->sprite->transform.size.x >= other.sprite->getOrigininalPosition().x
        && this->sprite->getOrigininalPosition().x + this->sprite->transform.size.x <= other.sprite->getOrigininalPosition().x + range)
    {
        this->positionData.position[this->collisionCnt] = s2d::BoxColliderPositionData::Position::Right;
        this->collisionCnt++;
        return;
    }

    // Left

    if (this->sprite->getOrigininalPosition().x <= other.sprite->getOrigininalPosition().x + other.sprite->transform.size.x
        && this->sprite->getOrigininalPosition().x + range >= other.sprite->getOrigininalPosition().x + other.sprite->transform.size.x)
    {
        this->positionData.position[this->collisionCnt] = s2d::BoxColliderPositionData::Position::Left;
        this->collisionCnt++;
        return;
    }


    // Down

    if (this->sprite->getOrigininalPosition().y + this->sprite->transform.size.y >= other.sprite->getOrigininalPosition().y
        && (this->sprite->getOrigininalPosition().y + this->sprite->transform.size.y <= other.sprite->getOrigininalPosition().y + range))
    {
        this->positionData.position[this->collisionCnt] = s2d::BoxColliderPositionData::Position::Down;
        this->collisionCnt++;
        return;
    }

    // Top

    if (this->sprite->getOrigininalPosition().y <= other.sprite->getOrigininalPosition().y + other.sprite->transform.size.y
        && (this->sprite->getOrigininalPosition().y + range >= other.sprite->getOrigininalPosition().y + other.sprite->transform.size.y))
    {
        this->positionData.position[this->collisionCnt] = s2d::BoxColliderPositionData::Position::Up;
        this->collisionCnt++;
        return;
    }
}

#pragma endregion


//Static functions

void s2d::BoxCollider::checkCollisions()
{

    for (int i = 0; i < s2d::Sprite::activeSprites.size(); i++)
    {
        int nCollide = 0;

        for (int j = i + 1; j < s2d::Sprite::activeSprites.size(); j++)
        {
            if (checkIAndJPCollisions(i, j))
            {
                s2d::Sprite::activeSprites[i]->collider.isInCollision = true;
                s2d::Sprite::activeSprites[j]->collider.isInCollision = true;

                s2d::Sprite::activeSprites[i]->collider.collidingSprite = s2d::Sprite::activeSprites[j];
                s2d::Sprite::activeSprites[j]->collider.collidingSprite = s2d::Sprite::activeSprites[i];
            }
            else
            {
                //Counting the times we dont collide so we can set the "isInCollision" bool to false
                nCollide++;
            }
            if (nCollide == j)
            {
                s2d::Sprite::activeSprites[i]->collider.collidingSprite = nullptr;
                s2d::Sprite::activeSprites[i]->collider.isInCollision = false;
            }
        }
    }
}