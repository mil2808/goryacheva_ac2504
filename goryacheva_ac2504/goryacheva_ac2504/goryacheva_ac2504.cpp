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
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Not a number.\n";
            writelog("Input error: not a number (expected double)");
            continue;
        }
        cin.ignore(1000, '\n');
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
    cout << "In repair: " << (pipe1.repair ? "yes" : "no") << "\n";
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

void searchpipes(const vector<Pipe>& pipes)
{
    cout << "1. Search by name\n";
    cout << "2. Search by repair status\n";
    int choice = inputint("Choice: ", 1);
    int count = 0;

    if (choice == 1)
    {
        string name = inputstring("Name (or part of name): ");
        for (size_t i = 0; i < pipes.size(); i++)
        {
            if (pipes[i].name_p.find(name) != string::npos)
            {
                showpipe(pipes[i]);
                count++;
            }
        }
    }
    else if (choice == 2)
    {
        bool repair = inputyesno("Search pipes in repair?");
        for (size_t i = 0; i < pipes.size(); i++)
        {
            if (pipes[i].repair == repair)
            {
                showpipe(pipes[i]);
                count++;
            }
        }
    }
    else
    {
        cout << "Wrong choice.\n";
        writelog("Search pipes: wrong choice " + to_string(choice));
        return;
    }

    if (count == 0) cout << "Nothing found.\n";
    writelog("Search pipes: found " + to_string(count));
}

void batchpipes(vector<Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        writelog("Batch edit: no pipes in the list");
        return;
    }

    cout << "1. All pipes\n";
    cout << "2. Pipes by name\n";
    cout << "3. Pipes by repair status\n";
    int filter = inputint("Choice: ", 1);
    string name;
    bool repair_filter = false;
    if (filter == 2) name = inputstring("Name (or part of name): ");
    else if (filter == 3) repair_filter = inputyesno("Pipes in repair?");
    else if (filter != 1)
    {
        cout << "Wrong choice.\n";
        writelog("Batch edit: wrong filter " + to_string(filter));
        return;
    }

    cout << "1. Process all of them\n";
    cout << "2. Choose one by one\n";
    int mode = inputint("Choice: ", 1);
    if (mode != 1 && mode != 2)
    {
        cout << "Wrong choice.\n";
        writelog("Batch edit: wrong mode " + to_string(mode));
        return;
    }

    cout << "1. Change repair status\n";
    cout << "2. Delete\n";
    int action = inputint("Choice: ", 1);
    bool new_repair = false;
    if (action == 1) new_repair = inputyesno("Set repair to");
    else if (action != 2)
    {
        cout << "Wrong choice.\n";
        writelog("Batch edit: wrong action " + to_string(action));
        return;
    }

    int count = 0;
    size_t i = 0;
    while (i < pipes.size())
    {
        bool match = true;
        if (filter == 2) match = (pipes[i].name_p.find(name) != string::npos);
        else if (filter == 3) match = (pipes[i].repair == repair_filter);

        if (match && mode == 2)
        {
            showpipe(pipes[i]);
            match = inputyesno("Process this pipe?");
        }

        if (!match)
        {
            i++;
            continue;
        }

        if (action == 1)
        {
            pipes[i].repair = new_repair;
            writelog("Batch edit: pipe id " + to_string(pipes[i].id) + " repair changed");
            i++;
        }
        else
        {
            writelog("Batch edit: pipe id " + to_string(pipes[i].id) + " deleted");
            pipes.erase(pipes.begin() + i);
        }
        count++;
    }
    cout << "Done. Pipes processed: " << count << "\n";
    writelog("Batch edit: processed " + to_string(count) + " pipe(s)");
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

void savepipes(vector<Pipe>& pipes, int next_id)
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

void savecs(vector<CS>& stations, int next_id)
{
    if (stations.empty())
    {
        cout << "No CS to save.\n";
        writelog("Save CS: no CS to save");
        return;
    }
    string file_name = inputstring("File name to save CS: ");
    ofstream file(file_name);
    if (!file)
    {
        cout << "Cannot open file for writing.\n";
        writelog("Save CS: cannot open file " + file_name);
        return;
    }
    file << next_id << "\n";
    file << stations.size() << "\n";
    for (size_t i = 0; i < stations.size(); i++)
    {
        file << stations[i].id << "\n";
        file << stations[i].name_cs << "\n";
        file << stations[i].amount_ws << "\n";
        file << stations[i].amount_ws_in_prog << "\n";
        file << stations[i].class_cs << "\n";
    }

    file.close();
    cout << "CS saved to " << file_name << "\n";
    writelog("CS saved to " + file_name + ": " + to_string(stations.size()) + " CS");
}

void loadpipes(vector<Pipe>& pipes, int& next_id)
{
    string file_name = inputstring("File name to load pipes: ");
    ifstream file(file_name);
    if (!file)
    {
        cout << "File " << file_name << " not found.\n";
        writelog("Load pipes: file " + file_name + " not found");
        return;
    }

    int new_next_id = 0;
    int count = 0;
    vector<Pipe> new_pipes;

    file >> new_next_id >> count;
    for (int i = 0; i < count && file; i++)
    {
        Pipe p;
        file >> p.id;
        file.ignore(1000, '\n');
        getline(file, p.name_p);
        file >> p.lenght >> p.diam >> p.repair;
        new_pipes.push_back(p);
    }

    if (file.fail())
    {
        cout << "File is damaged or has wrong format.\n";
        writelog("Load pipes: wrong format in " + file_name);
        return;
    }

    file.close();
    pipes = new_pipes;
    next_id = new_next_id;
    cout << "Pipes loaded from " << file_name << "\n";
    writelog("Pipes loaded from " + file_name + ": " + to_string(pipes.size()) + " pipe(s)");
}

void loadcs(vector<CS>& stations, int& next_id)
{
    string file_name = inputstring("File name to load CS: ");
    ifstream file(file_name);
    if (!file)
    {
        cout << "File " << file_name << " not found.\n";
        writelog("Load CS: file " + file_name + " not found");
        return;
    }

    int new_next_id = 0;
    int count = 0;
    vector<CS> new_stations;

    file >> new_next_id >> count;
    for (int i = 0; i < count && file; i++)
    {
        CS cs;
        file >> cs.id;
        file.ignore(1000, '\n');
        getline(file, cs.name_cs);
        file >> cs.amount_ws >> cs.amount_ws_in_prog;
        file.ignore(1000, '\n');
        getline(file, cs.class_cs);
        new_stations.push_back(cs);
    }

    if (file.fail())
    {
        cout << "File is damaged or has wrong format.\n";
        writelog("Load CS: wrong format in " + file_name);
        return;
    }

    file.close();
    stations = new_stations;
    next_id = new_next_id;
    cout << "CS loaded from " << file_name << "\n";
    writelog("CS loaded from " + file_name + ": " + to_string(stations.size()) + " CS");
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
        else if (option == 7) savecs(stations, next_CS_id);
        else if (option == 8) loadpipes(pipes, next_pipe_id);
        else if (option == 9) loadcs(stations, next_CS_id);
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
