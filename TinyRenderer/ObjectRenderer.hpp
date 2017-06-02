//
//  ObjectRenderer.hpp
//  TinyRenderer
//
//  Created by James Shephard on 02/06/2017.
//  Copyright © 2017 James Shephard. All rights reserved.
//

#ifndef ObjectRenderer_hpp
#define ObjectRenderer_hpp

#include <stdio.h>
#include "model.h"
#include "tgatarget.hpp"

typedef mat<3,3,float> M33;

class ObjectRenderer {
    
private:
    
    Model& model;
    TgaTarget& target;
    Vec3f position;
    float scale;
    
public:
    
    ObjectRenderer(Model& model, TgaTarget& target);
    
    void setPosition(const Vec3f& position);
    void setScale(const float scale);
    void renderWireFrame();
    void renderFilled();
    
private:
    
    std::vector<Vec2i> get2DFaceTris(int i);
    std::vector<Vec3f> get3DFaceTris(int i);
    
};

#endif /* ObjectRenderer_hpp */
