#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <assert.h>

class SfmlCamera;

class SfmlInput
{
public:
	explicit SfmlInput(SfmlCamera* camera);
	~SfmlInput();

	void SetPressedKey(sf::Keyboard::Key key);
	void SetReleasedKey(sf::Keyboard::Key key);

	void Update();

private:
	std::vector<bool> m_keyPressedList;
	SfmlCamera* m_camera;

	sf::Vector2f GetCameraMovement();
};

