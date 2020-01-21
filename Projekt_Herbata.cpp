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

int get_product_index() {
    // returns index for vector element
    int index;

    cout << "Podaj numer produktu: ";   cin>>index;

    return index-1;
}

T_dane_herbata from_string(const string& data) {
    // returns T_dane_herbata converted from string
    T_dane_herbata result;
    string entry{""};
    unsigned int struct_element = 1;

    for (const char& character : data) {
        if (character == ',') {
            if (struct_element==1) {
                result.name = entry;
            }
            if (struct_element==2) {
                result.grade = entry;
            }
            if (struct_element==3) {
                result.type = entry;
            }
            if (struct_element==4) {
                result.weight_package = entry;
            }
            if (struct_element==5) {
                result.type_package = entry;
            }
            if (struct_element==6) {
                result.available_items = entry;
            }
            if (struct_element==7) {
                result.time_delivery = entry;
            }
            if (struct_element==8) {
                result.comments = entry;
            }
            entry.clear();
            struct_element++;
        }
        else {
            entry.push_back(character);
        }
    }

    return result;
}

vector <T_dane_herbata> load_from_file() {
    // loads entries stored in herbata.txt file and returns them
    fstream fin;
    vector <T_dane_herbata> data;
    string file_string;

    fin.open("herbata.txt", ios::in);
    while (getline(fin, file_string)) {
        data.push_back(from_string(file_string));
    }
    fin.close();

    return data;
}

string to_string(const T_dane_herbata& entry) {
    // returns a string containing T_dane_herbata representation
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

string to_string(const vector<T_dane_herbata>& entries) {
    // returns a string containing vector <T_dane_herbata> representation
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
    // gets date info from user and returns it in dd/mm/yyyy format
    int day;
    int month;
    int year;
    string result = "";

    cout<<"Podaj dzien: ";;  cin>>day;
    cout<<"Podaj miesiac: "; cin>>month;
    cout<<"Podaj rok: ";     cin>>year;
    result = to_string(day) + '/' + to_string(month) + '/' + to_string(year);

    return result;
}

T_dane_herbata get_from_user() {
    // gets all struct elements from user and returns filled struct T_dane_herbata
    T_dane_herbata result;

    cin.ignore();
    cout<<"Dane dotyczace herbaty: \n";
    cout<<"Nazwa herbaty               = "; getline(cin,result.name);
    cout<<"Gatunek herbaty             = "; getline(cin,result.grade);
    cout<<"Typ herbaty                 = "; getline(cin,result.type);
    cout<<"Waga opakowania             = "; getline(cin,result.weight_package);
    cout<<"Typ_opakowania              = "; getline(cin,result.type_package);
    cout<<"Dostepne sztuki w magazynie = "; getline(cin,result.available_items);
    cout<<"Data dostawy herbaty:\n";        result.time_delivery = get_date_from_user();
    cout<<"Uwagi dotyczace herbaty     = "; getline(cin,result.comments);

    return result;
}

void display_from_memory (const vector<T_dane_herbata>& entry, int index) {
    // displays data from specific index of vector<T_dane_herbata>
    cout<<"\nProdukt nr: "<<index+1<<endl;
    cout<<"Nazwa herbaty               = "<<entry[index].name<<endl;
    cout<<"Gatunek herbaty             = "<<entry[index].grade<<endl;
    cout<<"Typ herbaty                 = "<<entry[index].type<<endl;
    cout<<"Waga opakowania             = "<<entry[index].weight_package<<endl;
    cout<<"Typ_opakowania              = "<<entry[index].type_package<<endl;
    cout<<"Dostepne sztuki w magazynie = "<<entry[index].available_items<<endl;
    cout<<"Data dostawy herbaty        = "<<entry[index].time_delivery<<endl;
    cout<<"Uwagi dotyczace herbaty     = "<<entry[index].comments<<endl;
}

void save_to_file(const vector<T_dane_herbata>& entries) {
    // saves entries to herbata.txt file
    fstream fout;

    fout.open("herbata.txt", ios::out | ios::trunc);
    fout<<to_string(entries);
    fout.close();
}

void change_product_details(vector<T_dane_herbata>& entries) {
    // allows user to change data of entire product contained in specific index of vector<T_dane_herbata>
    int index = get_product_index();

    display_from_memory(entries, index);
    entries.push_back(get_from_user());
    entries[index] = entries[entries.size()-1];
    entries.erase(entries.end() );
    save_to_file(entries);
}

void change_product_element_details(vector<T_dane_herbata>& entries) {
    // allows user to change data of specific product element contained in specific index of vector<T_dane_herbata>
    T_dane_herbata result;
    string product_element;
    int index = get_product_index();

    display_from_memory(entries, index);
    cout<<"\nCo zmienic w produkcie? [nazwa/gatunek/typ/waga/opakowanie/ilosc/data/uwagi]: ";
    cin.ignore();
    getline(cin,product_element);
    if (product_element=="nazwa") {
        cout<<"Podaj nowa nazwe dostawy     = ";
        getline(cin,result.name);
        entries[index].name = result.name;
        }
    if (product_element=="gatunek") {
        cout<<"Podaj nowy gatunek herbaty  = ";
        getline(cin,result.grade);
        entries[index].grade = result.grade;
    }
    if (product_element=="typ") {
        cout<<"Podaj nowy typ herbaty      = ";
        getline(cin,result.type);
        entries[index].type = result.type;
    }
    if (product_element=="waga") {
        cout<<"Podaj nowa wage opakowania  = ";
        getline(cin,result.weight_package);
        entries[index].weight_package = result.weight_package;
    }
    if (product_element=="opakowanie") {
        cout<<"Podaj nowy typ opakowania   = ";
        getline(cin,result.type_package);
        entries[index].type_package = result.type_package;
    }
    if (product_element=="ilosc") {
        cout<<"Podaj nowa ilosc w magazynie= ";
        getline(cin,result.available_items);
        entries[index].available_items = result.available_items;
    }
    if (product_element=="data") {
        cout<<"Podaj nowa date dostawy:";
        get_date_from_user();
        entries[index].time_delivery = result.time_delivery;
    }
    if (product_element=="uwagi") {
        cout<<"Podaj nowa tresc uwag       = ";
        getline(cin,result.comments);
        entries[index].comments = result.comments;
    }
    save_to_file(entries);
}

void product_search(const vector<T_dane_herbata>& data) {
    // allows user to search for specific name/grade/type of product
    cout<<"\nMozna wyszukac po:[nazwie/gatunku/typie]\n";
    string key_word;
    string struct_element;
    string searched_element;
    bool search_true=false;

    cin.ignore();
    getline(cin,searched_element);
    if (searched_element =="nazwie" || searched_element =="nazwa") {
        cout<<"\nJaka nazwa herbaty?\n";
        getline(cin,key_word);
        for(int i = 0; i<key_word.size(); i++){
            key_word[i] = tolower(key_word[i]);
        }
        for (int i=0;i<data.size();i++) {
            smatch result;

            struct_element = data[i].name;
            for(int i = 0; i<struct_element.size(); i++){
                struct_element[i] = tolower(struct_element[i]);
            }
            if( regex_search(struct_element, result, regex(key_word) ) ) {
                display_from_memory(data,i);
                search_true=true;
            }
        }
        if (search_true)
            cout<<"\nNie istnieje produkt o takiej nazwie\n";
    }
    if (searched_element =="gatunku" || searched_element =="gatunek") {
        cout<<"\nJaki gatunek herbaty?\n";
        getline(cin,key_word);
        for(int i = 0; i<key_word.size(); i++){
            key_word[i] = tolower(key_word[i]);
        }
        for (int i=0;i<data.size();i++) {
            smatch result;

            struct_element = data[i].grade;
            for(int i = 0; i<struct_element.size(); i++){
                struct_element[i] = tolower(struct_element[i]);
            }
            if( regex_search(struct_element, result, regex(key_word) ) ) {
                display_from_memory(data,i);
                search_true=true;
            }
        }
        if (search_true==0)
            cout<<"\nNie istnieje produkt o takim gatunku herbaty\n";
    }
    if (searched_element =="typie" || searched_element =="typ") {
        cout<<"\nJaki typ herbaty?\n";

        getline(cin,key_word);
        for(int i = 0; i<key_word.size(); i++){
            key_word[i] = tolower(key_word[i]);
        }
        for (int i=0;i<data.size();i++) {
            smatch result;

            struct_element = data[i].type;
            for(int i = 0; i<struct_element.size(); i++){
                struct_element[i] = tolower(struct_element[i]);
            }
            if( regex_search(struct_element, result, regex(key_word) ) ) {
                display_from_memory(data,i);
                search_true=true;
            }
        }
        if (search_true)
            cout<<"\nNie istnieje produkt o takim typie herbaty\n";
    }
}

int main () {
    vector<T_dane_herbata> database = load_from_file();
    char character;

    while (character != 'k'){
        // menu options
        cout<<"================================\n";
        cout<<" Co chcesz zrobic?"<<endl;
        cout<<" Dodac produkt: wpisz 1"<<endl;
        cout<<" Odczytac dane: wpisz 2"<<endl;
        cout<<" Usunac produkt: wpisz 3"<<endl;
        cout<<" Zmienic dane produktu: wpisz 4"<<endl;
        cout<<" Zmienic dane rekordu : wpisz 5"<<endl;
        cout<<" Wyszukiwanie: wpisz 6"<<endl;
        cout<<" Koniec: wpisz 'k'\n";
        cout<<"================================\n";
        cout<<" Twoj wybor to: ";   cin>>character;
        cout<<endl;
        switch ( character ) {
            // real use of menu options
            case '1': {
                database.push_back(get_from_user());
                save_to_file(database);
                break;
                }
            case '2': {
                for (int i=0;i<database.size();i++)
                    display_from_memory(database,i);
                break;
                }
            case '3': {
                database.erase(database.begin() + get_product_index() );
                save_to_file(database);
                break;
                }
            case '4': {
                change_product_details(database);
                break;
                }
            case '5': {
                change_product_element_details(database);
                break;
                }
            case '6': {
                product_search(database);
                break;
                }
            default: {
                if (character != 'k')
                    cout<<"Nie wiem co mam zrobic\n";
                else
                    cout<<"Koniec dzialania programu!\n";
                break;
                }
        }
    }

    return 0;
}
