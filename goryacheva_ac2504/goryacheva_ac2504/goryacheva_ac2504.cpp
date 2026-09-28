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
        else if (value < 0)
        {
            cout << "Value must be positive.\n";
        }
        else
        {
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
            cout << "Value must be positive.\n";
        }
        else
        {
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
        getline(cin >> ws, value);
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
        getline(cin >> ws, value);
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

void showcs(CS& CS1, bool& exist_cs)
{
    if (!exist_cs)
    {
        cout << "No CS yet";
        return;
    }
    cout << "CS:" << CS1.name_cs << "\n";
    cout << "Shops total:" << CS1.amount_ws << "\n";
    cout << "Shops working:" << CS1.amount_ws_in_prog << "\n";
    cout << "Class:" << CS1.class_cs << "\n";
}

void startshop(CS& CS1)
{
    if (CS1.amount_ws_in_prog == CS1.amount_ws)
    {
        cout << "All shops already working.\n";
    }
    else
    {
        CS1.amount_ws_in_prog++;
        cout << "Shop started. Working: " << CS1.amount_ws_in_prog << "/" << CS1.amount_ws << "\n";
    }
}

void stopshop(CS& CS1)
{
    if (CS1.amount_ws_in_prog <= 0)
    {
        cout << "No shops are working.\n";
    }
    else
    {
        CS1.amount_ws_in_prog--;
        cout << "Shop stopped. Working: " << CS1.amount_ws_in_prog << "/" << CS1.amount_ws << "\n";
    }
}
void editcs(CS& CS1, bool& exist_cs)
{
    if (!exist_cs)
    {
        cout << "No CS yet. Add it first.\n";
        return;
    }
    cout << "1. Start a shop\n";
    cout << "2. Stop a shop\n";
    int choice = inputint("Choice: ");

    if (choice == 1)
    {
        startshop(CS1);
    }
    else if (choice == 2)
    {
        stopshop(CS1);
    }
    else
    {
        cout << "Wrong choice.\n";
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
    Pipe pipe1;
    bool exist_pipe = false;
    CS CS1;
    bool exist_cs = false;
    int option;
    while (true)
    {
        menu();
        option = inputint("\nSelect one of the menu items: ");

        if (option == 1) addpipe(pipe1,exist_pipe);
        else if (option == 2) addcs(CS1, exist_cs);
        else if (option == 3) { showcs(CS1, exist_cs); showpipe(pipe1, exist_pipe); }
        else if (option == 4) editpipe(pipe1, exist_pipe);
        else if (option == 5) editcs(CS1, exist_cs);
 //       else if (option == 6) save(pipe1, exist_pipe, CS1, exist_cs);
 //       else if (option == 7) load(pipe1, exist_pipe, CS1, exist_cs);
        else if (option == 0) break;
        else cout << "Wrong menu item.\n";
    }
    return 0;
}
