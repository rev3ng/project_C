/*
 * lista.c
 *
 *  Created on: Oct 15, 2017
 *      Author: konrad
 */
#include <stdlib.h>
#include <stdio.h>
#include "linkedList_lib.h"

//wzkaznik pierwszego elementu listy
struct Node *head = NULL;

//funkcja rezerwująca pamięć dla nowego elementu listy
struct Node *reserve_mem (int a, int b){

	//stworzenie wskaźnika nowego elementu listy
	struct Node *new_node;
	static int id = 1;

	//zarezerwowanie pamięci
	new_node = malloc(sizeof (struct Node));

	//jeżeli nie wiesz po co ten if jest, to możesz go spokojnie usunąć, żeby się z niego nie tłumaczyć
	if (new_node == NULL) {
		printf("Cannot create new node");
		return NULL;
	}

	//przypisanie wartości to elementu listy
	new_node->id = id;
	id++;
	new_node->a = a;
	new_node->b = b;
	new_node->next = NULL;
	new_node->prev = NULL;

	//zwrócenie adresu nowego elementu
	return new_node;
}

//funkcja wpisująca nowy element na koniec listy
void insert_tail (int a, int b){

	struct Node *temp = head;
	struct Node *new_node = reserve_mem(a, b);


	if (head == NULL){
		head = new_node;
		return;
	}

	while (temp->next != NULL) //przejście do końca listy
		temp = temp->next;
	//dopisanie elementu na końcu listy
	temp->next = new_node;
	new_node->prev = temp;
}

//fukcja do wypisania całej listy
void print_list () {

	struct Node *temp = head;

	while (temp != NULL){
		printf ("id: %d, A: %d, B: %d\n", temp->id, temp->a, temp->b);
		temp = temp->next;
	}
}

//funkcja kasująca element o podanym id
void delete_id (int a){

	struct Node *temp = head;
	struct Node *del = NULL;
	struct Node *nxt = NULL;

	while (temp->id != a)
		temp = temp->next;
	//printf ("id: %d, A: %d, B: %d\n", temp->id, temp->a, temp->b);
	temp = temp->prev;
	del = temp->next;
	//printf ("id: %d, A: %d, B: %d\n", del->id, del->a, del->b);
	temp->next = del->next;
	nxt = del->next;
	nxt->prev = del->prev;
	free(del);
}




