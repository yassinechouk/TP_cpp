#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class capteur {
protected:
    string nom;
    string unite;
public:
    capteur(string n, string u): nom(n), unite(u) {}
    virtual double lirevaleur() = 0;
    virtual ~capteur() {}
};

class accelometre : public capteur {
public:
    accelometre(): capteur("accelometre", "m.s^-2") {}
    double lirevaleur() override {
        return (rand() % 1000) / 100.0;
    }
};

class analyseur_vibration {
private:
    vector<double> buffer;
    int capacity;
public:
    analyseur_vibration(int cap = 10): capacity(cap) {
        buffer.reserve(cap);
    }
    void ajoutmesure(double v) {
        if ((int)buffer.size() < capacity) {
            buffer.push_back(v);
        } else {
            rotate(buffer.begin(), buffer.begin() + 1, buffer.end());
            buffer.back() = v;
        }
    }
    double calculerMoyenne() {
        if (buffer.empty()) return 0.0;
        double somme = accumulate(buffer.begin(), buffer.end(), 0.0);
        return somme / buffer.size();
    }
    double detecterPic() {
        if (buffer.empty()) return 0.0;
        return *max_element(buffer.begin(), buffer.end());
    }
    bool estEnDanger(double seuil) {
        int count = count_if(buffer.begin(), buffer.end(),
            [seuil](double val) { return val > seuil; });
        return count > 3;
    }
};

int main() {
    srand(time(0));
    accelometre capteur;
    analyseur_vibration analyseur;
    for (int i = 0; i < 20; i++) {
        double mesure = capteur.lirevaleur();
        analyseur.ajoutmesure(mesure);
        cout << "Mesure " << i+1
             << " : " << mesure
             << " | Moyenne : " << analyseur.calculerMoyenne()
             << " | Pic max : " << analyseur.detecterPic()
             << endl;
        if (analyseur.estEnDanger(8.0)) {
            cout << ">>> ALERTE : Vibrations critiques detectees !" << endl;
        }
    }
    return 0;
}