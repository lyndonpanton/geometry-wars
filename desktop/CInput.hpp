#include "Component.h"

class CInput : public Component
{

public:
	bool is_up_pressed = false;
	bool is_right_pressed = false;
	bool is_down_pressed = false;
	bool is_left_pressed = false;
	bool is_shoot_pressed = false;

	CInput() = default;
};
