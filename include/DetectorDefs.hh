#ifndef DETECTORDEFS_HH
#define DETECTORDEFS_HH

//Size of the world
#define WORLD_SIZE 15

//Vertical Separation in m
#define VERTICAL_SEPARATION 13

// Long side length given in m
#define SIDELENGTH 13

// Short side length given in m
#define SHORT_SIDELENGTH 3

//Number of planes per detector stack
#define PLANES_PER_SIDE 8

//Number of strips per plane
#define STRIPS_PER_PLANE 650  //Was 650

//Some definitions for the MINERVA style planes
#define SCINT_TRIANGLE_HEIGHT_MM 17
#define SCINT_TRIANGLE_BASE_MM 33

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
#define STEEL_BOX 1
#define SPHERE_RADIUS_CM 10
#define SPHERE_DENSITY_KG_M3 19050
#define SPHERE_X_M 0.5
#define SPHERE_Y_M 1
#define SPHERE_Z_M 0.5
#define WATER_BOX_HALF_SIDE_CM 25
#define STEEL_BOX_X_M -0.5
#define STEEL_BOX_Y_M 3
#define STEEL_BOX_Z_M -0.5
#define STEEL_BOX_HALF_SIDE_CM 25
#define STEEL_THICKNESS_CM 1




#endif
