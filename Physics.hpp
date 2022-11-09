#pragma once

#include <assert.h>
#include <limits>

#include "Math.hpp"
#include "Element.hpp"

class Physics
{
public:
    // change the Y velocity of the element accordingly to the gravityAcceleration ant the time elapsed 
    static void apply_gravity(Element *element, float timeElapsed, float gravityAcceleration);

    /* 
     * Below functions are used to calculate colision and penetration depth vector
     *
     * for GJK :
     * reffer to this great video https://www.youtube.com/watch?v=ajv46BSqcK4&t
     * and this website https://dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi
     * 
     * for EPA reffer to thoses 2 websites
     * https://dyn4j.org/2010/05/epa-expanding-polytope-algorithm/
     * https://blog.winter.dev/2020/epa-algorithm/
     */

    // return true if 2 Element overlap
    // simply apply JGK algorithm without bothering to crate a full simplex
    static bool GJK(const Element *e1, const Element *e2);

    // return true if 2 Element overlap
    // take an empty vector and fill it with a simplex contained in the Minkowski difference
    static bool GJK(const Element *e1, const Element *e2, std::vector<Vector2D> &simplex);

    // return the shortest distance between 2 shapes
    // fill the direction vector with the direction of the shortest distance
    static float EPA(const Element *e1, const Element *e2, Vector2D &direction, std::vector<Vector2D> polytope);

    // return the shortest distance between 2 shapes
    // fill the direction vector with the direction of the shortest distance
    static float EPA(const Element *e1, const Element *e2, Vector2D &direction);

    // return the shortest distance between 2 shapes
    // fill the direction vector with the direction of the shortest distance
    static float EPA(const Element *e1, const Element *e2);

    // apply log(n) times EPA in order to find the position of the 2 elements just before the colision occure
    // then modify the coordinates of the 2 elements to theses coordinates
    static void set_position_before_colision(Element *e1, Element *e2, float dt);

    // this function is called when 2 elements are coliding,
    // the fuction correct the velocity of the 2 elements accordingly to their properties (velocity, bounciness$)
    static void resolve_collision(Element *e1, Element *e2, const Vector2D &direction, float penetrationDepth);

private:
    // aplly a little adjustement on both of the colliding object coordinates to avoid them sinking into each other
    static void PositionalCorrection(Element *e1, Element *e2, const Vector2D &direction, float penetrationDepth, const Vector2D &impulse);

    // return the point the point on the edge of the Minkowski difference in the given direction
    static Vector2D support(const Element *e1, const Element *e2, Vector2D &direction);

    // return true if the origin is inside the simplex 
    // else modify the simplex by adding/modifying points and redifine the direction vector
    // to prepare to the next step of the gjk algorithm 
    static bool handle_simplex(std::vector<Vector2D> &simplex, Vector2D &direction);

    // take a 2 points simplex, update the direction toward the origin, return false
    static bool handle_line_simplex(std::vector<Vector2D> &simplex, Vector2D &direction);

    // take a 3 points simplex, check if the the origin belongs in the simplex, if yes return true,
    // if not check the origin could belong in the Minkowski difference, if yes update the simplex by removing a point
    // else return false
    static bool handle_triangle_simplex(std::vector<Vector2D> &simplex, Vector2D &direction);

    // return the index of the point A of the edge AB wich is the closest to the origin
    // fill minDistance with distance between A and the origin, fill the vector minNormal 
    // with the normal of AB pointing toward the origin
    static int get_closest_edge_infos(const std::vector<Vector2D> &polytope, float &minDistance, Vector2D &minNormal);
};
