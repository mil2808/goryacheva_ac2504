#pragma once
#include <string>
#include <iostream>

class CS
{
private:
    static int next_id;   // общий счётчик для всех станций: следующий свободный id

    int id = 0;
    std::string name;
    int amount_ws = 1;
    int amount_ws_in_prog = 0;
    std::string class_cs;

public:
    void input();         // id теперь создаётся внутри класса
    void show() const;
    void save(std::ostream& out) const;
    bool load(std::istream& in);

    double unusedPercent() const;
    void startShop();
    void stopShop();

    int getId() const { return id; }
    const std::string& getName() const { return name; }

    // нужны для сохранения и загрузки счётчика
    static int getNextId() { return next_id; }
    static void setNextId(int value) { next_id = value; }
};