// stdafx.cpp : source file that includes just the standard includes
// hash_collision.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void DisplayMessageDigest(uint32_t sha1hash[5])
{
    printf("\t%08X %08X %08X %08X %08X\n", sha1hash[0], sha1hash[1], sha1hash[2], sha1hash[3], sha1hash[4]);
}

float twoPow(uint8_t pow)
{
  float ret = 1.f;
  for(uint8_t i = 0; i < pow; ++i)
  {
    ret *= 2.f;
  }
  return ret;
}