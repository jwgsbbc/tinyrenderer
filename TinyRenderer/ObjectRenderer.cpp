//
//  ObjectRenderer.cpp
//  TinyRenderer
//
//  Created by James Shephard on 02/06/2017.
//  Copyright © 2017 James Shephard. All rights reserved.
//

#include "ObjectRenderer.hpp"

ObjectRenderer::ObjectRenderer(Model& model, TgaTarget& target) : model(model), target(target) {
    position = Vec3f(0.0f,0.0f,0.0f);
    scale = 1.0f;
}

void ObjectRenderer::setPosition(const Vec3f &position) {
    this->position = position;
}

void ObjectRenderer::setScale(const float scale) {
    this->scale = scale;
}

void ObjectRenderer::renderWireFrame() {
    for (int i=0; i<model.nfaces(); i++) {
        auto tris = get2DFaceTris(i);
        target.drawLine(tris[0], tris[1], TGAColors::WHITE);
        target.drawLine(tris[1], tris[2], TGAColors::WHITE);
        target.drawLine(tris[2], tris[0], TGAColors::WHITE);
    }
}

std::vector<Vec2i> ObjectRenderer::get2DFaceTris(int i) {
    std::vector<Vec2i> ret;
    auto tris = get3DFaceTris(i);
    ret.push_back(Vec2i(tris[0].x, tris[0].y));
    ret.push_back(Vec2i(tris[1].x, tris[1].y));
    ret.push_back(Vec2i(tris[2].x, tris[2].y));
    return ret;
}

std::vector<Vec3f> ObjectRenderer::get3DFaceTris(int i) {
    std::vector<Vec3f> ret;
    auto face = model.face(i);
    auto v0 = model.vert(face[0]);
    auto v1 = model.vert(face[1]);
    auto v2 = model.vert(face[2]);
    ret.push_back(position + ( v0 * scale ) );
    ret.push_back(position + ( v1 * scale ) );
    ret.push_back(position + ( v2 * scale ) );
    return ret;
}

class ColourShader: public PixelShader {
private:
    int face;
    Model model;
    
public:
    ColourShader(int face, Model model) : face(face), model(model) {
    }
    
    virtual const TGAColor color(Vec3f bary) {
        Vec2f t0 = model.uv(face, 0);
        Vec2f t1 = model.uv(face, 1);
        Vec2f t2 = model.uv(face, 2);
        float u = t0.x*bary.x + t1.x*bary.y + t2.x*bary.z;
        float v = t0.y*bary.x + t1.y*bary.y + t2.y*bary.z;
        TGAColor col = model.diffuse(Vec2f(u,v));
        col[3] = 255;
        return col;
    }
};

void ObjectRenderer::renderFilled() {
    for (int i=0; i<model.nfaces(); i++) {
        auto verts = get3DFaceTris(i);
        Vec3f ab = verts[0] - verts[1];
        Vec3f ac = verts[0] - verts[2];
        Vec3f cp = cross(ab, ac);
        if(cp.z<=0.0f) {
            cp.normalize();
            cp = cp * 250.0f;
            auto col = TGAColor(std::max(0.0f,cp.x),
                                std::max(0.0f,cp.y),
                                std::max(0.0f,cp.x));
            ColourShader shader(i, model);
            target.draw3DTri(verts[0], verts[1], verts[2], shader);
        }
    }
}

