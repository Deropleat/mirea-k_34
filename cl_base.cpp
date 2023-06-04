#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, std::string s_object_name) // параметризированный конструктор объекта класса cl_base
{
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;

	if (p_head_object) p_head_object->subordinate_objects.push_back(this);
}

std::string cl_base::get_object_name() // получение имени текущего объекта
{
	return s_object_name;
}

void cl_base::change_head_object(cl_base* new_head_object) // смена головного объекта для текущего объекта
{
	cl_base* base = p_head_object;
	new_head_object->subordinate_objects.push_back(this);
	
	std::vector<cl_base*> new_subordinate_objects;
	for (size_t i = 0; i < base->subordinate_objects.size(); i++) if (base->subordinate_objects.at(i)->get_object_name() != s_object_name) new_subordinate_objects.push_back(base->subordinate_objects.at(i));
	base->subordinate_objects = new_subordinate_objects;
	
	for (size_t i = 0; i < new_head_object->subordinate_objects.size(); i++) if (new_head_object->subordinate_objects.at(i)->get_object_name() == s_object_name) new_head_object->subordinate_objects.at(i)->p_head_object = new_head_object; 
}

void cl_base::delete_object_by_name(std::string s_object_name) // удаление объекта из дереве иерархии на текущей ветке по имени
{
	std::vector<cl_base*> new_subordinate_objects;
	for (size_t i = 0; i < subordinate_objects.size(); i++) if (subordinate_objects.at(i)->get_object_name() != s_object_name) new_subordinate_objects.push_back(subordinate_objects.at(i));
	subordinate_objects = new_subordinate_objects;
}

void cl_base::set_state_all(int state) // установка общего состояния для всех объектов на текущей векте дерева иерархии
{
	i_object_state = state;
	if (subordinate_objects.size() > 0) for (int i = 0; i < subordinate_objects.size(); i++) subordinate_objects.at(i)->set_state_all(state);
}

void cl_base::show_object_tree(int level) // вывод текущей ветки дерева иерархии
{
	std::cout << std::endl << std::string(level * 4, ' ').c_str() << this->s_object_name;
	if (subordinate_objects.size() > 0) for (int i = 0; i < subordinate_objects.size(); i++) subordinate_objects.at(i)->show_object_tree(level + 1);
}

void cl_base::setup_object_connection(cl_object_signal p_object_signal, cl_base* p_target_object, cl_object_handler p_object_handler) // установка соединения между объектами посредством сигналов и обработчиков
{
	cl_object_connection* connection;
	for (size_t i = 0; i < object_connections.size(); i++) if (object_connections.at(i)->p_signal == p_object_signal && object_connections.at(i)->p_target == p_target_object && object_connections.at(i)->p_handler == p_object_handler) return;

	connection = new cl_object_connection();
	connection->p_signal = p_object_signal;
	connection->p_target = p_target_object;
	connection->p_handler = p_object_handler;
	object_connections.push_back(connection);
}

void cl_base::send_object_signal(cl_object_signal p_object_signal, std::string& s_signal) // отправка сигнала для текущего объекта 
{
	if (i_object_state == 0) return;

	cl_object_handler p_handler;
	cl_base* p_target;

	(this->*p_object_signal)(s_signal);

	for (size_t i = 0; i < object_connections.size(); i++)
	{
		if (object_connections.at(i)->p_signal == p_object_signal);
		{
			p_handler = object_connections.at(i)->p_handler;
			p_target = object_connections.at(i)->p_target;
			if (p_target->i_object_state != 0) (p_target->*p_handler)(s_signal);
		}
	}
}

void cl_base::delete_object_connection(cl_object_signal p_object_signal, cl_base* p_target_object, cl_object_handler p_object_handler) // удаление сигнала и обработчика из текущего объекта
{
	for (size_t i = 0; i < object_connections.size(); i++) if (object_connections.at(i)->p_signal == p_object_signal && object_connections.at(i)->p_target == p_target_object && object_connections.at(i)->p_handler == p_object_handler) object_connections.erase(object_connections.begin() + i);
}
