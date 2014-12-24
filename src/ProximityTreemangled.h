#ifndef __ASSFUCKER_H
#define __ASSFUCKER_H


#include <algorithm>
#include <vector>
#include <dolfin/common/constants.h>
#include <dolfin/geometry/Point.h>
#include <dolfin/mesh/Mesh.h>


/* #include <fstream> */
/* #include <string> */
/* #include <utility> */
/* #include <vector> */
/* #include "dolfin/io/GenericFile.h" */
/* #include "dolfin/io/VTKFile.h" */

#include <dolfin/geometry/GenericBoundingBoxTree.h>
#include <dolfin/geometry/BoundingBoxTree3D.h>


namespace dolfin
{
  // Forward declarations
  /* class Mesh; */
  /* class MeshEntity; */

  class ProximityTree3D //: public BoundingBoxTree3D
  {
  public:
    ProximityTree3D();
    virtual ~ProximityTree3D() {};
    /// Compute all collisions between entities and _Point_
    std::vector<unsigned int>
    compute_proximity_collisions(const Point& point,
    				 const Mesh &u,
    				 double radius) ;

  };

}

#endif
