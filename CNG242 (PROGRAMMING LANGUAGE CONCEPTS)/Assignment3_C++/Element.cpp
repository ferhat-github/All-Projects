#include "Element.h"
#include <iostream>
using namespace std;

Element::Element(int s, char c, int e) {
    size = s;
    character = c;
    effect = e;
}

char Element::getCharacter() const {
    return character;
}

int Element::getSize() const {
    return size;
}

int Element::getEffect() const {
    return effect;
}




Food::Food(int n) : Element(1, 'F', n/6) {

}

void Food::printing() {
    cout << "You found a Food. It increases health by " << effect <<endl;
}



Wood::Wood(int n) : Element(2, 'I', n/8) {

}

void Wood::printing() {
    cout << "You found a Wood. It increases health by " << effect << endl;
}



MedicalSupplies::MedicalSupplies(int n) : Element(1, 'S', n/4) {

}

void MedicalSupplies::printing() {
    cout << "You found a Medical Supplies. It increases health by " << effect << endl;
}



Gold::Gold() : Element(1, 'G', 100) {

}

void Gold::printing() {
    cout << "You found a Gold. It Increases score by " << effect << endl;
}



WildAnimal::WildAnimal(int size, char character, int effect) : Element(size, character, effect) {

}



Wolf::Wolf(int n) : WildAnimal(1, 'W', n/4) {

}

void Wolf::printing() {
    cout << "You found a WOLF!!" << endl;
}



Bear::Bear(int n) : WildAnimal(3, 'B', n/2) {

}

void Bear::printing() {
    cout << "You Found a BEAR!!" << endl;
}


