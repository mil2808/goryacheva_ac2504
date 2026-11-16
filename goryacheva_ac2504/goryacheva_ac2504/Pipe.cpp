#include "Pipe.h"
#include "utils.h"
using namespace std;

int Pipe::next_id = 1;   // нумерация труб начинается с 1

void Pipe::input()
{
    id = next_id++;      // берём свободный номер и сдвигаем счётчик
    name = inputstring("Name: ");
    length = inputdouble("Length in km: ");
    diam = inputint("Diameter in mm: ", 1);
    repair = inputyesno("Is it under repair?");
}

void Pipe::show() const
{
    cout << "Pipe id: " << id << "\n";
    cout << "Name pipe: " << name << "\n";
    cout << "Length: " << length << "\n";
    cout << "Diameter: " << diam << "\n";
    cout << "In repair: " << (repair ? "yes" : "no") << "\n";
}

void Pipe::save(ostream& out) const
{
    out << id << "\n";
    out << name << "\n";
    out << length << "\n";
    out << diam << "\n";
    out << repair << "\n";
}

bool Pipe::load(istream& in)
{
    in >> id;
    in.ignore(1000, '\n');
    getline(in, name);
    in >> length >> diam >> repair;
    return !in.fail();
}