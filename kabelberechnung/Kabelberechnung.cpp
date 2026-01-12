#include <iostream>

constexpr double WECHSELSTROM = 1.0;
constexpr double DREHSTROM = 1.732; // sqrt(3)

double calcLeiterstrom(double leistung_kw, double cosphi, int auswahl)
{
    int nennspannung = 0;
    double stromfaktor = 1.0;
    const char* stromartText = "";

    if (auswahl == 0) {              // Wechselstrom
        nennspannung = 230;
        stromfaktor = WECHSELSTROM;
        stromartText = "Wechselstrom (1~)";
    }
    else if (auswahl == 1) {         // Drehstrom
        nennspannung = 400;
        stromfaktor = DREHSTROM;
        stromartText = "Drehstrom (3~)";
    }
    else {
        std::cerr << "Ungueltige Stromart.\n";
        return 0.0;
    }
    std::cout << "Stromart: " << stromartText  << ", Nennspannung: " << nennspannung << " V" << std::endl;
    return (leistung_kw * 1000.0) / (cosphi * nennspannung * stromfaktor);
}

int main()
{
    std::cout << "Kabelberechnung - Leiterstrom\n";

    int auswahl = 0;
    double leistung = 0.0;
    double cosphi = 0.0;
    double querschnitt;
    double I_max = 0;

    std::cout << "Stromart waehlen (Wechselstrom = 0, Drehstrom= 1): ";
    std::cin >> auswahl;

    std::cout << "Leistung (kW): ";
    std::cin >> leistung;

    std::cout << "cos(phi): ";
    std::cin >> cosphi;

    if (leistung <= 0 || cosphi <= 0 || cosphi > 1) {
        std::cerr << "Ungueltige Eingabewerte.\n";
        return 1;
    }

    double strom = calcLeiterstrom(leistung, cosphi, auswahl);

    if (strom > 0) {
        std::cout << "Berechneter Leiterstrom: " << strom << " A\n";
    }
    std::cout << "Kabelquerschnitt eingeben (mm^2): ";
    std::cin >> querschnitt;
    if (querschnitt == 0.5) I_max = 1,5;
    else if (querschnitt == 1) I_max = 10;
    else if (querschnitt == 1.5) I_max = 16;
    else if (querschnitt == 2.5) I_max = 25;
    else if (querschnitt == 4) I_max = 32;
    else if (querschnitt == 6) I_max = 40;
    else if (querschnitt == 10) I_max = 63;
    else {
        std::cout << "Unbekannter Kabelquerschnitt!" << std::endl;
        return 0;
    }

    if (strom <= I_max)
        std::cout << "Der gewaehlte Kabelquerschnitt ist ausreichend." << std::endl;
    else
        std::cout << "Warnung: Der Kabelquerschnitt ist nicht ausreichend!" << std::endl;


    return 0;
}
