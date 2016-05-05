//
//  main.cpp
//  STLGenerate
//
//  Created by Oxymoron on 1/15/16.
//  Copyright © 2016 Oxymoron. All rights reserved.
//  z=cos(x).cos(2y)

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

float funeval(float x, float y)
{
    float z;
    z=cos(x)*cos(2*y);
    return z;
    
}


int main()
{

    float z[500][500],meshX[500][500],meshY[500][500],triangles[10000][3],normals[500][3];
    float x=0.0,y=0.0;
    int i=0,j=0,lenx,leny,count=0,normindex=0;
    float xc,yc,zc,modN;
    ofstream ofile ("surface.stl");
    
    ofile<<"solid surface\n";
    
    
    //Generation of the z coordinates
    for (x=0; x<=3.14; x+=0.1,++i)
    {   j=0;
        for (y=0; y<=3.14; y+=0.1,++j)
        {
            z[i][j]=funeval(x,y);
            meshX[i][j]=x;
            meshY[i][j]=y;
        }
    }
    
    lenx=i-1;
    leny=j-1;
    
    //Generating the points in the triangles and the normals
    for (i=0;i<lenx;++i)
        for (j=0;j<leny;++j)
        {
            // Forming triangles
            triangles[count][0]=meshX[i][j];
            triangles[count][1]=meshY[i][j];
            triangles[count][2]=z[i][j];
            
            count+=1;
            triangles[count][0]=meshX[i+1][j+1];
            triangles[count][1]=meshY[i+1][j+1];
            triangles[count][2]=z[i+1][j+1];
            
            count+=1;
            triangles[count][0]=meshX[i][j+1];
            triangles[count][1]=meshY[i][j+1];
            triangles[count][2]=z[i][j+1];
            
            
            count=count+1;
            triangles[count][0]=meshX[i][j];
            triangles[count][1]=meshY[i][j];
            triangles[count][2]=z[i][j];
            
            count+=1;
            triangles[count][0]=meshX[i+1][j];
            triangles[count][1]=meshY[i+1][j];
            triangles[count][2]=z[i+1][j];
            
            count+=1;
            triangles[count][0]=meshX[i+1][j+1];
            triangles[count][1]=meshY[i+1][j+1];
            triangles[count][2]=z[i+1][j+1];
            
            count=count+1;
            
            //Forming Normals
            
            xc=(meshX[i][j]+meshX[i][j+1]+meshX[i+1][j+1])/3;
            yc=(meshY[i][j]+meshY[i][j+1]+meshY[i+1][j+1])/3;
            zc=(z[i][j]+z[i][j+1]+z[i+1][j+1])/3;
            modN=fabs(sqrt(1+pow(sin(xc)*cos(2*yc),2)+4*pow(cos(xc)*sin(2*yc),2)));
            
            normals[normindex][0]=sin(xc)*cos(2*y)/modN;
            normals[normindex][1]=2*cos(xc)*sin(2*y)/modN;
            normals[normindex][2]=1/modN;
            
            normindex+=1;
            
            xc=(meshX[i][j]+meshX[i+1][j]+meshX[i+1][j+1])/3;
            yc=(meshY[i][j]+meshY[i+1][j]+meshY[i+1][j+1])/3;
            zc=(z[i][j]+z[i+1][j]+z[i+1][j+1])/3;
            modN=fabs(sqrt(1+pow(sin(xc)*cos(2*yc),2)+4*pow(cos(xc)*sin(2*yc),2)));
            
            normals[normindex][0]=sin(xc)*cos(2*y)/modN;
            normals[normindex][1]=2*cos(xc)*sin(2*y)/modN;
            normals[normindex][2]=1/modN;
            
            normindex+=1;
            
            ofile<<"\tfacet normal "<<normals[normindex-2][0]<<" "<<normals[normindex-2][1]<<" "<<normals[normindex-2][2]<<'\n';
            ofile<<"\t\touter loop\n";
            ofile<<"\t\t\tvertex "<<triangles[count-6][0]<<" "<<triangles[count-6][1]<<" "<<triangles[count-6][2]<<'\n';
            ofile<<"\t\t\tvertex "<<triangles[count-5][0]<<" "<<triangles[count-5][1]<<" "<<triangles[count-5][2]<<'\n';
            ofile<<"\t\t\tvertex "<<triangles[count-4][0]<<" "<<triangles[count-4][1]<<" "<<triangles[count-4][2]<<'\n';
            ofile<<"\t\tendloop\n";
            ofile<<"\tendfacet\n";
            
            ofile<<"\tfacet normal "<<normals[normindex-1][0]<<" "<<normals[normindex-1][1]<<" "<<normals[normindex-1][2]<<'\n';
            ofile<<"\t\touter loop\n";
            ofile<<"\t\t\tvertex "<<triangles[count-3][0]<<" "<<triangles[count-3][1]<<" "<<triangles[count-3][2]<<'\n';
            ofile<<"\t\t\tvertex "<<triangles[count-2][0]<<" "<<triangles[count-2][1]<<" "<<triangles[count-2][2]<<'\n';
            ofile<<"\t\t\tvertex "<<triangles[count-1][0]<<" "<<triangles[count-1][1]<<" "<<triangles[count-1][2]<<'\n';
            ofile<<"\t\tendloop\n";
            ofile<<"\tendfacet\n";
            
        }
    
    // Writing it into an ASCII stl file
    
   
    ofile<<"endsolid surface";
    ofile.close();
    
    return 0;
}

