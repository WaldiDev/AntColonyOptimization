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
	if (key < 0 || key >= 256) return;
	m_keyPressedList.at(key) = true;
	
}

void SfmlInput::SetReleasedKey(sf::Keyboard::Key key)
{
	if (key < 0 || key >= 256) return;
	m_keyPressedList.at(key) = false;
}

bool SfmlInput::GetKeyStatus(sf::Keyboard::Key key) const
{
	return m_keyPressedList.at(key);
}

void SfmlInput::Update()
{
	m_camera->Move(GetCameraMovement());
	if (m_keyPressedList.at(sf::Keyboard::LControl))
	{
		
	}
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
