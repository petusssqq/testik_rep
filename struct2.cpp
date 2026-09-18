#include <iostream>
#include <fstream>

using namespace std;

// Структуры
struct Node {
    int vertex;
    Node* next;
};

// Глобальные переменные
int n;

// матрица
int** matrixGraph = NULL;

// списки
Node** listGraph = NULL;

// Реализация матрицы
void readMatrix(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    file >> n;

    matrixGraph = new int*[n];
    for (int i = 0; i < n; i++) {
        matrixGraph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            file >> matrixGraph[i][j];
        }
    }
}

// Реализация списка
void addEdge(int u, int v) {
    Node* node = new Node;
    node->vertex = v;
    node->next = listGraph[u];
    listGraph[u] = node;
}

void readList(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    file >> n;

    listGraph = new Node*[n];
    for (int i = 0; i < n; i++)
        listGraph[i] = NULL;

    int u, v;
    char colon;

    for (int i = 0; i < n; i++) {
        file >> u >> colon;

        while (file.peek() != '\n' && file >> v) {
            addEdge(u, v);
        }
    }
}

// Функция для компактного вывода итоговых расстояний
void printCompactResult(int start, int* dist) {
    cout << "Вершина [" << start << "] -> расстояния до остальных: { ";
    for (int i = 0; i < n; i++) {
        cout << i << ":" << dist[i] << " ";
    }
    cout << "}\n";
}

// BFS (матрица)
bool bfsMatrix(int start) {
    int* dist = new int[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        visited[i] = false;
    }

    int* stack = new int[n];
    int head = 0, tail = 0;

    stack[tail++] = start;
    visited[start] = true;
    dist[start] = 0;

    while (head < tail) {
        int v = stack[head++];

        for (int i = 0; i < n; i++) {
            if (matrixGraph[v][i] && !visited[i]) {
                visited[i] = true;
                dist[i] = dist[v] + 1;

                if (dist[i] > 6) {
                    delete[] dist; delete[] visited; delete[] stack;
                    return false;
                }

                stack[tail++] = i;
            }
        }
    }

    // Выводим полученные расстояния на экран
    printCompactResult(start, dist);

    // Проверяем, остались ли недостижимые вершины (-1)
    bool isConnected = true;
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            isConnected = false;
            break;
        }
    }

    delete[] dist;
    delete[] visited;
    delete[] stack;
    return isConnected; // Возвращаем false, если граф не связан
}

// BFS (списки)
bool bfsList(int start) {
    int* dist = new int[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        visited[i] = false;
    }

    int* stack = new int[n];
    int head = 0, tail = 0;

    stack[tail++] = start;
    visited[start] = true;
    dist[start] = 0;

    while (head < tail) {
        int v = stack[head++];

        Node* temp = listGraph[v];
        while (temp) {
            int u = temp->vertex;

            if (!visited[u]) {
                visited[u] = true;
                dist[u] = dist[v] + 1;

                if (dist[u] > 6) {
                    delete[] dist; delete[] visited; delete[] stack;
                    return false;
                }

                stack[tail++] = u;
            }

            temp = temp->next;
        }
    }

    // Выводим полученные расстояния на экран
    printCompactResult(start, dist);

    // Проверяем, остались ли недостижимые вершины (-1)
    bool isConnected = true;
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            isConnected = false;
            break;
        }
    }

    delete[] dist;
    delete[] visited;
    delete[] stack;
    return isConnected; // Возвращаем false, если граф не связан
}

// Проверки
bool checkMatrix() {
    cout << "\n--- Запуск проверки для каждой вершины (Матрица) ---\n";
    bool totalResult = true;
    for (int i = 0; i < n; i++) {
        // Запускаем BFS для каждой вершины без прерывания цикла
        if (!bfsMatrix(i)) {
            totalResult = false; 
        }
    }
    return totalResult;
}

bool checkList() {
    cout << "\n--- Запуск проверки для каждой вершины (Списки) ---\n";
    bool totalResult = true;
    for (int i = 0; i < n; i++) {
        // Запускаем BFS для каждой вершины без прерывания цикла
        if (!bfsList(i)) {
            totalResult = false;
        }
    }
    return totalResult;
}


int main() {
    int mode;
    char filename[100];

    cout << "Выберите режим:\n";
    cout << "1 - Матрица смежности\n";
    cout << "2 - Списки смежности\n";
    cin >> mode;

    cout << "Введите имя файла: ";
    cin >> filename;

    if (mode == 1) {
        readMatrix(filename);
        if (matrixGraph == NULL) return 1;

        if (checkMatrix())
            cout << "\nТеория выполняется\n";
        else
            cout << "\nТеория НЕ выполняется\n";
    }
    else if (mode == 2) {
        readList(filename);
        if (listGraph == NULL) return 1;

        if (checkList())
            cout << "\nТеория выполняется\n";
        else
            cout << "\nТеория НЕ выполняется\n";
    }
    else {
        cout << "Неверный режим\n";
    }

    return 0;
}
