#include <iostream>
#include <string>
#include "windows.h"
//#include "objects.h"
//#include "functions.h"

using namespace std;

class GameBoy;
class User;

class Cartridge{
	public:
		float capacity;
		string name;
};

class EnergySystem{
	string details = "DC 3V 0.7 Âò";
	int quantity = 4;
	
	public:
		bool state = false;
		int energy_perc = 90;
		
		bool check_state();
};

class SoundSystem{
	float power = 0.1;
	
	public:
		bool state = false;
		int volume_perc = 20;
		
		void set_perc();
};

class Display{
	// hardware
	string size = "2.6''";
	string resolution = "160x144";
	float frame_scan = 9198;
	float horizontal_scan = 59.73;
	
	public:
		unsigned short int saturation_state = 50;
		bool state = false;
		
		void change_saturation();
		void show_picture();	
};

class CPU{
	// memory
	int video_mem = 8;
	int main_mem = 8;
	// hardware
	unsigned short int bit_depth = 8;
	float clock_frequency = 4.2;
	Cartridge cartridge;
	
	public:
		void read_cartridge();	
};

class ControlSystem{
	public:
		void power_on(Display& display);
		void power_off(Display& display);
		bool check_cartridge(GameBoy& gameboy);
		void set_volume(SoundSystem& sound);
		void set_saturation(Display& display);
		bool connect_cartridge(GameBoy& gameboy);
		bool disconnect_cartridge(GameBoy& gameboy);
		void get_command(GameBoy& gameboy, User& user);
		void game(GameBoy& gameboy);
};

class GameBoy{
	public:
		bool state = false;
		bool cartr_state = false;
		CPU cpu;
		Display display;
		Cartridge cartridge;
		EnergySystem energy_sys;
		SoundSystem sound_system;
		ControlSystem control_system;
		
		void set_cartridge_state();
		void power_on();
		void power_off();
};

class User{
	public:
		void press_power_button(GameBoy& gameboy);
		void press_volume_button(GameBoy& gameboy);
		void press_sat_button(GameBoy& gameboy);
		void put_cartridge(GameBoy& gameboy);
		void gaming(GameBoy& gameboy);
};

bool EnergySystem::check_state(){
	if (energy_perc > 5){
		state = true;
		cout << "Current battery state: " << energy_perc << "%\n"; 
		return true;	
	} else{
		cout << "Low battery\n";
		return false;	
	}
}

void SoundSystem::set_perc(){
	char ans;
	cout << "Raise volume (U|u)p or (D|d)own?\n";
	cout << "ENTER >> ";
	cin >> ans;
	switch(ans){
		case 'u':
		case 'U':{
			if (volume_perc < 100) {
				volume_perc += 5;
			} else {
				cout << "** It is already 100% **\n";
			}
			break;
		}
		case 'd':
		case 'D':{
			if (volume_perc > 0) {
				volume_perc -= 5;
			} else {
				cout << "** It is already 0% **\n";
			}
			break;
		}
	}
	cout << "** Volume: " << volume_perc << "% **\n";	
}

void Display::change_saturation(){
	char ans;
	cout << "Raise saturation (U|u)p or (D|d)own?\n";
	cout << "ENTER >> ";
	cin >> ans;
	switch(ans){
		case 'u':
		case 'U':{
			if (saturation_state < 100) {
				saturation_state += 5;
			} else {
				cout << "** It is already 100% **\n";
			}
				
			break;
		}
		case 'd':
		case 'D':{
			if (saturation_state > 0) {
				saturation_state -= 5;
			} else {
				cout << "** It is already 0% **\n";
			}
			break;
		}
	}
	cout << "** Saturation: " << saturation_state << "% **\n";		
}

void Display::show_picture(){
	cout << "Picture is on\n";
}

void CPU::read_cartridge(){
	cout << "Cartridge " << cartridge.name << " was read\n";
}

void ControlSystem::power_on(Display& display){
	cout << "** Welcome! **\n";
	display.state = true;
}

void ControlSystem::power_off(Display& display){
	cout << "** Bye **\n";
	display.state = false;
}

bool ControlSystem::check_cartridge(GameBoy& gameboy){
	if (gameboy.cartr_state == true){
		cout << "Cartridge is on\n";
		return true;
	} else {
		cout << "Cartridge error\n";
		return false;
	}
}

void ControlSystem::set_volume(SoundSystem& sound){
	sound.set_perc();
}

void ControlSystem::set_saturation(Display& display){
	display.change_saturation();
}

bool ControlSystem::connect_cartridge(GameBoy& gameboy){
	if (gameboy.cartr_state == true){
		cout << "Cartridge was successfully mounted\n";
		return true;
	} else {
		return false;
	}
}

bool ControlSystem::disconnect_cartridge(GameBoy& gameboy){
	if (gameboy.cartr_state == false){
		cout << "Cartridge was successfully unmounted\n";
		return true;
	} else {
		return false;
	}
}

void ControlSystem::get_command(GameBoy& gameboy, User& user){
	int answ;
	int vol_val;
	cout << "** What do you want to do? **\n";
	cout << "** 1. START GAME **\n** 2. CHANGE VOLUME **\n** 3. CHANGE SATURATION **\n** 0. EXIT **\n\n";
	do{
		cout << "ENTER > ";
		cin >> answ;
		switch(answ){
			case 1: {
				user.gaming(gameboy);
				break;}
			case 2: {
				user.press_volume_button(gameboy);
				break;
			}
			case 3:{
				user.press_sat_button(gameboy);
				break;
			}
			default:{
				power_off(gameboy.display);
				gameboy.power_off();
				break;
			}
		}
	} while (answ >= 1 && answ <= 3);
}

void ControlSystem::game(GameBoy& gameboy){
	cout << "** Welcome to " << gameboy.cartridge.name << " **\n";
	Sleep(5000);
}

void GameBoy::set_cartridge_state(){
	int a;
	cout << "Which one do you want to choose?\n";
	cout << "1. TETRIS\n2. KIRBY`S DREAM LAND\n3. FINAL FANTASY ADVENTURE\n4. CASTELVANIA: THE ADVENTURE\n5. DONKEY KONG\n0. NONE\n\n";
	cout << "ENTER > ";
	cin >> a;
	switch(a){
		case 1:{
			cartr_state = true;
			cartridge.name = "TETRIS";
			cartridge.capacity = 8;
			break;}
		case 2:{
			cartr_state = true;
			cartridge.name = "KIRBY`S DREAM LAND";
			cartridge.capacity = 12;
			break;}
		case 3:{
			cartr_state = true;
			cartridge.name = "FINAL FANTASY ADVENTURE";
			cartridge.capacity = 12;			
			break;}
		case 4:{
			cartr_state = true;
			cartridge.name = "CASTELVANIA: THE ADVENTURE";
			cartridge.capacity = 8;			
			break;}
		case 5:{
			cartr_state = true;
			cartridge.name = "DONKEY KONG";
			cartridge.capacity = 8;			
			break;}
		default:{
			cout << "None was choosen(\n";
			break;}
	}
}

void GameBoy::power_on(){
	cout << "Turning on...\n";
	Sleep(5000);
	if (energy_sys.check_state() == true){
		state = true;
		cout << "Gameboy is on\n";
	}
}

void User::press_power_button(GameBoy& gameboy){
	gameboy.power_on();
}

void User::press_volume_button(GameBoy& gameboy){
	gameboy.control_system.set_volume(gameboy.sound_system);
}

void User::press_sat_button(GameBoy& gameboy){
	gameboy.control_system.set_saturation(gameboy.display);
}

void User::put_cartridge(GameBoy& gameboy){
	gameboy.set_cartridge_state();
	cout << "*" << gameboy.cartridge.name << " was put*\n";
	
}

void User::gaming(GameBoy& gameboy){
	gameboy.control_system.game(gameboy);
	cout << "*gaming*\n";
}

void GameBoy::power_off(){
	cout << "Turning off...\n";
	Sleep(5000);
	state = false;
	cout << "Gameboy is off\n";
}

int main(){
	char a;
	User user;
	GameBoy gameboy;
	cout << "Do you want to connect a cartridge?\n";
	cin >> a;
	if (a == 'y' || a == 'Y'){
		user.put_cartridge(gameboy);
		if (gameboy.cartr_state == true){
			cout << "Do you want to power on your GameBoy?\n";
			cout << "ENTER > ";
			cin >> a;
			if ((a == 'y' || a == 'Y') && (gameboy.control_system.check_cartridge(gameboy) == true)){
				user.press_power_button(gameboy);
				gameboy.control_system.power_on(gameboy.display);
				gameboy.control_system.connect_cartridge(gameboy);
				gameboy.control_system.get_command(gameboy, user);
			}
		}
	}
	return 0;
}	
