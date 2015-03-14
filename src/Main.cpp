#include <iostream>

#include "geometry/Basis3D.hpp"
#include "geometry/Matrix3D.hpp"
#include "geometry/GridSurface3D.hpp"
#include "geometry/LocalVector3D.hpp"
#include "geometry/ISurface3D.hpp"
#include "geometry/Range3D.hpp"
#include "geometry/OrthogonalPlaneSurface3D.hpp"
#include "geometry/SphericalSurface3D.hpp"
#include "geometry/TransformationMatrix3D.hpp"
#include "geometry/Vector3D.hpp"
#include "optics/Refractor.hpp"
#include "optics/IDiffuser.hpp"
#include "optics/Interface.hpp"
#include "optics/ObjectDiffuser.hpp"
#include "optics/Object3D.hpp"
#include "optics/OpticalSystem.hpp"
#include "optics/PointSource3D.hpp"
#include "optics/PropagatorFactory.hpp"
#include "optics/SingleRayTracer.hpp"
#include "optics/Interface.hpp"

using namespace std;

#define COORD_TYPE double
#define INTENS_TYPE double

#define Basis Basis3D<COORD_TYPE>
#define ISurface ISurface3D<COORD_TYPE>
#define GridSurface GridSurface3D<COORD_TYPE>
#define PlanarSurface OrthogonalPlaneSurface3D<COORD_TYPE>
#define SphericalSurface SphericalSurface3D<COORD_TYPE>
#define ObjectDiffuser ObjectDiffuser<COORD_TYPE, INTENS_TYPE>
#define Object Object3D<COORD_TYPE, INTENS_TYPE>
#define PointSource PointSource3D<COORD_TYPE, INTENS_TYPE>
#define Matrix Matrix3D<COORD_TYPE>
#define Refractor Refractor<COORD_TYPE>
#define TransformationMatrix TransformationMatrix3D<COORD_TYPE>
#define Vector Vector3D<COORD_TYPE>
#define LocalVector LocalVector3D<COORD_TYPE>
#define Point Point3D<COORD_TYPE>
#define Range3D Range3D<COORD_TYPE>
#define Range Range<COORD_TYPE>
#define Ray Ray<COORD_TYPE, INTENS_TYPE>
#define Propagator IPropagator<COORD_TYPE, INTENS_TYPE>
#define PropagatorFactory PropagatorFactory<COORD_TYPE, INTENS_TYPE>
#define SingleRayTracer SingleRayTracer<COORD_TYPE, INTENS_TYPE>
#define OpticalSystem OpticalSystem<COORD_TYPE>
#define Interface Interface<COORD_TYPE>

int main(int argc, char *argv[]) {
    try {
        const Vector v1(1.234, 2.345, 3.456);
        const Vector v2(1,2,3);
        cout << "v1 = " << v1 << " , v2 = " << v2 << endl;
        cout << "v1 + v2 = " << (v1 + v2) << endl;
        cout << "v1 - v2 = " << (v1 - v2) << endl;
        cout << "v1 = " << v1 << ", ||v1|| = " << ~v1 << endl;
        cout << "v1/||v1|| = " << !v1 << ", ||v1/||v1|||| = " << ~!v1 << endl;
        cout << "v2 = " << v2 << ", ||v2|| = " << ~v2 << endl;
        cout << "v2/||v2|| = " << !v2 << ", ||v2/||v2|||| = " << ~!v2 << endl;
        const Vector u1(1, 0, 0);
        const Vector u2(0, 1, 0);
        cout << "u1 = " << u1 << " , u2 = " << u2 << endl;
        cout << "u1 * u2 = " << ( u1 * u2 ) << endl; // Vectorial product
        cout << "u1 | u2 = " << ( u1 | u2 ) << endl; // Scalar product
        const Vector u3 = u1 * u2;
        cout << "u3 = " << u3 << endl;
        cout << "2.0 * u1 + u2 * 1.5 - u3 * 4.0 = " << (2.0 * u1 + u2 / 2.0 - u3 * 4.0) << endl;
        const Matrix m(1, 0, 0, 0, 1, 0, 0, 0, 1);
        cout << "2 * [M] / 3 = " << (2.0 * m / 3.0) << endl;
        const Matrix m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        cout << "[M1] = " << m1 << endl;
        const Matrix m2(8, 1, 7, 2, 6, 3, 5, 4, 0);
        cout << "[M2] = " << m2 << endl;
        cout << "[M1 + M2] = " << (m1 + m2) << endl;
        cout << "[M1 * M2] = " << (m1 * m2) << endl;
        cout << "[M2 * M1] = " << (m2 * m1) << endl;
        cout << "[M * M1] = " << (m * m1) << endl;
        const Matrix m3(7, 2, 1, 0, 3, -1, -3, 4, -2);
        cout << "[M3] = " << m3 << endl;
        cout << "[M3^-1] = " << (m3^-1) << endl;
        const Matrix im3(-2, 8, -5, 3, -11, 7, 9, -34, 21);
        cout << "[IM3] = " << im3 << endl;
        cout << "[M3^-1]==[IM3] ? -> " << ((m3^-1) == im3 ? "yes" : "no") << endl;
        const Basis b1(u1, u2, u3);
        cout << "{b1} = " << b1 << endl;
        const Basis b2(2.0 * u2, 0.5 * u3, u1 / 10.0);
        cout << "{b2} = " << b2 << endl;
        const TransformationMatrix t(b1, b2);
        cout << "[T] = " << t << endl;
        const Vector v(1, 1, 1);
        cout << "v = " << v << endl;
        cout << "[T] * v = " << (t * v) << endl;

        const Vector normal = !Vector(0, 0, 1);
        const Vector incident = !Vector(sqrt(2), 0, -sqrt(2));
        const double n1 = 1.0; // Air
        const double n2 = 1.333; // Water
        const Vector refracted = Refractor::refract(incident, normal, n1, n2);
        cout << "inc = " << incident << endl;
        cout << "ref = " << refracted << endl;

        const Range3D r(Range(0, 1), Range(3, 4), Range(5, 6));
        cout << "Range = " << r << endl;

        const double dataZ[4] = { 1.234, 2.345, 3.456, 4.567 };
        GridSurface surface(r.rangeX, 1.0, r.rangeY, 1.0, dataZ);
        cout << "surface = " << surface << endl;
        cout << "surface->range = " << surface.getRange() << endl;
        cout << "surface X " << Point(-10, 0, 0) << " = " << surface.intersects(Point(-10, 0, 0)) << endl;
        cout << "surface X " << Point(0, 0, 0) << " = " << surface.intersects(Point(0, 0, 0)) << endl;
        cout << "surface X " << Point(0.5, 3.5, 3.0) << " = " << surface.intersects(Point(0.5, 3.5, 3.0)) << endl;
        Point location(0.5, 3.5, 3.0);
        LocalVector localVector = surface.getNormalVector(location);
        cout << "Local vector at " << location << " = " << localVector << endl;

        Point center(0.0, 0.0, 0.0);
        SphericalSurface ssurf(center, -6.0 /* curvature */, 1.0 /* radius */);
        cout << "Spherical surface: " << ssurf << endl;

        PlanarSurface psurf(ssurf.getRange().rangeZ.end);
        cout << "Planar surface: " << psurf << endl;

        Ray ray(v1, v2, 1.0);
        cout << "Ray: " << ray << endl;

        ObjectDiffuser diffuser(M_PI / 10);
        cout << "Image diffuser: " << diffuser << endl;
        vector<Ray> rays = diffuser.diffuse(Vector(0, 0, 1), ray);

        cout << "Diffused rays: " << endl;
        for (vector<Ray>::iterator it = rays.begin() ; it != rays.end(); ++it)
            cout << *it << endl;

        PointSource ps(Point(0.0, 0.0, -100.0) /* location */, 1.0 /* intensity */);
        Ray rin(ps.location, !(Vector(0.004, 0.002, 1.0)), 1.0);
        ISurface* surf = dynamic_cast<ISurface*>(&ssurf);
        Propagator* propagator = PropagatorFactory::GetPropagator(surf);
        if (!propagator)
            throw "Null propagator!";
        Ray rout = propagator->propagate(rin, surf);
        delete propagator;
        cout << "Source ray: " << rin << endl;
        cout << "Propagation to: " << rout << endl;
        const Vector _refracted = Refractor::refract(rout.direction, ssurf.getNormalVector(rout.location).normal, 1.0, 1.5);
        cout << "Refraction! " << rout.direction << " -> " << _refracted << endl;
        Ray rout2 = Ray(rout.location, _refracted, rout.intensity);
        surf = dynamic_cast<ISurface*>(&psurf);
        propagator = PropagatorFactory::GetPropagator(surf);
        if (!propagator)
            throw "Null propagator!";
        Ray rout3 = propagator->propagate(rout2, surf);
        delete propagator;
        cout << "Propagation to: " << rout3 << endl;
        const Vector _refracted2 = Refractor::refract(rout3.direction, psurf.getNormalVector(rout3.location).normal, 1.5, 1.0);
        cout << "Refraction! " << rout3.direction << " -> " << _refracted2 << endl;

        OpticalSystem os;
        Interface int1(1.0, ssurf, 1.5);
        cout << "Interface1: " << int1 << endl;
        os.push_back(int1);
        Interface int2(1.5, psurf, 1.0);
        cout << "Interface2: " << int2 << endl;
        os.push_back(int2);
        PlanarSurface imageplane(0.0);
        Interface int3(1.0, imageplane, 1.0);
        cout << "Interface3[image]: " << int3 << endl;
        os.push_back(int3);
        cout << "Optical system summary:\n" << os << endl;
        SingleRayTracer srt;
        Ray imageray = srt.trace(rin, os);
        cout << "Object ray: " << rin << endl;
        cout << "Image ray: " << imageray << endl;

    } catch (const char* error) {
        cout << "ERROR! >> " << error << endl;
        return -1;
    }
    return 0;
}
