#include <iostream>
#include <limits>
using namespace std;

// Часть 1

// Объявление шаблона функции
template <typename T>
void replaceOddWithZero(T* arr, int size) {
    for (int i = 1; i < size; i += 2) {
        arr[i] = 0;
    }
}
// Функция тестирования 
void testFunction() {
    int size1, size2;
    
    while (true) {
        cout << "Введите размер массива int: ";
        if (cin >> size1 && size1 > 0 && size1 <= 999) {
            break;
        }
        cout << "Ошибка!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int* arr1 = new int[size1];

    cout << "Введите элементы массива int через пробел:\n";
    int count1 = 0;
    while (count1 < size1) {
        int current;
        if (cin >> current) {
            arr1[count1++] = current;
        } else {
            cout << "Ошибка!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            count1 = 0;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    while (true) {
        cout << "Введите размер массива float: ";
        if (cin >> size2 && size2 > 0 && size2 <= 999) {
            break;
        }
        cout << "Ошибка!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    float* arr2 = new float[size2];
    
    cout << "Введите элементы массива float через пробел:\n";
    int count2 = 0;
    while (count2 < size2) {
        float val;
        if (cin >> val) {
            arr2[count2++] = val;
        } else {
            cout << "Ошибка!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            count2 = 0;
        }
    }
    
    replaceOddWithZero(arr1, size1);
    replaceOddWithZero(arr2, size2);
    
    cout << "Массив int: ";
    for (int i = 0; i < size1; i++)
        cout << arr1[i] << " ";
    cout << endl;
    
    cout << "Массив float: ";
    for (int i = 0; i < size2; i++)
        cout << arr2[i] << " ";
    cout << endl;
    
    delete[] arr1;
    delete[] arr2;
}
// Часть 2

// Объявление шаблрна класса
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* topNode;

public:
    // по умолчанию
    Stack() : topNode(nullptr) {}

    // копирования
    Stack(const Stack& other) : topNode(nullptr) {
        if (!other.topNode) return;

        Node* temp = other.topNode;
        Node* prev = nullptr;

        while (temp) {
            Node* newNode = new Node{temp->data, nullptr};
            if (!topNode)
                topNode = newNode;
            else
                prev->next = newNode;

            prev = newNode;
            temp = temp->next;
        }
    }

    // перемещения
    Stack(Stack&& other) noexcept {
        topNode = other.topNode;
        other.topNode = nullptr;
    }

    // перезагрузка присваивания
    Stack& operator=(const Stack& other) {
        if (this == &other) return *this;

        clear();

        Node* temp = other.topNode;
        Node* prev = nullptr;

        while (temp) {
            Node* newNode = new Node{temp->data, nullptr};
            if (!topNode)
                topNode = newNode;
            else
                prev->next = newNode;

            prev = newNode;
            temp = temp->next;
        }

        return *this;
    }

    // присваивания с перемещением
    Stack& operator=(Stack&& other) noexcept {
        if (this == &other) return *this;

        clear();
        topNode = other.topNode;
        other.topNode = nullptr;

        return *this;
    }

    // деструктор
    ~Stack() {
        clear();
    }

    void push(T value) {
    while (true) {
        if (cin >> value) {
            Node* newNode = new Node{value, topNode};
            topNode = newNode;
            break;
        } else {
            cout << "Ошибка!";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

    void pop() {
        if (!topNode) {
            cout << "Стек пуст\n";
            return;
        }

        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    T top() const {
        if (!topNode) {
             cout << "Стек пуст\n";
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void clear() {
        while (!isEmpty()) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    void print() const {
        if (isEmpty()) {
            cout << "Стек пуст\n";
            return;
        }

        cout << "Содержимое стека: ";
        Node* temp = topNode;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


void testStack() {
    Stack<int> s;
    int choice, value;

    do {
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Посмотреть верхний элемент\n";
        cout << "4. Показать стек\n";
        cout << "0. Выход\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            s.push(value);
            cout << "Элемент добавлен" << endl;
            break;

        case 2:
            s.pop();
            cout << "Элемент удален" << endl;
            break;

        case 3:
            try {
                cout << "Верхний элемент: " << s.top() << endl;
            } catch (...) {
                cout << "Стек пуст\n";
            }
            break;

        case 4:
            s.print();
            break;

        case 0:
            cout << "Выход из программы\n";
            break;

        default:
            cout << "Неверный выбор\n";
        }

    } while (choice != 0);
}

int main() {
    testFunction();
    testStack();

    return 0;
}