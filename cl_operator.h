#ifndef CL_OPERATOR_H
#define CL_OPERATOR_H

#include "cl_gas_station.h"

class cl_operator : public cl_base
{
public:
	cl_operator(cl_base*);

	int get_served_cars();
	int can_service(std::vector<cl_gas_station*>, std::string, int);
	size_t get_gas_station_by_name(std::vector<cl_gas_station*>, std::string);
	std::string get_gas_stations_status(std::vector<cl_gas_station*>);

	void add_served_counter(std::string&);
private:
	int served = 0;
};

#endif