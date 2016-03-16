#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class SfmlCamera;
class SfmlInput;

class SfmlWindow
{
public:
	explicit SfmlWindow(unsigned int windowWidth, unsigned int windowHeight);
	~SfmlWindow();

	void Run();

private:
	sf::RenderWindow* m_window;
	SfmlCamera* m_camera;
	SfmlInput* m_input;
};

