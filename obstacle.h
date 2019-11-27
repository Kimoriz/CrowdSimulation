#include "boid.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class obstacle
{
    public: 

    obstacle ();
    obstacle ( double xOrigin, double yOrigin, double Radius );

    double getxOrigin ();
    double getyOrigin ();
    double getRadius ();
    
    private:

    double xOrigin_, yOrigin_, Radius_;
};

vector <obstacle> Walls_;
vector <obstacle>::iterator It_Obs;

void genObstacles ();

void drawObstacles ();

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //
