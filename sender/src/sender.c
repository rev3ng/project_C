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
//#include "linkedList_lib.h"
#include <dlfcn.h>
#include <netinet/in.h>



int main (void) {

	//printf ("Load\n");
	void * Ipv4_lib = malloc(sizeof (void));
	void * Icmp_lib = malloc(sizeof (void));
	//void * List_lib = malloc(sizeof (void));

	int *count;
	char *interface;
	unsigned short *datagram;
	unsigned short * (*ipv4) () = malloc (sizeof (unsigned short *));
	void (*icmp) (unsigned char *) = malloc (sizeof(void));

	datagram = malloc (sizeof (4096));
	count = malloc (sizeof (int));
	interface = malloc (sizeof (char)*32);


	int a = Menu (count, interface);

	Ipv4_lib = LoadIpv4();

	ipv4 = dlsym(Ipv4_lib, "CreateIpv4Packet");
	datagram = (*ipv4)();
	//dlclose ( Ipv4_lib );
	//free ( Ipv4_lib );

	if ( a == 2 ){

		Icmp_lib = LoadIcmp();

		icmp = dlsym(Icmp_lib, "CreateIcmpPacket");
		(*icmp) ((unsigned char *) datagram);
		//dlclose( Icmp_lib );
		//free ( Icmp_lib );
	}


	LoadToList( count, (char*) datagram );
	PrintList ();

	SendPacket( interface );
	//print_list();

	/*dlclose ( Ipv4_lib );
	if ( Icmp_lib != NULL ){
		dlclose ( Icmp_lib );
		//free ( Icmp_lib );
	}*/
	//free ( Ipv4_lib );


	//free ( interface );
	//free ( count );
	//free ( ipv4 );
	//free ( icmp );
	EXIT_SUCCESS;
}
