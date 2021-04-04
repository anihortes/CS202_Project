#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using std::vector;

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("../cute_image.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("../sansation.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Red);
    // Load a music to play
    //   sf::Music music;
    //   if (!music.openFromFile("../nice_music.ogg"))
    //      return EXIT_FAILURE;
    //   // Play the music
    //   music.play();
    // Start the event loop
    sf::Clock clock;// starts the clock
    auto prevTime = clock.getElapsedTime();
    float circleX{};
    float circleY{};

    auto circleRadius = 40.0f;
    sf::CircleShape circle(circleRadius);
    vector<sf::Color> circleColors{sf::Color::Red,sf::Color::Green,sf::Color::Blue};
    int circleColorIndex = 0;
    circle.setFillColor(circleColors[circleColorIndex]);
    double circleTimeSinceLastColorChange = 0.0;

    while (window.isOpen()) {
        auto nowTime = clock.getElapsedTime();
        auto elapsedTime = (nowTime.asSeconds() - prevTime.asSeconds());
        circleTimeSinceLastColorChange += elapsedTime;
        if (circleTimeSinceLastColorChange > 1.0f) {
            --circleTimeSinceLastColorChange;
            circleColorIndex = (circleColorIndex + 1) % circleColors.size();
            circle.setFillColor(circleColors[circleColorIndex]);
        }
        prevTime = nowTime;
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                circleX = event.mouseMove.x-circleRadius;
                circleY = event.mouseMove.y-circleRadius;
                circle.setPosition(circleX,circleY);
            }
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);

        // define a circle with radius = 200
        window.draw(circle);

        // Draw the string
        //      window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
