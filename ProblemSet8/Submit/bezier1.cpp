# include <iostream>
# include "vector3D.h"
# include <math.h>
# include <fstream>
using namespace std;
using namespace CMU462;

float points[10000][3];
int countPoints=0;;

float tangents[10000][3];
int countTangents=0;

void calculateValues(Vector3D P0, Vector3D P1, Vector3D P2, Vector3D P3)
{
    int npiece = 20;
    
    double delta = 1.0/npiece;
    
    for (int i=0;i<npiece+1;++i)
    {
        float u = i*delta;
        Vector3D point = pow((1-u),3) * P0 + 3*(1-u)*(1-u) * u * P1 + 3*(1-u) * u*u * P2 + u*u*u * P3;
        Vector3D tangent = 3 * (1-u)*(1-u) * P0 + 3*(1-u)*(1-u) * P1 + 6*(1-u) * u * P1 - 3 * u*u * P2 + 6*(1-u) * u * P2 + 3 * u*u * P3;
        
        points[countPoints][0] = point[0];        points[countPoints][1] = point[1];        points[countPoints][2] = point[2];
        tangents[countTangents][0] = tangent[0];  tangents[countTangents][1] = tangent[1];  tangents[countTangents][2] = tangent[2];
        
        countTangents++;
        countPoints++;
        
    }
    
    
}


int main()
{
    ofstream ofile ("bezier1.wrl");
    
    
    /*
     P0 =(0,0,0), P1=(2,0,0), P2=(2,1,1), P3=(3,1,2)
     P3=(3,1,2), P4=(4,1,3), P5=(4,2,3), P6=(2,4,5)
     P6=(2,4,5), P7=(1,5,6), P8=(0,5,7), P9=(0,0,7)
     */
    
    //Curve 1
    Vector3D P0(0.0,0.0,0.0), P1(2.0,0.0,0.0), P2(2.0,1.0,1.0);
    //Curve 2
    Vector3D P3(3.0,1.0,2.0), P4(4.0,1.0,3.0), P5(4.0,2.0,3.0);
    //Curve 3
    Vector3D P6(2.0,4.0,5.0), P7(1.0,5.0,6.0), P8(0.0,5.0,7.0), P9(0.0,0.0,7.0);
    
    /*
     Bezier curve:
     (1-u)^3 * P0 + 3*(1-u)^2 * u * P1 + 3*(1-u) * u^2 * P2 + u^3 * P3;
     
     Tangent: 
     3 * (1-u)^2 * P0 + 3*(1-u)^2 * P1 + 6*(1-u) * u * P1 - 3 * u^2 * P2 + 6*(1-u) * u * P2 + 3 * u^2 * P3
     
     */
    
    //Calculating the points and tangents
    calculateValues(P0, P1, P2, P3);
    calculateValues(P3, P4, P5, P6);
    calculateValues(P6, P7, P8, P9);
    
    
    //Writing the VRML file
    ofile<<"#VRML V2.0 utf8\n\n";
    ofile<<"Background{\n";
    ofile<<"\t skyColor 1 1 1\n}\n\n";
    ofile<<"NavigationInfo{\n\ttype \"EXAMINE\"\n}\n\n";
    
    
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
    
    //TEXT X
    ofile<<"Transform\n";
    ofile<<"{\n";
    ofile<<"\ttranslation 12 0 0\n";
    ofile<<"\tchildren Shape\n";
    ofile<<"\t{\n";
    ofile<<"\t\tgeometry Text\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tstring [ \" X \"]\n";
    ofile<<"\t\t\tfontStyle FontStyle\n";
    ofile<<"\t\t\t{\n";
    ofile<<"\t\t\t\tfamily	\"SANS\"\n";
    ofile<<"\t\t\t\tjustify	\"MIDDLE\"\n";
    ofile<<"\t\t\t\tstyle	\"BOLD\"\n";
    ofile<<"\t\t\t\tsize 1\n";
    ofile<<"\t\t\t}\n";
    ofile<<"\t\t}\n\n";
            
    ofile<<"\t\tappearance Appearance\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tmaterial Material\n";
    ofile<<"\t\t\t{";
    ofile<<"\t\t\t\tdiffuseColor 0 0 0\n";
    ofile<<"\t\t\t}\n";
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n";

    //TEXT Y
    ofile<<"Transform\n";
    ofile<<"{\n";
    ofile<<"\ttranslation 0 12 0\n";
    ofile<<"\tchildren Shape\n";
    ofile<<"\t{\n";
    ofile<<"\t\tgeometry Text\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tstring [ \" Y \"]\n";
    ofile<<"\t\t\tfontStyle FontStyle\n";
    ofile<<"\t\t\t{\n";
    ofile<<"\t\t\t\tfamily	\"SANS\"\n";
    ofile<<"\t\t\t\tjustify	\"MIDDLE\"\n";
    ofile<<"\t\t\t\tstyle	\"BOLD\"\n";
    ofile<<"\t\t\t\tsize 1\n";
    ofile<<"\t\t\t}\n";
    ofile<<"\t\t}\n\n";
    
    ofile<<"\t\tappearance Appearance\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tmaterial Material\n";
    ofile<<"\t\t\t{";
    ofile<<"\t\t\t\tdiffuseColor 0 0 0\n";
    ofile<<"\t\t\t}\n";
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n";
    
    
    //TEXT Z
    ofile<<"Transform\n";
    ofile<<"{\n";
    ofile<<"\ttranslation 0 0 12\n";
    ofile<<"\tchildren Shape\n";
    ofile<<"\t{\n";
    ofile<<"\t\tgeometry Text\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tstring [ \" Z \"]\n";
    ofile<<"\t\t\tfontStyle FontStyle\n";
    ofile<<"\t\t\t{\n";
    ofile<<"\t\t\t\tfamily	\"SANS\"\n";
    ofile<<"\t\t\t\tjustify	\"MIDDLE\"\n";
    ofile<<"\t\t\t\tstyle	\"BOLD\"\n";
    ofile<<"\t\t\t\tsize 1\n";
    ofile<<"\t\t\t}\n";
    ofile<<"\t\t}\n\n";
    
    ofile<<"\t\tappearance Appearance\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tmaterial Material\n";
    ofile<<"\t\t\t{";
    ofile<<"\t\t\t\tdiffuseColor 0 0 0\n";
    ofile<<"\t\t\t}\n";
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n";

    
    ofile<<"Shape\n";
    ofile<<"{\n";
    ofile<<"\tgeometry IndexedLineSet\n";
    ofile<<"\t{\n";
    ofile<<"\t\tcolorPerVertex  FALSE\n";
    ofile<<"\t\tcoord Coordinate\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tpoint[\n";
    
    
    //PUT \t\t\tcoord here
    for (int i=0;i<countPoints;++i)
        ofile<<"\t\t\t"<< points[i][0]<<" "<<points[i][1]<<" "<<points[i][2]<<" \n";
    
    //Putting the control points
    ofile<<"\t\t\t"<<P0[0]<<" "<<P0[1]<<" "<<P0[2]<<"\n";
    ofile<<"\t\t\t"<<P1[0]<<" "<<P1[1]<<" "<<P1[2]<<"\n";
    ofile<<"\t\t\t"<<P2[0]<<" "<<P2[1]<<" "<<P2[2]<<"\n";
    ofile<<"\t\t\t"<<P3[0]<<" "<<P3[1]<<" "<<P3[2]<<"\n";
    ofile<<"\t\t\t"<<P4[0]<<" "<<P4[1]<<" "<<P4[2]<<"\n";
    ofile<<"\t\t\t"<<P5[0]<<" "<<P5[1]<<" "<<P5[2]<<"\n";
    ofile<<"\t\t\t"<<P6[0]<<" "<<P6[1]<<" "<<P6[2]<<"\n";
    ofile<<"\t\t\t"<<P7[0]<<" "<<P7[1]<<" "<<P7[2]<<"\n";
    ofile<<"\t\t\t"<<P8[0]<<" "<<P8[1]<<" "<<P8[2]<<"\n";
    ofile<<"\t\t\t"<<P9[0]<<" "<<P9[1]<<" "<<P9[2]<<"\n";
    
    
    
    ofile<<"\t\t\t]\n";
    ofile<<"\t\t}\n";
    ofile<<"\t\tcoordIndex [\n";
    
    
    for (int i=0;i<countPoints-1;++i)
        ofile<<"\t\t\t"<<i<<" "<<i+1<<" -1\n";
    
    int thisCount=0;
    int iter = countPoints;
    
    while (thisCount<9){
        ofile<<"\t\t\t"<<iter<<" "<<iter+1<<" -1\n";
        iter++;
        thisCount++;
        
    }
    
    ofile<<"\t\t\t]\n";
    ofile<<"\t\tcolor Color\n";
    ofile<<"\t\t{\n";
    ofile<<"\t\t\tcolor [\n";
    //PUT \t\t\t\t COLOR HERE
    for (int i=0;i<countPoints;++i){
        if (i/20==0)
            ofile<<"\t\t\t1 0 0 \n";
        else if (i/20==1)
            ofile<<"\t\t\t0 1 0 \n";
        else if (i/20==2)
            ofile<<"\t\t\t0 0 1 \n";
        else
            ofile<<"\t\t\t1 1 1 \n";
    }
    ofile<<"\t\t\t]\n";
    
    ofile<<"\t\t}\n";
    ofile<<"\t}\n";
    ofile<<"}\n";

    
}