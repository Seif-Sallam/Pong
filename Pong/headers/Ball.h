#pragma once
#include "SFML/Graphics.hpp"
#include <math.h>
#include <iostream>

class Ball: public sf::Drawable
{
public:
	Ball(const float& radius, const sf::Vector2f& position, float speed = 300.f);
	void StartMove();
	void Move(float deltaTime);
	void HitPlayer(const sf::FloatRect& other);
	void HitWall();
	sf::Vector2f GetPosition();
	void Reset();
	sf::FloatRect GetBounds();

private:
	float GetRadianAngle(float degree);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

private:
	sf::RectangleShape m_shape;
	float m_fAngle;
	float m_fSpeed;
	bool m_bCanMove;
	bool m_bFirstMove;
	sf::Vector2f m_fLastDirection;
	sf::Vector2f m_fOGPosition;
};

