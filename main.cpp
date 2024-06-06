#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <unordered_map>


struct Account {
    Account(Account *pAccount) {}
    unsigned int id;            // идентификатор
    std::string login;          // логин
    std::string name;           // имя
    std::string shell;          // оболочка
    std::string home_directory;// домашняя директория

    Account(unsigned int i, std::string log,std::string n, std::string s, std::string home){
        id = i;
        login = std::move(log);;
        name = std::move(n);
        shell = std::move(s);;
        home_directory = std::move(home);
    };
};


bool operator< (Account c1, Account c2){return(c1.id < c2.id);}
bool operator> (Account c1, Account c2){return c1.id > c2.id;}


int main() {
    std::vector<std::string> id;
    std::vector<std::string> names;
    std::vector<std::string> bash;
    {
        std::ifstream f("id.txt");
        std::string line;
        while (std::getline(f, line))
            id.push_back(line);
    }
    {
        std::ifstream f("name.txt");
        std::string line2;
        while (std::getline(f, line2))
            names.push_back(line2);
    }
    {
        std::ifstream f("bash.txt");
        std::string line3;
        while (std::getline(f, line3))
            bash.push_back(line3);
    }


    std::vector<Account> database;
    for (int i = 0; i < 321; i++) {
        unsigned int u = std::stoul(id[i]);
        database.emplace_back( u ,names[i],names[i],bash[i],bash[i]);
    }

    auto is_even = [](Account x) {
        return x.shell == "/usr/bin\r";
    };

    std::vector<Account> base1;
    auto it = database.begin();
    while (it != database.end()) {
        if (auto result = std::find_if(it, database.end(), is_even); result != database.end()){
            base1.push_back(*result);
            it = result+1;
        }
    }


    std::map<Account,unsigned int> base2;
    for (auto & i : database) {
        base2[i] = i.id;
    }
    std::erase_if(base2,[](const auto& item) {
        auto const& [key, value] = item;
        return (value > 1000 or value < 0);
    }
    );


    std::unordered_map<std::string ,unsigned int> base3;
    for (auto & i : database) {
        base3[i.shell] += 1;
    }


    std::unordered_set<unsigned int> setBase;
    std::unordered_set<unsigned int> dublBase;
    for (auto & i : database) {
        if (setBase.find(i.id) == setBase.end()){
            setBase.insert(i.id);
        }
        else
            dublBase.insert(i.id);
    }



    std::cout << "Task 1" << std::endl;;
    for (auto i: base1){
        std::cout<<i.shell<<std::endl;
    }

    std::cout << std::endl << "Task 2" << std::endl;
    for (auto i:base2){
        std::cout<<i.first.id<<std::endl;
    }

    std::cout << std::endl << "Task 3" << std::endl;
    for (auto i:base3){
        std::cout<<i.second<<" "<<i.first<<std::endl;
    }

    std::cout << std::endl << "Task 4" << std::endl;
    for (auto & i : dublBase) {
        std::cout << "Found " << i << std::endl ;
    }
    return 0;
}