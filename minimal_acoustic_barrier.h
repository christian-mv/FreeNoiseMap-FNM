#ifndef MINIMAL_ACOUSTIC_BARRIER_H
#define MINIMAL_ACOUSTIC_BARRIER_H


/*
 * This barrier is essentially defined as a line
 * and a height
*/

struct Minimal_acoustic_barrier
{
    double height;
    double p1x;
    double p1y;

    double p2x;
    double p2y;
};

#endif // MINIMAL_ACOUSTIC_BARRIER_H
