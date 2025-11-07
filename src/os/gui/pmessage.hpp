#pragma once

#include "pthing.hpp"

struct PegMessage;
struct PegThing_Thin;

struct PegMessage {
  WORD wType;
  SIGNED iData;
  PegThing_Thin *pTarget;
  PegThing_Thin *pSource;
  PegMessage *pNext;
  union {
    void *pData;
    LONG lData;
    PegRect rect;
    PegPoint point;
    LONG lUserData[2];
    DWORD dUserData[2];
    SIGNED iUserData[4];
    UCHAR uUserData[8];
  };
};