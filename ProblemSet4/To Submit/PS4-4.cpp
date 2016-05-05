#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cmath>

//#include<oxymoron>
using namespace std;

int main(){
    
    string line, identifier;
    double x,y,z,x_,y_,z_;
    double coordinates[3000][3],newface[10];
    const double ux=1/sqrt(3),uy=1/sqrt(3),uz=1/sqrt(3);
    

    
    bool sidebegin1=false,sidebegin2=false;
    const int delimiter=-1;
    const double theta=60*M_PI/180;
    
    const double a11=cos(theta)+ux*ux*(1-cos(theta));
    const double a12=ux*uy*(1-cos(theta)) - uz*sin(theta);
    const double a13=ux*uz*(1-cos(theta)) + uy*sin(theta);
    
    const double a21=ux*uy*(1-cos(theta)) + uz*sin(theta);
    const double a22=cos(theta)+uy*uy*(1-cos(theta));
    const double a23=uz*uy*(1-cos(theta)) - ux*sin(theta);
    
    const double a31=uz*ux*(1-cos(theta)) - uy*sin(theta);
    const double a32=uz*uy*(1-cos(theta)) + ux*sin(theta);
    const double a33=cos(theta)+uz*uz*(1-cos(theta));
    
    
    int sidecounter=0;
    int f1;
    
    ifstream ifile;
    ofstream ofile("triceratops2.wrl");
    
    ifile.open("triceratops.dat");
    
    //Preparing the file for writing coordinates
    ofile<<"#VRML V2.0 utf8\n\n";
    ofile<<"Background{\n";
    ofile<<"\t skyColor 1 1 1\n}\n\n";
    
    ofile<<"NavigationInfo{\n\ttype \"EXAMINE\"\n}\n\n";
    
    ofile<<"DEF Original Shape{\n\tgeometry IndexedFaceSet{\n\t\tcoord Coordinate{\n\t\t\tpoint[";
    
    //Parsing data
    
    while(getline(ifile, line)){
        istringstream in(line);
        
        in>>identifier;
        
        if (identifier=="v"){
            in>>x>>y>>z;
            ofile<<x<<" "<<y<<" "<<z<<", ";
            
        }
        
        else {
            if (sidebegin1==false){
                ofile<<"0 0 0]\n\t\t}\n\t\tcoordIndex[";
                sidebegin1=true;
            }
            
            sidecounter=0;
            while (in.good())
            {
                in>>f1;
                newface[sidecounter]=f1;
                sidecounter++;
            }
            for (int i=0;i<sidecounter-1;++i)
            {
                ofile<<" "<<newface[i];
            }
            ofile<<" "<<delimiter<<"\n\t\t\t\t\t";
        }
    }
    
    ifile.close();
    
    //Making the final touches to the file
    ofile<<"]\n\t\t}\n";
    ofile<<"\tappearance Appearance{\n\t\tmaterial Material{\n\t\t\tdiffuseColor 1 0 0\n\t\t}\n\t}\n}\n\n";
    
    
    
    //--------------------------------------------------------------------------------------------------------------------------------
    
    //Writing the transformed output
    
    ifile.open("triceratops.dat");
    ofile<<"DEF Transformed Shape{\n\tgeometry IndexedFaceSet{\n\t\tcoord Coordinate{\n\t\t\tpoint[";
    
    //Parsing data
    
    while(getline(ifile, line)){
        istringstream in(line);
        
        in>>identifier;
        
        if (identifier=="v"){
            in>>x>>y>>z;
            
            x_=2*(a11*x + a12*y + a13*z);
            y_=a21*x + a22*y + a23*z;
            z_=a31*x + a32*y + a33*z;
            
            ofile<<x_<<" "<<y_<<" "<<z_<<", ";
            
        }
        
        else {
            if (sidebegin2==false){
                ofile<<"0 0 0]\n\t\t}\n\t\tcoordIndex[";
                sidebegin2=true;
            }
            
            sidecounter=0;
            while (in.good())
            {
                in>>f1;
                newface[sidecounter]=f1;
                sidecounter++;
            }
            for (int i=0;i<sidecounter-1;++i)
            {
                ofile<<" "<<newface[i];
            }
            ofile<<" "<<delimiter<<"\n\t\t\t\t\t";
        }
    }
    
    //Making the final touches to the file
    ofile<<"]\n\t\t}\n";
    ofile<<"\tappearance Appearance{\n\t\tmaterial Material{\n\t\t\tdiffuseColor 0 1 0\n\t\t}\n\t}\n}\n\n";
    

    //---------------------------------------------------------------------------------------------------------------------------------
    
    //Putting the Name
    
    ofile<<"DEF myName Shape{\n\tgeometry Text {\n";
    ofile<<"\t\tstring [\"Ramnath Pillai (RVPILLAI)\" ]\n";
    ofile<<"\t\t\tfontStyle FontStyle{\n";
    ofile<<"\t\t\tfamily \"SANS\"\n";
    ofile<<"\t\t\tjustify \"MIDDLE\"\n";
    ofile<<"\t\t\tstyle \"BOLD\"\n";
    ofile<<"\t\t\tsize 0.5\n";
    ofile<<"\t\t}\n\t}\n";
    ofile<<"\tappearance Appearance {\n";
    ofile<<"\t\tmaterial Material {\n";
    ofile<<"\t\t\tdiffuseColor 1 0 1\n";
    ofile<<"\t\t}\n\t}\n";
    ofile<<"}\n\n";
    
    ofile<<"Transform{\n";
    ofile<<"\ttranslation 5 8 0\n";
    ofile<<"\tchildren [USE myName]\n";
    ofile<<"}\n\n";
    
    //Making axes
    
    ofile<<"DEF X Shape{\n\tgeometry Extrusion {\n\t\tspine[0 0 0, 10 0 0, 10 0 0, 11 0 0]\n\t\tcrossSection[0.5 0.5, 0.5 -0.5, -0.5 -0.5, -0.5 0.5, 0.5 0.5]\n\t\tscale[0.1 0.1, 0.1 0.1, 0.3 0.3, 0 0]\n\t\t}\n\n";
    ofile<<"\tappearance Appearance {\n";
    ofile<<"\t\tmaterial Material {\n";
    ofile<<"\t\t\tdiffuseColor 0 0 0\n";
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n\n";
    
    ofile<<"DEF Z Shape{\n\tgeometry Extrusion {\n\t\tspine[0 0 0, 0 10 0, 0 10 0, 0 11 0]\n\t\tcrossSection[0.5 0.5, 0.5 -0.5, -0.5 -0.5, -0.5 0.5, 0.5 0.5]\n\t\tscale[0.1 0.1, 0.1 0.1, 0.3 0.3, 0 0]\n\t\t}\n\n";
    ofile<<"\tappearance Appearance {\n";
    ofile<<"\t\tmaterial Material {\n";
    ofile<<"\t\t\tdiffuseColor 0 0 0\n";
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n\n";
    
    ofile<<"DEF Y Shape{\n\tgeometry Extrusion {\n\t\tspine[0 0 0, 0 0 10, 0 0 10, 0 0 11]\n\t\tcrossSection[0.5 0.5, 0.5 -0.5, -0.5 -0.5, -0.5 0.5, 0.5 0.5]\n\t\tscale[0.1 0.1, 0.1 0.1, 0.3 0.3, 0 0]\n\t\t}\n\n";
    ofile<<"\tappearance Appearance {\n";
    ofile<<"\t\tmaterial Material {\n";
    ofile<<"\t\t\tdiffuseColor 0 0 0\n";
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n\n";
    
    return 0;
    
}