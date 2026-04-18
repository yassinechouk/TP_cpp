#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

// Enum Etat pour connaitre l'etat de la machine
enum Etat { Attente, Remplissage_Etat, Fin, Defaut };

// Classe Capteur
class Capteur {
public:
    bool detecter() {
        // Simule la detection d'une bouteille
        return true;
    }
};

// Classe Vanne
class Vanne {
private:
    bool ouverte;

public:
    Vanne() : ouverte(false) {}

    void ouvrir() {
        ouverte = true;
        cout << "Vanne ouverte." << endl;
    }

    void fermer() {
        ouverte = false;
        cout << "Vanne fermee." << endl;
    }

    bool estOuverte() const { return ouverte; }
};

// Classe de base abstraite Machine
class Machine {
protected:
    Etat etat;
    string nom;
    int compteur;

public:
    Machine(string n) : nom(n), etat(Attente), compteur(0) {}

    virtual ~Machine() {}

    // Methode virtuelle pure : force les classes filles a definir leur propre cycle
    virtual void cycle() = 0;

    int getCompteur() const { return compteur; }

    string getNom() const { return nom; }

    void setEtat(Etat e) { etat = e; }
    Etat getEtat() const { return etat; }
};

// Classe Remplissage heritant de Machine
class RemplissageMachine : public Machine {
private:
    Capteur capteur;
    Vanne vanne;

public:
    RemplissageMachine() : Machine("Remplissage") {}

    void cycle() override {
        cout << "\n[" << nom << "] --- Debut du cycle ---" << endl;

        if (capteur.detecter()) {
            cout << "[" << nom << "] Bouteille detectee !" << endl;
            etat = Remplissage_Etat;
        }

        if (etat == Remplissage_Etat) {
            cout << "[" << nom << "] Remplissage en cours..." << endl;
            vanne.ouvrir();
            // Attente de 2 secondes
            this_thread::sleep_for(chrono::seconds(2));
            vanne.fermer();
            compteur++;
            cout << "[" << nom << "] Remplissage termine. (Total: " << compteur << ")" << endl;
            etat = Fin;
        }

        if (etat == Fin) {
            cout << "[" << nom << "] Cycle termine. Retour en attente." << endl;
            etat = Attente;
        }
    }
};

// Classe Etiquetage heritant de Machine
class Etiquetage : public Machine {
public:
    Etiquetage() : Machine("Etiquetage") {}

    void cycle() override {
        cout << "\n[" << nom << "] --- Debut du cycle ---" << endl;

        if (etat == Attente) {
            cout << "[" << nom << "] Etiquetage en cours..." << endl;
            // Simule la pose d'une etiquette pendant 1 seconde
            this_thread::sleep_for(chrono::seconds(1));
            compteur++;
            cout << "[" << nom << "] Etiquette posee. (Total: " << compteur << ")" << endl;
            etat = Fin;
        }

        if (etat == Fin) {
            cout << "[" << nom << "] Cycle termine. Retour en attente." << endl;
            etat = Attente;
        }
    }
};

int main() {
    // Vecteur de pointeurs Machine*
    vector<Machine*> machines;
    machines.push_back(new RemplissageMachine());
    machines.push_back(new Etiquetage());

    cout << "=== Simulation de l'usine ===" << endl;

    // Simuler 3 cycles de l'usine
    for (int i = 1; i <= 3; i++) {
        cout << "\n========== Cycle " << i << " ==========" << endl;
        for (Machine* m : machines) {
            m->cycle();
        }
    }

    // Afficher les compteurs
    cout << "\n=== Resultats ===" << endl;
    for (Machine* m : machines) {
        cout << m->getNom() << " : " << m->getCompteur() << " operations effectuees." << endl;
    }

    // Liberation de la memoire
    for (Machine* m : machines) {
        delete m;
    }

    return 0;
}
