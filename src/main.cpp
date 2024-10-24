#include <SFML/Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <sstream>

constexpr double PI = 3.14159265358979323846;

void draw_line(sf::RenderTarget &target, sf::Vector2f p1, sf::Vector2f p2) {
    std::array<sf::Vertex, 2> line = {sf::Vertex(p1), sf::Vertex(p2)};

    target.draw(line.data(), line.size(), sf::Lines);
}

int main() {
    auto window = sf::RenderWindow({800, 600}, "CMake SFML Project");
    window.setFramerateLimit(144);

    auto center = static_cast<sf::Vector2f>(window.getSize()) / 2.f;
    float radius = 0.7f * std::min(window.getSize().x, window.getSize().y) / 2.f;

    sf::CircleShape circle(radius);

    circle.setOrigin({radius, radius});
    circle.setPosition(center);
    circle.setPointCount(PI * radius / 10.f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1.f);

    std::array<sf::Vertex, 4> cross = {
        sf::Vertex(center + sf::Vector2f(-radius, 0.f)),
        sf::Vertex(center + sf::Vector2f(+radius, 0.f)),
        sf::Vertex(center + sf::Vector2f(0.f, -radius)),
        sf::Vertex(center + sf::Vector2f(0.f, radius))
    };

    sf::Font font;
    if (!font.loadFromFile("AnonymousPro-Regular.ttf")) {
        std::cerr << "Failed to load font!\n";
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Q) {
                    window.close();
                }
            }
        }

        sf::Vector2f mouse_dir_center = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - center;
        mouse_dir_center /= std::hypot(mouse_dir_center.x, mouse_dir_center.y);
        sf::Vector2f tangent_direction(-mouse_dir_center.y, mouse_dir_center.x);

        sf::Vector2f circle_point = center + radius * mouse_dir_center;
        mouse_dir_center.y *= -1.f; // In computer graphics (like SFML) the y-axis is usually reversed

        float radians = std::atan2(mouse_dir_center.y, mouse_dir_center.x);
        radians = std::fmod(radians + 2.f * PI, 2.f * PI);
        float degrees = 180.f / PI * radians;

        window.clear();

        window.draw(circle);
        window.draw(cross.data(), cross.size(), sf::Lines);
        draw_line(window, center, circle_point);
        draw_line(window, circle_point, {circle_point.x, center.y});
        draw_line(window, circle_point, circle_point + radius * std::tan(radians) * tangent_direction);

        std::ostringstream ss;
        ss << "Radius = " << radius << "\n\n"
           << "x = " << radius * mouse_dir_center.x << '\n'
           << "y = " << radius * mouse_dir_center.y << '\n'
           << "Angle: " << degrees << "\n\n"
           << "sin(" << degrees << ") = " << std::sin(radians) << '\n' // or mouse_dir_center.y
           << "cos(" << degrees << ") = " << std::cos(radians) << '\n' // or mouse_dir_center.x
           << "tan(" << degrees << ") = " << std::tan(radians);        // or mouse_dir_center.y / mouse_dir_center.x
        text.setString(ss.str());
        window.draw(text);

        window.display();
    }
}
