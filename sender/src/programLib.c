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
//#include "linkedList_lib.h"
#include <stdio.h>

struct Node *head = NULL;

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
/*void * Load_list (){

	void *LinkedLib = malloc ( sizeof (void ) );//handle to LinkedList lib

	LinkedLib = dlopen("./linkedList_lib.so", RTLD_LAZY);
		if (!LinkedLib)
			return 0;
		else
			return LinkedLib;

}*/

//function to send created packet
int SendPacket ( char *interface ){

	char *datagram = head -> datagram;
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


	while ( head != NULL ) {
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
		head = head -> next;
	}
	delete_list();
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


/*
 * lista.c
 *
 *  Created on: Oct 15, 2017
 *      Author: konrad
 */

void LoadToList ( int *count, char *dtgr ){

	for ( int i = 0; i != *count; i++ )
		insert_tail( dtgr );
	//struct Node *asd;
	//return return_head();
}





//wzkaznik pierwszego elementu listy


//funkcja rezerwująca pamięć dla nowego elementu listy
struct Node *reserve_mem ( char *datagram ){

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
	new_node-> datagram = datagram;
	new_node->next = NULL;
	new_node->prev = NULL;

	//zwrócenie adresu nowego elementu
	return new_node;
}

//funkcja wpisująca nowy element na koniec listy
void insert_tail ( char *datagram ){

	struct Node *temp = head;
	struct Node *new_node = reserve_mem( datagram );


	if (head == NULL){
		head = new_node;
		return;
	}

	while (temp->next != NULL) //przejście do końca listy
		temp = temp->next;
	//dopisanie elementu na końcu listy
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = NULL;
}

//fukcja do wypisania całej listy
void print_list () {

	struct Node *temp = head;

	if ( temp == NULL)
		printf ("\nList empty\n");

	while (temp != NULL){
		printf ("id: %d, dtgr: %p\n", temp->id, (void *)(temp-> datagram) );
		temp = temp->next;
	}
}

struct Node * return_head () {
	return head;
}

//funkcja kasująca element o podanym id
void delete_list (){

	struct Node *temp = head;
	struct Node *del = NULL;

	while ( temp != NULL ){
		del = temp;
		temp = temp -> next;
		free (del);
	}
	head = NULL;

}





