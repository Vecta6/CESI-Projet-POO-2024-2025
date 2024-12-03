#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
public:
    bool vivante;

    Cellule();
    void toggle();
    void setVivante(bool v);
    bool isVivante() const;
};

#endif
