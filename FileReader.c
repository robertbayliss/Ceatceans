#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "navigation.h"
#include "sea_area.h"
#include "structs.h"

location getMammalLocation(location observerLocation, double mammalBearing, double mammalRange);
location searchList(char searchForID[]);
struct observer* addobserver(char NewObserverID [4], double newLatit, double NewLongi);
struct sighting* addSighting(char newObserverID [4], char newType [1], double newBearing, double newRange);

void FileReader(char whichFile[], int openWhich) {
    char file_Name[255];
    FILE *filep;

    printf("Enter the directory/name of the %s File\n", whichFile);
    fgets(file_Name, 255, stdin);

    //Remove the newline character
    size_t end = strlen(file_Name) - 1;
    if (file_Name[end] == '\n') {
        file_Name[end] = '\0';
    }
    filep = fopen(file_Name, "r");

    /*If we can't find the file produce error and end*/
    if (filep == NULL) {
        perror("Error while opening the a file.\n");
        exit(EXIT_FAILURE);
    }
    /*
    char c;
    while( ( c = fgetc(filep) ) != EOF )
      printf("%c",c);
     */


    /*IF WE ARE OPENING THE OBSERVERS FILE*/
    if (openWhich == 0) {
        struct observerTimeStamp *ptr = malloc(sizeof (struct observerTimeStamp));
        int inDay, inMonth, inYear, inHour, inMin, inSec;
        double latitude = 0;
        double longitude = 0;
        char observer [4];

        fscanf(filep, "%d %d %d %d %d %d", &inDay, &inMonth, &inYear, &inHour, &inMin, &inSec);
        ptr->day = inDay;
        ptr->month = inMonth;
        ptr->year = inYear;
        ptr->hour = inHour;
        ptr->min = inMin;
        ptr->second = inSec;
        observerTS = ptr;

        while (fscanf(filep, " %s %lf %lf", observer, &latitude, &longitude) != EOF) {
            addobserver(observer, latitude, longitude);
        }

        /*IF WE ARE OPENING THE SIGHTINGS FILE*/
    } else if (openWhich == 1) {
        double range = 0;
        double bearing = 0;
        char observer [4];
        char type [1];

        while (fscanf(filep, " %s %c %lf %lf", observer, type, &bearing, &range) != EOF) {
            addSighting(observer, type, bearing, range);
        }
    }
    fclose(filep);
}

struct observer* addobserver(char NewObserverID [4], double newLatit, double NewLongi) {
    struct observer *ptr = malloc(sizeof (struct observer));

    strncpy(ptr->observerID, NewObserverID, 4);
    ptr->latit = newLatit;
    ptr->longi = NewLongi;
    ptr->next = NULL;

    if (observerHead == NULL) {
        observerHead = observerTail = ptr;
    } else {
        observerTail->next = ptr;
        observerTail = ptr;
    }
    return ptr;
}

struct sighting* addSighting(char newObserverID [4], char newType [1],
        double newBearing, double newRange) {

    struct sighting *ptr = malloc(sizeof (struct sighting));
    strncpy(ptr->observerID, newObserverID, 5);
    strncpy(ptr->type, newType, 1);
    ptr->bearing = newBearing;
    ptr->range = newRange;
    ptr->next = NULL;
    ptr->podID = 0;

    location observer = searchList(newObserverID);
    ptr->mammalLoc = getMammalLocation(observer, newBearing, newRange);
    if (sightingsHead == NULL) {
        sightingsHead = sightingsTail = ptr;
    } else {
        sightingsTail->next = ptr;
        sightingsTail = ptr;
    }

    /*This statement will set display to 1 if outside of our sea area and
     * to 0 if it is within the area we are interested in*/
    if ((ptr->mammalLoc.lat > south && ptr->mammalLoc.lat < north)&&
            (ptr->mammalLoc.lng < east && ptr->mammalLoc.lng > west)) {
        ptr->display = 0;
    } else {
        ptr->display = 1;
        //printf ("\n-lat : %lf",ptr->mammalLoc.lat);
        //printf ("\n-long : %lf",ptr->mammalLoc.lng);
    }
    return ptr;
}

location searchList(char searchForID[4]) {
    struct observer *ptr = observerHead;
    location observerLocation;
    while (ptr != NULL) {
        if (strcmp(ptr->observerID, searchForID) == 0) {
            double tempLAT = ptr->latit;
            double tempLONG = ptr->longi;
            location observerLocation = {tempLAT, tempLONG};
            return observerLocation;
        }
        ptr = ptr->next;
    }
    perror("Observer not recognised.\n");
    return observerLocation;
}