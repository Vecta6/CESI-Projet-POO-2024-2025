#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
private:
    bool vivante;
    bool obstacle;
public:

    Cellule();
    ~Cellule();
    void toggle();
    void setVivante(bool v);
    bool isVivante() const;
    void setObstacle(bool v);
    bool isObstacle();
};

#endif
