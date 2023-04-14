#include <stdio.h>
#include <stdlib.h>

int main() {

    int packetSize; // L == packetSize
    double maxDelay, propDelay; // D_max == maxDelay, Prop == propDelay

    // Διαβάζει το μέγεθος του πακέτου
    printf("Enter average packet size. Must be positive integer\n? ");
    do {
        scanf("%d", &packetSize);
        system("cls");
        if (packetSize <= 0)
            printf("Packet size must be a positive integer\nEnter average packet size\n? ");
        else
            break;
    } while (1);

    // Διαβάζει την μέγιστη επιτρεπτή καθυστέρηση
    printf("Enter maximum allowed delay. Must be positive real\n? ");
    do {
        scanf("%lf", &maxDelay);
        system("cls");
        if (maxDelay <= 0)
            printf("Delay must be positive real\nEnter maximum allowed delay\n? ");
        else 
            break;
    } while (1);

    // Διαβάζει την καθυστέρηση μεταβίβασης
    printf("Enter propagation delay of the link. Must be non negative real and smaller than maximum allowed delay\n? ");
    do {
        scanf("%lf", &propDelay);
        system("cls");
        if (propDelay < 0) 
            printf("Delay must be positive real\nEnter propagation delay\n? ");   
        else if (maxDelay <= propDelay)
            printf("Propagation delay longer than maximum delay allowed, impossible to send data in time\n Enter propagation delay\n? ");  
        else
            break;
    } while (1);

    // Υπολογισμός ελάχιστου επιτρεπτού bitrate
    double minBitrate = (double) (packetSize / (double) (maxDelay - propDelay));

    // Δεν δίνεται το διάστημα [t1, t2] ούτε
    // ζητείται να αναγνωθεί, υποθέτεται ότι είναι [0,3]
    double t1 = 0, t2 = 3;

    // Υλοποίηση σε περίπτωση που υπονοούταν να αναγνωθεί
    // double t1, t2;
    // do {
    //     printf("Enter time t1. Must be non negative real and smaller than t2\n? ");
    //     do {
    //         scanf("%lf", &t1);
    //         system("cls");
    //         if (t1 < 0)
    //             printf("t1 must be non positive real. Enter time t1\n? ");
    //         else
    //             break;
    //     } while (1);
        
    //     printf("Enter time t2. Must be non negative real and larger than t1\n? ");
    //     do {
    //         scanf("%lf", &t2);
    //         system("cls");
    //         if (t2 < 0)
    //             printf("Time t2 must be non positive real. Enter time t2\n? ");
    //         else
    //             break;
    //     } while (1);

    //     if (t1 >= t2) 
    //         printf("Time t1 must be smaller than t2\n");
    //     else 
    //         break;

    // } while (1);

    // Αν δεν έχει περάσει τουλάχιστον propDelay χρόνος
    // κανένα bit δεν θα έχει φτάσει στον δέκτη
    if (t1 < propDelay)
        t1 = propDelay;

    double Dt = t2-t1;
    if (Dt < 0)
        Dt = 0;

    // Ρυθμός * Χρόνος
    int bitsSent = (int) ((double) (minBitrate * Dt)); 

    printf("Minimum required bitrate: %.4lf bits/s\n", minBitrate);
    printf("Bits sent within period [%.2lf, %.2lf]: %d\n\n", t1, t2, bitsSent);
    system("pause");

    return 0;

}