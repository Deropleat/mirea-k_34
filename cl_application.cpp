#include "cl_application.h"

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object, "cl_application") // параметризированный конструктор объекта класса cl_application
{
	controller = new cl_controller(this);
	input = new cl_input(this);
	screen = new cl_screen(this);
}

void cl_application::build_tree_objects() // ввод исходных данных о заправочной станции
{
	set_state_all(1);

	setup_object_connection(SIGNALFN(cl_input::readline), controller, HANDLERFN(cl_controller::gasoline_handler));
	while (true)
	{
		std::string message;
		send_object_signal(SIGNALFN(cl_input::readline), message);

		if (message.empty()) break;
	}
	delete_object_connection(SIGNALFN(cl_input::readline), controller, HANDLERFN(cl_controller::gasoline_handler));
}

int cl_application::exec_app() // ввод и отработка коменд для отработки заправочной станции
{
	std::string message;
	setup_object_connection(SIGNALFN(cl_input::readline), controller, HANDLERFN(cl_controller::commands_handler));
	while (true)
	{
		controller->update();
		send_object_signal(SIGNALFN(cl_input::readline), message);

		callback.push_back(message);
		ticks++;

		if (message == "Turn off the system" || message == "SHOWTREE") break;
	}
	delete_object_connection(SIGNALFN(cl_input::readline), controller, HANDLERFN(cl_controller::commands_handler));
	setup_object_connection(SIGNALFN(cl_application::get_callback), screen, HANDLERFN(cl_screen::print_message));
	
	std::cout << "Ready to work";
	for (size_t i = 0; i < callback.size(); i++) send_object_signal(SIGNALFN(cl_application::get_callback), message);
	delete_object_connection(SIGNALFN(cl_application::get_callback), screen, HANDLERFN(cl_screen::print_message));
	
	return 0;
}

void cl_application::get_callback(std::string& message) // сигнал возврата полученной строки при выполнении команд
{
	if (callback.at(index) == "SHOWTREE")
	{
		show_object_tree();
		message = "";
		return;
	}
	message = callback.at(index);
	index++;
}
