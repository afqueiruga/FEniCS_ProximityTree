#include <ostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <boost/cstdint.hpp>
#include <boost/detail/endian.hpp>

#include <dolfin/common/Timer.h>
#include <dolfin/fem/GenericDofMap.h>
#include <dolfin/fem/FiniteElement.h>
#include <dolfin/function/Function.h>
#include <dolfin/function/FunctionSpace.h>
#include <dolfin/la/GenericVector.h>
#include <dolfin/mesh/Cell.h>
#include <dolfin/mesh/MeshEntityIterator.h>
#include <dolfin/mesh/Mesh.h>
#include <dolfin/mesh/MeshFunction.h>
#include <dolfin/mesh/Vertex.h>

#include "dolfin/io/Encoder.h"
#include "dolfin/io/VTKWriter.h"
#include "dolfin/io/VTKFile.h"

#include "ProximityTree.h"

namespace dolfin
{
  void FuckYouSwig(const  GenericFunction& u, const Mesh& mesh,const Function & f) 
  {
  }


  ProximityTree3D::ProximityTree3D()
  {
    // Do nothing
    // _tdim=0;
  }
  ProximityTree3D::~ProximityTree3D()
  {
    //do nothing
  }



  std::vector<unsigned int> ProximityTree3D::compute_proximity_collisions
  (const Point& point, double radius)
  {
    // // Point in entity only implemented for cells. Consider extending this.
    // if (_tdim != mesh->topology().dim())
    //   {
    // 	dolfin_error("GenericBoundingBoxTree.cpp",
    // 		     "compute collision between point and mesh entities",
    // 		     "Point-in-entity is only implemented for cells");
    //   }
    
    // // Call recursive find function to compute bounding box candidates
    std::vector<unsigned int> entities;
    // _compute_collisions(*this, point, num_bboxes() - 1, entities, mesh);
    _compute_proximity_collisions(*this, point,num_bboxes() - 1,
				  entities, radius*radius);
    return entities;
  }



  void ProximityTree3D::_compute_proximity_collisions
  (const ProximityTree3D& tree, const Point & point, unsigned int node,
   std::vector<unsigned int>& entities, double R2)
  {
    // Get bounding box for current node
    const BBox& bbox = tree.get_bbox(node);

    // If box is leaf, then compute distance and shrink radius
    if (tree.is_leaf(bbox, node))
      {
	const double r2 = tree.compute_squared_distance_point(point.coordinates(),
							      node);
	if (r2 < R2)
	  {
	    entities.push_back(bbox.child_1);
	  }
      }
    else
      {
	// If bounding box is outside radius, then don't search further
	const double r2 = tree.compute_squared_distance_bbox(point.coordinates(),
							     node);
	if (r2 > R2)
	  return;
	
	// Check both children
	_compute_proximity_collisions(tree, point, bbox.child_0, entities, R2);
	_compute_proximity_collisions(tree, point, bbox.child_1, entities, R2);
      }
  }
  

}

