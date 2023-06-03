#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include "cl_controller.h"
#include "cl_input.h"

class cl_application : public cl_base
{
public:
	cl_application(cl_base* = nullptr);

	void build_tree_objects();
	int exec_app();

	void get_callback(std::string&);
private:
	cl_controller* controller;
	cl_input* input;
	cl_screen* screen;

	int ticks = 0;
	size_t index = 0;
	std::vector<std::string> callback;
};

#endif