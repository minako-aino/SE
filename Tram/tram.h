#pragma once
#include <string>
#include <vector>

using namespace std;

class Tram;
class Passenger;

class Controller{
    public:
        int position = 0; // початковий стан
};

class Button{
    public:
        Button(string str){ appointment = str; }
        bool state; // стан
        string appointment; // призначення
};

class ControlSystem{
    public:
        // панель управління
        Button buttons[8] = {Button("move1"), Button("move2"), Button("open doors"), Button("close doors"), Button("turn on/off fans"), Button("turn on/off heat"), Button("make warmer"), Button("make colder")};
        // контроллер
        Controller controller;
};

class Fan{
    bool state;
    public:
        void rotate(bool stat);
};

class Heater{
    bool state;
    public:
        void heat(bool stat);
};

class FanHeaterSystem{
    public:
        int temperature;
        Fan fan;
        Heater heater;
};

class Engine{
    public:
        int speed = 0;
        void rotate(int rot_speed);
};

class MoveSystem{
    public:
        Engine engine;
        void move();
};

class Cashier{
    string name;
    public:
        Cashier(){ name = "Sasha"; }
        bool checkticket(Passenger& passenger);
};

class Ticket{
    public:
        int price = 5;
};

class PaySystem{
	int ID;
    public:
        PaySystem() { ID = 99;};
        Cashier cashier;
        int sum = 0;
        int checkmoney();
        bool give_money_ticket(int sum);
};

class ElectroSystem{
    public:
        int current;
        int givecurrent(int state);
};

class Door{
    public:
        bool state;
        bool open();
        void close();
};

class BodyWork{
    public:
        Door door;
        int sitting_places = 64;    // кількість сидячих місць
        int passengers_count = 0;   // к-сть пасажирів
        int sitting_passengers = 0; // к-сть зайнятих сидячих місць
        void primetime();
};

class Driver{
    string name;
    public:
        Driver(string str) { name = str; }
        void OpenDoor(Tram& tram);
        void CloseDoor(Tram& tram);
        void Go(Tram& tram);
        void ChangeSpeed(Tram& tram);
        void Stop(Tram& tram);
        void OnHeat(Tram& tram);
        void OffHeat(Tram& tram);
        void OnFan(Tram& tram);
        void OffFan(Tram& tram);
};

class Passenger{
    public:
       bool ticket = false;  // наявність квитка
       bool haveticket(PaySystem& pay);
       bool Goon(BodyWork& body);
       void Goout(BodyWork& body);
       bool Sit(BodyWork& body);
       bool HoldOn(); 
};

class Tram{
    int num;
    public:
        Tram() { num = 19; };
        FanHeaterSystem fanheat;            // підсистема вентиляції та опалення
        PaySystem pay;                      // підсистема оплати
        ElectroSystem electrosys;           // підсистема енергозабезпечення
        BodyWork body;                      // кузов
        ControlSystem controlsys;           // підсистема управління
        MoveSystem move;                    // ходова підсистема
};
