#include <iostream>
#include <string>

using namespace std;

class Osoba {
    private:
        string imie;
        string nazwisko;
        int indeks;
    public:
        Osoba() : imie(""), nazwisko(""), indeks(0) {}
        Osoba(string imie, string nazwisko, int indeks)
            : imie(imie), nazwisko(nazwisko), indeks(indeks) {}

        int setImie(string wartosc) {
            if(wartosc.length() <= 2) return -1;
            imie = wartosc;
            return 0;
        }
        string getImie() { return imie; }

        int setNazwisko(string wartosc) {
            if(wartosc.length() <= 2) return -1;
            nazwisko = wartosc;
            return 0;
        }
        string getNazwisko() { return nazwisko; }

        int getIndeks() { return indeks; }
        void setIndeks(int wartosc) { indeks = wartosc; }
};

class ListaObecnosci {
    private:
        string nazwaListy;
        Osoba** tabOsoby;
        bool tabObecnosc[10];

    public:
        ListaObecnosci(string nazwa, Osoba** tabOsoby) : nazwaListy(nazwa), tabOsoby(tabOsoby) {
            for(int i = 0; i < 10; i++)
                tabObecnosc[i] = false;
        }

        void ustawObecnosc(int indeks, bool obecnosc) {
            for(int i = 0; i < 10; i++) {
                if(tabOsoby[i] != nullptr && tabOsoby[i]->getIndeks() == indeks) {
                    tabObecnosc[i] = obecnosc;
                    cout << "Obecnosc ustawiona.\n";
                    return;
                }
            }
            cout << "Nie znaleziono studenta o podanym nr indeksu.\n";
        }

        void wyswietl() {
            cout << "\n--- Lista: " << nazwaListy << " ---\n";
            bool pusty = true;
            for(int i = 0; i < 10; i++) {
                if(tabOsoby[i] != nullptr) {
                    cout << tabOsoby[i]->getIndeks() << " "
                         << tabOsoby[i]->getImie() << " "
                         << tabOsoby[i]->getNazwisko() << " "
                         << (tabObecnosc[i] ? "OBECNY" : "NIEOBECNY") << "\n";
                    pusty = false;
                }
            }
            if(pusty) cout << "Lista jest pusta.\n";
            cout << "----------------------\n";
        }

        string getNazwa() { return nazwaListy; }
};

Osoba* znajdzOsobe(Osoba* tabOsoby[10], int indeks) {
    for(int i = 0; i < 10; i++) {
        if(tabOsoby[i] != nullptr && tabOsoby[i]->getIndeks() == indeks)
            return tabOsoby[i];
    }
    return nullptr;
}

void dodajNowaOsobe(Osoba* tabOsoby[10]) {
    string imie, nazwisko;
    int indeks;
    cout << "Podaj imie: ";       cin >> imie;
    cout << "Podaj nazwisko: ";   cin >> nazwisko;
    cout << "Podaj nr indeksu: "; cin >> indeks;

    for(int i = 0; i < 10; i++) {
        if(tabOsoby[i] == nullptr) {
            tabOsoby[i] = new Osoba(imie, nazwisko, indeks);
            cout << "Osoba dodana.\n";
            return;
        }
    }
    cout << "Baza osob jest pelna!\n";
}

void zmienDane(Osoba* tabOsoby[10]) {
    int indeks;
    cout << "Podaj nr indeksu studenta do edycji: ";
    cin >> indeks;
    Osoba* o = znajdzOsobe(tabOsoby, indeks);
    if(o == nullptr) { cout << "Nie znaleziono.\n"; return; }

    string imie, nazwisko;
    int nowyIndeks;
    cout << "Podaj nowe imie: ";       cin >> imie;
    cout << "Podaj nowe nazwisko: ";   cin >> nazwisko;
    cout << "Podaj nowy nr indeksu: "; cin >> nowyIndeks;

    o->setImie(imie);
    o->setNazwisko(nazwisko);
    o->setIndeks(nowyIndeks);
    cout << "Dane zmienione.\n";
}

int main() {

    Osoba* tabOsoby[10] = {};
    ListaObecnosci* listy[5] = {};
    int iloscList = 0;

    int wybor = 0;
    while(wybor != 6) {
        cout << "\nWybierz dzialanie:\n";
        cout << "1. Dodaj osobe do bazy.\n";
        cout << "2. Zmien dane osoby.\n";
        cout << "3. Stworz nowa liste obecnosci.\n";
        cout << "4. Ustaw obecnosc na liscie.\n";
        cout << "5. Wyswietl liste obecnosci.\n";
        cout << "6. Zakoncz program.\n";
        cin >> wybor;

        int indeks;
        int nrListy;
        bool obecnosc;

        switch(wybor) {
            case 1:
                dodajNowaOsobe(tabOsoby);
            break;
            case 2:
                zmienDane(tabOsoby);
            break;
            case 3:
                if(iloscList >= 5) { cout << "Osiagnieto limit list!\n"; break; }
                {
                    string nazwa;
                    cout << "Podaj nazwe listy: ";
                    cin >> nazwa;
                    listy[iloscList] = new ListaObecnosci(nazwa, tabOsoby);
                    iloscList++;
                    cout << "Lista stworzona.\n";
                }
            break;
            case 4:
                cout << "Podaj numer listy (0-" << iloscList-1 << "): ";
                cin >> nrListy;
                if(nrListy < 0 || nrListy >= iloscList) { cout << "Nieprawidlowy nr listy.\n"; break; }
                cout << "Podaj nr indeksu: ";
                cin >> indeks;
                cout << "Podaj obecnosc (0/1): ";
                cin >> obecnosc;
                listy[nrListy]->ustawObecnosc(indeks, obecnosc);
            break;
            case 5:
                cout << "Podaj numer listy (0-" << iloscList-1 << "): ";
                cin >> nrListy;
                if(nrListy < 0 || nrListy >= iloscList) { cout << "Nieprawidlowy nr listy.\n"; break; }
                listy[nrListy]->wyswietl();
            break;
            case 6:
                return 0;
            break;
            default:
                cout << "Nieprawidlowy wybor!\n";
            break;
        }
    }

    return 0;
}
