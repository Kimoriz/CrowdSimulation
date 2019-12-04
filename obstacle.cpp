#include "obstacle.h"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //
obstacle::obstacle()
{}

obstacle::obstacle ( double xOrigin, double yOrigin, double width, double height, int i )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    width_ = width;
    height_ = height;
    Radius_ = sqrt ((width_*width_)+(height_*height_));
    obsIndex_=i;
}

double obstacle::getxOrigin () { return xOrigin_; }
double obstacle::getyOrigin () { return yOrigin_; }
double obstacle::getRadius  () { return Radius_; }
double obstacle::getWidth   () { return width_; }
double obstacle::getHeight  () { return height_; }
int obstacle::getIndex  () { return obsIndex_; }

void genObstacles ()
{ 

    int nWallGen_ = 150;
    double wallRadius_ = (1.)/(nWallGen_);
    //double yWallRadius_ = yRange_/nWallGen_;
    //Walls_.resize (100); 
    
    /*for(int i = 0; i<nWallGen_; i++)
    {
        //Walls_[i] = obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_);
        //Walls_.push_back( obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_) );
        Walls_.push_back( obstacle(  -0.1, yMin_+i*wallRadius_, wallRadius_, 0.008,i) );
    }
    wallRadius_=1./nWallGen_;
    for(int i = 0; i<nWallGen_; i++)
    {
        //Walls_[i] = obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_);
        //Walls_.push_back( obstacle(  xMin_+i*wallRadius_, 0.4, wallRadius_) );
        Walls_.push_back( obstacle(  -0.1, i*wallRadius_, wallRadius_, 0.008,nWallGen_+i) );
    }*/
    for(int i=0; i<8*nWallGen_; i+=4)
    {
        Walls_.push_back( obstacle(  -0.99,yMin_+i*wallRadius_, wallRadius_, 0.008,i));
        Walls_.push_back( obstacle(  xMin_+i*wallRadius_,0.99, wallRadius_, 0.008,i+1));
        Walls_.push_back( obstacle(  0.99,yMin_+i*wallRadius_, wallRadius_, 0.008,i+2));
        Walls_.push_back( obstacle(  xMin_+i*wallRadius_,-0.99, wallRadius_, 0.008,i+3));
    }

}

void drawObstacles ( obstacle Obs)
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
