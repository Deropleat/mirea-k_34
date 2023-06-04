#include "cl_application.h"

int main() // главный алгоритм программы
{
	cl_application ob_cl_application;
	ob_cl_application.build_tree_objects();
	return ob_cl_application.exec_app();
}
