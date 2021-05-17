#pragma once
//#include <regex>
//#include <any>

using namespace std;

class Form;
class Webpage;

class Box {
    public:
        string text;
        void emerge(string message);
};

class Button{
    public:
        // за замовчуванням кнопка не натиснута
        bool state = false;
};

// наслідування
class DialogBox: public Box{
    public:
        int inputfield;
        Button SendButton;
        void fill(int number);
        bool empty(int number);
};

// наслідування
class Message: public Box{
    public:
        Button closebutton;
        string message;
};

class InteractionSystem{
    public:
        Message message;
        Button closebutton;
        void viewmessage(int mes);
};

class Validator{
    public:
        string name;
        string inputfield();
        // регулярний вираз для номеру телефону
        string phone = "[[:digit:]]{2}-[[:digit:]]{3}-[[:digit:]]{3}-[[:digit:]]{4}";
        // регулярний вираз для пошти
        string email = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
}; 

class ValidationSystem{
    public:
        Validator validator;
        // перевірка даних форми
        bool check(Form& form);
        // перевірка даних із діалогового вікна
        bool checkcapcha(DialogBox& box, int capcha);
};

class Form{
    public:
        string name;
        string phone;
        string email;
        string address;
        bool empty();
        bool full();
};

class StyleSystem{
    public:
        string colour;
        string texttype;
        string background;
        void viewstyle();
};

class Markup{
    public:
        int position;
        int size;
        StyleSystem style;
        string text;
        bool load_state = false;
        DialogBox dialogbox;

        void load();
        void makout();
        void show_content();
        void close();
};

class Ajax{
    public:
        int state;
        bool senddata(Webpage& webpage);
};

class DataExchangeSystem{
    public:
        Form form;
        DialogBox box;
        Button sendbutton;
        Ajax ajax;
};

class User{
    string name;
    public:
        User(string str) { name = str; }
        void Openpage(Webpage& webpage);
        void Closepage(Webpage& webpage);
        void Viewpage(Webpage& webpage);
        bool ClickButton(Webpage& webpage);
        void FilloutForm(Webpage& webpage);
        void FillPopup(Webpage& webpage, int number);
};

class Webpage{
    public:
        string welcometext = "Welcome!";
        Markup markup;
        DataExchangeSystem dataexchange;
        ValidationSystem valid;
        InteractionSystem interaction;
        string state;
};
