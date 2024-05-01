#include "game.h"
#include <iostream>

game::game():
    window(sf::VideoMode(800, 600), "Santorini")
{
    w = new world(window, this);
}

game::~game()
{
    delete w;
}

void game::play()
{
    w->update();
    w->draw();
}

void game::victory()
{
    sf::Font font;
    if (!font.loadFromFile("Data/Fonts/heorot.ttf"))
    {
        std::cout << "Failed To load Font" << std::endl;
    }

    sf::Text victoryText;

    victoryText.setFont(font);
    victoryText.setString("Victory!");
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::White);
    victoryText.setPosition(300, 100);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        state = gamestate::play;
        delete w;
        w = new world(window, this);
        w->setup();
    }

    window.draw(victoryText);
}

void game::defeat()
{
    sf::Font font;
    if (!font.loadFromFile("Data/Fonts/heorot.ttf"))
    {
        std::cout << "Failed To load Font" << std::endl;
    }

    sf::Text defeatText;

    defeatText.setFont(font);
    defeatText.setString("Defeat!");
    defeatText.setCharacterSize(50);
    defeatText.setFillColor(sf::Color::White);
    defeatText.setPosition(300, 100);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        state = gamestate::play;
        delete w;
        w = new world(window, this);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        std::cout << "Terminate" << std::endl;
        state = gamestate::terminate;
    }

    window.draw(defeatText);
}

void game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        switch (state) {
            case gamestate::play:
                play();
                break;
            case gamestate::victory:
                victory();
                break;
            case gamestate::defeat:
                defeat();
                break;
            case gamestate::terminate:
                return;
            default:
                break;       
        }
        window.display();
    }
}
