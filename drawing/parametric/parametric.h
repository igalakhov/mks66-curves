//
// Created by Ivan Galakhov on 2019-03-09.
//

#ifndef WORK_01_LINE_PARAMETRIC_H
#define WORK_01_LINE_PARAMETRIC_H

#include <iostream>
#include <tuple>

#include "../../matrix/edge_matrix.h"

void draw_parametric(EdgeMatrix *, std::tuple<float, float> * (float), float, float); // t is from 0 to 1 always
                                                                         // second parameter is step size
                                                                         // last one is z coordinate
void draw_circle(EdgeMatrix *, float, float, float, float);
void draw_bezier(EdgeMatrix *, float, float, float, float, float, float, float, float);
void draw_hermite(EdgeMatrix *, float, float, float, float, float, float, float, float);

#endif //WORK_01_LINE_PARAMETRIC_H
