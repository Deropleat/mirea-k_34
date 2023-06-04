#ifndef CL_BASE_H
#define CL_BASE_H

#include "main.h"

class cl_base
{
public:
	cl_base(cl_base*, std::string);

	std::string get_object_name();

	void change_head_object(cl_base*);
	void delete_object_by_name(std::string);
	void set_state_all(int);
	void show_object_tree(int = 0);

	typedef void (cl_base::* cl_object_signal)(std::string&);
	typedef void (cl_base::* cl_object_handler)(std::string&);

	struct cl_object_connection
	{
		cl_object_signal p_signal;
		cl_base* p_target;
		cl_object_handler p_handler;
	};

	void setup_object_connection(cl_object_signal, cl_base*, cl_object_handler);
	void send_object_signal(cl_object_signal, std::string&);
	void delete_object_connection(cl_object_signal, cl_base*, cl_object_handler);

	std::vector<cl_object_connection*> object_connections;
private:

	cl_base* p_head_object;
	std::string s_object_name;
	int i_object_state = 1;

	std::vector<cl_base*> subordinate_objects;
};

#define SIGNALFN(signal_fn) (cl_object_signal)(&signal_fn)
#define HANDLERFN(handler_fn) (cl_object_handler)(&handler_fn)

#endif
