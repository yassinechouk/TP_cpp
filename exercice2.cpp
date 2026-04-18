#include <iostream>
#include <iomanip>
using namespace std;

class Time {
protected:
    int hours, minutes, secondes;

public:
    // Constructeur par defaut : initialise a 0
    Time() : hours(0), minutes(0), secondes(0) {}

    // Constructeur avec valeurs fixes
    Time(int h, int m, int s) : hours(h), minutes(m), secondes(s) {}

    // Fonction membre pour afficher au format HH:MM:SS
    void getTime() const {
        cout << setfill('0') << setw(2) << hours << ":"
             << setfill('0') << setw(2) << minutes << ":"
             << setfill('0') << setw(2) << secondes << endl;
    }

    // Getters
    int getHours() const { return hours; }
    int getMin() const { return minutes; }
    int getSec() const { return secondes; }

    // Fonction membre pour additionner deux objets Time
    void addTime(Time t1, Time t2) {
        int totalSec = t1.secondes + t2.secondes;
        int retenue1 = totalSec / 60;
        secondes = totalSec % 60;

        int totalMin = t1.minutes + t2.minutes + retenue1;
        int retenue2 = totalMin / 60;
        minutes = totalMin % 60;

        hours = t1.hours + t2.hours + retenue2;
    }
};

int main() {
    Time t1(4, 45, 59), t2(1, 20, 32);
    Time t3;

    t1.getTime();   // 04:45:59
    t2.getTime();   // 01:20:32
    t3.addTime(t1, t2);
    t3.getTime();   // 06:06:31

    return 0;
}
