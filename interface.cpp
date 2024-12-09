#include "interface.hpp"
#include <iostream>
#include <unordered_map>
#include <memory>


// Action pour mettre en pause ou reprendre la simulation
class ActionPause : public ActionClavier {
public:
    void executer(Grille& grille, bool& enPause, int& vitesse, sf::RenderWindow& window) override {
        enPause = !enPause;
    }
};

// Action pour réinitialiser la grille
class ActionReset : public ActionClavier {
public:
    void executer(Grille& grille, bool& enPause, int& vitesse, sf::RenderWindow& window) override {
        grille.reset();
    }
};

// Action pour quitter la fenêtre
class ActionQuitter : public ActionClavier {
public:
    void executer(Grille& grille, bool& enPause, int& vitesse, sf::RenderWindow& window) override {
        window.close();
    }
};

// Action pour diminuer la vitesse
class ActionRalentir : public ActionClavier {
public:
    void executer(Grille& grille, bool& enPause, int& vitesse, sf::RenderWindow& window) override {
        if (vitesse < 1000) {
            vitesse += 10;
        }
    }
};

// Action pour augmenter la vitesse
class ActionAccelerer : public ActionClavier {
public:
    void executer(Grille& grille, bool& enPause, int& vitesse, sf::RenderWindow& window) override {
        if (vitesse > 10) {
            vitesse -= 10;
        }
    }
};

// Classe InterfaceGraphique mise à jour
InterfaceGraphique::InterfaceGraphique(Grille grille)
    : window(sf::VideoMode(grille.GetLargeur() * grille.GetTailleCellule(), grille.GetHauteur() * grille.GetTailleCellule()), "Jeu de la Vie"),
      main_grille(grille),
      saved_grille (grille) 
{
    // Initialisation des actions clavier
    actions[sf::Keyboard::Space] = std::make_unique<ActionPause>();
    actions[sf::Keyboard::R] = std::make_unique<ActionReset>();
    actions[sf::Keyboard::Q] = std::make_unique<ActionQuitter>();
    actions[sf::Keyboard::Left] = std::make_unique<ActionRalentir>();
    actions[sf::Keyboard::Right] = std::make_unique<ActionAccelerer>();
}

void InterfaceGraphique::executer() {
    bool enPause = false;       // Indique si la simulation est en pause
    int vitesse = 100;          // Temps entre les mises à jour (en ms)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Fermer la fenêtre avec le bouton standard
            } else if (event.type == sf::Event::KeyPressed) {
                auto it = actions.find(event.key.code);
                if (it != actions.end()) {
                    it->second->executer(main_grille, enPause, vitesse, window);
                }
            }
        }

        if (!enPause) {
            main_grille.mettreAJour();  // Mettre à jour la grille si pas en pause
        }

        render();  // Afficher l'état actuel de la grille
        sf::sleep(sf::milliseconds(vitesse));  // Contrôler la vitesse
    }
}

void InterfaceGraphique::render() {
    vector<vector<Cellule>> grille = main_grille.GetGrille();

    sf::RectangleShape cell(sf::Vector2f(main_grille.GetTailleCellule() - 1.0f, main_grille.GetTailleCellule() - 1.0f));

    window.clear();

    for (int y = 0; y < main_grille.GetHauteur(); y++) {
        for (int x = 0; x < main_grille.GetLargeur(); x++) {
            cell.setPosition(x * main_grille.GetTailleCellule(), y * main_grille.GetTailleCellule());

            if (grille[y][x].isObstacle()) {
                cell.setFillColor(sf::Color(255, 0, 0));
            } else if (grille[y][x].isVivante()) {
                cell.setFillColor(sf::Color::White);
            } else {
                cell.setFillColor(sf::Color::Black);
            }

            window.draw(cell);
        }
    }

    window.display();
}

InterfaceGraphique::~InterfaceGraphique() {}
