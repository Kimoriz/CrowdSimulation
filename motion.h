#include "quadrant.cpp"

double dt_ = 0;

void idle ();

void refSys ( int width, int height );

void resize ();

void axes ();

void fillGrid();

void genCrowd ( int nBoids );

void timeUpdate ( void );

void handler ();