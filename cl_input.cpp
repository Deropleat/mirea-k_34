#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object) : cl_base(p_head_object, "cl_input") // параметризированный конструктор объекта класса cl_input
{
}

void cl_input::readline(std::string& message) // метод чтения введенной строки
{
	std::getline(std::cin, message);
}
