#include <vector>
#include <iostream>

struct Adrian
{
    std::string name;
    std::string surname;

    std::string to_string() const 
    {
        return name + " " + surname;
    };
};

std::string to_string(const Adrian& adrian)
{
    return adrian.name + " " + adrian.surname;
}

int main()
{
    std::vector<Adrian> vector_of_adrians{
        {"Adrian", "Mazur"},
        {"Adrian", "NieMazur"}
    };


    vector_of_adrians.push_back({"Adrian", "Z Polski!"});

    for (const auto& adrian : vector_of_adrians)
    {
        std::cout << to_string(adrian) << std::endl;
    }

    for (auto i = 0 ; i < vector_of_adrians.size() ; ++i)
    {
        const auto& adrian = vector_of_adrians[i];
    
        std::cout << adrian.to_string() << std::endl;
    }


}