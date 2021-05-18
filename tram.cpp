#include <iostream>
#include <string>
#include <vector>
#include "tram.h"

using namespace std;

int random(int min, int max) {
    int num = min + rand() % (max - min + 1);
    return num;
}

void Driver::OpenDoor(Tram& tram){
    tram.body.primetime();
    cout << "D: pressing the button to open the door\n";
    tram.controlsys.buttons[2].state = true;
}

void Driver::CloseDoor(Tram& tram){
    tram.controlsys.buttons[2].state = false;
    tram.controlsys.buttons[3].state = true;
    cout << "D: pressing the button to close the door\n";
}

void Driver::Go(Tram& tram){
    cout << "D: started moving\n";
    tram.controlsys.controller.position = 1;
    tram.controlsys.buttons[0].state = true;
    cout << "D: moving in " << tram.controlsys.buttons[0].appointment << " mode\n";
}

void Driver::ChangeSpeed(Tram& tram){
    cout << "Enter the speed: ";
    cin >> tram.move.engine.speed;
    tram.controlsys.controller.position = 2;
}

void Driver::OnFan(Tram& tram){
    cout << "D: turning on fans\n";
    tram.fanheat.fan.rotate(true);
}

void Driver::OffFan(Tram& tram){
    cout << "D: turning off fans\n";
    tram.fanheat.fan.rotate(false);
}

void Driver::OnHeat(Tram& tram){
    cout << "D: turning on heat\n";
    tram.fanheat.heater.heat(true);
}

void Driver::OffHeat(Tram& tram){
    cout << "D: turning off heat\n";
    tram.fanheat.heater.heat(false);
}

void Driver::Stop(Tram& tram) {
    cout << "D: started moving\n";
    tram.controlsys.controller.position = 0;
    tram.controlsys.buttons[0].state = false;
    
    cout << "D: moving in " << tram.controlsys.buttons[0].appointment << " mode\n";
}

void Heater::heat(bool stat) { state = stat; }

void Fan::rotate(bool stat) { state = stat; }

int ElectroSystem::givecurrent(int state){
    current = state;
    return current;
}

bool Door::open() {
    cout << "The door is opened\n";
}

void Door::close(){
    cout << "The door is closed\n";
}

bool Passenger::Goon(BodyWork& body){
    if (body.passengers_count < 100) {
        cout << "New passenger is in\n";
        body.passengers_count++;
        return true;        
    } else  cout << "There is no left space\nYou`d better wait for the next tram\n";
    return false;   
}

bool Passenger::HoldOn() {
    int chance = random(0, 1);
    if (chance == 1) {
        cout << "P: the chance of falling is too high. I`d better hold on\n";
        return true;
    } else cout << "P: I don`t want hold on\n"; 
	return false;
}

bool Passenger::Sit(BodyWork& body){
    if (body.sitting_passengers < 64) {
        cout << "P: I`d like to sit down\n";
        body.sitting_passengers++;
    } else cout << "There is no free places to sit\n";
}

bool Passenger::haveticket(PaySystem& pay){
    int rand = random(1,5);
    int sum = 0;
    int money;
    
    if (rand == 5 && !ticket) {
    	cout << "P: I need to buy a ticket\n";
        if (pay.give_money_ticket(pay.checkmoney())) ticket = true;
    } else cout << "P: I won`t buy a ticket today\n";
}

int PaySystem::checkmoney(){
    int money;
    cout << "Price for the ticket is 5 h\nPlease use 1h (1), 2h (2), 5h (3), 10h (10) banknotes\n";
    while (sum < 5) {
        	cout << "Enter > ";	
        	cin >> money;
        	switch (money) {
        		case 1: {
        			sum++;
					break; }
				case 2: {
					sum = sum + 2;
					break; }
				case 5: {
					sum += 5;
					break; }
				case 10: {
					sum += 10;
					break;}
				defaul: cout << "Wrong input\n"; 
			}
            cout << "Current sum: " << sum << endl;
		}
    return sum;    
}

void Passenger::Goout(BodyWork& body){
    cout << "Passenger has left\n";
    body.passengers_count--;
}

bool PaySystem::give_money_ticket(int sum) {
    if (sum != 5) {
            cout << "Your rest: " << sum-5 << endl;
    }
    return true;
}

bool Cashier::checkticket(Passenger& passenger) {
    if (passenger.ticket != 223) {
        cout << "C: You don`t have a ticket, you need to buy one\n";
        return false;
    } else {
        cout << "C: Everything is ok\nHave a nice ride\n";
        return true;
    }
}

void BodyWork::primetime(){
    passengers_count = random(1, 100);
    do {
        sitting_passengers = random(1, 64);
    } while(sitting_passengers > passengers_count);    
}

void MoveSystem::move(){
    engine.rotate(100);
}

void Engine::rotate(int rot_speed){
    cout << "Engine rotation speed:" << rot_speed << endl;
}

int main() {
    Tram tram;
    Driver driver("Adam Driver");
    Passenger passenger;
    bool tmp;
    int check_ticket = random(0, 1);
    tram.fanheat.temperature = random(10, 30);

    driver.OpenDoor(tram);
    if (tram.controlsys.buttons[2].state && tram.body.door.open()) {
        tmp = passenger.Goon(tram.body);
        driver.CloseDoor(tram);
        if (tram.controlsys.buttons[3].state) tram.body.door.close();
    }

    if (tmp) {
        driver.Go(tram);
        if (tram.controlsys.buttons[0].state && tram.controlsys.controller.position == 1) {
            cout << "Electricity power: " << tram.electrosys.givecurrent(320) << endl;
            tram.move.move();
        }

        driver.ChangeSpeed(tram);
        if (tram.controlsys.controller.position == 2) {
            cout << "Electricity power: " << tram.electrosys.givecurrent(350) << endl;
            tram.move.engine.rotate(200);
            cout << "Current speed: " << tram.move.engine.speed << endl;
        }

        if (tram.move.engine.speed > 0) {
            passenger.HoldOn();
            passenger.ticket = passenger.haveticket(tram.pay);
            passenger.Sit(tram.body);
        }

        if (tram.fanheat.temperature > 25) {
            cout << "D: it seems to be too hot\n";
            driver.OnFan(tram);
            driver.OffHeat(tram);
        } else if (tram.fanheat.temperature < 16) {
            cout << "D: it seems to be too cold\n";
            driver.OnHeat(tram);
            driver.OffFan(tram);
        }

        if(check_ticket == 1) {
            cout << "! Cashier is here, time to check your ticket\n";
            if (!tram.pay.cashier.checkticket(passenger)) {
                if (tram.pay.give_money_ticket(tram.pay.checkmoney())) passenger.ticket = true;
            } 
        } else {
            cout << "No checks today\n";
        }
        
        driver.Stop(tram);
        if(tram.controlsys.buttons[0].state = false && tram.controlsys.controller.position == 0) {
            cout << "Electricity power: " << tram.electrosys.givecurrent(50) << endl;
            tram.move.engine.rotate(0);
        }

        driver.OpenDoor(tram);
        if (tram.controlsys.buttons[2].state && tram.body.door.open()) {
            passenger.Goout(tram.body);
            driver.CloseDoor(tram);
            if (tram.controlsys.buttons[3].state) tram.body.door.close();
        }
    }

    return 0;
}
