#include <iostream>
#include <string>
#include "header.h"

void bar(std::string msg)
{
	std::cout << msg << std::endl;
}

static Register val("yanyan", bar);

