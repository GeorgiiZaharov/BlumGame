#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "gamerenderer.h"
#include "gameobjects.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(402, 712), "Blum");
    window.setFramerateLimit(60);

    sf::FloatRect game_board(0,0,402,712);

    Blum blum(game_board);

    if (!GameRenderer::load_resources())
    {
        std::cout << "trouble" << std::endl;
    }
    GameRenderer game_renderer(game_board);
    sf::Clock clock; // Часы для отслеживания времени

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                game_renderer.click(mousePos);
            }
        }
        if (game_renderer.is_game_over())
        {
            window.close();
        }

        // Обновление позиции объекта
        int32_t cur_time = clock.getElapsedTime().asMilliseconds();
        game_renderer.update(cur_time);
        blum.move(cur_time);
        // Очистка окна
        window.clear();

        game_renderer.draw(window, cur_time);
        blum.draw(window, cur_time);
        // Отображение окна
        window.display();
    }

    return 0;
}
