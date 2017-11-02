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
	void * Ipv4_lib = malloc(sizeof (void));
	void * Icmp_lib = malloc(sizeof (void));
	void * List_lib = malloc(sizeof (void));

	int *count;
	char *interface;
	unsigned short *dtgr;

	dtgr = malloc (sizeof (4096));
	count = malloc (sizeof (int));
	interface = malloc (sizeof (char)*32);


	int a = Menu (count, interface);

	Ipv4_lib = Load_ipv4();
	unsigned short* (*ipv4) ();
	ipv4 = dlsym(Ipv4_lib, "CreateIpv4Packet");
	dtgr = (*ipv4)();

	if ( a == 2 ){

		Icmp_lib = Load_icmp();
		unsigned short* (*icmp) (unsigned char *);
		icmp = dlsym(Icmp_lib, "CreateIcmpPacket");
		(*icmp) ((unsigned char *)dtgr);
	}

	List_lib = Load_list();
	void (*list) ( char * );
	void (*print) ();
	list = dlsym( List_lib, "insert_tail" );
	print = dlsym( List_lib, "print_list");

	(*list) ((char *) dtgr );
	(*list) ((char *) dtgr );
	(*list) ((char *) dtgr );
	(*list) ((char *) dtgr );
	(*list) ((char *) dtgr );
	(*print) ();
	//printf ("\nCount: %d", *count);


	SendPacket(dtgr, interface);


	dlclose ( Ipv4_lib );
	dlclose ( Icmp_lib );
	dlclose ( List_lib );

	EXIT_SUCCESS;
}
