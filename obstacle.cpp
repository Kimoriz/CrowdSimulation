#include "obstacle.h"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

obstacle::obstacle ()
{}

obstacle::obstacle ( double xOrigin, double yOrigin, double Radius )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    Radius_ = Radius;
}

double obstacle::getxOrigin () { return xOrigin_; }
double obstacle::getyOrigin () { return yOrigin_; }
double obstacle::getRadius  () { return Radius_; }

//void genObstacles ()
//{ 
//    double wallRadius_ = xRange_/nWallGen_;
//    //double yWallRadius_ = yRange_/nWallGen_;
//    Walls_.resize (4*nWallGen_); 
//
//    for ( int i = 0; i<nWallGen_; i++)
//    { 
//        Walls_[i]               = obstacle(  xMin_-wallRadius_,     yMin_+(i*wallRadius_), wallRadius_ );
//        Walls_[i+(  nWallGen_)] = obstacle(  xMin_+(i*wallRadius_), yMax_+wallRadius_,     wallRadius_ );
//        Walls_[i+(2*nWallGen_)] = obstacle(  xMax_+wallRadius_,     yMax_-(i*wallRadius_), wallRadius_ );
//        Walls_[i+(3*nWallGen_)] = obstacle(  xMax_-(i*wallRadius_), yMin_-wallRadius_,     wallRadius_ );
//    }
//}

//void drawObstacles ();

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //