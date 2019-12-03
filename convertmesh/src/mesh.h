/*
 * mesh.h
 *
 *  Created on: 26/06/2012
 *      Author: caroline
 */

#ifndef MESH_H_
#define MESH_H_

#include "matrix.h"

/*-----------------------------------------------------------------------------
                               RNG File Format
-----------------------------------------------------------------------------*/
#pragma pack(1)

#define RNG_SIGNATURE "RNG 1.0"
// masks for dword data extraction
#define RNGMSK_TYPE          0xC0000000
#define RNGMSK_NUMBER        0x3FFFFFFF
#define RNG_INVALID          0x00000000
#define RNG_OBJECT           0x40000000
#define RNG_PLANE            0x80000000

// range data calibration info
typedef struct {
   int     rangeRow;                   // range data number of rows
   int     rangeCol;                   // range data number of columns
   int     colorRow;                   // color data number of rows
   int     colorCol;                   // color data number of columns
   float   pitchX;                     // distance between adjacent pixels of the color CCD in the horizontal direction
   float   pitchY;                     // distance between adjacent pixels of the color CCD in the vertical direction
   float   focus;                      // focal length of the imaging lens
   float   centerX;                    // the 2-D position of the optical axis (the optical center) on the color CCD
   float   centerY;                    // ditto
   cPoint3 viewpoint;                  // the 3-D position of the center of the imaging lens
   cPoint3 interest;                   // the 3-D position of a point on the optical axis (the z-axis)
   cPoint3 xVector;                    // the 3-D vector indicating the horizontal direction of the color CCD
   cPoint3 yVector;                    // the 3-D vector indicating the upward vertical direction of the color CCD
   cPoint3 zVector;                    // the 3-D vector indicating the depth direction of the color CCD
   } tViewCalibr;

// plane detection info
typedef struct {
   cPoint3 orig;                       // plane origin (centroid of plane points)
   cPoint3 normal;                     // plane normal
   float   tolerance;                  // plane tolerance in mm (plane point if (point-orig) dot normal < tolerance)
   int     objPoints;                  // number of object points (above plane)
   int     planePoints;                // number of point in plane or below it
   } tPlaneInfo;

// file header
typedef struct {
   char signature[8];                  // RNG\x201.0\0
   tViewCalibr calibr;                 // calibration data
   tPlaneInfo  plane;                  // plane info
   int  dataSize;                      // size of the range data in bytes
   int  reserved[28];                  // reserved for future expansion
   } tRngHeader;

typedef struct {
	byte type;
	int num;
} tValidation;

// texture coord structure
typedef struct {
	float   u, v;                       // texture coordinates
} tVT;

// wedge structure
typedef struct {
   float   u, v;                       // texture coordinates
   cPoint3 n;                          // normal of the wedge
   cPoint3 p;                          // point coordinate of the wedge
   } tWedge;

// wedge colors structure
typedef struct {
   byte r;                             // red color of the wedge
   byte g;                             // green color of the wedge
   byte b;                             // blue color of the wedge
   byte a;                             // alpha value of the wedge
   } tWedgeColor;

class mesh {
public:
	int numWedges;
	int numFaces;
	tWedge *wedge;
	int *face;
	tWedgeColor *wColor;
	float extents;

	// material information
	float diffuseColor[4];
	float specularColor[4];
	float specularFactor;

	tRngHeader headerRng;
	byte  *data;

	mesh();
	int loadM(char *fileName);
	int loadM2(char *fileName);
	int loadRng(char *fileName);
	int loadTxt(char *fileName);
	int loadObj(char *fileName);

	int saveM3_m(char *fileName);
	int saveM3_m2(char *fileName);

	int saveRng(char *fileName);
	int saveObj(char *fileName);
	int saveTxt(char *fileName);
	int savePly(char *fileName);

	int getNumObj(char *fileName, int type);
	int readLineFile(FILE *hFile, char *str, int maxLen);
	void close(void);

	virtual ~mesh();
};

#endif /* MESH_H_ */
