#include <SDL/SDL.h>
#include "Engine.h"

namespace ephidrena
{

void Engine::fastTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, SDL_Surface* ws)
{
    y1 = v1.y;
    y2 = v2.y;
    y3 = v3.y;

    x1 = v1.x;
    x2 = v2.x;
    x3 = v3.x;
    
    int        stride;
    Uint32*    pixels;

    SDL_LockSurface(ws);
	pixels = (Uint32*)ws->pixels;		
	if(pixels == NULL)
              return;

    // Bounding rectangle
    minx = (int)min(x1, x2, x3);
    maxx = (int)max(x1, x2, x3);
    miny = (int)min(y1, y2, y3);
    maxy = (int)max(y1, y2, y3);

    (char*&)pixels += miny * stride;

    // Scan through bounding rectangle
    for(int y = miny; y < maxy; y++)
    {
        for(int x = minx; x < maxx; x++)
        {
            // When all half-space functions positive, pixel is in triangle
            if((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 &&
               (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
               (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0)
            {
                pixels[x] = 0x00FFFFFF;   // White
            }
        }

        (char*&)pixels+= stride;
    }
}
/*
void Engine::triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    // 28.4 fixed-point coordinates
    const int Y1 = iround(16.0f * v1.y);
    const int Y2 = iround(16.0f * v2.y);
    const int Y3 = iround(16.0f * v3.y);

    const int X1 = iround(16.0f * v1.x);
    const int X2 = iround(16.0f * v2.x);
    const int X3 = iround(16.0f * v3.x);

    // Deltas
    const int DX12 = X1 - X2;
    const int DX23 = X2 - X3;
    const int DX31 = X3 - X1;

    const int DY12 = Y1 - Y2;
    const int DY23 = Y2 - Y3;
    const int DY31 = Y3 - Y1;

    // Fixed-point deltas
    const int FDX12 = DX12 << 4;
    const int FDX23 = DX23 << 4;
    const int FDX31 = DX31 << 4;

    const int FDY12 = DY12 << 4;
    const int FDY23 = DY23 << 4;
    const int FDY31 = DY31 << 4;

    // Bounding rectangle
    int minx = (min(X1, X2, X3) + 0xF) >> 4;
    int maxx = (max(X1, X2, X3) + 0xF) >> 4;
    int miny = (min(Y1, Y2, Y3) + 0xF) >> 4;
    int maxy = (max(Y1, Y2, Y3) + 0xF) >> 4;

    // Block size, standard 8x8 (must be power of two)
    const int q = 8;

    // Start in corner of 8x8 block
    minx &= ~(q - 1);
    miny &= ~(q - 1);

    (char*&)colorBuffer += miny * stride;

    // Half-edge constants
    int C1 = DY12 * X1 - DX12 * Y1;
    int C2 = DY23 * X2 - DX23 * Y2;
    int C3 = DY31 * X3 - DX31 * Y3;

    // Correct for fill convention
    if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
    if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
    if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;

    // Loop through blocks
    for(int y = miny; y < maxy; y += q)
    {
        for(int x = minx; x < maxx; x += q)
        {
            // Corners of block
            int x0 = x << 4;
            int x1 = (x + q - 1) << 4;
            int y0 = y << 4;
            int y1 = (y + q - 1) << 4;

            // Evaluate half-space functions
            bool a00 = C1 + DX12 * y0 - DY12 * x0 > 0;
            bool a10 = C1 + DX12 * y0 - DY12 * x1 > 0;
            bool a01 = C1 + DX12 * y1 - DY12 * x0 > 0;
            bool a11 = C1 + DX12 * y1 - DY12 * x1 > 0;
            int a = (a00 << 0) | (a10 << 1) | (a01 << 2) | (a11 << 3);
    
            bool b00 = C2 + DX23 * y0 - DY23 * x0 > 0;
            bool b10 = C2 + DX23 * y0 - DY23 * x1 > 0;
            bool b01 = C2 + DX23 * y1 - DY23 * x0 > 0;
            bool b11 = C2 + DX23 * y1 - DY23 * x1 > 0;
            int b = (b00 << 0) | (b10 << 1) | (b01 << 2) | (b11 << 3);
    
            bool c00 = C3 + DX31 * y0 - DY31 * x0 > 0;
            bool c10 = C3 + DX31 * y0 - DY31 * x1 > 0;
            bool c01 = C3 + DX31 * y1 - DY31 * x0 > 0;
            bool c11 = C3 + DX31 * y1 - DY31 * x1 > 0;
            int c = (c00 << 0) | (c10 << 1) | (c01 << 2) | (c11 << 3);

            // Skip block when outside an edge
            if(a == 0x0 || b == 0x0 || c == 0x0) continue;

            unsigned int *buffer = colorBuffer;

            // Accept whole block when totally covered
            if(a == 0xF && b == 0xF && c == 0xF)
            {
                for(int iy = 0; iy < q; iy++)
                {
                    for(int ix = x; ix < x + q; ix++)
                    {
                        buffer[ix] = 0x00007F00;   // Green
                    }

                    (char*&)buffer += stride;
                }
            }
            else   // Partially covered block
            {
                int CY1 = C1 + DX12 * y0 - DY12 * x0;
                int CY2 = C2 + DX23 * y0 - DY23 * x0;
                int CY3 = C3 + DX31 * y0 - DY31 * x0;

                for(int iy = y; iy < y + q; iy++)
                {
                    int CX1 = CY1;
                    int CX2 = CY2;
                    int CX3 = CY3;
      
                    for(int ix = x; ix < x + q; ix++)
                    {
                        if(CX1 > 0 && CX2 > 0 && CX3 > 0)
                        {
                            buffer[ix] = 0x0000007F;   // Blue
                        }

                        CX1 -= FDY12;
                        CX2 -= FDY23;
                        CX3 -= FDY31;
                    }

                    CY1 += FDX12;
                    CY2 += FDX23;
                    CY3 += FDX31;

                    (char*&)buffer += stride;
                }
            }
        }

        (char*&)colorBuffer += q * stride;
    }
}
*/
/*
int* Engine::max(int* v1, int* v2, int* v3)
{
     int* m = *v1 > *v2 ? v1 : v2;
     *m = *m > *v3 ? m : v3;
     return m;
     
}
*/
float Engine::max(float v1, float v2, float v3)
{
     float m = v1 > v2 ? v1 : v2;
     m = m > v3 ? m : v3;
     return m;
}

/*
int Engine::min(int *v1, int* v2, int* v3)
{
      m = *v1 < *v2 ? v1 : v2;
     *m = *m < *v3 ? m : v3
     return m;
}
*/
float Engine::min(float v1, float v2, float v3)
{
     float m = v1 < v2 ? v1 : v2;
     m = m < v3 ? m : v3;
     return m;
}


}
