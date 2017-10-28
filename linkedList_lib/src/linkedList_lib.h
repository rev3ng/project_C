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
	int a;
	int b;
	struct Node *next;
	struct Node *prev;
};

struct Node *reserve_mem (int a, int b);
void insert_tail (int a, int b);
void print_list ();
void delete_id (int a);


#endif /* LISTA_H_ */
