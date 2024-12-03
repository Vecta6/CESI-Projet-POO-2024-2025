#include "grille.h"

Grille::Grille(int largeur, int hauteur, int tailleCellule)
    : largeur(largeur), hauteur(hauteur), tailleCellule(tailleCellule) {
    cellules.resize(hauteur, std::vector<Cellule>(largeur));
}

void Grille::initialiserGrille() {

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            cellules[i][j].setVivante(rand() % 2);
        }
    }
}

void Grille::afficher(sf::RenderWindow& window) {

    window.clear();
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            sf::RectangleShape rect(sf::Vector2f(tailleCellule, tailleCellule));
            rect.setPosition(j * tailleCellule, i * tailleCellule);

            if (cellules[i][j].isVivante()) {
                rect.setFillColor(sf::Color::White);
            } else {
                rect.setFillColor(sf::Color::Black);
            }

            window.draw(rect);
        }
    }

    window.display();
}

int Grille::compterVoisinsVivants(int x, int y) {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int ni = (x + i + hauteur) % hauteur;
            int nj = (y + j + largeur) % largeur;
            
            if (cellules[ni][nj].isVivante()) {
                voisinsVivants++;
            }
        }
    }
    return voisinsVivants;
}

void Grille::mettreAJour() {
    std::vector<std::vector<Cellule>> nouvelleGrille = cellules;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            int voisinsVivants = compterVoisinsVivants(i, j);

            if (cellules[i][j].isVivante()) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    nouvelleGrille[i][j].setVivante(false);  // La cellule meurt
                }
            } else {
                if (voisinsVivants == 3) {
                    nouvelleGrille[i][j].setVivante(true);  // La cellule naît
                }
            }
        }
    }

    cellules = nouvelleGrille;
}
