#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <regex>

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
int get_line_number() {
    int number;
    cout << "Podaj numer produktu: ";
    cin>>number;
    return number-1;
}

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
string get_date_from_user() {
    int day; int month; int year;
    cout<<"Podaj dzien: ";;  cin>>day;
    cout<<"Podaj miesiac: "; cin>>month;
    cout<<"Podaj rok: ";     cin>>year;
    string result = "";
    result = to_string(day) + '/' + to_string(month) + '/' + to_string(year);
    return result;
}
T_dane_herbata get_from_user() {
    T_dane_herbata result;
    cin.ignore();
    cout<<"Dane dotyczace herbaty: \n";
    cout<<"Nazwa herbaty               = "; getline(std::cin,result.name);
    cout<<"Gatunek herbaty             = "; getline(std::cin,result.grade); //  cin>>result.grade;
    cout<<"Typ herbaty                 = "; getline(std::cin,result.type);
    cout<<"waga opakowania             = "; getline(std::cin,result.weight_package);
    cout<<"typ_opakowania              = "; getline(std::cin,result.type_package);
    cout<<"Dostepne sztuki w magazynie = "; getline(std::cin,result.available_items);
    cout<<"Data dostawy herbaty:\n"; result.time_delivery = get_date_from_user();
    cin.ignore();
    cout<<"Uwagi dotyczace herbaty     = "; getline(std::cin,result.comments);

    return result;
}

void display_from_memory (const vector<T_dane_herbata>& entry, int n) {
        cout<<"\nProdukt nr: "<<n+1<<endl;
        cout<<"Nazwa herbaty               = "<<entry[n].name<<endl;
        cout<<"Gatunek herbaty             = "<<entry[n].grade<<endl;
        cout<<"Typ herbaty                 = "<<entry[n].type<<endl;
        cout<<"waga opakowania             = "<<entry[n].weight_package<<endl;
        cout<<"typ_opakowania              = "<<entry[n].type_package<<endl;
        cout<<"Dostepne sztuki w magazynie = "<<entry[n].available_items<<endl;
        cout<<"Data dostawy herbaty        = "<<entry[n].time_delivery<<endl;
        cout<<"Uwagi dotyczace herbaty     = "<<entry[n].comments<<endl;
}
void save_to_file(const vector<T_dane_herbata>& entries) {

    // saves entries to herbata.txt file
    fstream fout;
    fout.open("herbata.txt", ios::out | ios::trunc);
    fout<<to_string(entries);
    fout.close();
}
void change_line(vector<T_dane_herbata>& entries) {
    int number = get_line_number();
    display_from_memory(entries, number);
    entries.push_back(get_from_user());
    entries[number] = entries[entries.size()-1];
    entries.erase(entries.end() );
    save_to_file(entries);
}
void change_line_properties(vector<T_dane_herbata>& entries) {
    T_dane_herbata result;
    string line;
    int number = get_line_number();
    display_from_memory(entries, number);
    cout<<"\nCo zmienic w produkcie? [nazwa/gatunek/typ/waga/opakowanie/ilosc/data/uwagi]: ";
    cin.ignore();
    getline(std::cin,line);
    if (line=="nazwa") {
        cout<<"Podaj nowa nazwe dostawy     = ";
        getline(std::cin,result.name);
        entries[number].name = result.name;
        }
    if (line=="gatunek") {
        cout<<"Podaj nowy gatunek herbaty  = ";
        getline(std::cin,result.grade);
        entries[number].grade = result.grade;
    }
    if (line=="typ") {
        cout<<"Podaj nowy typ herbaty      = ";
        getline(std::cin,result.type);
        entries[number].type = result.type;
    }
    if (line=="waga") {
        cout<<"Podaj nowa wage opakowania  = ";
        getline(std::cin,result.weight_package);
        entries[number].weight_package = result.weight_package;
    }
    if (line=="opakowanie") {
        cout<<"Podaj nowy typ opakowania   = ";
        getline(std::cin,result.type_package);
        entries[number].type_package = result.type_package;
    }
    if (line=="ilosc") {
        cout<<"Podaj nowa ilosc w magazynie= ";
        getline(std::cin,result.available_items);
        entries[number].available_items = result.available_items;
    }
    if (line=="data") {
        cout<<"Podaj nowa date dostawy:";
        get_date_from_user();
        entries[number].time_delivery = result.time_delivery;
    }
    if (line=="uwagi") {
        cout<<"Podaj nowa tresc uwag       = ";
        getline(std::cin,result.comments);
        entries[number].comments = result.comments;
    }
    save_to_file(entries);
}

/*
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
*/
void searching(const vector<T_dane_herbata>& data) {
    cout<<"\nMozna wyszukac po:[nazwie/gatunku/typie]\n";
    string line; string temporary;
    cin.ignore();
    getline(cin,line);
    for(int i = 1; i<line.size(); i++){
        line[i] = tolower(line[i]);
    }
    if (line =="nazwie" || line =="nazwa") {
        line = "";
        cout<<"\nJaka nazwa herbaty?\n";

        getline(cin,line);
        for(int i = 0; i<line.size(); i++){
            line[i] = tolower(line[i]);
        }
        int k=0;
        for (int i=0;i<data.size();i++) {
            smatch result;
            temporary = "";
            temporary = data[i].name;
                for(int i = 0; i<temporary.size(); i++){
                    temporary[i] = tolower(temporary[i]);
                }
            if( regex_search(temporary, result, regex(line) ) ) {
                display_from_memory(data,i);
                k++;
            }
        }
        if (k==0)
            cout<<"\nNie istnieje produkt o takiej nazwie\n";
    }
    if (line =="gatunku" || line =="gatunek") {
        line = "";
        cout<<"\nJaki gatunek herbaty?\n";

        getline(cin,line);
        for(int i = 0; i<line.size(); i++){
            line[i] = tolower(line[i]);
        }
        int k=0;
        for (int i=0;i<data.size();i++) {
            smatch result;
            temporary = "";
            temporary = data[i].grade;
                for(int i = 0; i<temporary.size(); i++){
                    temporary[i] = tolower(temporary[i]);
                }
            if( regex_search(temporary, result, regex(line) ) ) {
                display_from_memory(data,i);
                k++;
            }
        }
        if (k==0)
            cout<<"\nNie istnieje produkt o takim gatunku herbaty\n";

    }
    if (line =="typie" || line =="typ") {
        line = "";
        cout<<"\nJaki typ herbaty?\n";

        getline(cin,line);
        for(int i = 0; i<line.size(); i++){
            line[i] = tolower(line[i]);
        }
        int k=0;
        for (int i=0;i<data.size();i++) {
            smatch result;
            temporary = "";
            temporary = data[i].type;
                for(int i = 0; i<temporary.size(); i++){
                    temporary[i] = tolower(temporary[i]);
                }
            if( regex_search(temporary, result, regex(line) ) ) {
                display_from_memory(data,i);
                k++;
            }
        }
        if (k==0)
            cout<<"\nNie istnieje produkt o takim typie herbaty\n";

    }
}

int main () {
    vector<T_dane_herbata> database = load_from_file();
    char character;
    while (character != 'k')
    {
        cout<<"================================\n";
        cout<<" Co chcesz zrobic?"<<endl;
        cout<<" Dodac produkt: wpisz 1"<<endl;
        cout<<" Odczytac dane: wpisz 2"<<endl;
        cout<<" Usunac produkt: wpisz 3"<<endl;
        cout<<" zmienic dane produktu: wpisz 4"<<endl;
        cout<<" Zmienic dane rekordu : wpisz 5"<<endl;
        cout<<" wyszukiwanie: wpisz 6"<<endl;
        cout<<" koniec: wpisz 'k'\n";
        cout<<"================================\n";
        cout<<" Twoj wybor to: ";
        cin>>character;
        cout<<endl;

        switch ( character ) {
            case '1':{
                    database.push_back(get_from_user());
                    save_to_file(database);
                    break;
                }
            case '2':{
                //cout << to_string(database) << endl;
                for (int i=0;i<database.size();i++)
                    display_from_memory(database,i);
                break;
                }
            case '3':{
                    database.erase(database.begin() + get_line_number() );
                    save_to_file(database);
                    break;
                }
            case '4':{
                    change_line(database);
                    break;
                }
            case '5':{
                    change_line_properties(database);
                    break;
                }
            case '6':{
                    searching(database);
                    break;
                }
            /*case '9':{
                tests();
                break;
                } */
            default:{
                cout<<"nie wiem co mam zrobic\n";
                break;
                }
        }
    }
    return 0;
}
