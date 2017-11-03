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
//void * Load_list ();	//function declaration to load Linked list library
int SendPacket ( char *interface );
int Menu ( int *count, char *interface );
void LoadToList ( int *count, char *dtgr);
struct Node {
	int id;
	char *datagram;
	struct Node *next;
	struct Node *prev;
};

struct Node *reserve_mem ( char *datagram );
void insert_tail ( char *datagram );
void print_list ();
void delete_list ();
struct Node * return_head ();


#endif /* PROGRAMLIB_H_ */
