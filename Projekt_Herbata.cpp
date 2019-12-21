#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

string line1;
void load_line () {

    cout<<"PODAJ linie 1 ";  cin>> line1;
    cout<<"linia 1:"<<line1<<endl;

}

void add_line() {
    fstream fout;

    fout.open("herbata.txt", ios::out | ios::app);
    fout<<line1<<endl;

    fout.close();
}

void read_line () {
    fstream fin;
    fin.open("herbata.txt", ios::in);

    if (fin.good()==false) {
        cout<<"Plik nie istnieje!";
        exit(0);
    }
    string line;
    fin>> line;
    while (!fin.eof() ) {
        cout<<line<<endl;
        fin>>line;
    }
}

int main() {
    char character;
    cout<<"Co chcesz zrobic?"<<endl;
    cout<<"Dodac linie: wpisz 1"<<endl;
    cout<<"Odczytac aktualnie dodane dane: wpisz 2"<<endl;
    cin>>character;

    switch ( character ) {
    case '1':
        load_line();
        add_line();
        break;
    case '2':
        read_line();
        break;
    default:
        cout<<"nie wiem co mam zrobic ze soba";
        break;
    }

    return 0;
}
