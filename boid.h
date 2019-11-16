# include "vettore.cpp"

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+  Pre-existing Variables  -+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //
//                                  Necessary for Opengl function that do not have arguments

int argc_;
char ** argv_;

int xBegin_, yBegin_;
int Width_, Height_;

double xMin_, xMax_;        //(-1,1)
double yMin_, yMax_;        //(-1,1)
double xRange_, yRange_;
double xStep_, yStep_;

double capxV_, capyV_;      //(1,1)

void WindowSets ( int argc, char **argv );

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+  BOID CLASS  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

class boid
{   
    public:

    static int nBoidCounter_;

    boid ();                //redefinition of deafult costructor
    //~boid();              //destructor (useful ?)
    
    double getx ();
    double gety ();

    double getxV ();
    double getyV ();
    double getModV ();

    double getxA ();
    double getyA ();

    double getxGoal ();
    double getyGoal ();

    //double getbelongIndex ();
    //double getinfluencexIndex ();
    //double getinfluenceyIndex ();

    void setx ( double x );
    void sety ( double y );
    
    void setxV    ( double xV );
    void setyV    ( double yV );
    void setModV  ( double modV_ );

    void setxA ( double xA );
    void setyA ( double yA );

    void setxGoal ( double xGoal );
    void setyGoal ( double yGoal );

    //void setbelongIndex ( int belongIndex );
    //void setinfluencexIndex ( int influencexIndex );
    //void setinfluenceyIndex ( int influenceyIndex );

    void updatex ( double dt );
    void updatey ( double dt );

    void updatexV   ( double dt );
    void updateyV   ( double dt );

    void collision ( vector <boid> copynBoid );
    
    static double boidRadius_;

    private:   

    double  x_,  y_;
    double  xV_, yV_;
    double  modV_;
    double  xA_, yA_;
    double  xGoal_, yGoal_;


    int belongIndex_, influencexIndex_, influenceyIndex_;
};

int nBoids_;

vector <boid> nBoid_;
vector <boid>::iterator It_b;
vector <double> boidPositions_;

void genBoid ();

void boidBody ();

void renderBoid ();
int boidList_;

int boidDrawn_ = 0;
void drawBoid ( boid nBoid ); 

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+  BOID FUNCTION  +-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

void goalGiver ( boid &Guest, double xGoal, double yGoal ); 

void mindRefresher ( boid &Guest );

void goalReacher ( vector<boid> &nSubBoid ); 

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //