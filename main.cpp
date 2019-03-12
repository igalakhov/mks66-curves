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
#include "drawing/parametric/parametric.h"

void face_animation(){
    auto m = new EdgeMatrix();

    auto p = new MDLParser("../otherscript.mdl");

    p->run_file(m, TransformationMatrix::identity(), new Drawer());


    auto d = new Drawer();

    m->apply_transformation(TransformationMatrix::translation(-250, -250, 0));

    for(int i = 0; i < 360; i++){
        m->apply_transformation(TransformationMatrix::rotationY(2));
        m->apply_transformation(TransformationMatrix::translation(250, 250, 0));

        d = new Drawer();

        d->draw_edges(m);

        if(i < 10){
            d->save("../renders/face_rotate/face_00" + std::to_string(i) + ".ppm", ".ppm");

        } else if (i < 100){
            d->save("../renders/face_rotate/face_0" + std::to_string(i) + ".ppm", ".ppm");

        } else {
            d->save("../renders/face_rotate/face_" + std::to_string(i) + ".ppm", ".ppm");

        }

        std::cout << i << std::endl;

        m->apply_transformation(TransformationMatrix::translation(-250, -250, 0));

    }

    d->draw_edges(m);

    d->display();



}

int main(){

    //face_animation();

    //return 0;

    // renders the script
    auto d = new Drawer();

    auto m = new EdgeMatrix();
    auto t = TransformationMatrix::identity();

    auto p = new MDLParser("../script.mdl");

    p->run_file(m, t, d);

    d->save("../hello.ppm", "ppm");
}