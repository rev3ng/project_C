#!/bin/bash
gcc -fPIC -shared ~/project_C/icmp_lib/src/icmp_lib.c -o /home/konrad/project_C/sender/icmp_lib.so
gcc -fPIC -shared ~/project_C/ipv4_lib/src/ipv4_lib.c -o /home/konrad/project_C/sender/ipv4_lib.so
gcc -fPIC -shared ~/project_C/linkedList_lib/src/linkedList_lib.c -o /home/konrad/project_C/sender/linkedList_lib.so
