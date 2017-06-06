//
//  tgatarget.hpp
//  TinyRenderer
//
//  Created by James Shephard on 02/06/2017.
//  Copyright © 2017 James Shephard. All rights reserved.
//

#ifndef tgatarget_hpp
#define tgatarget_hpp

#include <stdio.h>
#include "tgaimage.h"
#include "geometry.h"

class PixelShader {
public:
    virtual const TGAColor color(Vec3f bary) = 0;
};

class TgaTarget {
    
private:
    
    TGAImage &tgaImage;
    std::vector<float> zBuffer;
    
    
public:
    
    TgaTarget(TGAImage &tgaImage);
    
    void drawLine(const Vec2i &start, const Vec2i &end, const TGAColor& colour);
    
    void drawTri(const std::vector<Vec2i> verts, const TGAColor& colour);
    
    void draw3DTri(Vec3f v0, Vec3f v1, Vec3f v2, PixelShader& shader);

    
private:
    
    void drawLToRLine(const Vec2i &start, const Vec2i &end, const TGAColor &colour);
    
    void drawShallowLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection);
    
    void drawSteepLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection);

    Vec2i project(const Vec3f &v);
    
    Vec2i bottomLeft(const Vec2i &v0, const Vec2i &v1, const Vec2i &v2);

    Vec2i topRight(const Vec2i &v0, const Vec2i &v1, const Vec2i &v2);

    Vec3f barycentric(Vec2f p, Vec2f a, Vec2f b, Vec2f c);
    
};

#endif /* tgatarget_hpp */
