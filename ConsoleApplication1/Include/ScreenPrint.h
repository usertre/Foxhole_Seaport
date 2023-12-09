#ifndef SCREEN_PRINT_H
#define SCREEN_PRINT_H
#include <PutText.h>

constexpr auto Final_Width = 1600;/* 最终图像宽度 */
constexpr auto Final_Height = 950;/* 最终图像高度 */



void Screen_Print();
void DrawTable(
    int Times,
    int Title_Width,
    int Title_Height,
    int Title_X,
    int Title_Y,
    int Title_Text_Offset,
    int Context_X_Offset,
    int Context_Y_Offset,
    int Context_Width,
    int Context_Height,
    int Text_X_Offset,
    int Text_Y_Offset,
    int Text_Size,
    const char* Text,
    int Number_Offset
);
void TransData();

#endif // !SCREEN_PRINT_H
