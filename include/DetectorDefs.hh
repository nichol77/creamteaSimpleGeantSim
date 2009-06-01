#ifndef DETECTORDEFS_HH
#define DETECTORDEFS_HH

//Size of the world
#define WORLD_SIZE 15

//Vertical Separation in m
#define VERTICAL_SEPARATION 3

// Long side length given in m
#define SIDELENGTH 13

// Short side length given in m
#define SHORT_SIDELENGTH 3

//Number of planes per detector stack
#define PLANES_PER_SIDE 8

//Number of strips per plane
#define STRIPS_PER_PLANE 650

//Some definitions for the MINERVA style planes
#define SCINT_TRIANGLE_HEIGHT_CM 2
#define SCINT_TRIANGLE_BASE_CM 2

//Gap between planes in cm
#define GAP_BETWEEN_PLANES_CM 10

//Plane width in cm
#define PLANE_WIDTH_CM 1

//Rotate each plane by 90??
#define ROTATE_EVERY_PLANE 1

// background if true only an empty room is imaged
#define BACKGROUND 0
#define SPHERE_RADIUS_CM 30
#define SPHERE_DENSITY_KG_M3 7800
#define SPHERE_X_M 0
#define SPHERE_Y_M 0
#define SPHERE_Z_M 0


#endif
