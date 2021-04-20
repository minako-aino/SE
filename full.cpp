#include <iostream>
#include <string>
#include "windows.h"
//#include "objects.h"
//#include "functions.h"

using namespace std;

class GameBoy;

class Cartridge{
	public:
	string name;
	float capacity;
};

class EnergySystem{
	public:
	bool state = false;
	int energy_perc = 90;
	string details;
	void check_state();
};

class SoundSystem{
	bool state = false;
	float power;
	unsigned short int volume_perc = 20;
	
	public:
		void set_perc(int volume);
};

class Display{
	string size;
	float diagonal;
	float frame_scan;
	float horizontal_scan;
	
	unsigned short int saturation_state;
	
	public:
		bool state = false;
		void change_saturation(int saturation);
		void show_picture();	
};

class CPU{
	// memory
	int video_mem;
	int main_mem;
	// hardware
	unsigned short int bit_depth;
	float clock_frequency;
	Cartridge cartridge;
	
	public:
		void read_cartridge();	
};

class ControlSystem{
	public:
	void power_on(Display display);
	void power_off(Display display);
	bool check_cartridge(GameBoy gameboy);
	void set_volume(SoundSystem sound, int value);
	void set_saturation(Display display, int value);
	void connect_cartridge();
	void disconnect_cartridge();
	void get_command(int answ, SoundSystem sound);
	void game();
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
		
};

void EnergySystem::check_state(){
	if (energy_perc > 5){
		state = true;	
	} else{
		cout << "Low battery\n";	
	}
}

void SoundSystem::set_perc(int volume){
	if (0 <= volume && volume <= 100){
		volume_perc = volume;
	}	
}

void Display::change_saturation(int saturation){
	if (0 <= saturation && saturation <= 100){
		saturation_state = saturation;
		cout << "Volume was changed\n";
	}
}

void Display::show_picture(){
	cout << "Picture is on\n";
}

void CPU::read_cartridge(){
	cout << "Cartridge " << cartridge.name << " was read\n";
}

void ControlSystem::power_on(Display display){
	cout << "Welcome!\n";
	display.state = true;
}

void ControlSystem::power_off(Display display){
	cout << "Bye\n";
	display.state = false;
}

// äîïèñàòü íåìíîãî ïîçæå
bool ControlSystem::check_cartridge(GameBoy gameboy){
	if (gameboy.cartr_state == true){
		cout << "Cartridge is on\n";
		return true;
	} else {
		cout << "Cartridge error\n";
		return false;
	}
}

void ControlSystem::set_volume(SoundSystem sound, int value){
	sound.set_perc(value);
}

void ControlSystem::set_saturation(Display display, int value){
	display.change_saturation(value);
}

void ControlSystem::connect_cartridge(){
	cout << "Cartridge was successfully mounted\n";
}

void ControlSystem::disconnect_cartridge(){
	cout << "Cartridge was successfully unmounted\n";
}

void ControlSystem::get_command(int value, SoundSystem sound){
	int answ;
	cout << "What do you want to do?\n";
	cout << "1. START GAME\n2. CHANGE VOLUME\n3. CHANGE SATURATION\n0. EXIT\n\n";
	cout << "ENTER > ";
	cin >> answ;
	switch(answ){
		case 1: {
			
			break;}
		case 2: {
			cin >> value;
			set_volume(sound, value);
			break;
		}
		case 3:{
			
			break;
		}
	}
}

void ControlSystem::game(){
	
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
	energy_sys.state = true;
	state = true;
	cout << "Gameboy is on\n";
}

int main(){
	char a;
	GameBoy gameboy;
	cout << "Do you want to connect a cartridge?\n";
	cin >> a;
	if (a == 'y' || a == 'Y'){
		gameboy.set_cartridge_state();
		if (gameboy.cartr_state == true){
			cout << "Do you want to power on your GameBoy?\n";
			cout << "ENTER > ";
			cin >> a;
			if ((a == 'y' || a == 'Y') && (gameboy.control_system.check_cartridge(gameboy) == true)){
				gameboy.power_on();
				gameboy.control_system.power_on(gameboy.display);	
			}
		}
	}
	return 0;
}	
