#include "motion.h"

void idle ()
{   
    glutInit ( &argc_, argv_ ); 
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize ( Width_ , Height_ );
    glutInitWindowPosition ( 0, 0 );
    glutCreateWindow ( "That's Sick Dude" );

    renderBoid();                                       //Generate boids structure, later should be used also for obstacles ecc...

    glClearColor (0.0, 0.2, 0.5, 0.5);
    for ( int i = 0; i < nBoids_; i++)
    {   
        drawBoid ( nBoid_[i] );
    }
}

void refSys ( int Width_, int Height_ )
{   
    glViewport ( 0, 0, Width_, Height_ );               //Position of left down corner and the top right of the frame
    glMatrixMode ( GL_PROJECTION );                     //GL_MODELVIEW to stack more Push-Pop/Matrix
    glLoadIdentity ();                                  //Load identity matrix
    gluOrtho2D ( xMin_, xMax_, yMin_, yMax_);           //Should be done with pixels...
    }

void resize ()
{   
    glColor3d ( 1.0, 0.2, 0.2 );
    glBegin ( GL_QUADS );
     glVertex2d ( xMin_, yMin_ );
     glVertex2d ( xMax_, yMin_ );
     glVertex2d ( xMax_, yMax_ );
     glVertex2d ( xMin_, yMax_ );
    glEnd ();
}

void axes ()
{
    glColor3d ( 0.0, 0.0, 0.0 );
    glBegin ( GL_LINES );
     glVertex2d ( xMin_,    0. );
     glVertex2d ( xMax_,    0. );
     glVertex2d (    0., yMin_ );
     glVertex2d (    0., yMax_ );
    glEnd (); 
}

void fillGrid() //filling the grid with people and walls, then deleting the empty vectors of people and walls
{
    double x=0; 
    double y=0; 
    for(int i=0; i<sqrt(nQuadrant_); i++)
    {
        for(int j=0; j<sqrt(nQuadrant_); j++)
        {
            x=-1+(i*(xRange_/sqrt(nQuadrant_))+((xRange_/sqrt(nQuadrant_))/2));
            y=1-(j*(yRange_/sqrt(nQuadrant_))+((yRange_/sqrt(nQuadrant_))/2));
            //cout<<"X="<<x<<" Y="<<y<<endl;
            grid_.push_back(quadrant(x,y));
        }
    }
    for(int i=0; i<grid_.size(); i++)
    {
        grid_[i].boidPlacer();
        grid_[i].wallPlacer();
    }
    nBoid_.shrink_to_fit();
    Walls_.shrink_to_fit();
}

void genCrowd ()
{   
    glClearColor ( 0.0, 0.4, 0.4, 0. );
    glClear ( GL_COLOR_BUFFER_BIT );

    int counter_ = 0;

    chrono::high_resolution_clock::time_point ti = chrono::high_resolution_clock::now ();
    /*while ( counter_<100 )
    {
        vector <boid> copynBoid_ = nBoid_;
        for ( int i=0; i<nBoids_; i++ )
        {
            nBoid_[i].collision ( copynBoid_ );
            nBoid_[i].updatex ( dt_ );
            nBoid_[i].updatey ( dt_ );
            nBoid_[i].updatexV ( dt_ );
            nBoid_[i].updateyV ( dt_ );
            nBoid_[i].setxA ( 0 );
            nBoid_[i].setyA ( 0 );
        }
        wallCollision();
        counter_ ++;
    }*/
    while(counter_<100)
    {
        vector <boid> copynBoid_;
        for(int i=0; i<grid_.size(); i++)          //looping the grid
        {
            copynBoid_=grid_[i].nSubBoid_;
            for(int j=0; j<copynBoid_.size(); j++) //looping the boid 
            {
                grid_[i].nSubBoid_[j].collision ( copynBoid_ );
                grid_[i].nSubBoid_[j].updatex ( dt_ );
                grid_[i].nSubBoid_[j].updatey ( dt_ );
                grid_[i].nSubBoid_[j].updatexV ( dt_ );
                grid_[i].nSubBoid_[j].updateyV ( dt_ );
                grid_[i].nSubBoid_[j].setxA ( 0 );
                grid_[i].nSubBoid_[j].setyA ( 0 );
            }
            wallCollision(copynBoid_,grid_[i].subWall_);//checking the walls
        }
        counter_ ++;
    }
    chrono::high_resolution_clock::time_point tf = chrono::high_resolution_clock::now ();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>> ( tf - ti );
    for(int i=0; i<grid_.size(); i++)
    {
        for(int j=0; j<grid_[i].nSubBoid_.size(); j++)
        {
           // It_ = nBoid_.begin() + j;

            //if((rand()%2)==1)                            //Randomizer x's and y's
            //    { mindRefresher (nBoid_[j]); }
            //else  
            //{ 
            //    mindRefresher (nBoid_[j]); 
            //}
            //goalReacher ( nBoid_[j]);
            drawBoid ( grid_[i].nSubBoid_[j] );
        }
    }
    //cout<<"Collision #: "<<nCollision_<<'\t'<<"Time: "<<time_span.count ()<<'\t'<<"Collision/time : "<<nCollision_/time_span.count ()<<endl;
    nCollision_ = 0;
    glutSwapBuffers ();
}

void timeUpdate ( void )
{
    dt_ = 0.001;
    glutPostRedisplay();
}

void handler () 
{   
    idle();
    glutDisplayFunc ( genCrowd );
    glutReshapeFunc ( refSys );
}