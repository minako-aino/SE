#include <iostream>
#include <string>
#include <regex>
#include "webpage.h"
#define GET_VARIABLE_NAME(Variable) (#Variable)

using namespace std;

int random(int min, int max) {
    int num = min + rand() % (max - min + 1);
    return num;
}

 // відкрити сторінку
void User::Openpage(Webpage& webpage){
    cout << "Opening page\n";
    webpage.markup.load();
    Viewpage(webpage);
}

// переглянути вміст
void User::Viewpage(Webpage& webpage){
    cout << "**" << webpage.welcometext << "**";
    webpage.markup.show_content();
}

// заповнення форми
void User::FilloutForm(Webpage& webpage){
    if(webpage.dataexchange.form.full()) cout << "Sending the result\n";
}

// натиснути на кнопку
bool User::ClickButton(Webpage& webpage){
    char answ;
    cout << "Do you want to send the form?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y') {
        return webpage.dataexchange.ajax.senddata(webpage);
    } else return false;
}

// закрити сторінку
void User::Closepage(Webpage& webpage){
    cout << "Closing the page\n";
    webpage.markup.close();
}

bool Ajax::senddata(Webpage& webpage){
    // можлива помилка на одній із сторін
    int number = random(1,100);
    if (webpage.valid.check(webpage.dataexchange.form) && number%27 != 0) {
        webpage.interaction.viewmessage(1);
        return true;
    } else {
        webpage.interaction.viewmessage(2);
        webpage.dataexchange.form.empty();
        return false;
    }
}

// очищення форми
bool Form::empty(){
    name = "N/A";
    phone = "N/A";
    email = "N/A";
    address = "N/A";
    cout << "The form was cleared\n";
    return true;
}

void InteractionSystem::viewmessage(int mes) {
    switch(mes){
        case 1: {
            message.message = "Success!\nThe form was send\n";
            break; }
        case 2: {
            message.message = "An error occured\n";
            break;
        }
    }

    message.emerge(message.message);
}

// виведення повідомлення
void Box::emerge(string message) {
    cout << message;
}

 // введення даних у діалоговому вікні
void User::FillPopup(Webpage& webpage, int number){
    webpage.dataexchange.box.fill(number);
}

// введення даних у діалогове вікно
void DialogBox::fill(int number){
    cout << "Please enter capcha in order to make sure you are not a robot\n";
    cout << number << endl;
    SendButton.state = true;
}

// заповнення форми
bool Form::full(){
    char answ;

    cout << "\n** Please enter your name **\n";
    cin >> name;
    cout << "** Please enter your phone **\n";
    cin >> phone;
    cout << "** Please enter your email **\n";
    cin >> email;
    cout << "** Please enter your address (city name) **\n";
    cin >> address;
}


bool ValidationSystem::check(Form& form){
    regex r1(validator.phone);
    regex r2(validator.email);

    // довжина імені була зменшена, оскільки 50 символів забагато
    if (form.name.size() < 2) {
        cout << "Your name is too short\n";
        return false;
    }

    if (!regex_match(form.phone, r1)) {
        cout << "Wrong phone format\nTry +xx-xxx-xxx-xxxx\n";
        return false;
    }

    if(!regex_match(form.email, r2)) {
        cout << "Wrong email format\n";
        return false;
    }
	
	if (form.name.size() < 3) {
        cout << "Your city name is too short\n";
        return false;
    }
    return true;
}

bool ValidationSystem::checkcapcha(DialogBox& box, int capcha){
	cin >> box.inputfield;
    if (box.inputfield == capcha) {
        cout << "Verification was successful\n";
        return true;
    } else {
        cout << "Verification was failed\n";
        return false;
    }
}

// завантаження сторінки
void Markup::load(){
    load_state = true;
    cout << "Page was loaded\n";
}

// закриття сторінки
void Markup::close(){
    load_state = false;
    cout << "Page was closed\n";
}

// виведення даних на сторінці
void Markup::show_content(){
    style.viewstyle();
}

// вивести підготовлений контент сторінки
void StyleSystem::viewstyle(){
    string colours[6] = {"green", "red", "blue", "yellow", "black", "white"};
    string types[4] = {"Calibri", "Times New Roman", "Consolas", "Cambria"};
    
    colour = colours[random(0,5)]; 
    texttype = types[random(0,3)];
    background = colours[random(0,5)];

    cout << "\n** Page style:" 
    << "Text colour: " << colour << ", \n" 
    << "Text type: " << texttype << ", \n" 
    << "Background colour: " << background << " **\n";
}

int main(){
    Webpage webpage;
    User user("Sasha");
    int number;
	
    // користувач відкриває сторінку
	user.Openpage(webpage);
	
	do {
   		do {
            // заповнення форми
        	user.FilloutForm(webpage);
        // у випадку помики повторне введення даних
    	} while(!webpage.valid.check(webpage.dataexchange.form));
    
    	do{
    	    number = random(1000, 9999);
            // введення даних у діалогове вікно
        	user.FillPopup(webpage, number);
    	} while(!webpage.valid.checkcapcha(webpage.markup.dialogbox, number));
    // повторити у випадку помилки або якщо користувач вирішив не відправляти діючу форму	
	} while(!user.ClickButton(webpage));
	
    // після завершення робти користувач закриває сторінку
	user.Closepage(webpage);

    return 0;
}
