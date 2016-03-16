#include "SfmlWindow.h"

#include <SFML/Window.hpp>
#include "SfmlCamera.h"
#include "SfmlInput.h"
#include "Tile.h"


SfmlWindow::SfmlWindow(unsigned int windowWidth, unsigned int windowHeight)
	: m_window(nullptr)
	, m_camera(nullptr)
	, m_input(nullptr)
{
	m_window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Ant Colony Optimization");

	m_camera = new SfmlCamera(sf::FloatRect(0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
	m_window->setView(m_camera->GetView());
	m_input = new SfmlInput(m_camera);
}

SfmlWindow::~SfmlWindow()
{
	delete m_input;
	delete m_camera;
	delete m_window;
}

void SfmlWindow::Run()
{
	std::vector< std::vector<int>> map{
		{ 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
		{ 2, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
		{ 2, 2, 2, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 6, 6, 7, 7, 7, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
		{ 2, 2, 2, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 6, 7, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
		{ 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 2, 2, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
		{ 2, 2, 3, 3, 3, 2, 1, 1, 4, 4, 1, 1, 3, 3, 3, 3, 2, 2, 2, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 3, 3, 3, 3, 2, 4, 4, 4, 4, 4, 1, 2, 3, 3, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 1, 2, 3, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 1, 2, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 1, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 4, 4, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 7, 7, 7, 7, 7, 6, 6, 6, 4, 4, 4, 4, 4, 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 6, 6, 7, 7, 7, 7, 7, 6, 6, 6, 6, 4, 4, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 2, 2, 2, 2, 2, 6, 6, 6, 2, 2, 2, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };


	std::vector<Tile*> m_tiles;

	for (auto i = 0; i < 30; ++i)
	{
		for (auto y = 0; y < 50; ++y)
		{
			auto c = map[i][y];
			auto type = static_cast<TileType>(c - '0');
			auto tile = new Tile(i, y, static_cast<TileType>(c));
			m_tiles.push_back(tile);
		}
	}

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
			else if (event.type == sf::Event::Resized)
			{
				sf::Vector2f newSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
				m_camera->Resize(newSize);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				m_input->SetPressedKey(event.key.code);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				m_input->SetReleasedKey(event.key.code);
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				auto pos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
				m_camera->Zoom(event.mouseWheelScroll.delta, pos);
			}

		}

		m_window->clear();

		m_input->Update();

		m_window->setView(m_camera->GetView());

		for (auto& m_tile : m_tiles)
		{
			m_tile->Render(*m_window);
		}

		m_window->display();
	}
}
