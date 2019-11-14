#include "vettore.cpp"

using namespace std;

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

    void setx ( double x );
    void sety ( double y );
    
    void setxV    ( double xV );
    void setyV    ( double yV );
    void setModV  ( double modV_ );

    void setxA ( double xA );
    void setyA ( double yA );

    void setxGoal ( double xGoal );
    void setyGoal ( double yGoal );

    void updatex ( double dt );
    void updatey ( double dt );

    void updatexV   ( double dt );
    void updateyV   ( double dt );

    void collision ( vector<boid> copynBoid_ );
    
    static double boidRadius_;

    private:   

    double  x_,  y_;
    double  xV_, yV_;
    double  modV_;
    double  xA_, yA_;
    double  xGoal_, yGoal_;
};

int nBoids_;

vector<boid> nBoid_;
vector<boid>::iterator It_;
vector <double> boidPositions_;

void boidBody ();

void renderBoid ();
int boidList_;

void drawBoid ( boid nBoid );

void genBoid ( int nBoid ); 

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ //

void goalGiver ( boid &Guest, double xGoal, double yGoal );

void goalReacher ( boid Guest );  

void mindRefresher ( boid &Guest );

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-  To-be-analysed params -+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-+ //

int Updates_ = 0;
int nCollision_ = 0;


















































// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+-+-  Colors Data  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-++-+-+-+-+-+-+ //

const int nColors_ = 152;
double Palette_ [nColors_][3] 
{ 
    {255.0/255.0,250.0/255.0,250/255.0},   //1 Snow                  
    {238.0/255.0,233.0/255.0,233/255.0},   //2 Snow 2 	              
    {205.0/255.0,201.0/255.0,201/255.0},   //3 Snow 3 	              
    {139.0/255.0,137.0/255.0,137/255.0},   //4 Snow 4 	              
    {248.0/255.0,248.0/255.0,255/255.0},   //5 Ghost White           
    {245.0/255.0,245.0/255.0,245/255.0},   //6 White Smoke           
    {220.0/255.0,220.0/255.0,220/255.0},   //7 Gainsboro 	          
    {255.0/255.0,250.0/255.0,240/255.0},   //8 Floral White          
    {253.0/255.0,245.0/255.0,230/255.0},   //9 Old Lace 	          
    {240.0/255.0,240.0/255.0,230/255.0},   //10 Linen                
    {250.0/255.0,235.0/255.0,215/255.0},   //11 Antique White 	      
    {238.0/255.0,223.0/255.0,204/255.0},   //12 Antique White 2 	  
    {205.0/255.0,192.0/255.0,176/255.0},   //13 Antique White 3 	  
    {139.0/255.0,131.0/255.0,120/255.0},   //14 Antique White 4 	  
    {255.0/255.0,239.0/255.0,213/255.0},   //15 Papaya Whip          
    {255.0/255.0,235.0/255.0,205/255.0},   //16 Blanched Almond 	  
    {255.0/255.0,228.0/255.0,196/255.0},   //17 Bisque 	          
    {238.0/255.0,213.0/255.0,183/255.0},   //18 Bisque 2 	          
    {205.0/255.0,183.0/255.0,158/255.0},   //19 Bisque 3 	          
    {139.0/255.0,125.0/255.0,107/255.0},   //20 Bisque 4 	          
    {255.0/255.0,218.0/255.0,185/255.0},   //21 Peach Puff           
    {238.0/255.0,203.0/255.0,173/255.0},   //22 Peach Puff 2         
    {205.0/255.0,175.0/255.0,149/255.0},   //23 Peach Puff 3         
    {139.0/255.0,119.0/255.0,101/255.0},   //24 Peach Puff 4         
    {255.0/255.0,222.0/255.0,173/255.0},   //25 Navajo White 	      
    {255.0/255.0,228.0/255.0,181/255.0},   //26 Moccasin             
    {255.0/255.0,248.0/255.0,220/255.0},   //27 Cornsilk             
    {238.0/255.0,232.0/255.0,205/255.0},   //28 Cornsilk 2           
    {205.0/255.0,200.0/255.0,177/255.0},   //29 Cornsilk 3           
    {139.0/255.0,136.0/255.0,120/255.0},   //30 Cornsilk 4           
    {255.0/255.0,255.0/255.0,240/255.0},   //31 Ivory                
    {238.0/255.0,238.0/255.0,224/255.0},   //32 Ivory 2 	          
    {205.0/255.0,205.0/255.0,193/255.0},   //33 Ivory 3 	          
    {139.0/255.0,139.0/255.0,131/255.0},   //34 Ivory 4 	          
    {255.0/255.0,250.0/255.0,205/255.0},   //35 Lemon Chiffon 	      
    {255.0/255.0,245.0/255.0,238/255.0},   //36 Seashell 	          
    {238.0/255.0,229.0/255.0,222/255.0},   //37 Seashell 2           
    {205.0/255.0,197.0/255.0,191/255.0},   //38 Seashell 3           
    {139.0/255.0,134.0/255.0,130/255.0},   //39 Seashell 4           
    {240.0/255.0,255.0/255.0,240/255.0},   //40 Honeydew             
    {244.0/255.0,238.0/255.0,224/255.0},   //41 Honeydew 2           
    {193.0/255.0,205.0/255.0,193/255.0},   //42 Honeydew 3           
    {131.0/255.0,139.0/255.0,131/255.0},   //43 Honeydew 4           
    {245.0/255.0,255.0/255.0,250/255.0},   //44 Mint Cream           
    {240.0/255.0,255.0/255.0,255/255.0},   //45 Azure 	              
    {240.0/255.0,248.0/255.0,255/255.0},   //46 Alice Blue           
    {230.0/255.0,230.0/255.0,250/255.0},   //47 Lavender 	          
    {255.0/255.0,240.0/255.0,245/255.0},   //48 Lavender Blush       
    {255.0/255.0,228.0/255.0,225/255.0},   //49 Misty Rose           
    {255.0/255.0,255.0/255.0,255/255.0},   //50 White
    {  0.0/255.0,  0.0/255.0,  0/255.0},   //51 Black
    { 49.0/255.0, 79.0/255.0,  7/255.0},   //52 Dark Slate Gray
    {105.0/255.0,105.0/255.0,105/255.0},   //53 Dim Gray             
    {112.0/255.0,138.0/255.0,144/255.0},   //54 Slate Gray
    {119.0/255.0,136.0/255.0,153/255.0},   //55 Light Slate Gray     
    {190.0/255.0,190.0/255.0,190/255.0},   //56 Gray               
    {211.0/255.0,211.0/255.0,211/255.0},   //57 Light Gray 	      
    { 25.0/255.0, 25.0/255.0,112/255.0},   //58 Midnight Blue        
    {  0.0/255.0,  0.0/255.0,128/255.0},   //59 Navy                 
    {100.0/255.0,149.0/255.0,237/255.0},   //60 Cornflower Blue      
    { 72.0/255.0, 61.0/255.0,139/255.0},   //61 Dark Slate Blue      
    {106.0/255.0, 90.0/255.0,205/255.0},   //62 Slate Blue           
    {123.0/255.0,104.0/255.0,238/255.0},   //63 Medium Slate Blue    
    {132.0/255.0,112.0/255.0,255/255.0},   //64 Light Slate Blue     
    {  0.0/255.0,  0.0/255.0,205/255.0},   //65 Medium Blue          
    { 65.0/255.0,105.0/255.0,225/255.0},   //66 Royal Blue           
    {  0.0/255.0,  0.0/255.0,255/255.0},   //67 Blue                 
    { 30.0/255.0,144.0/255.0,255/255.0},   //68 Dodger Blue          
    {  0.0/255.0,191.0/255.0,255/255.0},   //69 Deep Sky Blue        
    {135.0/255.0,206.0/255.0,250/255.0},   //70 Sky Blue             
    {134.0/255.0,206.0/255.0,250/255.0},   //71 Light Sky Blue       
    { 70.0/255.0,130.0/255.0,180/255.0},   //72 Steel Blue           
    {176.0/255.0,196.0/255.0,222/255.0},   //73 Light Steel Blue     
    {173.0/255.0,216.0/255.0,230/255.0},   //74 Light Blue           
    {176.0/255.0,224.0/255.0,230/255.0},   //75 Powder Blue          
    {175.0/255.0,238.0/255.0,238/255.0},   //76 Pale Turquoise       
    {  0.0/255.0,206.0/255.0,209/255.0},   //77 Dark Turquoise       
    { 72.0/255.0,209.0/255.0,204/255.0},   //78 Medium Turquoise     
    { 64.0/255.0,224.0/255.0,208/255.0},   //79 Turquoise            
    {  0.0/255.0,255.0/255.0,255/255.0},   //80 Cyan                 
    {224.0/255.0,255.0/255.0,255/255.0},   //81 Light Cyan           
    { 95.0/255.0,158.0/255.0,160/255.0},   //82 Cadet Blue           
    {102.0/255.0,205.0/255.0,170/255.0},   //83 Medium Aquamarine    
    {127.0/255.0,255.0/255.0,212/255.0},   //84 Aquamarine           
    {  0.0/255.0,100.0/255.0,  0/255.0},   //85 Dark Green           
    { 85.0/255.0,107.0/255.0, 47/255.0},   //86 Dark Olive Green     
    {143.0/255.0,188.0/255.0,143/255.0},   //87 Dark Sea Green       
    { 46.0/255.0,139.0/255.0, 87/255.0},   //88 Sea Green            
    { 60.0/255.0,179.0/255.0,113/255.0},   //89 Medium Sea Green     
    { 32.0/255.0,178.0/255.0,170/255.0},   //90 Light Sea Green      
    {152.0/255.0,251.0/255.0,152/255.0},   //91 Pale Green           
    {  0.0/255.0,255.0/255.0,127/255.0},   //92 Spring Green         
    {124.0/255.0,252.0/255.0,  0/255.0},   //93 Lawn Green           
    {127.0/255.0,255.0/255.0,  0/255.0},   //94 Chartreuse           
    {  0.0/255.0,250.0/255.0,154/255.0},   //95 Medium Spring Green  
    {173.0/255.0,255.0/255.0, 47/255.0},   //96 Green Yellow         
    { 50.0/255.0,205.0/255.0, 50/255.0},   //97 Lime Green           
    {154.0/255.0,205.0/255.0, 50/255.0},   //98 Yellow Green         
    { 34.0/255.0,139.0/255.0, 34/255.0},   //99 Forest Green         
    {107.0/255.0,142.0/255.0, 35/255.0},   //100 Olive Drab          
    {189.0/255.0,183.0/255.0,107/255.0},   //1 Dark Khaki            
    {240.0/255.0,230.0/255.0,140/255.0},   //2 Khaki                 
    {238.0/255.0,232.0/255.0,170/255.0},   //3 Pale Goldenrod        
    {250.0/255.0,250.0/255.0,210/255.0},   //4 Light Goldenrod Yellow
    {255.0/255.0,255.0/255.0,224/255.0},   //5 Light Yellow          
    {255.0/255.0,255.0/255.0,  0/255.0},   //6 Yellow                
    {255.0/255.0,215.0/255.0,  0/255.0},   //7 Gold                  
    {238.0/255.0,221.0/255.0,130/255.0},   //8 Light Goldenrod       
    {218.0/255.0,165.0/255.0, 32/255.0},   //9 Goldenrod             
    {184.0/255.0,134.0/255.0, 11/255.0},   //10 Dark Goldenrod       
    {188.0/255.0,143.0/255.0,143/255.0},   //11 Rosy Brown           
    {205.0/255.0, 92.0/255.0, 92/255.0},   //12 Indian Red           
    {139.0/255.0, 69.0/255.0, 19/255.0},   //13 Saddle Brown         
    {160.0/255.0, 82.0/255.0, 45/255.0},   //14 Sienna               
    {205.0/255.0,133.0/255.0, 63/255.0},   //15 Peru                 
    {222.0/255.0,184.0/255.0,135/255.0},   //16 Burlywood            
    {245.0/255.0,245.0/255.0,220/255.0},   //17 Beige                
    {245.0/255.0,222.0/255.0,179/255.0},   //18 Wheat                
    {244.0/255.0,164.0/255.0, 96/255.0},   //19 Sandy Brown          
    {210.0/255.0,180.0/255.0,140/255.0},   //20 Tan                  
    {210.0/255.0,105.0/255.0, 30/255.0},   //21 Chocolate            
    {178.0/255.0, 34.0/255.0, 34/255.0},   //22 Firebrick            
    {165.0/255.0, 42.0/255.0, 42/255.0},   //23 Brown                
    {233.0/255.0,150.0/255.0,122/255.0},   //24 Dark Salmon          
    {250.0/255.0,128.0/255.0,114/255.0},   //25 Salmon               
    {255.0/255.0,160.0/255.0,122/255.0},   //26 Light Salmon         
    {255.0/255.0,165.0/255.0,  0/255.0},   //27 Orange               
    {255.0/255.0,140.0/255.0,  0/255.0},   //28 Dark Orange          
    {255.0/255.0,127.0/255.0, 80/255.0},   //29 Coral                
    {240.0/255.0,128.0/255.0,128/255.0},   //30 Light Coral          
    {255.0/255.0, 99.0/255.0, 71/255.0},   //31 Tomato               
    {255.0/255.0, 69.0/255.0,  0/255.0},   //32 Orange Red           
    {255.0/255.0,  0.0/255.0,  0/255.0},   //33 Red                  
    {255.0/255.0,105.0/255.0,180/255.0},   //34 Hot Pink             
    {255.0/255.0, 20.0/255.0,147/255.0},   //35 Deep Pink            
    {255.0/255.0,192.0/255.0,203/255.0},   //36 Pink                 
    {255.0/255.0,182.0/255.0,193/255.0},   //37 Light Pink           
    {219.0/255.0,112.0/255.0,147/255.0},   //38 Pale Violet Red      
    {176.0/255.0, 48.0/255.0, 96/255.0},   //39 Maroon               
    {199.0/255.0, 21.0/255.0,133/255.0},   //40 Medium Violet Red    
    {208.0/255.0, 32.0/255.0,144/255.0},   //41 Violet Red           
    {238.0/255.0,130.0/255.0,238/255.0},   //42 Violet               
    {221.0/255.0,160.0/255.0,221/255.0},   //43 Plum                 
    {218.0/255.0,112.0/255.0,214/255.0},   //44 Orchid               
    {186.0/255.0, 85.0/255.0,211/255.0},   //45 Medium Orchid        
    {153.0/255.0, 50.0/255.0,204/255.0},   //46 Dark Orchid          
    {148.0/255.0,  0.0/255.0,211/255.0},   //47 Dark Violet          
    {138.0/255.0, 43.0/255.0,226/255.0},   //48 Blue Violet          
    {160.0/255.0, 32.0/255.0,240/255.0},   //49 Purple               
    {147.0/255.0,112.0/255.0,219/255.0},   //50 Medium Purple        
    {216.0/255.0,191.0/255.0,216/255.0},   //51 Thistle              
    {210.0/255.0,  31.0/255.0,27/255.0},   //52 Rosso pompeiano      
};

