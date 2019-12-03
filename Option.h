#pragma once
#include "Menu.h"

class Input;

class Option:public Menu{
private:
	int zanki;
public:
	Option();
	void setZanki(Input *input);
	void show();
};