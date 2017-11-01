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

//libraries handles declarations in "programLib.h"


int main (void) {


	void * Lib;
	void * Icmp;

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
