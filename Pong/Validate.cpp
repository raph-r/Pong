#include "Validate.h"

void Validate::object_was_initialized(const bool& result_to_validate, const char* object_name)
{
	if (!result_to_validate)
	{
		printf("%s wasn't initialized.\n", object_name);
		exit(1);
	}
}