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
