/* 
 * File:   main.c
 * Author: ROB41
 *
 * Created on 01 December 2014, 14:28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pod_distance.h"
#include "navigation.h"
#include "structs.h"


/*This is the code for the POD Mission*/
void createPod(struct sighting *sighting1, struct sighting *sighting2);
void addtoPod(struct sighting *sighting1, struct sighting *sighting2);
int numberOfPods = 0;

void createPod(struct sighting *x, struct sighting *y) {
    struct pod *pointer = malloc(sizeof (struct pod));

    numberOfPods++;
    pointer->sizeOfPod = 2;
    pointer->podID = numberOfPods;
    x->podID = numberOfPods;
    y->podID = numberOfPods;

    strncpy(pointer->type, x->type, 1);
    pointer->locations[0].lat = x->avgLoc.lat;
    pointer->locations[0].lng = x->avgLoc.lng;
    pointer->locations[1].lat = y->avgLoc.lat;
    pointer->locations[1].lng = y->avgLoc.lng;

    if (podHead == NULL) {
        podHead = podTail = pointer;
    } else {
        podTail->next = pointer;
        podTail = pointer;
    }
}

void addtoPod(struct sighting *x, struct sighting *y) {
    struct pod *pointer = podHead;

    //If x is in and pod and y isn't add y to x's pod
    if (x->podID != 0) {
        //Find the right pod
        while (pointer->podID != x->podID) {
            pointer = pointer->next;
        }
        pointer->locations[pointer->sizeOfPod].lat = y->avgLoc.lat;
        pointer->locations[pointer->sizeOfPod].lng = y->avgLoc.lng;
        y->podID = pointer->podID;

        //If y is in and pod and x isn't add x to y's pod    
    } else if (y->podID != 0) {
        //Find the right pod
        while (pointer->podID != y->podID) {
            pointer = pointer->next;
        }
        pointer->locations[pointer->sizeOfPod].lat = x->avgLoc.lat;
        pointer->locations[pointer->sizeOfPod].lng = x->avgLoc.lng;
        x->podID = pointer->podID;
    }
    pointer->sizeOfPod++;
}

void findPods() {
    struct sighting *x = sightingsHead;
    struct sighting *y = x->next;
    while (x != NULL) {
        while (y != NULL) {
            //printf("%lf\n",great_circle(x->avgLoc,y->avgLoc));

            /*If the great circle distance is less than the pod distance
             *And the mammal is the same type then set it to not be displayed*/
            if ((great_circle(x->avgLoc, y->avgLoc) < inAPod) && (strcmp(x->type,
                    y->type) == 0) && ((y->display == 0)&&(x->display == 0))) {

                //If there are no Pods or neither of them are already in a pod
                if (podHead == NULL || ((x->podID == 0) && (y->podID == 0))) {
                    createPod(x, y);
                    //If x is in a pod 
                } else if (((x->podID != 0) && (y->podID == 0)) ||
                        ((x->podID == 0) && (y->podID != 0))) {
                    addtoPod(x, y);
                }
            }
            y = y->next;
        }
        x = x->next;
        /*This prevents segmentation fault*/
        if (x != NULL) {
            y = x->next;
        }
    }
}