#pragma once

#include "Rectangle.hpp"
#include "Player.hpp"
#include "Text.hpp"

class ScoreBoard : public Rectangle 
{
public:
    ScoreBoard(float x, float y, int width, int height, const std::vector<sf::Image> &images, Repeated repeated, const std::vector<sf::Font> &fonts, const Player *player, bool collide = false);
    ScoreBoard(float x, float y, int width, int height, const std::vector<sf::Font> &fonts, const Player *player, bool collide = false, sf::Color color = sf::Color::White);
    ~ScoreBoard();

    void draw(sf::RenderWindow &window) override;

    // return a pointer to a copy of this element
    Element* clone() const override;

    // Getters
    Text getTextLevel() const;
    Text getTextScore() const;
    Text getTextVieMario() const;

private:
    Text m_text_level;
    Text m_text_score;
    Text m_text_player_life;
    const Player *m_players;
};
