#pragma once
#include <string>
#include <iostream>

class Pipe
{
private:
    static int next_id;   // общий счётчик для всех труб: следующий свободный id

    int id = 0;
    std::string name;
    int diam = 0;
    double length = 0;
    bool repair = false;

public:
    void input();         // id теперь создаётся внутри класса
    void show() const;
    void save(std::ostream& out) const;
    bool load(std::istream& in);

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    bool isRepair() const { return repair; }
    void setRepair(bool value) { repair = value; }

    // нужны для сохранения и загрузки счётчика
    static int getNextId() { return next_id; }
    static void setNextId(int value) { next_id = value; }
};