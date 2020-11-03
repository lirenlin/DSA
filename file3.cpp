#include "header.h"
Register* Register::global_register = 0;

int main()
{
	Register global_register;
	global_register.run();
	return 0;
}
