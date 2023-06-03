#ifndef CL_GAS_STATION_H
#define CL_GAS_STATION_H

#include "cl_car.h"

class cl_gas_station : public cl_base
{
public:
	cl_gas_station(cl_base*, std::string, std::string, int);

	void update();
	
	int get_in_queue(bool = false);
	int get_is_ordered();
	int get_gas_station_volume();
	std::string get_ordered_list();
	std::string get_gas_station_fuel();
	std::string get_gas_station_number();

	void push_on_service(cl_car*, int);
private:
	int volume, gasoline = 0;
	std::string number, fuel;

	std::vector<std::string> filled;
	std::vector<std::pair<cl_car*, int>> queue;
};

#endif