#ifndef CL_CAR_H
#define CL_CAR_H

#include "cl_base.h"

class cl_car : public cl_base
{
public:
	cl_car(cl_base*, std::string);

	std::string get_number();	
private:
	std::string number;
};

#endif
