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

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  Walls  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

void genWalls ()
{ 
    double wallRadius_ = xRange_/nWallGen_;
    //double yWallRadius_ = yRange_/nWallGen_;
    Walls_.resize (4*nWallGen_); 

    for ( int i = 0; i<nWallGen_; i++)
    { 
        Walls_[i]               = obstacle(  xMin_-wallRadius_,     yMin_+(i*wallRadius_), wallRadius_ );
        Walls_[i+(  nWallGen_)] = obstacle(  xMin_+(i*wallRadius_), yMax_+wallRadius_,     wallRadius_ );
        Walls_[i+(2*nWallGen_)] = obstacle(  xMax_+wallRadius_,     yMax_-(i*wallRadius_), wallRadius_ );
        Walls_[i+(3*nWallGen_)] = obstacle(  xMax_-(i*wallRadius_), yMin_-wallRadius_,     wallRadius_ );
    }
}

void wallCollision (vector<boid> bd, vector<obstacle> wl)
{
    
    for ( int i=0; i<wl.size(); i++ )
    {
        for ( int j=0; j<bd.size(); j++)
        {
            double distance_ = sqrt (
            (wl[i].getxOrigin ()-bd[j].getx ()) * (wl[i].getxOrigin ()-bd[j].getx ()) +
            (wl[i].getyOrigin ()-bd[j].gety ()) * (wl[i].getyOrigin ()-bd[j].gety ()) );

            double distancex_ = abs( wl[i].getxOrigin ()-bd[j].getx () );
            double distancey_ = abs( wl[i].getyOrigin ()-bd[j].gety () ); 
            if ( distance_ < wallRadius_ + boid::boidRadius_)
            {
                Updates_ +=1;

                if ( abs(bd[j].getx ()) > 1-boid::boidRadius_ )
                {
                    bd[j].setxV ( -bd[j].getxV () );
                }   

                if ( abs(bd[j].gety ()) > 1-boid::boidRadius_ )
                {
                    bd[j].setyV ( -bd[j].getyV () );
                } 
            }
        }
    }
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //