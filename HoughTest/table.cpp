#include "table.h"




Table::Table()
{
	doInit = false;
}

Table::Table(int theta_res)
{
	doInit = false;
	init(theta_res);
}

void Table::init(int theta_res)
{
	if (!doInit) {
		//PIK:単位角度
		const float PIK = M_PI / (float)theta_res;
		//三角関数テーブルを作成
		sn = new float[theta_res];
		cs = new float[theta_res];
		for (int i = 0; i<theta_res; i++) {
			sn[i] = (float)sin(PIK*i);
			cs[i] = (float)cos(PIK*i);
		}
		doInit = true;
	}
}


float Table::cos_t(int theta)
{
	return cs[theta];
}

float Table::sin_t(int theta)
{
	return sn[theta];
}

Table::~Table()
{
	delete[] sn;
	delete[] cs;
}
