#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef union rep
{
    float f;
    u_int32_t i;
}rep;


float i2f(u_int32_t i)
{
    rep r;
    r.i=i;
    return r.f;
}

u_int32_t f2i(float f)
{
    rep r;
    r.f=f;
    return r.i;
}

typedef union rep2
{
    double d;
    int32_t i;
}rep2;


float i2d(int32_t i)
{
    rep2 r;
    r.i=i;
    return r.d;
}

int32_t d2i(double d)
{
    rep2 r;
    r.d=d;
    return r.i;
}




int32_t float2int(int32_t f) {
    int32_t s = f >> 31; /* -1 jeśli znak był ujemny */
    int32_t e = (f >> 23 & 255) - 127; /* wykładnik po odjęciu bias */
    u_int32_t m = f << 8 | 0x80000000; /* mantysa 1.xxx... dosunięta do lewej */

    //int32_t s = f < 0 ? -1 : 1;
    //int32_t m = (f & 0x7fffff) | 0x800000;
    //int32_t e = (f & 0x7f800000) - 127 - 23; // o ile przesunąć m w prawo

    printf("%d %d %d\n", s, e, m);

    // if (e > 7) { // nadmiar
    //     return 0x80000000;
    // }
    // if (e > 0) {
    //     return s * (m << e);
    // } else if (e < -23) {
    //     return 0;
    // } else {
    //     return s * (m >> -e);
    // }

    if (e > 29) { // nadmiar
        return 0x80000000;
    }
    if (e > 0) {
        return s * m>>(31-(e+1));
    } else if (e < -23) {
        return 0;
    } else {
        return s * m>>(31-(e+1));
    }
}



int main()
{
int32_t f=3;
int32_t X=float2int(f);
printf("%d\n", X);
//zad.7.
// float f=3.52;

// u_int32_t f2=f2i(f);

// u_int32_t i = 3;

// printf("%d\n", f2);
// i=i<<23;

// f2+=i;

// float f3=i2f(f2);

// printf("%f %f\n", f, f3);

    //int32_t x=1, y=2, z=3;
    // int32_t x=INT_MAX, y=INT_MIN, z=INT_MIN;
    //double dx = i2d(x);
    //double dy = i2d(y);
    //double dz = i2d(z);
    // double dx = (double)x;
    // double dy = (double)y;
    // double dz = (double)z;
//     printf("%d %f\n", z, dz);

//  for(int32_t i=INT_MIN; i<=INT_MAX; i++)
//     {
//     int32_t x= (int32_t)i;
//     double dx = (double)x;
//     if((float)x == (float)dx)
//     {
//         //printf("TAK\n");
//         continue;
//     }
//     else
//     {
//         //printf("NIE\n");
//         printf("%d\n", i);
//         break;
//     }
//     }



// putchar('\n');
//     if(dx - dy == (double)(x - y))
//     {
//         printf("TAK\n");
//     }
//     else
//     {
//         printf("NIE\n");
//     }

//     if((dx + dy) + dz == dx + (dy + dz))
//     {
//         printf("TAK\n");
//     }
//     else
//     {
//         printf("NIE\n");
//     }

//     if((dx * dy) * dz == dx * (dy * dz))
//     {
//         printf("TAK\n");
//     }
//     else
//     {
//         printf("NIE\n");
//     }

    // if((dx / dx) == (dz / dz))
    // {
    //     printf("TAK\n");
    // }
    // else
    // {
    //     printf("NIE\n");
    // }


//zad.6.
// float f=1.5, g=-3.0;
// u_int32_t x = f2i(f);
// u_int32_t y = f2i(g);
// printf("%d %f %d %f\n", x, f, y, g);
// f=i2f(x);
// g=i2f(y);
// printf("%d %f %d %f\n", x, f, y, g);

// x^=(1<<31);
// f=i2f(x);
// printf("%d %f %d %f\n", x, f, y, g);

// y|=0x80000000;
// y&=0x7FFFFFFF;
// g=i2f(y);
// //y=y>>23;
// //y-=127;
// printf("%d %f %d %f\n", x, f, y, g);

// int32_t X=0;
// double x=(double)X;

// u_int32_t y=d2i(x);
// y&=0;
// u_int32_t y2 = d2i(x);

// y2|= (1<<31);

// float x1 = i2d(y);
// float x2 = i2d(y2);
// printf("%f %f %f\n", x, x1, x2);

u_int32_t x, y;
(((~(x | y) & (x - y)) | (x & y & (y - x)) | (x & ~y)) & 0x80000000) != 0 & ((x | y) != 0x80000000);
    return 0;
}

