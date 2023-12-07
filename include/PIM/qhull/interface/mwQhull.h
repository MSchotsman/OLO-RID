/* Copyright 2020 The MathWorks, Inc. */
#ifndef _MWQHULL_H_
#define _MWQHULL_H_

#ifdef __cplusplus
extern "C" {
#endif

int computeConvexhulln(double* pts, int numDims, int numPts, const char* options);
int getNumConvhullTrias();
int produceConvexhull(int* tri, int numTrias, int nTriSize, double* vol);
int computeDelaunayn(double* pts, int numDims, int numPts, const char* options);
int getNumDelunayTrias();
int produceDelaunay(int* tri, int numTrias, int nTriSize);
int computeVoronoin(double* pts, int numDims, int numPts, const char* options);
void getVoronoiSize(int* numcenters, int* numvertices);
int populateVoronoiInfo(int nPts, double* v, int mSize, int nSize, const double infScalar);
int getNumNeighborsForCell(int i);
void getNeighborsForCell(int i, double* facetIds);
void freeVoronoiStructures();

int getQhullErrorStr(char errString[]);

int freeQhullMemory();

#ifdef __cplusplus
}
#endif

#endif
