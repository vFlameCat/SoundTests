#include <format>

#include <SFML/Graphics.hpp>
#include <SoundPlayer.hpp>


bool isCloseWindowEvent (const std::optional<sf::Event> &event) {

    if (event->is<sf::Event::Closed>()) {

        return true;
    }
    else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {

            return true;
        }
    }

    return false;
}


int main() {

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "SoundTests");
    window.setFramerateLimit(60);


    SoundPlayer player("7NA.mp3");
    player.start();


    sf::Font font("ComicSansMS.ttf"); 
    sf::Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);


    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (isCloseWindowEvent(event)) {

                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {

                    player.swith();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {

                    player.adjustPitch(0.1);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {

                    player.adjustPitch(-0.1);
                }
            }
        }

        text.setString("Pitch: " + std::format("{:.2f}", player.getPitch()));


        window.clear();

        window.draw(text);

        window.display();
    }
}
