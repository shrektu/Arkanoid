#include "Platform.h"

Platform::Platform(float x, float y)
{
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Cyan);
	shape.setSize({ this->platform_width, this->platform_height });
	shape.setOrigin(platform_width / 2.f, platform_height / 2.f);
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Platform::update()
{
	this->shape.move(this->velocity);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && this->left() > 0)
		velocity.x = -platform_velocity;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && this->right() < SCREEN_WIDTH)
		velocity.x = platform_velocity;

	else
		velocity.x = 0;
}

float Platform::left()
{
	return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

float Platform::right()
{
	return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

float Platform::up()
{
	return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

float Platform::down()
{
	return this->shape.getPosition().y + shape.getSize().y / 2.f;
}

sf::Vector2f Platform::get_position()
{
	return shape.getPosition();
}
