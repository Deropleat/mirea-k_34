#include "cl_controller.h"

cl_controller::cl_controller(cl_base* p_head_object) : cl_base(p_head_object, "cl_controller") // параметризированный конструкор объекта класса cl_controller
{
	p_operator = new cl_operator(this);
}

void cl_controller::update() // отработка такта работы заправочной станции
{
	for (size_t i = 0; i < gas_stations.size(); i++) gas_stations.at(i)->update();
}

void cl_controller::gasoline_handler(std::string& message) // обработчик сигнала чтения входных данных о заправке
{
	if (message == "End of information about petrol filling stations")
	{
		message.clear();
		return;
	}

	int volume;
	std::string number, fuel;

	number = message.substr(0, message.find(' '));
	message = message.substr(message.find(' ') + 1);

	fuel = message.substr(0, message.find(' '));
	message = message.substr(message.find(' ') + 1);

	volume = atoi(message.c_str());

	cl_gas_station* station = new cl_gas_station(this, number, fuel, volume);
	gas_stations.push_back(station);
}

void cl_controller::commands_handler(std::string& message) // обработчик сигнала чтения входных данных (команд) 
{
	if (message == "Turn of the system" || message == "SHOWTREE") return;
	else if (message.find("Fill up the tank") != std::string::npos)
	{
		int amount;
		std::string number, gas;

		message = message.substr(message.find('k') + 2);
		number = message.substr(0, message.find(' '));

		message = message.substr(message.find(' ') + 1);
		gas = message.substr(0, message.find(' '));

		message = message.substr(message.find(' ') + 1);
		amount = atoi(message.c_str());

		int station = p_operator->can_service(gas_stations, gas, amount);
		if (station != -1)
		{
			cars.push_back(new cl_car(this, number));
			gas_stations.at(station)->push_on_service(cars.at(cars.size() - 1), amount);
			message.clear();
		}
		else message = "Denial of service " + number;
	}
	else if (message.find("Display the petrol filling station status") != std::string::npos)
	{
		std::string number = message.substr(message.find('u') + 3);
		size_t index = p_operator->get_gas_station_by_name(gas_stations, number);
		message = "Petrol filling station status " + number + " " + std::to_string(gas_stations.at(index)->get_in_queue()) + " " + std::to_string(gas_stations.at(index)->get_is_ordered()) + gas_stations.at(index)->get_ordered_list(); 

	}
	else if (message == "Display the system status") message = p_operator->get_gas_stations_status(gas_stations);
	else if (message.empty() || message == " ") message.clear();
}
