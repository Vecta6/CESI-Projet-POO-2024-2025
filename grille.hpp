#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <fstream>
#include "cellule.hpp"

using namespace std;

class Grille {
private:
    vector<vector<Cellule>> cellules;
    vector<vector<Cellule>> initialstate;
    int largeur, hauteur;
    int tailleCellule;
public:
    Grille(int largeur, int hauteur, int tailleCellule);
    ~Grille();
    
    int initialiserGrille(vector<vector<string>> table);
    vector<vector<Cellule>> GetGrille();
    int compterVoisinsVivants(int x, int y);
    void mettreAJour();
    int GetLargeur();
    int GetHauteur();
    int GetTailleCellule();
    void reset();
};

#endif
