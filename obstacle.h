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

    void obstaclePlacer ();

    private:

    double xOrigin_, yOrigin_, Radius_;
};

vector <obstacle> Obstacles_;
vector <obstacle>::iterator It_Obs;

void genObstacles ();

void drawObstacles ();

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //