#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include "Pipe.h"
#include "CS.h"
#include "utils.h"
using namespace std;

void addpipe(unordered_map<int, Pipe>& pipes)
{
    cout << "\nEnter pipe data:\n";
    Pipe p;
    p.input();
    pipes.emplace(p.getId(), p);
    cout << "Pipe added. Id = " << p.getId() << "\n";
}

void showallpipes(const unordered_map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        return;
    }
    for (const auto& item : pipes) item.second.show();
}

void showpipes(const unordered_map<int, Pipe>& pipes, const set<int>& ids)
{
    for (int id : ids) pipes.at(id).show();
}

int choosepipe(const unordered_map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        return -1;
    }
    showallpipes(pipes);
    int id = inputint("Enter pipe id: ", 1);
    if (pipes.find(id) == pipes.end())
    {
        cout << "Pipe with this id not found.\n";
        return -1;
    }
    return id;
}

void editpipe(unordered_map<int, Pipe>& pipes)
{
    int id = choosepipe(pipes);
    if (id == -1) return;

    cout << "Now in repair: " << (pipes.at(id).isRepair() ? "yes" : "no") << "\n";
    pipes.at(id).setRepair(inputyesno("Set to repair"));
    cout << "Done \n";
}

void deletepipe(unordered_map<int, Pipe>& pipes)
{
    int id = choosepipe(pipes);
    if (id == -1) return;

    pipes.erase(id);
    cout << "Pipe deleted.\n";
}

set<int> allpipes(const unordered_map<int, Pipe>& pipes)
{
    set<int> ids;
    for (const auto& item : pipes) ids.insert(item.first);
    return ids;
}

// --- Шаблон фильтрации (как в коде про студентов) ---

// Тип "функция-проверка": принимает трубу и параметр, отвечает да/нет
template<typename T>
using Filter = bool(*)(const Pipe& p, T param);

// Проверка 1: название содержит введённый текст
bool CheckByName(const Pipe& p, string param)
{
    return p.getName().find(param) != string::npos;
}

// Проверка 2: статус ремонта совпадает с нужным
bool CheckByRepair(const Pipe& p, bool param)
{
    return p.isRepair() == param;
}

// Общий поиск: возвращает id всех труб, которые прошли проверку f
template<typename T>
set<int> FindPipesByFilter(const unordered_map<int, Pipe>& pipes, Filter<T> f, T param)
{
    set<int> ids;
    for (const auto& item : pipes)
        if (f(item.second, param)) ids.insert(item.first);
    return ids;
}

void searchpipes(const unordered_map<int, Pipe>& pipes)
{
    cout << "1. Search by name\n";
    cout << "2. Search by repair status\n";
    int choice = inputint("Choice: ", 1);

    set<int> ids;
    if (choice == 1) ids = FindPipesByFilter(pipes, CheckByName, inputstring("Name (or part of name): "));
    else if (choice == 2) ids = FindPipesByFilter(pipes, CheckByRepair, inputyesno("Search pipes in repair?"));
    else
    {
        cout << "Wrong choice.\n";
        return;
    }

    if (ids.empty()) cout << "Nothing found.\n";
    else showpipes(pipes, ids);
}

set<int> selectpipes(const unordered_map<int, Pipe>& pipes)
{
    cout << "1. All pipes\n";
    cout << "2. Pipes by name\n";
    cout << "3. Pipes by repair status\n";
    int filter = inputint("Choice: ", 1);

    set<int> ids;
    if (filter == 1) ids = allpipes(pipes);
    else if (filter == 2) ids = FindPipesByFilter(pipes, CheckByName, inputstring("Name (or part of name): "));
    else if (filter == 3) ids = FindPipesByFilter(pipes, CheckByRepair, inputyesno("Pipes in repair?"));
    else
    {
        cout << "Wrong choice.\n";
        return ids;
    }

    if (ids.empty())
    {
        cout << "Nothing found.\n";
    }
    return ids;
}

set<int> choosesubset(const unordered_map<int, Pipe>& pipes, const set<int>& ids)
{
    cout << "1. Process all of them\n";
    cout << "2. Choose one by one\n";
    int mode = inputint("Choice: ", 1);

    if (mode == 1) return ids;

    set<int> chosen;
    if (mode != 2)
    {
        cout << "Wrong choice.\n";
        return chosen;
    }

    for (int id : ids)
    {
        pipes.at(id).show();
        if (inputyesno("Process this pipe?")) chosen.insert(id);
    }
    if (chosen.empty())
    {
        cout << "Nothing selected.\n";
    }
    return chosen;
}

void changerepair(unordered_map<int, Pipe>& pipes, const set<int>& ids)
{
    bool new_repair = inputyesno("Set repair to");
    for (int id : ids)
    {
        pipes.at(id).setRepair(new_repair);
    }
    cout << "Done. Pipes changed: " << ids.size() << "\n";
}

void deletepipes(unordered_map<int, Pipe>& pipes, const set<int>& ids)
{
    for (int id : ids)
    {
        pipes.erase(id);
    }
    cout << "Done. Pipes deleted: " << ids.size() << "\n";
}

void batchpipes(unordered_map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        return;
    }

    set<int> found = selectpipes(pipes);
    if (found.empty()) return;

    set<int> chosen = choosesubset(pipes, found);
    if (chosen.empty()) return;

    cout << "1. Change repair status\n";
    cout << "2. Delete\n";
    int action = inputint("Choice: ", 1);

    if (action == 1) changerepair(pipes, chosen);
    else if (action == 2) deletepipes(pipes, chosen);
    else
    {
        cout << "Wrong choice.\n";
        return;
    }
}

void savepipes(const unordered_map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipe to save.\n";
        return;
    }
    string file_name = inputstring("File name to save pipes: ");
    ofstream file(file_name);
    if (!file)
    {
        cout << "Cannot open file for writing.\n";
        return;
    }
    file << Pipe::getNextId() << "\n";
    file << pipes.size() << "\n";
    for (const auto& item : pipes) item.second.save(file);

    cout << "Pipes saved to " << file_name << "\n";
}

void loadpipes(unordered_map<int, Pipe>& pipes)
{
    string file_name = inputstring("File name to load pipes: ");
    ifstream file(file_name);
    if (!file)
    {
        cout << "File " << file_name << " not found.\n";
        return;
    }

    int new_next_id = 0;
    int count = 0;
    unordered_map<int, Pipe> new_pipes;

    file >> new_next_id >> count;
    for (int i = 0; i < count && file; i++)
    {
        Pipe p;
        if (!p.load(file)) break;
        new_pipes.emplace(p.getId(), p);
    }

    if (file.fail() || (int)new_pipes.size() != count)
    {
        cout << "File is damaged or has wrong format.\n";
        return;
    }

    pipes = new_pipes;
    Pipe::setNextId(new_next_id);
    cout << "Pipes loaded from " << file_name << "\n";
}

void addcs(unordered_map<int, CS>& stations)
{
    cout << "Enter cs data: \n";
    CS cs;
    cs.input();
    stations.emplace(cs.getId(), cs);
    cout << "CS added. Id = " << cs.getId() << "\n";
}

void showallcs(const unordered_map<int, CS>& stations)
{
    if (stations.empty())
    {
        cout << "No CS yet.\n";
        return;
    }
    for (const auto& item : stations) item.second.show();
}

void showcs(const unordered_map<int, CS>& stations, const set<int>& ids)
{
    for (int id : ids) stations.at(id).show();
}

int choosecs(const unordered_map<int, CS>& stations)
{
    if (stations.empty())
    {
        cout << "No CS yet.\n";
        return -1;
    }
    showallcs(stations);
    int id = inputint("Enter CS id: ", 1);
    if (stations.find(id) == stations.end())
    {
        cout << "CS with this id not found.\n";
        return -1;
    }
    return id;
}

void editcs(unordered_map<int, CS>& stations)
{
    int id = choosecs(stations);
    if (id == -1) return;

    cout << "1. Start a shop\n";
    cout << "2. Stop a shop\n";
    int choice = inputint("Choice: ", 1);

    if (choice == 1)
    {
        stations.at(id).startShop();
    }
    else if (choice == 2)
    {
        stations.at(id).stopShop();
    }
    else
    {
        cout << "Wrong choice.\n";
    }
}

void deletecs(unordered_map<int, CS>& stations)
{
    int id = choosecs(stations);
    if (id == -1) return;

    stations.erase(id);
    cout << "CS deleted.\n";
}

set<int> csbyname(const unordered_map<int, CS>& stations, const string& name)
{
    set<int> ids;
    for (const auto& item : stations)
        if (item.second.getName().find(name) != string::npos) ids.insert(item.first);
    return ids;
}

set<int> csbypercent(const unordered_map<int, CS>& stations, int from, int to)
{
    set<int> ids;
    for (const auto& item : stations)
    {
        double percent = item.second.unusedPercent();
        if (percent >= from && percent <= to) ids.insert(item.first);
    }
    return ids;
}

void searchcs(const unordered_map<int, CS>& stations)
{
    cout << "1. Search by name\n";
    cout << "2. Search by percent of unused shops\n";
    int choice = inputint("Choice: ", 1);

    set<int> ids;
    if (choice == 1) ids = csbyname(stations, inputstring("Name (or part of name): "));
    else if (choice == 2)
    {
        int from = inputpercent("Percent of unused shops from (0-100): ", 0);
        int to = inputpercent("Percent of unused shops to (" + to_string(from) + "-100): ", from);
        ids = csbypercent(stations, from, to);
    }
    else
    {
        cout << "Wrong choice.\n";
        return;
    }

    if (ids.empty()) cout << "Nothing found.\n";
    else showcs(stations, ids);
}

void savecs(const unordered_map<int, CS>& stations)
{
    if (stations.empty())
    {
        cout << "No CS to save.\n";
        return;
    }
    string file_name = inputstring("File name to save CS: ");
    ofstream file(file_name);
    if (!file)
    {
        cout << "Cannot open file for writing.\n";
        return;
    }
    file << CS::getNextId() << "\n";
    file << stations.size() << "\n";
    for (const auto& item : stations) item.second.save(file);

    cout << "CS saved to " << file_name << "\n";
}

void loadcs(unordered_map<int, CS>& stations)
{
    string file_name = inputstring("File name to load CS: ");
    ifstream file(file_name);
    if (!file)
    {
        cout << "File " << file_name << " not found.\n";
        return;
    }

    int new_next_id = 0;
    int count = 0;
    unordered_map<int, CS> new_stations;

    file >> new_next_id >> count;
    for (int i = 0; i < count && file; i++)
    {
        CS cs;
        if (!cs.load(file)) break;
        new_stations.emplace(cs.getId(), cs);
    }

    if (file.fail() || (int)new_stations.size() != count)
    {
        cout << "File is damaged or has wrong format.\n";
        return;
    }

    stations = new_stations;
    CS::setNextId(new_next_id);
    cout << "CS loaded from " << file_name << "\n";
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
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> stations;
    int option;

    while (true)
    {
        menu();
        option = inputint("\nSelect one of the menu items: ", 0);

        if (option == 1) addpipe(pipes);
        else if (option == 2) addcs(stations);
        else if (option == 3) { showallpipes(pipes); showallcs(stations); }
        else if (option == 4) editpipe(pipes);
        else if (option == 5) editcs(stations);
        else if (option == 6) savepipes(pipes);
        else if (option == 7) savecs(stations);
        else if (option == 8) loadpipes(pipes);
        else if (option == 9) loadcs(stations);
        else if (option == 10) deletepipe(pipes);
        else if (option == 11) deletecs(stations);
        else if (option == 12) searchpipes(pipes);
        else if (option == 13) searchcs(stations);
        else if (option == 14) batchpipes(pipes);
        else if (option == 0)
        {
            break;
        }
        else cout << "Wrong menu item.\n";
    }
    return 0;
}