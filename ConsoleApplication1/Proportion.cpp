#include <Proportion.h>
#include <cstdio>

double OemProportion[9][30][2];
int Proportion_Number[9];
/*
* ��ʼ����ɫ����ɫ����ɫ��������ʣ�С��OemProportion[i][j][0]��Ϊ��ɫ������OemProportion[i][j][1]��Ϊ��ɫ������Ϊ��ɫ
*/
void Init_Proportion()
{
	Proportion_Number[0] = 4;
	Proportion_Number[1] = 5;
	Proportion_Number[2] = 5;
	Proportion_Number[3] = 12;
	Proportion_Number[4] = 15;
	Proportion_Number[5] = 21;
	Proportion_Number[6] = 28;
	Proportion_Number[7] = 11;
	Proportion_Number[8] = 3;
	
	for (int i = 0;i < 9;++i) {
		for (int j = 0;j < Proportion_Number[i];++j) {
			OemProportion[i][j][0] = 0.2;
			OemProportion[i][j][1] = 0.8;
		}
	}

	return;
}