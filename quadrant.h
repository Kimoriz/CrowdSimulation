#include "obstacle.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  GRID -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class quadrant 
{

    public:

    static int quadCounter_;

    quadrant ( double xOrigin, double yOrigin );

    void boidPlacer ();

    void obstaclePlacer ();

    //vector <boid> nSubBoid_;
    vector <int> nSubBoid_;
    vector <obstacle> subObstacles_;
    
    //void wallCollision ( vector<boid> &boid);
    void wallCollision ( vector<int> &boid);
    
    //int obstacleCollision ( vector<boid> &boid, vector<obstacle> w );      //boid vs walls
    int obstacleCollision ( vector<int> &boid, vector<obstacle> w );      //boid vs walls

    void tresPass ();
    void boidMover ( int boidIndex, int quadIndex, int newQuadIndex );

    void boidxMover ( int boidIndex, int quadIndex, int newQuadIndex );
    void boidyMover ( int boidIndex, int quadIndex, int newQuadIndex );
    void boidDeleter ( int boidIndex, int quadIndex, int newQuadIndex );
    int nSubBoidSize_;
    void ObstaclePlacer ();

    private:

    double xOrigin_, yOrigin_;
    double xQuadMin_, xQuadMax_;
    double yQuadMin_, yQuadMax_;
    int quadIndex_;

};

int nQuadrant_ = 100;
double quadrantWidth_;

vector<quadrant> grid_;
void genGrid ();

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-  Walls  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //
//Actually walls do not need to be generated 

//double nWallGen_ = 200;
//double wallRadius_;

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //
