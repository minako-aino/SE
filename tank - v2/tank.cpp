#include <iostream>
#include "tank.h"

using namespace std;

int answ;

int random(int min, int max) {
    int num = min + rand() % (max - min + 1);
    return num;
}

void war(Tank& tank){
    int r = random(1, 100);
    if (r%21 == 0) {
    	cout << "----------------------------------------------\n";
        cout << "Alarm!\nYou were shot by one of the enemies\n";
        tank.movesystem.c_health = false;
        cout << "You need a repair\n";
        cout << "----------------------------------------------\n";
    }
}

void ElectroSystem::give_energy(ControlSystem& controlsystem) {
    if (!controlsystem.state) controlsystem.state = true;
    else cout << "It is already on\n";
}

void MoveSystem::rotate() {
    cout << "The tank was turned\n";
}

void MoveSystem::move() {
    c_state = true;
    cout << "Catterpillars are working\n";
    if (c_state) cout << "Started moving\n";
}

void MoveSystem::stop() {
    c_state = false;
    cout << "Catterpillars are stopped\n";
}

void MoveSystem::repair_c() {
    c_health = true;
}

void RadiolocationSystem::translate_command(int command, Human& human) {
    switch (command) {
        case 1: {
            commands = "go";
            break; }
        case 2: {
            commands = "shoot";
            break; }
        case 3: {
            commands = "stop"; 
            break; }
    }
}

void EngineSystem::rotate(bool n_state) {
    state = n_state;
}

void FuelSystem::refuel() {
    level = 100;
}

void FuelSystem::give_fuel(EngineSystem& engine) {
    cout << "Giving fuel\n";
    engine.state = true;
    cout << "Engines are working\n";
}

void FuelSystem::stop_giving_fuel(EngineSystem& engine) {
    cout << "Stopped giving fuel\n";
    engine.state = false;
    cout << "Engines are stopped\n";
}

void Mechanic::check_fuel(FuelSystem& fuelsystem) {
    cout << " -- Current fuel state: " << fuelsystem.level << endl;
    if (fuelsystem.level < 90) {
        cout << "Need to refuel\n";
        refuel(fuelsystem);
    } else cout << "Tank is ready to go\n";
}

void Mechanic::refuel(FuelSystem& fuelsystem) {
    if (fuelsystem.level == 100) cout << "It is already full\n";
    else {
        cout << "Refuelling...\n";
        fuelsystem.refuel();
    }
}

void Mechanic::fuel_supply(Tank& tank) {
    if (tank.radiolocationsystem.commands == "go") {
        tank.fuelsystem.give_fuel(tank.enginesystem);
        go(tank);
    }
}

void Mechanic::rotate(Tank& tank) {
    cout << "Sending command to the control system\n";
    tank.controlsystem.rotate(tank.movesystem);
}

void Mechanic::power_on(Tank& tank) {
    cout << "Turning on radio\n";
    tank.radiolocationsystem.state = true;
    cout << "Turning on computer control panel\n";
    tank.electrosystem.give_energy(tank.controlsystem);
}

void Mechanic::go(Tank& tank) {
    tank.movesystem.move();
}

void Mechanic::stop(Tank& tank) {
    tank.fuelsystem.stop_giving_fuel(tank.enginesystem);
    tank.movesystem.stop();
    cout << "Radio was stopped\n";
    tank.radiolocationsystem.state = false;
}

void Mechanic::repair_c(MoveSystem& movesystem) {
    if (movesystem.c_health == false) {
        movesystem.repair_c();
        cout << "Caterpillars were repaired\n";
    } else cout << "Caterpillars are ok\n";
}

void ControlSystem::rotate(MoveSystem& movesystem) {
    cout << "Starting rotation\n";
    movesystem.rotate();
}

void Cap::commandgo(RadiolocationSystem& radio, Mechanic& mechanic) {
    cout << "Cap: start the machine moving\n";
    radio.translate_command(1, mechanic);
}

void Cap::command(RadiolocationSystem& radio, Shooter& shooter) {
    char answ;
    cout << "Do you want to shoot?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y') {
        cout << "Cap: fire!\n";
        radio.translate_command(2, shooter);
    }
}

void Cap::commandstop(RadiolocationSystem& radio, Mechanic& mechanic) {
    cout << "Cap: stop the machine\n";
    radio.translate_command(3, mechanic);
}

void Shooter::rotatetower(TowerSystem& towersystem) {
    char answ;

    cout << "Do you want to rotate tower?\n";
    cin >> answ;
    do {
        cout << "Rotating tower\n";
        towersystem.rotate();
        cout << "Do you want to rotate it again?\n";
        cin >> answ;
    } while (answ == 'y' || answ == 'Y');
}

void Shooter::aim(TowerSystem& towersystem) {
    cout << "Setting the aim\n";
    towersystem.aim();
}

void Shooter::shoot(Tank& tank) {
    if (tank.radiolocationsystem.commands == "shoot") {
        tank.towersystem.shoot();
    }
}

void TowerSystem::rotate() {
    if (angle < 360) {
        cout << "The tower was rotated on 20 degrees\n";
        angle += 20;
    } else {
        cout << "Rotating tower in other way\n";
        angle = 0;
    }
}

void TowerSystem::aim() {
    cout << "Please enter x axis: ";
    cin >> x;
    cout << "\nPlease enter y axis: ";
    cin >> y;
    cout << "\n -- The aim was set on: " << x << " - " << y << endl;
    bool state = true;
    cout << "Waiting for the cap\n";
}

void TowerSystem::shoot() {
    int r = random(0, 100);
    if (r%15 == 0) cout << "You missed\n";
    else cout << "Success\n";
}

int main() {
    Tank tank("Tank01");
    Cap cap("Ricky Martin");
    Mechanic mechanic("Darren Criss");
    Shooter shooter("Nathan Lane");
    char answ;

    mechanic.check_fuel(tank.fuelsystem);
    cap.commandgo(tank.radiolocationsystem, mechanic);
    mechanic.fuel_supply(tank);
    mechanic.power_on(tank);

    cout << "Do you want to turn?\n";
    cin >> answ;
    do {
        mechanic.rotate(tank);
        cout << "Once again?\n";
        cin >> answ;
    } while (answ == 'y' || answ == 'Y');

    shooter.rotatetower(tank.towersystem);
    shooter.aim(tank.towersystem);
    cap.command(tank.radiolocationsystem, shooter);
    shooter.shoot(tank);
    
    war(tank);
    mechanic.repair_c(tank.movesystem);
    cap.commandstop(tank.radiolocationsystem, mechanic);
    mechanic.stop(tank);

    return 0;
}
