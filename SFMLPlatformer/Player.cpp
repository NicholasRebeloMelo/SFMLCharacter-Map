#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
}

void Player::initTexture()
{
	if(!this->textureSheet.loadFromFile("Textures/adventure_tilesheet.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE:: Couldn't load player sheet" << "\n";
	}
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 20.f;
	this->velocityMin = 1.f;
	this->acceleration = 5.f;
	this->drag = 0.85f;
	this->gravity = 1.f;
	this->velocityMaxY = 10.f;
}


void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 80, 110);// should be 80, 110
	
	this->sprite.setTextureRect(currentFrame);
	this->sprite.setScale(1.6f , 1.6f);
}
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //left
	{
		this->sprite.move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //right
	{
		this->sprite.move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) //right
	{
		this->sprite.move(0.f, -1.f);
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;
	}
	
	
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //top
	//{
	//	this->sprite.move(0.f, -1.f);
	//	
	//}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //down
	//{
	//	this->sprite.move(0.f, 1.f);
	//	
	//}
}
void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE) 
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 150.f)
			{
				this->currentFrame.left = 0;
			}
			
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 99.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 150.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
	{
		this->animationTimer.restart();
	}
}

void Player::move(const float dir_x, const float dir_y)
{
	//acceleration
	this->velocity.x += dir_x * this->acceleration;
	
	
	//limit velocity
	if(std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;
	if(this->animationSwitch)
	{
		this->animationSwitch = false;
	}
	return anim_switch;
}
const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const 
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::updatePhysics() 
{
	//gravity
	 this->velocity.y += 1.0 * this->gravity; 
	 //limit gravity
	 if (std::abs(this->velocity.x) > this->velocityMaxY)
	 {
		 this->velocity.y = velocityMaxY * ((this->velocity.y < 0.f) ? -0.5f : 0.5f);
	 }

	//deceleration
	this->velocity *= this->drag;
	//limit deceleration
	if(std::abs(this->velocity.x < this->velocityMin))
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y < this->velocityMin))
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);

}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
