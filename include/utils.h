#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <cmath>

#include "conf.h"

float randomx();
float randomy();

class Vec;
class Atom;

std::vector<Atom> create(int n, Color color);
void rule(std::vector<Atom>* atoms1, const std::vector<Atom>* atoms2, float g);

#endif
