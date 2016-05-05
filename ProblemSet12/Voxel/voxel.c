/*
 *                 24786  GEOMETRIC MODELING
 *                 Carnegie Mellon University
 *                          VOXEL
 */

#include "voxel.h"

main(int argc, char *argv[]) {
  int       i, j, k;                   /* voxel index in x,y,z          */
  FILE      *fp;                       /* target VRML file "voxel.wrl"  */
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

  /*
   *  visit each voxel and draw a cube if the voxel center is inside
   *  the solid defined as: Solid = Cube -* Sphere.
   */
  for(k=0; k<NDIV; k++){
    for(j=0; j<NDIV; j++){
      for(i=0; i<NDIV; i++){
        x = BOXPOSX + i*cellsize;
        y = BOXPOSY + j*cellsize;
        z = BOXPOSZ + k*cellsize;
        if ( in_cube(x,y,z) == 1 && in_sphere(x,y,z,x0,y0,z0) == 0 ) {
		  fprintf(fp, "\tTransform {\n");
		  fprintf(fp, "\t\ttranslation %lf %lf %lf\n",x,y,z);
		  fprintf(fp, "\t\tchildren Shape {\n");
		  fprintf(fp, "\t\t\tappearance Appearance { material Material { diffuseColor 0 0 1 }}\n");
		  fprintf(fp, "\t\t\tgeometry Box {size %lf %lf %lf}\n",
		      0.9*cellsize,0.9*cellsize,0.9*cellsize);
          fprintf(fp, "\t\t}\n");
          fprintf(fp, "\t},\n");
        }
      }
    }
  }

  fprintf(fp, "\t]\n");  // close children
  fprintf(fp, "}\n");      // close Transform


  /* close the target VRML file "output.wrl" */
  fclose(fp);
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








