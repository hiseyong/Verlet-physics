#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Circle {
private:
    float radius;
    sf::Vector2f position;
    sf::Vector2f lastPosition;
    sf::Vector2f acceleration;
    sf::CircleShape circleShape;
    bool isDragging;
    sf::Vector2f offset;

public:
    Circle(float radius, float x, float y) : radius(radius), isDragging(false) {
        position.x = x;
        position.y = y;
        lastPosition.x = position.x;
        lastPosition.y = position.y;
        circleShape.setRadius(radius);
        circleShape.setOrigin(radius, radius); // Set origin to the center of the circle
        circleShape.setFillColor(sf::Color::White);
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void update(float dt) {
        if (!isDragging) {
            sf::Vector2f velocity = position - lastPosition;
            lastPosition = position;
            applyGravity();
            applyCircularConstrain(velocity);
            position = position + velocity + acceleration * dt * dt;
            acceleration = {};
        } else {
            lastPosition = position;
        }
    }

    void applyGravity() {
        const sf::Vector2f gravity = {0.0f, 9.8f};
        acceleration += gravity;
    }

    void applyCircularConstrain(sf::Vector2f& velocity) {
        const sf::Vector2f center{400.0f, 300.0f};
        const float constrainRadius = 280.0f;
        const sf::Vector2f distanceVector = position - center;
        const float distance = std::sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

        if (distance > constrainRadius - radius) {
            const sf::Vector2f n = distanceVector / distance;
            position = center + n * (constrainRadius - radius);

            float restitution = 0.9f;
            velocity *= restitution;
        }
    }

    void draw(sf::RenderWindow &window) {
        circleShape.setPosition(position);
        window.draw(circleShape);
    }

    void handleMouseEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (circleShape.getGlobalBounds().contains(mousePos)) {
                    isDragging = true;
                    offset = position - mousePos;
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
            }
        }
        if (event.type == sf::Event::MouseMoved) {
            if (isDragging) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                setPosition(mousePos.x + offset.x, mousePos.y + offset.y);
            }
        }
    }
};