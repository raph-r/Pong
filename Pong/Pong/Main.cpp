#include "ATimer.h"
#include "ADisplay.h"

#include <memory>

int main(int argn, char** argv)
{
	Validate::object_was_initialize(al_init(), "Allegro");
	Validate::object_was_initialize(al_install_keyboard(), "Keyboard");
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>(640, 480);
	printf("Foi");
	system("PAUSE");
	return 0;
}