#include "draw.cpp"

int main ( int argc, char **argv )  
{   
    srand ( time (NULL) );
    WindowSets ( argc, argv );

    nBoids_ = 40;

    genBoid ();    //Generate boids
    genObstacles ();
    genGrid();     //Generate the grid and fill the quadrants

    crowding ();

    return 0;
} 