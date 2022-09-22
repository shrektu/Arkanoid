#include "Block.h"

Block::Block(float x, float y, float width, float height)
{
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Green);
	shape.setSize({ width, height});
	shape.setOrigin(width / 2.f, height / 2.f);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

sf::Vector2f Block::get_position()
{
	return shape.getPosition();
}

float Block::left()
{
	return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

float Block::right()
{
	return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

float Block::up()
{
	return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

float Block::down()
{
	return this->shape.getPosition().y + shape.getSize().y / 2.f;
}

bool Block::is_destroyed() {
	return this->destroyed;
}

void Block::destroy() 
{
	this->destroyed = true;
}

sf::Vector2f Block::get_size() 
{
	return shape.getSize();
}

void Block::update()
{

}