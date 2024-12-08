#include "interface.hpp"
#include <iostream>





InterfaceGraphique::InterfaceGraphique(Grille grille)
    : window(sf::VideoMode(grille.GetLargeur() * grille.GetTailleCellule(), grille.GetHauteur() * grille.GetTailleCellule() + 100), "Jeu de la Vie"),
      main_grille(grille) 
      {}

void InterfaceGraphique::executer() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed){
                window.close();
            }
        }
        

        render();

        main_grille.mettreAJour();

        sf::sleep(sf::milliseconds(100));


    }
    
}



void InterfaceGraphique::render()
{
    vector<vector<Cellule>> grille=main_grille.GetGrille();

    sf::RectangleShape cell(sf::Vector2f(main_grille.GetTailleCellule() - 1.0f, main_grille.GetTailleCellule() - 1.0f));

    window.clear();

    for(int y=0; y<main_grille.GetHauteur(); y++)
    {   
        
        for(int x=0; x<main_grille.GetLargeur(); x++)
        {
            
            cell.setPosition(x * main_grille.GetTailleCellule(), y * main_grille.GetTailleCellule());
            
            if(grille[y][x].isObstacle())
            {
                cell.setFillColor(sf::Color(255, 0, 0));
            } else if(grille[y][x].isVivante())
            {
                cell.setFillColor(sf::Color::White);
            }else if(!grille[y][x].isVivante())
            {
                cell.setFillColor(sf::Color::Black);
            }
        
            window.draw(cell);
        
        
        
        }
    }

    window.display();

}



InterfaceGraphique::~InterfaceGraphique() {}