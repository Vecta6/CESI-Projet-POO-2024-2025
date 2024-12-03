#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <iostream>
using namespace std;

#include "grille.h"
#include "cellule.h"

const int cellSize = 5;
const int gridWidth = 200;
const int gridHeight = 200;

Grille grille(gridWidth, gridHeight, cellSize);

// vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

// void initializeGrid() {
//     srand(time(0));
//     for (int x = 0; x < gridWidth; ++x) {
//         for (int y = 0; y < gridHeight; ++y) {
//             grid[x][y] = rand() % 2;
//         }
//     }
// }

// void renderGrid(sf::RenderWindow &window) {
//     int x, y;
    
//     window.clear();
//     sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
//     for (x = 0; x < gridWidth; ++x) {
//         for (y = 0; y < gridHeight; ++y) {

//             if (grid[x][y] == 1) {
//                 cell.setPosition(x * cellSize, y * cellSize);
//                 window.draw(cell);
//             }
//         }
//     }
//     window.display();
// }

int main() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");
    
    // initializeGrid();
    grille.initialiserGrille();
    
    // int pos=0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        // renderGrid(window);
        grille.afficher(window);

        grille.mettreAJour();

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
