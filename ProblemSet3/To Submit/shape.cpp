#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cmath>
using namespace std;

double STP(float a[3],float b[3],float c[3]){
    
    return(a[0]*(b[1]*c[2]-b[2]*c[1]) - a[1]*(b[0]*c[2]-b[2]*c[0]) + a[2]*(b[0]*c[1]-b[1]*c[0]));
}


double cross(float b[3],float c[3]){
    
    double cross[3];
    
    cross[0]=b[1]*c[2]-b[2]*c[1];
    cross[1]=-(b[0]*c[2]-b[2]*c[0]);
    cross[2]=b[0]*c[1]-b[1]*c[0];
    
    return(sqrt(cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2]));
    
}

int main(){
    
    string line, identifier;
    float x,y,z,centroidx=0,centroidy=0,centroidz=0;
    float coordinates[3000][3],face[3000][3];
    double volume=0,area=0;
    
    int vertexcount=0,facecount=0;
    int f1,f2,f3,j,k,l;
    
    float a[3],b[3],c[3];
    
    ifstream ifile;
    ifile.open("shape.dat");
    
    
    //Getting data and storing it into arrays
    while(getline(ifile, line)){
        istringstream in(line);
        
        in>>identifier;
        
        if (identifier=="v"){
            in>>x>>y>>z;
            coordinates[vertexcount][0]=x;
            coordinates[vertexcount][1]=y;
            coordinates[vertexcount][2]=z;
            
            centroidx+=x;
            centroidy+=y;
            centroidz+=z;
            ++vertexcount;
            
        }
        
        else {
            in>>f1>>f2>>f3;
            face[facecount][0]=f1;
            face[facecount][1]=f2;
            face[facecount][2]=f3;
            
            facecount++;
        }
        
    }
    
    coordinates[vertexcount][0]=coordinates[0][0];
    coordinates[vertexcount][1]=coordinates[0][1];
    coordinates[vertexcount][2]=coordinates[0][2];
    
    coordinates[vertexcount+1][0]=coordinates[1][0];
    coordinates[vertexcount+1][1]=coordinates[1][1];
    coordinates[vertexcount+1][2]=coordinates[1][2];

    
    centroidx/=vertexcount;
    centroidy/=vertexcount;
    centroidz/=vertexcount;
    
    //Finding volume
    
    for (int i=0;i<facecount;++i)
    {
        j=face[i][0];
        k=face[i][1];
        l=face[i][2];
        
        
        //Choosing the centroid as reference
        a[0]=coordinates[j][0]-centroidx;   a[1]=coordinates[j][1]-centroidy;   a[2]=coordinates[j][2]-centroidz;
        b[0]=coordinates[k][0]-centroidx;   b[1]=coordinates[k][1]-centroidy;   b[2]=coordinates[k][2]-centroidz;
        c[0]=coordinates[l][0]-centroidx;   c[1]=coordinates[l][1]-centroidy;   c[2]=coordinates[l][2]-centroidz;
        
        volume+=STP(a,b,c)/6;
        
        //For finding area keeping k as reference
        a[0]=coordinates[j][0]-coordinates[k][0]; a[1]=coordinates[j][1]-coordinates[k][1]; a[2]=coordinates[j][2]-coordinates[k][2];
        b[0]=coordinates[l][0]-coordinates[k][0]; b[1]=coordinates[l][1]-coordinates[k][1]; b[2]=coordinates[l][2]-coordinates[k][2];
        
        area+=(cross(a,b))/2;
        //cout<<area<<'\n';
    }
    
    
    
    
    // Displaying the answer
    
    cout<<"\nProblem Set 3-2\nRamnath Vijaykumar Pillai\nFile Name: shape.dat\n# of vertices: "<<vertexcount<<"\n# of faces: "<<facecount<<'\n';
    cout<<"Area: "<<area<<"\nVolume: "<<volume<<"\n\n\n";
    
    return 0;
    
}