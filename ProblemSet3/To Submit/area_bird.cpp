#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    
    string line;
    float x,y,sumx=0,sumy=0,centroidx,centroidy;
    float coordinates[180][2];
    float a1,b1,a2,b2;
    
    double area=0;
    
    int count=0;
    
    
    
    ifstream ifile;
    ifile.open("bird.txt");
    
    while(getline(ifile, line)){
        
        istringstream in(line);
        in>>x>>y;
        
        sumx+=x;
        sumy+=y;

        coordinates[count][0]=x;
        coordinates[count][1]=y;
    
        ++count;
        
    }
    
    coordinates[count][0]=coordinates[0][0];
    coordinates[count][1]=coordinates[0][1];
    
    centroidx=sumx/count;
    centroidy=sumy/count;
    
    //ASSUMING THE POINTS ARE IN ORDER
    
    for (int i=0;i<count;++i)
    {
        a1=coordinates[i][0]-centroidx; b1=coordinates[i][1]-centroidy;
        a2=coordinates[i+1][0]-centroidx; b2=coordinates[i+1][1]-centroidy;
        area+=0.5*( a1*b2-a2*b1);
    }
    
    // Displaying the answer
    
    cout<<"\nProblem Set 3-1\nRamnath Vijaykumar Pillai\nFile Name: bird.txt\n# of vertices: "<<count<<'\n';
    cout<<"Area: "<<area<<"\n\n\n";
    
    
    
    
    
    return 0;
    
}