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
    for ( int i=0; i<grid_.size(); i++ )
    {
        for ( int j=0; j<grid_[i].nSubBoid_.size(); j++ )
        {   
            drawBoid ( grid_[i].nSubBoid_[j] );
        }
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

void genCrowd ()
{   
    glClearColor ( 0.0, 0.4, 0.4, 0. );
    glClear ( GL_COLOR_BUFFER_BIT );

    int counter_ = 0;

    chrono::high_resolution_clock::time_point ti = chrono::high_resolution_clock::now ();
    
    while(counter_<100)
    {
        vector <boid> copynBoid_;
        for(int i=0; i<grid_.size(); i++)               //looping the grid
        {
            copynBoid_=grid_[i].nSubBoid_;
            for(int j=0; j<copynBoid_.size(); j++)      //looping the boid 
            {
                grid_[i].nSubBoid_[j].collision ( copynBoid_ );
                grid_[i].nSubBoid_[j].updatex ( dt_ );
                grid_[i].nSubBoid_[j].updatey ( dt_ );
                grid_[i].nSubBoid_[j].updatexV ( dt_ );
                grid_[i].nSubBoid_[j].updateyV ( dt_ );
                grid_[i].nSubBoid_[j].setxA ( 0 );
                grid_[i].nSubBoid_[j].setyA ( 0 );
            }
            wallCollision ( grid_[i].nSubBoid_ );       //checking the walls
            grid_[i].tresPass ();
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

            if((rand()%2)==1)                            //Randomizer x's and y's
            {
                mindRefresher ( grid_[i].nSubBoid_[j] ); 
            }
            else  
            { 
                mindRefresher ( grid_[i].nSubBoid_[j] ); 
            }            
            drawBoid ( grid_[i].nSubBoid_[j] );
        }
        goalReacher ( grid_[i].nSubBoid_ );
    }
    //cout<<boidDrawn_<<endl;
    cout<<"Collision #: "<<nCollision_<<'\t'<<"Time: "<<time_span.count ()<<'\t'<<"Collision/time : "<<nCollision_/time_span.count ()<<endl;
    nCollision_ = 0;
    glutSwapBuffers ();
}

void timeUpdate ( void )
{
    dt_ = 0.00001;
    glutPostRedisplay();
}

void handler () 
{   
    idle();
    glutDisplayFunc ( genCrowd );
    glutReshapeFunc ( refSys );
}