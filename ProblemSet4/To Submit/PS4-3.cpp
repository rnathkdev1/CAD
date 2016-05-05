#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cmath>

//#include <oxymoron>


using namespace std;

int main(){
    
    string line, identifier;
    double x,y,z;
    double coordinates[3000][3],newface[10];

    bool sidebegin=false;
    const int delimiter=-1;
    
    
    int sidecounter=0;
    int f1;
    
    ifstream ifile;
    ofstream ofile("triceratops.wrl");
    
    ifile.open("triceratops.dat");
    
    //Preparing the file for writing coordinates
    ofile<<"#VRML V2.0 utf8\n\n";
    ofile<<"Background{\n";
    ofile<<"\t skyColor 1 1 1\n}\n\n";
    
    ofile<<"NavigationInfo{\n\ttype \"EXAMINE\"\n}\n\n";
    
    ofile<<"Shape{\n\tgeometry IndexedFaceSet{\n\t\tcoord Coordinate{\n\t\t\tpoint[";
    
    //Parsing data
    
    while(getline(ifile, line)){
        istringstream in(line);
        
        in>>identifier;
        
        if (identifier=="v"){
            in>>x>>y>>z;
            
            
            
            
            ofile<<x<<" "<<y<<" "<<z<<", ";
            
        }
        
        else {
            if (sidebegin==false){
                ofile<<"0 0 0]\n\t\t}\n\t\tcoordIndex[";
                sidebegin=true;
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
    ofile<<"\tappearance Appearance{\n\t\tmaterial Material{\n\t\t\tdiffuseColor 1 0 0\n\t\t}\n\t}\n}\n\n";
    
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
    ofile<<"\ttranslation 5 5 0\n";
    ofile<<"\tchildren [USE myName]\n";
    ofile<<"}\n\n";
    
    
    
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