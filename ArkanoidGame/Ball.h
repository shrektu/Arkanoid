#pragma once

#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


class Ball : public sf::Drawable
{
private:
	sf::CircleShape shape;
	const float ball_radius{ 10.0f };
	const float ball_velocity{ 7.0f };
	sf::Vector2f velocity{ ball_velocity, ball_velocity };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
	Ball(float x, float y);
	Ball() = delete;
	~Ball() = default;

	void update();

	void move_up();
	void move_down();
	void move_right();
	void move_left();

	sf::Vector2f get_position();

	float left();
	float right();
	float up();
	float down();

};

