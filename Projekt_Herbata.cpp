#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int numberoflines() {
    string line; int number_of_lines=0;
    ifstream myfile("herbata.txt");

    if(myfile.is_open()){
        while(!myfile.eof()){
            getline(myfile,line);
            number_of_lines++;
        }
        myfile.close();
    }
    return number_of_lines-1; // number_of_lines jest o jeden wieksze
}

struct T_dane_herbata {
    string name;
    string grade ;
    string type;
    string weight_package;
    string type_package;
    string available_items;
    string time_delivery;
    string comments;
} data[4];

void LOAD_data_tea (){
    cout<<"Dane dotyczace herbaty: \n";
    cout<<"Nazwa herbaty               = "; cin>>data[numberoflines()].name;
    cout<<"Gatunek herbaty             = "; cin>>data[numberoflines()].grade;
    cout<<"Typ herbaty                 = "; cin>>data[numberoflines()].type;
    cout<<"waga opakowania             = "; cin>>data[numberoflines()].weight_package;
    cout<<"typ_opakowania              = "; cin>>data[numberoflines()].type_package;
    cout<<"Dostepne sztuki w magazynie = "; cin>>data[numberoflines()].available_items;
    cout<<"Data dostawy herbaty        = "; cin>>data[numberoflines()].time_delivery;
    cout<<"Uwagi dotyczace herbaty     = "; cin>>data[numberoflines()].comments;
    // dane w pliku
    fstream fout;
    fout.open("herbata.txt", ios::out | ios::app);
    fout<<numberoflines()+1<<',';
    fout<<data[numberoflines()].name<<',';
    fout<<data[numberoflines()].grade<<',';
    fout<<data[numberoflines()].type<<',';
    fout<<data[numberoflines()].weight_package<<',';
    fout<<data[numberoflines()].type_package<<',';
    fout<<data[numberoflines()].available_items<<',';
    fout<<data[numberoflines()].time_delivery<<',';
    fout<<data[numberoflines()].comments<<','<<endl;
    fout.close();
}

void DISPLAY_data_tea () {
    fstream fin;    string line_file;  string line_copy; unsigned int k; unsigned int n=0;    int how_many_times=0;
    fin.open("herbata.txt", ios::in);
    if (fin.good()==false) {
        cout<<"Plik nie istnieje!";
        exit(0);
    }
    while (how_many_times < numberoflines() )  {
    fin>>line_file;
    k=0;
    for (int i=0;i<line_file.size();i++) {
        if (line_file[i]==',') {
            k++;    n=0;
            line_copy.clear();
        }
        else {
            line_copy[n] = line_file[i];
            if (k==1) {
                data[how_many_times].name = data[how_many_times].name + line_copy[n];
            }
            if (k==2) {
                data[how_many_times].grade = data[how_many_times].grade + line_copy[n];
            }
            if (k==3) {
                data[how_many_times].type = data[how_many_times].type + line_copy[n];
            }
            if (k==4) {
                data[how_many_times].weight_package = data[how_many_times].weight_package + line_copy[n];
            }
            if (k==5) {
                data[how_many_times].type_package = data[how_many_times].type_package + line_copy[n];
            }
            if (k==6) {
                data[how_many_times].available_items = data[how_many_times].available_items + line_copy[n];
            }
            if (k==7) {
                data[how_many_times].time_delivery = data[how_many_times].time_delivery + line_copy[n];
            }
            if (k==8) {
                data[how_many_times].comments = data[how_many_times].comments + line_copy[n];
            }
        }
        n++;
    }
    cout<<"\nProdukt nr: "<<how_many_times+1<<endl;
    cout<<"\nNazwa herbaty               = "; cout<<data[how_many_times].name;
    cout<<"\nGatunek herbaty             = "; cout<<data[how_many_times].grade;
    cout<<"\nTyp herbaty                 = "; cout<<data[how_many_times].type;
    cout<<"\nwaga opakowania             = "; cout<<data[how_many_times].weight_package;
    cout<<"\ntyp_opakowania              = "; cout<<data[how_many_times].type_package;
    cout<<"\nDostepne sztuki w magazynie = "; cout<<data[how_many_times].available_items;
    cout<<"\nData dostawy herbaty        = "; cout<<data[how_many_times].time_delivery;
    cout<<"\nUwagi dotyczace herbaty     = "; cout<<data[how_many_times].comments;
    cout<<endl;
    how_many_times++;
    }
    fin.close();
}
void ERASE_data_tea() {
    fstream fin;    string  line;   int how_many_times=0;
    vector <string> data;
    fin.open("herbata.txt", ios::in);
    while (getline(fin,line) )
        data.push_back(line);
    fin.close();

    fstream fout;
    fout.open("herbata1.txt", ios::out | ios::app);
    while (how_many_times <= numberoflines() ){
        fout<< (data.begin() + how_many_times);
        how_many_times++;
    }
    fout.close();
}


int main () {
    char character;
    cout<<"Co chcesz zrobic?"<<endl;
    cout<<"Dodac produkt: wpisz 1"<<endl;
    cout<<"Odczytac aktualnie dodane dane: wpisz 2"<<endl;
    cin>>character;

    switch ( character ) {
    case '1':
            cout<<endl;
            LOAD_data_tea();
        break;
    case '2':
            cout<<endl;
            DISPLAY_data_tea();
        break;
    default:
        cout<<"nie wiem co mam zrobic ze soba";
        break;
    }

    return 0;
}
