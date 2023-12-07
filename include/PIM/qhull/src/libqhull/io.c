/*<html><pre>  -<a                             href="qh-io.htm"
  >-------------------------------</a><a name="TOP">-</a>

   io.c
   Input/Output routines of qhull application

   see qh-io.htm and io.h

   see user.c for qh_errprint and qh_printfacetlist

   unix.c calls qh_readpoints and qh_produce_output

   unix.c and user.c are the only callers of io.c functions
   This allows the user to avoid loading io.o from qhull.a

   copyright (c) 1993-2010 The Geometry Center.
   $Id: //product/qhull/main/rel/src/io.c#38 $$Change: 1179 $
   $DateTime: 2010/01/12 19:53:15 $$Author: bbarber $
*/

/* MathWorks has made shortcircuited several of the functions in this
 * file.  Since we want to provide our own io using other MATLAB functions
 * the io is short circuited here.  To accomplish this, the functions in
 * question are typically empty, or simply return 0;  */
#include "qhull_a.h"

/*========= -functions in alphabetical order after qh_produce_output()  =====*/

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="produce_output">-</a>

  qh_produce_output()
  qh_produce_output2()
    prints out the result of qhull in desired format
    qh_produce_output2() does not call qh_prepare_output()
    if qh.GETarea
      computes and prints area and volume
    qh.PRINTout[] is an array of output formats

  notes:
    prints output in qh.PRINTout order
*/
void qh_produce_output(void) {
    int tempsize= qh_setsize(qhmem.tempstack);

    qh_prepare_output();
    qh_produce_output2();
    if (qh_setsize(qhmem.tempstack) != tempsize) {
        qh_fprintf(qh ferr, 6206, "qhull internal error (qh_produce_output): temporary sets not empty(%d)\n",
            qh_setsize(qhmem.tempstack));
        qh_errexit(qh_ERRqhull, NULL, NULL);
    }
} /* produce_output */


void qh_produce_output2(void) {
  int i, tempsize= qh_setsize(qhmem.tempstack), d_1;

  if (qh PRINTsummary)
    qh_printsummary(qh ferr);
  else if (qh PRINTout[0] == qh_PRINTnone)
    qh_printsummary(qh fout);
  for (i=0; i < qh_PRINTEND; i++)
    qh_printfacets(qh fout, qh PRINTout[i], qh facet_list, NULL, !qh_ALL);
  qh_allstatistics();
  if (qh PRINTprecision && !qh MERGING && (qh JOGGLEmax > REALmax/2 || qh RERUN))
    qh_printstats(qh ferr, qhstat precision, NULL);
  if (qh VERIFYoutput && (zzval_(Zridge) > 0 || zzval_(Zridgemid) > 0))
    qh_printstats(qh ferr, qhstat vridges, NULL);
  if (qh PRINTstatistics) {
    qh_printstatistics(qh ferr, "");
    qh_memstatistics(qh ferr);
    d_1= sizeof(setT) + (qh hull_dim - 1) * SETelemsize;
    qh_fprintf(qh ferr, 8040, "\
    size in bytes: merge %d ridge %d vertex %d facet %d\n\
         normal %d ridge vertices %d facet vertices or neighbors %d\n",
            (int)sizeof(mergeT), (int)sizeof(ridgeT),
            (int)sizeof(vertexT), (int)sizeof(facetT),
            qh normal_size, d_1, d_1 + SETelemsize);
  }
  if (qh_setsize(qhmem.tempstack) != tempsize) {
    qh_fprintf(qh ferr, 6065, "qhull internal error (qh_produce_output2): temporary sets not empty(%d)\n",
             qh_setsize(qhmem.tempstack));
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
} /* produce_output2 */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="dfacet">-</a>

  dfacet( id )
    print facet by id, for debugging

*/
void dfacet(unsigned id) {
  facetT *facet;

  FORALLfacets {
    if (facet->id == id) {
      qh_printfacet(qh fout, facet);
      break;
    }
  }
} /* dfacet */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="dvertex">-</a>

  dvertex( id )
    print vertex by id, for debugging
*/
void dvertex(unsigned id) {
  vertexT *vertex;

  FORALLvertices {
    if (vertex->id == id) {
      qh_printvertex(qh fout, vertex);
      break;
    }
  }
} /* dvertex */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="compare_vertexpoint">-</a>

  qh_compare_vertexpoint( p1, p2 )
    used by qsort() to order vertices by point id
*/
int qh_compare_vertexpoint(const void *p1, const void *p2) {
  const vertexT *a= *((vertexT *const*)p1), *b= *((vertexT *const*)p2);

  return((qh_pointid(a->point) > qh_pointid(b->point)?1:-1));
} /* compare_vertexpoint */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="compare_facetarea">-</a>

  qh_compare_facetarea( p1, p2 )
    used by qsort() to order facets by area
*/
int qh_compare_facetarea(const void *p1, const void *p2) {
  const facetT *a= *((facetT *const*)p1), *b= *((facetT *const*)p2);

  if (!a->isarea)
    return -1;
  if (!b->isarea)
    return 1;
  if (a->f.area > b->f.area)
    return 1;
  else if (a->f.area == b->f.area)
    return 0;
  return -1;
} /* compare_facetarea */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="compare_facetmerge">-</a>

  qh_compare_facetmerge( p1, p2 )
    used by qsort() to order facets by number of merges
*/
int qh_compare_facetmerge(const void *p1, const void *p2) {
  const facetT *a= *((facetT *const*)p1), *b= *((facetT *const*)p2);

  return(a->nummerge - b->nummerge);
} /* compare_facetvisit */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="compare_facetvisit">-</a>

  qh_compare_facetvisit( p1, p2 )
    used by qsort() to order facets by visit id or id
*/
int qh_compare_facetvisit(const void *p1, const void *p2) {
  const facetT *a= *((facetT *const*)p1), *b= *((facetT *const*)p2);
  int i,j;

  if (!(i= a->visitid))
    i= 0 - a->id; /* do not convert to int, sign distinguishes id from visitid */
  if (!(j= b->visitid))
    j= 0 - b->id;
  return(i - j);
} /* compare_facetvisit */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="copyfilename">-</a>

  qh_copyfilename( dest, size, source, length )
    copy filename identified by qh_skipfilename()

  notes:
    see qh_skipfilename() for syntax
*/
void qh_copyfilename(char *filename, int size, const char* source, int length) {
  char c= *source;

  if (length > size + 1) {
      qh_fprintf(qh ferr, 6040, "qhull error: filename is more than %d characters, %s\n",  size-1, source);
      qh_errexit(qh_ERRinput, NULL, NULL);
  }
  strncpy(filename, source, length);
  filename[length]= '\0';
  if (c == '\'' || c == '"') {
    char *s= filename + 1;
    char *t= filename;
    while (*s) {
      if (*s == c) {
          if (s[-1] == '\\')
              t[-1]= c;
      }else
          *t++= *s;
      s++;
    }
    *t= '\0';
  }
} /* copyfilename */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="countfacets">-</a>

  qh_countfacets( facetlist, facets, printall,
          numfacets, numsimplicial, totneighbors, numridges, numcoplanar, numtricoplanars  )
    count good facets for printing and set visitid
    if allfacets, ignores qh_skipfacet()

  notes:
    qh_printsummary and qh_countfacets must match counts

  returns:
    numfacets, numsimplicial, total neighbors, numridges, coplanars
    each facet with ->visitid indicating 1-relative position
      ->visitid==0 indicates not good

  notes
    numfacets >= numsimplicial
    if qh.NEWfacets,
      does not count visible facets (matches qh_printafacet)

  design:
    for all facets on facetlist and in facets set
      unless facet is skipped or visible (i.e., will be deleted)
        mark facet->visitid
        update counts
*/
void qh_countfacets(facetT *facetlist, setT *facets, boolT printall,
    int *numfacetsp, int *numsimplicialp, int *totneighborsp, int *numridgesp, int *numcoplanarsp, int *numtricoplanarsp) {
  facetT *facet, **facetp;
  int numfacets= 0, numsimplicial= 0, numridges= 0, totneighbors= 0, numcoplanars= 0, numtricoplanars= 0;

  FORALLfacet_(facetlist) {
    if ((facet->visible && qh NEWfacets)
    || (!printall && qh_skipfacet(facet)))
      facet->visitid= 0;
    else {
      facet->visitid= ++numfacets;
      totneighbors += qh_setsize(facet->neighbors);
      if (facet->simplicial) {
        numsimplicial++;
        if (facet->keepcentrum && facet->tricoplanar)
          numtricoplanars++;
      }else
        numridges += qh_setsize(facet->ridges);
      if (facet->coplanarset)
        numcoplanars += qh_setsize(facet->coplanarset);
    }
  }

  FOREACHfacet_(facets) {
    if ((facet->visible && qh NEWfacets)
    || (!printall && qh_skipfacet(facet)))
      facet->visitid= 0;
    else {
      facet->visitid= ++numfacets;
      totneighbors += qh_setsize(facet->neighbors);
      if (facet->simplicial){
        numsimplicial++;
        if (facet->keepcentrum && facet->tricoplanar)
          numtricoplanars++;
      }else
        numridges += qh_setsize(facet->ridges);
      if (facet->coplanarset)
        numcoplanars += qh_setsize(facet->coplanarset);
    }
  }
  qh visit_id += numfacets+1;
  *numfacetsp= numfacets;
  *numsimplicialp= numsimplicial;
  *totneighborsp= totneighbors;
  *numridgesp= numridges;
  *numcoplanarsp= numcoplanars;
  *numtricoplanarsp= numtricoplanars;
} /* countfacets */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="detvnorm">-</a>

  qh_detvnorm( vertex, vertexA, centers, offset )
    compute separating plane of the Voronoi diagram for a pair of input sites
    centers= set of facets (i.e., Voronoi vertices)
      facet->visitid= 0 iff vertex-at-infinity (i.e., unbounded)

  assumes:
    qh_ASvoronoi and qh_vertexneighbors() already set

  returns:
    norm
      a pointer into qh.gm_matrix to qh.hull_dim-1 reals
      copy the data before reusing qh.gm_matrix
    offset
      if 'QVn'
        sign adjusted so that qh.GOODvertexp is inside
      else
        sign adjusted so that vertex is inside

    qh.gm_matrix= simplex of points from centers relative to first center

  notes:
    in io.c so that code for 'v Tv' can be removed by removing io.c
    returns pointer into qh.gm_matrix to avoid tracking of temporary memory

  design:
    determine midpoint of input sites
    build points as the set of Voronoi vertices
    select a simplex from points (if necessary)
      include midpoint if the Voronoi region is unbounded
    relocate the first vertex of the simplex to the origin
    compute the normalized hyperplane through the simplex
    orient the hyperplane toward 'QVn' or 'vertex'
    if 'Tv' or 'Ts'
      if bounded
        test that hyperplane is the perpendicular bisector of the input sites
      test that Voronoi vertices not in the simplex are still on the hyperplane
    free up temporary memory
*/
pointT *qh_detvnorm(vertexT *vertex, vertexT *vertexA, setT *centers, realT *offsetp) {
  facetT *facet, **facetp;
  int  i, k, pointid, pointidA, point_i, point_n;
  setT *simplex= NULL;
  pointT *point, **pointp, *point0, *midpoint, *normal, *inpoint;
  coordT *coord, *gmcoord, *normalp;
  setT *points= qh_settemp(qh TEMPsize);
  boolT nearzero= False;
  boolT unbounded= False;
  int numcenters= 0;
  int dim= qh hull_dim - 1;
  realT dist, offset, angle, zero= 0.0;

  midpoint= qh gm_matrix + qh hull_dim * qh hull_dim;  /* last row */
  for (k=0; k < dim; k++)
    midpoint[k]= (vertex->point[k] + vertexA->point[k])/2;
  FOREACHfacet_(centers) {
    numcenters++;
    if (!facet->visitid)
      unbounded= True;
    else {
      if (!facet->center)
        facet->center= qh_facetcenter(facet->vertices);
      qh_setappend(&points, facet->center);
    }
  }
  if (numcenters > dim) {
    simplex= qh_settemp(qh TEMPsize);
    qh_setappend(&simplex, vertex->point);
    if (unbounded)
      qh_setappend(&simplex, midpoint);
    qh_maxsimplex(dim, points, NULL, 0, &simplex);
    qh_setdelnth(simplex, 0);
  }else if (numcenters == dim) {
    if (unbounded)
      qh_setappend(&points, midpoint);
    simplex= points;
  }else {
    qh_fprintf(qh ferr, 6216, "qhull internal error (qh_detvnorm): too few points(%d) to compute separating plane\n", numcenters);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  i= 0;
  gmcoord= qh gm_matrix;
  point0= SETfirstt_(simplex, pointT);
  FOREACHpoint_(simplex) {
    if (qh IStracing >= 4)
      qh_printmatrix(qh ferr, "qh_detvnorm: Voronoi vertex or midpoint",
                              &point, 1, dim);
    if (point != point0) {
      qh gm_row[i++]= gmcoord;
      coord= point0;
      for (k=dim; k--; )
        *(gmcoord++)= *point++ - *coord++;
    }
  }
  qh gm_row[i]= gmcoord;  /* does not overlap midpoint, may be used later for qh_areasimplex */
  normal= gmcoord;
  qh_sethyperplane_gauss(dim, qh gm_row, point0, True,
                normal, &offset, &nearzero);
  if (qh GOODvertexp == vertexA->point)
    inpoint= vertexA->point;
  else
    inpoint= vertex->point;
  zinc_(Zdistio);
  dist= qh_distnorm(dim, inpoint, normal, &offset);
  if (dist > 0) {
    offset= -offset;
    normalp= normal;
    for (k=dim; k--; ) {
      *normalp= -(*normalp);
      normalp++;
    }
  }
  if (qh VERIFYoutput || qh PRINTstatistics) {
    pointid= qh_pointid(vertex->point);
    pointidA= qh_pointid(vertexA->point);
    if (!unbounded) {
      zinc_(Zdiststat);
      dist= qh_distnorm(dim, midpoint, normal, &offset);
      if (dist < 0)
        dist= -dist;
      zzinc_(Zridgemid);
      wwmax_(Wridgemidmax, dist);
      wwadd_(Wridgemid, dist);
      trace4((qh ferr, 4014, "qh_detvnorm: points %d %d midpoint dist %2.2g\n",
                 pointid, pointidA, dist));
      for (k=0; k < dim; k++)
        midpoint[k]= vertexA->point[k] - vertex->point[k];  /* overwrites midpoint! */
      qh_normalize(midpoint, dim, False);
      angle= qh_distnorm(dim, midpoint, normal, &zero); /* qh_detangle uses dim+1 */
      if (angle < 0.0)
        angle= angle + 1.0;
      else
        angle= angle - 1.0;
      if (angle < 0.0)
        angle -= angle;
      trace4((qh ferr, 4015, "qh_detvnorm: points %d %d angle %2.2g nearzero %d\n",
                 pointid, pointidA, angle, nearzero));
      if (nearzero) {
        zzinc_(Zridge0);
        wwmax_(Wridge0max, angle);
        wwadd_(Wridge0, angle);
      }else {
        zzinc_(Zridgeok)
        wwmax_(Wridgeokmax, angle);
        wwadd_(Wridgeok, angle);
      }
    }
    if (simplex != points) {
      FOREACHpoint_i_(points) {
        if (!qh_setin(simplex, point)) {
          facet= SETelemt_(centers, point_i, facetT);
          zinc_(Zdiststat);
          dist= qh_distnorm(dim, point, normal, &offset);
          if (dist < 0)
            dist= -dist;
          zzinc_(Zridge);
          wwmax_(Wridgemax, dist);
          wwadd_(Wridge, dist);
          trace4((qh ferr, 4016, "qh_detvnorm: points %d %d Voronoi vertex %d dist %2.2g\n",
                             pointid, pointidA, facet->visitid, dist));
        }
      }
    }
  }
  *offsetp= offset;
  if (simplex != points)
    qh_settempfree(&simplex);
  qh_settempfree(&points);
  return normal;
} /* detvnorm */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="detvridge">-</a>

  qh_detvridge( vertexA )
    determine Voronoi ridge from 'seen' neighbors of vertexA
    include one vertex-at-infinite if an !neighbor->visitid

  returns:
    temporary set of centers (facets, i.e., Voronoi vertices)
    sorted by center id
*/
setT *qh_detvridge(vertexT *vertex) {
  setT *centers= qh_settemp(qh TEMPsize);
  setT *tricenters= qh_settemp(qh TEMPsize);
  facetT *neighbor, **neighborp;
  boolT firstinf= True;

  FOREACHneighbor_(vertex) {
    if (neighbor->seen) {
      if (neighbor->visitid) {
        if (!neighbor->tricoplanar || qh_setunique(&tricenters, neighbor->center))
          qh_setappend(&centers, neighbor);
      }else if (firstinf) {
        firstinf= False;
        qh_setappend(&centers, neighbor);
      }
    }
  }
  qsort(SETaddr_(centers, facetT), (size_t)qh_setsize(centers),
             sizeof(facetT *), qh_compare_facetvisit);
  qh_settempfree(&tricenters);
  return centers;
} /* detvridge */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="detvridge3">-</a>

  qh_detvridge3( atvertex, vertex )
    determine 3-d Voronoi ridge from 'seen' neighbors of atvertex and vertex
    include one vertex-at-infinite for !neighbor->visitid
    assumes all facet->seen2= True

  returns:
    temporary set of centers (facets, i.e., Voronoi vertices)
    listed in adjacency order (!oriented)
    all facet->seen2= True

  design:
    mark all neighbors of atvertex
    for each adjacent neighbor of both atvertex and vertex
      if neighbor selected
        add neighbor to set of Voronoi vertices
*/
setT *qh_detvridge3 (vertexT *atvertex, vertexT *vertex) {
  setT *centers= qh_settemp(qh TEMPsize);
  setT *tricenters= qh_settemp(qh TEMPsize);
  facetT *neighbor, **neighborp, *facet= NULL;
  boolT firstinf= True;

  FOREACHneighbor_(atvertex)
    neighbor->seen2= False;
  FOREACHneighbor_(vertex) {
    if (!neighbor->seen2) {
      facet= neighbor;
      break;
    }
  }
  while (facet) {
    facet->seen2= True;
    if (neighbor->seen) {
      if (facet->visitid) {
        if (!facet->tricoplanar || qh_setunique(&tricenters, facet->center))
          qh_setappend(&centers, facet);
      }else if (firstinf) {
        firstinf= False;
        qh_setappend(&centers, facet);
      }
    }
    FOREACHneighbor_(facet) {
      if (!neighbor->seen2) {
        if (qh_setin(vertex->neighbors, neighbor))
          break;
        else
          neighbor->seen2= True;
      }
    }
    facet= neighbor;
  }
  if (qh CHECKfrequently) {
    FOREACHneighbor_(vertex) {
      if (!neighbor->seen2) {
          qh_fprintf(qh ferr, 6217, "qhull internal error (qh_detvridge3): neighbors of vertex p%d are not connected at facet %d\n",
                 qh_pointid(vertex->point), neighbor->id);
        qh_errexit(qh_ERRqhull, neighbor, NULL);
      }
    }
  }
  FOREACHneighbor_(atvertex)
    neighbor->seen2= True;
  qh_settempfree(&tricenters);
  return centers;
} /* detvridge3 */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="eachvoronoi">-</a>

  qh_eachvoronoi( fp, printvridge, vertex, visitall, innerouter, inorder )
    if visitall,
      visit all Voronoi ridges for vertex (i.e., an input site)
    else
      visit all unvisited Voronoi ridges for vertex
      all vertex->seen= False if unvisited
    assumes
      all facet->seen= False
      all facet->seen2= True (for qh_detvridge3)
      all facet->visitid == 0 if vertex_at_infinity
                         == index of Voronoi vertex
                         >= qh.num_facets if ignored
    innerouter:
      qh_RIDGEall--  both inner (bounded) and outer(unbounded) ridges
      qh_RIDGEinner- only inner
      qh_RIDGEouter- only outer

    if inorder
      orders vertices for 3-d Voronoi diagrams

  returns:
    number of visited ridges (does not include previously visited ridges)

    if printvridge,
      calls printvridge( fp, vertex, vertexA, centers)
        fp== any pointer (assumes FILE*)
        vertex,vertexA= pair of input sites that define a Voronoi ridge
        centers= set of facets (i.e., Voronoi vertices)
                 ->visitid == index or 0 if vertex_at_infinity
                 ordered for 3-d Voronoi diagram
  notes:
    uses qh.vertex_visit

  see:
    qh_eachvoronoi_all()

  design:
    mark selected neighbors of atvertex
    for each selected neighbor (either Voronoi vertex or vertex-at-infinity)
      for each unvisited vertex
        if atvertex and vertex share more than d-1 neighbors
          bump totalcount
          if printvridge defined
            build the set of shared neighbors (i.e., Voronoi vertices)
            call printvridge
*/
int qh_eachvoronoi(FILE *fp, printvridgeT printvridge, vertexT *atvertex, boolT visitall, qh_RIDGE innerouter, boolT inorder) {
  boolT unbounded;
  int count;
  facetT *neighbor, **neighborp, *neighborA, **neighborAp;
  setT *centers;
  setT *tricenters= qh_settemp(qh TEMPsize);

  vertexT *vertex, **vertexp;
  boolT firstinf;
  unsigned int numfacets= (unsigned int)qh num_facets;
  int totridges= 0;

  qh vertex_visit++;
  atvertex->seen= True;
  if (visitall) {
    FORALLvertices
      vertex->seen= False;
  }
  FOREACHneighbor_(atvertex) {
    if (neighbor->visitid < numfacets)
      neighbor->seen= True;
  }
  FOREACHneighbor_(atvertex) {
    if (neighbor->seen) {
      FOREACHvertex_(neighbor->vertices) {
        if (vertex->visitid != qh vertex_visit && !vertex->seen) {
          vertex->visitid= qh vertex_visit;
          count= 0;
          firstinf= True;
          qh_settruncate(tricenters, 0);
          FOREACHneighborA_(vertex) {
            if (neighborA->seen) {
              if (neighborA->visitid) {
                if (!neighborA->tricoplanar || qh_setunique(&tricenters, neighborA->center))
                  count++;
              }else if (firstinf) {
                count++;
                firstinf= False;
              }
            }
          }
          if (count >= qh hull_dim - 1) {  /* e.g., 3 for 3-d Voronoi */
            if (firstinf) {
              if (innerouter == qh_RIDGEouter)
                continue;
              unbounded= False;
            }else {
              if (innerouter == qh_RIDGEinner)
                continue;
              unbounded= True;
            }
            totridges++;
            trace4((qh ferr, 4017, "qh_eachvoronoi: Voronoi ridge of %d vertices between sites %d and %d\n",
                  count, qh_pointid(atvertex->point), qh_pointid(vertex->point)));
            if (printvridge && fp) {
              if (inorder && qh hull_dim == 3+1) /* 3-d Voronoi diagram */
                centers= qh_detvridge3 (atvertex, vertex);
              else
                centers= qh_detvridge(vertex);
              (*printvridge) (fp, atvertex, vertex, centers, unbounded);
              qh_settempfree(&centers);
            }
          }
        }
      }
    }
  }
  FOREACHneighbor_(atvertex)
    neighbor->seen= False;
  qh_settempfree(&tricenters);
  return totridges;
} /* eachvoronoi */


/*-<a                             href="qh-poly.htm#TOC"
  >-------------------------------</a><a name="eachvoronoi_all">-</a>

  qh_eachvoronoi_all( fp, printvridge, isUpper, innerouter, inorder )
    visit all Voronoi ridges

    innerouter:
      see qh_eachvoronoi()

    if inorder
      orders vertices for 3-d Voronoi diagrams

  returns
    total number of ridges

    if isUpper == facet->upperdelaunay  (i.e., a Vornoi vertex)
      facet->visitid= Voronoi vertex index(same as 'o' format)
    else
      facet->visitid= 0

    if printvridge,
      calls printvridge( fp, vertex, vertexA, centers)
      [see qh_eachvoronoi]

  notes:
    Not used for qhull.exe
    same effect as qh_printvdiagram but ridges not sorted by point id
*/
int qh_eachvoronoi_all(FILE *fp, printvridgeT printvridge, boolT isUpper, qh_RIDGE innerouter, boolT inorder) {
  facetT *facet;
  vertexT *vertex;
  int numcenters= 1;  /* vertex 0 is vertex-at-infinity */
  int totridges= 0;

  qh_clearcenters(qh_ASvoronoi);
  qh_vertexneighbors();
  maximize_(qh visit_id, (unsigned) qh num_facets);
  FORALLfacets {
    facet->visitid= 0;
    facet->seen= False;
    facet->seen2= True;
  }
  FORALLfacets {
    if (facet->upperdelaunay == isUpper)
      facet->visitid= numcenters++;
  }
  FORALLvertices
    vertex->seen= False;
  FORALLvertices {
    if (qh GOODvertex > 0 && qh_pointid(vertex->point)+1 != qh GOODvertex)
      continue;
    totridges += qh_eachvoronoi(fp, printvridge, vertex,
                   !qh_ALL, innerouter, inorder);
  }
  return totridges;
} /* eachvoronoi_all */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="facet2point">-</a>

  qh_facet2point( facet, point0, point1, mindist )
    return two projected temporary vertices for a 2-d facet
    may be non-simplicial

  returns:
    point0 and point1 oriented and projected to the facet
    returns mindist (maximum distance below plane)
*/
void qh_facet2point(facetT *facet, pointT **point0, pointT **point1, realT *mindist) {
  vertexT *vertex0, *vertex1;
  realT dist;

  if (facet->toporient ^ qh_ORIENTclock) {
    vertex0= SETfirstt_(facet->vertices, vertexT);
    vertex1= SETsecondt_(facet->vertices, vertexT);
  }else {
    vertex1= SETfirstt_(facet->vertices, vertexT);
    vertex0= SETsecondt_(facet->vertices, vertexT);
  }
  zadd_(Zdistio, 2);
  qh_distplane(vertex0->point, facet, &dist);
  *mindist= dist;
  *point0= qh_projectpoint(vertex0->point, facet, dist);
  qh_distplane(vertex1->point, facet, &dist);
  minimize_(*mindist, dist);
  *point1= qh_projectpoint(vertex1->point, facet, dist);
} /* facet2point */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="facetvertices">-</a>

  qh_facetvertices( facetlist, facets, allfacets )
    returns temporary set of vertices in a set and/or list of facets
    if allfacets, ignores qh_skipfacet()

  returns:
    vertices with qh.vertex_visit

  notes:
    optimized for allfacets of facet_list

  design:
    if allfacets of facet_list
      create vertex set from vertex_list
    else
      for each selected facet in facets or facetlist
        append unvisited vertices to vertex set
*/
setT *qh_facetvertices(facetT *facetlist, setT *facets, boolT allfacets) {
  setT *vertices;
  facetT *facet, **facetp;
  vertexT *vertex, **vertexp;

  qh vertex_visit++;
  if (facetlist == qh facet_list && allfacets && !facets) {
    vertices= qh_settemp(qh num_vertices);
    FORALLvertices {
      vertex->visitid= qh vertex_visit;
      qh_setappend(&vertices, vertex);
    }
  }else {
    vertices= qh_settemp(qh TEMPsize);
    FORALLfacet_(facetlist) {
      if (!allfacets && qh_skipfacet(facet))
        continue;
      FOREACHvertex_(facet->vertices) {
        if (vertex->visitid != qh vertex_visit) {
          vertex->visitid= qh vertex_visit;
          qh_setappend(&vertices, vertex);
        }
      }
    }
  }
  FOREACHfacet_(facets) {
    if (!allfacets && qh_skipfacet(facet))
      continue;
    FOREACHvertex_(facet->vertices) {
      if (vertex->visitid != qh vertex_visit) {
        vertex->visitid= qh vertex_visit;
        qh_setappend(&vertices, vertex);
      }
    }
  }
  return vertices;
} /* facetvertices */

/*-<a                             href="qh-geom.htm#TOC"
  >-------------------------------</a><a name="geomplanes">-</a>

  qh_geomplanes( facet, outerplane, innerplane )
    return outer and inner planes for Geomview
    qh.PRINTradius is size of vertices and points (includes qh.JOGGLEmax)

  notes:
    assume precise calculations in io.c with roundoff covered by qh_GEOMepsilon
*/
void qh_geomplanes(facetT *facet, realT *outerplane, realT *innerplane) {
  realT radius;

  if (qh MERGING || qh JOGGLEmax < REALmax/2) {
    qh_outerinner(facet, outerplane, innerplane);
    radius= qh PRINTradius;
    if (qh JOGGLEmax < REALmax/2)
      radius -= qh JOGGLEmax * sqrt((realT)qh hull_dim);  /* already accounted for in qh_outerinner() */
    *outerplane += radius;
    *innerplane -= radius;
    if (qh PRINTcoplanar || qh PRINTspheres) {
      *outerplane += qh MAXabs_coord * qh_GEOMepsilon;
      *innerplane -= qh MAXabs_coord * qh_GEOMepsilon;
    }
  }else
    *innerplane= *outerplane= 0;
} /* geomplanes */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="markkeep">-</a>

  qh_markkeep( facetlist )
    mark good facets that meet qh.KEEParea, qh.KEEPmerge, and qh.KEEPminArea
    ignores visible facets (!part of convex hull)

  returns:
    may clear facet->good
    recomputes qh.num_good

  design:
    get set of good facets
    if qh.KEEParea
      sort facets by area
      clear facet->good for all but n largest facets
    if qh.KEEPmerge
      sort facets by merge count
      clear facet->good for all but n most merged facets
    if qh.KEEPminarea
      clear facet->good if area too small
    update qh.num_good
*/
void qh_markkeep(facetT *facetlist) {
  facetT *facet, **facetp;
  setT *facets= qh_settemp(qh num_facets);
  int size, count;

  trace2((qh ferr, 2006, "qh_markkeep: only keep %d largest and/or %d most merged facets and/or min area %.2g\n",
          qh KEEParea, qh KEEPmerge, qh KEEPminArea));
  FORALLfacet_(facetlist) {
    if (!facet->visible && facet->good)
      qh_setappend(&facets, facet);
  }
  size= qh_setsize(facets);
  if (qh KEEParea) {
    qsort(SETaddr_(facets, facetT), (size_t)size,
             sizeof(facetT *), qh_compare_facetarea);
    if ((count= size - qh KEEParea) > 0) {
      FOREACHfacet_(facets) {
        facet->good= False;
        if (--count == 0)
          break;
      }
    }
  }
  if (qh KEEPmerge) {
    qsort(SETaddr_(facets, facetT), (size_t)size,
             sizeof(facetT *), qh_compare_facetmerge);
    if ((count= size - qh KEEPmerge) > 0) {
      FOREACHfacet_(facets) {
        facet->good= False;
        if (--count == 0)
          break;
      }
    }
  }
  if (qh KEEPminArea < REALmax/2) {
    FOREACHfacet_(facets) {
      if (!facet->isarea || facet->f.area < qh KEEPminArea)
        facet->good= False;
    }
  }
  qh_settempfree(&facets);
  count= 0;
  FORALLfacet_(facetlist) {
    if (facet->good)
      count++;
  }
  qh num_good= count;
} /* markkeep */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="markvoronoi">-</a>

  qh_markvoronoi( facetlist, facets, printall, isLower, numcenters )
    mark voronoi vertices for printing by site pairs

  returns:
    temporary set of vertices indexed by pointid
    isLower set if printing lower hull (i.e., at least one facet is lower hull)
    numcenters= total number of Voronoi vertices
    bumps qh.printoutnum for vertex-at-infinity
    clears all facet->seen and sets facet->seen2

    if selected
      facet->visitid= Voronoi vertex id
    else if upper hull (or 'Qu' and lower hull)
      facet->visitid= 0
    else
      facet->visitid >= qh num_facets

  notes:
    ignores qh.ATinfinity, if defined
*/
setT *qh_markvoronoi(facetT *facetlist, setT *facets, boolT printall, boolT *isLowerp, int *numcentersp) {
  int numcenters=0;
  facetT *facet, **facetp;
  setT *vertices;
  boolT isLower= False;

  qh printoutnum++;
  qh_clearcenters(qh_ASvoronoi);  /* in case, qh_printvdiagram2 called by user */
  qh_vertexneighbors();
  vertices= qh_pointvertex();
  if (qh ATinfinity)
    SETelem_(vertices, qh num_points-1)= NULL;
  qh visit_id++;
  maximize_(qh visit_id, (unsigned) qh num_facets);
  FORALLfacet_(facetlist) {
    if (printall || !qh_skipfacet(facet)) {
      if (!facet->upperdelaunay) {
        isLower= True;
        break;
      }
    }
  }
  FOREACHfacet_(facets) {
    if (printall || !qh_skipfacet(facet)) {
      if (!facet->upperdelaunay) {
        isLower= True;
        break;
      }
    }
  }
  FORALLfacets {
    if (facet->normal && (facet->upperdelaunay == isLower))
      facet->visitid= 0;  /* facetlist or facets may overwrite */
    else
      facet->visitid= qh visit_id;
    facet->seen= False;
    facet->seen2= True;
  }
  numcenters++;  /* qh_INFINITE */
  FORALLfacet_(facetlist) {
    if (printall || !qh_skipfacet(facet))
      facet->visitid= numcenters++;
  }
  FOREACHfacet_(facets) {
    if (printall || !qh_skipfacet(facet))
      facet->visitid= numcenters++;
  }
  *isLowerp= isLower;
  *numcentersp= numcenters;
  trace2((qh ferr, 2007, "qh_markvoronoi: isLower %d numcenters %d\n", isLower, numcenters));
  return vertices;
} /* markvoronoi */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="order_vertexneighbors">-</a>

  qh_order_vertexneighbors( vertex )
    order facet neighbors of a 2-d or 3-d vertex by adjacency

  notes:
    does not orient the neighbors

  design:
    initialize a new neighbor set with the first facet in vertex->neighbors
    while vertex->neighbors non-empty
      select next neighbor in the previous facet's neighbor set
    set vertex->neighbors to the new neighbor set
*/
void qh_order_vertexneighbors(vertexT *vertex) {
  setT *newset;
  facetT *facet, *neighbor, **neighborp;

  trace4((qh ferr, 4018, "qh_order_vertexneighbors: order neighbors of v%d for 3-d\n", vertex->id));
  newset= qh_settemp(qh_setsize(vertex->neighbors));
  facet= (facetT*)qh_setdellast(vertex->neighbors);
  qh_setappend(&newset, facet);
  while (qh_setsize(vertex->neighbors)) {
    FOREACHneighbor_(vertex) {
      if (qh_setin(facet->neighbors, neighbor)) {
        qh_setdel(vertex->neighbors, neighbor);
        qh_setappend(&newset, neighbor);
        facet= neighbor;
        break;
      }
    }
    if (!neighbor) {
      qh_fprintf(qh ferr, 6066, "qhull internal error (qh_order_vertexneighbors): no neighbor of v%d for f%d\n",
        vertex->id, facet->id);
      qh_errexit(qh_ERRqhull, facet, NULL);
    }
  }
  qh_setfree(&vertex->neighbors);
  qh_settemppop();
  vertex->neighbors= newset;
} /* order_vertexneighbors */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="prepare_output">-</a>

  qh_prepare_output( )
    prepare for qh_produce_output2() according to
      qh.KEEPminArea, KEEParea, KEEPmerge, GOODvertex, GOODthreshold, GOODpoint, ONLYgood, SPLITthresholds
    does not reset facet->good

  notes
    except for PRINTstatistics, no-op if previously called with same options
*/
void qh_prepare_output(void) {
  if (qh VORONOI) {
    qh_clearcenters (qh_ASvoronoi);
    qh_vertexneighbors();
  }
  if (qh TRIangulate && !qh hasTriangulation) {
    qh_triangulate();
    if (qh VERIFYoutput && !qh CHECKfrequently)
      qh_checkpolygon (qh facet_list);
  }
  qh_findgood_all (qh facet_list);
  if (qh GETarea)
    qh_getarea(qh facet_list);
  if (qh KEEParea || qh KEEPmerge || qh KEEPminArea < REALmax/2)
    qh_markkeep (qh facet_list);
  if (qh PRINTstatistics)
    qh_collectstatistics();
}

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printafacet">-</a>

  qh_printafacet( fp, format, facet, printall )
    print facet to fp in given output format (see qh.PRINTout)

  returns:
    nop if !printall and qh_skipfacet()
    nop if visible facet and NEWfacets and format != PRINTfacets
    must match qh_countfacets

  notes
    preserves qh.visit_id
    facet->normal may be null if PREmerge/MERGEexact and STOPcone before merge

  see
    qh_printbegin() and qh_printend()

  design:
    test for printing facet
    call appropriate routine for format
    or output results directly
*/
void qh_printafacet(FILE *fp, qh_PRINT format, facetT *facet, boolT printall) {
} /* printafacet */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printbegin">-</a>

  qh_printbegin(  )
    prints header for all output formats

  returns:
    checks for valid format

  notes:
    uses qh.visit_id for 3/4off
    changes qh.interior_point if printing centrums
    qh_countfacets clears facet->visitid for non-good facets

  see
    qh_printend() and qh_printafacet()

  design:
    count facets and related statistics
    print header for format
*/

void qh_printbegin(FILE *fp, qh_PRINT format, facetT *facetlist, setT *facets, boolT printall) {
} /* printbegin */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printcenter">-</a>

  qh_printcenter( fp, string, facet )
    print facet->center as centrum or Voronoi center
    string may be NULL.  Don't include '%' codes.
    nop if qh CENTERtype neither CENTERvoronoi nor CENTERcentrum
    if upper envelope of Delaunay triangulation and point at-infinity
      prints qh_INFINITE instead;

  notes:
    defines facet->center if needed
    if format=PRINTgeom, adds a 0 if would otherwise be 2-d
    Same as QhullFacet::printCenter
*/
void qh_printcenter(FILE *fp, qh_PRINT format, const char *string, facetT *facet) {
} /* printcenter */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printcentrum">-</a>

  qh_printcentrum( fp, facet, radius )
    print centrum for a facet in OOGL format
    radius defines size of centrum
    2-d or 3-d only

  returns:
    defines facet->center if needed
*/
void qh_printcentrum(FILE *fp, facetT *facet, realT radius) {
} /* printcentrum */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printend">-</a>

  qh_printend( fp, format )
    prints trailer for all output formats

  see:
    qh_printbegin() and qh_printafacet()

*/
void qh_printend(FILE *fp, qh_PRINT format, facetT *facetlist, setT *facets, boolT printall) {
} /* printend */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printend4geom">-</a>

  qh_printend4geom( fp, facet, numridges, printall )
    helper function for qh_printbegin/printend

  returns:
    number of printed ridges

  notes:
    just counts printed ridges if fp=NULL
    uses facet->visitid
    must agree with qh_printfacet4geom...

  design:
    computes color for facet from its normal
    prints each ridge of facet
*/
void qh_printend4geom(FILE *fp, facetT *facet, int *nump, boolT printall) {
} /* printend4geom */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printextremes">-</a>

  qh_printextremes( fp, facetlist, facets, printall )
    print extreme points for convex hulls or halfspace intersections

  notes:
    #points, followed by ids, one per line

    sorted by id
    same order as qh_printpoints_out if no coplanar/interior points
*/
void qh_printextremes(FILE *fp, facetT *facetlist, setT *facets, boolT printall) {
} /* printextremes */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printextremes_2d">-</a>

  qh_printextremes_2d( fp, facetlist, facets, printall )
    prints point ids for facets in qh_ORIENTclock order

  notes:
    #points, followed by ids, one per line
    if facetlist/facets are disjoint than the output includes skips
    errors if facets form a loop
    does not print coplanar points
*/
void qh_printextremes_2d(FILE *fp, facetT *facetlist, setT *facets, boolT printall) {
} /* printextremes_2d */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printextremes_d">-</a>

  qh_printextremes_d( fp, facetlist, facets, printall )
    print extreme points of input sites for Delaunay triangulations

  notes:
    #points, followed by ids, one per line

    unordered
*/
void qh_printextremes_d(FILE *fp, facetT *facetlist, setT *facets, boolT printall) {
} /* printextremes_d */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet">-</a>

  qh_printfacet( fp, facet )
    prints all fields of a facet to fp

  notes:
    ridges printed in neighbor order
*/
void qh_printfacet(FILE *fp, facetT *facet) {
} /* printfacet */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet2geom">-</a>

  qh_printfacet2geom( fp, facet, color )
    print facet as part of a 2-d VECT for Geomview

    notes:
      assume precise calculations in io.c with roundoff covered by qh_GEOMepsilon
      mindist is calculated within io.c.  maxoutside is calculated elsewhere
      so a DISTround error may have occured.
*/
void qh_printfacet2geom(FILE *fp, facetT *facet, realT color[3]) {
} /* printfacet2geom */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet2geom_points">-</a>

  qh_printfacet2geom_points( fp, point1, point2, facet, offset, color )
    prints a 2-d facet as a VECT with 2 points at some offset.
    The points are on the facet's plane.
*/
void qh_printfacet2geom_points(FILE *fp, pointT *point1, pointT *point2,
                               facetT *facet, realT offset, realT color[3]) {
} /* printfacet2geom_points */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet2math">-</a>

  qh_printfacet2math( fp, facet, format, notfirst )
    print 2-d Maple or Mathematica output for a facet
    may be non-simplicial

  notes:
    use %16.8f since Mathematica 2.2 does not handle exponential format
    see qh_printfacet3math
*/
void qh_printfacet2math(FILE *fp, facetT *facet, qh_PRINT format, int notfirst) {
} /* printfacet2math */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet3geom_nonsimplicial">-</a>

  qh_printfacet3geom_nonsimplicial( fp, facet, color )
    print Geomview OFF for a 3-d nonsimplicial facet.
    if DOintersections, prints ridges to unvisited neighbors(qh visit_id)

  notes
    uses facet->visitid for intersections and ridges
*/
void qh_printfacet3geom_nonsimplicial(FILE *fp, facetT *facet, realT color[3]) {
} /* printfacet3geom_nonsimplicial */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet3geom_points">-</a>

  qh_printfacet3geom_points( fp, points, facet, offset )
    prints a 3-d facet as OFF Geomview object.
    offset is relative to the facet's hyperplane
    Facet is determined as a list of points
*/
void qh_printfacet3geom_points(FILE *fp, setT *points, facetT *facet, realT offset, realT color[3]) {
} /* printfacet3geom_points */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet3geom_simplicial">-</a>

  qh_printfacet3geom_simplicial(  )
    print Geomview OFF for a 3-d simplicial facet.

  notes:
    may flip color
    uses facet->visitid for intersections and ridges

    assume precise calculations in io.c with roundoff covered by qh_GEOMepsilon
    innerplane may be off by qh DISTround.  Maxoutside is calculated elsewhere
    so a DISTround error may have occured.
*/
void qh_printfacet3geom_simplicial(FILE *fp, facetT *facet, realT color[3]) {
} /* printfacet3geom_simplicial */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet3math">-</a>

  qh_printfacet3math( fp, facet, notfirst )
    print 3-d Maple or Mathematica output for a facet

  notes:
    may be non-simplicial
    use %16.8f since Mathematica 2.2 does not handle exponential format
    see qh_printfacet2math
*/
void qh_printfacet3math(FILE *fp, facetT *facet, qh_PRINT format, int notfirst) {
} /* printfacet3math */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet3vertex">-</a>

  qh_printfacet3vertex( fp, facet, format )
    print vertices in a 3-d facet as point ids

  notes:
    prints number of vertices first if format == qh_PRINToff
    the facet may be non-simplicial
*/
void qh_printfacet3vertex(FILE *fp, facetT *facet, qh_PRINT format) {
} /* printfacet3vertex */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet4geom_nonsimplicial">-</a>

  qh_printfacet4geom_nonsimplicial(  )
    print Geomview 4OFF file for a 4d nonsimplicial facet
    prints all ridges to unvisited neighbors (qh.visit_id)
    if qh.DROPdim
      prints in OFF format

  notes:
    must agree with printend4geom()
*/
void qh_printfacet4geom_nonsimplicial(FILE *fp, facetT *facet, realT color[3]) {
} /* printfacet4geom_nonsimplicial */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacet4geom_simplicial">-</a>

  qh_printfacet4geom_simplicial( fp, facet, color )
    print Geomview 4OFF file for a 4d simplicial facet
    prints triangles for unvisited neighbors (qh.visit_id)

  notes:
    must agree with printend4geom()
*/
void qh_printfacet4geom_simplicial(FILE *fp, facetT *facet, realT color[3]) {
} /* printfacet4geom_simplicial */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacetNvertex_nonsimplicial">-</a>

  qh_printfacetNvertex_nonsimplicial( fp, facet, id, format )
    print vertices for an N-d non-simplicial facet
    triangulates each ridge to the id
*/
void qh_printfacetNvertex_nonsimplicial(FILE *fp, facetT *facet, int id, qh_PRINT format) {
} /* printfacetNvertex_nonsimplicial */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacetNvertex_simplicial">-</a>

  qh_printfacetNvertex_simplicial( fp, facet, format )
    print vertices for an N-d simplicial facet
    prints vertices for non-simplicial facets
      2-d facets (orientation preserved by qh_mergefacet2d)
      PRINToff ('o') for 4-d and higher
*/
void qh_printfacetNvertex_simplicial(FILE *fp, facetT *facet, qh_PRINT format) {
} /* printfacetNvertex_simplicial */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacetheader">-</a>

  qh_printfacetheader( fp, facet )
    prints header fields of a facet to fp

  notes:
    for 'f' output and debugging
    Same as QhullFacet::printHeader()
*/
void qh_printfacetheader(FILE *fp, facetT *facet) {
} /* printfacetheader */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacetridges">-</a>

  qh_printfacetridges( fp, facet )
    prints ridges of a facet to fp

  notes:
    ridges printed in neighbor order
    assumes the ridges exist
    for 'f' output
    same as QhullFacet::printRidges
*/
void qh_printfacetridges(FILE *fp, facetT *facet) {
} /* printfacetridges */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printfacets">-</a>

  qh_printfacets( fp, format, facetlist, facets, printall )
    prints facetlist and/or facet set in output format

  notes:
    also used for specialized formats ('FO' and summary)
    turns off 'Rn' option since want actual numbers
*/
void qh_printfacets(FILE *fp, qh_PRINT format, facetT *facetlist, setT *facets, boolT printall) {
} /* printfacets */


/*-<a                             href="qh-io.htm#TOC"
in Qhull\" (http://www.qhull.org/html/qh-impre.htm).\n\
  - use exact arithmetic (see \"Imprecision in Qhull\", http://www.qhull.org/html/qh-impre.htm)\n\
  >-------------------------------</a><a name="printhyperplaneintersection">-</a>

  qh_printhyperplaneintersection( fp, facet1, facet2, vertices, color )
    print Geomview OFF or 4OFF for the intersection of two hyperplanes in 3-d or 4-d
*/
void qh_printhyperplaneintersection(FILE *fp, facetT *facet1, facetT *facet2,
                   setT *vertices, realT color[3]) {
} /* printhyperplaneintersection */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printline3geom">-</a>

  qh_printline3geom( fp, pointA, pointB, color )
    prints a line as a VECT
    prints 0's for qh.DROPdim

  notes:
    if pointA == pointB,
      it's a 1 point VECT
*/
void qh_printline3geom(FILE *fp, pointT *pointA, pointT *pointB, realT color[3]) {
}

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printneighborhood">-</a>

  qh_printneighborhood( fp, format, facetA, facetB, printall )
    print neighborhood of one or two facets

  notes:
    calls qh_findgood_all()
    bumps qh.visit_id
*/
void qh_printneighborhood(FILE *fp, qh_PRINT format, facetT *facetA, facetT *facetB, boolT printall) {
} /* printneighborhood */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printpoint">-</a>

  qh_printpoint( fp, string, point )
  qh_printpointid( fp, string, dim, point, id )
    prints the coordinates of a point

  returns:
    if string is defined
      prints 'string p%d' (skips p%d if id=-1)

  notes:
    nop if point is NULL
    prints id unless it is undefined (-1)
    Same as QhullPoint's printPoint
*/
void qh_printpoint(FILE *fp, const char *string, pointT *point) {
} /* printpoint */

void qh_printpointid(FILE *fp, const char *string, int dim, pointT *point, int id) {
} /* printpointid */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printpoint3">-</a>

  qh_printpoint3( fp, point )
    prints 2-d, 3-d, or 4-d point as Geomview 3-d coordinates
*/
void qh_printpoint3 (FILE *fp, pointT *point) {
} /* printpoint3 */

/*----------------------------------------
-printpoints- print pointids for a set of points starting at index
   see geom.c
*/

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printpoints_out">-</a>

  qh_printpoints_out( fp, facetlist, facets, printall )
    prints vertices, coplanar/inside points, for facets by their point coordinates
    allows qh.CDDoutput

  notes:
    same format as qhull input
    if no coplanar/interior points,
      same order as qh_printextremes
*/
void qh_printpoints_out(FILE *fp, facetT *facetlist, setT *facets, boolT printall) {
} /* printpoints_out */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printpointvect">-</a>

  qh_printpointvect( fp, point, normal, center, radius, color )
    prints a 2-d, 3-d, or 4-d point as 3-d VECT's relative to normal or to center point
*/
void qh_printpointvect(FILE *fp, pointT *point, coordT *normal, pointT *center, realT radius, realT color[3]) {
} /* printpointvect */  

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printpointvect2">-</a>

  qh_printpointvect2( fp, point, normal, center, radius )
    prints a 2-d, 3-d, or 4-d point as 2 3-d VECT's for an imprecise point
*/
void qh_printpointvect2 (FILE *fp, pointT *point, coordT *normal, pointT *center, realT radius) {
} /* printpointvect2 */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printridge">-</a>

  qh_printridge( fp, ridge )
    prints the information in a ridge

  notes:
    for qh_printfacetridges()
    same as operator<< [QhullRidge.cpp]
*/
void qh_printridge(FILE *fp, ridgeT *ridge) {
} /* printridge */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printspheres">-</a>

  qh_printspheres( fp, vertices, radius )
    prints 3-d vertices as OFF spheres

  notes:
    inflated octahedron from Stuart Levy earth/mksphere2
*/
void qh_printspheres(FILE *fp, setT *vertices, realT radius) {
} /* printspheres */


/*----------------------------------------------
-printsummary-
                see libqhull.c
*/

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvdiagram">-</a>

  qh_printvdiagram( fp, format, facetlist, facets, printall )
    print voronoi diagram
      # of pairs of input sites
      #indices site1 site2 vertex1 ...

    sites indexed by input point id
      point 0 is the first input point
    vertices indexed by 'o' and 'p' order
      vertex 0 is the 'vertex-at-infinity'
      vertex 1 is the first Voronoi vertex

  see:
    qh_printvoronoi()
    qh_eachvoronoi_all()

  notes:
    if all facets are upperdelaunay,
      prints upper hull (furthest-site Voronoi diagram)
*/
void qh_printvdiagram(FILE *fp, qh_PRINT format, facetT *facetlist, setT *facets, boolT printall) {
} /* printvdiagram */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvdiagram2">-</a>

  qh_printvdiagram2( fp, printvridge, vertices, innerouter, inorder )
    visit all pairs of input sites (vertices) for selected Voronoi vertices
    vertices may include NULLs

  innerouter:
    qh_RIDGEall   print inner ridges(bounded) and outer ridges(unbounded)
    qh_RIDGEinner print only inner ridges
    qh_RIDGEouter print only outer ridges

  inorder:
    print 3-d Voronoi vertices in order

  assumes:
    qh_markvoronoi marked facet->visitid for Voronoi vertices
    all facet->seen= False
    all facet->seen2= True

  returns:
    total number of Voronoi ridges
    if printvridge,
      calls printvridge( fp, vertex, vertexA, centers) for each ridge
      [see qh_eachvoronoi()]

  see:
    qh_eachvoronoi_all()
*/
int qh_printvdiagram2 (FILE *fp, printvridgeT printvridge, setT *vertices, qh_RIDGE innerouter, boolT inorder) {
return 0;
} /* printvdiagram2 */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvertex">-</a>

  qh_printvertex( fp, vertex )
    prints the information in a vertex
    Duplicated as operator<< [QhullVertex.cpp]
*/
void qh_printvertex(FILE *fp, vertexT *vertex) {
} /* printvertex */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvertexlist">-</a>

  qh_printvertexlist( fp, string, facetlist, facets, printall )
    prints vertices used by a facetlist or facet set
    tests qh_skipfacet() if !printall
*/
void qh_printvertexlist(FILE *fp, const char* string, facetT *facetlist,
                         setT *facets, boolT printall) {
} /* printvertexlist */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvertices">-</a>

  qh_printvertices( fp, string, vertices )
    prints vertices in a set
    duplicated as printVertexSet [QhullVertex.cpp]
*/
void qh_printvertices(FILE *fp, const char* string, setT *vertices) {
} /* printvertices */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvneighbors">-</a>

  qh_printvneighbors( fp, facetlist, facets, printall )
    print vertex neighbors of vertices in facetlist and facets ('FN')

  notes:
    qh_countfacets clears facet->visitid for non-printed facets

  design:
    collect facet count and related statistics
    if necessary, build neighbor sets for each vertex
    collect vertices in facetlist and facets
    build a point array for point->vertex and point->coplanar facet
    for each point
      list vertex neighbors or coplanar facet
*/
void qh_printvneighbors(FILE *fp, facetT* facetlist, setT *facets, boolT printall) {
} /* printvneighbors */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvoronoi">-</a>

  qh_printvoronoi( fp, format, facetlist, facets, printall )
    print voronoi diagram in 'o' or 'G' format
    for 'o' format
      prints voronoi centers for each facet and for infinity
      for each vertex, lists ids of printed facets or infinity
      assumes facetlist and facets are disjoint
    for 'G' format
      prints an OFF object
      adds a 0 coordinate to center
      prints infinity but does not list in vertices

  see:
    qh_printvdiagram()

  notes:
    if 'o',
      prints a line for each point except "at-infinity"
    if all facets are upperdelaunay,
      reverses lower and upper hull
*/
void qh_printvoronoi(FILE *fp, qh_PRINT format, facetT *facetlist, setT *facets, boolT printall) {
} /* printvoronoi */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvnorm">-</a>

  qh_printvnorm( fp, vertex, vertexA, centers, unbounded )
    print one separating plane of the Voronoi diagram for a pair of input sites
    unbounded==True if centers includes vertex-at-infinity

  assumes:
    qh_ASvoronoi and qh_vertexneighbors() already set

  note:
    parameter unbounded is UNUSED by this callback

  see:
    qh_printvdiagram()
    qh_eachvoronoi()
*/
void qh_printvnorm(FILE *fp, vertexT *vertex, vertexT *vertexA, setT *centers, boolT unbounded) {
} /* printvnorm */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="printvridge">-</a>

  qh_printvridge( fp, vertex, vertexA, centers, unbounded )
    print one ridge of the Voronoi diagram for a pair of input sites
    unbounded==True if centers includes vertex-at-infinity

  see:
    qh_printvdiagram()

  notes:
    the user may use a different function
    parameter unbounded is UNUSED
*/
void qh_printvridge(FILE *fp, vertexT *vertex, vertexT *vertexA, setT *centers, boolT unbounded) {
} /* printvridge */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="projectdim3">-</a>

  qh_projectdim3( source, destination )
    project 2-d 3-d or 4-d point to a 3-d point
    uses qh.DROPdim and qh.hull_dim
    source and destination may be the same

  notes:
    allocate 4 elements to destination just in case
*/
void qh_projectdim3 (pointT *source, pointT *destination) {
  int i,k;

  for (k=0, i=0; k < qh hull_dim; k++) {
    if (qh hull_dim == 4) {
      if (k != qh DROPdim)
        destination[i++]= source[k];
    }else if (k == qh DROPdim)
      destination[i++]= 0;
    else
      destination[i++]= source[k];
  }
  while (i < 3)
    destination[i++]= 0.0;
} /* projectdim3 */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="readfeasible">-</a>

  qh_readfeasible( dim, curline )
    read feasible point from current line and qh.fin

  returns:
    number of lines read from qh.fin
    sets qh.FEASIBLEpoint with malloc'd coordinates

  notes:
    checks for qh.HALFspace
    assumes dim > 1

  see:
    qh_setfeasible
*/
int qh_readfeasible(int dim, const char *curline) {
  boolT isfirst= True;
  int linecount= 0, tokcount= 0;
  const char *s;
  char *t, firstline[qh_MAXfirst+1];
  coordT *coords, value;

  if (!qh HALFspace) {
    qh_fprintf(qh ferr, 6070, "qhull input error: feasible point(dim 1 coords) is only valid for halfspace intersection\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (qh feasible_string)
    qh_fprintf(qh ferr, 7057, "qhull input warning: feasible point(dim 1 coords) overrides 'Hn,n,n' feasible point for halfspace intersection\n");
  if (!(qh feasible_point= (coordT*)qh_malloc(dim* sizeof(coordT)))) {
    qh_fprintf(qh ferr, 6071, "qhull error: insufficient memory for feasible point\n");
    qh_errexit(qh_ERRmem, NULL, NULL);
  }
  coords= qh feasible_point;
  while ((s= (isfirst ?  curline : fgets(firstline, qh_MAXfirst, qh fin)))) {
    if (isfirst)
      isfirst= False;
    else
      linecount++;
    while (*s) {
      while (isspace(*s))
        s++;
      value= qh_strtod(s, &t);
      if (s == t)
        break;
      s= t;
      *(coords++)= value;
      if (++tokcount == dim) {
        while (isspace(*s))
          s++;
        qh_strtod(s, &t);
        if (s != t) {
          qh_fprintf(qh ferr, 6072, "qhull input error: coordinates for feasible point do not finish out the line: %s\n",
               s);
          qh_errexit(qh_ERRinput, NULL, NULL);
        }
        return linecount;
      }
    }
  }
  qh_fprintf(qh ferr, 6073, "qhull input error: only %d coordinates.  Could not read %d-d feasible point.\n",
           tokcount, dim);
  qh_errexit(qh_ERRinput, NULL, NULL);
  return 0;
} /* readfeasible */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="readpoints">-</a>

  qh_readpoints( numpoints, dimension, ismalloc )
    read points from qh.fin into qh.first_point, qh.num_points
    qh.fin is lines of coordinates, one per vertex, first line number of points
    if 'rbox D4',
      gives message
    if qh.ATinfinity,
      adds point-at-infinity for Delaunay triangulations

  returns:
    number of points, array of point coordinates, dimension, ismalloc True
    if qh.DELAUNAY & !qh.PROJECTinput, projects points to paraboloid
        and clears qh.PROJECTdelaunay
    if qh.HALFspace, reads optional feasible point, reads halfspaces,
        converts to dual.

  for feasible point in "cdd format" in 3-d:
    3 1
    coordinates
    comments
    begin
    n 4 real/integer
    ...
    end

  notes:
    dimension will change in qh_initqhull_globals if qh.PROJECTinput
    uses malloc() since qh_mem not initialized
    FIXUP QH10012: qh_readpoints needs rewriting, too long
*/
coordT *qh_readpoints(int *numpoints, int *dimension, boolT *ismalloc) {
  coordT *points, *coords, *infinity= NULL;
  realT paraboloid, maxboloid= -REALmax, value;
  realT *coordp= NULL, *offsetp= NULL, *normalp= NULL;
  char *s= 0, *t, firstline[qh_MAXfirst+1];
  int diminput=0, numinput=0, dimfeasible= 0, newnum, k, tempi;
  int firsttext=0, firstshort=0, firstlong=0, firstpoint=0;
  int tokcount= 0, linecount=0, maxcount, coordcount=0;
  boolT islong, isfirst= True, wasbegin= False;
  boolT isdelaunay= qh DELAUNAY && !qh PROJECTinput;

  if (qh CDDinput) {
    while ((s= fgets(firstline, qh_MAXfirst, qh fin))) {
      linecount++;
      if (qh HALFspace && linecount == 1 && isdigit(*s)) {
        dimfeasible= qh_strtol(s, &s);
        while (isspace(*s))
          s++;
        if (qh_strtol(s, &s) == 1)
          linecount += qh_readfeasible(dimfeasible, s);
        else
          dimfeasible= 0;
      }else if (!memcmp(firstline, "begin", (size_t)5) || !memcmp(firstline, "BEGIN", (size_t)5))
        break;
      else if (!*qh rbox_command)
        strncat(qh rbox_command, s, sizeof(qh rbox_command)-1);
    }
    if (!s) {
      qh_fprintf(qh ferr, 6074, "qhull input error: missing \"begin\" for cdd-formated input\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
  }
  while (!numinput && (s= fgets(firstline, qh_MAXfirst, qh fin))) {
    linecount++;
    if (!memcmp(s, "begin", (size_t)5) || !memcmp(s, "BEGIN", (size_t)5))
      wasbegin= True;
    while (*s) {
      while (isspace(*s))
        s++;
      if (!*s)
        break;
      if (!isdigit(*s)) {
        if (!*qh rbox_command) {
          strncat(qh rbox_command, s, sizeof(qh rbox_command)-1);
          firsttext= linecount;
        }
        break;
      }
      if (!diminput)
        diminput= qh_strtol(s, &s);
      else {
        numinput= qh_strtol(s, &s);
        if (numinput == 1 && diminput >= 2 && qh HALFspace && !qh CDDinput) {
          linecount += qh_readfeasible(diminput, s); /* checks if ok */
          dimfeasible= diminput;
          diminput= numinput= 0;
        }else
          break;
      }
    }
  }
  if (!s) {
    qh_fprintf(qh ferr, 6075, "qhull input error: short input file.  Did not find dimension and number of points\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (diminput > numinput) {
    tempi= diminput;    /* exchange dim and n, e.g., for cdd input format */
    diminput= numinput;
    numinput= tempi;
  }
  if (diminput < 2) {
    qh_fprintf(qh ferr, 6220,"qhull input error: dimension %d(first number) should be at least 2\n",
            diminput);
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (isdelaunay) {
    qh PROJECTdelaunay= False;
    if (qh CDDinput)
      *dimension= diminput;
    else
      *dimension= diminput+1;
    *numpoints= numinput;
    if (qh ATinfinity)
      (*numpoints)++;
  }else if (qh HALFspace) {
    *dimension= diminput - 1;
    *numpoints= numinput;
    if (diminput < 3) {
      qh_fprintf(qh ferr, 6221,"qhull input error: dimension %d(first number, includes offset) should be at least 3 for halfspaces\n",
            diminput);
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
    if (dimfeasible) {
      if (dimfeasible != *dimension) {
        qh_fprintf(qh ferr, 6222,"qhull input error: dimension %d of feasible point is not one less than dimension %d for halfspaces\n",
          dimfeasible, diminput);
        qh_errexit(qh_ERRinput, NULL, NULL);
      }
    }else
      qh_setfeasible(*dimension);
  }else {
    if (qh CDDinput)
      *dimension= diminput-1;
    else
      *dimension= diminput;
    *numpoints= numinput;
  }
  qh normal_size= *dimension * sizeof(coordT); /* for tracing with qh_printpoint */
  if (qh HALFspace) {
    qh half_space= coordp= (coordT*)qh_malloc(qh normal_size + sizeof(coordT));
    if (qh CDDinput) {
      offsetp= qh half_space;
      normalp= offsetp + 1;
    }else {
      normalp= qh half_space;
      offsetp= normalp + *dimension;
    }
  }
  qh maxline= diminput * (qh_REALdigits + 5);
  maximize_(qh maxline, 500);
  qh line= (char*)qh_malloc((qh maxline+1) * sizeof(char));
  *ismalloc= True;  /* use malloc since memory not setup */
  coords= points= qh temp_malloc=
        (coordT*)qh_malloc((*numpoints)*(*dimension)*sizeof(coordT));
  if (!coords || !qh line || (qh HALFspace && !qh half_space)) {
    qh_fprintf(qh ferr, 6076, "qhull error: insufficient memory to read %d points\n",
            numinput);
    qh_errexit(qh_ERRmem, NULL, NULL);
  }
  if (isdelaunay && qh ATinfinity) {
    infinity= points + numinput * (*dimension);
    for (k= (*dimension) - 1; k--; )
      infinity[k]= 0.0;
  }
  maxcount= numinput * diminput;
  paraboloid= 0.0;
  while ((s= (isfirst ?  s : fgets(qh line, qh maxline, qh fin)))) {
    if (!isfirst) {
      linecount++;
      if (*s == 'e' || *s == 'E') {
        if (!memcmp(s, "end", (size_t)3) || !memcmp(s, "END", (size_t)3)) {
          if (qh CDDinput )
            break;
          else if (wasbegin)
            qh_fprintf(qh ferr, 7058, "qhull input warning: the input appears to be in cdd format.  If so, use 'Fd'\n");
        }
      }
    }
    islong= False;
    while (*s) {
      while (isspace(*s))
        s++;
      value= qh_strtod(s, &t);
      if (s == t) {
        if (!*qh rbox_command)
         strncat(qh rbox_command, s, sizeof(qh rbox_command)-1);
        if (*s && !firsttext)
          firsttext= linecount;
        if (!islong && !firstshort && coordcount)
          firstshort= linecount;
        break;
      }
      if (!firstpoint)
        firstpoint= linecount;
      s= t;
      if (++tokcount > maxcount)
        continue;
      if (qh HALFspace) {
        if (qh CDDinput)
          *(coordp++)= -value; /* both coefficients and offset */
        else
          *(coordp++)= value;
      }else {
        *(coords++)= value;
        if (qh CDDinput && !coordcount) {
          if (value != 1.0) {
            qh_fprintf(qh ferr, 6077, "qhull input error: for cdd format, point at line %d does not start with '1'\n",
                   linecount);
            qh_errexit(qh_ERRinput, NULL, NULL);
          }
          coords--;
        }else if (isdelaunay) {
          paraboloid += value * value;
          if (qh ATinfinity) {
            if (qh CDDinput)
              infinity[coordcount-1] += value;
            else
              infinity[coordcount] += value;
          }
        }
      }
      if (++coordcount == diminput) {
        coordcount= 0;
        if (isdelaunay) {
          *(coords++)= paraboloid;
          maximize_(maxboloid, paraboloid);
          paraboloid= 0.0;
        }else if (qh HALFspace) {
          if (!qh_sethalfspace(*dimension, coords, &coords, normalp, offsetp, qh feasible_point)) {
            qh_fprintf(qh ferr, 8048, "The halfspace was on line %d\n", linecount);
            if (wasbegin)
              qh_fprintf(qh ferr, 8049, "The input appears to be in cdd format.  If so, you should use option 'Fd'\n");
            qh_errexit(qh_ERRinput, NULL, NULL);
          }
          coordp= qh half_space;
        }
        while (isspace(*s))
          s++;
        if (*s) {
          islong= True;
          if (!firstlong)
            firstlong= linecount;
        }
      }
    }
    if (!islong && !firstshort && coordcount)
      firstshort= linecount;
    if (!isfirst && s - qh line >= qh maxline) {
      qh_fprintf(qh ferr, 6078, "qhull input error: line %d contained more than %d characters\n",
              linecount, (int) (s - qh line));   /* WARN64 */
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
    isfirst= False;
  }
  if (tokcount != maxcount) {
    newnum= fmin_(numinput, tokcount/diminput);
    qh_fprintf(qh ferr, 7073,"\
qhull warning: instead of %d %d-dimensional points, input contains\n\
%d points and %d extra coordinates.  Line %d is the first\npoint",
       numinput, diminput, tokcount/diminput, tokcount % diminput, firstpoint);
    if (firsttext)
      qh_fprintf(qh ferr, 8051, ", line %d is the first comment", firsttext);
    if (firstshort)
      qh_fprintf(qh ferr, 8052, ", line %d is the first short\nline", firstshort);
    if (firstlong)
      qh_fprintf(qh ferr, 8053, ", line %d is the first long line", firstlong);
    qh_fprintf(qh ferr, 8054, ".  Continue with %d points.\n", newnum);
    numinput= newnum;
    if (isdelaunay && qh ATinfinity) {
      for (k= tokcount % diminput; k--; )
        infinity[k] -= *(--coords);
      *numpoints= newnum+1;
    }else {
      coords -= tokcount % diminput;
      *numpoints= newnum;
    }
  }
  if (isdelaunay && qh ATinfinity) {
    for (k= (*dimension) -1; k--; )
      infinity[k] /= numinput;
    if (coords == infinity)
      coords += (*dimension) -1;
    else {
      for (k=0; k < (*dimension) -1; k++)
        *(coords++)= infinity[k];
    }
    *(coords++)= maxboloid * 1.1;
  }
  if (qh rbox_command[0]) {
    qh rbox_command[strlen(qh rbox_command)-1]= '\0';
    if (!strcmp(qh rbox_command, "./rbox D4"))
      qh_fprintf(qh ferr, 8055, "\n\
This is the qhull test case.  If any errors or core dumps occur,\n\
recompile qhull with 'make new'.  If errors still occur, there is\n\
an incompatibility.  You should try a different compiler.  You can also\n\
change the choices in user.h.  If you discover the source of the problem,\n\
please send mail to qhull_bug@qhull.org.\n\
\n\
Type 'qhull' for a short list of options.\n");
  }
  qh_free(qh line);
  qh line= NULL;
  if (qh half_space) {
    qh_free(qh half_space);
    qh half_space= NULL;
  }
  qh temp_malloc= NULL;
  trace1((qh ferr, 1008,"qh_readpoints: read in %d %d-dimensional points\n",
          numinput, diminput));
  return(points);
} /* readpoints */


/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="setfeasible">-</a>

  qh_setfeasible( dim )
    set qh.FEASIBLEpoint from qh.feasible_string in "n,n,n" or "n n n" format

  notes:
    "n,n,n" already checked by qh_initflags()
    see qh_readfeasible()
*/
void qh_setfeasible(int dim) {
  int tokcount= 0;
  char *s;
  coordT *coords, value;

  if (!(s= qh feasible_string)) {
    qh_fprintf(qh ferr, 6223, "\
qhull input error: halfspace intersection needs a feasible point.\n\
Either prepend the input with 1 point or use 'Hn,n,n'.  See manual.\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (!(qh feasible_point= (pointT*)qh_malloc(dim * sizeof(coordT)))) {
    qh_fprintf(qh ferr, 6079, "qhull error: insufficient memory for 'Hn,n,n'\n");
    qh_errexit(qh_ERRmem, NULL, NULL);
  }
  coords= qh feasible_point;
  while (*s) {
    value= qh_strtod(s, &s);
    if (++tokcount > dim) {
      qh_fprintf(qh ferr, 7059, "qhull input warning: more coordinates for 'H%s' than dimension %d\n",
          qh feasible_string, dim);
      break;
    }
    *(coords++)= value;
    if (*s)
      s++;
  }
  while (++tokcount <= dim)
    *(coords++)= 0.0;
} /* setfeasible */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="skipfacet">-</a>

  qh_skipfacet( facet )
    returns 'True' if this facet is not to be printed

  notes:
    based on the user provided slice thresholds and 'good' specifications
*/
boolT qh_skipfacet(facetT *facet) {
  facetT *neighbor, **neighborp;

  if (qh PRINTneighbors) {
    if (facet->good)
      return !qh PRINTgood;
    FOREACHneighbor_(facet) {
      if (neighbor->good)
        return False;
    }
    return True;
  }else if (qh PRINTgood)
    return !facet->good;
  else if (!facet->normal)
    return True;
  return(!qh_inthresholds(facet->normal, NULL));
} /* skipfacet */

/*-<a                             href="qh-io.htm#TOC"
  >-------------------------------</a><a name="skipfilename">-</a>

  qh_skipfilename( string )
    returns pointer to character after filename

  notes:
    skips leading spaces
    ends with spacing or eol
    if starts with ' or " ends with the same, skipping \' or \"
    For qhull, qh_argv_to_command() only uses double quotes
*/
char *qh_skipfilename(char *filename) {
  char *s= filename;  /* non-const due to return */
  char c;

  while (*s && isspace(*s))
    s++;
  c= *s++;
  if (c == '\0') {
    qh_fprintf(qh ferr, 6204, "qhull input error: filename expected, none found.\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (c == '\'' || c == '"') {
    while (*s !=c || s[-1] == '\\') {
      if (!*s) {
        qh_fprintf(qh ferr, 6203, "qhull input error: missing quote after filename -- %s\n", filename);
        qh_errexit(qh_ERRinput, NULL, NULL);
      }
      s++;
    }
    s++;
  }
  else while (*s && !isspace(*s))
      s++;
  return s;
} /* skipfilename */

