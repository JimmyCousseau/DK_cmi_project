#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard(float x, float y, int width, int height, const std::vector<sf::Image> &images, Repeated repeated, const std::vector<sf::Font> &fonts, const Player *player, bool collide) :
Rectangle(x, y, width, height, images, repeated, 0, false, 0, 0, collide),
m_text_level(x + 580, y + 8, "", fonts[0], 20, -1, 0, false, sf::Color::Blue),
m_text_score(x + 7, y + 7, "", fonts[0], 28),
m_text_player_life(x + 7.3, y + 45.6, "", fonts[0], 15),
m_players(player)
{

}

ScoreBoard::ScoreBoard(float x, float y, int width, int height, const std::vector<sf::Font> &fonts, const Player *player, bool collide, sf::Color color) :
Rectangle(x, y, width, height, 0, false, 0, 0, collide, color),
m_text_level(x + 580, y + 8, "", fonts[0], 20, -1, 0, false, sf::Color::Blue),
m_text_score(x + 7, y + 7, "", fonts[0], 28),
m_text_player_life(x + 7.3, y + 45.6, "", fonts[0], 15),
m_players(player)
{

}
ScoreBoard::~ScoreBoard() {}

void ScoreBoard::draw(sf::RenderWindow &window)
{
    m_text_score.set_text(std::to_string(m_players->get_player_score()));
    m_text_player_life.set_text("Vies : " + std::to_string(m_players->get_player_life()));
    m_text_level.set_text("L=01"); // Need to change if there's other levels
    m_text_level.draw(window);
    m_text_score.draw(window);
    m_text_player_life.draw(window);
}

Element* ScoreBoard::clone() const
{
    return new ScoreBoard(*this);
}

Text ScoreBoard::getTextLevel() const { return m_text_level; }
Text ScoreBoard::getTextScore() const { return m_text_score; }
Text ScoreBoard::getTextVieMario() const { return m_text_player_life; }
