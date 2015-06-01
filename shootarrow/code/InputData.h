#ifndef INPUTDATA_H
#define INPUTDATA_H

struct InputData {
	int x;
	int y;
	int trig;
	int btnX;
	int btnO;
	int btnJoy;
	int btnTrig;
	int hatU;
	int hatD;
	int hatL;
	int hatR;
	InputData()
	{
		x = y = trig = 0;
		btnX = btnO = btnJoy = btnTrig = 0;
		hatU = hatD = hatL = hatR = 0;
	}
};

#endif