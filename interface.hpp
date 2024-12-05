#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <atomic>
#include <mutex>
#include <thread>
#include <iostream>
#include "grille.hpp"

// classe  bouton
class Button : public sf::Drawable {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font);
    bool isMouseOver(const sf::RenderWindow& window) const;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_button;
    sf::Text m_text;
};

// classe interface graphique
class InterfaceGraphique {
public:
    InterfaceGraphique(Grille grille);
    ~InterfaceGraphique();  // Destructeur pour gérer le thread
    void executer();

private:
    void gererEvenements();
    void dessiner();

    sf::RenderWindow window;
    sf::Font font;
    Grille main_grille;
    vector<vector<sf::RectangleShape>> ui_grille;
    Button playPauseButton;
    Button resetButton;
    Button quitButton;

    sf::RectangleShape slider;
    sf::RectangleShape cursor;

    std::atomic<bool> isRunning;
    std::mutex gridMutex;
    float vitesse; // vitesse simu
    bool isDragging; // pour le curseur

    std::thread simulationThread; // Déclaration du thread
};

#endif
