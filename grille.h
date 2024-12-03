#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include "cellule.h"
#include <SFML/Graphics.hpp>

class Grille {
private:
    std::vector<std::vector<Cellule>> cellules;
    int largeur, hauteur;
    int tailleCellule;
public:
    Grille(int largeur, int hauteur, int tailleCellule);
    
    void initialiserGrille();
    void afficher(sf::RenderWindow& window);
    int compterVoisinsVivants(int x, int y);
    void mettreAJour();
};

#endif
