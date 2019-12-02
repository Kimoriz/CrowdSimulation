#include "boid.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  OBSTACLE CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class obstacle
{
    public: 

    obstacle ();
    obstacle ( double xOrigin, double yOrigin, double width, double height );

    double getxOrigin ();
    double getyOrigin ();
    double getRadius ();
    double getWidth ();
    double getHeight ();

    private:

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
