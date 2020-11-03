#include <iostream>
#include <string>
#include "header.h"

void foo(std::string msg)
{
	std::cout << msg << std::endl;
}

static Register val("lirenlin", foo);
