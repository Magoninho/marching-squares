#include <math.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "OpenSimplexNoise.hpp"

constexpr int WIDTH = 1980;
constexpr int HEIGHT = 1080;
constexpr int8_t RESOLUTION = 10;

// TODO
constexpr int cols = (1 + WIDTH / RESOLUTION);
constexpr int rows = (1 + HEIGHT / RESOLUTION);

double zoff = 0.0;
int seed = 1;
double field[cols][rows];

int get_state(int a, int b, int c, int d) {
    return a * 8 + b * 4 + c * 2 + d * 1;
}

// sim eu sei que tem uma caralhada de função aí, nao sei fazer de outra maneira, nao sei overloading e nem sei se daria pra
// usar overloading nisso aí.

void drawTriangle(sf::RenderWindow &window, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = a;
    triangle[1].position = b;
    triangle[2].position = c;
    window.draw(triangle);
}

void drawQuad(sf::RenderWindow &window, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) {
    sf::VertexArray quad(sf::TrianglesStrip, 5);
    quad[0].position = a;
    quad[1].position = b;
    quad[2].position = c;
    quad[3].position = d;
    quad[4].position = a;
    window.draw(quad);
}

void drawPentagon(sf::RenderWindow &window, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, sf::Vector2f e) {
    sf::ConvexShape pentagon;
    pentagon.setPointCount(5);
    pentagon.setPoint(0, a);
    pentagon.setPoint(1, b);
    pentagon.setPoint(2, c);
    pentagon.setPoint(3, d);
    pentagon.setPoint(4, e);
    window.draw(pentagon);
}

void drawHexagon(sf::RenderWindow &window, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, sf::Vector2f e, sf::Vector2f f) {
    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);
    hexagon.setPoint(0, a);
    hexagon.setPoint(1, b);
    hexagon.setPoint(2, c);
    hexagon.setPoint(3, d);
    hexagon.setPoint(4, e);
    hexagon.setPoint(5, f);
    window.draw(hexagon);
}

OpenSimplexNoise noise;

void desenha(sf::RenderWindow &window) {
    // gera terreno
    double xoff = 0.0;
    for (int i = 0; i < cols; i++) {
        xoff += 0.1;
        double yoff = 0.0;
        for (int j = 0; j < rows; j++) {
            double value = ceil(noise.Evaluate(xoff, yoff, zoff));
            field[i][j] = value;
            // std::cout << field[i][j] << std::endl;
            yoff += 0.1;
        }
    }
    zoff += 0.05;

    for (int i = 0; i < cols - 1; i++) {
        for (int j = 0; j < rows - 1; j++) {
            sf::Vertex point(sf::Vector2f(i * RESOLUTION, j * RESOLUTION), sf::Color::White);
            window.draw(&point, 1, sf::Points);
        }
    }

    for (int i = 0; i < cols - 1; i++) {
        for (int j = 0; j < rows - 1; j++) {
            int x = i * RESOLUTION;
            int y = j * RESOLUTION;
            sf::Vector2f a = sf::Vector2f(x + RESOLUTION * 0.5, y);
            sf::Vector2f b = sf::Vector2f(x + RESOLUTION, y + RESOLUTION * 0.5);
            sf::Vector2f c = sf::Vector2f(x + RESOLUTION * 0.5, y + RESOLUTION);
            sf::Vector2f d = sf::Vector2f(x, y + RESOLUTION * 0.5);

            int state = get_state(field[i][j], field[i + 1][j], field[i + 1][j + 1], field[i][j + 1]);

            switch (state) {
            case 1:
                drawTriangle(window, c, d, sf::Vector2f(x, y + RESOLUTION));
                break;
            case 2:
                drawTriangle(window, b, c, sf::Vector2f(x + RESOLUTION, y + RESOLUTION));
                break;
            case 3:
                drawQuad(window, b, d, sf::Vector2f(x, y + RESOLUTION), sf::Vector2f(x + RESOLUTION, y + RESOLUTION));
                break;
            case 4:
                drawTriangle(window, a, b, sf::Vector2f(x + RESOLUTION, y));
                break;
            case 5:
                drawHexagon(window, a, sf::Vector2f(x + RESOLUTION, y), b, c, sf::Vector2f(x, y + RESOLUTION), d);
                break;
            case 6:
                drawQuad(window, a, c, sf::Vector2f(x + RESOLUTION, y + RESOLUTION), sf::Vector2f(x + RESOLUTION, y));
                break;
            case 7:
                drawPentagon(window, a, d, sf::Vector2f(x, y + RESOLUTION), sf::Vector2f(x + RESOLUTION, y + RESOLUTION), sf::Vector2f(x + RESOLUTION, y));
                break;
            case 8:
                drawTriangle(window, a, d, sf::Vector2f(x, y));
                break;
            case 9:
                drawQuad(window, a, c, sf::Vector2f(x, y + RESOLUTION), sf::Vector2f(x, y));
                break;
            case 10:
                drawHexagon(window, sf::Vector2f(x, y), a, b, sf::Vector2f(x + RESOLUTION, y + RESOLUTION), c, d);
                break;
            case 11:
                drawPentagon(window, a, b, sf::Vector2f(x + RESOLUTION, y + RESOLUTION), sf::Vector2f(x, y + RESOLUTION), sf::Vector2f(x, y));
                break;
            case 12:
                drawQuad(window, b, d, sf::Vector2f(x, y), sf::Vector2f(x + RESOLUTION, y));
                break;
            case 13:
                drawPentagon(window, b, c, sf::Vector2f(x, y + RESOLUTION), sf::Vector2f(x, y), sf::Vector2f(x + RESOLUTION, y));
                break;
            case 14:
                drawPentagon(window, c, d, sf::Vector2f(x, y), sf::Vector2f(x + RESOLUTION, y), sf::Vector2f(x + RESOLUTION, y + RESOLUTION));
                break;
            case 15:
                drawQuad(window, sf::Vector2f(x, y), sf::Vector2f(x + RESOLUTION, y), sf::Vector2f(x + RESOLUTION, y + RESOLUTION), sf::Vector2f(x, y + RESOLUTION));
                break;

            default:
                break;
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Marching Squares");

    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        desenha(window);
        window.display();
    }

    return 0;
}
