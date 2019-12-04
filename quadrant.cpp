#include "quadrant.h"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-  QUADRANT -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

int quadrant::quadCounter_ = 0;

double clamp(double x, double upper, double lower)
{
    return min(upper, max(x, lower));
}


quadrant::quadrant ( double xOrigin, double yOrigin )
{
    xOrigin_ = xOrigin;
    yOrigin_ = yOrigin;
    xQuadMin_ = xOrigin_ - quadrantWidth_;
    xQuadMax_ = xOrigin_ + quadrantWidth_;
    yQuadMin_ = yOrigin_ - quadrantWidth_;
    yQuadMax_ = yOrigin_ + quadrantWidth_;
    quadIndex_ = quadCounter_;

    nSubBoidSize_ = 0;

    quadCounter_ += 1;
}

void genGrid()                      //generates the grid and fill the subVector of boids and obstacles
{
    quadrantWidth_ = (xRange_/2.)/(sqrt(nQuadrant_));
    for ( int yIndex=0; yIndex<sqrt(nQuadrant_); yIndex++)
    {
        for ( int xIndex=0; xIndex<sqrt(nQuadrant_); xIndex++)
        {
            double xOrigin = xMin_+((1+(2*xIndex))*quadrantWidth_);
            double yOrigin = yMin_+((1+(2*yIndex))*quadrantWidth_);

            grid_.push_back( quadrant (xOrigin, yOrigin) );
        }
    }
    for(int i=0; i<grid_.size(); i++)
    {
        grid_[i].boidPlacer ();
        grid_[i].nSubBoidSize_ = grid_[i].nSubBoid_.size();
        grid_[i].ObstaclePlacer();
    }
    nBoid_.shrink_to_fit();
    //Obstacle_.shrink_to_fit();
}

void quadrant::boidPlacer ()
{
    for ( int boidIndex=0; boidIndex<nBoid_.size (); boidIndex++)               //by using a non-constant value, when a boid was found nBoid_.size () shrinks, so the index need to stay the same, otherwise a boid would be bounced
    {   
        if ( (nBoid_[boidIndex].getx () > xQuadMin_) && (nBoid_[boidIndex].getx () <= xQuadMax_) 
        &&   (nBoid_[boidIndex].gety () > yQuadMin_) && (nBoid_[boidIndex].gety () <= yQuadMax_) )
        {
            //nBoid_[boidIndex].setbelongIndex ( quadIndex_ ); 
            nSubBoid_.reserve (1);
            nSubBoid_.push_back ( nBoid_[boidIndex].getIdentity () );
            //nBoid_.erase ( nBoid_.begin ()+boidIndex );
            //boidIndex-=1;
        }
    }
}


void quadrant::ObstaclePlacer ()
{
    for ( int i=0; i<Walls_.size(); i++)
    { 
        if (xOrigin_-quadrantWidth_ < Walls_[i].getxOrigin () && Walls_[i].getxOrigin () < xOrigin_+quadrantWidth_ 
        &&  yOrigin_-quadrantWidth_ < Walls_[i].getyOrigin () && Walls_[i].getyOrigin () < yOrigin_+quadrantWidth_)
        {
            subObstacles_.reserve (1);
            subObstacles_.push_back ( Walls_[i].getIndex() );
            //Walls_.erase ( Walls_.begin ()+i );
            // i-=1;
        }
    }
}
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  Walls Collisions  -+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

/*void wallCollision ( vector<int> &nBoid )
{
    for ( int boidIndex=0; boidIndex<nBoid.size(); boidIndex++)
    {
        double distancex_ = xMax_-abs(nBoid_[nBoid[boidIndex]].getx ());
        double distancey_ = yMax_-abs(nBoid_[nBoid[boidIndex]].gety ()); 

        if ( distancex_ < boid::boidRadius_ || distancey_ < boid::boidRadius_ )
        {
            Updates_ +=1;
            if ( abs(nBoid_[nBoid[boidIndex]].getx ()) > 1-boid::boidRadius_ )
            {
                nBoid_[nBoid[boidIndex]].setxV ( -nBoid_[nBoid[boidIndex]].getxV () );
            }   
            if ( abs(nBoid_[nBoid[boidIndex]].gety ()) > 1-boid::boidRadius_ )
            {
                nBoid_[nBoid[boidIndex]].setyV ( -nBoid_[nBoid[boidIndex]].getyV () );
            } 

        }
    }
    
}*/

int obstacleCollision ( vector<int> &nBoid, vector<int> &wall)
{
    if(wall.size() == 0)
    {  
        return -1;
    }
    double wallRadius = Walls_[wall[0]].getRadius ();
    double wWidth_ = Walls_[wall[0]].getWidth ();
    double distancex_, distancey_;
    double xClamp_, yClamp_;
    double xP_, yP_;

    for(int i = 0; i<nBoid.size(); i++)
    {
        for (int j = 0; j<wall.size(); j++)
        {
            distancex_ = Walls_[wall[j]].getxOrigin()-(nBoid_[nBoid[i]].getx ());
            distancey_ = Walls_[wall[j]].getyOrigin()-(nBoid_[nBoid[i]].gety ()); 
            //cout <<wradius<<endl;
            if ( abs(distancex_) < (boid::boidRadius_ + wallRadius)  && abs(distancey_) < (boid::boidRadius_ + wallRadius) )
            {
                xClamp_ = clamp ( distancex_, -wWidth_ , wWidth_ ); 
                yClamp_ = clamp ( distancey_, -wWidth_ , wWidth_ ); 
                xP_ = Walls_[wall[j]].getxOrigin() + xClamp_; 
                yP_ = Walls_[wall[j]].getyOrigin() + yClamp_;
                
                if ( abs(nBoid_[nBoid[i]].getx()-(xP_))<abs(nBoid_[nBoid[i]].gety()-(yP_)) )
                {
                    nBoid_[nBoid[i]].setyV(-nBoid_[nBoid[i]].getyV());
                }
                else nBoid_[nBoid[i]].setxV(-nBoid_[nBoid[i]].getxV());
            }
        }
    }
    return 0;
}



// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

//OLD VERSION OF VOID TRESPASS: if we decide to use this, we also need to update the collision system
void quadrant::tresPass ()          //Logic based on a bounded 2D space (alias with walls)
{
    for ( int boidIndex=0; boidIndex<nSubBoid_.size(); boidIndex++ )
    {
        if ( nBoid_[nSubBoid_[boidIndex]].getExistance () )
        {
            if ( nBoid_[nSubBoid_[boidIndex]].getx () < xQuadMin_ ) boidMover ( boidIndex, quadIndex_, (quadIndex_-1) );
            if ( nBoid_[nSubBoid_[boidIndex]].getx () > xQuadMax_ ) boidMover ( boidIndex, quadIndex_, (quadIndex_+1) );
            if ( nBoid_[nSubBoid_[boidIndex]].gety () < yQuadMin_ ) boidMover ( boidIndex, quadIndex_, (quadIndex_-sqrt(nQuadrant_)) );
            if ( nBoid_[nSubBoid_[boidIndex]].gety () > yQuadMax_ ) boidMover ( boidIndex, quadIndex_, (quadIndex_+sqrt(nQuadrant_)) );  
        }
        else
        {
            nSubBoid_.erase ( nSubBoid_.begin() + boidIndex );
            boidIndex -= 1;
        } 
    }
}

void quadrant::boidMover ( int boidIndex, int quadIndex, int newQuadIndex )
{
    grid_[newQuadIndex].nSubBoid_.push_back ( grid_[quadIndex].nSubBoid_[boidIndex] );
    grid_[quadIndex].nSubBoid_.erase ( grid_[quadIndex].nSubBoid_.begin ()+boidIndex );
}