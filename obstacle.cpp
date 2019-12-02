#include "obstacle.h"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

obstacle::obstacle ()
{}

obstacle::obstacle ( double xOrigin, double yOrigin, double width, double height )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    width_ = width;
    height_ = height;
    Radius_ = sqrt ((width_*width_)+(height_*height_));
}

double obstacle::getxOrigin () { return xOrigin_; }
double obstacle::getyOrigin () { return yOrigin_; }
double obstacle::getRadius  () { return Radius_; }
double obstacle::getWidth   () { return width_; }
double obstacle::getHeight  () { return height_; }

void genObstacles ()
{ 
    int nWallGen_ = 0;
    double wallRadius_ = (xRange_)/(nWallGen_);
    //double yWallRadius_ = yRange_/nWallGen_;
    //Walls_.resize (100); 
    
    for(int i = 0; i<nWallGen_; i++)
    {
        //Walls_[i] = obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_);
        //Walls_.push_back( obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_) );
        Walls_.push_back( obstacle(  -0.1, yMin_+i*wallRadius_, wallRadius_, 0.008) );
        
    }
    //for(int i = nWallGen_/2; i<nWallGen_; i++)
    //{
    //    //Walls_[i] = obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_);
    //    //Walls_.push_back( obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_) );
    //    Walls_.push_back( obstacle(  -0.2, 0.2+i*wallRadius_, wallRadius_) );
    //}
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
    double obsWidth_ = Obs.getWidth ();
    double obsHeight_ = Obs.getHeight ();
    glPushMatrix ();
    glTranslatef ( Obs.getxOrigin(), Obs.getyOrigin(), 0 );
    glColor4d ( 1., 1., 1., 0. );
    glBegin ( GL_QUADS );
     glVertex2d ( -obsWidth_,  obsHeight_ );
     glVertex2d (  obsWidth_,  obsHeight_ );
     glVertex2d (  obsWidth_, -obsHeight_ );
     glVertex2d ( -obsWidth_, -obsHeight_ );
    glEnd ();
    glPopMatrix ();
}



// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //
