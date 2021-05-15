#pragma once
#include <iostream>

using namespace std;

class Human;
class Mechanic;
class TowerSystem;
class Tank;
class ControlSystem;
class Shooter;

class Generator {
    int power = 12000;                              // потужність
    string type = "G328SD";                         // модель
    public:
        bool generating_energy = true;              // стан генератора
};

class ElectroSystem {
    Generator generator;                            // джерело живлення
    string cables_type = "C576SS";                  // тип кабелів
    int cables_quantity = 50;                       // к-сть кабелів
    public:
        // подача енергії
        void give_energy(ControlSystem& controlsystem);
};

class MoveSystem {
    string caterpillar = "C345hg";                  // тип гусениць
    public:
        bool c_health = true;                       // відсутність пошкоджень гусениць
        bool c_state = false;                       // стан роботи гусениць
        void move();                                // початок руху
        void stop();                                // зупинка
        void rotate();                              // зміна руху
        void repair_c();                            // ремонт гусениць
};

class RadiolocationSystem {
    int volume;                                // гучність
    public:
        RadiolocationSystem(){ volume = 90; }       // чтан гучності за замовчуванням

        bool state = false;                         // стан роботи
        string commands;                            // команда, яку варто передати
        
        // передача команди до інших членів команди
        void translate_command(int command, Human& human);
};

class EngineSystem {
    string engine = "T9030ds";                      // модель двигуна
    public:
        bool state = false;                         // стан робооти
        void rotate(bool n_state);                    // рбота двигуна
};

class FuelSystem {
    public:
        FuelSystem() { level = 80; }                // к-сть палива за замовчуванням
        int level;                                  // ріваень заправленості
        void refuel();                              // дозаправка
        void give_fuel(EngineSystem& engine);       // подача палива
        void stop_giving_fuel(EngineSystem& engine);// припинення подачі палива
};

class Human {
    public:
        string name;
};

class Mechanic: public Human {
    string name;
    public:
        Mechanic(string var) { name = var; }
        void power_on(Tank& tank);                  // увімкнути системи
        void check_fuel(FuelSystem& fuelsystem);    // перевірити рівень палива
        void refuel(FuelSystem& fuelsystem);        // дозаправка
        void fuel_supply(Tank& tank);               // подача палива
        void go(Tank& tank);                        // початок руху
        void rotate(Tank& tank);                    // зміна руху
        void stop(Tank& tank);                      // припинення руху
        void repair_c(MoveSystem& movesystem);      // ремонт гусениць
};

class Cap: public Human {
    public:
        Cap(string var) { name = var; }
        // віддати команду про початок руху
        void commandgo(RadiolocationSystem& radio, Mechanic& mechanic);
        // віддати команду про припинення руху
        void commandstop(RadiolocationSystem& radio, Mechanic& mechanic);
        // інші команди
        void command(RadiolocationSystem& radio, Shooter& shooter);
};

class Shooter: public Human {
    public:
        Shooter(string var) { name = var; }
        void shoot(Tank& tank);                     // провести вистріл
        void aim(TowerSystem& towersystem);         // прицілювання
        void rotatetower(TowerSystem& towersystem); // поворот башти
};

class TowerSystem {
    string tower = "T42738dsa";                     // модель механізму повороту
    public:
        bool state = false;                         // готовність
        int x = 0;                                  // координати для прицілення
        int y = 0;
        int angle = 0;                              // кут повороту
        void rotate();                              // поворот башти
        void aim();                                 // захват цілі
        void shoot();                               // постріл
};

class ControlSystem {
    string steering_wheel = "ST7368SS";             // руль повороту
    public:
        bool state = false;                         // готовність до роботи
        void rotate(MoveSystem& movesystem);        // поворот
};

class Tank {
    string name;
    public:
        Tank(string var) { name = var; }
        ElectroSystem electrosystem;                // електросистема
        MoveSystem movesystem;                      // ходова система
        RadiolocationSystem radiolocationsystem;    // радіолокаційна система
        FuelSystem fuelsystem;                      // система пального
        EngineSystem enginesystem;                  // система двгунів
        TowerSystem towersystem;                    // система башти
        ControlSystem controlsystem;                // система контролю
};
