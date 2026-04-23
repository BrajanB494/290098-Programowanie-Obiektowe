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

        bool pusty() { return nazwisko == ""; }
};

class ListaObecnosci {
    public:
        void drukuj() {
            cout << "\n--- Lista: " << nazwa << " ---\n";
            if(iloscOsob == 0) { cout << "Lista jest pusta.\n"; return; }
            for(int i = 0; i < iloscOsob; i++) {
                cout << tabOsob[i]->getIndeks() << " "
                     << tabOsob[i]->getImie() << " "
                     << tabOsob[i]->getNazwisko() << " "
                     << (tabObecny[i] ? "OBECNY" : "NIEOBECNY") << "\n";
            }
            cout << "----------------------\n";
        }

        void dodajOsobe(Osoba* osoba) {
            if(iloscOsob >= 10) { cout << "Lista jest pelna!\n"; return; }
            tabOsob[iloscOsob] = osoba;
            tabObecny[iloscOsob] = false;
            iloscOsob++;
            cout << "Osoba dodana do listy.\n";
        }

        void ustawObecnosc(int indeks, bool obecnosc) {
            for(int i = 0; i < iloscOsob; i++) {
                if(tabOsob[i]->getIndeks() == indeks) {
                    tabObecny[i] = obecnosc;
                    cout << "Obecnosc ustawiona.\n";
                    return;
                }
            }
            cout << "Nie znaleziono osoby na liscie.\n";
        }

        void usunOsobe(int indeks) {
            for(int i = 0; i < iloscOsob; i++) {
                if(tabOsob[i]->getIndeks() == indeks) {
                    for(int j = i; j < iloscOsob - 1; j++) {
                        tabOsob[j] = tabOsob[j+1];
                        tabObecny[j] = tabObecny[j+1];
                    }
                    iloscOsob--;
                    cout << "Osoba usunieta z listy.\n";
                    return;
                }
            }
            cout << "Nie znaleziono osoby na liscie.\n";
        }

        void setNazwa(string n) { nazwa = n; }
        string getNazwa() { return nazwa; }
        bool pustaNazwa() { return nazwa == ""; }

    private:
        string nazwa;
        Osoba* tabOsob[10];
        bool tabObecny[10];
        int iloscOsob = 0;
};

class InterfejsUzytkownika {
    public:
        InterfejsUzytkownika(Osoba* tabOsob, ListaObecnosci* tabLista)
            : tabOsob(tabOsob), tabLista(tabLista), iloscOsob(0), iloscList(0) {}

        void loop() {
            int wybor = 0;
            while(wybor != 8) {
                cout << "\nWybierz dzialanie:\n";
                cout << "1. Dodaj osobe.\n";
                cout << "2. Dodaj liste obecnosci.\n";
                cout << "3. Dodaj osobe do listy.\n";
                cout << "4. Ustaw obecnosc.\n";
                cout << "5. Usun osobe z listy.\n";
                cout << "6. Zmien dane osoby.\n";
                cout << "7. Wyswietl liste obecnosci.\n";
                cout << "8. Zakoncz program.\n";
                cin >> wybor;

                switch(wybor) {
                    case 1: dodajOsobe();
                    break;
                    case 2: dodajListe();
                    break;
                    case 3: dodajOsobeDoListy();
                    break;
                    case 4: ustawObecnosc();
                    break;
                    case 5: usunOsobeZListy();
                    break;
                    case 6: zmienDane();
                    break;
                    case 7: wyswietlListe();
                    break;
                    case 8: cout << "Do widzenia!\n";
                    break;
                    default: cout << "Nieprawidlowy wybor!\n";
                    break;
                }
            }
        }

    private:
        Osoba* tabOsob;
        int iloscOsob;
        ListaObecnosci* tabLista;
        int iloscList;

        Osoba* znajdzOsobe(int indeks) {
            for(int i = 0; i < iloscOsob; i++)
                if(tabOsob[i].getIndeks() == indeks)
                    return &tabOsob[i];
            return nullptr;
        }

        int () {
            cout << "Dostepne listy:\n";
            for(int i = 0; i < iloscList; i++)
                cout << i << ". " << tabLista[i].getNazwa() << "\n";
            cout << "Podaj numer listy: ";
            int nr; cin >> nr;
            if(nr < 0 || nr >= iloscList) { cout << "\nNieprawidlowy nr listy.\n"; return -1; }
            return nr;
        }

        void dodajOsobe() {
            if(iloscOsob >= 10) { cout << "Baza osob jest pelna!\n"; return; }
            string imie, nazwisko;
            int indeks;
            cout << "Podaj imie: ";       cin >> imie;
            cout << "Podaj nazwisko: ";   cin >> nazwisko;
            cout << "Podaj nr indeksu: "; cin >> indeks;
            tabOsob[iloscOsob].setImie(imie);
            tabOsob[iloscOsob].setNazwisko(nazwisko);
            tabOsob[iloscOsob].setIndeks(indeks);
            iloscOsob++;
            cout << "Osoba dodana.\n";
        }

        void dodajListe() {
            if(iloscList >= 2) { cout << "Osiagnieto limit list!\n"; return; }
            string nazwa;
            cout << "Podaj nazwe listy: "; cin >> nazwa;
            tabLista[iloscList].setNazwa(nazwa);
            iloscList++;
            cout << "Lista stworzona.\n";
        }

        void dodajOsobeDoListy() {
            int nr = wybierzListe();
            if(nr == -1) return;
            int indeks;
            cout << "Podaj nr indeksu osoby: "; cin >> indeks;
            Osoba* o = znajdzOsobe(indeks);
            if(o == nullptr) { cout << "Nie znaleziono osoby.\n"; return; }
            tabLista[nr].dodajOsobe(o);
        }

        void ustawObecnosc() {
            int nr = wybierzListe();
            if(nr == -1) return;
            int indeks;
            bool obecnosc;
            cout << "Podaj nr indeksu: ";    cin >> indeks;
            cout << "Podaj obecnosc (0/1): "; cin >> obecnosc;
            tabLista[nr].ustawObecnosc(indeks, obecnosc);
        }

        void usunOsobeZListy() {
            int nr = wybierzListe();
            if(nr == -1) return;
            int indeks;
            cout << "Podaj nr indeksu osoby do usuniecia: "; cin >> indeks;
            tabLista[nr].usunOsobe(indeks);
        }

        void wyswietlListe() {
            int nr = wybierzListe();
            if(nr == -1) return;
            tabLista[nr].drukuj();
        }

        void zmienDane() {
            int indeks;
            cout << "Podaj nr indeksu osoby do edycji: "; cin >> indeks;
            Osoba* o = znajdzOsobe(indeks);
            if(o == nullptr) { cout << "Nie znaleziono osoby.\n"; return; }
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
};

int main() {
    Osoba tabOsob[10];
    ListaObecnosci tabLista[2];
    InterfejsUzytkownika menu(tabOsob, tabLista);
    menu.loop();
}
