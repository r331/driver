/* city.h — city / level index (P15_State; the city value of an MLADDER SETCITY record).
 * Names from the LEVELS\*.D3D palette file each index loads (ported145.c); the MLADDER parser
 * (ported141.c) accepts the tokens [MIAMI], [SF], [LA], [NY] for 0..3.  Plain integer constants. */
#pragma once

enum {
  CITY_MIAMI     = 0,
  CITY_FRISCO    = 1,   /* San Francisco, MLADDER token [SF] */
  CITY_LA        = 2,
  CITY_NEWYORK   = 3,   /* MLADDER token [NY] */
  CITY_IVIEW     = 4,   /* garage interview level */
  CITY_TRAIN     = 5,   /* training level */
  CITY_NEWCASTLE = 6
};
