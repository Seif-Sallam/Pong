#include "Player.h"

Player::Player(const sf::Vector2f& size, const sf::Vector2f& position, float playerSpeed)
	:m_fPlayerSpeed(playerSpeed)
{
	m_body.setSize(size);
	m_body.setOrigin(size / 2.0f);
	m_body.setPosition(position);
}

void Player::Move(const sf::Vector2f& direction)
{
	m_body.move(direction * m_fPlayerSpeed);
}

bool Player::IsColliding(const sf::FloatRect& other)
{
	return (other.intersects(m_body.getGlobalBounds()));
}

void Player::SetScale(const sf::Vector2f& scale)
{
	if(scale.x > 0.f && scale.y > 0.f)
		m_body.setScale(scale);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	m_body.setPosition(pos);
}

sf::FloatRect Player::GetBounds()
{
	return m_body.getGlobalBounds();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_body, state);
}