#include "obstacle.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  GRID -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class boid;

class quadrant 
{

    public:

    static int quadCounter_;
    quadrant ( double xOrigin, double yOrigin );

    void boidPlacer ();
    void boidReplacer ( int boidIndex, int quadIndex );

    void obstaclePlacer ();

    vector <boid> nSubBoid_;
    vector <obstacle> subObstacles_;
    
    void wallCollision ( vector<boid> &boid);

    void tresPass ();
    void boidMover ( int boidIndex, int quadIndex, int newQuadIndex );

    private:

    double xOrigin_, yOrigin_;
    double xQuadMin_, xQuadMax_;
    double yQuadMin_, yQuadMax_;
    int quadIndex_;
};

int nQuadrant_ = 16;
double quadrantWidth_;

vector<quadrant> grid_;
void genGrid ();

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  Walls  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //
//Actually walls do not need to be generated 

//double nWallGen_ = 200;
//double wallRadius_;

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //