#ifndef CONSOLE_H
#define CONSOLE_H


#include "cellule.hpp"
#include "grille.hpp"

class Console {
private:
    Grille main_grille;
    vector<vector<Cellule>> stat_grille;
    bool is_running;
    void ShowStat();
    bool VerifDiff();
    
public:
    Console(Grille grille);
    void execute(string nom_fichier, int iterration);
};

#endif