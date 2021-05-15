#pragma once
#include <iostream>

using namespace std;

class Machine;
class RecoilDumping;

// металическая пластина
class Baffle {
    string material = "steel";
};

class Ammunition {
    public:
        int quantity = 28;
        bool is_enough = true;
        string name;
        bool check_state();
};

class Type1: public Ammunition {
    public:
        Type1() { name = "Type1"; }
};

class Type2: public Ammunition {
    public:
        Type2() { name = "Type2"; }
};

// затвор
class Gate {
    public:
        bool is_open = false;
};

// казенник
class Breech {
    public: 
        bool is_loaded = false;
};

class LoadingSystem {
    Baffle baffle;
    Gate gate;
    Ammunition ammunition;
    Type1 type1;
    Type2 type2;
    bool loaded_state = false;
    unsigned short int max_time = 8;
    bool tenacity = true;
    int min_set_size = 28;

    public:
        Ammunition ammunition_list[2] = { type1, type2 };
        LoadingSystem() {}
        bool state = false;
        float time;
        int set_size;
        bool prepare_ammunition(int type);
        bool load();
};

class Trunk {
    int length_m = 2;
    bool state = true;
    public:
        Trunk(int var){ ID = var; }
        int ID;
        bool check_state();
};

// разгон снаряда
class ProjectileAcceleration {
    Trunk trunk = 10 ;

    public:
        ProjectileAcceleration() {}
        bool state = false;
        int shots_state;
        void fire();
        void accelate();
        void shoot(RecoilDumping& rd);
        void change_trunk();
};

// прицеливание
class Sight {
    public:
        bool state = false;
        bool chasing = false;
        int x;
        int y;
        void aim();
        void chase();
};

// сброс отдачи
class RecoilDumping {
    public:
        bool state = false;
        void recoil();
};

class  ControlSystem {
    bool fault_tolerance = true;
    bool reliability = true;

    public:
        bool activate_systems(Machine& machine);
        bool prepare_ammunition(LoadingSystem& loadingsystem);
        void aim(Sight& sight);
        void shoot(ProjectileAcceleration& pa, RecoilDumping& rd, Sight& sight);
        void disactivate_systems(Machine& machine);
};

class Machine {
    string name;
    public:
    LoadingSystem loadingsystem;
    ProjectileAcceleration pa;
    Sight sight;
    ControlSystem controlsystem;
    RecoilDumping rd;
    Machine(string var) { name = var; }
};

class Operator {
    string name;

    public:
        Operator(string var) { name = var;}
        bool activate(Machine& machine);
        bool prepare_ammunition(Machine& machine);
        void aim(Machine& machine);
        void shoot(Machine& machine);
        bool disactivate(Machine& machine);
};
