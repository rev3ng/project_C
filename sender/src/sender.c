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
#include <netinet/in.h>



int main (void) {

	printf ("Load");
	void * Lib = malloc(sizeof(void));
	void * Icmp = malloc(sizeof (void));
	//int *a, *b;

	//Menu (a ,b);
	printf ("Load");
	Lib = Load_ipv4();
	unsigned short* (*ipv4) ();
	ipv4 = dlsym(Lib, "CreateIpv4Packet");

	Icmp = Load_icmp();
	unsigned short* (*icmp) (unsigned char *);
	icmp = dlsym(Icmp, "CreateIcmpPacket");

	unsigned short *asd = (*ipv4)();
	icmp ( (unsigned char*) asd );

	SendPacket(asd);
	//for ( int i = 0; i < 10; i++)
	//	printf ("\n%d: %X", i, ntohs((unsigned short)asd[i]));
	return EXIT_SUCCESS;
}
