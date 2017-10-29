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

	int i = Load_ipv4();
	char* (*ipv4) ();
	ipv4 = dlsym(IpLib, "Create_ipv4_packet");
	char *asd = (*ipv4)();

	return EXIT_SUCCESS;
}
