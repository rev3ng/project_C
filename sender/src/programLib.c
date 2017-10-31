/*
 * programLib.c
 *
 *  Created on: Oct 29, 2017
 *      Author: konrad
 */
#include <dlfcn.h>
#include <stdio.h>
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
void SendPacket ( char *datagram, unsigned short size ){

	//open socket

}
