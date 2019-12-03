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

/*void quadrant::tresPass ()          //Logic based on a bounded 2D space (alias with walls)
{
    for ( int boidIndex=0; boidIndex<nSubBoidSize_; boidIndex++ )
    {
            cout<< nSubBoidSize_<< endl;
        if ( nSubBoid_[boidIndex].getbelongIndex () == quadIndex_ )
        {
            if ( nSubBoid_[boidIndex].getx () < xQuadMin_+boid::boidRadius_ ) 
            {
                if ( nSubBoid_[boidIndex].getinfluencexIndex () != quadIndex_-1 ) boidxMover ( boidIndex, quadIndex_, (quadIndex_-1) );
                if ( nSubBoid_[boidIndex].getx () < xQuadMin_ )                   boidDeleter ( boidIndex, quadIndex_, (quadIndex_-1) );
            }
            if ( nSubBoid_[boidIndex].getx () > xQuadMax_-boid::boidRadius_ ) 
            {
                if ( nSubBoid_[boidIndex].getinfluencexIndex () != quadIndex_+1 ) boidxMover ( boidIndex, quadIndex_, (quadIndex_+1) );
                if ( nSubBoid_[boidIndex].getx () > xQuadMax_ )                   boidDeleter ( boidIndex, quadIndex_, (quadIndex_+1) );
            }
            if ( nSubBoid_[boidIndex].gety () < yQuadMin_+boid::boidRadius_ ) 
            {
                if ( nSubBoid_[boidIndex].getinfluenceyIndex () != quadIndex_-sqrt(nQuadrant_) ) boidyMover ( boidIndex, quadIndex_, (quadIndex_-sqrt(nQuadrant_)) );
                if ( nSubBoid_[boidIndex].gety () < yQuadMin_ )                                  boidDeleter ( boidIndex, quadIndex_, (quadIndex_-sqrt(nQuadrant_)) ); 
            }
            if ( nSubBoid_[boidIndex].getx () > yQuadMax_-boid::boidRadius_ ) 
            {
                if ( nSubBoid_[boidIndex].getinfluenceyIndex () != quadIndex_+sqrt(nQuadrant_) ) boidyMover ( boidIndex, quadIndex_, (quadIndex_+sqrt(nQuadrant_)) );
                if ( nSubBoid_[boidIndex].gety () > yQuadMax_ )                                  boidDeleter ( boidIndex, quadIndex_, (quadIndex_+sqrt(nQuadrant_)) ); 
            }
        }
    }
    nSubBoidSize_=nSubBoid_.size();
}
void quadrant::boidxMover ( int boidIndex, int quadIndex, int newQuadIndex )
{
    grid_[newQuadIndex].nSubBoid_.push_back ( grid_[quadIndex].nSubBoid_[boidIndex] );
    grid_[newQuadIndex].nSubBoid_[boidIndex].setinfluencexIndex ( newQuadIndex );
}
void quadrant::boidyMover ( int boidIndex, int quadIndex, int newQuadIndex )
{
    grid_[newQuadIndex].nSubBoid_.push_back ( grid_[quadIndex].nSubBoid_[boidIndex] );
    grid_[newQuadIndex].nSubBoid_[boidIndex].setinfluenceyIndex ( newQuadIndex );
}
void quadrant::boidDeleter ( int boidIndex, int quadIndex, int newQuadIndex )
{
    grid_[quadIndex].nSubBoid_[boidIndex].setbelongIndex ( newQuadIndex );
    grid_[quadIndex].nSubBoid_.erase ( grid_[quadIndex].nSubBoid_.begin ()+boidIndex );
}*/

void quadrant::ObstaclePlacer ()
{
    for ( int i=0; i<Walls_.size(); i++)
    { 
        if (xOrigin_-quadrantWidth_ < Walls_[i].getxOrigin () && Walls_[i].getxOrigin () < xOrigin_+quadrantWidth_ 
        &&  yOrigin_-quadrantWidth_ < Walls_[i].getyOrigin () && Walls_[i].getyOrigin () < yOrigin_+quadrantWidth_)
        {
            subObstacles_.reserve (1);
            subObstacles_.push_back ( Walls_[i] );
            //Walls_.erase ( Walls_.begin ()+i );
            // i-=1;
        }
    }
}
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  Walls Collisions  -+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

/*void wallCollision ( vector<boid> &nBoid )
{
    for ( int boidIndex=0; boidIndex<nBoid.size(); boidIndex++)
    {
        double distancex_ = xMax_-abs(nBoid[boidIndex].getx ());
        double distancey_ = yMax_-abs(nBoid[boidIndex].gety ()); 

        if ( distancex_ < boid::boidRadius_ || distancey_ < boid::boidRadius_ )
        {
            Updates_ +=1;
            if ( abs(nBoid[boidIndex].getx ()) > 1-boid::boidRadius_ )
            {
                nBoid[boidIndex].setxV ( -nBoid[boidIndex].getxV () );
            }   
            if ( abs(nBoid[boidIndex].gety ()) > 1-boid::boidRadius_ )
            {
                nBoid[boidIndex].setyV ( -nBoid[boidIndex].getyV () );
            } 
        }
    }
}*/

void wallCollision ( vector<int> &nBoid )
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
    
}

int obstacleCollision ( vector<int> &nBoid, vector<obstacle> &wall)
{
    if(wall.size() == 0)
    {  
        return -1;
    }
    double wallRadius = wall[0].getRadius ();
    double wWidth_ = wall[0].getWidth ();
    double distancex_, distancey_;
    double xClamp_, yClamp_;
    double xP_, yP_;

    for(int i = 0; i<nBoid.size(); i++)
    {
        for (int j = 0; j<wall.size(); j++)
        {
            distancex_ = wall[j].getxOrigin()-(nBoid_[nBoid[i]].getx ());
            distancey_ = wall[j].getyOrigin()-(nBoid_[nBoid[i]].gety ()); 
            //cout <<wradius<<endl;
            if ( abs(distancex_) < (boid::boidRadius_ + wallRadius)  && abs(distancey_) < (boid::boidRadius_ + wallRadius) )
            {
                xClamp_ = clamp ( distancex_, -wWidth_ , wWidth_ ); 
                yClamp_ = clamp ( distancey_, -wWidth_ , wWidth_ ); 
                xP_ = wall[j].getxOrigin() + xClamp_; 
                yP_ = wall[j].getyOrigin() + yClamp_;
                
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
/*int obstacleCollision(vector<boid> &boid, vector<obstacle> w)
{
    if(w.size() == 0)
    {  
        return -1;
    }
    double wradius = w[0].getRadius ();
    double wWidth_ = w[0].getWidth ();
    double distancex_, distancey_;
    double xClamp_, yClamp_;
    double xP_, yP_;

    for(int i = 0; i<boid.size(); i++)
    {
        for (int j = 0; j<w.size(); j++)
        {
            distancex_ = w[j].getxOrigin()-(boid[i].getx ());
            distancey_ = w[j].getyOrigin()-(boid[i].gety ()); 
            //cout <<wradius<<endl;
            if ( abs(distancex_) < (boid::boidRadius_ + wradius)  && abs(distancey_) < (boid::boidRadius_ + wradius) )
            {
                xClamp_ = clamp ( distancex_, -wWidth_ , wWidth_ ); 
                yClamp_ = clamp ( distancey_, -wWidth_ , wWidth_ ); 
                //cout<<"entrato"<<i<<endl;
                xP_ = w[j].getxOrigin() + xClamp_; 
                yP_ = w[j].getyOrigin() + yClamp_;
                
                if ( abs(boid[i].getx()-(xP_))<abs(boid[i].gety()-(yP_)) )
                {
                    boid[i].setyV(-boid[i].getyV());
                }
                else boid[i].setxV(-boid[i].getxV());
            }
        }
    }
    return 0;
}*/


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