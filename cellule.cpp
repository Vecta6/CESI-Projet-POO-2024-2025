#include "cellule.h"

Cellule::Cellule() : vivante(false) {}

void Cellule::toggle() {
    vivante = !vivante;
}

void Cellule::setVivante(bool v) {
    vivante = v;
}

bool Cellule::isVivante() const {
    return vivante;
}
