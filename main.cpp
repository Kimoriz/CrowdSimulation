//Give vision to generate check Walls in an easier way, actually walls do not ever need to be drawn or create, those are the border of the frame
//Grid collision evaluation 


#include "draw.cpp"

int main ( int argc, char **argv )  
{   
    srand ( time (NULL) );
    WindowSets ( argc, argv );

    int nboids_ = 100;
    genWalls ();

    genBoid ( nboids_ );    //Generate boids
    fillGrid();
    crowding ();

    return 0;
}  
