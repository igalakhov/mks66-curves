//
// Created by Ivan Galakhov on 2019-02-28.
//

#include "mdl_parser.h"

void MDLParser::run_file(EdgeMatrix * m, TransformationMatrix * t, Drawer * d) {
    std::ifstream file(file_name);
    std::string str;

    std::vector<std::string> args;

    while(std::getline(file, str)){
        trim(str);

        if(str == "line"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            m->add_edge(std::stof(args.at(0)), std::stof(args.at(1)), std::stof(args.at(2)),
                    std::stof(args.at(3)), std::stof(args.at(4)), std::stof(args.at(5)));
        } else if(str == "ident"){
            t->copy_vals(TransformationMatrix::identity());
        } else if(str == "display"){
            d->clear();
            d->draw_edges(m);
            d->display();
        } else if(str == "scale"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            t->add_transformation(TransformationMatrix::dilation(
                    std::stof(args.at(0)),
                    std::stof(args.at(1)),
                    std::stof(args.at(2))
                    ));
        } else if(str == "translate"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            t->add_transformation(TransformationMatrix::translation(
                    std::stof(args.at(0)),
                    std::stof(args.at(1)),
                    std::stof(args.at(2))
            ));
        } else if(str == "rotate"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            if(args.at(0) == "x"){
                t->add_transformation(TransformationMatrix::rotationX(
                        std::stof(args.at(1))
                        ));
            }
            if(args.at(0) == "y"){
                t->add_transformation(TransformationMatrix::rotationY(
                        std::stof(args.at(1))
                ));
            }
            if(args.at(0) == "z"){
                t->add_transformation(TransformationMatrix::rotationZ(
                        std::stof(args.at(1))
                ));
            }
        } else if(str == "apply"){
            m->apply_transformation(t);
        } else if(str == "save"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            d->clear();
            d->draw_edges(m);
            d->save(args.at(0), ".ppm");
        } else if(str == "quit"){
            return;
        } else {
            throw std::invalid_argument("Invalid command [" + str + "]");
        }

    }
}

MDLParser::MDLParser(std::string file_name) {
    this->file_name = std::move(file_name);
}

MDLParser::~MDLParser(){
    // nothing here yet
}

// split string
std::vector<std::string> MDLParser::split_string(std::string str){
    std::string buf;
    std::stringstream ss(str);

    std::vector<std::string> tokens;

    while (ss >> buf)
        tokens.push_back(buf);

    return tokens;
}

// string trimming
void MDLParser::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void MDLParser::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void MDLParser::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
