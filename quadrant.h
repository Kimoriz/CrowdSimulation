#include "obstacle.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  GRID -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class quadrant 
{
    public:

    quadrant quadrant ( double xOrigin, double yOrigin );

    void boidPlacer ();
    void wallPlacer ();

    private:

    double xOrigin_, yOrigin_;
    double quadrantWidth_;
    
    vector <boid> nSubBoid_;
    vector <obstacle> subWall_;
};

int nQuadrant_ = 9;

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //