#include "Animator.h"
#include <physicalComponents/sprite.h>

#define EXIST if (!this->exists) return

s2d::Animator::Animator()
{
	this->exists = false;
	this->ptr_attachedSprite = nullptr;
}

s2d::Animator::Animator(Sprite* ptr_attachedSprite)
{
	this->exists = false;
	this->ptr_attachedSprite = ptr_attachedSprite;
	this->animationPlaying.isAAnimationPlaying = false;
	this->animationPlaying.name = "<Unknown>";
}

void s2d::Animator::createAnimation(const std::string& name, const std::vector<s2d::KeyFrame>& textures)
{
	EXIST;
	animations.push_back(Animation(ptr_attachedSprite, name, textures));
}

void s2d::Animator::play(const std::string& name)
{
	EXIST;
	bool found = false;
	for (Animation& anim : animations)
	{
		if (anim.name == name && !this->animationPlaying.isAAnimationPlaying)
		{
			found = true;
			this->animationPlaying.name = name;
			this->animationPlaying.isAAnimationPlaying = true;
			anim.play();
		}
	}
	if (!found)
	{
		std::cout << "LOG [WARNING] Could not find animation (Maybe you tried playing it while it is active or you passed a wrong name?)" << std::endl;
	}
	
}

void s2d::Animator::stop(const std::string& name)
{
	EXIST;
	for (Animation& anim : animations)
	{
		if (anim.name == name && anim.isPlaying)
		{
			this->animationPlaying.name = "<Unknown>";
			this->animationPlaying.isAAnimationPlaying = false;
			anim.stop();
		}
	}
}

void s2d::Animator::update()
{
	EXIST;

	for (Animation& anim : this->ptr_attachedSprite->animator.animations)
	{
		if (anim.isPlaying)
			anim.update();
	}
}

void s2d::Animator::resetComponent()
{
	this->animationPlaying.name = "<Unknown>";;
	this->animationPlaying.isAAnimationPlaying = false;
	this->exists = false;
	this->animations.clear();
}

//Static functions

void s2d::Animator::stopAllAnimations()
{
	for (int i = 0; i < s2d::Sprite::s_sprites.size(); i++)
	{
		s2d::Sprite::s_sprites[i]->animator.stop(s2d::Sprite::s_sprites[i]->animator.animationPlaying.name);
	}
}
