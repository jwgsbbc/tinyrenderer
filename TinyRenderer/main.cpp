#include <iostream>
#include "geometry.h"
#include "tgaimage.h"
#include "tgatarget.hpp"
#include "model.h"
#include "ObjectRenderer.hpp"
#include <math.h>

int main(int argc, const char * argv[]) {
    
    Model model("obj/diablo3_pose/diablo3_pose.obj");
    
    std::cout << "loaded model, " << model.nfaces() << " faces\n";
    
    Vec3f vec(1.0f, 0.0f, 0.0f);
    
    TGAImage image(512, 512, 4);
    
    for(int x=0; x<image.get_width(); x++) {
        for (int y=0; y<image.get_height(); y++) {
            image.set(x, y, TGAColor(128, 128, 128));
        }
    }
    
    TgaTarget target(image);
    
    ObjectRenderer objRender(model, target);
    
    objRender.setPosition(Vec3f(256.0f,256.0,0.0));
    objRender.setScale(256.0);
    
    // objRender.renderWireFrame();
    
    objRender.renderFilled();
    
    image.flip_vertically();
    
    bool done = image.write_tga_file("image.tga");
    
    std::cout << "Hello, World!\n" << vec << "\n" << ( done ? "done" : "failed" ) << "\n";
    
    
    
    return 0;
}
