#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct T_dane_herbata {
    string name;
    string grade ;
    string type;
    string weight_package;
    string type_package;
    string available_items;
    string time_delivery;
    string comments;
};

T_dane_herbata from_string(const string& data)
{
    // returns T_dane_herbata converted from string
    // example data:  "Lipton,Czarna,Czarna,250g,papierowe,10,24/27/2000,brak,"

    T_dane_herbata result;

    string entry{""};
    unsigned int k = 1;
    for (const char& ch : data)
    {
        if (ch == ',') {
            if (k==1) {
                result.name = entry;
            }
            if (k==2) {
                result.grade = entry;
            }
            if (k==3) {
                result.type = entry;
            }
            if (k==4) {
                result.weight_package = entry;
            }
            if (k==5) {
                result.type_package = entry;
            }
            if (k==6) {
                result.available_items = entry;
            }
            if (k==7) {
                result.time_delivery = entry;
            }
            if (k==8) {
                result.comments = entry;
            }
            entry.clear();
            k++;
        } else {
            entry.push_back(ch);
        }
    }

    return result;
}

vector<T_dane_herbata> load_from_file()
{
    // loads entries stored in herbata.txt file and returns them
    fstream fin;
    vector <T_dane_herbata> data;
    string line;

    fin.open("herbata.txt", ios::in);  // TODO: store file name in global const variable
    while (getline(fin, line)) {
        data.push_back(from_string(line));
    }

    fin.close();

    return data;
}

T_dane_herbata get_from_user() {
    T_dane_herbata result;

    cout<<"Dane dotyczace herbaty: \n";
    cout<<"Nazwa herbaty               = "; cin>>result.name;
    cout<<"Gatunek herbaty             = "; cin>>result.grade;
    cout<<"Typ herbaty                 = "; cin>>result.type;
    cout<<"waga opakowania             = "; cin>>result.weight_package;
    cout<<"typ_opakowania              = "; cin>>result.type_package;
    cout<<"Dostepne sztuki w magazynie = "; cin>>result.available_items;
    cout<<"Data dostawy herbaty        = "; cin>>result.time_delivery;
    cout<<"Uwagi dotyczace herbaty     = "; cin>>result.comments;

    return result;
}

std::string to_string(const T_dane_herbata& entry)
{
    // returns a string containing T_dane_herbata representation
    // example output string: "Lipton,Czarna,Czarna,250g,papierowe,10,24/27/2000,brak,"
    string result{""};

    result += entry.name + ",";
    result += entry.grade + ",";
    result += entry.type + ",";
    result += entry.weight_package + ",";
    result += entry.type_package + ",";
    result += entry.available_items + ",";
    result += entry.time_delivery + ",";
    result += entry.comments + ",";

    return result;
}

std::string to_string(const vector<T_dane_herbata>& entries)
{
    // returns a string containing vector<T_dane_herbata> representation
    string result{""};
    int iterated = 0;
    for (const T_dane_herbata& entry : entries) {
        ++iterated;

        if (iterated < entries.size())
            result += to_string(entry) + "\n";
        else
            result += to_string(entry);
    }

    return result;
}
void save_to_file(vector<T_dane_herbata>& entries) {

    // saves entries to herbata.txt file
    fstream fout;
    fout.open("herbata.txt", ios::out | ios::trunc);
    fout<<to_string(entries);
    fout.close();
}

void tests()
{
    cout << "Testing to_string..." << endl;

    cout << to_string(T_dane_herbata{"Lipton", "Czarna", "Czarna", "250g", "", "", "", ""}) << endl;

    cout << "Testing from_string..." << endl;

    std::cout << to_string(
        from_string("Lipton,Czarna,Czarna,250g,papierowe,10,24/27/2000,brak,")
     ) << std::endl;

    cout << "Testing load_from_file..." << endl;

    std::cout << to_string(
        load_from_file()
     ) << std::endl;
}

int main () {
    vector<T_dane_herbata> database = load_from_file();
    char character;
    while (character != 'k')
    {
        cout<<"Co chcesz zrobic?"<<endl;
        cout<<"Dodac produkt: wpisz 1"<<endl;
        cout<<"Odczytac aktualnie dodane dane: wpisz 2"<<endl;
        cout<<"Usunac wpis: wpisz 3"<<endl;
        cout<<"Test! wpisz 9"<<endl;
        cin>>character;

        switch ( character ) {
            case '1':
            {
                database.push_back(get_from_user());
                save_to_file(database);
                break;
            }
            case '2':
                cout << to_string(database) << endl;
                break;
            case '3':
                {
                    cout << "Podaj numer wiersza";

                    char number;
                    cin>>number;
                    string str_representation;
                    str_representation.push_back(number-1);
                    database.erase(database.begin() + stoi(str_representation));
                    save_to_file(database);

                    break;
                }
            case '9':
            {
                tests();
                break;
            }
            default:
                cout<<"nie wiem co mam zrobic ze soba\n";
                break;
        }
    }

    return 0;
}
