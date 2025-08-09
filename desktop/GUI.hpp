#pragma once

#ifndef GUI_H
#define GUI_H

class GUI
{

public:
	bool movement = true;
	bool lifespan = true;
	bool collision = true;
	bool spawning = true;
	int spawn_interval = 30;
	bool gui = true;
	bool rendering = true;

	GUI() = default;
	GUI(int si)
		: spawn_interval(si)
	{ }
};

#endif
