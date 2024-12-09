#include "cellule.hpp"

Cellule::Cellule() : vivante(false), obstacle(false) {}

void Cellule::toggle() {
    vivante = !vivante;
}

void Cellule::setVivante(bool v) {
    vivante = v;
}

bool Cellule::isVivante() const {
    return vivante;
}


void Cellule::setObstacle(bool v) {
    obstacle = v;
}

bool Cellule::isObstacle() {
    return obstacle;
}



Cellule::~Cellule(){}
