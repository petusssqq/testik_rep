#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Красно-черное дерево

enum Color
{
    RED,
    BLACK
};

struct RBNode
{
    long long key;
    Color color;

    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(long long k)
    {
        key = k;
        color = RED;

        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RBTree
{
private:
    RBNode* root;
    int nodeCount;

    void leftRotate(RBNode* x)
    {
        RBNode* y = x->right;

        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode* y)
    {
        RBNode* x = y->left;

        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    void fixInsert(RBNode* z)
    {
        while (z != root &&
               z->parent != nullptr &&
               z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBNode* y =
                    z->parent->parent->right;

                if (y != nullptr &&
                    y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;

                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;

                    rightRotate(
                        z->parent->parent);
                }
            }
            else
            {
                RBNode* y =
                    z->parent->parent->left;

                if (y != nullptr &&
                    y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;

                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;

                    leftRotate(
                        z->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

public:
    RBTree()
    {
        root = nullptr;
        nodeCount = 0;
    }

    void insert(long long key)
    {
        RBNode* z = new RBNode(key);

        RBNode* y = nullptr;
        RBNode* x = root;

        while (x != nullptr)
        {
            y = x;

            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == nullptr)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        fixInsert(z);

        nodeCount++;
    }

    bool search(long long key,
                int& comparisons)
    {
        RBNode* current = root;

        while (current != nullptr)
        {
            comparisons++;

            if (key == current->key)
                return true;

            comparisons++;

            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }

    long long getMemoryUsage()
    {
        return (long long)nodeCount *
               sizeof(RBNode);
    }
};

// Декартово дерево

struct TreapNode
{
    long long key;
    int priority;

    TreapNode* left;
    TreapNode* right;

    TreapNode(long long k)
    {
        key = k;
        priority = rand();

        left = nullptr;
        right = nullptr;
    }
};

class Treap
{
private:
    TreapNode* root;
    int nodeCount;

    void split(TreapNode* current,
               long long key,
               TreapNode*& left,
               TreapNode*& right)
    {
        if (current == nullptr)
        {
            left = nullptr;
            right = nullptr;
        }
        else if (key < current->key)
        {
            split(current->left,
                  key,
                  left,
                  current->left);

            right = current;
        }
        else
        {
            split(current->right,
                  key,
                  current->right,
                  right);

            left = current;
        }
    }

    TreapNode* insertNode(TreapNode* current,
                          TreapNode* node)
    {
        if (current == nullptr)
            return node;

        if (node->priority >
            current->priority)
        {
            split(current,
                  node->key,
                  node->left,
                  node->right);

            return node;
        }

        if (node->key < current->key)
        {
            current->left =
                insertNode(current->left,
                           node);
        }
        else
        {
            current->right =
                insertNode(current->right,
                           node);
        }

        return current;
    }

public:
    Treap()
    {
        root = nullptr;
        nodeCount = 0;
    }

    void insert(long long key)
    {
        TreapNode* node =
            new TreapNode(key);

        root = insertNode(root, node);

        nodeCount++;
    }

    bool search(long long key,
                int& comparisons)
    {
        TreapNode* current = root;

        while (current != nullptr)
        {
            comparisons++;

            if (key == current->key)
                return true;

            comparisons++;

            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }

    long long getMemoryUsage()
    {
        return (long long)nodeCount *
               sizeof(TreapNode);
    }
};

// Главная функция

int main()
{
    srand(time(0));

    RBTree rbTree;
    Treap treap;

    ifstream file("test_numbers.txt");

    if (!file)
    {
        cout << "Ошибка открытия файла!"
             << endl;

        return 1;
    }

    // Существующие ключи
    long long existingKeys[50];
    int existingCount = 0;

    long long value;

    // Загрузка данных
    while (file >> value)
    {
        rbTree.insert(value);
        treap.insert(value);

        // Сохраняем только 50 ключей
        if (existingCount < 50)
        {
            existingKeys[existingCount] =
                value;

            existingCount++;
        }
    }

    file.close();

    // Тестовые ключи

    long long testKeys[100];

    // 50 существующих ключей
    for (int i = 0; i < 50; i++)
    {
        testKeys[i] = existingKeys[i];
    }

    // 20 ключей меньше 140
    for (int i = 50; i < 70; i++)
    {
        testKeys[i] = rand() % 140;
    }

    // 15 ключей больше 100000000
    for (int i = 70; i < 85; i++)
    {
        testKeys[i] =
            100000001 + rand() % 1000000;
    }

    // 15 ключей из диапазона
    for (int i = 85; i < 100; i++)
    {
        testKeys[i] =
            140 + rand() % 99999860;
    }

    // КЧ-дерево 
    cout << "Красно-черное дерево"
         << endl;
    cout << "================================="
         << endl;

    int totalRBComparisons = 0;

    for (int i = 0; i < 100; i++)
    {
        int comparisons = 0;

        bool found =
            rbTree.search(testKeys[i],
                          comparisons);

        cout << "Ключ: "
             << testKeys[i];

        if (found)
            cout << " найден";
        else
            cout << " не найден";

        cout << " | Сравнений: "
             << comparisons
             << endl;

        totalRBComparisons += comparisons;
    }

    // Декартово дерево 
    cout << "Декартово дерево"
         << endl;
    cout << "================================="
         << endl;

    int totalTreapComparisons = 0;

    for (int i = 0; i < 100; i++)
    {
        int comparisons = 0;

        bool found =
            treap.search(testKeys[i],
                         comparisons);

        cout << "Ключ: "
             << testKeys[i];

        if (found)
            cout << " найден";
        else
            cout << " не найден";

        cout << " | Сравнений: "
             << comparisons
             << endl;

        totalTreapComparisons += comparisons;
    }

    // Итоги

    cout << endl;
    cout << "Итоговые результаты"
         << endl;
    cout << "================================="
         << endl;

    cout << "Среднее число сравнений "
         << "(КЧ-дерево): "
         << (double)totalRBComparisons / 100
         << endl;

    cout << "Среднее число сравнений "
         << "(Декартово дерево): "
         << (double)totalTreapComparisons / 100
         << endl;

    cout << endl;

    cout << "Память КЧ-дерева: "
         << rbTree.getMemoryUsage()
         << " байт"
         << endl;

    cout << "Память декартового дерева: "
         << treap.getMemoryUsage()
         << " байт"
         << endl;

    return 0;
}