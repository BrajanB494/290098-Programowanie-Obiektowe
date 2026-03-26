#include <iostream>
#include <string>

using namespace std;

void dodajOsobe(string *tabImie, string *tabNazwisko, int *tabIndeks, bool *tabObecnosc, string imie, string nazwisko, int indeks, bool obecnosc) {
    for(int i = 0; i < 10; i++)
    {
        if(tabNazwisko[i] == "")
        {
            tabImie[i] = imie;
            tabNazwisko[i] = nazwisko;
            tabIndeks[i] = indeks;
            tabObecnosc[i] = obecnosc;
            return;
        }
    }
    return;
}

void ustawObecnosc(int *tabIndeks, bool *tabObecnosc, int indeks, bool obecnosc) {
    for (int i = 0; i < 10; i++)
    {
        if(tabIndeks[i] == indeks)
        {
            tabObecnosc[i] = obecnosc;
            return;
        }
    }
    cout << "Nie znaleziono studenta o podanym nr indeksu.\n";
}

void zmienDane(string *tabImie, string *tabNazwisko, int *tabIndeks, int indeks) {
    for (int i = 0; i < 10; i++)
    {
        if(tabIndeks[i] == indeks)
        {
            cout << "Podaj nowe imie: ";
            cin >> tabImie[i];
            cout << "Podaj nowe nazwisko: ";
            cin >> tabNazwisko[i];
            cout << "Podaj nowy nr indeksu: ";
            cin >> tabIndeks[i];
            cout << "Dane zmienione.\n";
            return;
        }
    }
    cout << "Nie znaleziono studenta o podanym nr indeksu.\n";
}

void usunOsobe(string *tabImie, string *tabNazwisko, int *tabIndeks, bool *tabObecnosc, int indeks) {
    for (int i = 0; i < 10; i++)
    {
        if(tabIndeks[i] == indeks)
        {
            tabImie[i] = "";
            tabNazwisko[i] = "";
            tabIndeks[i] = 0;
            tabObecnosc[i] = false;
            cout << "Student usuniety.\n";
            return;
        }
    }
    cout << "Nie znaleziono studenta o podanym nr indeksu.\n";
}

void wyswietlListe(string *tabImie, string *tabNazwisko, int *tabIndeks, bool *tabObecnosc) {
    for(int i = 0; i < 10; i++)
    {
        if(tabNazwisko[i] != "") {
            cout << tabIndeks[i] << " " << tabImie[i] << " " << tabNazwisko[i] << " ";
            if(tabObecnosc[i] == 1)
            cout << "Obecny/a\n";
            else
            cout << "Nie obecny/a\n"; }
    }
    return;
}

int main() {

    string tabImie[10];
    string tabNazwisko[10];
    int tabIndeks[10] = {};
    bool tabObecnosc[10] = {};
    string imie, nazwisko;
    int indeks;
    bool obecnosc;
    int wybor = 0;

    while(wybor != 6){
        cout << "Wybierz dzialanie:\n";
        cout << "1. Dodaj osobe.\n";
        cout << "2. Ustaw obecnosc.\n";
        cout << "3. Zmien dane studenta.\n";
        cout << "4. Usun studenta.\n";
        cout << "5. Wyswietl liste.\n";
        cout << "6. Zakoncz program\n";

        cin >> wybor;

        switch (wybor){
            case 1:
                cout << "Podaj imie: ";
                cin >> imie;
                cout << "Podaj nazwisko: ";
                cin >> nazwisko;
                cout << "Podaj nr indeksu: ";
                cin >> indeks;
                cout << "Podaj obecnosc (0/1): ";
                cin >> obecnosc;
                dodajOsobe(tabImie, tabNazwisko, tabIndeks, tabObecnosc, imie, nazwisko, indeks, obecnosc);
            break;
            case 2:
                cout << "Podaj nr indeksu: ";
                cin >> indeks;
                cout << "Podaj obecnosc (0/1): ";
                cin >> obecnosc;
                ustawObecnosc(tabIndeks, tabObecnosc, indeks, obecnosc);
            break;
            case 3:
                cout << "Podaj nr indeksu studenta do edycji: ";
                cin >> indeks;
                zmienDane(tabImie, tabNazwisko, tabIndeks, indeks);
            break;
            case 4:
                cout << "Podaj nr indeksu studenta do usuniecia: ";
                cin >> indeks;
                usunOsobe(tabImie, tabNazwisko, tabIndeks, tabObecnosc, indeks);
            break;
            case 5:
                wyswietlListe(tabImie, tabNazwisko, tabIndeks, tabObecnosc);
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