#include "game.hpp"

namespace
{
// Defensiver Zugriff: vereinfacht Bonusberechnungen und macht Randfaelle robust.
int getRollResult(const std::vector<int>& rolls, int idx)
{
   if (idx < 0 || idx >= static_cast<int>(rolls.size()))
   {
      return 0;
   }
   return rolls[static_cast<std::vector<int>::size_type>(idx)];
}
}


Game::Game()
: m_rollResults{}
{
}


void Game::roll(int rollResult)
{
   m_rollResults.push_back(rollResult);
}


int Game::getScore()
{
   // Erst pruefen, ob ein vollstaendiges Spiel vorliegt.
   // Diese Regel ist testgetrieben durch die Incomplete-Tests entstanden.
   if (!isCompleteGame())
   {
      return -1;
   }

   int score = 0;
   int rollIndex = 0;

   for (int frame = 0; frame < 10; ++frame)
   {
      // TDD-Refactoring: Regelwerk in kleine, klar benannte Helfer aufteilen.
      if (isStrike(rollIndex))
      {
         score += 10 + getStrikeBonus(rollIndex);
         rollIndex += 1;
      }
      else if (isSpare(rollIndex))
      {
         score += 10 + getSpareBonus(rollIndex);
         rollIndex += 2;
      }
      else
      {
         score += getRegularPointsInFrame(rollIndex);
         rollIndex += 2;
      }
   }

   return score;
}

bool Game::isCompleteGame()
{
   // Diese Methode kapselt ausschliesslich die Gueltigkeit/Vollstaendigkeit
   // des Inputs, nicht die eigentliche Punktberechnung.
   const auto nRolls = static_cast<int>(m_rollResults.size());
   int rollIndex = 0;

   for (int frame = 0; frame < 10; ++frame)
   {
      if (rollIndex >= nRolls)
      {
         return false;
      }

      const int firstRoll = m_rollResults[static_cast<std::vector<int>::size_type>(rollIndex)];

      if (firstRoll == 10)
      {
         if (frame == 9)
         {
            return (rollIndex + 2) < nRolls;
         }

         rollIndex += 1;
         continue;
      }

      if ((rollIndex + 1) >= nRolls)
      {
         return false;
      }

      const int secondRoll = m_rollResults[static_cast<std::vector<int>::size_type>(rollIndex + 1)];
      const int frameScore = firstRoll + secondRoll;

      if (frameScore > 10)
      {
         return false;
      }

      if (frame == 9)
      {
         if (frameScore == 10)
         {
            return (rollIndex + 2) < nRolls;
         }

         return (rollIndex + 1) < nRolls;
      }

      rollIndex += 2;
   }

   return true;
}

bool Game::isStrike(int rollIndex)
{
   return getRollResult(m_rollResults, rollIndex) == 10;
}

bool Game::isSpare(int rollIndex)
{
   return getRegularPointsInFrame(rollIndex) == 10;
}

int Game::getStrikeBonus(int rollIndex)
{
   return getRollResult(m_rollResults, rollIndex + 1) + getRollResult(m_rollResults, rollIndex + 2);
}

int Game::getSpareBonus(int rollIndex)
{
   return getRollResult(m_rollResults, rollIndex + 2);
}

int Game::getRegularPointsInFrame(int rollIndex)
{
   return getRollResult(m_rollResults, rollIndex) + getRollResult(m_rollResults, rollIndex + 1);
}
