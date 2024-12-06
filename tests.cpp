#include "cellule.hpp"
#include "grille.hpp"
#include "interface.hpp"
#include <cassert>
#include <iostream>

void test_cellule() {
    Cellule c;
    assert(!c.isVivante());
    c.toggle();
    assert(c.isVivante());
    c.toggle();
    assert(!c.isVivante());
    c.setVivante(true);
    assert(c.isVivante());
    c.setVivante(false);
    assert(!c.isVivante());
}

void test_grille() {
    Grille grille(5, 5, 1);
    grille.initialiserGrille();

    // Test compterVoisinsVivants() avec toutes les cellules mortes
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            assert(grille.compterVoisinsVivants(i, j) == 0);
        }
    }
    
    grille.initialiserGrille();
    grille.mettreAJour();
}

void test_interface() {
    try {
        InterfaceGraphique interface(10, 10, 1);
        // Test si l'interface se crée sans erreur.
    } catch (const std::exception& e) {
        assert(false && "Exception levée lors de la création de l'interface");
    }
}

int main() {
    test_cellule();
    std::cout << "Tests Cellule OK" << std::endl;

    test_grille();
    std::cout << "Tests Grille OK" << std::endl;

    test_interface();
    std::cout << "Tests Interface OK" << std::endl;

    return 0;
}
