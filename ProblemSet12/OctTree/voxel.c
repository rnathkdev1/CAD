/*
 *                 24786  GEOMETRIC MODELING
 *                 Carnegie Mellon University
 *                          VOXEL
 */

#include "voxel.h"

int MAXDEPTH = 4;

int subdivide(struct cell* thisCell);
void WriteToFile(double x, double y, double z, double cellsize, int depth, int ispartial);

void initialize(struct cell* thisCell, double cellsize, double startX, double startY, double startZ, int depth){
  //printf("%f %f %f %f\n", startX , startY, startZ,cellsize);
  
  thisCell->startX = startX;
  thisCell->startY = startY;
  thisCell->startZ = startZ;
  thisCell->depth = depth;
  thisCell->cellsize = cellsize;
}

void encodeOctTree(struct cell *thisCell){
  
  //Checking if subdivision is required
  int condition = subdivide (thisCell);

  //printf("Condition value is %d \n",condition);

  //if (thisCell->depth>=4)  return;

  if (condition == 2){
    //printf("Returning\n");
    return;
  }


  else if (condition == 0){
    //printf("Don't subdivide but write to VRML file\n");
    WriteToFile(thisCell->startX, thisCell->startY, thisCell->startZ, thisCell->cellsize, thisCell->depth, 0);
    return;
  }

  else if (thisCell->depth == MAXDEPTH){
    if (thisCell->code == 'p'){
      WriteToFile(thisCell->startX, thisCell->startY, thisCell->startZ, thisCell->cellsize, thisCell->depth,1);
    }  
  }

  else if (condition == 1){
    //printf("Subdivide\n");
    double cellsize = thisCell->cellsize/2.0;
    double startX = thisCell->startX, startY = thisCell->startY, startZ = thisCell->startZ;
    int nextdepth = thisCell->depth + 1;

    thisCell->oct[0] = malloc(sizeof(struct cell));
    thisCell->oct[1] = malloc(sizeof(struct cell));
    thisCell->oct[2] = malloc(sizeof(struct cell));
    thisCell->oct[3] = malloc(sizeof(struct cell));
    thisCell->oct[4] = malloc(sizeof(struct cell));
    thisCell->oct[5] = malloc(sizeof(struct cell));
    thisCell->oct[6] = malloc(sizeof(struct cell));
    thisCell->oct[7] = malloc(sizeof(struct cell));

    //printf("Subdividing the parent having startX %f startY %f startZ %f and width %f\n", startX, startY, startZ, thisCell->cellsize);

    initialize (thisCell->oct[0],cellsize, startX, startY, startZ, nextdepth);
    initialize (thisCell->oct[1],cellsize, startX + cellsize, startY, startZ, nextdepth);
    initialize (thisCell->oct[2],cellsize, startX, startY + cellsize, startZ, nextdepth);
    initialize (thisCell->oct[3],cellsize, startX, startY, startZ + cellsize, nextdepth);
    initialize (thisCell->oct[4],cellsize, startX+cellsize, startY + cellsize, startZ, nextdepth);
    initialize (thisCell->oct[5],cellsize, startX, startY + cellsize, startZ+cellsize, nextdepth);
    initialize (thisCell->oct[6],cellsize, startX+cellsize, startY, startZ + cellsize, nextdepth);
    initialize (thisCell->oct[7],cellsize, startX+cellsize, startY + cellsize, startZ+cellsize, nextdepth);

    for (int i = 0; i<8; ++i){
      encodeOctTree(thisCell->oct[i]);
    }
    return;
  }
}

double X0, X1, X2;
FILE      *fp;                       /* target VRML file "voxel.wrl"  */

int main(int argc, char *argv[]) {
  int       i, j, k;                   /* voxel index in x,y,z          */
  double    x0, y0, z0;                /* sphere center position        */
  double    x, y, z;                   /* current cell position         */
  double    cellsize = BOXSIZE/NDIV;   /* current cell size             */

  fprintf(stderr, "\n>> 24786  GEOMETRIC MODELING  PS4-1:VOXEL <<\n\n");

  /* Check if the number of arguments is correct */
  if (argc != 4){
    fprintf(stderr, "use: voxel x0 y0 z0 \n");
    exit(-1);
  }
  /* set sphere's center */
  x0 = atof(argv[1]);  y0 = atof(argv[2]);  z0 = atof(argv[3]);
  X0 = x0; X1 = y0; X2 = z0;
  /* open the target VRML file, "voxel.wrl" */
  fp = fopen("voxel.wrl", "w");

  fprintf(fp, "#VRML V2.0 utf8\n\n");
  /* draw the cube and the sphere */
  fprintf(fp, "Background { skyColor 1 1 1 }\n");
  fprintf(fp, "NavigationInfo { type \"EXAMINE\"}\n");

  fprintf(fp, "Shape {\n");
  fprintf(fp, "\tappearance Appearance { material Material { diffuseColor 0 0 1 }}\n");
  fprintf(fp, "\tgeometry Box { size %lf %lf %lf}\n",WIDTH, HEIGHT, DEPTH);
  fprintf(fp, "}\n");

  fprintf(fp, "Transform {\n");
  fprintf(fp, "\ttranslation %lf %lf %lf\n",x0,y0,z0);
  fprintf(fp, "\tchildren Shape {\n");
  fprintf(fp, "\t\tgeometry Sphere { radius %lf }\n", RADIUS);
  fprintf(fp, "\t\tappearance Appearance { material Material { diffuseColor 1 0 0 }}\n");
  fprintf(fp, "\t}\n");
  fprintf(fp, "}\n");

  fprintf(fp, "Transform {\n");
  fprintf(fp, "\ttranslation 0.0 %lf 0.0\n",1.5*BOXSIZE);
  fprintf(fp, "\tchildren [\n");

  //Creating a root node
  struct cell *firstCell = malloc(sizeof(struct cell));

  
  firstCell->cellsize = BOXSIZE;
  firstCell->startX = BOXPOSX;
  firstCell->startY = BOXPOSY;
  firstCell->startZ = BOXPOSZ;
  firstCell->depth = 0;

  struct octree *thisOctree = malloc (sizeof(struct octree));

  thisOctree->root = firstCell;

  encodeOctTree(firstCell);

  fprintf(fp, "\t]\n");  // close children
  fprintf(fp, "}\n");      // close Transform


  /* close the target VRML file "output.wrl" */
  fclose(fp);
}

int determineCoverage(x,y,z){

  //printf("Inside determine coverage\n");
  int incube = in_cube(x,y,z);
  int insphere = in_sphere (x,y,z, X0, X1, X2);

  if (incube && insphere)
    return 2;


  if ((incube && !insphere))
    return 1;

  if (!incube && insphere)
    return 3;

  return 0;

}

int isincube(int vert){
 if (vert==1 || vert==2)
   return 1;
 return 0;

}

int subdivide (struct cell* thisCell){
  // If all the 8 corners are outside but center is inside something then subdivide
  // If partial then subdivide
  // If all 8 corners are inside sphere or all 8 are in cube then leave as it is

  //Here 0 stands for outside it all, 1 stands for cube only , 3 for sphere only, 2 inside both
 
  
  int vert1 = -1, vert2 = -1, vert3 = -1, vert4 = -1, vert5 = -1, vert6 = -1, vert7 = -1, vert8 = -1, vert9 = -1;
  double x, y, z;
  
  //printf("Inside subdivide\n");
  x = thisCell->startX;
  y = thisCell->startY;
  z = thisCell->startZ;

  vert1 = determineCoverage(x,y,z);
  //printf("vert1 %d\n",vert1);

  x = thisCell->startX + thisCell->cellsize;
  y = thisCell->startY;
  z = thisCell->startZ;

  vert2 = determineCoverage(x,y,z);
  //printf("vert2 %d\n",vert2);

  x = thisCell->startX + thisCell->cellsize;
  y = thisCell->startY + thisCell->cellsize;
  z = thisCell->startZ;

  vert3 = determineCoverage(x,y,z);
  //printf("vert3 %d\n",vert3);

  x = thisCell->startX;
  y = thisCell->startY + thisCell->cellsize;
  z = thisCell->startZ;

  vert4 = determineCoverage(x,y,z);
  //printf("vert4 %d\n",vert4);

  x = thisCell->startX + thisCell->cellsize;
  y = thisCell->startY;
  z = thisCell->startZ + thisCell->cellsize;
  vert5 = determineCoverage(x,y,z);
  //printf("vert5 %d\n",vert5);

  x = thisCell->startX;
  y = thisCell->startY + thisCell->cellsize;
  z = thisCell->startZ + thisCell->cellsize;
  vert6 = determineCoverage(x,y,z);
  //printf("vert6 %d\n",vert6);
  
  x = thisCell->startX + thisCell->cellsize;
  y = thisCell->startY + thisCell->cellsize;
  z = thisCell->startZ + thisCell->cellsize;
  vert7 = determineCoverage(x,y,z);
  //printf("vert7 %d\n",vert7);

  x = thisCell->startX;
  y = thisCell->startY;
  z = thisCell->startZ + thisCell->cellsize;
  vert8 = determineCoverage(x,y,z);
  //printf("vert8 %d\n",vert8);
  
  x = thisCell->startX + 0.5*thisCell->cellsize;
  y = thisCell->startY + 0.5*thisCell->cellsize;
  z = thisCell->startZ + 0.5*thisCell->cellsize;
  vert9 = determineCoverage(x,y,z);
  //printf("vert9 %d\n",vert9);

  //if 8 corners outside and midpoint is outside then dont subdivide, dont display
  if (vert1 == 0 && vert2 ==0 && vert3 == 0 && vert4 ==0 && vert5 ==0 && vert6 ==0 && vert7 ==0 && vert8 == 0 && vert9==0){
    thisCell->code = 'e';
    return 2;
  }

  //if all are inside only sphere dont subdivide and dont display
  if (vert1 == 3  && vert2 == 3 && vert3 == 3 && vert4 ==3 && vert5 ==3 && vert6 ==3 && vert7 ==3 && vert8 == 3 && vert9==3){
    thisCell->code = 'e';
    return 2;
  }

  //if all are inside cube alone dont subdivide but display
  if (vert1 == 1  && vert2 == 1 && vert3 == 1 && vert4 == 1 && vert5 == 1 && vert6 == 1 && vert7 == 1 && vert8 == 1 && vert9 == 1){
    thisCell->code = 'f';
    return 0;
  }

  //If all are inside both then dont subdivide and dont display
  if (vert1 == 3  && vert2 == 3 && vert3 == 3 && vert4 ==3 && vert5 ==3 && vert6 ==3 && vert7 ==3 && vert8 == 3 && vert9==3){
    thisCell->code = 'e';
    return 2;
  }

  //If it is is last depth stage, only verify the center of the box. If it is inside the cube and in the sphere, then parital. else it is z.

  if (isincube(vert1) && isincube(vert2) && isincube(vert3) && isincube(vert4) && isincube(vert5) && isincube(vert6) && isincube(vert7) && isincube(vert8)){
    if (thisCell->depth == MAXDEPTH && (vert9==1) && (vert1==2 || vert2==2 || vert3 == 2 || vert4 == 2 || vert5 == 2 || vert6 == 2 || vert7 == 2 || vert8 == 2)){
      printf("MAXDEPTH %f %f %f\n",x,y,z);
      thisCell->code = 'p';
      return 1;
    }
  }
  //in any other case subdivide and assign z
  thisCell->code = 'z';
  return 1;
}



/*
 * Check if the point is inside the cube. Return 1 if inside, 0 if outside.
 */

int in_cube(double x, double y, double z){
  if (x < CUBX1 || CUBX2 < x || y < CUBY1 || CUBY2 < y
                || z < CUBZ1 || CUBZ2 < z)
     return 0;
  else return 1;
}

/*
 * Check if the point is inside the sphere. Return 1 if inside, 0 if outside.
 */
int in_sphere(double x, double y, double z, double x0, double y0, double z0){
  if ( ((x-x0)*(x-x0) + (y-y0)*(y-y0) + (z-z0)*(z-z0) ) < RADIUS2 )
     return 1;
  else return 0;
}

void WriteToFile(double x, double y, double z, double cellsize, int depth, int ispartial){
  double transX, transY, transZ;

  transX = x + cellsize/2.0;
  transY = y + cellsize/2.0;
  transZ = z + cellsize/2.0;


  fprintf(fp, "\tTransform {\n");
  fprintf(fp, "\t\ttranslation %lf %lf %lf\n",transX,transY,transZ);
  fprintf(fp, "\t\tchildren Shape {\n");
  if (depth == MAXDEPTH && ispartial){
    fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 0.8 0.8 0.8 }}\n");
  }
  else if (depth == 1)
    fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 0 0 1 }}\n");
  else if (depth == 2)
    fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 1 0 0 }}\n");

  else if (depth == 3)
    fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 0 1 0 }}\n");

  else if (depth == 4)
    fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 1 0 1 }}\n");

  else 
    fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 1 1 0 }}\n");

  fprintf(fp, "\t\t\tgeometry Box {size %lf %lf %lf}\n",0.9*cellsize,0.9*cellsize,0.9*cellsize);
  fprintf(fp, "\t\t}\n");
  fprintf(fp, "\t},\n");
}

