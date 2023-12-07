/* Copyright 2020 The MathWorks, Inc. */

#include <stdio.h>
#include <stdlib.h>

#include "../src/libqhull/qhull_a.h"
#include "../src/libqhull/mem.h"
#include "../src/libqhull/qset.h"

#include "mwQhull.h"

static void orientSeedFacet(facetT* facet, int* tri, int k, int num_vx_per_facet) {

    vertexT *vertex, **vertexp;
    int lpr1, lpr2, ctr = 0;
    double det_val;
    double the_vxs[4];
    double pts[4][3];

    double point_id = 0;

    FOREACHvertex_(facet->vertices) {
        point_id = qh_pointid(vertex->point) + 1;
        for (lpr1 = 0; lpr1 < num_vx_per_facet - 1; lpr1++) {
            pts[ctr][lpr1] = vertex->point[lpr1];
        }
        the_vxs[ctr] = tri[facet->id + k * (ctr)];
        ctr++;
    }
    /* Translate the facet so the first point is located at the origin. */
    for (lpr2 = 1; lpr2 < ctr; lpr2++) {
        for (lpr1 = 0; lpr1 < num_vx_per_facet - 1; lpr1++) {
            pts[lpr2][lpr1] -= pts[0][lpr1];
        }
    }
    /* Orient the facets for 3 and 4 dimensions to be consistent with neighbors */
    if (num_vx_per_facet == 3) {
        /* using signed area of the facet to check the orientation */
        det_val = pts[1][0] * pts[2][1] - pts[2][0] * pts[1][1];
        if (det_val < 0) {
            for (lpr1 = 0; lpr1 < num_vx_per_facet; lpr1++) {
                tri[facet->id + k * (lpr1)] = (int)the_vxs[(num_vx_per_facet - 1) - lpr1];
            }
        }
    } else if (num_vx_per_facet == 4) {
        /* using signed volume of the facet to check the orientation */
        det_val = pts[1][0] * pts[2][1] * pts[3][2] - pts[1][0] * pts[3][1] * pts[2][2] -
                  pts[2][0] * pts[1][1] * pts[3][2] + pts[2][0] * pts[3][1] * pts[1][2] +
                  pts[3][0] * pts[1][1] * pts[2][2] - pts[3][0] * pts[2][1] * pts[1][2];
        if (det_val < 0) {
            tri[facet->id + k * (1)] = (int)the_vxs[2];
            tri[facet->id + k * (2)] = (int)the_vxs[1];
        }
    }
}

static void orientTriangle(unsigned this_tri_id, unsigned other_tri_id, int* tri, int k) {

    double this_vxs[3], other_vxs[3];
    int lpr1 = 0, lpr2 = 0;

    flagT reorient = False;

    for (lpr1 = 0; lpr1 < 3; lpr1++) {
        this_vxs[lpr1] = tri[this_tri_id + k * (lpr1)];
        other_vxs[lpr1] = tri[other_tri_id + k * (lpr1)];
    }

    for (lpr1 = 0; lpr1 < 3 && reorient == False; lpr1++) {
        for (lpr2 = 0; lpr2 < 3; lpr2++) {
            if (this_vxs[(lpr1)] == other_vxs[(lpr2)] &&
                this_vxs[((lpr1 + 1) % 3)] == other_vxs[((lpr2 + 1) % 3)]) {
                reorient = True;
            }
        }
    }

    if (reorient == True) {
        lpr2 = 2;
        for (lpr1 = 0; lpr1 < 3; lpr1++) {
            tri[other_tri_id + k * (lpr1)] = (int)other_vxs[lpr2 - lpr1];
        }
    }
}


static void orientTetrahedron(unsigned this_tet_id, unsigned other_tet_id, int* tri, int k) {
    /* Face codes for a tetrahedron */
    static const int face_code[4][3] = {{0, 1, 2}, {1, 0, 3}, {2, 1, 3}, {0, 2, 3}};

    double this_vxs[4], other_vxs[4];
    int lpr1 = 0, lpr2 = 0, lpr3 = 0;

    flagT reorient = False;

    for (lpr1 = 0; lpr1 < 4; lpr1++) {
        this_vxs[lpr1] = tri[this_tet_id + k * (lpr1)];
        other_vxs[lpr1] = tri[other_tet_id + k * (lpr1)];
    }

    for (lpr1 = 0; lpr1 < 4 && reorient == False; lpr1++) {
        for (lpr2 = 0; lpr2 < 4 && reorient == False; lpr2++) {
            for (lpr3 = 0; lpr3 < 3; lpr3++) {
                if (this_vxs[face_code[lpr1][0]] == other_vxs[face_code[lpr2][(lpr3)]] &&
                    this_vxs[face_code[lpr1][1]] == other_vxs[face_code[lpr2][((lpr3 + 1) % 3)]] &&
                    this_vxs[face_code[lpr1][2]] == other_vxs[face_code[lpr2][((lpr3 + 2) % 3)]]) {
                    reorient = True;
                }
            }
        }
    }

    if (reorient == True) {
        tri[other_tet_id + k * (1)] = (int)other_vxs[2];
        tri[other_tet_id + k * (2)] = (int)other_vxs[1];
    }
}

/* Perform a linear traversal to propagate orientations.
   Do not recurse, because it will exhaust the stack space. Variable k is the number of simplices in
   the mesh */
static void orientTriangulation(facetT* seed_facet, int* tri, int k, int num_vx_per_facet) {
    int num_facets = 0, looper;
    facetT *this_facet, *neighbor_facet, **facet_array;
    ridgeT *ridge, **ridgep;

    facet_array = (facetT**)(malloc(sizeof(facetT*) * k));
    qh visit_id++;

    if (seed_facet->id == 0) {
        /* Orient the seed_facet first using a geometric test.
           All other facets are oriented relative to this one
           using topological tests. */
        orientSeedFacet(seed_facet, tri, k, num_vx_per_facet);
    }
    facet_array[num_facets] = seed_facet;
    seed_facet->visitid = qh visit_id;
    num_facets++;
    for (looper = 0; looper < num_facets; looper++) {
        this_facet = facet_array[looper];
        qh_makeridges(this_facet);
        FOREACHridge_(this_facet->ridges) {
            neighbor_facet = otherfacet_(ridge, this_facet);
            if (neighbor_facet->good && neighbor_facet->visitid != qh visit_id) {
                neighbor_facet->visitid = qh visit_id;
                facet_array[num_facets] = neighbor_facet;
                num_facets++;
                if (num_vx_per_facet == 3) {
                    orientTriangle(this_facet->id, neighbor_facet->id, tri, k);
                } else if (num_vx_per_facet == 4) {
                    orientTetrahedron(this_facet->id, neighbor_facet->id, tri, k);
                }
            }
        }
    }
    free(facet_array);
}


int produceConvexhull(int* tri, int numv, int nTriSize, double* vol) {
    int i = 0, j;
    facetT* facet;
    vertexT *vertex, **vertexp;
    setT* vertices;

    qh NOerrexit = False;
    qh_getarea(qh facet_list);
    qh_findgood_all(qh facet_list);
    FORALLfacet_(qh facet_list) {
        if ((qh_skipfacet(facet)) || (facet->visible && qh NEWfacets)) {
            continue;
        }
        j = 0;
        if (qh hull_dim == 3) {
            vertices = qh_facet3vertex(facet);
            FOREACHvertex_(vertices) {
                if (i + numv * j >= numv * nTriSize) {
                    return -1;
                }
                tri[i + numv * j++] = qh_pointid(vertex->point) + 1;
            }
        } else {
            FOREACHvertexreverse12_(facet->vertices) {
                if (i + numv * j >= numv * nTriSize) {
                    return -1;
                }
                tri[i + numv * j++] = qh_pointid(vertex->point) + 1;
            }
        }
        i++;
        if (i >= numv) {
            break;
        }
    }
    vol[0] = qh totvol;
    qh NOerrexit = True;

    return 0;
}

static int runQhull(double* pts, int numDims, int numPts) {
    boolT ismalloc = False;
    int exitcode = setjmp(qh errexit);
    if (exitcode) {
        return exitcode;
    }

    qh NOerrexit = False;
    qh_initflags(qh qhull_command);
    if (qh DELAUNAY) {
        qh PROJECTdelaunay = True;
    }

    qh_init_B(pts, numPts, numDims, ismalloc);
    qh_qhull();
    qh_check_output();

    if (qh VORONOI) {
        qh_clearcenters(qh_ASvoronoi);
        qh_vertexneighbors();
    }
    if (qh TRIangulate) {
        qh_triangulate();
        if (qh VERIFYoutput && !qh CHECKfrequently) {
            qh_checkpolygon(qh facet_list);
        }
    }
    qh_findgood_all(qh facet_list);
    qh_getarea(qh facet_list);
    qh NOerrexit = True;
    return 0;
}

int computeConvexhulln(double* pts, int numDims, int numPts, const char* options) {
    qh_meminit(stderr);
    qh_initqhull_start(stdin, stdout, stderr);
    strcpy(qh qhull_command, "qhull ");
    strcat(qh qhull_command, options);
    int retval = runQhull(pts, numDims, numPts);

    return retval;
}

int getNumConvhullTrias() {
    int numTrias = 0;
    int numfacets;
    int numsimplicial, totneighbors, numridges, numcoplanars, numtricoplanarsp;

    qh NOerrexit = False;
    qh_countfacets(qh facet_list, NULL, !qh_ALL, &numfacets, &numsimplicial, &totneighbors,
                   &numridges, &numcoplanars, &numtricoplanarsp);
    qh NOerrexit = True;

    if (qh hull_dim <= 3) {
        numTrias = numfacets;
    } else {
        numTrias = numsimplicial + numridges;
    }
    return numTrias;
}

int freeQhullMemory() {
    int curlong, totlong;

    qh_freeqhull(False);
    qh_memfreeshort(&curlong, &totlong);
    if (curlong || totlong) {
        return -1;
    }

    return 0;
}

int produceDelaunay(int* tri, int numTrias, int nTriSize) {
    int i = 0, j;
    vertexT *vertex, **vertexp;
    facetT *facet, *seed_facet = 0;

    FORALLfacet_(qh facet_list) {
        if (facet->good) {
            j = 0;
            if (i >= numTrias) {
                return -1;
            }
            FOREACHvertex_(facet->vertices) {
                if (j >= nTriSize) {
                    return -2;
                }
                tri[i + numTrias * (j++)] = qh_pointid(vertex->point) + 1;
            }
            facet->id = i;
            if (i == 0) {
                seed_facet = facet;
            }
            i++;
        }
    }

    if ((nTriSize == 3 || nTriSize == 4) && seed_facet) {
        /* Orient the triangles and tetrahedra so that they are consistent */
        /* All triangles having positive area, all tets having positive volume */
        orientTriangulation(seed_facet, tri, numTrias, nTriSize);
    }
    return 0;
}

int computeDelaunayn(double* pts, int numDims, int numPts, const char* options) {
    qh_meminit(stderr);
    qh_initqhull_start(stdin, stdout, stderr);
    strcpy(qh qhull_command, "qhull d ");
    strcat(qh qhull_command, options);
    int retval = runQhull(pts, numDims, numPts);

    return retval;
}

int getNumDelunayTrias() {
    int numTrias = 0;
    int numfacets = 0;
    int numsimplicial, totneighbors, numridges, numcoplanars, numtricoplanarsp;

    qh NOerrexit = False;
    qh_countfacets(qh facet_list, NULL, !qh_ALL, &numfacets, &numsimplicial, &totneighbors,
                   &numridges, &numcoplanars, &numtricoplanarsp);
    qh NOerrexit = True;

    if (qh hull_dim <= 3) {
        numTrias = numfacets;
    } else {
        numTrias = numsimplicial + numridges;
    }

    return numTrias;
}

int computeVoronoin(double* pts, int numDims, int numPts, const char* options) {
    qh_meminit(stderr);
    qh_initqhull_start(stdin, stdout, stderr);
    strcpy(qh qhull_command, "qhull v ");
    strcat(qh qhull_command, options);
    int retval = runQhull(pts, numDims, numPts);

    return retval;
}

static void getVoronoiCenter(facetT* facet, double* vor, int numvor, int nVorSize, int* vct) {
    int k, num;

    if (qh CENTERtype != qh_ASvoronoi && qh CENTERtype != qh_AScentrum) {
        return;
    }

    num = qh hull_dim - 1;
    if (!facet->normal || !facet->upperdelaunay || !qh ATinfinity) {
        if (!facet->center) {
            facet->center = qh_facetcenter(facet->vertices);
        }

        for (k = 0; k < num; k++) {
            vor[(*vct) + k * numvor] = facet->center[k];
        }
        *vct = *vct + 1;
    }
    return;
}

void getVoronoiSize(int* numcenters, int* numvertices) {
    setT* vertices = NULL;
    boolT is_lower = False;
    vertices = qh_markvoronoi(qh facet_list, NULL, !qh_ALL, &is_lower, numcenters);

    int vertex_i, vertex_n;
    vertexT* vertex = NULL;
    *numvertices = 0;
    FOREACHvertex_i_(vertices) {
        if (vertex) {
            *numvertices = *numvertices + 1;
        }
    }

    return;
}

double** voronoiCells;
int* numVoronoiNeighbors;
int voronoiAllocSize;

int populateVoronoiInfo(int nPts, double* v, int mSize, int nSize, const double infScalar) {

    int k, numcenters, numneighbors, numinf, vertex_i, vertex_n;
    facetT *facet, *neighbor, **neighborp;
    setT* vertices;
    vertexT* vertex;    
    boolT is_lower;
    unsigned int numfacets = (unsigned int)qh num_facets;

    int vct = 0;

    vertices = qh_markvoronoi(qh facet_list, NULL, !qh_ALL, &is_lower, &numcenters);
    
    int mn = mSize * nSize;
    for (k = 0; k < qh hull_dim - 1; k++) {
        if (k*numcenters >= mn) {
            return -1;
        }
        v[k * numcenters] = infScalar;
    }
    vct++;

    FORALLfacet_(qh facet_list) {
        if (facet->visitid && facet->visitid < numfacets) {
            getVoronoiCenter(facet, v, numcenters, mSize * nSize, &vct);
        }
    }
    vct = 0;

    voronoiCells = (double**)(malloc(sizeof(double*) * nPts));
    numVoronoiNeighbors = (int*)(malloc(sizeof(int) * nPts));
    voronoiAllocSize = nPts;

    FOREACHvertex_i_(vertices) {
        numneighbors = 0;
        numinf = 0;

        if (vertex) {
            if (qh hull_dim == 3) {
                qh_order_vertexneighbors(vertex);
            } else if (qh hull_dim >= 4) {
                qsort(SETaddr_(vertex->neighbors, vertexT), qh_setsize(vertex->neighbors),
                      sizeof(facetT*), qh_compare_facetvisit);
            }
            FOREACHneighbor_(vertex) {
                if (neighbor->visitid == 0) {
                    numinf = 1;
                } else if (neighbor->visitid < numfacets) {
                    numneighbors++;
                }
            }
        }
        if (numinf) {
            numneighbors++;
        }
        if (vertex) {
            voronoiCells[vct] = (double*)malloc(sizeof(double) * numneighbors);
            k = 0;
            FOREACHneighbor_(vertex) {
                if (neighbor->visitid == 0) {
                    if (numinf) {
                        numinf = 0;
                        if (k >= numneighbors) {
                            return -2;
                        }
                        voronoiCells[vct][k++] = neighbor->visitid + 1;
                    }
                } else if (neighbor->visitid < numfacets) {
                    if (k >= numneighbors) {
                        return -2;
                    }
                    voronoiCells[vct][k++] = neighbor->visitid + 1;
                }
            }
            numVoronoiNeighbors[vct++] = k;
        }
    }
    qh_settempfree(&vertices);
    vct = 0;
    return 0;
}

int getNumNeighborsForCell(int i) {
    return numVoronoiNeighbors[i];
}

void getNeighborsForCell(int vertexId, double* facetIds) {
    for (int it = 0; it < numVoronoiNeighbors[vertexId]; it++) {
        facetIds[it] = voronoiCells[vertexId][it];
    }
    return;
}

void freeVoronoiStructures() {
    free(numVoronoiNeighbors);
    for (int it = 0; it < voronoiAllocSize && voronoiCells[it] != NULL; it++) {
        free(voronoiCells[it]);
    }
    free(voronoiCells);
    numVoronoiNeighbors = NULL;
    voronoiCells = NULL;
    voronoiAllocSize = 0;
    return;
}

int getQhullErrorStr(char errString[]) {
    strncpy(errString, qh mwerrmsg, qh_buflen);
    return strlen(errString);
}
