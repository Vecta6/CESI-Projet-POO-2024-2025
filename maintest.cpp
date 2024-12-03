#include <iostream>

#include "interface.h"

int main() {
    try {
        InterfaceGraphique interface(120, 100, 5);
        interface.executer();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    return 0;
}


//problème de clignotement