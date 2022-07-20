#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits")
{
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);  
}

TEST_CASE("classify breach type accordingly")
{
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-5) == TOO_LOW);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,39) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,25) == NORMAL);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 47) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,35) == NORMAL);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-6) == TOO_LOW);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 43) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-5) == TOO_LOW);
}
            
TEST_CASE("Check and Alert of coolingType Temperature for HI_ACTIVE_COOLING ")
{
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,0));
  assert(checkAndAlert(TO_EMAIL,batteryChar,47));		
}
            
TEST_CASE("Check and Alert of coolingType Temperature for PASSIVE_COOLING ")
{
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,0));
  assert(checkAndAlert(TO_EMAIL,batteryChar,30));		
}

