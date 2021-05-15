#include <iostream>
#include "tank.h"

using namespace std;

int answ;
char answer;

int random(int min, int max) {
    int num = min + rand() % (max - min + 1);
    return num;
}

bool Ammunition::check_state() {
    cout << " # Current ammunition state: " << quantity;
    if (quantity > 10) return true;
    else {
        cout << "Not enough ammunition. Try another one.\n";
        return false;
    } 
}

bool LoadingSystem::prepare_ammunition(int type) {
	cout << "Checking the ammunition...\n";
    if (ammunition_list[type].is_enough){
    	cout << "Preparing ammunition\n";
        ammunition = ammunition_list[type];
        ammunition_list[type].quantity--;
        ammunition_list[type].is_enough = ammunition_list[type].check_state();
        loaded_state = true;
    } else {
        cout << "The machine wasn`t loaded\nNot enough ammunition\n";
        loaded_state = false;
    }
    return loaded_state;
}

bool LoadingSystem::load() {
    bool result;
        cout << "Choose ammunion type:\n 1. TYPE_1\n 2. TYPE_2\n";
        cin >> answ;
        switch(answ){
            case 1: {
                result = prepare_ammunition(0);
                break; }
            case 2: {
                result = prepare_ammunition(1);
                break; }    
            default: cout << "Wrong type\n";
        }
    return result;
}

void ProjectileAcceleration::fire() {
    cout << "Fire!\n";
}

void ProjectileAcceleration::accelate() {
    cout << "Starting accelation\n";
}

void ProjectileAcceleration::shoot(RecoilDumping& rd) {
    if (state) {
        fire();
        accelate();
        rd.recoil();
        shots_state++;
    } else cout << "Projectile acceleration is not ready\n";

}

void ProjectileAcceleration::change_trunk() {
    if (shots_state > 1000 ) {
        cout << "Changing trunk\n";
        trunk.ID += 10;
        cout << " # New ID: " << trunk.ID << endl; 
    }
}

void Sight::aim() {
    cout << "Please enter the coordinates of your aim\nx: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    cout << "New aim was set: " << x << " - " << y << endl;
    chase();
}

void Sight::chase() {
    cout << "Started chasing the aim\n";
    chasing = true;
}

void RecoilDumping::recoil() {
    cout << "Recoil was dumped\n";
}

bool ControlSystem::activate_systems(Machine& machine) {
    int num = random(0, 100);
    if (num%27 == 0) {
        cout << "Something went wrong\nPlease try again later";
        return false;
    } else {
        machine.sight.state = true;
        cout << "Sight system was activated\n";
        machine.loadingsystem.state = true;
        cout << "Loading system was activated\n";
        machine.rd.state = true;
        cout << "Recoil dumping system was activated\n";
        machine.pa.state = true;
        cout << "Projectile acceleration system was activated\n";
        return true;
    }
}

bool ControlSystem::prepare_ammunition(LoadingSystem& loadingsystem) {
    bool result = loadingsystem.load();
    return result;
}

void ControlSystem::aim(Sight& sight) {
    sight.aim();
}

void ControlSystem::shoot(ProjectileAcceleration& pa, RecoilDumping& rd, Sight& sight) {
    pa.shoot(rd);
    sight.chasing = false;
    cout << "Aim system returned to its original state\n";
}

void ControlSystem::disactivate_systems(Machine& machine) {
    machine.sight.state = false;
    cout << "Sight system was disactivated\n";
    machine.loadingsystem.state = false;
    cout << "Loading system was disactivated\n";
    machine.rd.state = false;
    cout << "Recoil dumping system was disactivated\n";
    machine.pa.state = false;
    cout << "Projectile acceleration system was disactivated\n";
}

bool Operator::activate(Machine& machine) {
    cout << "#Operator: activate systems!\n";
    bool res = machine.controlsystem.activate_systems(machine);
    return res;
}

bool Operator::prepare_ammunition(Machine& machine) {
    bool result = machine.controlsystem.prepare_ammunition(machine.loadingsystem);
    return result;
}

void Operator::aim(Machine& machine) {
	char answ;
    cout << "#Operator: aim\n";
    do {
        machine.controlsystem.aim(machine.sight);
        cout << "Do you want to change the aim?\n";
        cin >> answ;
    } while (answ == 'y' || answ == 'Y');
}

void Operator::shoot(Machine& machine) {
    cout << "#Operator: fire!\n";
    machine.controlsystem.shoot(machine.pa, machine.rd, machine.sight);
}

bool Operator::disactivate(Machine& machine) {
    cout << "Disactivating systems\n";
    machine.controlsystem.disactivate_systems(machine);
}

int main(){
    Machine tank("TANK_01");
    Operator ops("Casey Edwards");

    if (ops.activate(tank)) {
        do { 
            cout << "Do you want to shoot?\n";
            cin >> answer;
            if (answer == 'y' || answer == 'Y') {
                cout << "Preparing for shooting\n";
                if (ops.prepare_ammunition(tank)) {
                    ops.aim(tank);
                    ops.shoot(tank);
                } else cout << "An error occured\nPlease try again later\n";
            }
        } while (answer == 'y' || answer == 'Y');
        ops.disactivate(tank);
    }

    return 0;
}
