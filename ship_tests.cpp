#define BOOST_TEST_MODULE ship_test_module
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "ship_impl.h"
struct Fixture
{
  Point readPointValue(std::int64_t x, std::int64_t y)
  {
    std::stringstream ss(std::to_string(x) + " " + std::to_string(y));
    Point p;
    ss >> p;
    return p;
  }

  Ship createShip(std::int64_t x1, std::int64_t y1, std::int64_t x2, std::int64_t y2)
  {
    auto p1 = readPointValue(x1, y1);
    auto p2 = readPointValue(x2, y2);

    return Ship(p1, p2);
  }
};

BOOST_FIXTURE_TEST_SUITE(PointsTests, Fixture)

BOOST_AUTO_TEST_CASE(TwoIntNumbersInStream_ReadPointFromStream_XYValuesSetInPoint)
{
  auto p = readPointValue(1, 2);

  BOOST_CHECK_EQUAL(getX(p), 1);
  BOOST_CHECK_EQUAL(getY(p), 2);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShipTests, Fixture)

BOOST_AUTO_TEST_CASE(GivenBasePosition_TurnRight_ResultsShipTurnedRight)
{
  auto ship = createShip(2, 2, 2, 4);
  auto nextPoint = readPointValue(4, 6);

  ship.move(nextPoint);

  BOOST_CHECK(ship.getResult());
}

BOOST_AUTO_TEST_CASE(GivenBaseCourse_TurnLeft_ResultMarkedFalse)
{
  auto ship = createShip(2, 2, 2, 4);
  ship.move(readPointValue(0, 4));

  BOOST_CHECK(!ship.getResult());
}

BOOST_AUTO_TEST_CASE(GivenBaseCourse_TurnRight_ResultMarkedTrue)
{
  auto ship = createShip(2, 2, 2, 4);
  ship.move(readPointValue(6, 4));

  BOOST_CHECK(ship.getResult());
}

BOOST_AUTO_TEST_CASE(GivenBaseCourse_MoveForwardThenTurnRight_ResultMarkedTrue)
{
  auto ship = createShip(2, 2, 2, 4);
  ship.move(readPointValue(2, 6));
  ship.move(readPointValue(6, 4));

  BOOST_CHECK(ship.getResult());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(NavigationModuleTests)

BOOST_AUTO_TEST_CASE(ShipOnStraightCourse_TurnLeft_ToggleLeft)
{
  BOOST_CHECK_EQUAL(Ship::nav(0, -1, -1), -1);
}

BOOST_AUTO_TEST_CASE(ShipOnStraightCourse_MoveStraightAhead_NoCrossing)
{
  BOOST_CHECK_EQUAL(Ship::nav(0, 0, 0), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheLeft_MoveStraightAhead_NoCrossing)
{
  BOOST_CHECK_EQUAL(Ship::nav(-1, 0, 0), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheLeft_TurnRightNoCrossingBase_NoCrossing)
{
  BOOST_CHECK_EQUAL(Ship::nav(-1, -1, 1), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheLeft_TurnRightCrossingBase_ToggleRight)
{
  BOOST_CHECK_EQUAL(Ship::nav(-1, 1, 1), static_cast<std::int8_t>(2));
}

BOOST_AUTO_TEST_CASE(ShipOnTheLeft_TurnLeftNoCrossingBase_NoCrossingBase)
{
  BOOST_CHECK_EQUAL(Ship::nav(-1, -1, -1), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheLeft_TurnLeftCrossingBase_ToggleLeft)
{
  BOOST_CHECK_EQUAL(Ship::nav(-1, 1, -1), static_cast<std::int8_t>(-2));
}


BOOST_AUTO_TEST_CASE(ShipOnTheRight_MoveStraightAhead_NoCrossing)
{
  BOOST_CHECK_EQUAL(Ship::nav(1, 0, 0), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheRight_TurnLeftNoCrossingBase_NoCrossing)
{
  BOOST_CHECK_EQUAL(Ship::nav(1, 1, -1), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheRight_TurnLeftCrossingBase_ToggleLeft)
{
  BOOST_CHECK_EQUAL(Ship::nav(1, -1, -1), static_cast<std::int8_t>(-2));
}

BOOST_AUTO_TEST_CASE(ShipOnTheRight_TurnRightNoCrossingBase_NoCrossingBase)
{
  BOOST_CHECK_EQUAL(Ship::nav(1, 1, 1), 0);
}

BOOST_AUTO_TEST_CASE(ShipOnTheRight_TurnRightCrossingBase_ToggleRight)
{
  BOOST_CHECK_EQUAL(Ship::nav(1, -1, 1), static_cast<std::int8_t>(2));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UncertainityModuleTests)

BOOST_AUTO_TEST_CASE(ShipOnRight_TurnBack_ToggleUncerainity)
{
  BOOST_CHECK_EQUAL(Ship::pav(1, -1, 0), static_cast<std::int8_t>(2));
}

BOOST_AUTO_TEST_CASE(ShipOnLeft_TurnBack_ToggleUncerainity)
{
  BOOST_CHECK_EQUAL(Ship::pav(-1, 1, 0), static_cast<std::int8_t>(2));
}

BOOST_AUTO_TEST_CASE(ShipOnStraight_MoveForward_HalfToggleUncerainity)
{
  BOOST_CHECK_EQUAL(Ship::pav(0, 0, 0), static_cast<std::int8_t>(1));
}

BOOST_AUTO_TEST_CASE(ShipOnTheRight_TurnRightCrossingBase_NoUncertainity)
{
  BOOST_CHECK_EQUAL(Ship::pav(1, -1, 1), 0);
}

BOOST_AUTO_TEST_SUITE_END()
