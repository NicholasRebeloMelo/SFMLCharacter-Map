#include "stdafx.h"
#include "Player.h"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;
	//player
	Player* player;

	//world
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	sf::Vector2u textureSize;
	sf::Vector2u windowSize;

	void initWindow();
	void initPlayer();
	void initWorld();
public:
	Game();
	virtual ~Game();

	//functions
	void updatePlayer();
	void updateCollision();
	void update();
	void renderWorld();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;

};

