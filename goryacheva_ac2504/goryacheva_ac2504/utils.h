#pragma once
#include <string>

void writelog(const std::string& text);
int inputint(std::string text, int min_value);
double inputdouble(std::string text);
std::string inputstring(std::string text);
bool inputyesno(std::string text);
int inputpercent(std::string text, int min_value);