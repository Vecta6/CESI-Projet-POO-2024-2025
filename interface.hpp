#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "grille.hpp"
#include "cellule.hpp"

// Classe abstraite pour encapsuler les actions clavier
class ActionClavier {
public:
    virtual void executer(Grille& grille, bool& enPause, int& vitesse, sf::RenderWindow& window) = 0;
    virtual ~ActionClavier() = default;
};

// Classe principale InterfaceGraphique
class InterfaceGraphique {
public:
    InterfaceGraphique(Grille grille);
    ~InterfaceGraphique();  // Destructeur pour gérer les ressources
    void executer();        // Boucle principale d'exécution

private:
    void render();                                   // Méthode pour afficher la grille

    sf::RenderWindow window;                        // Fenêtre SFML
    sf::Font font;                                  // Police pour le texte (par exemple, pour afficher la vitesse)
    Grille main_grille;                             // Grille principale
    Grille saved_grille;
    std::unordered_map<sf::Keyboard::Key, std::unique_ptr<ActionClavier>> actions; // Map des actions clavier
};

#endif
