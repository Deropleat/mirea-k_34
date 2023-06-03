#include "cl_gas_station.h"

cl_gas_station::cl_gas_station(cl_base* p_head_object, std::string number, std::string fuel, int volume) : cl_base(p_head_object, "cl_gas_station " + number)
{
	this->number = number;
	this->fuel = fuel;
	this->volume = volume;
}

void cl_gas_station::update()
{
	if (queue.size() > 0)
	{
		gasoline += 10;
		if (gasoline == queue.at(0).second)
		{
			gasoline = 0;
			filled.push_back(queue.at(0).first->get_number());
			delete_object_by_name(queue.at(0).first->get_number());
			queue.erase(queue.begin());
		}
	}
}

void cl_gas_station::push_on_service(cl_car* car, int amount)
{
	car->change_head_object(this);
	queue.push_back(std::pair<cl_car*, int>(car, amount));
	volume -= amount;
}

int cl_gas_station::get_in_queue(bool filling)
{
	if (queue.size() == 0) return 0;
	
	if (filling) return queue.size();
	return queue.size() - 1;
}

int cl_gas_station::get_is_ordered()
{
	return filled.size();
}

std::string cl_gas_station::get_ordered_list()
{
	std::string ret = "";
	for (size_t i = 0; i < filled.size(); i++) ret += "\n" + filled.at(i);
	return ret;
}

int cl_gas_station::get_gas_station_volume()
{
	return volume;
}

std::string cl_gas_station::get_gas_station_fuel()
{
	return fuel;
}

std::string cl_gas_station::get_gas_station_number()
{
	return number;
}