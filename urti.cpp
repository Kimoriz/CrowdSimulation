#include "urti.h"
/*
urti::urti(){}

urti::urti(double time, double creation, int id1, int id2)
{
    time_0=creation;
    tau=time;
    id_1=id1;
    id_2=id2;
}*/

int urtoni(vector<int> gridboids, vector<int> copynboid, vector<int> walls, int gird, double &tau)
{
    double t,x,v;
    vettore cong;
    double pos1x,pos2x,pos1y,pos2y;
    double xClamp_, yClamp_;
    double xP_, yP_;
    double wWidth_ = Walls_[walls[0]].getWidth ();
    double distancex_, distancey_;
    double db=nBoid_[0].boidRadius_;
    double dw=Walls_[0].getRadius();
    int a,b;
    int trool;
    vector<tuple<bool,int, int, double>> list;
    priority_queue<double,vector<double>,greater<double>> heap;
    list.push_back(make_tuple(3,-1,-1,0));
    cout<<"Size gridboid="<<gridboids.size()<<endl;
    cout<<"Size copynboid="<<copynboid.size()<<endl;
    cout<<"Size walls="<<walls.size()<<endl;
    for(int i=0; i<gridboids.size(); i++)
    {
        //cout<<i<<" ciclo 1 urtoni\n";
        for(int j=0; j<copynboid.size(); j++)
        {
            if(copynboid[j]!=gridboids[i])
            {
                cout<<"Boid index="<<gridboids[i]<<"\t";
                x=sqrt(((nBoid_[gridboids[i]].getx()-nBoid_[copynboid[j]].getx())*(nBoid_[gridboids[i]].getx()-nBoid_[copynboid[j]].getx()))
                +((nBoid_[gridboids[i]].gety()-nBoid_[copynboid[j]].gety())*(nBoid_[gridboids[i]].gety()-nBoid_[copynboid[j]].gety())));
            
                v=sqrt(((nBoid_[gridboids[i]].getxV()-nBoid_[copynboid[j]].getxV())*(nBoid_[gridboids[i]].getxV()-nBoid_[copynboid[j]].getxV()))
                    +((nBoid_[gridboids[i]].getyV()-nBoid_[copynboid[j]].getyV())*(nBoid_[gridboids[i]].getyV()-nBoid_[copynboid[j]].getyV())));

                t=((2*db)-(x))/v;

                if(t<0 || t<tau)
                {
                    continue;
                }
                else
                {
                    heap.push(t);
                    list.push_back(make_tuple(0,gridboids[i],copynboid[j],t));
                }
            }
            
        }
        for(int j=0; j<walls.size(); j++)
        {
            cout<<"Boid index wall="<<gridboids[i]<<"\t";
            x=sqrt(((nBoid_[gridboids[i]].getx()-Walls_[walls[j]].getxOrigin())*(nBoid_[gridboids[i]].getx()-Walls_[walls[j]].getxOrigin()))
                +((nBoid_[gridboids[i]].gety()-Walls_[walls[j]].getyOrigin())*(nBoid_[gridboids[i]].gety()-Walls_[walls[j]].getyOrigin())));
            
            v=sqrt((nBoid_[gridboids[i]].getxV()*nBoid_[gridboids[i]].getxV())+(nBoid_[gridboids[i]].getyV()*nBoid_[gridboids[i]].getyV()));

            t=((dw+db)-x)/v;
            if(t<0 || t<tau)
            {
                continue;
            }
            else
            {
                heap.push(t);
                list.push_back(make_tuple(1,gridboids[i],walls[j],t));
            }
        }
    }
    tau=heap.top();
    if(tau==0)
    {
        return -1;
    }
    for(int i=0; i<list.size(); i++)
    {
        if(get<3>(list[i])==tau)
        {
            a=get<1>(list[i]);
            b=get<2>(list[i]);
            trool=get<0>(list[i]);
            break;
        }
    }

    pos1x=nBoid_[a].getx()+nBoid_[a].getxV()*tau;
    pos1y=nBoid_[a].gety()+nBoid_[a].getyV()*tau;
    
    if(trool==1)//walls
    {
        distancex_ = Walls_[b].getxOrigin()-(pos1x);
        distancey_ = Walls_[b].getyOrigin()-(pos2y);
        xClamp_ = clamp ( distancex_, -wWidth_ , wWidth_ ); 
        yClamp_ = clamp ( distancey_, -wWidth_ , wWidth_ ); 
        xP_ = Walls_[b].getxOrigin() + xClamp_; 
        yP_ = Walls_[b].getyOrigin() + yClamp_;
        
        if ( abs(pos1x-(xP_))<abs(pos1y-(yP_)) )
        {
            nBoid_[a].setyV(-nBoid_[a].getyV());
        }
        else nBoid_[a].setxV(-nBoid_[a].getxV());
        nBoid_[a].setx(pos1x-(nBoid_[a].getxV()*tau));
        nBoid_[a].sety(pos1y-(nBoid_[a].getyV()*tau));
    }
    else if(trool==0)//boids
    {
        
        pos2x=nBoid_[b].getx()+nBoid_[b].getxV()*tau;
        pos2y=nBoid_[b].gety()+nBoid_[b].getyV()*tau;

        vettore r_1 ( pos1x, pos1y);
        vettore r_2 ( pos2x, pos2y);
        vettore v_1 ( nBoid_[a].getxV(), nBoid_[a].getyV());
        vettore v_2 ( nBoid_[b].getxV(), nBoid_[b].getyV());

        cong=r_2-r_1;
        cong=cong.get_versor ();
        vettore norm=cong.get_normal ();

        double mod_v1n=cong*v_1;
        double mod_v2n=cong*v_2;
        double mod_v1tg=norm*v_1;
        double mod_v2tg=norm*v_2;

        vettore v_1n,v_2n,v_1tg,v_2tg;
        v_1n = mod_v1n * cong;
        v_1tg = mod_v1tg * norm;
        v_2n = mod_v2n * cong;
        v_2tg = mod_v2tg * norm;   
        vettore v_1new=v_2n+v_1tg;
        vettore v_2new=v_1n+v_2tg;
        nBoid_[a].setxV(v_1new.componenti[0]);
        nBoid_[a].setyV(v_1new.componenti[1]);
        nBoid_[a].setx(pos1x-(nBoid_[a].getxV()*tau));
        nBoid_[a].sety(pos1y-(nBoid_[a].getyV()*tau));
        //nBoid_[b].setxV(v_2new.componenti[0]);
        //nBoid_[b].setyV(v_2new.componenti[1]);
    }
    /*else if(trool==-1)
    {

    }*/
    return 1;
    
}

void updater(vector<int> boids, double deltaT)
{
    for(int i=0; i<boids.size(); i++)
    {
        nBoid_[boids[i]].setx(nBoid_[boids[i]].getx()+nBoid_[boids[i]].getxV()*deltaT);
        nBoid_[boids[i]].sety(nBoid_[boids[i]].gety()+nBoid_[boids[i]].getyV()*deltaT);
    }
}