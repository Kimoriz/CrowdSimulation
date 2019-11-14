#include "obstacle.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  GRID -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class quadrant 
{
    public:

    quadrant ( double xOrigin, double yOrigin );

    void boidPlacer ();
    void wallPlacer ();

    vector <boid> nSubBoid_;
    vector <obstacle> subWall_;

    private:

    double xOrigin_, yOrigin_;
    double quadrantWidth_;
    
};

vector<quadrant> grid_;

int nQuadrant_ = 9;

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //