#include <iostream>
#include <limits>

#include "game.hpp"

int main()
{
    Game game;

    std::cout << "Bowling Kata - manuelles Spiel\n";
    std::cout << "Gib fuer jeden Wurf die umgeworfenen Pins ein (0-10).\n";
    std::cout << "Mit -1 beendest du die Eingabe und siehst den Score.\n\n";

    int rollNumber = 1;
    while (true)
    {
        std::cout << "Wurf " << rollNumber << ": ";

        int pins = 0;
        if (!(std::cin >> pins))
        {
            std::cout << "Ungueltige Eingabe. Bitte Zahl eingeben.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (pins == -1)
        {
            break;
        }

        if (pins < 0 || pins > 10)
        {
            std::cout << "Bitte nur Werte von 0 bis 10 eingeben oder -1 zum Beenden.\n";
            continue;
        }

        game.roll(pins);
        ++rollNumber;
    }

    std::cout << "\nAktueller Gesamt-Score: " << game.getScore() << "\n";
    return 0;
}
