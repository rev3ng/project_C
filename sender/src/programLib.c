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
int Load_ipv4 (){

	IpLib = dlopen("./ipv4_lib.so", RTLD_LAZY);
		if (!IpLib)
			return 0;
		else
			return 1;

}

//function to load ICMP library
int Load_icmp (){

	IcmpLib = dlopen("./icmp_lib.so", RTLD_LAZY);
		if (!IcmpLib)
			return 0;
		else
			return 1;

}

//funtion to load Linked list library
int Load_list (){

	LinkedLib = dlopen("./linkedList_lib.so", RTLD_LAZY);
		if (!LinkedLib)
			return 0;
		else
			return 1;

}

