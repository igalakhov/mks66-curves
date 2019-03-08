#include <iostream>
#include <zconf.h>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "drawing/display.h"
#include "drawing/drawer.h"
#include "matrix/edge_matrix.h"
#include "matrix/transformation_matrix.h"
#include "parsing/obj_parser.h"
#include "parsing/mdl_parser.h"

int main(){


    for(int i = 1; i <= 206; i++){
        std::string f_name = "../resources/default_dance/dance_000";


        if(i < 10){
            f_name += "00" + std::to_string(i);
        } else if(i < 100){
            f_name += "0" + std::to_string(i);
        } else {
            f_name += "" + std::to_string(i);
        }

        f_name += ".obj";

        float r = (float) ((i-1)/206.0) * 360; // rotation

        std::cout << f_name << std::endl;
        std::cout << r << std::endl;

        auto o = new OBJFileParser(f_name);

        auto e = o->get_edge_matrix();

        e->apply_transformation(TransformationMatrix::dilation(110, 110, 110));
        e->apply_transformation(TransformationMatrix::rotationX(180));
        e->apply_transformation(TransformationMatrix::rotationY(r));
        e->apply_transformation(TransformationMatrix::translation(250, 450, 0));

        auto d = new Drawer();

        d->draw_edges(e);

        if(i < 10) {
            d->save("../renders/default_dance/dance_00" + std::to_string(i) + ".ppm", ".ppm");
        } else if(i < 100){
            d->save("../renders/default_dance/dance_0" + std::to_string(i) + ".ppm", ".ppm");
        } else {
            d->save("../renders/default_dance/dance_" + std::to_string(i) + ".ppm", ".ppm");
        }

    }

    return 0;

    auto o = new OBJFileParser("../resources/default_dance/dance_000050.obj");

    auto e = o->get_edge_matrix();

    e->apply_transformation(TransformationMatrix::dilation(110, 110, 110));
    e->apply_transformation(TransformationMatrix::rotationX(180));
    e->apply_transformation(TransformationMatrix::rotationY(20));
    e->apply_transformation(TransformationMatrix::translation(250, 450, 0));

    auto d = new Drawer();

    d->draw_edges(e);

    d->display();

    return 0;

    // initialize the parser and parse commands
    // the return type of the parse is a vector of vectors because that's the easiest to iterate/parse
    // we also know that if the parser returns something, it's 100% with correct syntax and format

    std::cout << "Note: this graphics engine uses a different coordinate system with (0, 0) on the top right" << std::endl;
    std::cout << "If a script outputs something else it's because of that and not because my code is bad or anything" << std::endl;

    auto p = new MDLParser("script.mdl");

    p->run_file(new EdgeMatrix(), TransformationMatrix::identity(), new Drawer());
}