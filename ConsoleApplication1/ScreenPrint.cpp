#include <Proportion.h>
#include <PutText.h>
#include <ScreenPrint.h>
#include <Opencv2/opencv.hpp>
#include <cstdio>


extern Mat FinalImage;
extern int Temp_Save_Data[12 + 1][98 + 1];
extern double OemProportion[9][30][2];
extern int Proportion_Number[9];

#define OneFourthWidth (Final_Width / 4)
#define White (Scalar(255, 255, 255))
#define Black (Scalar(0, 0, 0))
#define Yellow (Scalar(0,255,255))
#define Red (Scalar(0,0,255))
#define Green (Scalar(0,255,0))
#define TitleColor (Scalar(67, 67, 67))
#define ContextBackGroundColor (Scalar(105, 105, 105))

#define TitleFontSize 20

int MaxNumber[9] = {300,100,100,100,100,100,100,100,100};
int PrintData[9][30];
char PrintName[9][30][50];
int Now_Y = 0;
int Title_Count = 0;
/*
*   [param]Times               生成几个条形图
*   [param]Title_Width         标题的背景宽度
*   [param]Title_Height        标题的背景高度
*   [param]Title_X             标题背景左上角的横坐标
*   [param]Title_Y             标题背景左上角的纵坐标
*   [param]Title_Text_Offset   标题文本的0点位置距离中轴线向左偏移的距离
*   [param]Context_X_Offset    条形图左侧距离底色的偏移量
*   [param]Context_Y_Offset    条形图上侧距离底色的偏移量
*   [param]Context_Width       条形图长度
*   [param]Context_Height      条形图高度
*   [param]Text_X_Offset       物品名字距离条形图右端的X轴偏移值
*   [param]Text_Y_Offset       物品名字距离条形图上侧的Y轴偏移值
*   [param]Text_Size           物品名字的字体大小
*   [param]*Text               标题名字
*   [param]Number_Offset       物品数量较条形图中线向左的偏移值
*/
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
    const char *Text,
    int Number_Offset
)
{
    int Context_Count = 0; /* 第几个要显示的物品 */
    char Number_Text[20] = {0}; /* 输出文本中的数字部分 */

    /* 画标题背景色 */
    rectangle (
        FinalImage,
        Point (Title_X, Title_Y),
        Point (Title_X + Title_Width, Title_Y + Title_Height),
        TitleColor,
        -1,
        8
        );
    /* 输出标题文字 */
    putTextHusky (
        FinalImage,
        Text,
        Point (int(Title_X + (Title_Width / 2) - Title_Text_Offset), Title_Y),
        White,
        TitleFontSize,
        "微软雅黑",
        false, 
        false
        );

    for (Context_Count = 0;Context_Count < Times; Context_Count++) {
        /* 画灰色背景 */
        rectangle(
            FinalImage,
            Point (Title_X, Title_Y + Title_Height + Context_Count * Context_Height + 2 * Context_Count * Context_Y_Offset),
            Point (Title_X + Title_Width, Title_Y + Title_Height + (Context_Count + 1) * Context_Height + 2 * (Context_Count + 1) * Context_Y_Offset),
            ContextBackGroundColor,
            -1,
            8
            );
        /* 画条形图的白色背景 */
        rectangle(
            FinalImage,
            Point (Title_X + Context_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
            Point (Title_X + Context_X_Offset + Context_Width, Title_Y + Title_Height + (Context_Count + 1) * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
            White,
            -1,
            8
            );

        /* 画条形图前景色 */
        if (PrintData[Title_Count][Context_Count] < (MaxNumber[Title_Count] * 1.0 * OemProportion[Title_Count][Context_Count][0])) {
            /* 如果数量不够，画红色条形图 */
            rectangle(
                FinalImage,
                Point(Title_X + Context_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                Point(Title_X + Context_X_Offset + Context_Width * PrintData[Title_Count][Context_Count] / MaxNumber[Title_Count], Title_Y + Title_Height + (Context_Count + 1) * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                Red,
                -1,
                8
                );
        }
        else if (PrintData[Title_Count][Context_Count] < (MaxNumber[Title_Count] * 1.0 * OemProportion[Title_Count][Context_Count][1])) {
            /* 如果数量一般，画黄色条形图 */
            rectangle(
                FinalImage,
                Point(Title_X + Context_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                Point(Title_X + Context_X_Offset + Context_Width * PrintData[Title_Count][Context_Count] / MaxNumber[Title_Count], Title_Y + Title_Height + (Context_Count + 1) * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                Yellow,
                -1,
                8
                );
        }
        else {
            if (PrintData[Title_Count][Context_Count] <= MaxNumber[Title_Count]) {
                /* 如果数量充足且小于100%，按比例画绿色条形图 */
                rectangle(
                    FinalImage,
                    Point(Title_X + Context_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                    Point(Title_X + Context_X_Offset + Context_Width * PrintData[Title_Count][Context_Count] / MaxNumber[Title_Count], Title_Y + Title_Height + (Context_Count + 1) * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                    Green,
                    -1,
                    8
                    );
            }
            else {
                /* 如果数量充足且大于100%(公仓)，画满绿色条形图 */
                rectangle(
                    FinalImage,
                    Point(Title_X + Context_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                    Point(Title_X + Context_X_Offset + Context_Width , Title_Y + Title_Height + (Context_Count + 1) * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
                    Green,
                    -1,
                    8
                    );
            }
        }

        /* 输出物品数量以及上限数量 */
        sprintf_s (Number_Text, 20, "%d / %d", PrintData[Title_Count][Context_Count], MaxNumber[Title_Count]);
        putTextHusky(
            FinalImage,
            Number_Text,
            Point(Title_X + Context_X_Offset + Context_Width / 2 + Text_X_Offset - Number_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset + Text_Y_Offset),
            Black,
            Text_Size,
            "微软雅黑",
            false,
            false
        );

        /* 输出物品文字 */
        putTextHusky(
            FinalImage,
            PrintName[Title_Count][Context_Count],
            Point (Title_X + Context_X_Offset + Context_Width + Text_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset + Text_Y_Offset),
            White,
            Text_Size,
            "微软雅黑",
            false,
            false
            );
    }
    Now_Y = Title_Y + Title_Height + Context_Count * Context_Height + 2 * Context_Count * Context_Y_Offset; /* 记录当前高度，即一个Title输出完毕后的高度 */
    Title_Count++;
    return;
}


void Screen_Print()
{

    TransData();
    /* 比例初始化 */
    Init_Proportion();


    DrawTable(4, OneFourthWidth, 30, 0, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14,"材料",50);

    DrawTable(5, OneFourthWidth, 30, 0, Now_Y, 60, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "医疗用品", 50);

    DrawTable(5, OneFourthWidth, 30, 0, Now_Y, 60, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "重型弹药", 50);

    Now_Y = 0;

    DrawTable(12, OneFourthWidth, 30, OneFourthWidth, Now_Y, 45, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "轻武器", 50);

    DrawTable(15, OneFourthWidth, 30, OneFourthWidth, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "工具", 50);
        
    Now_Y = 0;

    DrawTable(21, OneFourthWidth, 30, OneFourthWidth * 2, Now_Y, 45, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "重武器", 50);

    DrawTable(8, OneFourthWidth, 30, OneFourthWidth * 2, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "制服", 50);

    Now_Y = 0;

    DrawTable(11, OneFourthWidth, 30, OneFourthWidth * 3, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "载具", 50);

    DrawTable(3, OneFourthWidth, 30, OneFourthWidth * 3, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "结构", 50);

    return;
}

/*
*   将识别到的物品数据传输至PrintData[][]中，有利于for()循环调用
*/
void TransData()
{
    /* Bmats Emats Hemats Rmats */
    PrintData[0][0] = Temp_Save_Data[6][19];
    PrintData[0][1] = Temp_Save_Data[6][21];
    PrintData[0][2] = Temp_Save_Data[6][24];
    PrintData[0][3] = Temp_Save_Data[6][27];

    sprintf_s(PrintName[0][0], 50, "基础材料");
    sprintf_s(PrintName[0][1], 50, "爆炸材料");
    sprintf_s(PrintName[0][2], 50, "高爆材料");
    sprintf_s(PrintName[0][3], 50, "精炼材料");

    /* 绷带 血浆 医疗箱 急救箱 衣服 */
    PrintData[1][0] = Temp_Save_Data[5][1];
    PrintData[1][1] = Temp_Save_Data[5][2];
    PrintData[1][2] = Temp_Save_Data[5][3];
    PrintData[1][3] = Temp_Save_Data[5][4];
    PrintData[1][4] = Temp_Save_Data[5][5];

    sprintf_s(PrintName[1][0], 50, "绷带");
    sprintf_s(PrintName[1][1], 50, "血浆");
    sprintf_s(PrintName[1][2], 50, "医疗箱");
    sprintf_s(PrintName[1][3], 50, "急救箱");
    sprintf_s(PrintName[1][4], 50, "士兵制服");

    /* 120mm 150mm 250mm 40mm 68mm */
    PrintData[2][0] = Temp_Save_Data[3][8];
    PrintData[2][1] = Temp_Save_Data[3][6];
    PrintData[2][2] = Temp_Save_Data[3][10];
    PrintData[2][3] = Temp_Save_Data[3][12];
    PrintData[2][4] = Temp_Save_Data[3][11];

    sprintf_s(PrintName[2][0], 50, "120mm");
    sprintf_s(PrintName[2][1], 50, "150mm");
    sprintf_s(PrintName[2][2], 50, "250mm");
    sprintf_s(PrintName[2][3], 50, "40mm");
    sprintf_s(PrintName[2][4], 50, "68mm");

    /* 12.7 轻机 重机 7.62 阿根廷 7.92 暴风步枪 9mm 1号位冲锋枪 木柄雷 毒气 烟雾 */
    PrintData[3][0] = Temp_Save_Data[1][39];
    PrintData[3][1] = Temp_Save_Data[1][5];
    PrintData[3][2] = Temp_Save_Data[1][6];
    PrintData[3][3] = Temp_Save_Data[1][29];
    PrintData[3][4] = Temp_Save_Data[1][19];
    PrintData[3][5] = Temp_Save_Data[1][4];
    PrintData[3][6] = Temp_Save_Data[1][1];
    PrintData[3][7] = Temp_Save_Data[1][36];
    PrintData[3][8] = Temp_Save_Data[1][33];
    PrintData[3][9] = Temp_Save_Data[1][8];
    PrintData[3][10] = Temp_Save_Data[1][38];
    PrintData[3][11] = Temp_Save_Data[1][37];

    sprintf_s(PrintName[3][0], 50, "12.7mm");
    sprintf_s(PrintName[3][1], 50, "轻机枪");
    sprintf_s(PrintName[3][2], 50, "重机枪");
    sprintf_s(PrintName[3][3], 50, "7.62mm");
    sprintf_s(PrintName[3][4], 50, "阿根廷步枪");
    sprintf_s(PrintName[3][5], 50, "7.92mm");
    sprintf_s(PrintName[3][6], 50, "风暴步枪");
    sprintf_s(PrintName[3][7], 50, "9mm");
    sprintf_s(PrintName[3][8], 50, "主武器冲锋枪");
    sprintf_s(PrintName[3][9], 50, "木柄雷");
    sprintf_s(PrintName[3][10], 50, "毒气雷");
    sprintf_s(PrintName[3][11], 50, "烟雾雷");

    /* 地雷 望远镜 刺刀 面具 滤芯 炸药 起爆器 金箍棒 侦听 无线电 无线电背包 铲子 三脚架 扳手 喷火器燃料 */
    PrintData[4][0] = Temp_Save_Data[4][15];
    PrintData[4][1] = Temp_Save_Data[4][2];
    PrintData[4][2] = Temp_Save_Data[4][21];
    PrintData[4][3] = Temp_Save_Data[4][22];
    PrintData[4][4] = Temp_Save_Data[4][23];
    PrintData[4][5] = Temp_Save_Data[4][4];
    PrintData[4][6] = Temp_Save_Data[4][11];
    PrintData[4][7] = Temp_Save_Data[4][3];
    PrintData[4][8] = Temp_Save_Data[4][7];
    PrintData[4][9] = Temp_Save_Data[4][25];
    PrintData[4][10] = Temp_Save_Data[4][9];
    PrintData[4][11] = Temp_Save_Data[4][13];
    PrintData[4][12] = Temp_Save_Data[4][16];
    PrintData[4][13] = Temp_Save_Data[4][19];
    PrintData[4][14] = Temp_Save_Data[4][5];

    sprintf_s(PrintName[4][0], 50, "地雷");
    sprintf_s(PrintName[4][1], 50, "望远镜");
    sprintf_s(PrintName[4][2], 50, "刺刀");
    sprintf_s(PrintName[4][3], 50, "防毒面具");
    sprintf_s(PrintName[4][4], 50, "防毒滤芯");
    sprintf_s(PrintName[4][5], 50, "高爆炸药");
    sprintf_s(PrintName[4][6], 50, "高爆炸药起爆器");
    sprintf_s(PrintName[4][7], 50, "金箍棒");
    sprintf_s(PrintName[4][8], 50, "侦听设备");
    sprintf_s(PrintName[4][9], 50, "无线电");
    sprintf_s(PrintName[4][10], 50, "无线电背包");
    sprintf_s(PrintName[4][11], 50, "铲子");
    sprintf_s(PrintName[4][12], 50, "三脚架");
    sprintf_s(PrintName[4][13], 50, "扳手");
    sprintf_s(PrintName[4][14], 50, "喷火器燃料");

    /* 架设机枪 20mm 30mm 30mm炮 架设AT枪 火焰发射器 粘弹 高爆手雷 迫击炮管 照明弹 高爆弹 破片弹 AP/RPG ARC/RPG 重筒 铁拳 RPG 轻筒 掷弹筒 架设掷弹筒 高爆枪榴弹 */
    PrintData[5][0] = Temp_Save_Data[2][16];
    PrintData[5][1] = Temp_Save_Data[2][3];
    PrintData[5][2] = Temp_Save_Data[2][18];
    PrintData[5][3] = Temp_Save_Data[2][17];
    PrintData[5][4] = Temp_Save_Data[2][1];
    PrintData[5][5] = Temp_Save_Data[2][10];
    PrintData[5][6] = Temp_Save_Data[2][26];
    PrintData[5][7] = Temp_Save_Data[2][25];
    PrintData[5][8] = Temp_Save_Data[2][19];
    PrintData[5][9] = Temp_Save_Data[2][20];
    PrintData[5][10] = Temp_Save_Data[2][22];
    PrintData[5][11] = Temp_Save_Data[2][21];
    PrintData[5][12] = Temp_Save_Data[2][6];
    PrintData[5][13] = Temp_Save_Data[2][9];
    PrintData[5][14] = Temp_Save_Data[2][5];
    PrintData[5][15] = Temp_Save_Data[2][24];
    PrintData[5][16] = Temp_Save_Data[2][30];
    PrintData[5][17] = Temp_Save_Data[2][4];
    PrintData[5][18] = Temp_Save_Data[2][12];
    PrintData[5][19] = Temp_Save_Data[2][13];
    PrintData[5][20] = Temp_Save_Data[2][14];

    sprintf_s(PrintName[5][0], 50, "架设机枪");
    sprintf_s(PrintName[5][1], 50, "20mm");
    sprintf_s(PrintName[5][2], 50, "30mm");
    sprintf_s(PrintName[5][3], 50, "30mm炮");
    sprintf_s(PrintName[5][4], 50, "架设AT枪");
    sprintf_s(PrintName[5][5], 50, "喷火器");
    sprintf_s(PrintName[5][6], 50, "粘弹");
    sprintf_s(PrintName[5][7], 50, "高爆手雷");
    sprintf_s(PrintName[5][8], 50, "迫击炮管");
    sprintf_s(PrintName[5][9], 50, "照明弹");
    sprintf_s(PrintName[5][10], 50, "高爆弹");
    sprintf_s(PrintName[5][11], 50, "破片弹");
    sprintf_s(PrintName[5][12], 50, "穿甲/火箭弹");
    sprintf_s(PrintName[5][13], 50, "曲射穿甲/火箭弹");
    sprintf_s(PrintName[5][14], 50, "重筒");
    sprintf_s(PrintName[5][15], 50, "铁拳");
    sprintf_s(PrintName[5][16], 50, "RPG");
    sprintf_s(PrintName[5][17], 50, "轻筒");
    sprintf_s(PrintName[5][18], 50, "掷弹筒");
    sprintf_s(PrintName[5][19], 50, "架设掷弹筒");
    sprintf_s(PrintName[5][20], 50, "高爆枪榴弹");


    /* 扳手衣服 掷弹兵衣服 冬季衣服 雨衣 医疗衣服 侦察衣服 坦克兵衣服 重甲衣服 */
    PrintData[6][0] = Temp_Save_Data[7][4];
    PrintData[6][1] = Temp_Save_Data[7][6];
    PrintData[6][2] = Temp_Save_Data[7][14];
    PrintData[6][3] = Temp_Save_Data[7][11];
    PrintData[6][4] = Temp_Save_Data[7][7];
    PrintData[6][5] = Temp_Save_Data[7][12];
    PrintData[6][6] = Temp_Save_Data[7][18];
    PrintData[6][7] = Temp_Save_Data[7][2];

    sprintf_s(PrintName[6][0], 50, "工程兵服");
    sprintf_s(PrintName[6][1], 50, "掷弹兵服");
    sprintf_s(PrintName[6][2], 50, "冬季衣服");
    sprintf_s(PrintName[6][3], 50, "雨衣");
    sprintf_s(PrintName[6][4], 50, "医疗兵服");
    sprintf_s(PrintName[6][5], 50, "侦察兵服");
    sprintf_s(PrintName[6][6], 50, "坦克兵服");
    sprintf_s(PrintName[6][7], 50, "重甲兵服");

    /* 两栖人员登陆艇 平板卡车 半履带车 R-1补给卡 救护车 越野车 86K-a 突击虎 85K-b H-5 68mm推炮 */

    PrintData[7][0] = Temp_Save_Data[8][19] * 3 + Temp_Save_Data[9][45];
    PrintData[7][1] = Temp_Save_Data[8][15] * 3 + Temp_Save_Data[9][31];
    PrintData[7][2] = Temp_Save_Data[8][16] * 3 + Temp_Save_Data[9][34];
    PrintData[7][3] = Temp_Save_Data[8][42] * 3 + Temp_Save_Data[9][90];
    PrintData[7][4] = Temp_Save_Data[8][1] * 3 + Temp_Save_Data[9][1];
    PrintData[7][5] = Temp_Save_Data[8][39] * 3 + Temp_Save_Data[9][80];
    PrintData[7][6] = Temp_Save_Data[8][23] * 3  + Temp_Save_Data[9][59];
    PrintData[7][7] = Temp_Save_Data[8][27] * 3 + Temp_Save_Data[9][70];
    PrintData[7][8] = Temp_Save_Data[8][25] * 5 + Temp_Save_Data[9][65];
    PrintData[7][9] = Temp_Save_Data[8][21] * 3 + Temp_Save_Data[9][52];
    PrintData[7][10] = Temp_Save_Data[8][9] * 3 + Temp_Save_Data[9][23];

    sprintf_s(PrintName[7][0], 50, "两栖人员登陆艇");
    sprintf_s(PrintName[7][1], 50, "平板卡车");
    sprintf_s(PrintName[7][2], 50, "半履带车");
    sprintf_s(PrintName[7][3], 50, "R-1补给卡");
    sprintf_s(PrintName[7][4], 50, "救护车");
    sprintf_s(PrintName[7][5], 50, "越野车");
    sprintf_s(PrintName[7][6], 50, "86K-a");
    sprintf_s(PrintName[7][7], 50, "突击虎");
    sprintf_s(PrintName[7][8], 50, "85K-b");
    sprintf_s(PrintName[7][9], 50, "H-5");
    sprintf_s(PrintName[7][10], 50, "68mm推炮");

    /* 150mm炮 12.7mm坐地机枪 坐地萝卜 */

    PrintData[8][0] = Temp_Save_Data[10][3] * 3 + Temp_Save_Data[11][5];
    PrintData[8][1] = Temp_Save_Data[10][11] * 3 + Temp_Save_Data[11][8];
    PrintData[8][2] = Temp_Save_Data[10][10] * 3 + Temp_Save_Data[11][7];

    sprintf_s(PrintName[8][0], 50, "150mm炮");
    sprintf_s(PrintName[8][1], 50, "12.7mm坐地机枪");
    sprintf_s(PrintName[8][2], 50, "坐地萝卜");
    
    return;
}