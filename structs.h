/* 
 * File:   Structs.h
 * Author: rob41
 *
 * Created on 05 December 2014, 18:35
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

    
#ifdef	__cplusplus
extern "C" {
#endif

struct observerTimeStamp{
        int day;
        int month;
        int year;
        int hour;
        int min;
        int second;
    };
    
    struct observer{
        struct observer *next;
        char observerID [5];
        double latit;
        double longi;
    };

    struct sighting{
        struct sighting *next;
        char observerID [5];
        char type [1];
        double bearing;
        double range;
        _Bool display;
        int numOfDup;
        int podID;
        location mammalLoc;
        location dupLocs[50];
        location avgLoc;
    };
     
    struct pod{
        struct pod *next;
        location locations[50];
        char type [1];
        int podID;
        int sizeOfPod;
    };
    
    struct observerTimeStamp *observerTS;
    
    struct pod *podHead;
    struct pod *podTail;
    
    struct observer *observerHead;
    struct observer *observerTail;
    
    struct sighting *sightingsHead;
    struct sighting *sightingsTail;


#ifdef	__cplusplus
}
#endif

#endif	/* STRUCTS_H */

