#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

// Константы
const int MAX_NAME = 50;
const int MAX_SYMBOL = 10;
const int PAGE_SIZE = 3;


// Структра элемента с union (вариативная часть)
struct Element {
    char name[MAX_NAME];
    char symbol[MAX_SYMBOL];
    
    union {
        struct { double mass; int charge; } phys;   // физические характеристики
        struct { char group[20]; int period; } chem; // химические характеристики
    } data;
    
    bool isPhys;  // true - физ, false - хим
};

// Структура узла двусвязного списка
struct Node {
    Element* elem;   // указатель на данные
    Node* prev;      // указатель на предыдущий узел
    Node* next;      // указатель на следующий узел
    
    Node(Element* e) : elem(e), prev(nullptr), next(nullptr) {}
};


class List {
private:
    Node* head;  // начало списка
    Node* tail;  // конец списка
    int count;   // количество элементов
    
public:
    List() : head(nullptr), tail(nullptr), count(0) {}
    
    // деструктор: освобождает память
    ~List() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->elem;
            delete temp;
        }
    }
    
    // Метод для добавления в конец
    void addToEnd(Element* elem) {
        Node* newNode = new Node(elem);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }
    
    // Вставка в упорядоченный список (функция сравнения передаётся параметром)
    void insertOrdered(Element* elem, bool (*cmp)(Element*, Element*)) {
        Node* newNode = new Node(elem);
        
        if (!head) {
            head = tail = newNode;
            count++;
            return;
        }
        
        Node* curr = head;
        while (curr && cmp(curr->elem, elem))  // поиск места вставки
            curr = curr->next;
        
        if (curr == head) {        // вставка в начало
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else if (!curr) {        // вставка в конец
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {                   // вставка в середину
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }
        count++;
    }
    
    // Удаление элементов по условию (функция-предикат передаётся)
    bool removeIf(bool (*match)(Element*)) {
        bool removed = false;
        Node* curr = head;
        
        while (curr) {
            Node* next = curr->next;
            if (match(curr->elem)) {   // если подходит под условие
                // перевязываем соседей
                if (curr->prev) curr->prev->next = curr->next;
                if (curr->next) curr->next->prev = curr->prev;
                if (curr == head) head = curr->next;
                if (curr == tail) tail = curr->prev;
                
                delete curr->elem;
                delete curr;
                count--;
                removed = true;
            }
            curr = next;
        }
        return removed;
    }
    
    // Прямой обход (от головы к хвосту)
    void printForward(void (*print)(Element*)) {
        cout << "\n>>> Прямой обход (" << count << " шт.)\n";
        Node* curr = head;
        int i = 1;
        while (curr) {
            cout << i++ << ". ";
            print(curr->elem);
            curr = curr->next;
        }
    }
    
    // Обратный обход (от хвоста к голове)
    void printBackward(void (*print)(Element*)) {
        cout << "\n>>> Обратный обход (" << count << " шт.)\n";
        Node* curr = tail;
        int i = count;
        while (curr) {
            cout << i-- << ". ";
            print(curr->elem);
            curr = curr->prev;
        }
    }
    
    // Вспомогательный список для вывода упорядочных списков
    class PtrList {
    public:
        struct PNode {
            Element* elem;   // указатель на элемент (без владения)
            PNode* next;
            PNode(Element* e) : elem(e), next(nullptr) {}
        };
        PNode* head;
        PNode* tail;
        
        PtrList() : head(nullptr), tail(nullptr) {}
        
        ~PtrList() {
            while (head) {
                PNode* temp = head;
                head = head->next;
                delete temp;
            }
        }
        
        void add(Element* e) {
            PNode* n = new PNode(e);
            if (!head) head = tail = n;
            else {
                tail->next = n;
                tail = n;
            }
        }
        
        // сортировка пузырьком с переданной функцией сравнения
        void sort(bool (*cmp)(Element*, Element*)) {
            for (PNode* i = head; i; i = i->next)
                for (PNode* j = i->next; j; j = j->next)
                    if (!cmp(i->elem, j->elem))
                        swap(i->elem, j->elem);
        }
        
        void print(void (*printElem)(Element*)) {
            PNode* curr = head;
            int i = 1;
            while (curr) {
                cout << i++ << ". ";
                printElem(curr->elem);
                curr = curr->next;
            }
        }
    };
    
    // создание вспомогательного списка указателей
    PtrList* makePtrList() {
        PtrList* pl = new PtrList();
        for (Node* curr = head; curr; curr = curr->next)
            pl->add(curr->elem);
        return pl;
    }
    
    Node* getHead() { return head; }
    int getCount() { return count; }
};

// Функция вывода элемента на экран
void printElement(Element* e) {
    cout << "  " << left;
    cout << setw(15) << e->name << " ";
    cout << setw(5) << e->symbol << " ";
    
    if (e->isPhys)
        cout << "Масса=" << e->data.phys.mass << " Заряд атома=" << e->data.phys.charge;
    else
        cout << "Группа=" << e->data.chem.group << " Период=" << e->data.chem.period;
    
    cout << endl;
}

// вывод разделительной линии
void printLine() {
    cout << "  -----------------------------------------\n";
}

// функции сравнения для сортировки
bool cmpName(Element* a, Element* b) { return strcmp(a->name, b->name) < 0; }
bool cmpSymbol(Element* a, Element* b) { return strcmp(a->symbol, b->symbol) < 0; }
bool cmpMass(Element* a, Element* b) { 
    return a->isPhys && b->isPhys ? a->data.phys.mass < b->data.phys.mass : false; 
}

// для передачи статического символа в функцию-предикат
struct MatchData {
    static char symbol[MAX_SYMBOL];
    static bool matchBySymbol(Element* e) {
        return strcmp(e->symbol, symbol) == 0;
    }
};
char MatchData::symbol[MAX_SYMBOL] = "";


class DB {
private:
    List list;       // список элементов
    char fname[100]; // имя файла
    
public:
    DB(const char* name) {
        strcpy(fname, name);
        load();   // загрузка при создании
    }
    
    ~DB() { save(); }  // сохранение при разрушении
    
    // загрузка из бинарного файла
    void load() {
        ifstream f(fname, ios::binary);
        if (!f) { cout << "> Новый файл\n"; return; }
        
        Element tmp;
        while (f.read((char*)&tmp, sizeof(Element))) {
            Element* e = new Element;
            memcpy(e, &tmp, sizeof(Element));
            list.addToEnd(e);
        }
        f.close();
        cout << "> Загружено: " << list.getCount() << "\n";
    }
    
    // сохранение в бинарный файл
    void save() {
        ofstream f(fname, ios::binary | ios::trunc);
        if (!f) { cout << "! Ошибка сохранения\n"; return; }
        
        for (Node* curr = list.getHead(); curr; curr = curr->next)
            f.write((char*)curr->elem, sizeof(Element));
        f.close();
    }
    
    // добавление нового элемента
    void add() {
        Element* e = new Element;
        cout << "Название: "; cin.ignore(); cin.getline(e->name, MAX_NAME);
        cout << "Символ: "; cin.getline(e->symbol, MAX_SYMBOL);
        cout << "Тип (1-физ/0-хим): "; cin >> e->isPhys;
        
        if (e->isPhys) {
            cout << "Масса: "; cin >> e->data.phys.mass;
            cout << "Заряд: "; cin >> e->data.phys.charge;
        } else {
            cout << "Группа: "; cin.ignore(); cin.getline(e->data.chem.group, 20);
            cout << "Период: "; cin >> e->data.chem.period;
        }
        list.addToEnd(e);
        cout << "> OK\n";
    }
    
    // удаление по символу
    void remove() {
        char sym[MAX_SYMBOL];
        cout << "Символ для удаления: "; cin >> sym;
        strcpy(MatchData::symbol, sym);
        
        if (list.removeIf(MatchData::matchBySymbol))
            cout << "> Удалено\n";
        else
            cout << "> Не найдено\n";
    }
    
    // поиск по символу (индивидуальное задание)
    void search() {
        char sym[MAX_SYMBOL];
        cout << "Символ для поиска: "; cin >> sym;
        
        cout << "\nРезультат:\n";
        printLine();
        Node* curr = list.getHead();
        bool found = false;
        while (curr) {
            if (strcmp(curr->elem->symbol, sym) == 0) {
                printElement(curr->elem);
                found = true;
            }
            curr = curr->next;
        }
        if (!found) cout << "  Ничего не найдено\n";
        printLine();
    }
    
    // максимальная масса по первой букве (индивидуальное задание)
    void maxMass() {
        char letter;
        cout << "Первая буква: "; cin >> letter;
        
        Element* maxElem = nullptr;
        Node* curr = list.getHead();
        
        while (curr) {
            if (curr->elem->name[0] == letter && curr->elem->isPhys) {
                if (!maxElem || curr->elem->data.phys.mass > maxElem->data.phys.mass)
                    maxElem = curr->elem;
            }
            curr = curr->next;
        }
        
        if (maxElem) {
            cout << "\nМАКС. МАССА:\n";
            printLine();
            printElement(maxElem);
        } else
            cout << "> Не найдено\n";
        printLine();
    }
    
    // постраничный вывод с листанием
    void pageView() {
        if (list.getCount() == 0) { cout << "> Список пуст\n"; return; }
        
        int total = (list.getCount() + PAGE_SIZE - 1) / PAGE_SIZE;
        int page = 1;
        char c;
        
        do {
            Node* start = list.getHead();
            for (int i = 0; i < (page-1)*PAGE_SIZE && start; i++)
                start = start->next;
            
            cout << "\n Страница " << page << "/" << total << "\n";
            printLine();
            
            Node* curr = start;
            for (int i = 0; i < PAGE_SIZE && curr; i++) {
                printElement(curr->elem);
                curr = curr->next;
            }
            
            printLine();
            cout << "[n] следующая [p] предыдущая [q] выход: ";
            cin >> c;
            
            if (c == 'n' && page < total) page++;
            else if (c == 'p' && page > 1) page--;
        } while (c != 'q');
    }
    
    // вывод отсортированного списка (через вспомогательный список)
    void sortView() {
        if (list.getCount() == 0) { cout << "> Список пуст\n"; return; }

        int ch;
        cout << "\nСОРТИРОВКА:\n";
        cout << "  1 - по названию\n";
        cout << "  2 - по символу\n";
        cout << "  3 - по массе\n";
        cout << "Выбор: ";
        cin >> ch;
        
        List::PtrList* pl = list.makePtrList();  // создаём вспомогательный список
        
        switch(ch) {
            case 1: pl->sort(cmpName); cout << "\nПО НАЗВАНИЮ:\n"; break;
            case 2: pl->sort(cmpSymbol); cout << "\nПО СИМВОЛУ:\n"; break;
            case 3: pl->sort(cmpMass); cout << "\nПО МАССЕ:\n"; break;
            default: pl->sort(cmpName); cout << "\nПО НАЗВАНИЮ:\n";
        }
        
        printLine();
        pl->print(printElement);
        delete pl;  // удаляем вспомогательный список (данные не теряются)
    }
    
    void showForward() { list.printForward(printElement); }
    void showBackward() { list.printBackward(printElement); }
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    
    char name[100];
    if (argc > 1)                     // имя файла из параметров командной строки
        strcpy(name, argv[1]);
    else {                            // или запрашиваем с клавиатуры
        cout << "Имя файла: ";
        cin.getline(name, 100);
    }
    
    DB db(name);   // создание БД (автозагрузка)
    int cmd;
    
    // главное меню
    do {
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        cout << " 1 - добавить\n";
        cout << " 2 - удалить\n";
        cout << " 3 - поиск по символу\n";
        cout << " 4 - макс. масса по букве\n";
        cout << " 5 - постранично\n";
        cout << " 6 - сортировка\n";
        cout << " 7 - прямой обход\n";
        cout << " 8 - обратный обход\n";
        cout << " 0 - выход\n";
        cout << "Выбор: ";
        cin >> cmd;
        
        switch(cmd) {
            case 1: db.add(); break;
            case 2: db.remove(); break;
            case 3: db.search(); break;
            case 4: db.maxMass(); break;
            case 5: db.pageView(); break;
            case 6: db.sortView(); break;
            case 7: db.showForward(); break;
            case 8: db.showBackward(); break;
            case 0: cout << "Выход\n"; break;
            default: cout << "? Неверный выбор\n";
        }
    } while (cmd != 0);
    
    return 0;
}