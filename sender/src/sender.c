/*
 ============================================================================
 Name        : sender.c
 Author      : Konrad Śledziewski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "programLib.h"
#include <dlfcn.h>

//libraries handles declarations in "programLib.h"


int main (void) {


	void * Lib;

	Lib = Load_ipv4();
	char* (*ipv4) ();
	ipv4 = dlsym(Lib, "CreateIpv4Packet");

	char *asd = (*ipv4)();

	return EXIT_SUCCESS;
}
