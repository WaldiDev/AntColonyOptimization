#include "SfmlWindow.h"

#include <SFML/Window.hpp>
#include "SfmlCamera.h"
#include "SfmlInput.h"

SfmlWindow::SfmlWindow(unsigned int windowWidth, unsigned int windowHeight)
	: m_window(nullptr)
	, m_camera(nullptr)
	, m_input(nullptr)
	, m_tileMap()
	, m_antManager(m_tileMap)
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
				auto mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
				m_camera->Zoom(event.mouseWheelScroll.delta, mousePos);
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				auto mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				
				m_tileMap.MouseMovement(mousePos);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				auto mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				auto button = event.mouseButton.button;				
				if (button == 0)
				{
					m_tileMap.MouseClick(mousePos);
				}
			}
		}

		m_window->clear();

		m_input->Update();
		
		if (m_antManager.Run(m_tileMap, m_tileMap))
		{
			printf("");
		}

		m_window->setView(m_camera->GetView());
		
		m_tileMap.Render(*m_window);

		m_window->display();
	}
}
