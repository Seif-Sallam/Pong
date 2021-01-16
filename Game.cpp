#include "Game.h"

Game::Game(const int& sWidth, const int& sHeight)
{
	m_window = new sf::RenderWindow(sf::VideoMode(sWidth, sHeight), "Pong");
	m_event = new sf::Event();
	m_window->setFramerateLimit(60);
	m_fCharacterSize = {2.0f, 80.f};
	m_window->setPosition(sf::Vector2i(0, 0));
	m_fTotalTime = 0;
	m_fPlayGroundSize = { 800.f, 600.0f };
	m_view.setSize(sf::Vector2f(m_window->getSize()));
	m_view.setCenter(m_view.getSize() / 2.0f);

	p1 = new Player(m_fCharacterSize, sf::Vector2f(m_fCharacterSize.x * 3.0f + 30.0f, m_fPlayGroundSize.y / 2.0f));
	p2 = new Player(m_fCharacterSize, sf::Vector2f(m_fPlayGroundSize.x - (m_fCharacterSize.x * 3.0f + 30.0f), m_fPlayGroundSize.y / 2.0f));

	ball = new Ball(10.0f, m_fPlayGroundSize / 2.0f);
	srand(time(0));
	m_upperWall = sf::FloatRect(0.0f, 0.0f, m_fPlayGroundSize.x, 2.0f);
	m_downWall = sf::FloatRect(0.0f, m_fPlayGroundSize.y, m_fPlayGroundSize.x, 2.0f);
	m_rightWall = sf::FloatRect(m_fPlayGroundSize.x + 2.0f, 0.0f, 2.0f, m_fPlayGroundSize.y);
	m_leftWall = sf::FloatRect(-2.0f, 0.0f, 2.0f, m_fPlayGroundSize.y);
	
	p1Score = 0;
	p2Score = 0;
	m_font.loadFromFile("game_over.ttf");
	m_tScore1.setFont(m_font);
	m_tScore2.setFont(m_font);
	m_tScore1.setCharacterSize(100.0f);
	m_tScore2.setCharacterSize(100.0f);
	m_tScore1.setString(std::to_string(p1Score));
	m_tScore2.setString(std::to_string(p2Score));
	m_tScore1.setPosition(sf::Vector2f(40.0f, 0.0f));
	m_tScore2.setPosition(sf::Vector2f(m_fPlayGroundSize.x - 80.f, 0.0f));
}

void Game::Run()
{
	while (m_window->isOpen())
	{
		EventHandler();
		Update();
		Draw();
	}
}

void Game::EventHandler()
{
	while (m_window->pollEvent(*m_event))
	{
		if (m_event->type == sf::Event::Closed)
			m_window->close();
		if (m_event->type == sf::Event::Resized)
		{
			m_view.setSize(sf::Vector2f(m_window->getSize()));
			m_view.setCenter(m_view.getSize() / 2.0f); // Needs to change based on the propotions
		}
		if (EventKeyPressed(sf::Keyboard::Space))
		{
			ball->StartMove();
		}
		if (EventKeyPressed(sf::Keyboard::R)) {
			ball->Reset();
			p1Score = 0;
			p2Score = 0;
			p1->SetScale(sf::Vector2f(1.f, 1.f));
			p2->SetScale(sf::Vector2f(1.f, 1.f));
			p1->SetPosition(sf::Vector2f(m_fCharacterSize.x * 3.0f + 30.0f, m_fPlayGroundSize.y / 2.0f));
			p2->SetPosition(sf::Vector2f(m_fPlayGroundSize.x - (m_fCharacterSize.x * 3.0f + 30.f), m_fPlayGroundSize.y / 2.0f));
			m_tScore1.setString(std::to_string(p1Score));
			m_tScore2.setString(std::to_string(p2Score));
			m_fTotalTime = 0.f;
		}
	}
}

void Game::Update()
{
	float deltaTime = m_clock.restart().asSeconds();
	m_fTotalTime += deltaTime;
	
	if (RLKeyPressed(sf::Keyboard::Up) && !p1->GetBounds().intersects(m_upperWall))
	{
		p1->Move(sf::Vector2f(0, -1 * deltaTime));
	}
	else if (RLKeyPressed(sf::Keyboard::Down) && !p1->GetBounds().intersects(m_downWall))
	{
		p1->Move(sf::Vector2f(0, +1 * deltaTime));
	}

	if (RLKeyPressed(sf::Keyboard::W) && !p2->GetBounds().intersects(m_upperWall))
	{
		p2->Move(sf::Vector2f(0, -1 * deltaTime));
	}
	else if (RLKeyPressed(sf::Keyboard::S) && !p2->GetBounds().intersects(m_downWall))
	{
		p2->Move(sf::Vector2f(0, +1 * deltaTime));
	}


	ball->HitPlayer(p1->GetBounds());
	ball->HitPlayer(p2->GetBounds());
	
	if (ball->GetBounds().intersects(m_upperWall) || ball->GetBounds().intersects(m_downWall))
	{
		ball->HitWall();
	}

	if (ball->GetBounds().intersects(m_rightWall))
	{
		ball->Reset();
		p1->SetScale(sf::Vector2f(1.f, 1.f));
		p2->SetScale(sf::Vector2f(1.f, 1.f));
		p1->SetPosition(sf::Vector2f(m_fCharacterSize.x * 3.0f + 30.f, m_fPlayGroundSize.y / 2.0f));
		p2->SetPosition(sf::Vector2f(m_fPlayGroundSize.x - (m_fCharacterSize.x * 3.0f + 30.0f), m_fPlayGroundSize.y / 2.0f));
		p1Score++;
		m_tScore1.setString(std::to_string(p1Score));
		m_fTotalTime = 0.f;
	}
	if (ball->GetBounds().intersects(m_leftWall))
	{
		ball->Reset();
		p1->SetScale(sf::Vector2f(1.f, 1.f));
		p2->SetScale(sf::Vector2f(1.f, 1.f));
		p1->SetPosition(sf::Vector2f(m_fCharacterSize.x * 3.0f + 30.f, m_fPlayGroundSize.y / 2.0f));
		p2->SetPosition(sf::Vector2f(m_fPlayGroundSize.x - (m_fCharacterSize.x * 3.0f + 30.0f), m_fPlayGroundSize.y / 2.0f));
		p2Score++;
		m_tScore2.setString(std::to_string(p2Score));
		m_fTotalTime = 0.f;
	}
	ball->Move(deltaTime);
	p1->SetScale(sf::Vector2f(1.0f, 1 - m_fTotalTime * scalingChange));
	p2->SetScale(sf::Vector2f(1.0f, 1 - m_fTotalTime * scalingChange));
}

void Game::Draw()
{
	m_window->clear(sf::Color::Black);
	m_window->setView(m_view);
	m_window->draw(*ball);
	m_window->draw(*p1);
	m_window->draw(*p2);
	m_window->draw(m_tScore1);
	m_window->draw(m_tScore2);
	m_window->display();
}

bool Game::EventKeyPressed(sf::Keyboard::Key k)
{
	if (m_event)
	{
		return (m_event->type == sf::Event::KeyPressed && m_event->key.code == k);
	}
	return false;
}

bool Game::RLKeyPressed(sf::Keyboard::Key k)
{
	return sf::Keyboard::isKeyPressed(k);
}
