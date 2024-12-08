#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <atomic>
#include <mutex>
#include <thread>
#include <iostream>
#include "grille.hpp"
#include "cellule.hpp"


// classe interface graphique
class InterfaceGraphique {
public:
    InterfaceGraphique(Grille grille);
    ~InterfaceGraphique();  // Destructeur pour gérer le thread
    void executer();

private:
    void gererEvenements();
    void render();

    sf::RenderWindow window;
    sf::Font font;
    vector<vector<string>> initial;
    Grille main_grille;
};

#endif
