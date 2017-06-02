//
//  tgatarget.cpp
//  TinyRenderer
//
//  Created by James Shephard on 02/06/2017.
//  Copyright © 2017 James Shephard. All rights reserved.
//

#include "tgatarget.hpp"

TgaTarget::TgaTarget(TGAImage &tgaImage) : tgaImage(tgaImage) {
    
}

void TgaTarget::drawLine(const Vec2i &start, const Vec2i &end, const TGAColor &colour) {
    if(start.x>end.x) {
        drawLToRLine(end, start, colour);
    }
    else {
        drawLToRLine(start, end, colour);
    }
}

void TgaTarget::drawLToRLine(const Vec2i &start, const Vec2i &end, const TGAColor &colour) {
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int yDirection = (dy>0) ? 1 : -1;
    if(std::abs(dy)<=dx) {
        drawShallowLToRLine(start, end, colour, yDirection);
    }
    else {
        drawSteepLToRLine(start, end, colour, yDirection);
    }
}

void TgaTarget::drawShallowLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection) {
        int dx = end.x - start.x;
    int dy = end.y - start.y;
    int stepAdd = dy*yDirection;
    int stepper = 0;
    int y = start.y;

    for(int x=start.x; x!=end.x; x++) {
        tgaImage.set(x, y, colour);
        stepper += stepAdd;
        if(stepper>=dx) {
            y+=yDirection;
            stepper-=dx;
        }
    }
}

void TgaTarget::drawSteepLToRLine(const Vec2i &start, const Vec2i end, const TGAColor &colour, int yDirection) {
    
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int xDirection = (dx>0) ? 1 : -1;
    int stepAdd = dx*xDirection;
    int dyCmp = dy*yDirection;
    int stepper = 0;
    int x = start.x;

    for(int y=start.y; y!=end.y; y+=yDirection) {
        tgaImage.set(x, y, colour);
        stepper += stepAdd;
        if(stepper>=dyCmp) {
            x+=xDirection;
            stepper-=dyCmp;
        }
    }
}

void TgaTarget::drawTri(const std::vector<Vec2i> verts, const TGAColor &colour) {

    int maxX = 0;
    int maxY = 0;
    int minX = INT_MAX;
    int minY = INT_MAX;
    
    for(auto it=verts.begin() ; it < verts.end(); it++ ) {
        auto v = (*it);
        maxX = std::max(maxX, v.x);
        maxY = std::max(maxY, v.y);
        minX = std::min(minX, v.x);
        minY = std::min(minY, v.y);
    }
    
    Vec2i ab = verts[1] - verts[0];
    Vec2i bc = verts[2] - verts[1];
    Vec2i ca = verts[0] - verts[2];
    
    // take the tangent
    Vec2i tab = Vec2i(ab.y, -ab.x);
    Vec2i tbc = Vec2i(bc.y, -bc.x);
    Vec2i tca = Vec2i(ca.y, -ca.x);
    
    for(int x=minX; x<=maxX; x++) {
        for(int y=minY; y<=maxY; y++) {
            auto pos = Vec2i(x, y);
            float xAb = tab * (pos - verts[0]);
            float xBc = tbc * (pos - verts[1]);
            float xCa = tca * (pos - verts[2]);
            if( xAb>=0 && xBc>=0 && xCa>=0 ) {
                tgaImage.set(x, y, colour);
            }
        }
    }
}


