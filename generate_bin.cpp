#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Константы (такие же, как в основной программе)
const int MAX_NAME = 50;
const int MAX_SYMBOL = 10;

// Структура элемента (точно такая же, как в основной программе)
struct Element {
    char name[MAX_NAME];
    char symbol[MAX_SYMBOL];
    
    union {
        struct { double mass; int charge; } phys;
        struct { char group[20]; int period; } chem;
    } data;
    
    bool isPhys;
};

int main() {
    // Создаём массив тестовых элементов
    Element elements[] = {
        // Физические элементы (с массой и зарядом)
        {"Водород", "H", {.phys = {1.008, 1}}, true},
        {"Гелий", "He", {.phys = {4.0026, 2}}, true},
        {"Литий", "Li", {.phys = {6.94, 3}}, true},
        {"Бериллий", "Be", {.phys = {9.012, 4}}, true},
        {"Бор", "B", {.phys = {10.81, 5}}, true},
        {"Углерод", "C", {.phys = {12.011, 6}}, true},
        {"Азот", "N", {.phys = {14.007, 7}}, true},
        {"Кислород", "O", {.phys = {15.999, 8}}, true},
        {"Фтор", "F", {.phys = {18.998, 9}}, true},
        {"Неон", "Ne", {.phys = {20.180, 10}}, true},
        {"Натрий", "Na", {.phys = {22.990, 11}}, true},
        {"Магний", "Mg", {.phys = {24.305, 12}}, true},
        {"Алюминий", "Al", {.phys = {26.982, 13}}, true},
        {"Кремний", "Si", {.phys = {28.086, 14}}, true},
        {"Фосфор", "P", {.phys = {30.974, 15}}, true},
        {"Сера", "S", {.phys = {32.06, 16}}, true},
        {"Хлор", "Cl", {.phys = {35.45, 17}}, true},
        {"Аргон", "Ar", {.phys = {39.948, 18}}, true},
        {"Калий", "K", {.phys = {39.098, 19}}, true},
        {"Кальций", "Ca", {.phys = {40.078, 20}}, true},
        
        // Химические элементы (с группой и периодом)
        {"Железо", "Fe", {.chem = {"Переход", 4}}, false},
        {"Медь", "Cu", {.chem = {"Переход", 4}}, false},
        {"Цинк", "Zn", {.chem = {"Переход", 4}}, false},
        {"Серебро", "Ag", {.chem = {"Переход", 5}}, false},
        {"Золото", "Au", {.chem = {"Переход", 6}}, false},
        {"Ртуть", "Hg", {.chem = {"Переход", 6}}, false},
        {"Уран", "U", {.chem = {"Актиноид", 7}}, false},
        
        // Дополнительные элементы для тестирования поиска по букве
        {"Цезий", "Cs", {.phys = {132.905, 55}}, true},
        {"Церий", "Ce", {.phys = {140.116, 58}}, true},
        {"Цинк", "Zn", {.phys = {65.38, 30}}, true},  // Дубликат для проверки
    };
    
    int count = sizeof(elements) / sizeof(elements[0]);
    
    // Запрашиваем имя файла
    char filename[100];
    cout << "Введите имя файла для сохранения: ";
    cin.getline(filename, 100);
    
    // Открываем файл для бинарной записи
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Ошибка создания файла!" << endl;
        return 1;
    }
    
    // Записываем все элементы
    file.write((char*)elements, sizeof(elements));
    
    file.close();
    
    cout << "Успешно создан файл '" << filename << "'\n";
    cout << "Записано элементов: " << count << "\n";
    cout << "Размер файла: " << sizeof(elements) << " байт\n\n";
    
    // Выводим содержимое для проверки
    cout << "Содержимое файла:\n";
    cout << "========================================\n";
    
    for (int i = 0; i < count; i++) {
        cout << i+1 << ". " << elements[i].name;
        cout << " (" << elements[i].symbol << ") - ";
        
        if (elements[i].isPhys) {
            cout << "Физ: масса=" << elements[i].data.phys.mass;
            cout << ", заряд=" << elements[i].data.phys.charge;
        } else {
            cout << "Хим: группа=" << elements[i].data.chem.group;
            cout << ", период=" << elements[i].data.chem.period;
        }
        cout << endl;
    }
    
    return 0;
}