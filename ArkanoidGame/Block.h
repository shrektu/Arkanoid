#pragma once

#include <SFML/Graphics.hpp>


class Block : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape shape;
	bool destroyed{ false };

public:
	Block(float x, float y, float width, float height);
	Block() = delete;
	~Block() = default;

	void update();

	sf::Vector2f get_position();

	float left();
	float right();
	float up();
	float down();

	bool is_destroyed();
	void destroy();
	sf::Vector2f get_size();
};

