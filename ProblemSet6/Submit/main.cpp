#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

//-----------------------------------------------------------VECTOR TOOLS----------------------------------------------------------//

void cross(float b[3],float c[3], float crossProd[3]){
    
    
    crossProd[0]=b[1]*c[2]-b[2]*c[1];
    crossProd[1]=-(b[0]*c[2]-b[2]*c[0]);
    crossProd[2]=b[0]*c[1]-b[1]*c[0];
}

void normalize(float v[3], float normalV[3])
{
    normalV[0]=v[0]/sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    normalV[1]=v[1]/sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    normalV[2]=v[2]/sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

float dot(float a[3], float b[3]){
    
    float answer = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
    return answer;
}

//--------------------------------------------------------------------FACE CLASS------------------------------------------------------//

class Face{

    
public:
    
    float vertex1[3], vertex2[3], vertex3[3];
    float centroid[3];
    float normal[3];
    int index1,index2,index3;
    
    void initialize(float* vertexa, float* vertexb, float* vertexc, int i, int j, int width, bool flip){
        this->vertex1[0]=vertexa[0];    this->vertex1[1]=vertexa[1];    this->vertex1[2]=vertexa[2];
        this->vertex2[0]=vertexb[0];    this->vertex2[1]=vertexb[1];    this->vertex2[2]=vertexb[2];
        this->vertex3[0]=vertexc[0];    this->vertex3[1]=vertexb[1];    this->vertex3[2]=vertexb[2];
        
        if (!flip){
            this->index1=i + j*width;
            this->index2=(i+1) + j*width;
            this->index3=(i+1) + (j+1)*width;
            
        }
        
        else
        {
            this->index1=i + j*width;
            this->index3=(i) + (j+1)*width;
            this->index2=(i+1) + (j+1)*width;
        }
        
        this->calculateCentroid();
        this->calculateNormal();
        
        return;
    }
    
    void calculateCentroid(){
        this->centroid[0]=(this->vertex1[0]+this->vertex2[0]+this->vertex3[0])/3;
        this->centroid[1]=(this->vertex1[1]+this->vertex2[1]+this->vertex3[1])/3;
        this->centroid[2]=(this->vertex1[2]+this->vertex2[2]+this->vertex3[2])/3;
    }
    
    void calculateNormal(){
        
        float a[3],b[3], normal[3], normalized[3];
        
        a[0]=this->vertex1[0]-this->centroid[0];   a[1]=this->vertex1[1]-this->centroid[1];   a[2]=this->vertex1[2]-this->centroid[2];
        b[0]=this->vertex2[0]-this->centroid[0];   b[1]=this->vertex2[1]-this->centroid[1];   a[2]=this->vertex2[2]-this->centroid[2];
        
        cross(a,b,normal);
        normalize(normal,normalized);
        this->normal[0]=normalized[0];  this->normal[1]=normalized[1];  this->normal[2]=normalized[2];
        
    }
    
};

//---------------------------------------------------------------MAIN---------------------------------------------------------------//


int main()
{
    int width;
    int height;
    
    string line, identifier;
    bool firstline=true;
    int W,B;
    
    float e[3],q[3],a[3], b[3], d, dir[3];
    float x_[200][200], y_[200][200], z_[200][200], normal[200][200][3], planeNormal[3];
    float color[200][200];
    
    int count = 0,faceCount=0;
    
    Face face[33000];
    
    //Parsing through the parameter file
    ifstream paramFile;
    
    paramFile.open("parameters.txt");
    
    while (getline(paramFile, line)){
        istringstream in(line);
        
        
        
        float x, y, z;
        x=0; y=0;z=0;
        
        in>>identifier;
        in>>x>>y>>z;
        
        //Viewpoint e
        if (identifier=="e")
        {   e[0]=x; e[1]=y; e[2]=z;}
        
        
        //Zebra board
        if (identifier == "q")
        {   q[0]=x; q[1]=y; q[2]=z;}
        
        if (identifier == "a")
        {   a[0]=x; a[1]=y; a[2]=z;}
        
        if (identifier == "b")
        {   b[0]=x; b[1]=y; b[2]=z;}
        
        if (identifier == "W")
            W=x;
        
        if (identifier == "B")
            B=x;
        
        if (identifier == "d")
        {   dir[0]=x; dir[1]=y; dir[2]=z;}
            
    }
    paramFile.close();
    
    // Processing the plane input
    cross(a,b,planeNormal);
    normalize(a,a);
    normalize(b,b);
    normalize(planeNormal,planeNormal);
    d=dot(planeNormal,q);
    
    
    
    // Parsing through the data file and simultaneously writing the coordinates
    
    ifstream ifile;
    ifile.open("surface.txt");
    
    if (!ifile)
    {
        cout<<"File doesnot exist\n";
        return 0;
    }
    
    ofstream ofile("output.wrl");
    ofile<<"#VRML V2.0 utf8\n\n";
    ofile<<"Background{\n";
    ofile<<"\t skyColor 1 1 1\n}\n\n";
    
    ofile<<"NavigationInfo{\n\ttype \"EXAMINE\"\n}\n\n";
    
    ofile<<"Shape{\n\tgeometry IndexedFaceSet{\n\t\tcoord Coordinate{\n\t\t\tpoint[";
    
    while(getline(ifile, line)){
        float x, y, z;
        x=0;y=0;z=0;
        istringstream in(line);
        in>>x>>y>>z;
        
        if (firstline==true){
            firstline=false;
            width=x;
            height=y;
            continue;
        }
        
        ofile<<x<<" "<<y<<" "<<z<<", \n\t\t\t\t";
        
        
        int j=count % width;
        int i=count/width;
        
        
        x_[i][j]=x;
        y_[i][j]=y;
        z_[i][j]=z;
        ++count;
    }
    
    ofile<<"]\n\t\t}\n\t\tcoordIndex[";
    
    ifile.close();
    
    count=0;
    
    float vertexa[3], vertexb[3], vertexc[3], vertexd[3];
    float tempA[3], tempB[3], tempNormal[3], tempNormalized[3];
    float p_[3], u[3], t, finalPoint[3],v[3], newCoeff;
    
    
    for (int i=0; i< width; ++i)
        for (int j=0;j< height; ++j)
        {
            
            
            if (i>0 && i<width-1){
                tempA[0] = x_[i+1][j]-x_[i-1][j];    tempA[1] = y_[i+1][j]-y_[i-1][j];    tempA[2] = z_[i+1][j]-z_[i-1][j];
            }
            else if (i==0){
                tempA[0] = x_[i+1][j]-x_[i][j];    tempA[1] = y_[i+1][j]-y_[i][j];    tempA[2] = z_[i+1][j]-z_[i][j];
            }
            else if (i==width-1)
            {
                    tempA[0] = x_[i][j]-x_[i-1][j];    tempA[1] = y_[i][j]-y_[i-1][j];    tempA[2] = z_[i][j]-z_[i-1][j];
            }
            
            if (j>0 && j<height-1){
                tempB[0] = x_[i][j+1]-x_[i][j-1];    tempB[1] = y_[i][j+1]-y_[i][j-1];    tempB[2] = z_[i][j+1]-z_[i][j-1];
            }
            else if (j==0){
                tempB[0] = x_[i][j+1]-x_[i][j];    tempB[1] = y_[i][j+1]-y_[i][j];    tempB[2] = z_[i][j+1]-z_[i][j];
            }
            else if (j==height-1)
            {
                tempB[0] = x_[i][j]-x_[i][j-1];    tempB[1] = y_[i][j]-y_[i][j-1];    tempB[2] = z_[i][j]-z_[i][j-1];
            }
            
            cross(tempB,tempA,tempNormal);
            normalize(tempNormal,tempNormalized);
            
            
            normal[i][j][0]=tempNormalized[0];  normal[i][j][1]=tempNormalized[1];  normal[i][j][2]=tempNormalized[2];
            
            p_[0]=x_[i][j];p_[1]=y_[i][j];p_[2]= z_[i][j];
            
            v[0]=p_[0]-e[0]; v[1]=p_[1]-e[1]; v[2]=p_[2]-e[2];
            
            newCoeff=-2*dot(v,tempNormalized);
            
            for (int k=0;k<3;++k)
                u[k]=v[k]+newCoeff*tempNormalized[k];
            
            t=(d-dot(p_,planeNormal))/dot(u,planeNormal);
            
            for (int k=0;k<3;++k)
                finalPoint[k]=p_[k] + t*u[k];
            
            
            float localVec[3]={finalPoint[0]-q[0], finalPoint[1]-q[1], finalPoint[2]-q[2]};
            
            float localA=dot(localVec,dir);
            
            int BWrem=(int)(localA)%(B + W);
            int BWBrem=(int)(localA)%(B + W + B);
        
            if (BWrem>B)
            {
                color[i][j]=1;}// this is 1
            else
            {
                
                color[i][j]=0;
            }
         
            
            //--------------------------------------------Making faces :P :D :D :O :D ;)--------------------------------------------------
            
            if ((i<width-1) && (j<height-1)){
                
                vertexa[0]=x_[i][j]; vertexa[1]=y_[i][j]; vertexa[2]=z_[i][j];
                vertexb[0]=x_[i+1][j]; vertexb[1]=y_[i+1][j]; vertexb[2]=z_[i+1][j];
                vertexc[0]=x_[i+1][j+1]; vertexc[1]=y_[i+1][j+1]; vertexc[2]=z_[i+1][j+1];
                vertexd[0]=x_[i][j+1]; vertexd[1]=y_[i][j+1]; vertexd[2]=z_[i][j+1];
                
                face[faceCount].initialize(vertexa, vertexb, vertexc,i,j,width,false);
                
                faceCount++;
                face[faceCount].initialize(vertexa, vertexc, vertexd,i,j,width,true);
                faceCount++;
                
            }
         
        }
    
    for (int i=0;i<faceCount;++i)
    {
        ofile<<face[i].index1<<" "<<face[i].index2<<" "<<face[i].index3<<" -1";
        ofile<<"\n\t\t\t\t\t";
        
    }
    
    
     ofile<<"]\n";
    
    
     ofile<<"\t\tcolor Color{\n";
     ofile<<"\t\t\tcolor[0 0 0, 1 1 1]\n";
     ofile<<"\t\t}\n";
     
     ofile<<"\t\t colorIndex[";
     
    
     for (int i=0;i<width-1;++i)
         for (int j=0;j<height-1;++j)
         {
             ofile<<color[i][j]<<" "<<color[i+1][j]<<" "<<color[i+1][j+1]<<" -1";
             ofile<<"\n\t\t\t\t\t";
             ofile<<color[i][j]<<" "<<color[i+1][j+1]<<" "<<color[i][j+1]<<" -1";
             ofile<<"\n\t\t\t\t\t";
     
         }
     
    ofile<<"]\n";
    
    ofile<<"\t\t}\n";
    
    ofile<<"}";
    
    ofile.close();
    return 0;
    
}