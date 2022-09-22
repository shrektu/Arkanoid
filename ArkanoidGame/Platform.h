#pragma once

#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Platform : public sf::Drawable
{
private:
	sf::RectangleShape shape;
	const float platform_width{ 110.0f };
	const float platform_height{ 10.0f };
	const float platform_velocity{ 10.0f };
	sf::Vector2f velocity{ platform_velocity, 0.0f };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
	Platform(float x, float y);
	Platform() = delete;
	~Platform() = default;

	void update();

	sf::Vector2f get_position();

	float left();
	float right();
	float up();
	float down();

};

