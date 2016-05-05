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


void cross(float b[3],float c[3], double crossProd[3]){
    
    
    crossProd[0]=b[1]*c[2]-b[2]*c[1];
    crossProd[1]=-(b[0]*c[2]-b[2]*c[0]);
    crossProd[2]=b[0]*c[1]-b[1]*c[0];
    
    //cout<<crossProd[0]<<'\n';
    //return(sqrt(cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2]));
    
}



int main(){
    
    string line, identifier;
    double x,y,z,centroidx=0,centroidy=0,centroidz=0,thisCentroidx,thisCentroidy,thisCentroidz;
    double coordinates[3000][3],face[3000][15];
    int polygon[3000];
    double volume=0,area=0,crossProd[3],sumCross[3];
    
    int vertexcount=0,facecount=0, sidecounter=0;
    int f1,f2,f3,f4,j,k,l,m,thisIndex,nextIndex;
    
    float a[3],b[3],c[3];
    
    ifstream ifile;
    ifile.open("triceratops.dat");
    
    
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
            
            sidecounter=0;
            while (in)
            {
                in>>f1;
                face[facecount][sidecounter]=f1;
                sidecounter++;
            }
            //cout<<'\n';
            polygon[facecount]=sidecounter-1;
            facecount++;
        }
    }
    
    centroidx/=vertexcount;
    centroidy/=vertexcount;
    centroidz/=vertexcount;
    
    //Finding volume
    for (int i=0;i<facecount;++i)
    {
        thisCentroidx=0;
        thisCentroidy=0;
        thisCentroidz=0;
        
        //Finding Centroids
        for (int j=0;j<polygon[i];++j)
            
        {
            thisIndex=face[i][j];
            thisCentroidx+=coordinates[thisIndex][0]/polygon[i];
            thisCentroidy+=coordinates[thisIndex][1]/polygon[i];
            thisCentroidz+=coordinates[thisIndex][2]/polygon[i];
        }
        
        //Finding volume and area
        sumCross[0]=0;
        sumCross[1]=0;
        sumCross[2]=0;
        
        for (int j=0;j<polygon[i];++j){
            
            // For finding areas taking "thisCentroid" as reference
            thisIndex=face[i][j];
            nextIndex=face[i][(j+1)%polygon[i]];
            
            a[0]=coordinates[thisIndex][0]-thisCentroidx; a[1]=coordinates[thisIndex][1]-thisCentroidy; a[2]=coordinates[thisIndex][2]-thisCentroidz;
            
            b[0]=coordinates[nextIndex][0]-thisCentroidx; b[1]=coordinates[nextIndex][1]-thisCentroidy; b[2]=coordinates[nextIndex][2]-thisCentroidz;
            
            cross(a,b,crossProd);
            //cout<<crossProd[0]<<'\n';
            sumCross[0]+=0.5*crossProd[0];
            sumCross[1]+=0.5*crossProd[1];
            sumCross[2]+=0.5*crossProd[2];
            
            //For finding volume,
            
            c[0]=centroidx-thisCentroidx; c[1]=centroidy-thisCentroidy; c[2]=centroidz-thisCentroidz;
            
            volume+=STP(a,b,c)/6;
           
        }
        //cout<<area<<'\n';
        area+=sqrt(sumCross[0]*sumCross[0] +sumCross[1]*sumCross[1]+sumCross[2]*sumCross[2]);
    }
    
    /*
    for (int i=0;i<facecount;++i){
        cout<<'\n';
        for (int j=0;j<polygon[i];++j)
            cout<<face[i][j]<<" ";
    }
    */
    
    volume=abs(volume);
    area=abs(area);
    
    // Displaying the answer
    cout<<"\nProblem Set 3-2\nRamnath Vijaykumar Pillai\nFile Name: triceratops.dat\n# of vertices: "<<vertexcount<<"\n# of faces: "<<facecount<<'\n';
    cout<<"Area: "<<area<<"\nVolume: "<<volume<<"\n\n\n";
    
    return 0;
    
}