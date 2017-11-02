/*
 * lista.h
 *
 *  Created on: Oct 15, 2017
 *      Author: konrad
 */

#ifndef LISTA_H_
#define LISTA_H_

struct Node {
	int id;
	char *datagram;
	struct Node *next;
	struct Node *prev;
};

struct Node *reserve_mem ( char *datagram );
void insert_tail ( char *datagram );
void print_list ();
void delete_id (int id);


#endif /* LISTA_H_ */
