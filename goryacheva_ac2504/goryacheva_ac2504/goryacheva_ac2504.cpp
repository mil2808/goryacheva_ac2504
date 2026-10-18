#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std; 

struct Pipe 
{
    int id;
    string name_p;
    int diam;
    double lenght;
    bool repair;
};

struct CS
{
    int id;
    string name_cs;
    int amount_ws;
    int amount_ws_in_prog;
    string class_cs;
};

void writelog(const string& text)
{
    ofstream file("log.txt", ios::app);
    if (file)
    {
        file << text << "\n";
    }
}

int inputint(string text, int min_value)
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
            cout << "Not a number.\n";
            writelog("Input error: not a number (expected int)");
            continue;
        }
        cin.ignore(1000, '\n');
        if (value < min_value)
        {
            cout << "Value must be at least " << min_value << ".\n";
            writelog("Input error: int " + to_string(value) + " is less than " + to_string(min_value));
            continue;
        }
        writelog("Input int: " + to_string(value));
        return value;
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
        cin.ignore(1000, '\n');
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Not a number.\n";
            writelog("Input error: not a number (expected double)");
            continue;
        }
        if (value <= 0)
        {
            cout << "Value must be positive.\n";
            writelog("Input error: double " + to_string(value) + " is not positive");
            continue;
        }
        writelog("Input double: " + to_string(value));
        return value;
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
            cout << "Cannot be empty.\n";
            writelog("Input error: empty string");
            continue;
        }
        writelog("Input string: " + value);
        return value;
    }
}

bool inputyesno(string text)
{
    string value;
    while (true)
    {
        cout << text << " y/n ";
        getline(cin >> ws, value);
        if (value == "y")
        {
            writelog("Input y/n: y");
            return true;
        }
        if (value == "n")
        {
            writelog("Input y/n: n");
            return false;
        }
        cout << "Please type y or n.\n";
        writelog("Input error: expected y or n, got: " + value);
    }
}

void addpipe(vector<Pipe>& pipes, int& pipe_id)
{
    Pipe p;
    cout << "\nEnter pipe data:\n";
    p.id = pipe_id;
    p.name_p = inputstring("Name: ");
    p.lenght = inputdouble("Lenght in km: ");
    p.diam = inputint("Diametr in mm: ", 1);
    p.repair = inputyesno("Is it under repair?");

    pipes.push_back(p);
    pipe_id++;
    cout << "Pipe added. Id = " << p.id << "\n";
    writelog("Pipe added, id = " + to_string(p.id) + ", name = " + p.name_p);
}

int findpipe(const vector<Pipe>& pipes, int id)
{
    for (size_t i = 0; i < pipes.size(); i++)
    {
        if (pipes[i].id == id) return (int)i;
    }
    return -1;
}

void showpipe(const Pipe& pipe1)
{
    cout << "Name id: " << pipe1.id << "\n";
    cout << "Name pipe: " << pipe1.name_p << "\n";
    cout << "Lenght: " << pipe1.lenght << "\n";
    cout << "Diametr: " << pipe1.diam << "\n";
    cout << "In ripair: " << (pipe1.repair ? "yes" : "no") << "\n";
}

void showallpipes(const vector<Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        return;
    }
    for (size_t i = 0; i < pipes.size(); i++)
    {
        showpipe(pipes[i]);
    }
}

int choosepipe(const vector<Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        writelog("Pipe select: no pipes in the list");
        return -1;
    }
    showallpipes(pipes);
    int index = findpipe(pipes, inputint("Enter pipe id: ", 1));
    if (index == -1)
    {
        cout << "Pipe with this id not found.\n";
        writelog("Pipe select: id not found");
    }
    return index;
}

void editpipe(vector<Pipe>& pipes)
{
    int index = choosepipe(pipes);
    if (index == -1) return;

    cout << "Now in repair: " << (pipes[index].repair ? "yes" : "no") << "\n";
    pipes[index].repair = inputyesno("Set to repair");
    cout << "Done \n";
    writelog("Pipe id " + to_string(pipes[index].id) + " edited");
}

void deletepipe(vector<Pipe>& pipes)
{
    int index = choosepipe(pipes);
    if (index == -1) return;

    writelog("Pipe id " + to_string(pipes[index].id) + " deleted");
    pipes.erase(pipes.begin() + index);
    cout << "Pipe deleted.\n";
}

double unsed_p(const CS& cs)
{
    return (cs.amount_ws - cs.amount_ws_in_prog) * 100.0 / cs.amount_ws;
}

void addcs(vector<CS>& stations, int& CS_id)
{
    CS cs;
    cout << "Enter cs data: \n";
    cs.id = CS_id;
    cs.name_cs = inputstring("Name: ");
    cs.amount_ws = inputint("Total number of shops: ", 1);
    cs.amount_ws_in_prog = inputint("Shops working now: ", 0);
    while (cs.amount_ws_in_prog > cs.amount_ws)
    {
        cout << "Cannot be more than " << cs.amount_ws << ".\n";
        writelog("Input error: working shops more than total");
        cs.amount_ws_in_prog = inputint("Shops working now: ", 0);
    }
    cs.class_cs = inputstring("Station class: ");

    stations.push_back(cs);
    CS_id++;
    cout << "CS added. Id = " << cs.id << "\n";
    writelog("CS added, id = " + to_string(cs.id) + ", name = " + cs.name_cs);
}

int findcs(const vector<CS>& stations, int id)
{
    for (size_t i = 0; i < stations.size(); i++)
    {
        if (stations[i].id == id) return (int)i;
    }
    return -1;
}

void showcs(const CS& CS1)
{
    cout << "Name id:" << CS1.id << "\n";
    cout << "Name CS:" << CS1.name_cs << "\n";
    cout << "Shops total:" << CS1.amount_ws << "\n";
    cout << "Shops working:" << CS1.amount_ws_in_prog << "\n";
    cout << "Unused shops:" << unsed_p(CS1) << "%\n";
    cout << "Class:" << CS1.class_cs << "\n";
}

void showallcs(const vector<CS>& stations)
{
    if (stations.empty())
    {
        cout << "No CS yet.\n";
        return;
    }
    for (size_t i = 0; i < stations.size(); i++)
    {
        showcs(stations[i]);
    }

}

int choosecs(const vector<CS>& stations)
{
    if (stations.empty())
    {
        cout << "No CS yet.\n";
        writelog("CS select: no CS in the list");
        return -1;
    }
    showallcs(stations);
    int index = findcs(stations, inputint("Enter CS id: ", 1));
    if (index == -1)
    {
        cout << "CS with this id not found.\n";
        writelog("CS select: id not found");
    }
    return index;
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
void editcs(vector<CS>& stations)
{
    int index = choosecs(stations);
    if (index == -1) return;

    cout << "1. Start a shop\n";
    cout << "2. Stop a shop\n";
    int choice = inputint("Choice: ", 1);

    if (choice == 1)
    {
        startshop(stations[index]);
        writelog("CS id " + to_string(stations[index].id) + ": start shop");
    }
    else if (choice == 2)
    {
        stopshop(stations[index]);
        writelog("CS id " + to_string(stations[index].id) + ": stop shop");
    }
    else
    {
        cout << "Wrong choice.\n";
        writelog("Edit CS: wrong choice " + to_string(choice));
    }
}

void deletecs(vector<CS>& stations)
{
    int index = choosecs(stations);
    if (index == -1) return;

    writelog("CS id " + to_string(stations[index].id) + " deleted");
    stations.erase(stations.begin() + index);
    cout << "CS deleted.\n";
}

int inputpercent(string text, int min_value)
{
    int value = inputint(text, min_value);
    while (value > 100)
    {
        cout << "Cannot be more than 100.\n";
        writelog("Input error: percent more than 100");
        value = inputint(text, min_value);
    }
    return value;
}

void searchcs(const vector<CS>& stations)
{
    cout << "1. Search by name\n";
    cout << "2. Search by percent of unused shops\n";
    int choice = inputint("Choice: ", 1);
    int count = 0;

    if (choice == 1)
    {
        string name = inputstring("Name (or part of name): ");
        for (size_t i = 0; i < stations.size(); i++)
        {
            if (stations[i].name_cs.find(name) != string::npos)
            {
                showcs(stations[i]);
                count++;
            }
        }
    }
    else if (choice == 2)
    {
        int from = inputpercent("Percent of unused shops from (0-100): ", 0);
        int to = inputpercent("Percent of unused shops to (" + to_string(from) + "-100): ", from);
        for (size_t i = 0; i < stations.size(); i++)
        {
            double percent = unsed_p(stations[i]);
            if (percent >= from && percent <= to)
            {
                showcs(stations[i]);
                count++;
            }
        }
    }
    else
    {
        cout << "Wrong choice.\n";
        writelog("Search CS: wrong choice " + to_string(choice));
        return;
    }

    if (count == 0) cout << "Nothing found.\n";
    writelog("Search CS: found " + to_string(count));
}

void savepipe(vector<Pipe>& pipes, int next_id)
{
    if (pipes.empty())
    {
        cout << "No pipe to save.\n";
        writelog("Save pipes: no pipes to save");
        return;
    }
    string file_name = inputstring("File name to save pipes: ");
    ofstream file(file_name);
    if (!file)
    {
        cout << "Cannot open file for writing.\n";
        writelog("Save pipes: cannot open file " + file_name);
        return;
    }
    file << next_id << "\n";
    file << pipes.size() << "\n";
    for (size_t i = 0; i < pipes.size(); i++)
    {
        file << pipes[i].id << "\n";
        file << pipes[i].name_p << "\n";
        file << pipes[i].lenght << "\n";
        file << pipes[i].diam << "\n";
        file << pipes[i].repair << "\n";
    }

    file.close();
    cout << "Pipes saved to " << file_name << "\n";
    writelog("Pipes saved to " + file_name + ": " + to_string(pipes.size()) + " pipe(s)");
}

void savecs(CS& CS1, bool exist_cs)
{
    if (!exist_cs)
    {
        cout << "No CS to save.\n";
        return;
    }

    ofstream file("cs.txt");
    if (!file)
    {
        cout << "Cannot open file for writing.\n";
        return;
    }

    file << CS1.name_cs << "\n";
    file << CS1.amount_ws << "\n";
    file << CS1.amount_ws_in_prog << "\n";
    file << CS1.class_cs << "\n";

    file.close();
    cout << "CS saved to cs.txt\n";

    file.close();
    cout << "Saved to goryacheva_ac2504.txt\n";
}

void loadpipe(Pipe& pipe1, bool& exist_pipe)
{
    ifstream file("pipe.txt");
    if (!file)
    {
        cout << "File pipe.txt not found.\n";
        return;
    }

    getline(file, pipe1.name_p);
    file >> pipe1.lenght >> pipe1.diam >> pipe1.repair;

    file.close();
    exist_pipe = true;
    cout << "Pipe loaded from pipe.txt\n";
}

void loadcs(CS& CS1, bool& exist_cs)
{
    ifstream file("cs.txt");
    if (!file)
    {
        cout << "File cs.txt not found.\n";
        return;
    }

    getline(file, CS1.name_cs);
    file >> CS1.amount_ws >> CS1.amount_ws_in_prog;
    file.ignore();
    getline(file, CS1.class_cs);

    file.close();
    exist_cs = true;
    cout << "CS loaded from cs.txt\n";
}
void menu()
{
    cout << "1. add pipe\n";
    cout << "2. add cs\n";
    cout << "3. view all objects\n";
    cout << "4. edit pipe\n";
    cout << "5. edit cs\n";
    cout << "6. save pipe\n";
    cout << "7. save cs\n";
    cout << "8. load pipe\n";
    cout << "9. load cs\n";
    cout << "10. delete pipe\n";
    cout << "11. delete cs\n";
    cout << "12. search pipes\n";
    cout << "13. search cs\n";
    cout << "14. batch edit pipes\n";
    cout << "0. exit\n";
}
int main()
{
    vector<Pipe> pipes;
    int next_pipe_id = 1;
    vector<CS> stations;
    int next_CS_id = 1;
    int option;

    writelog("Program started");
    while (true)
    {
        menu();
        option = inputint("\nSelect one of the menu items: ", 0);

        if (option == 1) addpipe(pipes, next_pipe_id);
        else if (option == 2) addcs(stations, next_CS_id);
        else if (option == 3) { showallpipes(pipes); showallcs(stations); }
        else if (option == 4) editpipe(pipes);
        else if (option == 5) editcs(stations);
        else if (option == 6) savepipes(pipes, next_pipe_id);
        else if (option == 7) savecs(stations, next_cs_id);
        else if (option == 8) loadpipes(pipes, next_pipe_id);
        else if (option == 9) loadcs(stations, next_cs_id);
        else if (option == 10) deletepipe(pipes);
        else if (option == 11) deletecs(stations);
        else if (option == 12) searchpipes(pipes);
        else if (option == 13) searchcs(stations);
        else if (option == 14) batchpipes(pipes);
        else if (option == 0)
        {
            writelog("Program finished");
            break;
        }
        else cout << "Wrong menu item.\n";
    }
    return 0;
}
