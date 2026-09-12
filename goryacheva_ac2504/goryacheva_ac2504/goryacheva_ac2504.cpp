#include <iostream>
#include <string>
using namespace std; 

struct Pipe 
{
    string name_p;
    int diam;
    double lenght;
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
    cout << "1. add pipe\n";
    cout << "2. add cs\n";
    cout << "3. view all objects\n";
    cout << "4. edit pipe\n";
    cout << "5. edit cs\n";
    cout << "6. save\n";
    cout << "7. load\n";
    cout << "0. exit\n";
}

