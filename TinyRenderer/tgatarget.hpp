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

class TgaTarget {
    
private:
    
    TGAImage &tgaImage;
    std::vector<float> zBuffer;
    
    
public:
    
    TgaTarget(TGAImage &tgaImage);
    
    void drawLine(const Vec2i &start, const Vec2i &end, const TGAColor& colour);
    
    void drawTri(const std::vector<Vec2i> verts, const TGAColor& colour);
    
    void draw3DTri(Vec3f v0, Vec3f v1, Vec3f v2);
    
private:
    
    void drawLToRLine(const Vec2i &start, const Vec2i &end, const TGAColor &colour);
    
    void drawShallowLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection);
    
    void drawSteepLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection);

    Vec2f project(const Vec3f &v);
    
    Vec2f bottomLeft(const Vec2i &v0, const Vec2i &v1, const Vec2i &v2);

    Vec2f topRight(const Vec2i &v0, const Vec2i &v1, const Vec2i &v2);

    
};

#endif /* tgatarget_hpp */
