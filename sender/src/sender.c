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

	//printf ("Load\n");
	void * Lib = malloc(sizeof(void));
	void * Icmp = malloc(sizeof (void));
	int *count, *interface;
	unsigned short *dtgr;

	dtgr = malloc (sizeof (4096));
	count = malloc (sizeof (int));
	interface = malloc (sizeof (int));


	int a = Menu (count, interface);

	Lib = Load_ipv4();
	unsigned short* (*ipv4) ();
	ipv4 = dlsym(Lib, "CreateIpv4Packet");
	dtgr = (*ipv4)();

	if ( a == 2 ){

		Icmp = Load_icmp();
		unsigned short* (*icmp) (unsigned char *);
		icmp = dlsym(Icmp, "CreateIcmpPacket");
		(*icmp) ((unsigned char *)dtgr);
	}

	SendPacket(dtgr);


}
