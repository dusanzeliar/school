 // myripsniffer.cpp
 // Riesenie ISA-Nastroj monitorovanie RIP a RIPng, 15.11.2015
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: g++ 4.8.4

#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
Function to print IPv6 address in short format 
*/

void parseipv6(const u_char * packet, int index){
	int short_flag=0;
	int zero=1;
    int byte=0;


	for (int i=0;i<16;i++){
		//not 4th byte
		byte++;
		//all previous bytes are zero
		if (zero == 1){
			if ((unsigned)packet[index+i] != 0x00 ){
				//NOT 0, we print the number
				printf("%x", (unsigned)packet[index+i] );
				zero=0;
			}
		}
		else{
			if ((unsigned)packet[index+i] < 16){
				//need to print first zero too
				printf("0");
			}
			printf("%x", (unsigned)packet[index+i] );
		}
		if (byte == 2){
			if ( zero == 1){
				if ((short_flag == 1) && (i==15)) printf("0");
				if (short_flag == 0){
				    short_flag=1;
				    printf(":");
                                }
				else if (short_flag == 2){
					if  (i!=15) printf(":");
				}

			}
			else {
				if (i!=15) printf(":" );
			}
		        
                   zero=1;
                   byte=0;
	       }
        }
}

/*
Function processes packet that was accepted on 520 or 521 ports
*/

void processPacket(u_char *arg, const struct pcap_pkthdr* pkthdr,const u_char * packet){

	int ip_type;
	int version;
    int package_size=pkthdr->len;
    int position;

	/*check type of packet*/
	if ( (packet[12] == 0x08) && (packet[13] == 0x00)) ip_type = 4;
	    else ip_type=6;

    /*
    ITS IPv4 packet, print it
    */
	if (ip_type == 4){
        printf("IPv4, Package size: %d\n",package_size);
		//Souce address and destination address
		printf("Source address: ");
		for (int i=26;i<30;i++) {
			printf("%u", (unsigned)packet[i] );
			if (i!= 29) printf(".");
		}

		printf(" Destination address: ");
		for (int i=30;i<34;i++) {
			printf("%u", (unsigned)packet[i] );
			if (i!= 33) printf(".");
				else printf("\n");
		}

		if  (packet[42] == 0x02) printf("Response ");
			else printf("Request ");

		if  (packet[43] == 0x02){
			version=2;
			printf("RIPv2\n");
		} 
		else {
		    version=1;
		    printf("RIPv1\n");
		    }

        //Check if first route is password
        position=46;
		if ((version == 2) && (packet[46] == 0xFF) && (packet[47] == 0xFF)) {
			if (  (packet[48] == 0x00) && (packet[49] == 0x02) ) {
				printf("Authentication: Simple Password:");
				for (int i=0;i<16;i++){
					printf("%c",packet[50+i]);
				}
				printf("\n");
                position=position+20;
			} 
		} 
                
        /*
        Print informations from route entry
        */ 
        while (position < package_size){
            if (  (packet[position] == 0x00) && (packet[position+1] == 0x02) ) {
                //For both RIPv1 and RIPv2 packets
                position+=4;
                printf("IP Address: ");
                for (int i=0;i<4;i++) {
                    printf("%u", (unsigned)packet[position+i] );
                    if (i!= 3) printf(".");
                }
                position+=4;
                //Read mask and nexthop if RIPv2
                if (version == 2) {
                    printf(" Mask: ");
                    for (int i=0;i<4;i++) {
                        printf("%u", (unsigned)packet[position+i] );
                        if (i!= 3) printf(".");
                    }
                    position+=4;

                    printf("\nNext hop: ");
                    for (int i=0;i<4;i++) {
                        printf("%u", (unsigned)packet[position+i] );
                        if (i!= 3) printf(".");
                    }
                    position+=4;
                }else position+=8;

                int num = (packet[position] << 24) + (packet[position+1] << 16) + (packet[position+2] << 8) + packet[position+3];
                printf(" Metric: %d\n",num);
                position+=4;
           }
      }
      printf("\n");

	}

    /*
    ITS IPv6 packet
    */
          
	if (ip_type == 6){
        printf("IPv6, Package size: %d\n",package_size);
		//Souce address and destination address
		printf("Source address: ");
                parseipv6(packet,22); 

		printf(" Destination address: ");
                parseipv6(packet,38); 
                printf("\n");

		if  (packet[62] == 0x02) printf("Response ");
			else printf("Request ");

		printf("RIPng\n");

        position=66;
        printf("Route Table Entry:\n");
        //Read all route entries
        while (position < package_size){
            //read IPv6 address
            printf("IPv6 Prefix: ");
            parseipv6(packet,position);
            position+=18;
            //maskc and metric
            printf("/%u Metric: %u",(unsigned)packet[position],(unsigned)packet[position+1]);
            position+=2;
            printf("\n");
        }
        printf("\n");
    }

	return;
}

int main( int argc, char * argv[]){
	int i=0, count=0;
	//Packet structure desrc
	pcap_t *desrc = NULL;
	//Create error buffer and clean it
	char errbuf[PCAP_ERRBUF_SIZE], *device=NULL;
	memset(errbuf,0,PCAP_ERRBUF_SIZE);
    struct bpf_program fp;
    //set filter to accept only RIP and RIPng packets
    char filter_exp[] = "port 520 or port 521";
    bpf_u_int32 mask;
    bpf_u_int32 net;
    //Pcap Header
    struct pcap_pkthdr header;
    //Packet we received
    const u_char *packet;


    if (argc != 3){
        printf("Bad input, need -i parameter and interface\n");
        exit(2);
    }
    char *parameter=argv[1];
    //check parameter, if interface was set
    if ((parameter[0] != '-') || (parameter[1] != 'i') || (parameter[2] != 0)){
        fprintf(stderr, "Bad input, no -i parameter to set interface : %s\n", errbuf);
        return (2);
    }
	/*Get the name of the connection name to sniff on*/
	device = argv[2]; 
        if (device == NULL) {
            fprintf(stderr, "Couldn't find ineterface: %s\n", errbuf);
            return (2);
        } 
 
    /*Find the properties for the device*/
    if(pcap_lookupnet(device,&net,&mask,errbuf) == -1) {
        fprintf(stderr, "Couldn't get netmask for device %s: %s\n",device,errbuf);
        exit(2);
    }

	/*open device in promiscuos mode*/
	desrc= pcap_open_live(device, 2048,1,512,errbuf);

    if (desrc == NULL) {
        fprintf(stderr, "Couldnt open device %s: %s\n", device, errbuf);
        return(2);
    }

    /*compile and apply the filter*/
    if (pcap_compile(desrc, &fp,filter_exp, 0,net) == -1) {
        fprintf(stderr,"Couldn't parse filter %s: %s\n",filter_exp,pcap_geterr(desrc));
        return(2);
    }
    if (pcap_setfilter(desrc, &fp) ==-1) {
        fprintf(stderr,"Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(desrc));
        return(2);
    }

	/* processPacket for every received packet*/
	pcap_loop(desrc,-1, processPacket, (u_char *) &count);

	return 0;
}

