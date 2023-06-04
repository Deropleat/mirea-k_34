#ifndef CL_CONTROLLER_H
#define CL_CONTROLLER_H

#include "cl_operator.h"

class cl_controller : public cl_base
{
public:
	cl_controller();
	cl_controller(cl_base*);

	void update();

	void gasoline_handler(std::string&);
	void commands_handler(std::string&);
private:
	cl_operator* p_operator;

	std::vector<std::string> callback;

	std::vector<cl_car*> cars;
	std::vector<cl_gas_station*> gas_stations;
};

#endif
