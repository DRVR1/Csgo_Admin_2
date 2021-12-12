#pragma once
#include "hackbools.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

std::ifstream read("performance.log");

int i = 0;

void readOffsets() {
	std::string current;
	while (std::getline(read, current)) {
		offsetload::offset[i] = std::stoi(current);
		printf("setting in %d the offset %d\n",i, offsetload::offset[i]);
		i++;
	}
}
