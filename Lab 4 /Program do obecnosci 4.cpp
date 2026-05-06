#include <iostream>
#include <string>

using namespace std;

class Osoba {
    private:
        string imie;
        string nazwisko;
    public:
        int typ; // 1 = Student, 2 = Stazysta

        Osoba() : imie(""), nazwisko(""), typ(0) {}

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

        bool pusty() { return nazwisko == ""; }

        void drukuj() {
            cout << imie << " " << nazwisko;
        }
};

class Student : public Osoba {
    private:
        int indeks;
    public:
        Student() : Osoba(), indeks(0) { typ = 1; }

        void setIndeks(int wartosc) { indeks = wartosc; }
        int getIndeks() { return indeks; }

        void drukuj() {
            Osoba::drukuj();
            cout << " [Student, indeks: " << indeks << "]";
        }
};

class Stazysta : public Osoba {
    private:
        int idPracownika;
    public:
        Stazysta() : Osoba(), idPracownika(0) { typ = 2; }

        void setIdPracownika(int id) { idPracownika = id; }
        int getIdPracownika() { return idPracownika; }

        void drukuj() {
            Osoba::drukuj();
            cout << " [Stazysta, ID: " << idPracownika << "]";
        }
};

class ListaObecnosci {
    public:
        void drukuj() {
            cout << "\n--- Lista: " << nazwa << " ---\n";
            if(iloscOsob == 0) { cout << "Lista jest pusta.\n"; return; }
            for(int i = 0; i < iloscOsob; i++) {
                if(tabOsob[i]->typ == 1)
                    ((Student*)tabOsob[i])->drukuj();
                else if(tabOsob[i]->typ == 2)
                    ((Stazysta*)tabOsob[i])->drukuj();
                else
                    tabOsob[i]->drukuj();
                cout << " " << (tabObecny[i] ? "OBECNY" : "NIEOBECNY") << "\n";
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

        void ustawObecnosc(int id, bool obecnosc) {
            for(int i = 0; i < iloscOsob; i++) {
                if(tabOsob[i]->typ == 1 && ((Student*)tabOsob[i])->getIndeks() == id) {
                    tabObecny[i] = obecnosc;
                    cout << "Obecnosc ustawiona.\n";
                    return;
                }
                if(tabOsob[i]->typ == 2 && ((Stazysta*)tabOsob[i])->getIdPracownika() == id) {
                    tabObecny[i] = obecnosc;
                    cout << "Obecnosc ustawiona.\n";
                    return;
                }
            }
            cout << "Nie znaleziono osoby na liscie.\n";
        }

        void usunOsobe(int id) {
            for(int i = 0; i < iloscOsob; i++) {
                bool found = false;
                if(tabOsob[i]->typ == 1 && ((Student*)tabOsob[i])->getIndeks() == id) found = true;
                if(tabOsob[i]->typ == 2 && ((Stazysta*)tabOsob[i])->getIdPracownika() == id) found = true;
                if(found) {
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

    private:
        string nazwa;
        Osoba* tabOsob[10];
        bool tabObecny[10];
        int iloscOsob = 0;
};

class InterfejsUzytkownika {
    public:
        InterfejsUzytkownika(Osoba** tabOsob, ListaObecnosci* tabLista)
            : tabOsob(tabOsob), tabLista(tabLista), iloscOsob(0), iloscList(0) {}

        ~InterfejsUzytkownika() {
            for(int i = 0; i < iloscOsob; i++)
                delete tabOsob[i];
        }

        void loop() {
            int wybor = 0;
            while(wybor != 9) {
                cout << "\nWybierz dzialanie:\n";
                cout << "1. Dodaj studenta.\n";
                cout << "2. Dodaj stazyste.\n";
                cout << "3. Dodaj liste obecnosci.\n";
                cout << "4. Dodaj osobe do listy.\n";
                cout << "5. Ustaw obecnosc.\n";
                cout << "6. Usun osobe z listy.\n";
                cout << "7. Zmien dane osoby.\n";
                cout << "8. Wyswietl liste obecnosci.\n";
                cout << "9. Zakoncz program.\n";
                cin >> wybor;

                switch(wybor) {
                    case 1: dodajStudenta();     break;
                    case 2: dodajStazyste();     break;
                    case 3: dodajListe();        break;
                    case 4: dodajOsobeDoListy(); break;
                    case 5: ustawObecnosc();     break;
                    case 6: usunOsobeZListy();   break;
                    case 7: zmienDane();         break;
                    case 8: wyswietlListe();     break;
                    case 9:                      break;
                    default: cout << "Nieprawidlowy wybor!\n"; break;
                }
            }
        }

    private:
        Osoba** tabOsob;
        int iloscOsob;
        ListaObecnosci* tabLista;
        int iloscList;

        Osoba* znajdzOsobe(int id) {
            for(int i = 0; i < iloscOsob; i++) {
                if(tabOsob[i]->typ == 1 && ((Student*)tabOsob[i])->getIndeks() == id)
                    return tabOsob[i];
                if(tabOsob[i]->typ == 2 && ((Stazysta*)tabOsob[i])->getIdPracownika() == id)
                    return tabOsob[i];
            }
            return nullptr;
        }

        int wybierzListe() {
            cout << "Dostepne listy:\n";
            for(int i = 0; i < iloscList; i++)
                cout << i << ". " << tabLista[i].getNazwa() << "\n";
            cout << "Podaj numer listy: ";
            int nr; cin >> nr;
            if(nr < 0 || nr >= iloscList) { cout << "Nieprawidlowy nr listy.\n"; return -1; }
            return nr;
        }

        void dodajStudenta() {
            if(iloscOsob >= 10) { cout << "Baza osob jest pelna!\n"; return; }
            string imie, nazwisko;
            int indeks;
            cout << "Podaj imie: ";       cin >> imie;
            cout << "Podaj nazwisko: ";   cin >> nazwisko;
            cout << "Podaj nr indeksu: "; cin >> indeks;
            Student* s = new Student();
            s->setImie(imie);
            s->setNazwisko(nazwisko);
            s->setIndeks(indeks);
            tabOsob[iloscOsob] = s;
            iloscOsob++;
            cout << "Student dodany.\n";
        }

        void dodajStazyste() {
            if(iloscOsob >= 10) { cout << "Baza osob jest pelna!\n"; return; }
            string imie, nazwisko;
            int idPracownika;
            cout << "Podaj imie: ";          cin >> imie;
            cout << "Podaj nazwisko: ";      cin >> nazwisko;
            cout << "Podaj ID pracownika: "; cin >> idPracownika;
            Stazysta* st = new Stazysta();
            st->setImie(imie);
            st->setNazwisko(nazwisko);
            st->setIdPracownika(idPracownika);
            tabOsob[iloscOsob] = st;
            iloscOsob++;
            cout << "Stazysta dodany.\n";
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
            int id;
            cout << "Podaj indeks (student) lub ID pracownika (stazysta): "; cin >> id;
            Osoba* o = znajdzOsobe(id);
            if(o == nullptr) { cout << "Nie znaleziono osoby.\n"; return; }
            tabLista[nr].dodajOsobe(o);
        }

        void ustawObecnosc() {
            int nr = wybierzListe();
            if(nr == -1) return;
            int id;
            bool obecnosc;
            cout << "Podaj indeks (student) lub ID pracownika (stazysta): "; cin >> id;
            cout << "Podaj obecnosc (0/1): "; cin >> obecnosc;
            tabLista[nr].ustawObecnosc(id, obecnosc);
        }

        void usunOsobeZListy() {
            int nr = wybierzListe();
            if(nr == -1) return;
            int id;
            cout << "Podaj indeks (student) lub ID pracownika (stazysta): "; cin >> id;
            tabLista[nr].usunOsobe(id);
        }

        void wyswietlListe() {
            int nr = wybierzListe();
            if(nr == -1) return;
            tabLista[nr].drukuj();
        }

        void zmienDane() {
            int id;
            cout << "Podaj indeks (student) lub ID pracownika (stazysta): "; cin >> id;
            Osoba* o = znajdzOsobe(id);
            if(o == nullptr) { cout << "Nie znaleziono osoby.\n"; return; }
            string imie, nazwisko;
            cout << "Podaj nowe imie: ";     cin >> imie;
            cout << "Podaj nowe nazwisko: "; cin >> nazwisko;
            o->setImie(imie);
            o->setNazwisko(nazwisko);
            cout << "Dane zmienione.\n";
        }
};

int main() {
    Osoba* tabOsob[10] = {};
    ListaObecnosci tabLista[2];
    InterfejsUzytkownika ui(tabOsob, tabLista);
    ui.loop();
}
