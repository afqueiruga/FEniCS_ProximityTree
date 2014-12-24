#!/usr/bin/python


from dolfin import *
import numpy as np
import os

from IPython import embed

srcdir = os.path.dirname(os.path.realpath(__file__))+"/src/"
header_file = open(srcdir+"/ProximityTree.h", "r")
code = header_file.read()
header_file.close()
compiled_module = compile_extension_module(
    code=code, source_directory=srcdir, sources=["ProximityTree.cpp"],
    include_dirs=[".",os.path.abspath(srcdir)],
    additional_declarations='%feature("notabstract") ProximityTree3D;')


def create_line(x0,x1,N):
    mesh = Mesh()
    edit = MeshEditor()
    edit.open(mesh,1,3)
    edit.init_vertices(N+1)
    d = (x1-x0)*1.0/N
    for i in xrange(N):
        # xx = (x0+d*i)
        edit.add_vertex(i,(x0+d*i)) #xx[0],xx[1],xx[2])
    edit.add_vertex(N,x1)
    edit.init_cells(N)
    for i in xrange(N):
        edit.add_cell(i,i,i+1)
    edit.close()
    return mesh

def cubetest():
    me = UnitCubeMesh(10,10,10);
    pt=compiled_module.ProximityTree3D()
    pt.build(me,3)
    ent=pt.compute_proximity_collisions(Point(0.5,0.5,0.1),0.5)
    mf = CellFunction("size_t",me)
    mf.set_all(0)
    for i in ent:
        mf.set_value(i,1)
    ff = File("cubetest.pvd")
    ff << mf

def plotpairs(pairs,me1,me2):
    mesh = Mesh()
    edit = MeshEditor()
    edit.open(mesh,1,3)
    edit.init_vertices(2*len(pairs))
    edit.init_cells(len(pairs))

    for i,p in enumerate(pairs):
        edit.add_vertex(2*i,Cell(me1,p[0]).midpoint())
        edit.add_vertex(2*i+1,Cell(me2,p[1]).midpoint())
        edit.add_cell(i,2*i,2*i+1)
    edit.close()
    return mesh
def linetest():
    me1 = create_line(np.array([-1.0, 0.0,0.1]),np.array([1.0,0.0,0.1]),20)
    me2 = create_line(np.array([ 0.0,-1.0,0.0]),np.array([0.0,1.0,0.0]),20)
    pt = compiled_module.ProximityTree3D()
    pt.build(me1,1)
    # embed()
    pairs = []
    for i,c in enumerate(cells(me2)):
        ent = pt.compute_proximity_collisions(c.midpoint(),0.3)
        for e in ent:
            pairs.append([e,i])

    mf1 = CellFunction("size_t",me1)
    mf1.set_all(0)
    mf2 = CellFunction("size_t",me2)
    mf2.set_all(0)
    for p in pairs:
        mf1.set_value(p[0],1)
        mf2.set_value(p[1],1)
    ff = File("linetest_me1.pvd")
    ff << mf1
    ff = File("linetest_me2.pvd")
    ff << mf2
    ff = File("linetest_pairs.pvd")
    ff << plotpairs(pairs,me1,me2)
if __name__=="__main__":
    cubetest()
    linetest()

