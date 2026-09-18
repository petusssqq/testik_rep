#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Metrics {

    long long assignments = 0;
    long long extraOperations = 0;
    long long memory = 0;

    double time = 0;
};

Metrics metrics;

// Сброс

void resetMetrics() {

    metrics.assignments = 0;
    metrics.extraOperations = 0;
    metrics.memory = 0;
    metrics.time = 0;
}

// Обмен

void swapCount(int& a, int& b) {

    int temp = a;
    metrics.assignments++;

    a = b;
    metrics.assignments++;

    b = temp;
    metrics.assignments++;
}

// Сортировка расческой

void combSort(vector<int>& arr) {

    int n = arr.size();

    double factor = 1.247;

    int gap = n;

    bool swapped = true;

    while (gap > 1 || swapped) {

        gap = int(gap / factor);

        metrics.extraOperations++;

        if (gap < 1) {

            gap = 1;

            metrics.extraOperations++;
        }

        swapped = false;

        for (int i = 0; i + gap < n; i++) {

            metrics.extraOperations += 2;

            if (arr[i] < arr[i + gap]) {

                swapCount(arr[i], arr[i + gap]);

                swapped = true;

                metrics.extraOperations++;
            }
        }
    }
}

// Сортировка вставками

void insertionSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 1; i < n; i++) {

        metrics.extraOperations += 2;

        int key = arr[i];

        metrics.assignments++;

        int j = i - 1;

        while (j >= 0 && arr[j] < key) {

            arr[j + 1] = arr[j];

            metrics.assignments++;

            j--;

            metrics.extraOperations++;
        }

        arr[j + 1] = key;

        metrics.assignments++;
    }
}

// Heapify

void heapify(vector<int>& arr, int n, int i) {

    int largest = i;

    int left = 2 * i + 1;

    int right = 2 * i + 2;

    metrics.extraOperations += 3;

    if (left < n && arr[left] < arr[largest]) {

        largest = left;

        metrics.extraOperations++;
    }

    if (right < n && arr[right] < arr[largest]) {

        largest = right;

        metrics.extraOperations++;
    }

    if (largest != i) {

        swapCount(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

// Пирамидальная сортировка

void heapSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {

        metrics.extraOperations += 2;

        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {

        metrics.extraOperations += 2;

        swapCount(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

// TimSort

const int RUN = 32;

// Вставки для TimSort

void insertionSortTim(
    vector<int>& arr,
    int left,
    int right
) {

    for (int i = left + 1; i <= right; i++) {

        metrics.extraOperations += 2;

        int temp = arr[i];

        metrics.assignments++;

        int j = i - 1;

        while (j >= left && arr[j] < temp) {

            arr[j + 1] = arr[j];

            metrics.assignments++;

            j--;

            metrics.extraOperations++;
        }

        arr[j + 1] = temp;

        metrics.assignments++;
    }
}

// Merge

void merge(
    vector<int>& arr,
    int l,
    int m,
    int r
) {

    int len1 = m - l + 1;

    int len2 = r - m;

    vector<int> left(len1);

    vector<int> right(len2);

    metrics.memory +=
        (len1 + len2) * sizeof(int);

    for (int i = 0; i < len1; i++) {

        left[i] = arr[l + i];

        metrics.assignments++;
    }

    for (int i = 0; i < len2; i++) {

        right[i] = arr[m + 1 + i];

        metrics.assignments++;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {

        if (left[i] >= right[j]) {

            arr[k++] = left[i++];
        }
        else {

            arr[k++] = right[j++];
        }

        metrics.assignments++;

        metrics.extraOperations += 3;
    }

    while (i < len1) {

        arr[k++] = left[i++];

        metrics.assignments++;

        metrics.extraOperations += 2;
    }

    while (j < len2) {

        arr[k++] = right[j++];

        metrics.assignments++;

        metrics.extraOperations += 2;
    }
}

// TimSort

void timSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i += RUN) {

        insertionSortTim(
            arr,
            i,
            min(i + RUN - 1, n - 1)
        );

        metrics.extraOperations++;
    }

    for (int size = RUN; size < n; size *= 2) {

        for (int left = 0; left < n; left += 2 * size) {

            int mid =
                min(left + size - 1, n - 1);

            int right =
                min(left + 2 * size - 1, n - 1);

            metrics.extraOperations += 2;

            if (mid < right) {

                merge(arr, left, mid, right);
            }
        }
    }
}

// Чтение файла

vector<int> readNumbers(
    string filename,
    int N
) {

    vector<int> arr;

    ifstream file(filename);

    int x;

    while (file >> x && arr.size() < N) {

        arr.push_back(x);
    }

    return arr;
}

// Тест

void testSort(
    void (*sortFunc)(vector<int>&),
    vector<int> arr,
    string sortName,
    string type
) {

    resetMetrics();

    auto start =
        high_resolution_clock::now();

    sortFunc(arr);

    auto stop =
        high_resolution_clock::now();

    metrics.time =
        duration<double, milli>(
            stop - start
        ).count();

    cout << "\n====================================\n";

    cout << "Метод: "
         << sortName << endl;

    cout << "Тип массива: "
         << type << endl;

    cout << "Размер: "
         << arr.size() << endl;

    cout << "Присваивания: "
         << metrics.assignments << endl;

    cout << "Вспомогательные операции: "
         << metrics.extraOperations << endl;

    cout << "Дополнительная память: "
         << metrics.memory
         << " байт" << endl;

    cout << "Время: "
         << metrics.time
         << " мс" << endl;
}

// Все тесты

void runAllTests(
    vector<int> original,
    string label
) {

    vector<int> randomArr = original;

    vector<int> sortedArr = original;

    sort(
        sortedArr.begin(),
        sortedArr.end(),
        greater<int>()
    );

    vector<int> reverseArr = sortedArr;

    reverse(
        reverseArr.begin(),
        reverseArr.end()
    );

    cout << label << endl;

    // Расческой

    testSort(
        combSort,
        randomArr,
        "Сортировка расческой",
        "Неупорядоченный"
    );

    testSort(
        combSort,
        sortedArr,
        "Сортировка расческой",
        "Упорядоченный"
    );

    testSort(
        combSort,
        reverseArr,
        "Сортировка расческой",
        "Обратный порядок"
    );

    // Вставками

    testSort(
        insertionSort,
        randomArr,
        "Сортировка простыми вставками",
        "Неупорядоченный"
    );

    testSort(
        insertionSort,
        sortedArr,
        "Сортировка простыми вставками",
        "Упорядоченный"
    );

    testSort(
        insertionSort,
        reverseArr,
        "Сортировка простыми вставками",
        "Обратный порядок"
    );

    // Пирамидальная

    testSort(
        heapSort,
        randomArr,
        "Пирамидальная сортировка",
        "Неупорядоченный"
    );

    testSort(
        heapSort,
        sortedArr,
        "Пирамидальная сортировка",
        "Упорядоченный"
    );

    testSort(
        heapSort,
        reverseArr,
        "Пирамидальная сортировка",
        "Обратный порядок"
    );

    // TimSort

    testSort(
        timSort,
        randomArr,
        "TimSort",
        "Неупорядоченный"
    );

    testSort(
        timSort,
        sortedArr,
        "TimSort",
        "Упорядоченный"
    );

    testSort(
        timSort,
        reverseArr,
        "TimSort",
        "Обратный порядок"
    );
}

// Main

int main() {

    setlocale(LC_ALL, "Russian");

    vector<int> sizes = {
        60000,
        120000,
        180000,
        280000
    };

    // Основная часть

    for (int N : sizes) {

        vector<int> data =
            readNumbers(
                "test_numbers.txt",
                N
            );

        runAllTests(
            data,
            "ОСНОВНОЙ ФАЙЛ N = "
            + to_string(N)
        );
    }

    // Только N4 = 280000

    int N4 = 280000;

    // x10

    vector<int> repeat10 =
        readNumbers(
            "repeats10.txt",
            N4
        );

    runAllTests(
        repeat10,
        "ПОВТОРЫ x10 N = 280000"
    );

    // x100

    vector<int> repeat100 =
        readNumbers(
            "repeats100.txt",
            N4
        );

    runAllTests(
        repeat100,
        "ПОВТОРЫ x100 N = 280000"
    );

    // x500

    vector<int> repeat500 =
        readNumbers(
            "repeats500.txt",
            N4
        );

    runAllTests(
        repeat500,
        "ПОВТОРЫ x500 N = 280000"
    );

    // x1000

    vector<int> repeat1000 =
        readNumbers(
            "repeats1000.txt",
            N4
        );

    runAllTests(
        repeat1000,
        "ПОВТОРЫ x1000 N = 280000"
    );

    return 0;
}