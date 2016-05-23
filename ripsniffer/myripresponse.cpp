 // myripresponse.cpp
 // Riesenie ISA-Nastroj monitorovanie RIP a RIPng, 15.11.2015
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: g++ 4.8.4

//INCLUDED LIBS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <linux/if_link.h>

/*
Function transfers IPv4 address stored in char* to store[4]
*/
void strtoip(char * string, char * store){
    memset(store, 0, 4);
    int number=0;
    int index =0;
    for (int pos=0;(unsigned) string[pos]!= 0;pos ++){
        if ((string[pos] != '.') ) {
            number*=10;
            number+=(unsigned) string[pos] - 48;
            store[index]= (unsigned char) number;
            if (number > 255) {
                printf("Invalid IP address\n");
                exit(1);
            }
        }
        else{
            index++;
            number=0;
        }
    }
}

/*
Function transfers interger to mask stored in store[4]
*/
void inttomask(int mask, char * store){
    memset(store, 255, 4);
    for (int i=0;i<32-mask;i++){
        store[3-i/8]=store[3-i/8] << 1;
    }
}

main (int argc, char **argv)
{
    //Variables store parsed arguments
    int iflag = 0;
    int rflag = 0;
    int nflag = 0;
    int mflag = 0;
    int tflag = 0;
    int pflag = 0;
    char *interface=NULL;
    char *route=NULL;
    char *nexthop=NULL;
    char *metric=NULL;
    char *tag=NULL;
    char *password=NULL;
  
    int c;
  
    opterr = 0;
    while ((c = getopt (argc, argv, "i:r:n:m:t:p:")) != -1)
        switch (c)
            {
            case 'i':
                if (iflag != 0) {
                  fprintf(stderr, "Interface has already been set\n");
                  return -1;
                }
                iflag++;
                interface = strdup(optarg);
                break;
            case 'r':
                if (rflag != 0) {
                  fprintf(stderr, "Route has already been set\n");
                  return -1;
                }
                rflag++;
                route = strdup(optarg);
                break;
            case 'n':
                if (nflag != 0) {
                  fprintf(stderr, "Nexthop has already been set\n");
                  return -1;
                }
                nflag++;
                nexthop = strdup(optarg);
                break;
            case 'm':
                if (mflag != 0) {
                  fprintf(stderr, "Metric has already been set\n");
                  return -1;
                }
                mflag++;
                metric = strdup(optarg);
                break;
            case 't':
                if (tflag != 0) {
                  fprintf(stderr, "Tag has already been set\n");
                  return -1;
                }
                tflag++;
                tag = strdup(optarg);
                break;
            case 'p':
                if (pflag != 0) {
                  fprintf(stderr, "Password has already been set\n");
                  return -1;
                }
                pflag++;
                password = strdup(optarg);
                break;
            case ':':                           /* error - missing operand */
                fprintf(stderr, "Option -%c requires an operand\n", optopt);
                return -1;
                break;
            case '?':                           /* error - unknown option */
                fprintf(stderr,"Unrecognized option: -%c\n", optopt);
                return -1;
                break;
            }

    if ( optind<argc) {
      printf("Redundant arguments\n");
      return -1;
    }

    //Fill buffer with chars to be send

    char buffer[200];
    char address[20];
    char pass[16];
    int mask_size=0;
    int metric_size=0;
    int tag_size=0;
    char ip[4];
    char mask[4];
    //cler arrays
    memset(&address[0], 0, sizeof(address)); 
    memset(&buffer[0], 0, sizeof(buffer)); 


    //check that route and mask was set
    if (!rflag) {
        perror("No route argument -r");
        exit(1);
    } 


    //Get length of address
    int mask_pos=0;
    while(route[mask_pos]!='/') mask_pos++;
    //store address
    memcpy(address, route, mask_pos);
    mask_pos++;
    //load mask size
    while((unsigned)route[mask_pos]!=0) {
        mask_size*=10;
        mask_size+=(unsigned) route[mask_pos] - '0';
        mask_pos++;
    }
    if ( (mask_size>30) || (mask_size<8)){
        printf("Bad mask value\n");
        return 1;
    }

    //NEXt HOP
    if (!nflag) nexthop="0.0.0.0";

    //METRIC store from char* to int metric_size
    if (mflag) {
        int pos=0;
        while((unsigned)metric[pos]!=0) {
            metric_size*=10;
            metric_size+=(unsigned) metric[pos] - '0';
            pos++;
        }
        if ( (metric_size>16) || (metric_size<0)){
            printf("Bad metric value\n");
            exit(1);
        }
    }else metric_size=1;


    //TAG store from char* to int tag_size
    if (tflag) {
        int pos=0;
        while((unsigned)tag[pos]!=0) {
            tag_size*=10;
            tag_size+=(unsigned) tag[pos] - '0';
            pos++;
        }
        if ( (tag_size>65535) || (tag_size<0)){
            printf("Bad tag value\n");
            exit(1);
        }
    }else tag_size=0;


    //PASSWORD
    if (pflag){
        memset(&pass[0], 0, sizeof(pass)); 
        for (int i=0; (i<16) && password[i]!=0;i++)
            pass[i]=password[i];
    }



    /*
    FILL BUFFER 
    */

    //HEADER RIPv2 Response
    buffer[0]=0x02;
    buffer[1]=0x02;
    buffer[2]=buffer[3]=0x00;

    //stores actual position of message
    int index=4;

    //Check if password was set, if yes add it to buffer
    if (pflag){
        //PASSWORD HEADER
        buffer[4]=buffer[5]=0xFF;
        buffer[6]=0x00;
        buffer[7]=0x02;
        index=8;
        //COPY PASSWORD TO BUFFER
        for (int i=0;i<16;i++)
            buffer[i+index]=pass[i];
        index=24;
    }

    //ROUTE 
    //Address family-ip
    buffer[index]=0x00;
    index++;
    buffer[index]=0x02;
    index++;
    //Route tagg
    buffer[index] = (unsigned) (tag_size >> 8) & 0xFF;
    index++;
    buffer[index] = (unsigned) tag_size & 0xFF;
    index++;
    //IP ADDRESS
    strtoip(address,ip);
    buffer[index]=ip[0];
    buffer[index+1]=ip[1];
    buffer[index+2]=ip[2];
    buffer[index+3]=ip[3];
    index+=4;
    //MASK
    inttomask(mask_size,ip);
    buffer[index]=ip[0];
    buffer[index+1]=ip[1];
    buffer[index+2]=ip[2];
    buffer[index+3]=ip[3];
    index+=4;
    //NEXTHOP
    strtoip(nexthop,ip);
    buffer[index]=ip[0];
    buffer[index+1]=ip[1];
    buffer[index+2]=ip[2];
    buffer[index+3]=ip[3];
    index+=4;
    //METRIC
    buffer[index]=buffer[index+1]=buffer[index+2]=0x00;
    buffer[index+3]=metric_size;
    index+=4;




    //structures to get interfaces IP address
    //two ifaddres, to keep pointer to start of list to succesful close it
    struct ifaddrs *ifaddr, *ifa;
    int family,n;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) {
        perror("unable to get local interfaces");
        exit(1);
    }

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
        //skip interface with no IP address
        if (ifa->ifa_addr == NULL)
            continue;

        //skip interface withou IPv4 address
        family = ifa->ifa_addr->sa_family;
        if (family != AF_INET)
            continue;

        int check = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

        if (check != 0) {
            printf("unable to get local interfaces");
            exit(1);
        }

        //if interface was set, check if it match current one in the list
        if (iflag && (strcmp(interface,ifa->ifa_name) !=0) ) continue;

        //CEATE SOCKET AND SEND IT
        int sockfd;
        struct sockaddr_in target_addr, myaddr;
    
        memset((char *)&target_addr, 0, sizeof(myaddr));

        //set target IP and port
        target_addr.sin_family = AF_INET;
        target_addr.sin_addr.s_addr=0x090000E0;
        target_addr.sin_port = htons(520);
    
        sockfd = socket(AF_INET,SOCK_DGRAM,0);
    
        memset((char *)&myaddr, 0, sizeof(myaddr));

        //set host address to used interface, set host port
        myaddr.sin_family = AF_INET;
        inet_aton(host, &myaddr.sin_addr);
        myaddr.sin_port = htons(520);
    
        if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
            perror("bind failed");
            exit(1);
        }
    
    
        sendto(sockfd, buffer, index, 0,(struct sockaddr *) &target_addr,sizeof(target_addr));

        //unbind socket
        int one = 1;
        setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(int)); 
        close(sockfd);
    
    
    }
        
    freeifaddrs(ifaddr);
    return 0;
}
