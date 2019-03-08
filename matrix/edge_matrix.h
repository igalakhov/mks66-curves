//
// Created by Ivan Galakhov on 2019-02-19.
//

#ifndef WORK_01_LINE_EDGE_MATRIX_H
#define WORK_01_LINE_EDGE_MATRIX_H

#include "transformation_matrix.h"
#include "../settings.h"

#include <iostream>
#include <thread>
#include "math.h"

class TransformationMatrix;
class EdgeMatrix {
public:
    EdgeMatrix(); // constructor
    ~EdgeMatrix(); // destructor

    void add_edge(float_mat, float_mat, float_mat, float_mat, float_mat, float_mat); // add a new edge
    void print_self(); // print self out
    int get_size(); // return number of edges
    float_mat * get_start(); // return pointer to start of matrix
    void apply_transformation(TransformationMatrix *); // apply a transformation
    void multiply_recursive(float_mat *, int, int, float_mat *, int);

    // transformations
    // TODO: move transformations into transformation_matrix and only keep apply_transformations here

    // not really used either
    void add_point(float_mat, float_mat, float_mat, float_mat);

    // static methods
    static EdgeMatrix * from_transformation(TransformationMatrix *); // creates a new Edge matrix from transformation matrix

private:
    void add_point(float_mat, float_mat, float_mat);
    float_mat * vals;
    int num_points;
};


#endif //WORK_01_LINE_EDGE_MATRIX_H
