#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

class SfmlCamera
{
public:
	explicit SfmlCamera(sf::FloatRect viewBox);

	~SfmlCamera();

	void Move(sf::Vector2f offset);
	void Resize(sf::Vector2f newSize);
	void Zoom(float delta, sf::Vector2f mousePos);

	sf::View GetView() const { return m_view; }

private:
	sf::View m_view;
	const float m_Speed = 1.0f;
	const float m_Zoom = 0.5f;
};

