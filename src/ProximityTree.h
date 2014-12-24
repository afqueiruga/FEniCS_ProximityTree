#ifndef __PROXIMITY_TREE_H
#define __PROXIMITY_TREE_H 


#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "dolfin/io/GenericFile.h"
#include "dolfin/io/VTKFile.h"

#include "dolfin/geometry/Point.h"
#include "dolfin/geometry/BoundingBoxTree3D.h"


#include <memory>
#include <set>
#include <vector>
#include <dolfin/geometry/Point.h>
#include <dolfin/geometry/BoundingBoxTree3D.h>

namespace dolfin {
  // Put in a function with a bunch of types in the call signature to make 
  // sure SWIG wraps them first 'cuz it can't do Mesh alone.
  void FuckYouSwig(const  GenericFunction& u, const Mesh& mesh,const Function & f);

  class ProximityTree3D : public BoundingBoxTree3D
  {
  public:
    ProximityTree3D();
    ~ProximityTree3D();
    std::vector<unsigned int> compute_proximity_collisions(const Point& point, double radius);
    void _compute_proximity_collisions
      (const ProximityTree3D& tree, const Point & point, unsigned int node,
       std::vector<unsigned int>& entities, double R2);
  };
}

#endif
