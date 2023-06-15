#include "stdafx.h"

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT,MOVING_RIGHT, JUMPING, FALLING};
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	
	//animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;
	
	
	//core
	void initVariables();
	void initSprite();
	void initTexture();
	void initAnimations();
	void initPhysics();


public:
	Player();
	virtual ~Player();
	
	//accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	
	//modifiers
	void setPosition(const float x, const float y);
	void resetVelocityX();
	void resetVelocityY();

	//functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

