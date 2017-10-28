/*
 * ipv4_lib.c
 *
 *  Created on: Oct 23, 2017
 *      Author: konrad
 */

#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void create_ipv4_packet (){

	//sender address
	char sender_ip [32];
	strcpy (sender_ip, "192.168.1.123");

	//datagram to represent the packet
	char datagram [4096], *data;

	//clear datagram memory
	memset( datagram, 0, 4096 );

	//IP header
	struct iphdr *iph = (struct iphdr *) datagram;

	//data part (jump after header adress)
	data = datagram + sizeof (struct iphdr);
	//fill field with some data
	data = strcpy(data, "1234567890QWERTYUIOPASDFGHJKLZXCVBNM")

	//fill header fields
	iph->version = 4;	//
	iph->ihl = 5;		//
	iph->tos = 0;		//
	iph->tot_len = sizeof (struct iphdr) + strlen(data);	//
	iph->id = htonl (1234);	//packet id
	iph->frag_off = 0;		//fragment offset
	iph->ttl = 64;			//time to live
	iph->protocol = IPPROTO_IP;			//protocol
	iph->check = 0;		//checksum
	iph->saddr = inet_addr(sender_ip);		//source address
	iph->daddr = ;		//destination address

	iph->check = ;		//TODO checksum function




	/*printf ("Fill the packet:\n");
	iph->version = 4;
	scanf ("IHL: ", iph->ihl);
	scanf ("")
	*/


	//return iph;
}
