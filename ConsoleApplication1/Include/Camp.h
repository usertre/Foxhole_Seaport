#ifndef CAMP_H
#define CAMP_H
#include <Number.h>

/*  0 means Warden , 1 means Colonial , 2 means both , 3 means unable to be produced , */
int Guns_Camp[GUNS_NUMBER+1] = {0,
	1, 0, 0, 2, 1, 1, 0, 1,
	0, 3, 0, 0, 2, 2, 0, 2,
	1, 0, 1, 1, 1, 0, 1, 0,
	0, 0, 1, 0, 2, 2, 2, 1,
	1, 0, 0, 2, 2, 2, 2
};

int Heavy_Weapons_Camp[HEAVY_WEAPONS_NUMBER+1] = { 0,
	1, 0, 2, 1, 1, 1, 0, 0,
	2, 1, 0, 1, 1, 2, 1, 0,
	1, 2, 2, 2, 2, 2, 0, 1,
	2, 2, 0, 0, 0, 2
};

int Shell_Camp[SHELL_NUMBER+1] = { 0,
	2, 2, 1, 2, 2, 2, 2, 2,
	2, 2, 2, 2
};

int Tools_Camp[TOOLS_NUMBER+1] = { 0,
	2, 2, 1, 2, 1, 0, 2, 2,
	2, 2, 2, 0, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 0,
	2
};

int Medic_Camp[MEDIC_NUMBER+1] = { 0,
	2, 2, 2, 2, 2
};

int Material_Camp[MATERIAL_NUMBER+1] = { 0,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2
};

int Uniform_Camp[UNIFORM_NUMBER+1] = { 0,
	0, 1, 0, 1, 0, 1, 1, 0,
	1, 0, 1, 1, 0, 1, 0, 1,
	0, 1, 0
};

int Vehicle_Crate_Camp[VEHICLE_CRATE_NUMBER+1] = { 0,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2
};

int Vehicle_Camp[VEHICLE_NUMBER+1] = { 0,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2
};

int Other_Crate_Camp[OTHER_CRATE_NUMBER+1] = { 0,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2
};

int Other_Camp[OTHER_NUMBER+1] = {
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2
};

#endif