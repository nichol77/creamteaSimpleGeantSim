#ifndef DETECTORDEFS_HH
#define DETECTORDEFS_HH
// At some point all of this will move into a steering file that feeds in
// to the static DataInput class and can then be changed without having 
// to recompile.


//Size of the world
#define WORLD_SIZE 15

//Vertical Separation in m
#define VERTICAL_SEPARATION 13
// Long side length given in m
#define SIDELENGTH 13
//Number of planes per detector stack
#define PLANES_PER_SIDE 8
//Number of strips per plane
#define STRIPS_PER_PLANE 650  //Was 650

//Some definitions for the MINERVA style planes
#define USE_MINERVA_STRIPS 1
#define SCINT_TRIANGLE_HEIGHT_MM 17
#define SCINT_TRIANGLE_BASE_MM 33
#define SCINT_Y_NUM_STRIPS 800
#define SCINT_Y_STRIP_LENGTH_M 13
#define SCINT_X_NUM_STRIPS 800
#define SCINT_X_STRIP_LENGTH_M 13


//Gap between planes in cm
#define GAP_BETWEEN_PLANES_CM 10

//Plane width in cm
#define PLANE_WIDTH_CM 1
//Rotate each plane by 90??
#define ROTATE_EVERY_PLANE 1


#define FAKE_CONTAINER 1 // Whether to simulate a fake box container or not
#define CONTAINER 0 // Whether to include the container or not
#define BACKGROUND 0 // background if true only, don't simulate target
#define WATER_TANK 0
#define STEEL_BOX 0
#define SPHERE_RADIUS_CM 10
#define SPHERE_DENSITY_KG_M3 19050
#define SPHERE_X_M 0.5
#define SPHERE_Y_M 1
#define SPHERE_Z_M 0.5
#define WATER_BOX_HALF_SIDE_CM 25
#define WATER_BOX_SIDE_THICKNESS_MM 5
#define STEEL_BOX_X_M -0.5
#define STEEL_BOX_Y_M 3
#define STEEL_BOX_Z_M -0.5
#define STEEL_BOX_HALF_SIDE_CM 25
#define STEEL_THICKNESS_CM 1




#endif
