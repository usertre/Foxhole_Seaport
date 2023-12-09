#ifndef CAMP_H
#define CAMP_H
#include <Number.h>

/*  1 means Warden , 2 means Colonial , 3(11B) means both , 4(100B) means unable to be produced , */

int Guns_Camp[GUNS_NUMBER+1] = {4,
	2, 1, 1, 3, 2, 2, 2, 2,
	1, 4, 1, 1, 3, 3, 1, 3,
	2, 1, 2, 2, 2, 1, 2, 1,
	1, 1, 2, 1, 3, 3, 3, 2,
	2, 1, 1, 3, 3, 3, 3
};

int Heavy_Weapons_Camp[HEAVY_WEAPONS_NUMBER+1] = { 4,
	2, 1, 3, 2, 2, 2, 1, 1,
	3, 2, 1, 2, 2, 3, 2, 1,
	2, 3, 3, 3, 3, 3, 1, 2,
	3, 3, 1, 1, 1, 3
};

int Shell_Camp[SHELL_NUMBER+1] = { 4,
	3, 3, 2, 3, 3, 3, 3, 3,
	3, 3, 3, 3
};

int Tools_Camp[TOOLS_NUMBER+1] = { 4,
	3, 3, 2, 3, 2, 1, 3, 3,
	3, 3, 3, 1, 3, 3, 3, 3,
	2, 3, 3, 3, 3, 3, 3, 1,
	3
};

int Medic_Camp[MEDIC_NUMBER+1] = { 4,
	3, 3, 3, 3, 3
};

int Material_Camp[MATERIAL_NUMBER+1] = { 4,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3
};

int Uniform_Camp[UNIFORM_NUMBER+1] = { 4,
	1, 2, 1, 2, 1, 2, 2, 1,
	2, 1, 2, 2, 1, 2, 1, 2,
	1, 2, 1
};

int Vehicle_Crate_Camp[VEHICLE_CRATE_NUMBER+1] = { 4,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3
};

int Vehicle_Camp[VEHICLE_NUMBER+1] = { 4,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3
};

int Other_Crate_Camp[OTHER_CRATE_NUMBER+1] = { 4,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3
};

int Other_Camp[OTHER_NUMBER+1] = { 4,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3
};

#endif