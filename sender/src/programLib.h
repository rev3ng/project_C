/*
 * programLib.h
 *
 *  Created on: Oct 29, 2017
 *      Author: konrad
 */

#ifndef PROGRAMLIB_H_
#define PROGRAMLIB_H_





void * Load_ipv4 ();	//function declaration to load IPv4 library
void * Load_icmp ();	//function declaration to load ICMP library
void * Load_list ();	//function declaration to load Linked list library
int SendPacket ( unsigned short *datagram, char *interface );
int Menu ( int *count, char *interface );



#endif /* PROGRAMLIB_H_ */
