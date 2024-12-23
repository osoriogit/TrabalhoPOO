//
// Created by tomas on 28/11/2024.
//

#ifndef MONTANHAS_H
#define MONTANHAS_H



class Montanhas {
    int x;
    int y;

public:
    Montanhas(){x=-1;y=-1;}
    int getX() const {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }
    ~Montanhas()= default;
};



#endif //MONTANHAS_H
