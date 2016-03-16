/* 
 * File:   main.c
 * Author: ROB41
 *
 * Created on 01 December 2014, 14:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "navigation.h"
#include "structs.h"

_Bool endProgram = 0;
void featureOne();
void featureTwo();
void calculateAverages(struct sighting *sighting);
void featureThree();
void findPods();
void continueProgram(char[4]);
int compareLocations(location, location);
void FileReader(char[], int);

int main(int argc, char** argv) {
    printf("===============================================================\n");
    printf("Launching cetacean sighting program. Running on:-\n");
    system("hostname");
    featureOne();
    if (endProgram == 0) {
        featureTwo();
    }
    if (endProgram == 0) {
        featureThree();
    }
    return (EXIT_SUCCESS);
}
//aber//dap//cetaceans//data//
/*This is the code associated with reading in from files*/
void featureOne() {
    int counter;
    for (counter = 0; counter < 2; counter++) {
        if (counter == 0) {
            FileReader("observers", counter);
        } else if (counter == 1) {
            FileReader("sightings", counter);
        }
    }
    printf("\n===============================================================");
    printf("\n%02d / %02d / %04d AT %02d %02d %02d\n",
            observerTS->day, observerTS->month, observerTS->year,
            observerTS->hour, observerTS->min, observerTS->second);
    /*
    printf("Printing observer list\n");
    struct observer *x = observerHead;
    while(x!=NULL){
        printf("Observer: %-4s Lat: %f Long: %f\n",x->observerID,x->latit,x->longi);
        x=x->next;
    }
     */
    printf("Latitude   Longitude   Observer ID     Type\n");
    struct sighting *i = sightingsHead;
    while (i != NULL) {
        if (i->display == 0) {
            printf("%lf  %lf   %-4s            %-1s\n",
                    i->mammalLoc.lat, i->mammalLoc.lng, i->observerID, i->type);
        }
        i = i->next;
    }
    printf("\nAny mammals outside of the sea area are not displayed\n");
    continueProgram("\nshall we analyse this data to find the duplicate entries? Y/N\n");

}

/*this is the code to analyse the locations of the cetacean mammals*/
void featureTwo() {
    calculateAverages(sightingsHead);

    //print out the sightings
    printf("\n===============================================================");
    printf("\nType   Average Location         All Sightings\n");
    printf("       Lat        Long          Lat        Long\n");
    struct sighting *i = sightingsHead;
    while (i != NULL) {
        if (i->display == 0) {
            printf("%s      %0.6f  %0.6f     ", i->type, i->avgLoc.lat, i->avgLoc.lng);
            int counter = 0;
            while (counter != i->numOfDup) {
                if (counter != 0) {
                    printf("                                ");
                }
                printf("%0.6f  %0.6f\n", i->dupLocs[counter].lat, i->dupLocs[counter].lng);
                counter++;
            }
        }
        i = i->next;
    }
    continueProgram("\nShall we analyse the data to find any PODs? Y/N\n");
}

void featureThree() {
    findPods();

    printf("\n===============================================================");
    struct pod *i = podHead;
    while (i != NULL) {
        int counter;
        printf("\nPod Number: %d", i->podID);
        printf("\nPod Size   Type     Location(of each)\n");
        for (counter = 0; counter != i->sizeOfPod; counter++) {
            if (counter == 0) {
                printf("%3d        %-1s        %0.6f  %0.6f\n",
                        i->sizeOfPod, i->type, i->locations[counter].lat, i->locations[counter].lng);
            } else {
                printf("                    %0.6f  %0.6f\n",
                        i->locations[counter].lat, i->locations[counter].lng);
            }
        }
        i = i->next;

    }
}

void continueProgram(char message[]) {
    char nextFeature[1];
    _Bool validInput = 0;
    while (validInput == 0) {
        printf("%s", message);
        scanf(" %c", nextFeature);
        if (strncmp(nextFeature, "Y", 1) == 0 || strncmp(nextFeature, "y", 1) == 0) {
            validInput = 1;
        } else if (strncmp(nextFeature, "N", 1) == 0 || strncmp(nextFeature, "n", 1) == 0) {
            validInput = 1;
            endProgram = 1;
        } else {
            printf("Please enter Either Y or N.\n");
        }
    }
}