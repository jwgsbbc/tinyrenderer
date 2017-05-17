#include <iostream>
#include "geometry.h"
#include "tgaimage.h"
#include "model.h"

int main(int argc, const char * argv[]) {
    
    Model model("obj/diablo3_pose/diablo3_pose.obj");
    
    std::cout << "loaded model, " << model.nfaces() << " faces\n";
    
    Vec3f vec(1.0f, 0.0f, 0.0f);
    
    TGAImage image(256, 256, 4);
    
    for(int x=0; x<image.get_width(); x++) {
        for (int y=0; y<image.get_height(); y++) {
            image.set(x, y, TGAColor(x, y, 0));
        }
    }
    
    bool done = image.write_tga_file("image.tga");
    
    std::cout << "Hello, World!\n" << vec << "\n" << ( done ? "done" : "failed" ) << "\n";
    
    return 0;
}
