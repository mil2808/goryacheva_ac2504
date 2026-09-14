#include <iostream>
#include <string>
using namespace std; 

struct Pipe 
{
    string name_p;
    int diam;
    double lenght;
    bool repair;
};

struct CS
{
    string name_cs;
    int amount_ws;
    int amount_ws_in_prog;
    string class_cs;
};

bool exist_pipe = false;
bool exist_cs = false;
Pipe pipe1;
CS CS1;

int inputint(string text)
{
    int value;
    while (true)
    {
        cout << text;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "not number.\n";
        }
        else
        {
            cin.ignore(1000, '\n');
            return value;

        }

    } 
}

double inputdouble(string text)
{
    double value;
    while (true)
    {
        cout << text;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "not number. \n";
        }
        else
        {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

string inputstrind(string text)
{
    string value;
    while (true);
    {
        cout << text;
        getline(cin, value);
        if (value == "")
        {
            cout << "Cannot be empty. \n";
        }
        else
        {
            return value;
        }
    }
}

bool inputyesno(string text)
{
    string value;
    while (true)
    {
        cout << text << " y/n ";
        getline(cin, value);
        if (value == "y") return true;
        if (value == "n")  return false;
        cout << "Please type y or n.\n";
    }
}

void menu()
{
    cout << "1. add pipe\n";
    cout << "2. add cs\n";
    cout << "3. view all objects\n";
    cout << "4. edit pipe\n";
    cout << "5. edit cs\n";
    cout << "6. save\n";
    cout << "7. load\n";
    cout << "0. exit\n";
}

int main()
{

}

