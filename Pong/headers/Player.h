#pragma once
#include "SFML/Graphics.hpp"

class Player : public sf::Drawable
{
public:
	Player(const sf::Vector2f& size, const sf::Vector2f& position, float playerSpeed = 300.0f);
	void Move(const sf::Vector2f& direction);
	bool IsColliding(const sf::FloatRect& other); // basic collision from the library
	void SetScale(const sf::Vector2f& scale);
	void SetPosition(const sf::Vector2f& pos);
	sf::FloatRect GetBounds();
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
private:
	sf::RectangleShape m_body;
	float m_fPlayerSpeed;
};

