#ifndef CL_SCREEN_H
#define CL_SCREEN_H

#include "cl_base.h"

class cl_screen : public cl_base
{
public:
	cl_screen(cl_base*);

	void print_message(std::string&);
};

#endif	