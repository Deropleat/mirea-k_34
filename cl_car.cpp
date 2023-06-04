#include "cl_car.h"

cl_car::cl_car(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) // параметризированный конструктор объекта класса cl_car
{
	number = s_object_name;
}

std::string cl_car::get_number() // получение номера текущей машины
{
	return number;
}
