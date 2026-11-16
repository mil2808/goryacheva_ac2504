#include "CS.h"
#include "utils.h"
using namespace std;

int CS::next_id = 1;     // нумерация станций начинается с 1

void CS::input()
{
    id = next_id++;      // берём свободный номер и сдвигаем счётчик
    name = inputstring("Name: ");
    amount_ws = inputint("Total number of shops: ", 1);
    amount_ws_in_prog = inputint("Shops working now: ", 0);
    while (amount_ws_in_prog > amount_ws)
    {
        cout << "Cannot be more than " << amount_ws << ".\n";
        amount_ws_in_prog = inputint("Shops working now: ", 0);
    }
    class_cs = inputstring("Station class: ");
}

void CS::show() const
{
    cout << "CS id: " << id << "\n";
    cout << "Name CS: " << name << "\n";
    cout << "Shops total: " << amount_ws << "\n";
    cout << "Shops working: " << amount_ws_in_prog << "\n";
    cout << "Unused shops: " << unusedPercent() << "%\n";
    cout << "Class: " << class_cs << "\n";
}

double CS::unusedPercent() const
{
    return (amount_ws - amount_ws_in_prog) * 100.0 / amount_ws;
}

void CS::startShop()
{
    if (amount_ws_in_prog == amount_ws)
        cout << "All shops already working.\n";
    else
    {
        amount_ws_in_prog++;
        cout << "Shop started. Working: " << amount_ws_in_prog << "/" << amount_ws << "\n";
    }
}

void CS::stopShop()
{
    if (amount_ws_in_prog <= 0)
        cout << "No shops are working.\n";
    else
    {
        amount_ws_in_prog--;
        cout << "Shop stopped. Working: " << amount_ws_in_prog << "/" << amount_ws << "\n";
    }
}

void CS::save(ostream& out) const
{
    out << id << "\n";
    out << name << "\n";
    out << amount_ws << "\n";
    out << amount_ws_in_prog << "\n";
    out << class_cs << "\n";
}

bool CS::load(istream& in)
{
    in >> id;
    in.ignore(1000, '\n');
    getline(in, name);
    in >> amount_ws >> amount_ws_in_prog;
    in.ignore(1000, '\n');
    getline(in, class_cs);
    return !in.fail();
}