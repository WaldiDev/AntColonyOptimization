#include "SfmlInput.h"

#include "SfmlCamera.h"

SfmlInput::SfmlInput(SfmlCamera* camera)
	: m_camera(camera)
{
	m_keyPressedList.resize(256);
}

SfmlInput::~SfmlInput()
{
}

void SfmlInput::SetPressedKey(sf::Keyboard::Key key)
{	
	assert(key >= 0 || key < 256);
	m_keyPressedList.at(key) = true;
	
}

void SfmlInput::SetReleasedKey(sf::Keyboard::Key key)
{
	assert(key >= 0 || key < 256);
	m_keyPressedList.at(key) = false;
}

void SfmlInput::Update()
{
	m_camera->Move(GetCameraMovement());
}

sf::Vector2f SfmlInput::GetCameraMovement()
{
	sf::Vector2f cameraMovement;

	if (m_keyPressedList.at(sf::Keyboard::W) || m_keyPressedList.at(sf::Keyboard::Up))
	{
		cameraMovement.y--;
	}

	if (m_keyPressedList.at(sf::Keyboard::S) || m_keyPressedList.at(sf::Keyboard::Down))
	{
		cameraMovement.y++;
	}

	if (m_keyPressedList.at(sf::Keyboard::D) || m_keyPressedList.at(sf::Keyboard::Right))
	{
		cameraMovement.x++;
	}

	if (m_keyPressedList.at(sf::Keyboard::A) || m_keyPressedList.at(sf::Keyboard::Left))
	{
		cameraMovement.x--;
	}

	return cameraMovement;
}
