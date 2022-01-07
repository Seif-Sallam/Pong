#include "Ball.h"

Ball::Ball(const float& radius, const sf::Vector2f& position, float speed)
{
	m_shape.setSize(sf::Vector2f(radius * 2.0f, radius * 2.0f));
	m_fOGPosition = position;
	m_shape.setOrigin(radius / 2.0f, radius / 2.0f);
	m_shape.setPosition(position);
	m_bCanMove = false;
	m_bFirstMove = true;
	m_fAngle = 45.0f;
	m_fSpeed = speed;
}

void Ball::StartMove()
{
	if (m_bCanMove == false)
	{
		m_bCanMove = true;
	}
	else
		m_bCanMove = false;
}

void Ball::Move(float deltaTime)
{
	if (m_bCanMove) {
		if (m_bFirstMove)
		{
			m_fAngle = (rand() % 360);
			m_fLastDirection = sf::Vector2f(std::cos(GetRadianAngle(m_fAngle)), std::sin(GetRadianAngle(m_fAngle)));
		} 
		m_shape.move(m_fLastDirection * m_fSpeed * deltaTime);
		m_bFirstMove = false;
	}
}

void Ball::HitPlayer(const sf::FloatRect& other)
{
	if(m_shape.getGlobalBounds().intersects(other))
		m_fLastDirection.x = - m_fLastDirection.x;
}

void Ball::HitWall()
{
	m_fLastDirection.y = -m_fLastDirection.y;
}

sf::Vector2f Ball::GetPosition()
{
	return m_shape.getPosition();
}

void Ball::Reset()
{
	m_shape.setPosition(m_fOGPosition);
	m_bCanMove = false;
	m_bFirstMove = true;
}

sf::FloatRect Ball::GetBounds()
{
	return m_shape.getGlobalBounds();
}

float Ball::GetRadianAngle(float degree)
{
	return (degree * 3.14 / 180.f);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_shape, state);
}
