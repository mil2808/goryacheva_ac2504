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

int main()
{
    Pipe pipe1;
    bool exist_pipe = false;
    CS CS1;
    bool exist_cs = false;

    addpipe(pipe1, exist_pipe);
    showpipe(pipe1, exist_pipe);
    editpipe(pipe1, exist_pipe);

    return 0;
}


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
        else if (value <= 0)
        {
            cin.ignore(1000, '\n');
            cout << "Value must be positive.\n";
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
        else if (value <= 0)
        {
            cin.ignore(1000, '\n');
            cout << "Value must be positive.\n";
        }
        else
        {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

string inputstring(string text)
{
    string value;
    while (true)
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

void addpipe(Pipe& pipe1, bool& exist_pipe)
{
    cout << "\nEnter pipe data:\n";
    pipe1.name_p = inputstring("Name: ");

    pipe1.lenght = inputdouble("Lenght in km: ");

    pipe1.diam = inputint("Diametr in mm: ");

    pipe1.repair = inputyesno("Is it under repair?");

    exist_pipe = true;
    cout << "Pipe added.\n";
}

void showpipe(Pipe& pipe1, bool& exist_pipe)
{
    if (!exist_pipe)
    {
        cout << "No pipe yet.\n";
            return;
    }
    cout << "Pipe: " << pipe1.name_p << "\n";
    cout << "Lenght: " << pipe1.lenght << "\n";
    cout << "Diametr: " << pipe1.diam << "\n";
    cout << "In ripair: " << (pipe1.repair ? "yes" : "no") << "\n";
}
void editpipe(Pipe& pipe1, bool& exist_pipe)
{
    if (!exist_pipe)
    {
        cout << "No pipe yet. Add it first. \n";
        return;
    }
    cout << "Now in repair: " << (pipe1.repair ? "yes" : "no") << "\n";
    pipe1.repair = inputyesno("Set to repair");
    cout << "Done \n";

}
void addcs(CS& CS1, bool& exist_cs)
{
    cout << "Enter cs data: \n";
    CS1.name_cs = inputstring("Name: ");

    CS1.amount_ws = inputint("Total number of shops: ");

    CS1.amount_ws_in_prog = inputint("Shops working now: ");
    while (CS1.amount_ws_in_prog > CS1.amount_ws)
    {
        cout << "CS1.amount_ws" << CS1.amount_ws << ".\n";
        CS1.amount_ws_in_prog = inputint("Shops working now: ");
    }
    CS1.class_cs = inputstring("Station class: ");

    exist_cs = true;
    cout << "CS added.\n";
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
    Pipe pipe1;
    bool exist_pipe = false;
    CS CS1;
    bool exist_cs = false;

    addpipe(pipe1, exist_pipe);
    showpipe(pipe1, exist_pipe);
    editpipe(pipe1, exist_pipe);

    return 0;
}
