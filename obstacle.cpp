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

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  Walls  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

void wallCollision ( vector<boid> &boid )
{
    for ( int j=0; j<boid.size(); j++)
    {
        double distancex_ = xMax_-abs(boid[j].getx ());
        double distancey_ = yMax_-abs(boid[j].gety ()); 

        if ( distancex_ < boid::boidRadius_ || distancey_ < boid::boidRadius_ )
        {
            Updates_ +=1;
            if ( abs(boid[j].getx ()) > 1-boid::boidRadius_ )
            {
                boid[j].setxV ( -boid[j].getxV () );
            }   
            if ( abs(boid[j].gety ()) > 1-boid::boidRadius_ )
            {
                boid[j].setyV ( -boid[j].getyV () );
            } 
        }
    }
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //