#ifndef CONFIG_H
#define CONFIG_H

#define BITSET(B,N) B |= 1 << N
#define BITCLR(B,N) B &= ~(1 << N)

typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef unsigned int UINT32;
typedef unsigned long int UINT64;
typedef float UFLOAT;
typedef double UFLOAT64;

typedef char INT8;
typedef short int INT16;
typedef int INT32;
typedef long int INT64;

typedef bool BOOLT;
#define TRUE 1
#define FALSE 0
#endif
