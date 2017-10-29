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


//libraries handles declarations in "programLib.h"


int main (void) {


printf ("%d", Load_ipv4());
printf ("%d", Load_icmp());
printf ("%d", Load_list());

	return EXIT_SUCCESS;
}
