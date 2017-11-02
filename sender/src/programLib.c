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
#include <net/if.h>
#include "programLib.h"
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>



//function to load IPv4 library
void * Load_ipv4 (){

	void *IpLib = malloc ( sizeof (void ) );	//handle to IP lib

	IpLib = dlopen("./ipv4_lib.so", RTLD_LAZY);
		if (!IpLib)
			return 0;
		else
			return IpLib;

}

//function to load ICMP library
void * Load_icmp (){

	void *IcmpLib = malloc ( sizeof (void ) );	//handle to ICMP lib

	IcmpLib = dlopen("./icmp_lib.so", RTLD_LAZY);
		if (!IcmpLib)
			return 0;
		else
			return IcmpLib;

}

//funtion to load Linked list library
void * Load_list (){

	void *LinkedLib = malloc ( sizeof (void ) );//handle to LinkedList lib

	LinkedLib = dlopen("./linkedList_lib.so", RTLD_LAZY);
		if (!LinkedLib)
			return 0;
		else
			return LinkedLib;

}

//function to send created packet
int SendPacket ( unsigned short *datagram, char *interface ){

	struct iphdr *iph = (struct iphdr *) datagram;

	//open socket
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
		if (s == -1){
			printf ("\nSocket not opened\n");
			return EXIT_FAILURE;
		}


	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons (80);
	sin.sin_addr.s_addr = iph->daddr;

	struct ifreq ifr;
	//char interface [40];

	//strcpy(interface, "enp9s0");

	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", interface);
	if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
			perror("ioctl() failed to find interface ");
			return (EXIT_FAILURE);
		}
	//close (s);
	if (setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
		printf ("\nNot binded\n");
		return EXIT_FAILURE;
	}
	//bind (s, sin,  );
	//for ( int i = 0; i <10; i++){
	if (sendto (s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof (sin)) < 0){
		perror("Sendto failed: ");
		return EXIT_FAILURE;
	}
	else
		printf ("Packet send. Length : %d \n" , iph->tot_len);
	//}
		//int bytes = write (s, datagram, iph -> tot_len);
		//printf ("Bytes sent:%d\n", bytes);
	return EXIT_SUCCESS;
}

int Menu ( int *count, char *interface ) {

	char input [32];
	int result;

	//printf ("%d", sizeof (struct iphdr));

	printf ("\033[H\033[J");
	printf ("Welcome to sender. What do you want to do: \n");
	printf ("[1] Send IPv4 packet \n");
	printf ("[2] Send ICMP packet \n");

	fgets ( input, 32, stdin );
	result = atoi (input);

	printf ("\033[H\033[J");	//cleans console
	printf ("Which interface do you want to use? Type name of interface.\n");

	char cmd [30];
	sprintf(cmd, "/bin/ip link");
	system(cmd);

	printf ("Name:");
	fgets ( input, 32, stdin );
	memcpy ( interface, input, strlen (input)-1 );
	//printf ("\n strllen:%d", strlen ( interface ));
	//str

	printf ("\nHow many packets do you want to send? ");
	fgets ( input, 32, stdin );
	*count = atoi (input);

	return result;
}




