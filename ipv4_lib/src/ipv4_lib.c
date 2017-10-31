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
#include <netinet/in.h>
#include <sys/socket.h>


unsigned short Ipv4_checksum (unsigned short *dtg, struct iphdr *iph){

	long sum = 0;

	for ( int i = 0; i <= (iph->ihl) * 2; i++ ){
		sum = sum + *(dtg+i);
	}

	//printf ("SUM: %x", sum);
	//printf ("SUM >> 12: %x", (sum >> 12));
	/*sum += (sum >> 12) + (sum & 0x000f);

	sum = (short)~sum;
	printf ("SUM: %x", (short)sum);
	sum = htons (sum);
*/
	//printf ("\nChecksum: %x", sum);
	while (sum >> 16)
		sum = (sum & 0xffff) + ( sum >> 16 );
	printf ("~sum = %x", (short)~sum);
	return ~sum;
}

unsigned short csum(unsigned short *ptr,int nbytes)
{
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    /*if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }*/

    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
    printf ("answer = %x:", answer);
    return(answer);
}


void Print_packet (char *dtgr, char *data){

	struct iphdr *iphd = (struct iphdr *) dtgr;
	//struct in_addr *addr;
	printf ("\n\n---------- PACKET START ----------");
	printf ("\nVersion: %d\n", iphd->version);
	printf ("Ihl: %d\n", iphd->ihl);
	printf ("tos: %d\n", iphd->tos);
	printf ("tot len: %d\n", iphd->tot_len);
	printf ("id: %d\n", ntohs(iphd->id));
	printf ("frag off: %d\n", iphd->frag_off);
	printf ("ttl: %d\n", iphd->ttl);
	unsigned char *addr = (unsigned char *) &(iphd->saddr);
	printf ("saddr: %d.%d.%d.%d\n", addr [0], addr [1], addr [2], addr [3]);
	addr = (unsigned char *) &(iphd->daddr);
	printf ("daddr: %d.%d.%d.%d\n", addr [0], addr [1], addr [2], addr [3]);
	printf ("proto (ipv4): %d\n", iphd->protocol);
	printf ("checksum: %x\n", iphd->check);
	printf ("data: %s", data);
	printf ("\n---------- PACKET END ----------\n");

}

void Print_header_hex (unsigned short *dtgr){

	//struct iphdr *iphd = (struct iphdr *) dtgr;
	//struct in_addr *addr;
	int i = 0;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	i++;
	printf ("\n%d: %x", i, ntohs(dtgr[i]));
	printf ("\n---------- HEX END ----------\n");
}


char * Create_ipv4_packet (){

	//sender address
	char sender_ip [32];
	strcpy (sender_ip, "192.168.1.1");

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
	strcpy(data, "1234567890QWERTYUI");

	//input buffer
	char input [32];

	//fill header fields
	printf ("Creating IPv4 packet (if empty, set default): \n");
	printf ("Internet header length (5): ");
		fgets (input, 32, stdin);
		if (atoi(input)== 0)
			iph->ihl = 5;
		else
			iph->ihl = atoi (input);
	printf ("Version set to: 4. \n");
			iph->version = 4;	//version 4/6

	printf ("Type of service (0): ");
		fgets (input, 32, stdin);
			if (atoi(input)== 0)
				iph->tos = 0;
			else
				iph->tos = atoi (input);

	printf ("Total length will be calculated... \n");
		iph->tot_len = sizeof (struct iphdr) + strlen(data);

	printf ("ID (54321): ");
		fgets (input, 32, stdin);
			if (atoi(input)== 0)
				iph->id = htons (54321);
			else
				iph->id = htons (atoi(input));

	printf ("Fragmentation offset (0): ");
		fgets (input, 32, stdin);
				if (atoi(input)== 0)
					iph->frag_off = 0;
				else
					iph->frag_off = atoi (input);

	printf ("Time to live (64): ");
		fgets (input, 32, stdin);
				if (atoi(input)== 0)
					iph->ttl = 64;
				else
					iph->ttl = atoi (input);
	printf ("Protocol set to IPv4...\n");
		iph->protocol = IPPROTO_IP;	 		//protocol

	printf ("Checksum will be calculated...\n");
			iph->check = 0;		//checksum

	printf ("Source address (192.168.1.1): ");
		fgets (input, 32, stdin);
				if (atoi(input)== 0)
					iph->saddr = inet_addr("192.168.1.1");
				else
					iph->saddr = inet_addr(input);



	printf ("Data automaticly set: %s", data);

	iph->daddr = inet_addr(destination_ip);	//destination address
	iph->check = csum((unsigned short *) datagram, iph->tot_len);
	//iph->check = Ipv4_checksum((unsigned short *)datagram, iph);		//checksum function
	Print_header_hex((unsigned short *) datagram);

	Print_packet(datagram, data);
	char *ret = malloc(sizeof (datagram));
	ret = datagram;

	int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
		if (s == -1)
			printf ("\nSocket not opened\n");

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons (80);
	sin.sin_addr.s_addr = iph->daddr;


	if (sendto (s, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
	            perror("sendto failed");
	        else
	            printf ("Packet Send. Length : %d \n" , iph->tot_len);

	return ret;

}
