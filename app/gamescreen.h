#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>

#include "gamerenderer.h"

class GameScreen
{
public:
    explicit GameScreen(void) = default;
    explicit GameScreen(sf::RenderWindow& window, const sf::FloatRect& game_screen);
    static bool load_resources(void);
    void run(void);
private:
    sf::RenderWindow* m_window = nullptr;
    sf::FloatRect m_game_screen;
    GameRenderer m_game_renderer;
};

#endif // GAMESCREEN_H
