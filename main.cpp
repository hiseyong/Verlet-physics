#include <SFML/Graphics.hpp>
#include "Circle.h"

void drawConstrain(sf::RenderWindow &window) {
    sf::CircleShape circleShape;
    circleShape.setRadius(280.0f);
    circleShape.setOrigin(280.0f, 280.0f); // Set origin to the center of the circle
    circleShape.setFillColor(sf::Color::Black);
    sf::Vector2f position{400.0f, 300.0f};
    circleShape.setPosition(position);
    window.draw(circleShape);
}

void applyDistanceConstraint(Circle& c1, Circle& c2, float restLength) {
    sf::Vector2f pos1 = c1.getPosition();
    sf::Vector2f pos2 = c2.getPosition();
    sf::Vector2f delta = pos2 - pos1;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float difference = (distance - restLength) / distance;

    if (distance != 0) {
        sf::Vector2f offset = delta * difference * 0.5f;
        c1.setPosition(pos1.x + offset.x, pos1.y + offset.y);
        c2.setPosition(pos2.x - offset.x, pos2.y - offset.y);
    }
}

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const bool isConstrain = true;
    const int numCircles = 3;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Circles with String Constraint");


    std::vector<Circle> circles;
    circles.reserve(numCircles);

    for (int i = 0; i < numCircles; ++i) {
        float x = 300.0f + i * 50.0f;
        float y = 300.0f;
        Circle circle(10.0f, x, y);
        circles.push_back(circle);
    }

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            for (auto& circle : circles) {
                circle.handleMouseEvent(event, window);
            }
        }

        float deltaTime = 0.002;

        for (auto& circle : circles) {
            circle.update(deltaTime);
        }

        if (isConstrain)
        for (int i = 0; i < circles.size() - 1; ++i) {
            applyDistanceConstraint(circles[i], circles[i + 1], 100.0f);
        }

        window.clear(sf::Color(128, 128, 128));

        drawConstrain(window);
        for (auto& circle : circles) {
            circle.draw(window);
        }

        if (isConstrain)
        for (int i = 0; i < circles.size() - 1; ++i) {
            sf::Vertex line[] =
                    {
                            sf::Vertex(circles[i].getPosition(), sf::Color::White),
                            sf::Vertex(circles[i + 1].getPosition(), sf::Color::White)
                    };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
