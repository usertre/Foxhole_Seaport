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
*   [param]Times               ���ɼ�������ͼ
*   [param]Title_Width         ����ı������
*   [param]Title_Height        ����ı����߶�
*   [param]Title_X             ���ⱳ�����Ͻǵĺ�����
*   [param]Title_Y             ���ⱳ�����Ͻǵ�������
*   [param]Title_Text_Offset   �����ı���0��λ�þ�������������ƫ�Ƶľ���
*   [param]Context_X_Offset    ����ͼ�������ɫ��ƫ����
*   [param]Context_Y_Offset    ����ͼ�ϲ�����ɫ��ƫ����
*   [param]Context_Width       ����ͼ����
*   [param]Context_Height      ����ͼ�߶�
*   [param]Text_X_Offset       ��Ʒ���־�������ͼ�Ҷ˵�X��ƫ��ֵ
*   [param]Text_Y_Offset       ��Ʒ���־�������ͼ�ϲ��Y��ƫ��ֵ
*   [param]Text_Size           ��Ʒ���ֵ������С
*   [param]*Text               ��������
*   [param]Number_Offset       ��Ʒ����������ͼ���������ƫ��ֵ
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
    int Context_Count = 0; /* �ڼ���Ҫ��ʾ����Ʒ */
    char Number_Text[20] = {0}; /* ����ı��е����ֲ��� */

    /* �����ⱳ��ɫ */
    rectangle (
        FinalImage,
        Point (Title_X, Title_Y),
        Point (Title_X + Title_Width, Title_Y + Title_Height),
        TitleColor,
        -1,
        8
        );
    /* ����������� */
    putTextHusky (
        FinalImage,
        Text,
        Point (int(Title_X + (Title_Width / 2) - Title_Text_Offset), Title_Y),
        White,
        TitleFontSize,
        "΢���ź�",
        false, 
        false
        );

    for (Context_Count = 0;Context_Count < Times; Context_Count++) {
        /* ����ɫ���� */
        rectangle(
            FinalImage,
            Point (Title_X, Title_Y + Title_Height + Context_Count * Context_Height + 2 * Context_Count * Context_Y_Offset),
            Point (Title_X + Title_Width, Title_Y + Title_Height + (Context_Count + 1) * Context_Height + 2 * (Context_Count + 1) * Context_Y_Offset),
            ContextBackGroundColor,
            -1,
            8
            );
        /* ������ͼ�İ�ɫ���� */
        rectangle(
            FinalImage,
            Point (Title_X + Context_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
            Point (Title_X + Context_X_Offset + Context_Width, Title_Y + Title_Height + (Context_Count + 1) * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset),
            White,
            -1,
            8
            );

        /* ������ͼǰ��ɫ */
        if (PrintData[Title_Count][Context_Count] < (MaxNumber[Title_Count] * 1.0 * OemProportion[Title_Count][Context_Count][0])) {
            /* �����������������ɫ����ͼ */
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
            /* �������һ�㣬����ɫ����ͼ */
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
                /* �������������С��100%������������ɫ����ͼ */
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
                /* ������������Ҵ���100%(����)��������ɫ����ͼ */
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

        /* �����Ʒ�����Լ��������� */
        sprintf_s (Number_Text, 20, "%d / %d", PrintData[Title_Count][Context_Count], MaxNumber[Title_Count]);
        putTextHusky(
            FinalImage,
            Number_Text,
            Point(Title_X + Context_X_Offset + Context_Width / 2 + Text_X_Offset - Number_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset + Text_Y_Offset),
            Black,
            Text_Size,
            "΢���ź�",
            false,
            false
        );

        /* �����Ʒ���� */
        putTextHusky(
            FinalImage,
            PrintName[Title_Count][Context_Count],
            Point (Title_X + Context_X_Offset + Context_Width + Text_X_Offset, Title_Y + Title_Height + Context_Count * Context_Height + (2 * Context_Count + 1) * Context_Y_Offset + Text_Y_Offset),
            White,
            Text_Size,
            "΢���ź�",
            false,
            false
            );
    }
    Now_Y = Title_Y + Title_Height + Context_Count * Context_Height + 2 * Context_Count * Context_Y_Offset; /* ��¼��ǰ�߶ȣ���һ��Title�����Ϻ�ĸ߶� */
    Title_Count++;
    return;
}


void Screen_Print()
{

    TransData();
    /* ������ʼ�� */
    Init_Proportion();


    DrawTable(4, OneFourthWidth, 30, 0, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14,"����",50);

    DrawTable(5, OneFourthWidth, 30, 0, Now_Y, 60, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "ҽ����Ʒ", 50);

    DrawTable(5, OneFourthWidth, 30, 0, Now_Y, 60, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "���͵�ҩ", 50);

    Now_Y = 0;

    DrawTable(12, OneFourthWidth, 30, OneFourthWidth, Now_Y, 45, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "������", 50);

    DrawTable(15, OneFourthWidth, 30, OneFourthWidth, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "����", 50);
        
    Now_Y = 0;

    DrawTable(21, OneFourthWidth, 30, OneFourthWidth * 2, Now_Y, 45, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "������", 50);

    DrawTable(8, OneFourthWidth, 30, OneFourthWidth * 2, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "�Ʒ�", 50);

    Now_Y = 0;

    DrawTable(11, OneFourthWidth, 30, OneFourthWidth * 3, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "�ؾ�", 50);

    DrawTable(3, OneFourthWidth, 30, OneFourthWidth * 3, Now_Y, 30, 5, 5, OneFourthWidth / 2, 20, 20, 0, 14, "�ṹ", 50);

    return;
}

/*
*   ��ʶ�𵽵���Ʒ���ݴ�����PrintData[][]�У�������for()ѭ������
*/
void TransData()
{
    /* Bmats Emats Hemats Rmats */
    PrintData[0][0] = Temp_Save_Data[6][19];
    PrintData[0][1] = Temp_Save_Data[6][21];
    PrintData[0][2] = Temp_Save_Data[6][24];
    PrintData[0][3] = Temp_Save_Data[6][27];

    sprintf_s(PrintName[0][0], 50, "��������");
    sprintf_s(PrintName[0][1], 50, "��ը����");
    sprintf_s(PrintName[0][2], 50, "�߱�����");
    sprintf_s(PrintName[0][3], 50, "��������");

    /* ���� Ѫ�� ҽ���� ������ �·� */
    PrintData[1][0] = Temp_Save_Data[5][1];
    PrintData[1][1] = Temp_Save_Data[5][2];
    PrintData[1][2] = Temp_Save_Data[5][3];
    PrintData[1][3] = Temp_Save_Data[5][4];
    PrintData[1][4] = Temp_Save_Data[5][5];

    sprintf_s(PrintName[1][0], 50, "����");
    sprintf_s(PrintName[1][1], 50, "Ѫ��");
    sprintf_s(PrintName[1][2], 50, "ҽ����");
    sprintf_s(PrintName[1][3], 50, "������");
    sprintf_s(PrintName[1][4], 50, "ʿ���Ʒ�");

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

    /* 12.7 ��� �ػ� 7.62 ����͢ 7.92 ���粽ǹ 9mm 1��λ���ǹ ľ���� ���� ���� */
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
    sprintf_s(PrintName[3][1], 50, "���ǹ");
    sprintf_s(PrintName[3][2], 50, "�ػ�ǹ");
    sprintf_s(PrintName[3][3], 50, "7.62mm");
    sprintf_s(PrintName[3][4], 50, "����͢��ǹ");
    sprintf_s(PrintName[3][5], 50, "7.92mm");
    sprintf_s(PrintName[3][6], 50, "�籩��ǹ");
    sprintf_s(PrintName[3][7], 50, "9mm");
    sprintf_s(PrintName[3][8], 50, "���������ǹ");
    sprintf_s(PrintName[3][9], 50, "ľ����");
    sprintf_s(PrintName[3][10], 50, "������");
    sprintf_s(PrintName[3][11], 50, "������");

    /* ���� ��Զ�� �̵� ��� ��о ըҩ ���� �𹿰� ���� ���ߵ� ���ߵ米�� ���� ���ż� ���� �����ȼ�� */
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

    sprintf_s(PrintName[4][0], 50, "����");
    sprintf_s(PrintName[4][1], 50, "��Զ��");
    sprintf_s(PrintName[4][2], 50, "�̵�");
    sprintf_s(PrintName[4][3], 50, "�������");
    sprintf_s(PrintName[4][4], 50, "������о");
    sprintf_s(PrintName[4][5], 50, "�߱�ըҩ");
    sprintf_s(PrintName[4][6], 50, "�߱�ըҩ����");
    sprintf_s(PrintName[4][7], 50, "�𹿰�");
    sprintf_s(PrintName[4][8], 50, "�����豸");
    sprintf_s(PrintName[4][9], 50, "���ߵ�");
    sprintf_s(PrintName[4][10], 50, "���ߵ米��");
    sprintf_s(PrintName[4][11], 50, "����");
    sprintf_s(PrintName[4][12], 50, "���ż�");
    sprintf_s(PrintName[4][13], 50, "����");
    sprintf_s(PrintName[4][14], 50, "�����ȼ��");

    /* �����ǹ 20mm 30mm 30mm�� ����ATǹ ���淢���� ճ�� �߱����� �Ȼ��ڹ� ������ �߱��� ��Ƭ�� AP/RPG ARC/RPG ��Ͳ ��ȭ RPG ��Ͳ ����Ͳ ��������Ͳ �߱�ǹ�� */
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

    sprintf_s(PrintName[5][0], 50, "�����ǹ");
    sprintf_s(PrintName[5][1], 50, "20mm");
    sprintf_s(PrintName[5][2], 50, "30mm");
    sprintf_s(PrintName[5][3], 50, "30mm��");
    sprintf_s(PrintName[5][4], 50, "����ATǹ");
    sprintf_s(PrintName[5][5], 50, "�����");
    sprintf_s(PrintName[5][6], 50, "ճ��");
    sprintf_s(PrintName[5][7], 50, "�߱�����");
    sprintf_s(PrintName[5][8], 50, "�Ȼ��ڹ�");
    sprintf_s(PrintName[5][9], 50, "������");
    sprintf_s(PrintName[5][10], 50, "�߱���");
    sprintf_s(PrintName[5][11], 50, "��Ƭ��");
    sprintf_s(PrintName[5][12], 50, "����/�����");
    sprintf_s(PrintName[5][13], 50, "���䴩��/�����");
    sprintf_s(PrintName[5][14], 50, "��Ͳ");
    sprintf_s(PrintName[5][15], 50, "��ȭ");
    sprintf_s(PrintName[5][16], 50, "RPG");
    sprintf_s(PrintName[5][17], 50, "��Ͳ");
    sprintf_s(PrintName[5][18], 50, "����Ͳ");
    sprintf_s(PrintName[5][19], 50, "��������Ͳ");
    sprintf_s(PrintName[5][20], 50, "�߱�ǹ��");


    /* �����·� �������·� �����·� ���� ҽ���·� ����·� ̹�˱��·� �ؼ��·� */
    PrintData[6][0] = Temp_Save_Data[7][4];
    PrintData[6][1] = Temp_Save_Data[7][6];
    PrintData[6][2] = Temp_Save_Data[7][14];
    PrintData[6][3] = Temp_Save_Data[7][11];
    PrintData[6][4] = Temp_Save_Data[7][7];
    PrintData[6][5] = Temp_Save_Data[7][12];
    PrintData[6][6] = Temp_Save_Data[7][18];
    PrintData[6][7] = Temp_Save_Data[7][2];

    sprintf_s(PrintName[6][0], 50, "���̱���");
    sprintf_s(PrintName[6][1], 50, "��������");
    sprintf_s(PrintName[6][2], 50, "�����·�");
    sprintf_s(PrintName[6][3], 50, "����");
    sprintf_s(PrintName[6][4], 50, "ҽ�Ʊ���");
    sprintf_s(PrintName[6][5], 50, "������");
    sprintf_s(PrintName[6][6], 50, "̹�˱���");
    sprintf_s(PrintName[6][7], 50, "�ؼױ���");

    /* ������Ա��½ͧ ƽ�忨�� ���Ĵ��� R-1������ �Ȼ��� ԽҰ�� 86K-a ͻ���� 85K-b H-5 68mm���� */

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

    sprintf_s(PrintName[7][0], 50, "������Ա��½ͧ");
    sprintf_s(PrintName[7][1], 50, "ƽ�忨��");
    sprintf_s(PrintName[7][2], 50, "���Ĵ���");
    sprintf_s(PrintName[7][3], 50, "R-1������");
    sprintf_s(PrintName[7][4], 50, "�Ȼ���");
    sprintf_s(PrintName[7][5], 50, "ԽҰ��");
    sprintf_s(PrintName[7][6], 50, "86K-a");
    sprintf_s(PrintName[7][7], 50, "ͻ����");
    sprintf_s(PrintName[7][8], 50, "85K-b");
    sprintf_s(PrintName[7][9], 50, "H-5");
    sprintf_s(PrintName[7][10], 50, "68mm����");

    /* 150mm�� 12.7mm���ػ�ǹ �����ܲ� */

    PrintData[8][0] = Temp_Save_Data[10][3] * 3 + Temp_Save_Data[11][5];
    PrintData[8][1] = Temp_Save_Data[10][11] * 3 + Temp_Save_Data[11][8];
    PrintData[8][2] = Temp_Save_Data[10][10] * 3 + Temp_Save_Data[11][7];

    sprintf_s(PrintName[8][0], 50, "150mm��");
    sprintf_s(PrintName[8][1], 50, "12.7mm���ػ�ǹ");
    sprintf_s(PrintName[8][2], 50, "�����ܲ�");
    
    return;
}