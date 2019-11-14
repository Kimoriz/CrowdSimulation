#include "quadrant.h"


// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-  QUADRANT -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

quadrant::quadrant ( double xOrigin, double yOrigin )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    quadrantWidth_ = (xRange_/2)/sqrt(nQuadrant_);
}

void quadrant::boidPlacer ()
{
    int a=0; //just as debugger
    for ( int i=0; i<nBoids_; i++)
    { 
        It_b = nBoid_.begin ()+i;

        if (xOrigin_-quadrantWidth_ < nBoid_[i].getx () && nBoid_[i].getx () < xOrigin_+quadrantWidth_ 
        &&  yOrigin_-quadrantWidth_ < nBoid_[i].gety () && nBoid_[i].gety () < yOrigin_+quadrantWidth_)
        {
            a++;
            nSubBoid_.push_back ( nBoid_[i] );
            nBoid_.erase ( It_b );
            //cout<<"Boid # "<<a<<" is inside\n";
        }
    }
}

void quadrant::wallPlacer ()
{
    for ( int i=0; i<nBoids_; i++)
    { 
        It_w = Walls_.begin ()+i;

        if (xOrigin_-quadrantWidth_ < Walls_[i].getxOrigin () && Walls_[i].getxOrigin () < xOrigin_+quadrantWidth_ 
        &&  yOrigin_-quadrantWidth_ < Walls_[i].getyOrigin () && Walls_[i].getyOrigin () < yOrigin_+quadrantWidth_)
        {
            subWall_.push_back ( Walls_[i] );
            subWall_.erase ( It_w );
        }
    }
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //
