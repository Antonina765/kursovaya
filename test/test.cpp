#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "nlohmann/json.hpp"

// для упрощения записи
using json = nlohmann::json;
using namespace std;

// перечесление типов жилья
enum class PropertyType{
    FLAT = 0,
    HOUSE = 1,
    GARAGE = 2,
    DACHA = 3,
    OTHER = 4 
};

// перечесление размещения жилья
enum class PropertyLocation {
    MINSK = 0,
    OBLCITIES = 1,
    BIGTOWNS = 2,
    OTHERS = 3
};

// структура недвижимость
struct RealEstate {
public:
        PropertyType TYPE;
        PropertyLocation LOCATION;
        double area;

        // Конструктор для инициализации всех полей структуры
        RealEstate(PropertyType propT, PropertyLocation propL, double area)
            : TYPE(propT), LOCATION(propL), area(area) {}


        // Конструктор по умолчанию
        RealEstate() : TYPE(PropertyType::OTHER), LOCATION(PropertyLocation::OTHERS), area(0.0) {}

        //вывод всей инфы о недвижимости
        void PrintInfo() {
            cout << "Тип недвижимости\t|\t Расположение недвижимости\t|" << "Площадь недвижимости\t|" << endl;
            switch (static_cast<int>(this->TYPE)) {
            case 0:
                cout << "Квартира\t|\t";
                break;
            case 1:
                cout << "Дом\t|\t";
                break;
            case 2:
                cout << "Гараж/машиноместо\t|\t";
                break;
            case 3:
                cout << "Дача/садовый домик\t|\t";
                break;
            case 4:
                cout << "Другое\t|\t";
                break;
            default:
                cout << "error" << endl;
                break;
            }
            switch (static_cast<int>(this->LOCATION)) {
            case 0:
                cout << "Минск\t|\t" << endl;
                break;
            case 1:
                cout << "Областной город\t|\t" << endl;
                break;
            case 2:
                cout << "Большой город\t|\t" << endl;
                break;
            case 3:
                cout << "Другое\t|\t" << endl;
                break;
            default:
                cout << "error" << endl;
                    break;
                
            }
        }
};


struct User {
public:
    string name;
    string password;
    bool hasPrivileges;
    bool isBlocked;
    RealEstate possession;
    double totalTax;

    //конструктор с параматрами
    User(const string& n, const string& pass, bool privileges, bool blocked, const RealEstate& estate) {
        name = n;
        password = pass; 
        hasPrivileges = privileges;
        possession = estate;
        isBlocked = blocked;
        Calculator calc;
        totalTax = calc.Calculate(User{ name, password, hasPrivileges, isBlocked, possession });
    }

    // Конструктор по умолчанию
    User() : name(""), password(""), hasPrivileges(false), isBlocked(false), possession(), totalTax(0) {}

    void PrintAllOwnInfo() {
        if (isBlocked)
        {
            BlockedMessage();
            return;
        }
        cout << "Имя пользователя\t|\t Наличие привелегий\t|" << endl;
        cout << this->name << "\t|\t" << this->hasPrivileges << "\t|" << endl;
        cout << "Данные о недвижимости:" << endl;
        this->possession.PrintInfo();
    }

    void ChangeOwnInfo(string nameToChange, string passwordToChange, bool hasPrivilegesToChange, RealEstate possessionToChange) {
        if (isBlocked)
        {
            BlockedMessage();
            return;
        }
        this->name = nameToChange;
        this->password = passwordToChange;
        this->hasPrivileges = hasPrivilegesToChange;
        this->possession = possessionToChange;
    }
    void Menu() {}


    void OperationMessage() {}
    void BlockedMessage() {
        cout << "Вы заблокированы, действие невозможно" << endl;
    }
};


struct Admin
{
public:
    const string Name = "Admin";
    const int PASSWORD = 1111;

    void EditUser(User& userToEdit) {


        #pragma region EasyToEdit


        cout << "На какой имя сменить" << endl;
        string newName = "";
        cin >> newName;
        cout << "" << endl;

        cout << "На какой пароль сменить" << endl;
        string newPassword = "";
        cin >> newPassword;
        cout << "" << endl;

        cout << "Имеет ли пользователь льготы? (1 - da/2 - net)" << endl;
        int tempHasPrivileges;
        bool newHasPrivileges;
        cin >> tempHasPrivileges;
        cout << "" << endl;
        newHasPrivileges = tempHasPrivileges == 1;
#pragma endregion

        #pragma region realEstateStat



        #pragma region Тип недвижимости
        cout << "Какой тип недвидимости у пользователя? (1-5)" << endl;
        PropertyType TypeToChange;
        int tempType;
        cin >> tempType;
        cout << "" << endl;
        switch (tempType)
        {
        case 0:
            TypeToChange = PropertyType::FLAT;
            break;
        case 1:
            TypeToChange = PropertyType::HOUSE;
            break;
        case 2:
            TypeToChange = PropertyType::GARAGE;
            break;
        case 3:
            TypeToChange = PropertyType::DACHA;
            break;
        case 4:
            TypeToChange = PropertyType::OTHER;
            break;

        default:
            cout << "err" << endl;
            return;
        }
#pragma endregion

        #pragma region Расположение недвижимости
            cout << "Какой тип недвидимости у пользователя? (1-5)" << endl;
        PropertyLocation LocationToChange;
        int tempLocation;
        cin >> tempType;
        cout << "" << endl;
        switch (tempLocation)
        {
        case 0:
            LocationToChange = PropertyLocation::MINSK;
            break;
        case 1:
            LocationToChange = PropertyLocation::OBLCITIES;
            break;
        case 2:
            LocationToChange = PropertyLocation::BIGTOWNS;
            break;
        case 3:
            LocationToChange = PropertyLocation::OTHERS;
            break;
        default:
            cout << "err" << endl;
            return;
        }
#pragma endregion
        
        cout << "Какая площедь у недвижимости?" << endl;
        double areaToChange;
        cin >> areaToChange;
        cout << "" << endl;
#pragma endregion

        userToEdit.ChangeOwnInfo(newName, newPassword, newHasPrivileges, RealEstate(TypeToChange, LocationToChange, areaToChange));
    }

    // поиск заблоканых 

    void SearchByUserName(vector<User> users, string userToFind) {
        for (const auto& user : users) {
            if (user.name == userToFind) {
                cout << "Пользователь найден!" << endl;
                PrintAllInfo(user);
            }
        }
    }

    void SearchByPropertyType(vector<User> users, int propType) {
        for (const auto& user : users) {
            if (static_cast<int>(user.possession.TYPE) == propType) {
                PrintAllInfo(user);
            }
        }
    }

    void PrintAllInfo(User user) {
        cout << "Имя пользователя\t|\t Наличие привелегий\t|\t Заблокирован" << endl;
        cout << user.name << "\t|\t" << user.hasPrivileges << "\t|\t" << user.isBlocked << endl;
        cout << "Данные о недвижимости:" << endl;
        user.possession.PrintInfo();
    }

    void SortByTax(vector<User>& users) {
        for (size_t i = 0; i < users.size() - 1; ++i) {
            for (size_t j = 0; j < users.size() - i - 1; ++j) {
                if (users[j].totalTax > users[j + 1].totalTax) {
                    // Обмен местами элементов
                    User temp = users[j];
                    users[j] = users[j + 1];
                    users[j + 1] = temp;
                }
            }
        }
    }

    void BlockUser(User& userToEdit) {}

    //void SortByTaxDescending(vector<User> users) {}
};


struct Calculator {
private:
    const double minsk[5] = { 900, 720, 330, 550, 1750 };
    const double oblCities[5] = { 750, 570, 280, 440, 1120 };
    const double bigTowns[5] = { 660, 530, 220, 330, 660 };
    const double other[5] = { 500, 280, 150, 280, 480 };
    const double rate = 0.001;

    double DeterminePricePerSqMeter(PropertyLocation pl, PropertyType pt) {
        switch (static_cast<int>(pl))
        {
        case 0:
            return minsk[static_cast<int>(pt)];
        case 1:
            return oblCities[static_cast<int>(pt)];
        case 2:
            return bigTowns[static_cast<int>(pt)];
        case 3:
            return other[static_cast<int>(pt)];
        default:
            cout << "Calculation err" << endl;
            break;
        }
    }

public:
    double Calculate(User us) {
        if (us.hasPrivileges) {
            return 0.0;  // если есть льготы то платить не надо
        }
        return rate * DeterminePricePerSqMeter(us.possession.LOCATION, us.possession.TYPE) * us.possession.area;
    }
};


#pragma region RelatedToJson
// Функция для сериализации вектора из n количества структур User в JSON объект
json serializeUsers(const vector<User>& users) {
    // Создаем JSON объект
    json j;

    // Заполняем JSON объект данными из вектора структур
    for (size_t i = 0; i < users.size(); ++i) {
        json userJson;
        userJson["name"] = users[i].name;
        userJson["password"] = users[i].password;
        userJson["hasPrivileges"] = users[i].hasPrivileges;
        userJson["isBlocked"] = users[i].isBlocked;

        // Сериализуем поле possession (недвижимость)
        json realEstateJson;
        realEstateJson["TYPE"] = static_cast<int>(users[i].possession.TYPE);
        realEstateJson["LOCATION"] = static_cast<int>(users[i].possession.LOCATION);
        realEstateJson["area"] = users[i].possession.area;

        userJson["possession"] = realEstateJson;

        // Добавляем каждый объект User в массив JSON объектов
        j.push_back(userJson);
    }

    // Возвращаем JSON объект
    return j;
}

// Функция для записи сериализованных данных в файл в формате JSON
void WriteToFile(const string& filename, const json& data) {
    // Открываем файл для записи
    ofstream file(filename);
    if (file.is_open()) {
        // Записываем данные в файл
        file << data.dump(4); // 4 - количество пробелов для форматирования JSON для улучшения читаемости
        // Закрываем файл
        file.close();
        cout << "Данные успешно записаны в файл: " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

// Функция для чтения данных из файла в формате JSON
vector<User> ReadJson(const string& filename) {
    // Открываем файл для чтения
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return {};
    }

    // Читаем данные из файла в формате JSON
    json jsonData;
    file >> jsonData;
    file.close();

    // Создаем вектор пользователей
    vector<User> users;

    // Проходим по каждому элементу в JSON и создаем объекты User
    for (const auto& userData : jsonData) {
        // Извлекаем данные из JSON объекта
        string name = userData["name"];
        string password = userData["password"];
        bool hasPrivileges = userData["hasPrivileges"];
        bool isBlocked = userData["isBlocked"];

        // Извлекаем данные о недвижимости (RealEstate)
        json realEstateData = userData["possession"];
        PropertyType propType = static_cast<PropertyType>(realEstateData["TYPE"]);
        PropertyLocation propLocation = static_cast<PropertyLocation>(realEstateData["LOCATION"]);
        double area = realEstateData["area"];

        // Создаем объект RealEstate
        RealEstate possession(propType, propLocation, area);

        // Создаем объект User и добавляем его в вектор
        users.push_back(User(name, password, hasPrivileges, isBlocked, possession));
    }

    return users;
}
#pragma endregion


json CreateJson4Test() {
    // Создаем 4 пользователей с произвольными данными
    vector<User> users = {
        User("Alice", "pass123", true, false, RealEstate(PropertyType::FLAT, PropertyLocation::MINSK, 66.0)),
        User("Bob", "qwerty", false, false, RealEstate(PropertyType::HOUSE, PropertyLocation::BIGTOWNS, 150.0)),
        User("Charlie", "password", true, true, RealEstate(PropertyType::GARAGE, PropertyLocation::OBLCITIES, 25.0)),
        User("David", "123456", false, true, RealEstate(PropertyType::DACHA, PropertyLocation::OTHERS, 500.0))
    };

    // Сериализуем вектор пользователей в JSON объект
    json jsonData = serializeUsers(users);

    return jsonData;
}




int main() {
    setlocale(LC_ALL, "Russian");

    vector<User> users = ReadJson("User_Data.json");

    // chto to delaem

    json data = serializeUsers(users);

    WriteToFile("User_Data.json", data);
}


//todo     нужно чтобы сначала создавался вектор из считанных пользователей из файла (из json или текста)
//todo     если человек входит в аккаунт, то присвоить номер по порядку переменной чтобы обращаться к этому конктретному пользователю ( users[counter] )
//todo     если регистрация то нужно присвоить значение равное vector.size()-1 (так как отсчет начинается с нуля)

