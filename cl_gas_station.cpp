#include "cl_gas_station.h"

cl_gas_station::cl_gas_station(cl_base* p_head_object, std::string number, std::string fuel, int volume) : cl_base(p_head_object, "cl_gas_station " + number) // параметризированный конструктор объекта класса cl_gas_station
{
	this->number = number;
	this->fuel = fuel;
	this->volume = volume;
}

void cl_gas_station::update() // отработка такта текущей бензоколонки
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

void cl_gas_station::push_on_service(cl_car* car, int amount) // постановка машины в очередь к текущей бензоколонке
{
	car->change_head_object(this);
	queue.push_back(std::pair<cl_car*, int>(car, amount));
	volume -= amount;
}

int cl_gas_station::get_in_queue(bool filling) // получение количества машин в очереди к текущей бензоколонке
{
	if (queue.size() == 0) return 0;
	
	if (filling) return queue.size();
	return queue.size() - 1;
}

int cl_gas_station::get_is_ordered() // получение количества обслуженных машин текущей бензоколонкой
{
	return filled.size();
}

std::string cl_gas_station::get_ordered_list() // получение списка обслуженных машин текущей бензоколонкой
{
	std::string ret = "";
	for (size_t i = 0; i < filled.size(); i++) ret += "\n" + filled.at(i);
	return ret;
}

int cl_gas_station::get_gas_station_volume() // получение количества оставшегося бензина в текущей бензоколонке
{
	return volume;
}

std::string cl_gas_station::get_gas_station_fuel() // получение типа бензина на текущей бензоколонке
{
	return fuel;
}

std::string cl_gas_station::get_gas_station_number() // получение названия/номера текущей бензоколонки
{
	return number;
}
