#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct BusStop
{
    string name;
    BusStop* next;
    int price;
    BusStop(string n, BusStop* nxt = nullptr, int p = 0)
        : name(n), next(nxt), price(p) {
    }
};
vector<BusStop*> branches;
void clearScreen() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause()
{
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void viewStop(BusStop* stop) 
{
    if (!stop) 
    {
        cout << "Остановка не найдена!\n";
        return;
    }

    cout << "\n=== Информация об остановке ===\n";
    cout << "Название: " << stop->name << endl;

    if (stop->next) 
    {
        cout << "Следующая остановка: " << stop->next->name << endl;
        cout << "Цена проезда до следующей: " << stop->price << " руб." << endl;
    }
    else 
    {
        cout << "Конечная остановка (дальше автобус не идет)\n";
    }
}

void viewAllStopsInBranch(BusStop* start)
{
    if (!start) 
    {
        cout << "Ветка пуста!\n";
        return;
    }

    BusStop* current = start;
    int stopNumber = 1;

    cout << "\n=== Маршрут ветки ===\n";
    while (current)
    {
        cout << stopNumber << ". " << current->name;
        if (current->next) 
        {
            cout << " -> " << current->next->name
                << " (цена: " << current->price << " руб.)";
        }
        else 
        {
            cout << " [КОНЕЧНАЯ]";
        }
        cout << endl;

        current = current->next;
        stopNumber++;
    }
}

void viewAllBranches()
{
    if (branches.empty())
    {
        cout << "Нет созданных веток!\n";
        return;
    }

    cout << "\n=== Все ветки маршрутов ===\n";
    for (size_t i = 0; i < branches.size(); i++) 
    {
        cout << "\nВетка " << i + 1 << ":\n";
        viewAllStopsInBranch(branches[i]);
        cout << "-------------------\n";
    }
}

BusStop* createStop(string name, BusStop* nextStop = nullptr, int price = 0) 
{
    return new BusStop(name, nextStop, price);
}

void addStopToEnd()
{
    if (branches.empty())
    {
        cout << "Сначала создайте хотя бы одну ветку!\n";
        return;
    }
    viewAllBranches();
    int branchChoice;
    cout << "\nВыберите ветку для добавления остановки (1-" << branches.size() << "): ";
    cin >> branchChoice;
    if (branchChoice < 1 || branchChoice > static_cast<int>(branches.size())) 
    {
        cout << "Неверный выбор!\n";
        return;
    }
    BusStop* current = branches[branchChoice - 1];
    while (current->next) 
    {
        current = current->next;
    }
    string newStopName;
    int price;
    cout << "Текущая конечная остановка: " << current->name << endl;
    cout << "Введите название новой остановки: ";
    cin.ignore();
    getline(cin, newStopName);
    cout << "Введите цену проезда от '" << current->name << "' до '" << newStopName << "': ";
    cin >> price;
    current->next = createStop(newStopName, nullptr, price);
    cout << "Остановка '" << newStopName << "' успешно добавлена!\n";
}

void findPath() 
{
    if (branches.empty())
    {
        cout << "Нет созданных веток!\n";
        return;
    }
    string startName, endName;
    cout << "Введите начальную остановку (А): ";
    cin.ignore();
    getline(cin, startName);
    cout << "Введите конечную остановку (Б): ";
    getline(cin, endName);
    bool found = false;
    for (size_t i = 0; i < branches.size(); i++) 
    {
        BusStop* current = branches[i];
        BusStop* startStop = nullptr;
        int totalCost = 0;
        bool onRoute = false;
        while (current) 
        {
            if (current->name == startName)
            {
                startStop = current;
                onRoute = true;
                break;
            }
            current = current->next;
        }
        if (startStop) 
        {
            current = startStop;
            vector<string> path;
            while (current && onRoute)
            {
                path.push_back(current->name);
                if (current->name == endName) 
                {
                    found = true;
                    cout << "\n=== Найден маршрут ===\n";
                    cout << "Ветка " << i + 1 << ":\n";
                    for (size_t j = 0; j < path.size(); j++)
                    {
                        cout << path[j];
                        if (j < path.size() - 1) 
                        {
                            cout << " -> ";
                        }
                    }
                    cout << "\nОбщая стоимость проезда: " << totalCost << " руб.\n";
                    if (!current->next) 
                    {
                        cout << "Внимание: '" << endName << "' - конечная остановка, "
                            << "автобус дальше не идет!\n";
                    }
                    return;
                }
                if (current->next) 
                {
                    totalCost += current->price;
                }
                current = current->next;
                if (!current) 
                {
                    cout << "\nПуть найден, но остановка '" << endName
                        << "' не находится после '" << startName
                        << "' на этой ветке.\n";
                    onRoute = false;
                }
            }
        }
    }

    if (!found) {
        cout << "\nПрямого маршрута из '" << startName
            << "' в '" << endName << "' не найдено!\n";
        cout << "Возможно, эти остановки находятся на разных ветках.\n";
    }
}

void createNewBranch()
{
    int numStops;
    cout << "Сколько остановок будет в новой ветке? (минимум 2): ";
    cin >> numStops;
    if (numStops < 2)
    {
        cout << "В ветке должно быть минимум 2 остановки!\n";
        return;
    }
    vector<string> stopNames(numStops);
    vector<int> prices(numStops - 1);
    cin.ignore();
    for (int i = 0; i < numStops; i++)
    {
        cout << "Введите название остановки " << i + 1 << ": ";
        getline(cin, stopNames[i]);
    }
    for (int i = 0; i < numStops - 1; i++) 
    {
        cout << "Введите цену проезда от '" << stopNames[i]
            << "' до '" << stopNames[i + 1] << "': ";
        cin >> prices[i];
    }
    BusStop* last = createStop(stopNames[numStops - 1]);
    BusStop* current = last;
    for (int i = numStops - 2; i >= 0; i--)
    {
        BusStop* newStop = createStop(stopNames[i], current, prices[i]);
        current = newStop;
    }
    branches.push_back(current);
    cout << "Новая ветка успешно создана!\n";
    viewAllStopsInBranch(current);
}

void initializeTestData() 
{

    for (auto branch : branches) 
    {
        BusStop* current = branch;
        while (current)
        {
            BusStop* temp = current;
            current = current->next;
            delete temp;
        }
    }
    branches.clear();
    BusStop* stop5 = createStop("Вокзал");
    BusStop* stop4 = createStop("Университет", stop5, 25);
    BusStop* stop3 = createStop("Парк", stop4, 20);
    BusStop* stop2 = createStop("Центр", stop3, 15);
    BusStop* stop1 = createStop("Дом", stop2, 10);
    branches.push_back(stop1);
    BusStop* bStop4 = createStop("Завод");
    BusStop* bStop3 = createStop("Школа", bStop4, 30);
    BusStop* bStop2 = createStop("Больница", bStop3, 25);
    BusStop* bStop1 = createStop("Рынок", bStop2, 20);
    branches.push_back(bStop1);
    BusStop* cStop3 = createStop("Аэропорт");
    BusStop* cStop2 = createStop("Гостиница", cStop3, 40);
    BusStop* cStop1 = createStop("Стадион", cStop2, 35);
    branches.push_back(cStop1);
    cout << "Тестовые данные успешно загружены!\n";
    cout << "Создано 3 несвязанные ветки маршрутов.\n";
}

void cleanup()
{
    for (auto& branch : branches)
    {
        BusStop* current = branch;
        while (current) 
        {
            BusStop* temp = current;
            current = current->next;
            delete temp;
        }
    }
    branches.clear();
    cout << "Все данные очищены!\n";
}

void displayMenu() 
{
    clearScreen();
    cout << "=================================\n";
    cout << "     СИСТЕМА УПРАВЛЕНИЯ ОСТАНОВКАМИ\n";
    cout << "=================================\n";
    cout << "1. Просмотреть все ветки маршрутов\n";
    cout << "2. Показать путь и стоимость между остановками\n";
    cout << "3. Добавить новую остановку в конец пути\n";
    cout << "4. Создать новую ветку маршрута\n";
    cout << "5. Просмотреть информацию об остановке\n";
    cout << "6. Загрузить тестовые данные (2-3 ветки)\n";
    cout << "7. Очистить все данные\n";
    cout << "0. Выход\n";
    cout << "=================================\n";
    cout << "Выберите действие: ";
}

void viewSpecificStop() 
{
    if (branches.empty())
    {
        cout << "Нет созданных веток!\n";
        return;
    }
    string stopName;
    cout << "Введите название остановки: ";
    cin.ignore();
    getline(cin, stopName);
    bool found = false;
    for (size_t i = 0; i < branches.size(); i++)
    {
        BusStop* current = branches[i];
        while (current) 
        {
            if (current->name == stopName) 
            {
                cout << "\nОстановка найдена в ветке " << i + 1 << ":\n";
                viewStop(current);
                found = true;
            }
            current = current->next;
        }
    }
    if (!found) 
    {
        cout << "Остановка с названием '" << stopName << "' не найдена!\n";
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    int choice;

    do 
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            clearScreen();
            viewAllBranches();
            pause();
            break;

        case 2:
            clearScreen();
            findPath();
            pause();
            break;

        case 3:
            clearScreen();
            addStopToEnd();
            pause();
            break;

        case 4:
            clearScreen();
            createNewBranch();
            pause();
            break;

        case 5:
            clearScreen();
            viewSpecificStop();
            pause();
            break;

        case 6:
            clearScreen();
            initializeTestData();
            pause();
            break;

        case 7:
            clearScreen();
            cleanup();
            pause();
            break;

        case 0:
            cout << "Выход из программы...\n";
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
            pause();
            break;
        }

    } while (choice != 0);
    cleanup();
    return 0;
}
