#include <stdio.h>
#include <stdlib.h>

int main () {

    int lowBnd = 0, highBnd = 0, numOfQuantLev = 0;
    float samples[1024] = {0};
    size_t i = 0;
    
    do { // 1.1 Διαβάζει τα άκρα του πεδίου τιμών
        printf("Input low bound of domain\n? ");
        scanf("%d", &lowBnd);
        system("cls");
        printf("Input high bound of domain\n? ");
        scanf("%d", &highBnd);
        system("cls");
        if (lowBnd >= highBnd)
            printf("Low bound can't be higher than high bound\n");
        else if (lowBnd < 0)
            printf("Bounds must be positive\n");
        else 
            break;
    } while (1);
    
    do { // 1.2 Διαβάζει τον αριθμό σταθμών κβαντοποίησης
        printf("Input number of quantisation levels\n? ");
        scanf("%d", &numOfQuantLev);
        system("cls");
        if (numOfQuantLev < 1)
            printf("There must be at least two zones to quantise to\n");
        else
            break;
    } while (1);
 
    do { // 1.3 Διαβάζει τα δείγματα
        printf("Input samples between %d-%d in sequence\n-1 to stop\n? ", lowBnd, highBnd);
        scanf("%f", &samples[i]);
        system("cls");
        if (samples[i] == -1)
            break;
        if (samples[i] > highBnd || samples[i] < lowBnd) {
            printf("Value outside of accepted range\n");
            continue;
        }
        i++;
    } while (1);

    // 2.1 Ειδική περίπτωση, μόνο ένα επίπεδο κβαντοποίησης
    if (numOfQuantLev == 1) {
        for (int j = 0; j < i; j++) {
            printf("0 ");
        }
        return 0;
    }

    // 2.2 Μεταφέρει το πεδίο τιμών στο [0,highBnd-lowBnd]
    int adjhighBnd = highBnd - lowBnd;

    // 2.3 Βρίσκει τον ελάχιστο αριθμό bit που είναι απαραίτητα
    int reqBits = 0;
    int temp = numOfQuantLev - 1;
    while (temp > 0) {
        temp = temp/2;
        reqBits++;
    }

    // 2.4 Αντιστοιχεί δεκαδικούς αριθμούς των στοιβών σε δυαδικούς
    char code[numOfQuantLev][reqBits];
    int asciiOffset = 48;
    for (int j = 0; j < numOfQuantLev; j++) {
        int temp = j;
        for (int k = 1; k <= reqBits; k++) {
            code[j][reqBits-k] = temp % 2 + asciiOffset;
            temp /= 2;
        }
    }
        
    // 2.5 Βρίσκει την διαφορά μεταξή σταθμών κβαντοποίησης
    float quantLevStep = (float) adjhighBnd / (numOfQuantLev - 1);

    for (int j = 0; j < i; j++) {

        // 3.1 Κβαντοποιεί τον αριθμό στο κοντινότερο επίπεδο [0,numOfQuant-1]
        int quantised = (int) ( (float) 0.5 + (samples[j]/quantLevStep));

        // 3.2 Εκτυπώνει τον αριθμό
        for (int k = 0; k < reqBits; k++) {
            printf("%c", code[quantised][k]);
        }
        printf(" ");
    }
    printf("\n");
    system("pause");
    
    return 0;

}