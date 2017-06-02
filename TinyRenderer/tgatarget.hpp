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
    
    
public:
    
    TgaTarget(TGAImage &tgaImage);
    
    void drawLine(const Vec2i &start, const Vec2i &end, const TGAColor& colour);
    
    void drawTri(const std::vector<Vec2i> verts, const TGAColor& colour);
    
private:
    
    void drawLToRLine(const Vec2i &start, const Vec2i &end, const TGAColor &colour);
    
    void drawShallowLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection);
    
    void drawSteepLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection);

};

#endif /* tgatarget_hpp */
