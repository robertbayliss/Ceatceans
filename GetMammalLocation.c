#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "navigation.h"
#define M_PI 3.14159265358979323846

location getMammalLocation(location observerLocation, double mammalBearing, double mammalRange) {
    double cmLAT, cmLONG;
    double oLAT = observerLocation.lat;
    double oLONG = observerLocation.lng;

    double oLATR = (oLAT) * M_PI / 180.0;
    double bGR = (mammalBearing) * M_PI / 180.0;

    cmLAT = oLAT + (mammalRange * cos(bGR)) / 60.0;
    cmLONG = oLONG + (mammalRange * sin(bGR) / cos(oLATR)) / 60.0;

    location mammalLocation = {cmLAT, cmLONG};
    return mammalLocation;
}
