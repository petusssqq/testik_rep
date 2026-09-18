#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>
#include <random>
#include <cmath>
#include <ctime>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

struct Item {
    string name;
    double mainParam;
    double secondaryParam;
};

// Вывод структуры
ostream& operator<<(ostream& os, const Item& item) {
    os << "Name: " << item.name
       << ", Main: " << item.mainParam
       << ", Secondary: " << item.secondaryParam;
    return os;
}

// Сохранение в JSON
void saveToJson(const list<Item>& items, const string& filename) {
    json j = json::array();

    for (const auto& item : items) {
        j.push_back({
            {"name", item.name},
            {"mainParam", item.mainParam},
            {"secondaryParam", item.secondaryParam}
        });
    }

    ofstream out(filename);
    out << j.dump(4);
    out.close();
}

// Загрузка из JSON
list<Item> loadFromJson(const string& filename) {
    list<Item> items;
    ifstream in(filename);

    if (!in.is_open()) {
        cerr << "Нельзя открыть JSON файл.\n";
        return items;
    }

    json j;
    in >> j;

    for (const auto& elem : j) {
        Item item;
        item.name = elem["name"];
        item.mainParam = elem["mainParam"];
        item.secondaryParam = elem["secondaryParam"];
        items.push_back(item);
    }

    return items;
}

int main() {
    srand(time(0));
    random_device rd;
    mt19937 gen(rd());

    // Шаг 1
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Невозможно открыть words.txt\n";
        return 1;
    }

    set<string> uniqueWords;
    string line;

    regex wordRegex("[A-Za-z]+");

    while (getline(file, line)) {
        sregex_iterator begin(line.begin(), line.end(), wordRegex);
        sregex_iterator end;

        for (auto it = begin; it != end; ++it) {
            uniqueWords.insert(it->str());
        }
    }

    cout << "Шаг 1. Уникальные слова:\n";
    for (const auto& w : uniqueWords) {
        cout << w << " ";
    }
    cout << "\n\n";

    file.clear();
    file.seekg(0);

    // Шаг 2
    map<char, int> freqMap;
    string word;
    regex validWord("^[A-Za-z]+$");

    while (file >> word) {
        if (regex_match(word, validWord)) {
            char first = tolower(word[0]);
            freqMap[first]++;
        }
        else {
            cout << "Некорректное слово пропущено: " << word << endl;
        }
    }
    file.close();

    cout << "Шаг 2. Словарь:\n";
    for (const auto& pair : freqMap) {
        cout << pair.first << " : " << pair.second << endl;
    }
    cout << endl;

    // Шаг 3
    list<Item> items;

    uniform_int_distribution<> wordDist(0, uniqueWords.size() - 1);
    uniform_int_distribution<> mapDist(0, freqMap.size() - 1);

    for (int i = 0; i < 100; ++i) {
        Item item;

        // случайное слово из множества
        auto wordIt = uniqueWords.begin();
        advance(wordIt, wordDist(gen));
        item.name = *wordIt;

        // 3 случайных элемента из словаря
        double product = 1;
        for (int j = 0; j < 3; ++j) {
            auto mapIt = freqMap.begin();
            advance(mapIt, mapDist(gen));
            product *= mapIt->second;
        }
        item.mainParam = product;

        // квадрат значения словаря по первой букве
        char first = tolower(item.name[0]);
        item.secondaryParam = pow(freqMap[first], 2);

        items.push_back(item);
    }

    cout << "Шаг 3. Сгенерированный список:\n";
    int count = 0;
    for (const auto& item : items) {
        cout << item << endl;
        count++;
        if (count == 10) break;
    }
    cout << endl;

    // Шаг 4
    items.sort([](const Item& a, const Item& b) {
        return a.name > b.name;
    });

    cout << "Шаг 4. Отсортированный список:\n";
    int count2 = 0;
    for (const auto& item : items) {
        cout << item << endl;
        count2++;
        if (count2 == 10) break;
    }
    cout << endl;

    // Шаг 5
    list<Item> filteredItems;

    copy_if(items.begin(), items.end(), back_inserter(filteredItems),
        [](const Item& item) {
            int diff = round(item.mainParam - item.secondaryParam);
            return diff % 2 == 0;
        });

    cout << "Шаг 5. Отфильтрованный список:\n";
    int count3 = 0;
    for (const auto& item : filteredItems) {
        cout << item << endl;
        count3++;
        if (count3 == 10) break;
    }
    cout << endl;

    // Шаг 6
    saveToJson(filteredItems, "result.json");
    cout << "Шаг 6. Список сохранён в result.json\n\n";

    // Шаг 7
    list<Item> loadedItems = loadFromJson("result.json");

    vector<Item> temp(loadedItems.begin(), loadedItems.end());
    shuffle(temp.begin(), temp.end(), gen);

    loadedItems.assign(temp.begin(), temp.end());

    cout << "Шаг 7:\n";
    for (const auto& item : loadedItems) {
        cout << item << endl;
    }

    return 0;
}