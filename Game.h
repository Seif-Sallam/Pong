#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h" 
#include "Ball.h"
#include <iostream>
#include <string>

class Game
{
public:
	Game(const int& sWidth,const int& sHeight);
	void Run();

private:
	void EventHandler();
	void Update();
	void Draw();

	bool EventKeyPressed(sf::Keyboard::Key k);
	bool RLKeyPressed(sf::Keyboard::Key k);
private:
	sf::RenderWindow* m_window;
	sf::Event* m_event;
	sf::View m_view;
	sf::Clock m_clock;
	Player* p1;
	Player* p2;
	Ball* ball;
	sf::Vector2f m_fPlayGroundSize;
	sf::Vector2f m_fCharacterSize;
	sf::FloatRect m_upperWall;
	sf::FloatRect m_downWall;
	sf::FloatRect m_rightWall;
	sf::FloatRect m_leftWall;

	int p1Score;
	int p2Score;
	float m_fTotalTime = 0;
	float scalingChange = .02;
	
	sf::Text m_tScore1;
	sf::Text m_tScore2;
	sf::Font m_font;

};

