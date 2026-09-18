#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>

using namespace std;

class Cat {
protected:
    double weight;
    string gender;
    int age;
    string name;

public:
    Cat() {
        weight = 0;
        gender = "неизвестно";
        age = 0;
        name = "неизвестно";
    }

    Cat(double w, const string& g, int a, const string& n) {
        weight = w;
        gender = g;
        age = a;
        name = n;
    }

    Cat(const Cat& other) {
        weight = other.weight;
        gender = other.gender;
        age = other.age;
        name = other.name;
    }

    virtual ~Cat() {}

    virtual void play() = 0;
    virtual void feed() = 0;
    virtual void pet() = 0;
    virtual void printClassName() const = 0;

    virtual string toString() const {
        stringstream ss;
        ss << "Тип: Cat, Имя: " << name << ", Пол: " << gender
           << ", Возраст: " << age << ", Вес: " << fixed << setprecision(2) << weight << " кг";
        return ss.str();
    }

};


class ScottishFold : public Cat {
private:
    bool foldedEars;

public:
    ScottishFold() {
        weight = 0;
        gender = "неизвестно";
        age = 0;
        name = "неизвестно";
        foldedEars = true;
    }

    ScottishFold(double w, const string& g, int a, const string& n, bool folded) {
        weight = w;
        gender = g;
        age = a;
        name = n;
        foldedEars = folded;
    }

    ScottishFold(const ScottishFold& other) {
        weight = other.weight;
        gender = other.gender;
        age = other.age;
        name = other.name;
        foldedEars = other.foldedEars;
    }

    ~ScottishFold() override {}

    void play() override {
        cout << name << " играет с мячиком." << endl;
    }

    void feed() override {
        cout << name << " ест специальный корм для шотландских вислоухих кошек." << endl;
    }

    void pet() override {
        cout << "Вы гладите " << name << ", она мурлычет и ещё сильнее загибает ушки." << endl;
    }

    void printClassName() const override {
        cout << "ScottishFold" << endl;
    }

    string toString() const override {
        stringstream ss;
        ss << "Тип: ScottishFold, Имя: " << name << ", Пол: " << gender
           << ", Возраст: " << age << ", Вес: " << fixed << setprecision(2) << weight << " кг"
           << ", Ушки загнуты: " << (foldedEars ? "да" : "нет");
        return ss.str();
    }

    // Уникальный метод
    void foldEars() {
        if (foldedEars) {
            cout << name << " уже имеет загнутые ушки." << endl;
        } else {
            foldedEars = true;
            cout << name << " теперь имеет загнутые ушки!" << endl;
        }
    }

    void setFoldedEars(bool f) { foldedEars = f; }
    bool getFoldedEars() const { return foldedEars; }
};

class MaineCoon : public Cat {
private:
    double furLength;

public:
    MaineCoon() {
        weight = 0;
        gender = "неизвестно";
        age = 0;
        name = "неизвестно";
        furLength = 5.0;
    }

    MaineCoon(double w, const string& g, int a, const string& n, double fur) {
        weight = w;
        gender = g;
        age = a;
        name = n;
        furLength = fur;
    }

    MaineCoon(const MaineCoon& other) {
        weight = other.weight;
        gender = other.gender;
        age = other.age;
        name = other.name;
        furLength = other.furLength;
    }

    ~MaineCoon() override {}

    void play() override {
        cout << name << "  охотится на игрушечную мышку." << endl;
    }

    void feed() override {
        cout << name << " ест большую порцию корма." << endl;
    }

    void pet() override {
        cout << "Вы гладите " << name << ", его длинная шерсть очень мягкая." << endl;
    }

    void printClassName() const override {
        cout << "MaineCoon" << endl;
    }

    string toString() const override {
        stringstream ss;
        ss << "Тип: MaineCoon, Имя: " << name << ", Пол: " << gender
           << ", Возраст: " << age << ", Вес: " << fixed << setprecision(2) << weight << " кг"
           << ", Длина шерсти: " << fixed << setprecision(1) << furLength << " см";
        return ss.str();
    }

    // Уникальный метод
    void fluffFur() {
        furLength += 1;
        cout << name << " распушил шерсть, теперь она " << furLength << " см длиной!" << endl;
    }

    void setFurLength(double fl) { furLength = fl; }
    double getFurLength() const { return furLength; }
};

class Persian : public Cat {
private:
    string faceExpression;

public:
    Persian() {
        weight = 0;
        gender = "неизвестно";
        age = 0;
        name = "неизвестно";
        faceExpression = "спокойное";
    }

    Persian(double w, const string& g, int a, const string& n, const string& expr) {
        weight = w;
        gender = g;
        age = a;
        name = n;
        faceExpression = expr;
    }

    Persian(const Persian& other) {
        weight = other.weight;
        gender = other.gender;
        age = other.age;
        name = other.name;
        faceExpression = other.faceExpression;
    }

    ~Persian() override {}

    void play() override {
        cout << name << " играет с пёрышком." << endl;
    }

    void feed() override {
        cout << name << " ест корм для персидских кошек." << endl;
    }

    void pet() override {
        cout << "Вы гладите " << name << ", у неё плоская мордочка и выражение: " << faceExpression << "." << endl;
    }

    void printClassName() const override {
        cout << "Persian" << endl;
    }

    string toString() const override {
        stringstream ss;
        ss << "Тип: Persian, Имя: " << name << ", Пол: " << gender
           << ", Возраст: " << age << ", Вес: " << fixed << setprecision(2) << weight << " кг"
           << ", Выражение мордочки: " << faceExpression;
        return ss.str();
    }

    // Уникальный метод
    void changeExpression(const string& newExpr) {
        faceExpression = newExpr;
        cout << name << " теперь выглядит " << faceExpression << "." << endl;
    }

    void setFaceExpression(const string& expr) { faceExpression = expr; }
    string getFaceExpression() const { return faceExpression; }
};

class Sphynx : public Cat {
private:
    bool hasMustache;

public:
    Sphynx() {
        weight = 0;
        gender = "неизвестно";
        age = 0;
        name = "неизвестно";
        hasMustache = false;
    }

    Sphynx(double w, const string& g, int a, const string& n, bool m) {
        weight = w;
        gender = g;
        age = a;
        name = n;
        hasMustache = m;
    }

    Sphynx(const Sphynx& other) {
        weight = other.weight;
        gender = other.gender;
        age = other.age;
        name = other.name;
        hasMustache = other.hasMustache;
    }

    ~Sphynx() override {}

    void play() override {
        cout << name << " энергично прыгает." << endl;
    }

    void feed() override {
        cout << name << " ест высококалорийный корм, чтобы согреться." << endl;
    }

    void pet() override {
        cout << "Вы гладите " << name << ", его кожа тёплая и гладкая." << endl;
    }

    void printClassName() const override {
        cout << "Sphynx" << endl;
    }

    string toString() const override {
        stringstream ss;
        ss << "Тип: Sphynx, Имя: " << name << ", Пол: " << gender
           << ", Возраст: " << age << ", Вес: " << fixed << setprecision(2) << weight << " кг"
           << ", Есть усы: " << (hasMustache ? "да" : "нет");
        return ss.str();
    }

    // Уникальный метод
    void warmUp() {
        cout << name << " Греется под одеялом." << endl;
    }

    void setHasMustache(bool m) { hasMustache = m; }
    bool getHasMustache() const { return hasMustache; }
};


void printMenu() {
    cout << "1. Добавить новую кошку\n";
    cout << "2. Выполнить play() для всех кошек\n";
    cout << "3. Выполнить feed() для всех кошек\n";
    cout << "4. Выполнить pet() для всех кошек\n";
    cout << "5. Показать информацию о всех кошках\n";
    cout << "6. Выполнить уникальный метод для выбранной кошки\n";
    cout << "0. Выход\n";
}


int main() {
    vector<Cat*> cats;
    int choice;

    cats.push_back(new ScottishFold(4.5, "женский", 2, "Луна", true));
    cats.push_back(new MaineCoon(8.0, "мужской", 3, "Тор", 7.5));
    cats.push_back(new Persian(3.8, "женский", 4, "Белла", "сонное"));
    cats.push_back(new Sphynx(3.2, "мужской", 1, "Гизмо", false));
    cats.push_back(new ScottishFold(5.0, "мужской", 5, "Оливер", false));
    cats.push_back(new Persian(4.0, "женский", 6, "Хлоя", "сердитое"));

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int type;
            cout << "Выберите тип кошки:\n";
            cout << "1. Шотландская вислоухая\n2. Мейн-кун\n3. Персидская\n4. Сфинкс\n";
            cin >> type;

            double w;
            string g, n;
            int a;
            cout << "Введите вес: "; cin >> w;
            cout << "Введите пол: "; cin >> g;
            cout << "Введите возраст: "; cin >> a;
            cout << "Введите имя: "; cin >> n;

            if (type == 1) {
                bool folded;
                cout << "Ушки загнуты? (1-да, 0-нет): "; cin >> folded;
                cats.push_back(new ScottishFold(w, g, a, n, folded));
            }
            else if (type == 2) {
                double fur;
                cout << "Длина шерсти: "; cin >> fur;
                cats.push_back(new MaineCoon(w, g, a, n, fur));
            }
            else if (type == 3) {
                string expr;
                cout << "Выражение мордочки: "; cin >> expr;
                cats.push_back(new Persian(w, g, a, n, expr));
            }
            else if (type == 4) {
                bool mustache;
                cout << "Есть усы? (1-да, 0-нет): "; cin >> mustache;
                cats.push_back(new Sphynx(w, g, a, n, mustache));
            }
            else {
                cout << "Неверный тип\n";
            }
            break;
        }
        case 2:
            for (auto cat : cats) cat->play();
            break;
        case 3:
            for (auto cat : cats) cat->feed();
            break;
        case 4:
            for (auto cat : cats) cat->pet();
            break;
        case 5:
            for (size_t i = 0; i < cats.size(); ++i) {
                cout << i + 1 << ". " << cats[i]->toString() << endl;
            }
            break;
        case 6: {
            int index;
            cout << "Введите номер кошки (индекс): ";
            cin >> index;
            if (index < 1 || index > (int)cats.size()) {
                cout << "Неверный номер\n";
                break;
            }
            Cat* cat = cats[index - 1];

            if (typeid(*cat) == typeid(ScottishFold)) {
                ScottishFold* sf = dynamic_cast<ScottishFold*>(cat);
                if (sf) sf->foldEars();
            }
            else if (typeid(*cat) == typeid(MaineCoon)) {
                MaineCoon* mc = dynamic_cast<MaineCoon*>(cat);
                if (mc) mc->fluffFur();
            }
            else if (typeid(*cat) == typeid(Persian)) {
                Persian* p = dynamic_cast<Persian*>(cat);
                if (p) {
                    string newExpr;
                    cout << "Введите новое выражение мордочки: ";
                    cin >> newExpr;
                    p->changeExpression(newExpr);
                }
            }
            else if (typeid(*cat) == typeid(Sphynx)) {
                Sphynx* s = dynamic_cast<Sphynx*>(cat);
                if (s) s->warmUp();
            }
            else {
                cout << "Неизвестный тип\n";
            }
            break;
        }
        case 0:
            cout << "Выход из программы\n";
            break;
        default:
            cout << "Неверный выбор\n";
        }
    } while (choice != 0);

    for (auto cat : cats) {
        delete cat;
    }
    cats.clear();

    return 0;
}