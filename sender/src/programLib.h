/*
 * programLib.h
 *
 *  Created on: Oct 29, 2017
 *      Author: konrad
 */

#ifndef PROGRAMLIB_H_
#define PROGRAMLIB_H_


void *IpLib;	//handle to IP lib
void *IcmpLib;	//handle to ICMP lib
void *LinkedLib;//handle to LinkedList lib


int Load_ipv4 ();	//function declaration to load IPv4 library
int Load_icmp ();	//function declaration to load ICMP library
int Load_list ();	//function declaration to load Linked list library


#endif /* PROGRAMLIB_H_ */
