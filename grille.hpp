#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <fstream>
#include "cellule.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

class Grille {
private:
    vector<vector<Cellule>> cellules;
    int largeur, hauteur;
    int tailleCellule;
public:
    Grille(int largeur, int hauteur, int tailleCellule);
    
    int initialiserGrille(string file="");
    vector<vector<Cellule>> GetGrille();
    int compterVoisinsVivants(int x, int y);
    void mettreAJour();
    int GetLargeur();
    int GetHauteur();
    int GetTailleCellule();
};

#endif
