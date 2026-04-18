#include <iostream>
using namespace std;

class Complex {
private:
    double re, im;

public:
    // Constructeur par defaut : initialise les attributs a 0
    Complex() : re(0), im(0) {}

    // Constructeur avec des valeurs fixes
    Complex(double r, double i) : re(r), im(i) {}

    // Fonction membre pour afficher un complexe
    void afficher() const {
        cout << re << " + " << im << "i" << endl;
    }

    // Fonction membre qui fait la somme de 2 complexes
    Complex somme(Complex c1, Complex c2) {
        Complex resultat;
        resultat.re = c1.re + c2.re;
        resultat.im = c1.im + c2.im;
        return resultat;
    }
};

int main() {
    double re1, im1, re2, im2;

    cout << "Premier nombre" << endl;
    cout << "Entrez la partie reelle: ";
    cin >> re1;
    cout << "Entrez la partie imaginaire: ";
    cin >> im1;

    cout << endl;

    cout << "Deuxieme nombre" << endl;
    cout << "Entrez la partie reelle: ";
    cin >> re2;
    cout << "Entrez la partie imaginaire: ";
    cin >> im2;

    Complex c1(re1, im1);
    Complex c2(re2, im2);
    Complex c3;

    c3 = c3.somme(c1, c2);

    cout << endl;
    cout << "La somme est ";
    c3.afficher();

    return 0;
}
