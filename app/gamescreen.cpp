#include "gamescreen.h"

GameScreen::GameScreen(sf::RenderWindow& window, const sf::FloatRect& game_screen)
    :m_window(&window),
      m_game_screen(game_screen)
{
}

bool GameScreen::load_resources(void)
{

}
