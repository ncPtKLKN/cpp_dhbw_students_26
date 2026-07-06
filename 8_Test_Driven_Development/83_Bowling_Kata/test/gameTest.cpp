#include "gtest/gtest.h"
#include "../src/game.hpp"

// TDD-Hinweis:
// Jede Regel wird erst als Test beschrieben (Red), dann minimal implementiert (Green),
// danach wird bei Bedarf refaktoriert (Refactor).

// Fixture fuer alle TEST_F-Faelle: gemeinsamer Zustand + gemeinsame Helper.
class GameTest
    : public ::testing::Test
{
protected:
    Game m_game;

    // Wird vor jedem einzelnen TEST_F ausgefuehrt.
    void SetUp() override
    {
        m_game = Game();
    }

    // Hilfsmethode, um viele gleiche Rolls kompakt zu erzeugen.
    void rollOnlyThisNumber(int nRolls, int rollResult)
    {
        for (int i = 0; i < nRolls; ++i)
        {
            m_game.roll(rollResult);
        }
    }
};


// TEST_F(GameTest, ScoreIsZeroWithOnlyZeroRolls)
    // Start-Test fuer den Zyklus: einfachster gueltiger Fall ohne Bonusregeln.
    // 20-mal 0 Pins => Gesamtpunktzahl 0.

    // Noch ohne Spare/Strike: prueft lineares Summieren ueber alle Frames.
    // 20-mal 1 Pin => Gesamtpunktzahl 20 (ohne Spare/Strike-Bonus).
    // ScoreIsTwentyWithOnlyOnesRolled

    // Spare im ersten Frame: 5 + 5, Bonus ist der naechste Wurf (3).
    // Erwartung: 10 + 3 + Rest(0) = 16.
    // testOneSpare

    // testOneStrike, testPerfectGame, testIncompleteGameOneFrame, testIncompleteGameNineFrames
