//
// Created by Ivan Galakhov on 2019-02-19.
//

#include "edge_matrix.h"

// multiplication
void EdgeMatrix::apply_transformation(TransformationMatrix * m){
    auto new_matrix = (float_mat *) std::malloc(sizeof(float_mat) * 4 * num_points);

    multiply_recursive(m->get_start(), 0, num_points, new_matrix, 0); // will spawn a max of 16 threads

    std::free(vals);

    vals = new_matrix;
}

// recursive multiplication
void EdgeMatrix::multiply_recursive(float_mat * m, int start, int end, float_mat * new_matrix, int depth) {
    //std::cout << start << " " << end << "\n";

    if(depth == 0) { // if the depth is 0
        for (int i = start; i < end; i++) {
            for (int j = 0; j < 4; j++) {
                new_matrix[i * 4 + j] =
                        vals[i * 4 + 0] * m[j * 4 + 0] +
                        vals[i * 4 + 1] * m[j * 4 + 1] +
                        vals[i * 4 + 2] * m[j * 4 + 2] +
                        vals[i * 4 + 3] * m[j * 4 + 3];

            }
        }

        return;
    }

    // start two threads to do half the multiplication
    int mid = (end - start)/2;

    std::thread first_mult (&EdgeMatrix::multiply_recursive, this, m, start, mid, new_matrix, depth-1);
    std::thread second_mult (&EdgeMatrix::multiply_recursive, this, m, mid, end, new_matrix, depth-1);

    first_mult.join();
    second_mult.join();

}

// print self
void EdgeMatrix::print_self(){
    std::cout << "[\n";
    for(int j = 0; j < 4; j++){
        float_mat * s = vals + j;
        for(int i = 0; i < num_points; i++){
            float_mat val = s[4*i];
            if(val < 10){
                std::cout << " " << val << "    ";
            } else if(val < 100){
                std::cout << val << "    ";
            } else if(val < 1000){
                std::cout << val << "   ";
            } else if(val < 10000){
                std::cout << val << "  ";
            } else if(val < 100000){
                std::cout << val << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "]\n";
}

// add an edge
// TODO: make this work with triangles
void EdgeMatrix::add_edge(float_mat x1, float_mat y1, float_mat z1,
                          float_mat x2, float_mat y2, float_mat z2){
    add_point(x1, y1, z1);
    add_point(x2, y2, z2);

}

// add a point
void EdgeMatrix::add_point(float_mat x, float_mat y, float_mat z) {
    vals = (float_mat *) std::realloc(vals, (size_t) sizeof(float_mat) * (4*num_points + 4));

    float_mat * s = vals + num_points*4;

    *s = x;
    s++;
    *s = y;
    s++;
    *s = z;
    s++;
    *s = 1;

    num_points += 1;
}

// add a point (you can specify the 3rd value)
void EdgeMatrix::add_point(float_mat x, float_mat y, float_mat z, float_mat k) {
    vals = (float_mat *) std::realloc(vals, (size_t) sizeof(float_mat) * (4*num_points + 4));

    float_mat * s = vals + num_points*4;

    *s = x;
    s++;
    *s = y;
    s++;
    *s = z;
    s++;
    *s = k;

    num_points += 1;
}

int EdgeMatrix::get_size() {
    return num_points;
}

float_mat * EdgeMatrix::get_start() {
    return vals;
}

// constructor
EdgeMatrix::EdgeMatrix(){
    num_points = 0;
    vals = (float_mat *) std::malloc(0);
}

// static constructor thingy
EdgeMatrix * EdgeMatrix::from_transformation(TransformationMatrix * t) {
    auto * ret = new EdgeMatrix();

    float_mat * p = t->get_start();

    ret->add_point(p[0], p[4], p[8], p[12]);
    ret->add_point(p[1], p[5], p[9], p[13]);
    ret->add_point(p[2], p[6], p[10], p[14]);
    ret->add_point(p[3], p[7], p[11], p[15]);

    return ret;
}

// destructor
EdgeMatrix::~EdgeMatrix(){
    std::free(vals);
}