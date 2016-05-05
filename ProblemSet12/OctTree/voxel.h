/*
 *                 24786  GEOMETRIC MODELING
 *                 Carnegie Mellon University
 *                           VOXEL
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * constants
 */

#define BOXPOSX  (-10.0)       /* x position of voxel box          */
#define BOXPOSY  (-10.0)       /* y position of voxel box          */
#define BOXPOSZ  (-10.0)       /* z position of voxel box          */
#define BOXSIZE  (20.0)        /* size of the voxel box            */
#define NDIV     (16)          /* number of division in x,y,z axes */

#define WIDTH    (18.0)        /* width of the cube (x direction)  */
#define HEIGHT   (10.0)        /* height of the cube (y direction) */
#define DEPTH    (12.0)        /* depth of the cube (z direction)  */

#define CUBX1    (-9.0)        /* min-x face of the cube           */
#define CUBX2     (9.0)        /* max-x face of the cube           */
#define CUBY1    (-5.0)        /* min-y face of the cube           */
#define CUBY2     (5.0)        /* max-y face of the cube           */
#define CUBZ1    (-6.0)        /* min-z face of the cube           */
#define CUBZ2     (6.0)        /* max-z face of the cube           */

#define RADIUS    (8.0)        /* radius of the sphere             */
#define RADIUS2  (64.0)        /* radius of the sphere **2         */

/*
 * function calls
 */


/* 
 * sample struct and types for octree
 * (optional: you do not need to use structs for doing this problem set.)
 */

 struct cell {
   char          code;        /* f:full, e:empty, p:partial       */ 
   struct cell   *oct[8];     /* Pointers to octant cells)        */
   double cellsize;
   int depth;
   double startX, startY, startZ;

 };

 struct octree {
   double  xc, yc, zc;        /* space of octree box)             */    
   double  boxsize;           /* size of the octree box)          */
   struct cell    *root;             /* root cell of the octree)         */
 };

int in_cube(double x, double y, double z);
int in_sphere(double x, double y, double z, double x0, double y0, double z0);

