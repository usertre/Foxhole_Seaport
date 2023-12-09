#ifndef NUMBER_H
#define NUMBER_H

/*
* 仓库中页面的数量及每一页物品的种类数
*/
#define Pages                 12

#define GUNS_NUMBER           39
#define HEAVY_WEAPONS_NUMBER  30
#define SHELL_NUMBER          16
#define TOOLS_NUMBER          25
#define MEDIC_NUMBER          5
#define MATERIAL_NUMBER       27
#define UNIFORM_NUMBER        19
#define VEHICLE_CRATE_NUMBER  51
#define VEHICLE_NUMBER        98
#define OTHER_CRATE_NUMBER    12
#define OTHER_NUMBER          21

/*
* 每个页面中有多少种物品
*/
int Total_Number[Pages + 1] = {
    0,
    GUNS_NUMBER ,
    HEAVY_WEAPONS_NUMBER ,
    SHELL_NUMBER ,
    TOOLS_NUMBER ,
    MEDIC_NUMBER ,
    MATERIAL_NUMBER ,
    UNIFORM_NUMBER ,
    VEHICLE_CRATE_NUMBER ,
    VEHICLE_NUMBER,
    OTHER_CRATE_NUMBER,
    OTHER_NUMBER
};

#endif // !NUMBER_H
