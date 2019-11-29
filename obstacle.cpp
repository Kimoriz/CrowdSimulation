#include "obstacle.h"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

obstacle::obstacle ()
{}

obstacle::obstacle ( double xOrigin, double yOrigin, double Radius )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    Radius_ = Radius;
    width_ = Radius/sqrt(2);
}

double obstacle::getxOrigin () { return xOrigin_; }
double obstacle::getyOrigin () { return yOrigin_; }
double obstacle::getRadius  () { return Radius_; }
double obstacle::getWidth   () { return width_; }

void genObstacles ()
{ 
    int nWallGen_ = 1000;
    double wallRadius_ = (1.6)/(nWallGen_);
    //double yWallRadius_ = yRange_/nWallGen_;
    //Walls_.resize (100); 
    
    for(int i = 0; i<nWallGen_/2; i++)
    {
        //Walls_[i] = obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_);
        //Walls_.push_back( obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_) );
        Walls_.push_back( obstacle(  -0.2, yMin_+i*wallRadius_, wallRadius_) );
    }
    for(int i = nWallGen_/2; i<nWallGen_; i++)
    {
        //Walls_[i] = obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_);
        //Walls_.push_back( obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_) );
        Walls_.push_back( obstacle(  -0.2, 0.2+i*wallRadius_, wallRadius_) );
    }
/*    
    for(int i = 11; i<90; i++)
    {
        Walls_[i] = obstacle(  -0.8 + (2+i)*wallRadius_, 0.7, wallRadius_);
    }
     
    for(int i = 92; i<100; i++)
    {
        Walls_[i] = obstacle( 0.8+(2+i)*wallRadius_, 0.7, wallRadius_);
    }
/*
    for ( int i = 0; i<nWallGen_; i++)
    { 
        Walls_[i]               = obstacle(  xMin_-wallRadius_,     yMin_+(i*wallRadius_), wallRadius_ );
        Walls_[i+(  nWallGen_)] = obstacle(  xMin_+(i*wallRadius_), yMax_+wallRadius_,     wallRadius_ );
        Walls_[i+(2*nWallGen_)] = obstacle(  xMax_+wallRadius_,     yMax_-(i*wallRadius_), wallRadius_ );
        Walls_[i+(3*nWallGen_)] = obstacle(  xMax_-(i*wallRadius_), yMin_-wallRadius_,     wallRadius_ );
    }
*/
}

void drawObstacles ( obstacle Obs )
{
    double Displacement_ = Obs.getWidth ();
    glPushMatrix ();
    glTranslatef ( Obs.getxOrigin(), Obs.getyOrigin(), 0 );
    glColor4d ( 1., 1., 1., 0. );
    glBegin ( GL_QUADS );
     glVertex2d ( -Displacement_,  Displacement_ );
     glVertex2d (  Displacement_,  Displacement_ );
     glVertex2d (  Displacement_, -Displacement_ );
     glVertex2d ( -Displacement_, -Displacement_ );
    glEnd ();
    glPopMatrix ();
}



// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //
