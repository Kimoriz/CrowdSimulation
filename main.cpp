#include "draw.cpp"

int main ( int argc, char **argv )  
{   
    srand ( time (NULL) );
    WindowSets ( argc, argv );

    int nboids_ = 100;
    //genObstacles ();

    genBoid ( nboids_ );    //Generate boids
    fillGrid();
    crowding ();

    return 0;
}  
