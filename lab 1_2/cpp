#include <iostream>
#include <string>

using namespace std;

class player
{
private:
    string name;
    int posX;
    int posY;
    int health;
    bool isActive;

public:
    player() : name("Unknown"), posX(0), posY(0), health(100), isActive(true)
    {
        cout << "Вызван конструктор по умолчанию" << endl;
    }

    player(const string& name, int x, int y, int hp, bool active) : name(name), posX(x), posY(y), health(hp), isActive(active)
    {
        cout << "Вызван конструктор полного заполнения" << endl;
    }

    player(const player& other) : name(other.name), posX(other.posX), posY(other.posY), health(other.health), isActive(other.isActive)
    {
        cout << "Вызван конструктор копирования" << endl;
    }

    ~player()
    {
        cout << "Персонаж " << name << " уничтожен" << endl;
    }

    string getName() const
    {
        return name;
    }

    int getPosX() const
    {
        return posX;
    }

    int getPosY() const
    {
        return posY;
    }

    int getHealth() const
    {
        return health;
    }

    bool getActionStatus() const
    {
        return isActive;
    }

    void setPosition(int x, int y)
    {
        posX = x;
        posY = y;
        cout << name << " переместился в позицию (" << x << ", " << y << ")" << endl;
    }

    void setPosX(int x)
    {
        posX = x;
        cout << name << ": X изменен на " << x << endl;
    }

    void setPosY(int y)
    {
        posY = y;
        cout << name << ": Y изменен на " << y << endl;
    }

    void displayInfo() const
    {
        cout << "\n=== Информация о персонаже ===" << endl;
        cout << "Имя: " << name << endl;
        cout << "Позиция: (" << posX << ", " << posY << ")" << endl;
        cout << "ХП: " << health << endl;
        cout << "Статус действия: " << (isActive ? "Активен" : "Неактивен") << endl;
        cout << "==============================\n" << endl;
    }

    void takeDamage(int damage)
    {
        if (damage < 0)
        {
            cout << "Урон не может быть отрицательным!" << endl;
            return;
        }
        health -= damage;
        cout << name << " получил " << damage << " урона" << endl;
        if (health <= 0)
        {
            health = 0;
            isActive = false;
            cout << name << " повержен!" << endl;
        }
    }

    void heal(int amount)
    {
        if (amount < 0)
        {
            cout << "Лечение не может быть отрицательным!" << endl;
            return;
        }
        health += amount;
        cout << name << " восстановил " << amount << " ХП" << endl;
        if (health > 100)
        {
            health = 100;
        }
        if (health > 0)
        {
            isActive = true;
        }
    }

protected:
    void changeName(const string& newName)
    {
        name = newName;
    }
};

int main()
{
    setlocale(0, "Rus");
    cout << "=== Создание персонажей ===" << endl;

    player player1;
    player1.displayInfo();

    player player2("Игрок", 10, 20, 80, true);
    player2.displayInfo();

    player player3 = player2;
    player3.displayInfo();

    cout << "\n=== Тестирование методов ===" << endl;
    player1.setPosition(5, 15);
    player1.setPosX(8);
    player1.setPosY(12);

    cout << "\nГеттеры character2:" << endl;
    cout << "Имя: " << player2.getName() << endl;
    cout << "X: " << player2.getPosX() << endl;
    cout << "Y: " << player2.getPosY() << endl;
    cout << "ХП: " << player2.getHealth() << endl;
    cout << "Статус: " << player2.getActionStatus() << endl;

    cout << "\n=== Бой и лечение ===" << endl;
    player2.displayInfo();
    player2.takeDamage(30);
    player2.displayInfo();
    player2.takeDamage(60);
    player2.displayInfo();
    player2.heal(50);
    player2.displayInfo();
    player2.heal(100);
    player2.displayInfo();

    cout << "\n======" << endl;
}
