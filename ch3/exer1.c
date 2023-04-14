#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

    int packet_size, fragment_size, header_size, nodes;
    double bitrate;

    printf("Enter size length, must be positive integer\n? ");
    scanf("%d", &packet_size);
    while(packet_size <= 0) {
        system("cls");
        printf("Packet size must be positive integer\n? ");
        scanf("%d", &packet_size);
    }
    system("cls");

    printf("Enter number of nodes, must be positive integer\n? ");
    scanf("%d", &nodes);
    while(nodes <= 0) {
        system("cls");
        printf("Number of nodes must be positive integer\n? ");
        scanf("%d", &nodes);
    }
    system("cls");

    printf("Enter link bitrate, must be positive real\n? ");
    scanf("%lf", &bitrate);
    while(bitrate <= 0) {
        system("cls");
        printf("Link bitrate must be positive real\n? ");
        scanf("%lf", &bitrate);
    }
    system("cls");

    printf("Enter fragment size, must be positive integer\n? ");
    scanf("%d", &fragment_size);
    while(fragment_size <= 0) {
        system("cls");
        printf("Fragment size must be positive integer\n? ");
        scanf("%d", &fragment_size);
    }
    system("cls");

    printf("Enter header size, must be positive integer\n? ");
    scanf("%d", &header_size);
    while(header_size <= 0) {
        system("cls");
        printf("Header size must be positive integer\n? ");
        scanf("%d", &header_size);
    }
    system("cls");

    double delay = (double) ((nodes-1)*packet_size/bitrate);
    double delay_frag = (double) ( (1/bitrate) * (packet_size + (packet_size*header_size)/fragment_size + (nodes-2)*(fragment_size+header_size)) );

    printf("Packet size:\t%d\n", packet_size);
    printf("Num of nodes:\t%d\n", nodes);
    printf("Link bitrate:\t%lf\n", bitrate);
    printf("Fragment size:\t%d\n", fragment_size);
    printf("Header size:\t%d\n", header_size);
    printf("\nDelay:\n\tWithout fragmentation:\t%lf\n\tWith fragmentation:\t%lf", delay, delay_frag);

    return 0;
}