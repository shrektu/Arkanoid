#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "Platform.h"
#include "Block.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


template <class T1, class T2> bool is_intersecting(T1& a, T2& b)
{
    return a.right() >= b.left() && a.left() <= b.right() 
        && a.down() >= b.up() && a.up() <= b.down();
}

bool collision_test(Platform& platform, Ball& ball)
{
    if (!is_intersecting(platform, ball))
        return false;

    ball.move_up();

    if (ball.get_position().x < platform.get_position().x)
        ball.move_left();

    else if (ball.get_position().x > platform.get_position().x)
        ball.move_right();
}

bool collision_test(Block& block, Ball& ball)
{
    if (!is_intersecting(block, ball))
        return false;

    block.destroy();

    // przesuniêcie krawêdzi kulki wzglêdem krawêdzi bloczka

    float overlap_left{ ball.right() - block.left() };
    float overlap_right{ block.right() - ball.left() };
    float overlap_up{ ball.down() - block.up() };
    float overlap_down{ block.down() - ball.up() };

    bool ball_from_left(abs(overlap_left) < abs(overlap_right));        // sprawdŸ czy kulka uderzy³a z lewej 
    bool ball_from_up(abs(overlap_up) < abs(overlap_down));             // sprawdŸ czy kulka uderzy³a z do³u 

    float min_overlap_x{ ball_from_left ? overlap_left : overlap_right };
    float min_overlap_y{ ball_from_up ? overlap_up : overlap_down };

    if (abs(min_overlap_x) < abs(min_overlap_y))
        ball_from_left ? ball.move_left() : ball.move_right();

    else
        ball_from_up ? ball.move_up() : ball.move_down();
}

int main()
{
    sf::RenderWindow window{ sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid Game", sf::Style::Close | sf::Style::Titlebar };
    window.setFramerateLimit(60);

    sf::Font game_over;
    
    if (!game_over.loadFromFile("PixelFont.ttf"))
        throw("COULD NOT LOAD FONT!");

    sf::Text game_over_text, esc_to_exit;

    game_over_text.setString("GAME OVER");
    game_over_text.setFont(game_over);
    game_over_text.setCharacterSize(100);
    game_over_text.setFillColor(sf::Color(255, 255, 255));
    game_over_text.setPosition(window.getSize().x / 4, window.getSize().y / 4);

    esc_to_exit.setString("Press Escape to exit");
    esc_to_exit.setFont(game_over);
    esc_to_exit.setCharacterSize(50);
    esc_to_exit.setFillColor(sf::Color(255, 255, 255));
    esc_to_exit.setPosition(window.getSize().x / 4 - 20, window.getSize().y / 3 + 80);
    
        

    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    Platform platform(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);

    sf::Event ev;


    unsigned int blocks_in_x{ 9 };
    unsigned int blocks_in_y{ 4 };
    unsigned int block_width{ 115 };
    unsigned int block_height{ 40 };

    std::vector<Block> blocks;

    for (int i{ 0 }; i < blocks_in_y; i++)
    {
        for (int j{ 0 }; j < blocks_in_x; j++)
        {
            blocks.emplace_back((j + 1) * (block_width + 10), (i + 1) * (block_height + 10), block_width, block_height);
        }
    }

    while (window.isOpen())
    {

        while (!blocks.empty())
        {
            window.pollEvent(ev);

            if (ev.type == sf::Event::Closed)
            {
                window.close();
                break;
            }


            window.clear(sf::Color::Black);

            if (blocks.empty())
                break;

            ball.update();
            platform.update();

            collision_test(platform, ball);

            for (auto& block : blocks)
                if (collision_test(block, ball))
                    break;

            auto iter = std::remove_if(blocks.begin(), blocks.end(), [](Block& block) {return block.is_destroyed(); });
            blocks.erase(iter, blocks.end());


            window.draw(ball);
            window.draw(platform);

            for (auto& block : blocks)
                window.draw(block);


            window.display();
        }

        window.clear();
        window.draw(game_over_text);
        window.draw(esc_to_exit);
        window.display();

        window.pollEvent(ev);

        if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
    }




    return 0;
}