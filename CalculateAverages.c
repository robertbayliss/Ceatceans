#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "average_distance.h"
#include "navigation.h"
#include "structs.h"
void removeDuplicateAvgs(struct sighting *sighting);
int compareLocations(location, location);

void calculateAverages(struct sighting *sighting) {
    struct sighting *sighting2 = sightingsHead;
    struct sighting *sighting1;
    sighting1 = sighting;
    int counter = 0;

    while (sighting2 != NULL) {
        //If they're of the same type and with in the duplicate distance
        if ((great_circle(sighting1->mammalLoc, sighting2->mammalLoc) < isADuplicate)
                && (strcmp(sighting1->type, sighting2->type) == 0)) {
            //added the co-ordinates to the array
            sighting1->dupLocs[counter].lat = sighting2->mammalLoc.lat;
            sighting1->dupLocs[counter].lng = sighting2->mammalLoc.lng;
            counter++;
        }
        sighting2 = sighting2->next;
    }
    sighting1->numOfDup = counter;


    //Work out the average of the array locations and store
    int countup;
    double avgLat = 0;
    double avgLng = 0;

    for (countup = 0; countup != sighting1->numOfDup; countup++) {
        avgLat = avgLat + sighting1->dupLocs[countup].lat;
        avgLng = avgLng + sighting1->dupLocs[countup].lng;
    }
    avgLat = avgLat / sighting1->numOfDup;
    avgLng = avgLng / sighting1->numOfDup;


    location averageLoc = {avgLat, avgLng};
    sighting1->avgLoc = averageLoc;


    sighting1 = sighting1->next;
    if (sighting1->next != NULL) {
        calculateAverages(sighting1);
    }
    removeDuplicateAvgs(sightingsHead);

}

void removeDuplicateAvgs(struct sighting *sighting) {
    struct sighting *x = sightingsHead;
    struct sighting *y;
    y = sighting;

    while (x != NULL && (x != y)) {
        if (compareLocations(x->avgLoc, y->avgLoc) == 1) {
            y->display = 1;
        }
        x = x->next;
    }

    y = y->next;
    if (y->next != NULL) {
        removeDuplicateAvgs(y);
    }
}

int compareLocations(location loc1, location loc2) {
    //If the latitude ad longitude are the same return 1
    if ((loc1.lat == loc2.lat) && (loc1.lng == loc2.lng)) {
        return 1;
    } else {
        return 0;
    }
}