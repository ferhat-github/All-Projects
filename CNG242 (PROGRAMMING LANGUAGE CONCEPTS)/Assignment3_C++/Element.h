#ifndef ASSIGNMENT3_ELEMENT_H
#define ASSIGNMENT3_ELEMENT_H


class Element {
protected:
    int size;
    char character;
    int effect;

public:
    Element(int, char, int);
    virtual ~Element() = default;

    char getCharacter() const;
    int getSize() const;
    int getEffect() const;

    virtual void printing() = 0; //Pure virtual function
};


class Food : public Element {
public:
    Food(int);
    void printing() override;
};


class Wood : public Element {
public:
    Wood(int);
    void printing() override;
};


class MedicalSupplies : public Element {
public:
    MedicalSupplies(int);
    void printing() override;
};


class Gold : public Element {
public:
    Gold();
    void printing() override;
};



class WildAnimal : public Element {
public:
    WildAnimal(int, char, int);
    virtual void printing() override = 0; // Pure virtual function
};


class Wolf : public WildAnimal {
public:
    Wolf(int);
    void printing() override;
};




class Bear : public WildAnimal {
public:
    Bear(int);
    void printing() override;
};





#endif //ASSIGNMENT3_ELEMENT_H

