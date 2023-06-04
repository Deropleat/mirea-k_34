#include "cl_operator.h"

cl_operator::cl_operator(cl_base* p_head_object) : cl_base(p_head_object, "cl_operator")
{

}

int cl_operator::can_service(std::vector<cl_gas_station*> gas_stations, std::string fuel, int amount)
{
	for (size_t i = 0; i < gas_stations.size(); i++) if (gas_stations.at(i)->get_gas_station_fuel() == fuel) if (gas_stations.at(i)->get_gas_station_volume() >= amount) return i;
	return -1;
}

size_t cl_operator::get_gas_station_by_name(std::vector<cl_gas_station*> gas_stations, std::string name)
{
	for (size_t i = 0; i < gas_stations.size(); i++) if (gas_stations.at(i)->get_gas_station_number() == name) return i;
	return NULL;
}

std::string cl_operator::get_gas_stations_status(std::vector<cl_gas_station*> gas_stations)
{
	int filled = 0, queue = 0;
	std::string ret = "";
	for (size_t i = 0; i < gas_stations.size(); i++)
	{
		if (i > 0) ret += "\n";
		ret += "Petrol station " + gas_stations.at(i)->get_gas_station_number() + " " + std::to_string(gas_stations.at(i)->get_gas_station_volume()) + " " + std::to_string(gas_stations.at(i)->get_in_queue(true));
		queue += gas_stations.at(i)->get_in_queue(true);
		filled += gas_stations.at(i)->get_is_ordered();
	}
	ret += "\nOperator " + std::to_string(filled) + " " + std::to_string(queue);

	return ret;
}
