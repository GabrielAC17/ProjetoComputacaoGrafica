/*
 * mesh.cpp
 *
 *  Created on: 26/06/2012
 *      Author: caroline
 */

#include "mesh.h"

mesh::mesh() {
wedge = NULL;
face = NULL;
wColor = NULL;
numWedges = 0;
numFaces = 0;
extents = 0.0f;
}
int mesh::loadM2(char *fileName)
{
static char str[256];
cPoint3 pMin, pMax, pCenter, pExt;
FILE  *hFile;
int   i, pt, red, green, blue;

// release previous data
this->close();

// load a mesh file, with vertices and faces
if( (hFile=fopen(fileName,"rt")) == NULL )
   {
   return 0;
   }

// read number of vertices
this->readLineFile(hFile, str, sizeof(str));
sscanf(str,"%d",&numWedges);
if( numWedges <= 0 )
   return 0;

// allocate memory for wedges
if( ((wedge =new tWedge[numWedges])      == NULL) ||
    ((wColor=new tWedgeColor[numWedges]) == NULL) )
   return 0;

// loop reading the wedges
pMin.set(MAX_FLOAT,MAX_FLOAT,MAX_FLOAT);
pMax.set(-MAX_FLOAT,-MAX_FLOAT,-MAX_FLOAT);
for(i=0; i<numWedges; i++)
   {
   this->readLineFile(hFile, str, sizeof(str));
   sscanf(str,"%f %f %f %f %f %f %d %d %d", &wedge[i].p.x, &wedge[i].p.y, &wedge[i].p.z, &wedge[i].n.x, &wedge[i].n.y, &wedge[i].n.z, &red, &green, &blue);
   wColor[i].r = (byte)red;
   wColor[i].g = (byte)green;
   wColor[i].b = (byte)blue;
   wColor[i].a = 255;
   }

// read number of faces
this->readLineFile(hFile, str, sizeof(str));
sscanf(str,"%d",&numFaces);
if( numFaces <= 0 )
   return 0;

// allocate memory for faces
if( (face=new int[numFaces*3]) == NULL )
   return 0;

// loop reading the faces
for(i=0, pt=0; i<numFaces; i++, pt+=3)
   {
   this->readLineFile(hFile, str, sizeof(str));
   sscanf(str,"%d %d %d", &face[pt], &face[pt+1], &face[pt+2]);

   assert( (face[pt]   >= 0) && (face[pt]   < numWedges) );
   assert( (face[pt+1] >= 0) && (face[pt+1] < numWedges) );
   assert( (face[pt+2] >= 0) && (face[pt+2] < numWedges) );

   }

// read material information
this->readLineFile(hFile, str, sizeof(str));
sscanf(str, "%d %d %d", &red, &green, &blue);
diffuseColor[0] = (float)red   / 255.0f;
diffuseColor[1] = (float)green / 255.0f;
diffuseColor[2] = (float)blue  / 255.0f;
diffuseColor[3] = 1.0f;
this->readLineFile(hFile, str, sizeof(str));
sscanf(str, "%d %d %d %f", &red, &green, &blue, &specularFactor);
specularColor[0] = (float)red   / 255.0f;
specularColor[1] = (float)green / 255.0f;
specularColor[2] = (float)blue  / 255.0f;
specularColor[3] = 1.0f;

// close the file
fclose(hFile);

return 1;
}

int mesh::loadM(char *fileName)
{
static char str[256];
cPoint3 pMin, pMax, pCenter, pExt;
FILE  *hFile;
int   i, pt, red, green, blue;


// release previous data
this->close();

// load a mesh file, with vertices and faces
if( (hFile=fopen(fileName,"rt")) == NULL )
   {
   sprintf(str,"Failure opening %s",fileName);
   return 0;
   }

// read number of vertices
this->readLineFile(hFile, str, sizeof(str));
sscanf(str,"%d",&numWedges);
if( numWedges <= 0 )
   return 0;

// allocate memory for wedges
if( (wedge=new tWedge[numWedges]) == NULL )
   return 0;

// loop reading the wedges
pMin.set(MAX_FLOAT,MAX_FLOAT,MAX_FLOAT);
pMax.set(-MAX_FLOAT,-MAX_FLOAT,-MAX_FLOAT);
for(i=0; i<numWedges; i++)
   {
   this->readLineFile(hFile, str, sizeof(str));
   sscanf(str,"%f %f %f %f %f %f %f %f", &wedge[i].p.x, &wedge[i].p.y, &wedge[i].p.z, &wedge[i].n.x, &wedge[i].n.y, &wedge[i].n.z, &wedge[i].u, &wedge[i].v);

   // calculate minimum and maximum extents
   if( wedge[i].p.x < pMin.x )
      pMin.x = wedge[i].p.x;
   if( wedge[i].p.x > pMax.x )
      pMax.x = wedge[i].p.x;
   if( wedge[i].p.y < pMin.y )
      pMin.y = wedge[i].p.y;
   if( wedge[i].p.y > pMax.y )
      pMax.y = wedge[i].p.y;
   if( wedge[i].p.z < pMin.z )
      pMin.z = wedge[i].p.z;
   if( wedge[i].p.z > pMax.z )
      pMax.z = wedge[i].p.z;
   }

// center the model
pExt    = (pMax-pMin);
extents = pExt.x;
if( pExt.y > extents )
   extents = pExt.y;
if( pExt.z > extents )
   extents = pExt.z;
pCenter = (pMax+pMin)*0.5f;
for(i=0; i<numWedges; i++)
   {
   wedge[i].p.x = (wedge[i].p.x-pCenter.x);
   wedge[i].p.y = (wedge[i].p.y-pCenter.y);
   wedge[i].p.z = (wedge[i].p.z-pCenter.z);
   }

// read number of faces
this->readLineFile(hFile, str, sizeof(str));
sscanf(str,"%d",&numFaces);
if( numFaces <= 0 )
   return 0;

// allocate memory for faces
if( (face=new int[numFaces*3]) == NULL )
   return 0;

// loop reading the faces
for(i=0, pt=0; i<numFaces; i++, pt+=3)
   {
   this->readLineFile(hFile, str, sizeof(str));
   sscanf(str,"%d %d %d", &face[pt], &face[pt+1], &face[pt+2]);
   assert( (face[pt]   >= 0) && (face[pt]   < numWedges) );
   assert( (face[pt+1] >= 0) && (face[pt+1] < numWedges) );
   assert( (face[pt+2] >= 0) && (face[pt+2] < numWedges) );
   }

// read material information
this->readLineFile(hFile, str, sizeof(str));
sscanf(str, "%d %d %d", &red, &green, &blue);
diffuseColor[0] = (float)red   / 255.0f;
diffuseColor[1] = (float)green / 255.0f;
diffuseColor[2] = (float)blue  / 255.0f;
diffuseColor[3] = 1.0f;
this->readLineFile(hFile, str, sizeof(str));
sscanf(str, "%d %d %d %f", &red, &green, &blue, &specularFactor);
specularColor[0] = (float)red   / 255.0f;
specularColor[1] = (float)green / 255.0f;
specularColor[2] = (float)blue  / 255.0f;
specularColor[3] = 1.0f;
//this->readLineFile(hFile, textureFile, sizeof(textureFile));

// close the file
fclose(hFile);

return 1;
}

int mesh::loadRng(char *fileName)
{
static char str[1024];
cBoundBox3 bb;
cPoint3    pAux, pExt;
FILE  *hFile;
byte *pt;
int   *flag;
dword code, curCount, curType;
float dz14, dz23;
int   i, j, curW, idx;
int   w1, w2, w3, w4;

int inval = 0;
int val = 0;
int plan = 0;

// load our RNG file (range image)
if( (hFile=fopen(fileName,"rb")) == NULL )
   {
   sprintf(str,"Failure opening %s",fileName);
   return 0;
   }

// read header and check its validity
fread(&headerRng, sizeof(headerRng), 1, hFile);
if( (memcmp(headerRng.signature, RNG_SIGNATURE, sizeof(headerRng.signature)) != 0) ||
    (headerRng.plane.objPoints <= 0) || (headerRng.dataSize <= 0)                  )
   {
   return 0;
   }

// allocate memory
numWedges = headerRng.plane.objPoints;
if( numWedges <= 0 )
   return 0;
wedge = new tWedge[headerRng.plane.objPoints];

flag = new int[headerRng.calibr.rangeRow*headerRng.calibr.rangeCol];

data = new byte[headerRng.dataSize];

if( (wedge == NULL) || (flag == NULL) || (data == NULL) )
   return 0;

// read RLE compressed data
fread(data, headerRng.dataSize, 1, hFile);
fclose(hFile);

// loop extracting the wedges, and building flags
memset(flag, 0xFF, sizeof(int)*headerRng.calibr.rangeRow*headerRng.calibr.rangeCol);
bb.reset();
curW = 0;
idx  = 0;
pt   = data;

while( idx < headerRng.calibr.rangeRow*headerRng.calibr.rangeCol )
	{
	// get current span
	code     = *((dword *)pt);
	pt      += sizeof(dword);
	curCount = (code & RNGMSK_NUMBER);
	curType  = (code & RNGMSK_TYPE);

	switch( curType ) {
	case RNG_INVALID:
		// nothing to do, just skip curCount positions
		idx += curCount;
		inval++;
		break;
	case RNG_PLANE:
		// we must skip curCount cPoint3 structures
		idx += curCount;
		pt  += (sizeof(cPoint3)*curCount);
		plan++;
		break;
	case RNG_OBJECT:
		val++;
		// extract wedges
		while( curCount != 0 )
			{
			pAux      = *((cPoint3 *)pt);
			pt       += sizeof(cPoint3);
			flag[idx] = curW;
			wedge[curW].p.set(pAux.z, pAux.x, pAux.y);
			wedge[curW].u = (idx % headerRng.calibr.rangeCol);
			wedge[curW].v = (idx / headerRng.calibr.rangeCol);
			bb.add(wedge[curW].p);

			curW++;
			idx++;
			curCount--;
			}
		break;
	}
	}

assert( curW == headerRng.plane.objPoints );
assert( idx == headerRng.calibr.rangeRow*headerRng.calibr.rangeCol );
assert( pt == (data + headerRng.dataSize) );

// calculate number of faces (according to flags)
numFaces = 0;
for(i=0; i<headerRng.calibr.rangeRow-1; i++)
	for(j=0; j<headerRng.calibr.rangeCol-1; j++)
		{
		idx  = (flag[i*headerRng.calibr.rangeCol+j]       != -1);
		idx += (flag[i*headerRng.calibr.rangeCol+j+1]     != -1);
		idx += (flag[(i+1)*headerRng.calibr.rangeCol+j]   != -1);
		idx += (flag[(i+1)*headerRng.calibr.rangeCol+j+1] != -1);
		if( idx == 4 )
			numFaces += 2;
		else if( idx == 3 )
			numFaces++;
		}

if( numFaces == 0 )
   return 0;

// allocate memory for faces
face = new int[numFaces*3];
if( face == NULL )
   return 0;

// loop creating the faces
idx = 0;
for(i=0; i<headerRng.calibr.rangeRow-1; i++)
	for(j=0; j<headerRng.calibr.rangeCol-1; j++)
		{
		w1  = flag[i*headerRng.calibr.rangeCol+j];
		w2  = flag[i*headerRng.calibr.rangeCol+j+1];
		w3  = flag[(i+1)*headerRng.calibr.rangeCol+j];
		w4  = flag[(i+1)*headerRng.calibr.rangeCol+j+1];
		if( (w1 != -1) && (w2 != -1) && (w3 != -1) && (w4 != -1) )
			{
			// generate 2 faces
			dz14 = fAbs(wedge[w1].p.x - wedge[w4].p.x);
			dz23 = fAbs(wedge[w2].p.x - wedge[w3].p.x);
			if( dz14 > dz23 )
            	{
				// edge in 23
				face[idx++] = w1;
				face[idx++] = w3;
				face[idx++] = w2;
				face[idx++] = w2;
				face[idx++] = w3;
				face[idx++] = w4;
            	}
			else // edge in 14
            	{
				face[idx++] = w1;
				face[idx++] = w3;
				face[idx++] = w4;
				face[idx++] = w1;
				face[idx++] = w4;
				face[idx++] = w2;
            	}
			}
      else if( (w1 == -1) && (w2 != -1) && (w3 != -1) && (w4 != -1) )
      	  {
    	  // generate 1 face
    	  face[idx++] = w2;
    	  face[idx++] = w3;
    	  face[idx++] = w4;
      	  }
      else if( (w1 != -1) && (w2 == -1) && (w3 != -1) && (w4 != -1) )
      	  {
    	  // generate 1 face
    	  face[idx++] = w1;
    	  face[idx++] = w3;
    	  face[idx++] = w4;
      	  }
      else if( (w1 != -1) && (w2 != -1) && (w3 == -1) && (w4 != -1) )
      	  {
    	  // generate 1 face
    	  face[idx++] = w1;
    	  face[idx++] = w4;
    	  face[idx++] = w2;
      	  }
      else if( (w1 != -1) && (w2 != -1) && (w3 != -1) && (w4 == -1) )
      	  {
    	  // generate 1 face
    	  face[idx++] = w1;
    	  face[idx++] = w3;
    	  face[idx++] = w2;
      	  }
		}

assert( idx == numFaces*3 );

printf("LoadRng: number of wedges = %d\n", numWedges);
/*
printf("dataSize: %d\n", headerRng.dataSize);
printf("inval: %d\n", inval);
printf("val: %d\n", val);
printf("plan: %d\n", plan);*/

// deallocate flags
delete[] flag;
return 1;
}

int mesh::loadObj(char *fileName)
{
FILE  *hFile;
static char str[256];
static char type[3];
static char barra[1];
int v1, vt1, v2, vt2, v3, vt3;
tVT *textCoord;
int numTextCoord = 0;
int num, numF;

if ( (hFile=fopen(fileName,"rt")) == NULL )
   return 0;

numWedges = getNumObj(fileName, 0);
printf("LoadObj: number of wedges = %d\n",numWedges);

numFaces = getNumObj(fileName, 1);
printf("LoadObj: number of faces = %d\n",numFaces);

numTextCoord = getNumObj(fileName, 2);
printf("LoadObj: number of texture coordinates = %d\n",numTextCoord);

if ( (numWedges <= 0) || (numFaces <= 0) || (numTextCoord <= 0))
   return 0;

/*
if (numWedges != numTextCoord)
	{
	printf("LoadObj: Error!\n");
	printf("Numero de coordenadas de textura diferente do numero de vertices.\n");
	printf("Remova os vertices nao referenciados no meshlab apos a edicao.\n");
	printf("Compare: [cat arquivo.obj | grep \"v \" | wc -l] == [cat arquivo.obj | grep \"vt \" | wc -l]\n");
	return 0;
	}
*/
wedge = new tWedge[numWedges];
textCoord = new tVT[numTextCoord];
face = new int[numFaces*3];

if ( (wedge == NULL) || (face == NULL) || (textCoord == NULL))
   return 0;

// Para o formato todos os v depois todos os vt

num = 0;
do {
	if ( !(readLineFile(hFile, str, sizeof(str))) )
		break;
	sscanf(str,"%s", type);
	if (strcmp(type, "v") == 0)
		{
		sscanf(str,"%s %f %f %f", type, &wedge[num].p.x, &wedge[num].p.y, &wedge[num].p.z);
		num++;
		}
} while (!(feof(hFile)));

assert(num == numWedges);
rewind(hFile);
num = 0;

do {
	if ( !(readLineFile(hFile, str, sizeof(str))) )
		break;
	sscanf(str,"%s", type);
	if (strcmp(type, "vt") == 0)
		{
		sscanf(str,"%s %f %f", type, &textCoord[num].u, &textCoord[num].v);
		num++;
		}
} while (!(feof(hFile)));

assert(num == numTextCoord);
rewind(hFile);
num = 0;
numF = 0;

do {
	if ( !(readLineFile(hFile, str, sizeof(str))) )
		break;
	sscanf(str,"%s", type);
	if (strcmp(type, "f") == 0)
		{
		sscanf(str,"%s %d%c%d %d%c%d %d%c%d",type, &v1, barra, &vt1, &v2, barra, &vt2, &v3, barra, &vt3);
		face[num] = v1-1;
		face[num+1] = v2-1;
		face[num+2] = v3-1;
		num += 3;
		numF++;
		wedge[v1-1].u = textCoord[vt1-1].u;
		wedge[v1-1].v = textCoord[vt1-1].v;
		wedge[v2-1].u = textCoord[vt2-1].u;
		wedge[v2-1].v = textCoord[vt2-1].v;
		wedge[v3-1].u = textCoord[vt3-1].u;
		wedge[v3-1].v = textCoord[vt3-1].v;
		}
} while (!(feof(hFile)));

assert(numF == numFaces);
fclose(hFile);
printf("LoadObj: done.\n");
return 1;
}

int mesh::loadTxt(char *fileName)
{
FILE  *hFile;

if( (hFile=fopen(fileName,"rt")) == NULL )
   return 0;

fread(&headerRng, sizeof(headerRng), 1, hFile);
fclose(hFile);

return 1;
}

int mesh::saveM3_m2(char *fileName)
{
FILE *hFile;
byte *data;
byte *ptData;
int i, pt, size;

dword *ptD;
sbyte *ptB; //signed byte
float *ptF;

cPoint3 pMin, pMax, pCenter, pExt;
pMin.set(MAX_FLOAT,MAX_FLOAT,MAX_FLOAT);
pMax.set(-MAX_FLOAT,-MAX_FLOAT,-MAX_FLOAT);
for(i=0; i<numWedges; i++)
   {
   // calculate minimum and maximum extents
   if( wedge[i].p.x < pMin.x )
      pMin.x = wedge[i].p.x;
   if( wedge[i].p.x > pMax.x )
      pMax.x = wedge[i].p.x;
   if( wedge[i].p.y < pMin.y )
      pMin.y = wedge[i].p.y;
   if( wedge[i].p.y > pMax.y )
      pMax.y = wedge[i].p.y;
   if( wedge[i].p.z < pMin.z )
      pMin.z = wedge[i].p.z;
   if( wedge[i].p.z > pMax.z )
      pMax.z = wedge[i].p.z;
   }

// center the model
pExt = (pMax-pMin);
extents = pExt.x;
if( pExt.y > extents )
   extents = pExt.y;
if( pExt.z > extents )
   extents = pExt.z;

pCenter = (pMax+pMin)*0.5f;
for(i=0; i<numWedges; i++)
   {
   wedge[i].p.x = (wedge[i].p.x-pCenter.x);
   wedge[i].p.y = (wedge[i].p.y-pCenter.y);
   wedge[i].p.z = (wedge[i].p.z-pCenter.z);
   }

size = sizeof(dword) + (numWedges*3*sizeof(float)) + (numWedges*3*sizeof(float))
	+ (numWedges*3*sizeof(sbyte)) + sizeof(dword) + (numFaces*3*sizeof(dword))
	+ sizeof(float);

data = new byte[size];
ptData = data;

// numWedges
ptD = (dword *) ptData;
*ptD = numWedges;
ptData += sizeof(dword);

for(i=0; i<numWedges; i++)
	{
	ptF = (float *) ptData;
	*ptF = wedge[i].p.x;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].p.y;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].p.z;
	ptData += sizeof(float);

	// normals
	ptF = (float *) ptData;
	*ptF = wedge[i].n.x;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].n.y;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].n.z;
	ptData += sizeof(float);

	//colors
	ptB = (sbyte *) ptData;
	*ptB = (sbyte) wColor[i].r;
	ptData += sizeof(sbyte);

	ptB = (sbyte *) ptData;
	*ptB = (sbyte) wColor[i].g;
	ptData += sizeof(sbyte);

	ptB = (sbyte *) ptData;
	*ptB = (sbyte) wColor[i].b;
	ptData += sizeof(sbyte);
	}

// numFaces
ptD = (dword *) ptData;
*ptD = numFaces;
ptData += sizeof(dword);

for (i=0, pt=0; i<numFaces; i++, pt+=3)
	{
	ptD = (dword *) ptData;
	*ptD = face[pt];
	ptData += sizeof(dword);

	ptD = (dword *) ptData;
	*ptD = face[pt+1];
	ptData += sizeof(dword);

	ptD = (dword *) ptData;
	*ptD = face[pt+2];
	ptData += sizeof(dword);
   }

ptF = (float *) ptData;
*ptF = extents;
ptData += sizeof(float);

if ( (hFile=fopen(fileName,"wb")) == NULL )
	return 0;

fwrite(data, size, 1, hFile);
fclose(hFile);

delete[] data;
return 1;
}

int mesh::saveM3_m(char *fileName)
{
FILE *hFile;
byte *data;
byte *ptData;
int i, pt, size;

dword *ptD;
float *ptF;

cPoint3 pMin, pMax, pCenter, pExt;
pMin.set(MAX_FLOAT,MAX_FLOAT,MAX_FLOAT);
pMax.set(-MAX_FLOAT,-MAX_FLOAT,-MAX_FLOAT);
for(i=0; i<numWedges; i++)
   {
   // calculate minimum and maximum extents
   if( wedge[i].p.x < pMin.x )
      pMin.x = wedge[i].p.x;
   if( wedge[i].p.x > pMax.x )
      pMax.x = wedge[i].p.x;
   if( wedge[i].p.y < pMin.y )
      pMin.y = wedge[i].p.y;
   if( wedge[i].p.y > pMax.y )
      pMax.y = wedge[i].p.y;
   if( wedge[i].p.z < pMin.z )
      pMin.z = wedge[i].p.z;
   if( wedge[i].p.z > pMax.z )
      pMax.z = wedge[i].p.z;
   }

// center the model
pExt = (pMax-pMin);
extents = pExt.x;
if( pExt.y > extents )
   extents = pExt.y;
if( pExt.z > extents )
   extents = pExt.z;

pCenter = (pMax+pMin)*0.5f;
for(i=0; i<numWedges; i++)
   {
   wedge[i].p.x = (wedge[i].p.x-pCenter.x);
   wedge[i].p.y = (wedge[i].p.y-pCenter.y);
   wedge[i].p.z = (wedge[i].p.z-pCenter.z);
   }

size = sizeof(dword) + (numWedges*3*sizeof(float)) + (numWedges*3*sizeof(float))
	+ (numWedges*2*sizeof(float)) + sizeof(dword) + (numFaces*3*sizeof(dword))
	+ sizeof(float);

data = new byte[size];
ptData = data;

// numWedges
ptD = (dword *) ptData;
*ptD = numWedges;
ptData += sizeof(dword);

for(i=0; i<numWedges; i++)
	{
	ptF = (float *) ptData;
	*ptF = wedge[i].p.x;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].p.y;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].p.z;
	ptData += sizeof(float);

	// normals
	ptF = (float *) ptData;
	*ptF = wedge[i].n.x;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].n.y;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].n.z;
	ptData += sizeof(float);

	//texture coordinates
	ptF = (float *) ptData;
	*ptF = wedge[i].u;
	ptData += sizeof(float);

	ptF = (float *) ptData;
	*ptF = wedge[i].v;
	ptData += sizeof(float);
	}

// numFaces
ptD = (dword *) ptData;
*ptD = numFaces;
ptData += sizeof(dword);

for (i=0, pt=0; i<numFaces; i++, pt+=3)
	{
	ptD = (dword *) ptData;
	*ptD = face[pt];
	ptData += sizeof(dword);

	ptD = (dword *) ptData;
	*ptD = face[pt+1];
	ptData += sizeof(dword);

	ptD = (dword *) ptData;
	*ptD = face[pt+2];
	ptData += sizeof(dword);
   }

ptF = (float *) ptData;
*ptF = extents;
ptData += sizeof(float);

if ( (hFile=fopen(fileName,"wb")) == NULL )
	return 0;

fwrite(data, size, 1, hFile);
fclose(hFile);

delete[] data;
return 1;
}


int mesh::saveRng(char *fileName)
{
int i, j, k, idx;

//para calcular dataSize
tValidation *v;
int ptV = 0; 	//ponteiro para andar em v

int ptImage = 0; 	//ponteiro para simular as posicoes em uma imagem

int numVal = 0; 	//numero de  de validos
int val = 0;		//numero de sequencia de invalidos

int numInval = 0;	//numero de invalidos
int inval = 0;	//numero de sequencia de invalidos

//para preencher o data
byte      *buf, *pt;
dword     *ptD;
cPoint3   *ptP;
FILE  *hFile;


if( (v=new tValidation[numWedges*2]) == NULL )
	return 0;

for (i=0; i<numWedges; i++){
	idx = (((int) wedge[i].v) * (headerRng.calibr.rangeCol)) + (((int) wedge[i].u));

	numInval = fAbs(ptImage - idx);

	if (numInval) { //temos um ou uma sequencia de invalidos

		if (numVal > 0) {	//se ja temos anteriormente um ou uma sequencia de validos -> fecha valido
			v[ptV].type = 1;
			v[ptV].num = numVal;
			ptV++;
			val++;
		}

		//fecha invalido
		v[ptV].type = 0;
		v[ptV].num = numInval;
		ptV++;
		inval++;
		numVal = 1;
	}
	else	//incrementa validos
		numVal++;

    // incrementa ponteiro que anda na imagem
	ptImage += numInval + 1;
}

//se a imagem termina um ou uma sequencia de validos -> fecha valido
if ( numVal > 0 ) {
	v[ptV].type = 1;
	v[ptV].num = numVal;
	ptV++;
	val++;
}

//se a imagem termina um ou uma sequencia de invalidos -> fecha invalido
if ( ptImage < headerRng.calibr.rangeRow*headerRng.calibr.rangeCol ){
	v[ptV].type = 0;
	v[ptV].num = fAbs(ptImage - (headerRng.calibr.rangeRow*headerRng.calibr.rangeCol));
	ptV++;
	inval++;
}

headerRng.dataSize = (inval+val)*sizeof(dword) + numWedges*(sizeof(cPoint3));
headerRng.plane.objPoints = numWedges;

printf("SaveRng: data size = %d\n", headerRng.dataSize);
/*
printf("dataSize: %d\n", headerRng.dataSize);
printf("inval: %d\n",inval);
printf("val: %d\n",val);*/

 // allocate memory for data
 if( (buf=new byte[headerRng.dataSize]) == NULL )
    return 0;

pt = buf;
ptD = (dword *)pt;
j = 0;

for (i=0; i<ptV; i++)
	{
	if (v[i].type == 0) //salva invalido
		{
		ptD = (dword *)pt;
		*ptD = (RNG_INVALID | v[i].num);
		pt += sizeof(dword);
		}
	else if (v[i].type == 1) //salva valido
		{
		ptD = (dword *)pt;
		*ptD = (RNG_OBJECT | v[i].num);
		pt += sizeof(dword);

		k = 0;
		while (k < v[i].num)
			{
			ptP = (cPoint3 *)pt;

			ptP->x = wedge[j].p.y;
			ptP->y = wedge[j].p.z;
			ptP->z = wedge[j].p.x;
			;
			pt += sizeof(cPoint3);
			k++;
			j++;
			}
		}
	}


if( (hFile=fopen(fileName,"wb")) == NULL )
	{
    delete[] buf;
    return 0;
    }
fwrite(&headerRng, sizeof(headerRng), 1, hFile);
fwrite(buf, headerRng.dataSize, 1, hFile);
fclose(hFile);

// deallocate buffer
delete[] buf;

printf("SaveRng: done.\n");
return 1;
}

int mesh::saveObj(char *fileName)
{

FILE *objFile;
int i,pt;

// Para o formato todos os v depois todos os vt
if( (objFile=fopen(fileName,"w")) == NULL )
	return 0;

for (i=0;i<numWedges;i++)
	{
	//save the (x,y,z) values
	fprintf(objFile, "v ");
	fprintf(objFile, "%f ", wedge[i].p.x);
	fprintf(objFile, "%f ", wedge[i].p.y);
	fprintf(objFile, "%f",  wedge[i].p.z);
	fprintf(objFile, "\n");
	}

for (i=0;i<numWedges;i++)
	{
	fprintf(objFile, "vt ");
	fprintf(objFile, "%f ", wedge[i].u);
	fprintf(objFile, "%f ", wedge[i].v);
	fprintf(objFile, "\n");
	}

for(i=0,pt=0;i<numFaces; i++,pt+=3)
	{
	fprintf(objFile, "f ");
	fprintf(objFile, "%d/%d ", face[pt]+1, face[pt]+1);
	fprintf(objFile, "%d/%d ", face[pt+1]+1, face[pt+1]+1);
	fprintf(objFile, "%d/%d", face[pt+2]+1, face[pt+2]+1);
	fprintf(objFile, "\n");
	}

fclose(objFile);

printf("SaveObj: number of wedges = %d\n",numWedges);
printf("SaveObj: number of faces = %d\n",numFaces);
return 1;
}

int mesh::savePly(char *fileName)
{
FILE *plyFile;
int i,pt;

if( (plyFile=fopen(fileName,"w")) == NULL )
	return 0;

fprintf(plyFile, "ply\n");
fprintf(plyFile, "format ascii 1.0\n");
fprintf(plyFile, "element vertex %d\n", numWedges);
fprintf(plyFile, "property float x\n");
fprintf(plyFile, "property float y\n");
fprintf(plyFile, "property float z\n");
fprintf(plyFile, "property float nx\n");
fprintf(plyFile, "property float ny\n");
fprintf(plyFile, "property float nz\n");
fprintf(plyFile, "property uchar red\n");
fprintf(plyFile, "property uchar green\n");
fprintf(plyFile, "property uchar blue\n");
fprintf(plyFile, "property uchar alpha\n");
fprintf(plyFile, "element face %d\n", numFaces);
fprintf(plyFile, "property list uchar int vertex_indices\n");
fprintf(plyFile, "end_header\n");

for (i=0;i<numWedges;i++)
	{
	//save the (x,y,z) values
	fprintf(plyFile, "%f %f %f %f %f %f %d %d %d %d\n", wedge[i].p.x, wedge[i].p.y, wedge[i].p.z, wedge[i].n.x, wedge[i].n.y, wedge[i].n.z, wColor[i].r, wColor[i].g, wColor[i].b, wColor[i].a);
	}

for(i=0,pt=0;i<numFaces; i++,pt+=3)
	{
	fprintf(plyFile, "3 %d %d %d\n", face[pt], face[pt+1], face[pt+2]);
	}

fclose(plyFile);

printf("SavePly: number of wedges = %d\n",numWedges);
printf("SavePly: number of faces = %d\n",numFaces);
return 1;
}


int mesh::saveTxt(char *fileName)
{
FILE  *hFile;

if( (hFile=fopen(fileName,"wt")) == NULL )
   return 0;

fwrite(&headerRng, sizeof(headerRng), 1, hFile);
fclose(hFile);

return 1;
}

int mesh::getNumObj(char *fileName, int type)
{
// type: 0-vertices; 1-faces; 2-vt

FILE  *hFile;
static char str[256];
static char tCompare[3];
static char compare[3];
int num = 0;

if ( (hFile=fopen(fileName,"rt")) == NULL )
   return 0;

switch (type) {
case 0:
	tCompare[0] = 'v'; tCompare[1] ='\0';
	break;
case 1:
	tCompare[0] = 'f'; tCompare[1] ='\0';
	break;
case 2:
	strcpy(tCompare,"vt"); tCompare[2] ='\0';
	break;
}

do {
	if ( !(readLineFile(hFile, str, sizeof(str))) )
		break;
	sscanf(str,"%s", compare);
	if (strcmp(compare,tCompare) == 0)
		num++;
} while (!(feof(hFile)));

fclose(hFile);
return num;
}

int mesh::readLineFile(FILE *hFile, char *str, int maxLen)
{
int i;

// read a line from a TXT file, skipping comments and ending \r\n
do {
   if( feof(hFile) )
      return 0;
   fgets(str, maxLen, hFile);
   }while( (str[0] == ';') || (str[0] == '#') || ( str[0] == '\n') );
str[maxLen-1] = '\0';

// search for any \r\n and strip it
for(i=0; (str[i] != '\r') && (str[i] != '\n') && (str[i] != '\0'); i++)
   ;
str[i] = '\0';

return 1;
}

void mesh::close(void)
{
if( wedge != NULL )
   delete[] wedge;
if( face != NULL )
   delete[] face;
if( wColor != NULL )
   delete[] wColor;

wedge      = NULL;
face       = NULL;
wColor     = NULL;
numWedges  = 0;
numFaces   = 0;
extents    = 0.0f;
}


mesh::~mesh() {
	// TODO Auto-generated destructor stub
}

