#ifndef ITEM_H
#define ITEM_H

class item {
public:
    [[nodiscard]] int x1() const {
        return x;
    }

    void set_x(int x) {
        this->x = x;
    }

    [[nodiscard]] int y1() const {
        return y;
    }

    void set_y(int y) {
        this->y = y;
    }

    [[nodiscard]] int tipo1() const {
        return tipo;
    }

    void set_tipo(int tipo) {
        this->tipo = tipo;
    }

private:
    int x=0;
    int y=0;
    int tipo=0;
    public:
};

#endif //ITEM_H
