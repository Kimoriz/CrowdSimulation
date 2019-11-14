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

void wallCollision ()
{
    for ( int i=0; i<Walls_.size(); i++ )
    {
        for ( int j=0; j<nBoid_.size(); j++)
        {
            double distance_ = sqrt (
            (Walls_[i].getxOrigin ()-nBoid_[j].getx ()) * (Walls_[i].getxOrigin ()-nBoid_[j].getx ()) +
            (Walls_[i].getyOrigin ()-nBoid_[j].gety ()) * (Walls_[i].getyOrigin ()-nBoid_[j].gety ()) );

            double distancex_ = abs( Walls_[i].getxOrigin ()-nBoid_[j].getx () );
            double distancey_ = abs( Walls_[i].getyOrigin ()-nBoid_[j].gety () ); 
            if ( distance_ < wallRadius_ + boid::boidRadius_)
            {
                Updates_ +=1;

                if ( abs(nBoid_[j].getx ()) > 1-boid::boidRadius_ )
                {
                    nBoid_[j].setxV ( -nBoid_[j].getxV () );
                }   

                if ( abs(nBoid_[j].gety ()) > 1-boid::boidRadius_ )
                {
                    nBoid_[j].setyV ( -nBoid_[j].getyV () );
                } 
            }
        }
    }
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //