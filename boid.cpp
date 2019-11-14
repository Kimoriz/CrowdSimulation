#include "boid.h"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+  Pre-existing Variables  -+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //
//                                  Necessary for Opengl function that do not have arguments

void WindowSets ( int argc, char **argv)
{
    argc_ = argc;
    argv_ = argv;

    xBegin_= 0, yBegin_ = 0;
    Width_ = 1000, Height_ = 1000;

    xMin_ = -1., xMax_ = 1.;        //(-1,1)
    yMin_ = xMin_, yMax_ = xMax_;   //The frame must be square to generate Walls more easily
    xRange_ = xMax_-xMin_;
    yRange_ = yMax_-yMin_;
    xStep_ = xRange_/Width_;
    yStep_ = yRange_/Height_;

    capxV_ = 1., capyV_ = 1.; 
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+  BOID CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

double boid::boidRadius_ = 0.02;
int boid::nBoidCounter_ = 0;

boid::boid() 
{   
    if ( nBoidCounter_ == 0 )
    {
        if((rand()%2)==1)                            //Randomizer x's and y's
            { x_  =  ( 1-((float)(rand()%100))/500.); }
        else  
            { x_  = -( 1-((float)(rand()%100))/500.); }
        if((rand()%2)==1)
            { y_  =  ( 1-((float)(rand()%100))/500.); }
        else  
            { y_  = -( 1-((float)(rand()%100))/500.); }
        //y_  =  ( -0.5-((float)(rand()%100))/200.);
    }

    for ( int i =0; i<(nBoidCounter_*2); i+=2)
    {
        if (i==0)
        {
            if((rand()%2)==1)                               //Randomizer x's and y's
                { x_  =  ( 1-((float)(rand()%100))/100.); }
            else  
                { x_  = -( 1-((float)(rand()%100))/100.); }
            if((rand()%2)==1)
                { y_  =  ( 1-((float)(rand()%100))/100.); }
            else  
                { y_  = -( 1-((float)(rand()%100))/100.); }
            //y_  = ( -0.5-((float)(rand()%100))/200.);

        }
        if ( sqrt( (x_-boidPositions_[i])  *(x_-boidPositions_[i]) + 
                   (y_-boidPositions_[i+1])*(y_-boidPositions_[i+1]))  < (2*boidRadius_) )
                   {
                       i = -2; 
                   }  
        if (  abs(x_) > (1-boidRadius_) || abs(y_) > (1-boidRadius_) ) {i = -2;}  
    }

    if((rand()%2)==1)                                       //Randomizer Vx's & Vy's
        { xV_  =  ( (float)(rand()%100))/100.; }  
    else  
        { xV_  = -( (float)(rand()%100))/100.; }
    
    if((rand()%2)==1)
        { yV_  =  ( (float)(rand()%100))/100.; }
    else  
        { yV_  = -( (float)(rand()%100))/100.; }

    //xV_ = 0.;
    //yV_ = 0.;

    xGoal_ = xV_;
    yGoal_ = yV_;

    modV_  = sqrt ( (pow (xV_, 2 ) + pow ( yV_, 2 )) ); 

    xA_ = 0;
    yA_ = 0;

    boidPositions_.push_back(x_);
    boidPositions_.push_back(y_);
    nBoidCounter_ += 1;
}
    
double boid::getx () { return x_; }
double boid::gety () { return y_; }

double boid::getxV   () { return   xV_; }
double boid::getyV   () { return   yV_; }
double boid::getModV () { return modV_; }

double boid::getxA () { return xA_; }
double boid::getyA () { return yA_; }

double boid::getxGoal () { return xGoal_; }
double boid::getyGoal () { return yGoal_; }

void boid::setx ( double x ) { x_ =  x; }
void boid::sety ( double y ) { y_ =  y; }

void boid::setxV    ( double xV )     { xV_ = xV; }
void boid::setyV    ( double yV )     { yV_ = yV; }
void boid::setModV ( double modV) { modV_ = modV; }

void boid::setxA ( double xA ) { xA_ = xA; }
void boid::setyA ( double yA ) { yA_ = yA; }

void boid::setxGoal ( double xGoal ) { xGoal_ = xGoal; } 
void boid::setyGoal ( double yGoal ) { yGoal_ = yGoal; }


void boid::updatex ( double dt )
{   
    x_ = x_ + (xV_*dt) + (xA_*dt*dt)/2;

         if ( x_<xMin_ ) { x_ = x_+xRange_; }
    else if ( x_>xMax_ ) { x_ = x_-xRange_; }
}

void boid::updatey ( double dt )
{   
    y_ = y_ + (yV_*dt) + (yA_*dt*dt)/2;

         if ( y_<yMin_ ) { y_ = y_+yRange_; }
    else if ( y_>yMax_ ) { y_ = y_-yRange_; }
}

void boid::updatexV ( double dt)
{   
    if ( xV_ >  capxV_ ) { xV_ =  capxV_; }
    if ( xV_ < -capxV_ ) { xV_ = -capxV_; }
    else xV_ = xV_ + dt*xA_;
}

void boid::updateyV ( double dt)
{
    if ( xV_ >  capxV_ ) { xV_ =  capxV_; }
    if ( xV_ < -capxV_ ) { xV_ = -capxV_; }
    else xV_ = xV_ + dt*xA_;;
}

void boidBody()
{
    glBegin ( GL_POLYGON );
    for(int i=0; i<20; i++)
    {
        double p=M_PI/10;
        glVertex2d ( boid::boidRadius_*cos(i*p),  boid::boidRadius_*sin(i*p) );
    }
    glEnd ();
}

void renderBoid ()
{   
    boidList_ = glGenLists ( 1 );
    glNewList ( boidList_, GL_COMPILE );
    boidBody ();
    glEndList ();
}

void genBoid ( int nBoids )
{   
    nBoids_ = nBoids;
    nBoid_.resize ( nBoids_ );
    //for ( int i=0; i<nBoids_; i++)
    //{
    //    if ( (rand()%2) == 1 ) { goalGiver ( nBoid_[i], 0.8, 0.8); }
    //    else { goalGiver ( nBoid_[i], -0.8, 0.8); }
    //}
}

void drawBoid ( boid nBoid )
{
    double colorinoB = ( sqrt (nBoid.getxV () * nBoid.getyV () + nBoid.getyV () * nBoid.getyV () ) / sqrt(2) );
    glColor3d (colorinoB, 0., 0. );
    glPushMatrix ();
    glTranslatef ( nBoid.getx(), nBoid.gety(), 0 );
    glCallList ( boidList_ );
    glPopMatrix ();
}


// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

void boid::collision ( vector<boid> copynBoid_ )
{
    double d;
    vettore cong;
    for(int i=0; i<copynBoid_.size (); i++)
    {
        d=sqrt( (this->getx ()-copynBoid_[i].getx ())*(this->getx () -copynBoid_[i].getx ()) 
               +(this->gety ()-copynBoid_[i].gety ())*(this->gety () -copynBoid_[i].gety ()) );
        if(d<=(2*boid::boidRadius_) && d!=0)
        {    
            Updates_ +=1; 
            nCollision_ += 1;      
            
            vettore r_1 ( this->getx (), this->gety ());
            vettore r_2 ( copynBoid_[i].getx (), copynBoid_[i].gety ());
            vettore v_1 ( this->getxV (), this->getyV ());
            vettore v_2 ( copynBoid_[i].getxV (), copynBoid_[i].getyV ());
            cong=r_2-r_1;
            cong=cong.get_versor ();
            vettore norm=cong.get_normal ();

            double mod_v1n=cong*v_1;        //dot product
            double mod_v2n=cong*v_2;
            double mod_v1tg=norm*v_1;
            double mod_v2tg=norm*v_2;
            
            vettore v_1n,v_2n,v_1tg,v_2tg;
            
            v_1n = mod_v1n * cong;
            v_1tg = mod_v1tg * norm;

            v_2n = mod_v2n * cong;
            v_2tg = mod_v2tg * norm;    

            vettore v_1new=v_2n+v_1tg;
            vettore v_2new=v_1n+v_2tg;

            this->setxV(v_1new.componenti[0]);
            this->setyV(v_1new.componenti[1]);            
        }
    }
}


void goalGiver ( boid &Guest, double xGoal, double yGoal )
{
    Updates_ +=1;
    Guest.setxGoal ( xGoal );
    Guest.setyGoal ( yGoal );
}

void goalReacher ( boid Guest )
{
    Updates_ +=1;
    double distance = sqrt( ( Guest.getx () -Guest.getxGoal ())*(Guest.getx () -Guest.getxGoal()) +
                            ( Guest.gety () -Guest.getyGoal ())*(Guest.gety () -Guest.getyGoal()) ); 
    
    if ( distance < 0.05 )
    {
            nBoid_.erase ( It_b );
            nBoids_ -= 1;
    }
}

void mindRefresher ( boid &Guest )
{
    Updates_ +=1;
    vettore distance_ ( (Guest.getxGoal()-Guest.getx ()), (Guest.getyGoal()-Guest.gety ()) );   //constructor with components
    vettore normal_ = distance_.get_versor ();

    Guest.setxV ( normal_.componenti[0] );
    Guest.setyV ( normal_.componenti[1] );
}
