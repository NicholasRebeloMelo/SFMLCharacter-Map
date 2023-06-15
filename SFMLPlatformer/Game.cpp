#include"stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Nick's Platformer", sf::Style::Close | sf::Style::Titlebar );
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/backgroundColorDesert.png"))
	{
		std::cout << "ERROR::GAME::INITWORLD: Unable to load background!" << "\n";
	} 
	else
	{
		textureSize = worldBackgroundTex.getSize();
		windowSize = window.getSize();

		float scaleX = (float)windowSize.x / textureSize.x;
		float scaleY = (float)windowSize.y / textureSize.y;

		this->worldBackground.setTexture(this->worldBackgroundTex);
		this->worldBackground.setScale(scaleX, scaleY);
	}
}

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}


void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	//bottom of screen collision
	if(this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height);
	}else if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->window.getSize().x)
	{
		this->player->resetVelocityX();
		this->player->setPosition(
			this->player->getPosition().y,
			this->window.getSize().x - this->player->getGlobalBounds().height);
	}
}

void Game::update()
{
	//polling window events
	while(this->window.pollEvent(this->ev))
	{
		if(this->ev.type == sf::Event::Closed)
		{
			this->window.close();
		}else if(ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
		{
			this->window.close();
		}

		if (this->ev.type == sf::Event::KeyReleased &&
		   (this->ev.key.code == sf::Keyboard::A ||
			this->ev.key.code == sf::Keyboard::D || 
			this->ev.key.code == sf::Keyboard::W ||
			this->ev.key.code == sf::Keyboard::S  ))
		{
			this->player->resetAnimationTimer();
		}
	}
	this->updatePlayer();

	this->updateCollision();
}

void Game::renderWorld()
{
	this->window.draw(this->worldBackground);
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();
	//Draw world
	this->renderWorld();

	//render game
	this->renderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}
