#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void writelog(const string& text)
{
    ofstream file("log.txt", ios::app);
    if (file) file << text << "\n";
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
            continue;
        }
        string rest;
        getline(cin, rest);
        if (rest.find_first_not_of(" \t") != string::npos)
        {
            cout << "Not a number.\n";
            continue;
        }
        if (value < min_value)
        {
            cout << "Value must be at least " << min_value << ".\n";
            continue;
        }
        writelog(to_string(value));
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
            continue;
        }
        string rest;
        getline(cin, rest);
        if (rest.find_first_not_of(" \t") != string::npos)
        {
            cout << "Not a number.\n";
            continue;
        }
        ostringstream out;
        out << value;
        writelog(out.str());
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
            continue;
        }
        writelog(value);
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
            writelog("y");
            return true;
        }
        if (value == "n")
        {
            writelog("n");
            return false;
        }
        cout << "Please type y or n.\n";
    }
}

int inputpercent(string text, int min_value)
{
    int value = inputint(text, min_value);
    while (value > 100)
    {
        cout << "Cannot be more than 100.\n";
        value = inputint(text, min_value);
    }
    return value;
}