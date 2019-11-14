#include "quadrant.h"


// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  GRID -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

quadrant::quadrant ( double xOrigin, double yOrigin )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    quadrantWidth_ = (xRange_/2)/sqrt(nGrid_);
}

void quadrant::boidPlacer ()
{
    for ( int i=0; i<nBoids_; i++)
    { 
        It_ = nBoid_.begin ()+i;

        if (xOrigin_-quadrantWidth_ < nBoid_[i].getx () && nBoid_[i].getx () < xOrigin_+quadrantWidth_ 
        &&  yOrigin_-quadrantWidth_ < nBoid_[i].gety () && nBoid_[i].gety () < yOrigin_+quadrantWidth_)
        {
            nSubBoid_.push_back ( nBoid_[i] );
            nBoid_.erase ( It_ );
        }
    }

}


// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //