/*
 * icmp_lib.c
 *
 *  Created on: Oct 23, 2017
 *      Author: konrad
 */

#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>

unsigned short Checksum ( unsigned short *datagram, int nbytes )
{
	//

    long sum;
    short answer;

    sum=0;

    while( nbytes > 1 ) {
        sum += *datagram++;
        nbytes -= 2;
    }

    sum = ( sum >> 16 ) + ( sum & 0xffff );
    sum = sum + ( sum >> 16 );
    answer = (short) ~sum;
    //printf ("answer = %x:", answer);
    return answer;
}

unsigned short * CreateIcmpPacket ( unsigned char * datagram ) {

	struct icmp *icmp = (struct icmp *) ( datagram + sizeof ( struct iphdr ));
	char input [32];

	printf ("\nICMP type (0): ");
	fgets (input, 32, stdin);
		if (atoi(input)== 0)
			icmp -> icmp_type = 0;
		else
			icmp -> icmp_type = atoi (input);

	printf ("\nICMP code (0): ");
	fgets (input, 32, stdin);
		if (atoi(input)== 0)
			icmp -> icmp_code = 0;
		else
			icmp -> icmp_code = atoi (input);

	printf ("\nICMP checksum will be calcuated: ");
	icmp -> icmp_cksum = 0;
	icmp -> icmp_cksum = Checksum( (unsigned short *) (datagram + sizeof ( struct iphdr ) ), 2);

}
