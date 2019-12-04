#include "boid.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class obstacle
{
    public: 

    obstacle ();
    obstacle ( double , double , double , double, int );

    double getxOrigin ();
    double getyOrigin ();
    double getRadius ();
    double getWidth ();
    double getHeight ();
    int getIndex ();

    private:

    int obsIndex_;
    double xOrigin_, yOrigin_, Radius_;
    double height_;
    double width_;
};

vector <obstacle> Walls_;
vector <obstacle>::iterator It_Obs;


double clamp(double, double, double);


void genObstacles ();

void drawObstacles ();

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //
