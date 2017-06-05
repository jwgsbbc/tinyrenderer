//
//  tgatarget.cpp
//  TinyRenderer
//
//  Created by James Shephard on 02/06/2017.
//  Copyright © 2017 James Shephard. All rights reserved.
//

#include "tgatarget.hpp"

TgaTarget::TgaTarget(TGAImage &tgaImage) : tgaImage(tgaImage) {
    int size = tgaImage.get_width()*tgaImage.get_height();
    for (int i=0; i<size; i++) {
        zBuffer.push_back(10000.0f);
    }
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

void TgaTarget::draw3DTri(Vec3f v30, Vec3f v31, Vec3f v32, const TGAColor &col) {
    
    Vec2i v20 = project(v30);
    Vec2i v21 = project(v31);
    Vec2i v22 = project(v32);
    Vec2i vBL = bottomLeft(v20, v21, v22);
    Vec2i vTR = topRight(v20, v21, v22);

    Vec2f v20f(v20.x, v20.y);
    Vec2f v21f(v21.x, v21.y);
    Vec2f v22f(v22.x, v22.y);
    
    for(int x=vBL.x; x<=vTR.x; x++) {
        for(int y=vBL.y; y<=vTR.y; y++) {
            Vec3f bary = barycentric(Vec2f(x,y), v20f, v21f, v22f);
            if(bary.x>=0.0 && bary.y>=0.0f && bary.z>=0.0f) {
                float z = v30.z*bary.x + v31.z*bary.y + v32.z+bary.z;
                int zIndex = y*tgaImage.get_width()+x;
                float zTest = zBuffer[zIndex];
                if(zTest>=z) {
                    zBuffer[zIndex] = z;
                    tgaImage.set(x, y, col);
                }
            }
        }
    }
}

Vec2i TgaTarget::project(const Vec3f &v) {
    return Vec2i(v.x, v.y);
}

Vec2i TgaTarget::bottomLeft(const Vec2i &v0, const Vec2i &v1, const Vec2i &v2) {
    int minX = std::min(v0.x, std::min(v1.x, std::min(v2.x, tgaImage.get_width()-1)));
    int minY = std::min(v0.y, std::min(v1.y, std::min(v2.y, tgaImage.get_height()-1)));
    return Vec2i(minX, minY);
}

Vec2i TgaTarget::topRight(const Vec2i &v0, const Vec2i &v1, const Vec2i &v2) {
    int maxX = std::max(v0.x, std::max(v1.x, std::max(v2.x, 0)));
    int maxY = std::max(v0.y, std::max(v1.y, std::max(v2.y, 0)));
    return Vec2i(maxX, maxY);
}

Vec3f TgaTarget::barycentric(Vec2f p, Vec2f a, Vec2f b, Vec2f c) {
    Vec2f v0 = b - a;
    Vec2f v1 = c - a;
    
    float d00 = v0 * v0;
    float d01 = v0 * v1;
    float d11 = v1 * v1;
    float denom = d00 * d11 - d01 * d01;

    Vec2f v2 = p - a;
    float d20 = v2 * v0;
    float d21 = v2 * v1;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    
    return Vec3f(u,v,w);
}

