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
#include <arpa/inet.h>



unsigned short Ipv4_checksum (unsigned short *dtg, struct iphdr *iph){

	unsigned short sum = 0;

	for ( int i = 0; i <= (iph->ihl) * 2; i++ ){
		sum = sum + *(dtg+i);
	}

	sum += 2;
	sum = ~sum;

	return sum;
}



void Create_ipv4_packet (){

	//sender address
	char sender_ip [32];
	strcpy (sender_ip, "192.168.1.123");

	//destination address
	char destination_ip [32];
	strcpy (destination_ip, "8.8.8.8");

	//datagram to represent the packet
	char datagram [4096], *data;

	//clear datagram memory
	memset( datagram, 0, 4096 );

	//IP header
	struct iphdr *iph = (struct iphdr *) datagram;

	//data part (jump after header adress)
	data = datagram + sizeof (struct iphdr);
	//fill field with some data
	data = strcpy(data, "1234567890QWERTYUIOPASDFGHJKLZXCVBNM");

	//fill header fields
	iph->version = 4;	//version 4/6
	iph->ihl = 5;		//internet header length (32bit words)
	iph->tos = 0;		//type of service
	iph->tot_len = sizeof (struct iphdr) + strlen(data);	//
	iph->id = htonl (1234);	//packet id
	iph->frag_off = 0;		//fragment offset
	iph->ttl = 64;			//time to live
	iph->protocol = IPPROTO_IP;	 		//protocol
	iph->check = 0;		//checksum
	iph->saddr = inet_addr(sender_ip);		//source address --inet_addr->converts string to address
	iph->daddr = inet_addr(destination_ip);	//destination address

	iph->check = htonl(ipv4_checksum((unsigned short *)datagram, iph));		//checksum function




	/*printf ("Fill the packet:\n");
	iph->version = 4;
	scanf ("IHL: ", iph->ihl);
	scanf ("")
	*/


	//return iph;
}
