#include "SfmlCamera.h"

SfmlCamera::SfmlCamera(sf::FloatRect viewBox)
{
	m_view.reset(viewBox);
}

SfmlCamera::~SfmlCamera()
{
}

void SfmlCamera::Move(sf::Vector2f offset, float speed = 1.f)
{
	offset *= speed;
	m_view.move(offset);
}

void SfmlCamera::Resize(sf::Vector2f newSize)
{
	m_view.setSize(newSize);
}

void SfmlCamera::Zoom(float delta, float factor)
{
	if (delta < 0)
	{
		m_view.zoom(1 + factor);
	}
	else
	{
		//m_view.setCenter(mousePos);
		m_view.zoom(1 - factor);
	}
	
}
