#include <gtest/gtest.h>
#include <string>
#include <memory>

#include "parse.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "shadedObject.hpp"
#include "color.hpp"

class PlaneTests: public testing::Test {

protected:
    PlaneTests() {
        point3D loc(0,0,5);
        point3D normal(0,0,-1);
        Color color(255, 0, 0);

        p2 = std::make_unique<Plane>(2.0, loc, color, normal);
    }

    Plane p1;
    std::unique_ptr<Plane> p2;
};

TEST_F(PlaneTests, TestConstructors){

}

TEST_F(PlaneTests, TestAssignment) {

    Plane p3 = *p2;

    EXPECT_EQ(p2->normal(), p3.normal());
    EXPECT_EQ(p2->lambert(), p3.lambert());
    EXPECT_EQ(p2->center(), p3.center());
    EXPECT_EQ(p2->color(), p3.color());
}

TEST_F(PlaneTests, Intersection) {

    point3D start(0,0,0);
    point3D dir(0,0,1);
    point3D intersection, normal;

    EXPECT_EQ(true, p2->intersects(start, dir, intersection, normal));
}