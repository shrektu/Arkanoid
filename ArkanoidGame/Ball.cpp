#include "Ball.h"

Ball::Ball(float x, float y)
{
	shape.setPosition(x, y);
	shape.setRadius(this->ball_radius);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(this->ball_radius, this->ball_radius);	// ustawienie originu na œrodek kulki

}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Ball::update()
{
	shape.move(this->velocity);

	if (this->left() < 0)
		velocity.x = ball_velocity;

	else if (this->right() > SCREEN_WIDTH)
		velocity.x = -ball_velocity;

	else if (this->up() < 0)
		velocity.y = ball_velocity;

	else if (this->down() > SCREEN_HEIGHT)
		velocity.y = -ball_velocity;
}

float Ball::left()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Ball::right()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Ball::up()
{
	return this->shape.getPosition().y - shape.getRadius();
}

float Ball::down()
{
	return this->shape.getPosition().y + shape.getRadius();
}

void Ball::move_down()
{
	this->velocity.y = ball_velocity;
}

void Ball::move_up()
{
	this->velocity.y = -ball_velocity;
}

void Ball::move_right()
{
	this->velocity.x = ball_velocity;
}

void Ball::move_left()
{
	this->velocity.x = -ball_velocity;
}

sf::Vector2f Ball::get_position()
{
	return shape.getPosition();
}
