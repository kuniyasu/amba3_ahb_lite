/*
 * main.cpp
 *
 *  Created on: 2013/12/31
 *      Author: Kuniyasu
 */

#include "TOP.h"

TOP* top;

int sc_main(int argc, char* argv[]){
	top = new TOP("top");
	sc_start();
	return 0;
}


