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
            drawBoid ( nBoid_[grid_[i].nSubBoid_[j]] );
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
        for(int i=0; i<grid_.size(); i++)               //looping the grid
        {
            vector <int> copynBoid_;
            int N=sqrt(nQuadrant_);
            //cout<<N<<"\t"<<i<<"\n";
            copynBoid_=grid_[i].nSubBoid_;
            //cout<<copynBoid_.size()<<endl;
            if(i==0)//bot left corner
            {
                //cout<<"Bot Left\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1].nSubBoid_.begin(),grid_[i+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N].nSubBoid_.begin(),grid_[i+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N+1].nSubBoid_.begin(),grid_[i+N+1].nSubBoid_.end());
            }
            else if(i==((N*N)-1))//top right corner
            {
                //cout<<"Top Right\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1].nSubBoid_.begin(),grid_[i-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N].nSubBoid_.begin(),grid_[i-N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N-1].nSubBoid_.begin(),grid_[i-N-1].nSubBoid_.end());
            }
            else if(i==(N-1))//bottom right corner
            {
                //cout<<"Bot Right\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1].nSubBoid_.begin(),grid_[i-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N].nSubBoid_.begin(),grid_[i+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N-1].nSubBoid_.begin(),grid_[i+N-1].nSubBoid_.end());   
            }
            else if(i==((N*N)-1-N))//top left corner
            {
                //cout<<"Top Left\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1].nSubBoid_.begin(),grid_[i+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N].nSubBoid_.begin(),grid_[i-N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N+1].nSubBoid_.begin(),grid_[i-N+1].nSubBoid_.end()); 
            }
            else if(i>((N*N)-N))//first row
            {
                //cout<<"First Row\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1].nSubBoid_.begin(),grid_[i-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1].nSubBoid_.begin(),grid_[i+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N].nSubBoid_.begin(),grid_[i-N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N-1].nSubBoid_.begin(),grid_[i-N-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N+1].nSubBoid_.begin(),grid_[i-N+1].nSubBoid_.end());
            }
            else if(i<N)//last row
            {
                //cout<<"Last Row\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1].nSubBoid_.begin(),grid_[i-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1].nSubBoid_.begin(),grid_[i+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N].nSubBoid_.begin(),grid_[i+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N-1].nSubBoid_.begin(),grid_[i+N-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N+1].nSubBoid_.begin(),grid_[i+N+1].nSubBoid_.end());
            }
            else if(i%N==0)//first column
            {
                //cout<<"First Col\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N].nSubBoid_.begin(),grid_[i+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N].nSubBoid_.begin(),grid_[i-N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1].nSubBoid_.begin(),grid_[i+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1+N].nSubBoid_.begin(),grid_[i+1+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1-N].nSubBoid_.begin(),grid_[i+1-N].nSubBoid_.end());
            }
            else if(i%N==1)//last column
            {
                //cout<<"Last Col\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N].nSubBoid_.begin(),grid_[i+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N].nSubBoid_.begin(),grid_[i-N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1].nSubBoid_.begin(),grid_[i-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1+N].nSubBoid_.begin(),grid_[i-1+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1-N].nSubBoid_.begin(),grid_[i-1-N].nSubBoid_.end());
            }
            else
            {
                //cout<<"Else\n";
                //copynBoid_.insert(copynBoid_.end(),grid_[i].nSubBoid_.begin(),grid_[i].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-1].nSubBoid_.begin(),grid_[i-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+1].nSubBoid_.begin(),grid_[i+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N].nSubBoid_.begin(),grid_[i-N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N-1].nSubBoid_.begin(),grid_[i-N-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i-N+1].nSubBoid_.begin(),grid_[i-N+1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N].nSubBoid_.begin(),grid_[i+N].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N-1].nSubBoid_.begin(),grid_[i+N-1].nSubBoid_.end());
                copynBoid_.insert(copynBoid_.end(),grid_[i+N+1].nSubBoid_.begin(),grid_[i+N+1].nSubBoid_.end());
            }
            //cout<<"After copynBoid\n";
            //cout<<copynBoid_.size()<<endl;
            for(int j=0; j<grid_[i].nSubBoid_.size(); j++)      //looping the boid 
            {
                //cout<<j<<" Before collision\n";
                nBoid_[grid_[i].nSubBoid_[j]].collision ( copynBoid_ );
                nBoid_[grid_[i].nSubBoid_[j]].updatex ( dt_ );
                nBoid_[grid_[i].nSubBoid_[j]].updatey ( dt_ );
                nBoid_[grid_[i].nSubBoid_[j]].updatexV ( dt_ );
                nBoid_[grid_[i].nSubBoid_[j]].updateyV ( dt_ );
                nBoid_[grid_[i].nSubBoid_[j]].setxA ( 0 );
                nBoid_[grid_[i].nSubBoid_[j]].setyA ( 0 );
            }
            wallCollision ( grid_[i].nSubBoid_ );       //checking the walls
            obstacleCollision(grid_[i].nSubBoid_, grid_[i].subObstacles_);
            grid_[i].tresPass ();
            //cout<<"Out collision\n";
        }
        
        counter_ ++;
    }
    chrono::high_resolution_clock::time_point tf = chrono::high_resolution_clock::now ();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>> ( tf - ti );
    
    for(int i=0; i<grid_.size(); i++)
    {
        for ( int j=0; j<grid_[i].subObstacles_.size(); j++ )
        {   
            drawObstacles ( grid_[i].subObstacles_[j] );
        }
    
        for(int j=0; j<grid_[i].nSubBoid_.size(); j++)   //grid_[i].nSubBoid_[j]
        {
            //It_ = nBoid_.begin() + j;
            if((rand()%2)==1)                            //Randomizer x's and y's
            {
                mindRefresher ( nBoid_[grid_[i].nSubBoid_[j]] ); 
            }
            else  
            { 
                mindRefresher ( nBoid_[grid_[i].nSubBoid_[j]] ); 
            }           
            drawBoid ( nBoid_[grid_[i].nSubBoid_[j]] );
            goalReacher ( nBoid_[grid_[i].nSubBoid_[j]] );
        }
        //goalReacher ( nBoid_[grid_[i].nSubBoid_] );
    }
    //cout<<boidDrawn_<<endl;
    //cout<<"Collision #: "<<nCollision_<<'\t'<<"Time: "
    cout<<time_span.count ()<<endl;//'\t'<<"Collision/time : "<<nCollision_/time_span.count ()<<endl;
    nCollision_ = 0;
    glutSwapBuffers ();
}

void timeUpdate ( void )
{
    dt_ = 0.0001;
    glutPostRedisplay();
}

void handler () 
{   
    idle();
    glutDisplayFunc ( genCrowd );
    glutReshapeFunc ( refSys );
}