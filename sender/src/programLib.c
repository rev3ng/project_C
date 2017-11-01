/*
 * programLib.c
 *
 *  Created on: Oct 29, 2017
 *      Author: konrad
 */
#include <dlfcn.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include "programLib.h"



//function to load IPv4 library
void * Load_ipv4 (){

	void *IpLib;	//handle to IP lib

	IpLib = dlopen("./ipv4_lib.so", RTLD_LAZY);
		if (!IpLib)
			return 0;
		else
			return IpLib;

}

//function to load ICMP library
void * Load_icmp (){

	void *IcmpLib;	//handle to ICMP lib

	IcmpLib = dlopen("./icmp_lib.so", RTLD_LAZY);
		if (!IcmpLib)
			return 0;
		else
			return IcmpLib;

}

//funtion to load Linked list library
void * Load_list (){

	void *LinkedLib;//handle to LinkedList lib

	LinkedLib = dlopen("./linkedList_lib.so", RTLD_LAZY);
		if (!LinkedLib)
			return 0;
		else
			return LinkedLib;

}

//function to send created packet
void SendPacket ( unsigned short *datagram ){

	struct iphdr *iph = (struct iphdr *) datagram;

	//open socket
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
		if (s == -1)
			printf ("\nSocket not opened\n");

		struct sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons (80);
		sin.sin_addr.s_addr = iph->daddr;

		for ( int i = 0; i <10; i++){

		if (sendto (s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
			perror("Sendto failed: ");
		else
			printf ("Packet send. Length : %d \n" , iph->tot_len);
		}

}

int Menu ( int *count, int *interface ) {

	char input [32];
	int result;

	printf ("Welcome to sender. What do you want to do: \n");
	printf ("[1] Send IPv4 packet \n");
	printf ("[2] Send ICMP packet \n");

	fgets ( input, 32, stdin );
	result = atoi (input);

	//printf ("\033[H\033[J");	//cleans console
	printf ("Which interface do you want to use? Type number of interface.\n");

	/*char cmd [12];
	sprintf(cmd, "/bin/ip link");
	system(cmd);
*/
	return 1;
}




