#include <iostream>
#include "geometry.h"
#include "tgaimage.h"

int main(int argc, const char * argv[]) {
    
    Vec3f vec(1.0f, 0.0f, 0.0f);
    
    TGAImage image(100, 100, 4);
    
    for(int x=0; x<image.get_width(); x++) {
        for (int y=0; y<image.get_height(); y++) {
            image.set(x, y, TGAColor(x, y, 0));
        }
    }
    
    bool done = image.write_tga_file("image.tga");
    
    std::cout << "Hello, World!\n" << vec << "\n" << ( done ? "done" : "failed" ) << "\n";
    return 0;
}
