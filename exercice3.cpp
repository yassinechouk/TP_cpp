#include <iostream>
#include <string>
using namespace std;

class Personnel {
protected:
    string nom;
    string position;
    double salaire;

public:
    // Constructeur par defaut
    Personnel() : nom(""), position(""), salaire(0) {}

    // Constructeur avec parametres
    Personnel(string n, string p, double s) : nom(n), position(p), salaire(s) {}

    // Fonction pour afficher les informations du personnel
    void affiche_personnel() const {
        cout << "Nom : " << nom << endl;
        cout << "Position : " << position << endl;
        cout << "Salaire : " << salaire << endl;
    }

    // Fonction pour saisir les informations d'un personnel
    void saisie_personnel() {
        cout << "Entrez le nom : ";
        cin >> nom;
        cout << "Entrez la position : ";
        cin >> position;
        cout << "Entrez le salaire : ";
        cin >> salaire;
    }

    // Declaration de la fonction amie
    friend void affiche_externe(Personnel p);
};

// Fonction amie pour afficher une instance Personnel
void affiche_externe(Personnel p) {
    cout << "--- Affichage externe ---" << endl;
    cout << "Nom : " << p.nom << endl;
    cout << "Position : " << p.position << endl;
    cout << "Salaire : " << p.salaire << endl;
}

// Classe Patron derivant publiquement de Personnel
class Patron : public Personnel {
private:
    double ba;      // bonus annuel
    string mv;      // marque de voiture

public:
    // Constructeur initialisant les donnees membres
    Patron() : Personnel(), ba(0), mv("") {}

    Patron(string n, string p, double s, double bonus, string marque)
        : Personnel(n, p, s), ba(bonus), mv(marque) {}

    // Fonction de saisie du patron
    void saisie_patron() {
        saisie_personnel();
        cout << "Entrez le bonus annuel : ";
        cin >> ba;
        cout << "Entrez la marque de voiture : ";
        cin >> mv;
    }

    // Fonction d'affichage du patron
    void affiche_patron() const {
        affiche_personnel();
        cout << "bonus annuel = " << ba << endl;
        cout << "Marque de voiture = " << mv << endl;
    }
};

int main() {
    // Test avec des valeurs directes
    Personnel p1("gerald", "gerant", 1250);
    p1.affiche_personnel();

    cout << "----->Patron:" << endl;

    Patron patron1("fallon", "PDG", 2000, 500, "BMW");
    patron1.affiche_patron();

    return 0;
}
