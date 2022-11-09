#include "Physics.hpp"

#define INFINIT_DISTANCE std::numeric_limits<float>::max()
#define EPA_PRECISION_WANTED 0.001

void Physics::apply_gravity(Element *element, float timeElapsed, float gravityAcceleration)
{
    if (element->get_has_gravity()) // apply gravity only if the element shoud be affected by the gravity
    {
        const float oldVelocityOnY = element->get_velocity_on_y();
        const float newVelocityOnY = oldVelocityOnY + timeElapsed*gravityAcceleration;
        element->set_velocity_on_y(newVelocityOnY);
    }
}

bool Physics::GJK(const Element *e1, const Element *e2)
{
    // get the first direction vector
    const Vector2D e1Center = e1->get_center();
    const Vector2D e2Center = e2->get_center();
    Vector2D direction(Math::normalize_vector(e2Center - e1Center));

    // create the simplex vector and then add the first point to it
    std::vector<Vector2D> simplex;
    simplex.push_back(Physics::support(e1, e2, direction));

    // setting the new direction toward the origin
    direction = Math::normalize_vector(-simplex[0]); // == ORIGIN - A == (0, 0) - A

    while (true)
    {
        // get an other point on the Minkowski difference
        Vector2D A = Physics::support(e1, e2, direction);

        // if the new point didn't pass the origin then the origin can't be inside the Minkowski difference
        // and by extention the 2 shapes aren't colliding, so return false
        if (Math::dot(A, direction) < 0) 
        {
            return false; 
        }
        
        // append the new point to the simplex
        simplex.push_back(A);

        // return true if the origin is inside the simplex
        // else modify the direction vector and the simplex in order to reiterate the steps
        if (handle_simplex(simplex, direction))
        {
            return true;
        }
    }
}

bool Physics::GJK(const Element *e1, const Element *e2, std::vector<Vector2D> &simplex)
{
    // get the first direction vector
    const Vector2D e1Center = e1->get_center();
    const Vector2D e2Center = e2->get_center();
    Vector2D direction(Math::normalize_vector(e2Center - e1Center));

    // make sure the simplex is empty and then add the first point to it
    assert(simplex.size() == 0);
    simplex.push_back(Physics::support(e1, e2, direction));

    // setting the new direction toward the origin
    direction = Math::normalize_vector(-simplex[0]); // == ORIGIN - A == (0, 0) - A

    while (true)
    {
        // get an other point on the Minkowski difference
        Vector2D A = Physics::support(e1, e2, direction);

        // if the new point didn't pass the origin then the origin can't be inside the Minkowski difference
        // and by extention the 2 shapes aren't colliding, so return false
        // BUT since we need the function to return a 3D simplex (in order to be able to use it in EPA)
        // we will add points to the simplex if needed
        if (Math::dot(A, direction) < 0) 
        {
            direction = Math::normal_clockwise(direction);

            while (simplex.size() < 3)
            {
                Vector2D newPoint = Physics::support(e1, e2, direction);

                // if the new point isn't already in the simplex
                if (std::find(simplex.begin(), simplex.end(), newPoint) == simplex.end())
                {
                    simplex.push_back(newPoint); // add the new point to the simplex
                }

                direction = Math::normal_clockwise(direction);
            }
            return false;
        }
        
        // append the new point to the simplex
        simplex.push_back(A);

        // return true if the origin is inside the simplex
        // else modify the direction vector and the simplex in order to reiterate the steps
        if (handle_simplex(simplex, direction))
        {
            return true;
        }
    }
}

float Physics::EPA(const Element *e1, const Element *e2, Vector2D &direction, std::vector<Vector2D> polytope)
{
    float closestEdgeDistance;
    Vector2D closestEdgeNormal;

    // while the precision is too low copared to the goal minDistance will be set to INFINIT_DISTANCE
    while (true)
    {
        int closestEdgeIndex = Physics::get_closest_edge_infos(polytope, closestEdgeDistance, closestEdgeNormal);

        // once we got the normal of the closest edge to the origin so we can use it to determine a new point
        // on the edge of the Minkowski difference
        Vector2D support = Physics::support(e1, e2, closestEdgeNormal);

        // calculate the distance 
        float supportDistance = Math::dot(closestEdgeNormal, support);
        
        // the difference between the 2 distance is less then the precision then we 
        // there is no need to expand the polytope any futher, so we return 
        if(supportDistance - closestEdgeDistance < EPA_PRECISION_WANTED)
        {
            direction = closestEdgeNormal;
            return -closestEdgeDistance; // negate the distance to correct the winding probleme
        }

        // if we still are able to expand the polytope, insert the new point in the polytope
        // the point must be inserted bewteen i and j in order to keep the polytope convex
        polytope.insert(polytope.begin() + closestEdgeIndex, support);
    }
}

float Physics::EPA(const Element *e1, const Element *e2, Vector2D &direction)
{
    std::vector<Vector2D> polytope;
    Physics::GJK(e1, e2, polytope);
    return Physics::EPA(e1, e2, direction, polytope);
}

float Physics::EPA(const Element *e1, const Element *e2)
{
    std::vector<Vector2D> polytope;
    Physics::GJK(e1, e2, polytope);
    Vector2D direction;
    return Physics::EPA(e1, e2, direction, polytope);
}

void Physics::set_position_before_colision(Element *e1, Element *e2, float dt)
{
    // replace e1 and e2 at their last position
    e1->set_position(e1->get_previous_position());
    e2->set_position(e2->get_previous_position());

    float distance = Physics::EPA(e1, e2);

    // first test if e1 and e2 were already coliding on theire last position, if so we are unable to
    // determine how they should react now, so we return without doing anything
    if (distance < 0) { std::cout << "Etait déja en collision" << std::endl; return; }

    // while the 2 elements not close enought or are in colision 
    while ((distance > EPA_PRECISION_WANTED) || (distance < 0))
    {
        dt /= 2;

        // if the 2 elements are too far, forward in time there position
        if (distance > 0)
        {
            e1->update_position(dt);
            e2->update_position(dt);
        }
        else // else the 2 elements already collide, so go back in time
        {
            e1->update_position(-dt);
            e2->update_position(-dt);
        }

        // recalculate the distance with their new position
        distance = Physics::EPA(e1, e2);
    }
}

void Physics::resolve_collision(Element *e1, Element *e2, const Vector2D &direction, float penetrationDepth)
{
    // using : https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331#highlighter_753279

    // Calculate relative velocity
    Vector2D relativeVelocity = e2->get_velocity() - e1->get_velocity();
    
    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = Math::dot(relativeVelocity, direction);
    
    // Do not resolve if velocities are separating
    if(velAlongNormal > 0) { return; }
    
    // Calculate restitution
    const float restitution = std::min( e1->get_bounciness(), e2->get_bounciness());
    
    // Calculate impulse scalar
    float impulseScalar = -(1 + restitution) * velAlongNormal;
    impulseScalar /= (e1->get_inv_mass() + e2->get_inv_mass());
    
    // Apply impulse
    Vector2D impulse = impulseScalar * direction;

    const float e1Mass = e1->get_mass();
    const float e2Mass = e2->get_mass();
    const float massSum = e1Mass + e2Mass;

    // if the summ is equal to 0 it mean the 2 element have an infint mass, 
    // so none of theme will move, and cant divide per 0 anyway so return
    if (massSum == 0) { return; }

    const float e1Ratio = e1Mass/massSum;
    const float e2Ratio = e2Mass/massSum;
    Vector2D e1NewVelocity = e1->get_velocity() - e1Ratio*impulse;
    Vector2D e2NewVelocity = e2->get_velocity() + e2Ratio*impulse;
    e1->set_velocity(e1NewVelocity);
    e2->set_velocity(e2NewVelocity);

    // instantly modify there coordinates to avoid elements to sink into each other
    Physics::PositionalCorrection(e1, e2, direction, penetrationDepth, impulse);
}

void Physics::PositionalCorrection(Element *e1, Element *e2, const Vector2D &direction, float penetrationDepth, const Vector2D &impulse)
{
    const float percent = 0.8;
    const float slop = 0.01;
    Vector2D correction = std::max(-penetrationDepth - slop, 0.0f) / (e1->get_inv_mass() + e2->get_inv_mass()) * percent * direction;

    Vector2D e1NewCoordinates = e1->get_position() - e1->get_inv_mass()*correction;
    Vector2D e2NewCoordinates = e2->get_position() + e2->get_inv_mass()*correction;
    e1->set_position(e1NewCoordinates);
    e2->set_position(e2NewCoordinates);
}

Vector2D Physics::support(const Element *e1, const Element *e2, Vector2D &direction)
{
    return e1->get_futhest_point(direction) - e2->get_futhest_point(-direction);
}

bool Physics::handle_simplex(std::vector<Vector2D> &simplex, Vector2D &direction)
{
    if (simplex.size() == 2) { return handle_line_simplex(simplex, direction); }
    return handle_triangle_simplex(simplex, direction);
}

bool Physics::handle_line_simplex(std::vector<Vector2D> &simplex, Vector2D &direction)
{
    Vector2D B = simplex[0];
    Vector2D A = simplex[1];

    Vector2D AB = B - A;
    Vector2D OA = -A; // == (0, 0) - A

    // get the vector perpendicular to AB and pointing toward the origin
    Vector2D ABPerp = Math::triple_cross_product(AB, OA, AB);

    direction = Math::normalize_vector(ABPerp); // redifine the direction toward the origin

    // since the simplex is a line the odd of it to containing the origin in a 2D space
    // is almost null, so return null without bothering to check is more efficient
    // if the simplex was indeed containing the origin the next step of the gjk will tell it
    return false;
}

bool Physics::handle_triangle_simplex(std::vector<Vector2D> &simplex, Vector2D &direction)
{
    Vector2D A = simplex[2];
    Vector2D B = simplex[1];
    Vector2D C = simplex[0];

    Vector2D AB = B - A;
    Vector2D AC = C - A;
    Vector2D AO = -A; // == (0, 0) - A

    Vector2D ABPerp = Math::triple_cross_product(AC, AB, AB);
    if (Math::dot(ABPerp, AO) > 0) // if the origin is in the region AB
    {
        simplex.erase(simplex.begin()); // remove the point C of the simplex
        direction = Math::normalize_vector(ABPerp); // setting the new direction toward the region AB
        return false; // since the point is contain in the region AB then it's not contain in the simplex
    }

    Vector2D ACPerp = Math::triple_cross_product(AB, AC, AC);
    if (Math::dot(ACPerp, AO) > 0) // if the origin is in the region AC
    {
        simplex.erase(std::next(simplex.begin())); // remove the point B of the simplex
        direction = Math::normalize_vector(ACPerp); // setting the new direction toward the region AC
        return false; // since the point is contain in the region AC then it's not contain in the simplex
    }

    // if the origin isn't in both of the 2 area then it belong in the simplex due to the way
    // we first obtained this simplex, so we return true
    return true;
}

int Physics::get_closest_edge_infos(const std::vector<Vector2D> &polytope, float &minDistance, Vector2D &minNormal)
{
    // making sure the politype is valid
    assert(polytope.size() > 2);

    int closestEdgeIndex;
    minDistance = INFINIT_DISTANCE;

    for (int i = 0; i < polytope.size(); ++i)
    {
        // determine the index j wich is the second point of the tested edge (i being the first one)
        int j = (i+1) % polytope.size();

        Vector2D vertexI = polytope[i];
        Vector2D vertexJ = polytope[j];

        Vector2D IJ = vertexJ - vertexI;

        // get the normal vector by swapping coordinates and negating one
        // avoid to use the triple product wich can cause troubles when dealing with really tiny vectors
        Vector2D currentNormal = Math::normalize_vector(Math::normal_clockwise(IJ));

        float currentDistance = Math::dot(currentNormal, vertexI);

        // if the new distance is smaller than the actual smallest replace the smallest
        if (currentDistance < minDistance)
        {
            minDistance = currentDistance;
            minNormal = currentNormal;
            closestEdgeIndex = j;
        }
    }

    return closestEdgeIndex;
}
