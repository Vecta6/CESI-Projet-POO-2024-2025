#include "interface.hpp"
#include <iostream>


Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font) {
    m_button.setSize(size);
    m_button.setPosition(position);
    m_button.setFillColor(sf::Color::White);

    m_text.setString(text);
    m_text.setFont(font);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position.x + 10, position.y + 10);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    return m_button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_button, states);
    target.draw(m_text, states);
}

InterfaceGraphique::InterfaceGraphique(Grille grille)
    : window(sf::VideoMode(grille.GetLargeur() * grille.GetTailleCellule(), grille.GetHauteur() * grille.GetTailleCellule() + 100), "Jeu de la Vie"),
      main_grille(grille),
      playPauseButton({50.0f, static_cast<float>(grille.GetHauteur() * grille.GetTailleCellule() + 20)}, {150.0f, 40.0f}, "Play/Pause", font),
      resetButton({250.0f, static_cast<float>(grille.GetHauteur() * grille.GetTailleCellule() + 20)}, {150.0f, 40.0f}, "Reset", font),
      quitButton({450.0f, static_cast<float>(grille.GetHauteur() * grille.GetTailleCellule() + 20)}, {150.0f, 40.0f}, "Quit", font),
      isRunning(false), vitesse(0.5f), isDragging(false) {

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        throw std::runtime_error("Impossible de charger la police");
    }

    slider.setSize({400, 10});
    slider.setFillColor(sf::Color(200, 200, 200));
    slider.setPosition(50, grille.GetHauteur() * grille.GetTailleCellule() + 70);

    cursor.setSize({10, 30});
    cursor.setFillColor(sf::Color::Red);
    cursor.setPosition(250, grille.GetHauteur() * grille.GetTailleCellule() + 65);
}

void InterfaceGraphique::executer() {
    
    
    
    ui_grille.resize(main_grille.GetHauteur(), std::vector<sf::RectangleShape>(main_grille.GetLargeur()));

    for (int i = 0; i < main_grille.GetHauteur(); i++) {
        for (int j = 0; j < main_grille.GetLargeur(); j++) {
            sf::RectangleShape rect(sf::Vector2f(main_grille.GetTailleCellule(), main_grille.GetTailleCellule()));
            rect.setPosition(j * main_grille.GetTailleCellule(), i * main_grille.GetTailleCellule());
            rect.setFillColor(sf::Color::Black);
            ui_grille[i][j]=rect;

            window.draw(rect);
        }
    }




    // Lancer le thread pour la simulation
    std::thread simulationThread([&]() {
        while (window.isOpen()) {
            if (isRunning) {
                // Synchronisation pour protéger l'accès à la grille
                {
                    std::lock_guard<std::mutex> lock(gridMutex);
                    main_grille.mettreAJour(); // Mettre à jour la grille
                    
                    for (int i = 0; i < main_grille.GetHauteur(); i++) {
                        for (int j = 0; j < main_grille.GetLargeur(); j++) {

                            if (main_grille.GetGrille()[i][j].isVivante()) {
                                ui_grille[i][j].setFillColor(sf::Color::White);
                            } else {
                                ui_grille[i][j].setFillColor(sf::Color::Black);
                            }

                            window.draw(ui_grille[i][j]);
                        }
                    }

                }
                // Pause pour simuler la vitesse
                std::this_thread::sleep_for(std::chrono::duration<float>(vitesse));
            }
        }
    });

    // Boucle principale pour gérer les événements de la fenêtre
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Affichage de la grille

        

        gererEvenements();  // Gérer les événements utilisateur

        dessiner();          // Dessiner la grille et les boutons

        
    }

    // Attendre la fin du thread avant de quitter
    if (simulationThread.joinable()) {
        simulationThread.join();
    }

}

void InterfaceGraphique::gererEvenements() {
    sf::Event event;
    cout << window.pollEvent(event) << endl;
    while (window.pollEvent(event)) {
        
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (playPauseButton.isMouseOver(window)) {
                isRunning = !isRunning;
            } else if (resetButton.isMouseOver(window)) {
                std::lock_guard<std::mutex> lock(gridMutex);
                main_grille.initialiserGrille();
            } else if (quitButton.isMouseOver(window)) {
                window.close();
            } else if (cursor.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                isDragging = true;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            isDragging = false;
        }

        if (event.type == sf::Event::MouseMoved && isDragging) {
            float posX = event.mouseMove.x;
            if (posX >= 50 && posX <= 450) {
                cursor.setPosition(posX - cursor.getSize().x / 2, cursor.getPosition().y);
                vitesse = 0.01f + ((posX - 50) / 400.0f) * (1.0f - 0.01f);
            }
        }
    }
}

void InterfaceGraphique::dessiner() {
    {
        std::lock_guard<std::mutex> lock(gridMutex);
    }



    window.draw(playPauseButton);
    window.draw(resetButton);
    window.draw(quitButton);
    window.draw(slider);
    window.draw(cursor);

    window.display();
}

InterfaceGraphique::~InterfaceGraphique() {
    if (simulationThread.joinable()) {
        simulationThread.join(); // S'assurer que le thread se termine proprement
    }
}

