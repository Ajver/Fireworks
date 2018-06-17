#ifndef TOSTRING_H
#define TOSTRING_H

#endif // TOSTRING_H

#include <iostream>

using namespace std;

extern string cutString(string, int, int);

extern string toString(int);
extern string toString(const char[]);
extern string toString(float);

extern const char* toCharArr(int);
extern const char* toCharArr(string);

extern string mergeStrings(string, string);

extern float map(float, float, float, float, float);