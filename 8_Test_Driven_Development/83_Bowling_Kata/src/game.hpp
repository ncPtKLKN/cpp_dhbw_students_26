#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

class Game
{
public:
    // API bewusst klein halten: in TDD nur das freigeben, was Tests wirklich benoetigen.
    Game();
    void roll(int);
    int getScore();

private:
    bool isCompleteGame();
    bool isStrike(int);
    bool isSpare(int);
    int getStrikeBonus(int);
    int getSpareBonus(int);
    int getRegularPointsInFrame(int);

    std::vector<int> m_rollResults;
};


#endif // GAME_HPP