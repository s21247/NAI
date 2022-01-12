#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> get_data_from_file(istream &file) {
    vector<vector<int>> graph;
    while (true) {
        char begin;
        char end;
        int cost;
        file >> begin;
        file >> end;
        file >> cost;
        if (file.eof()){
            break;
        }
        vector<int> edge = {(int)begin, (int)end, cost};
        graph.push_back(edge);
    }
    return graph;
}


int main (int argc, char **argv){
    string infile = argv[1];
    ifstream file_in(infile);
    vector<vector<int>> graph = get_data_from_file(file_in);
    string outfile = argv[2];
    ofstream file_out(outfile);


    file_out << "graph {\n";
    for(auto e:graph){
        file_out << (char)e[0]
                 << " -- "
                 << (char)e[1]
                 << "[label="
                 << e[2]
                 << "];\n";
    }
    file_out << "}";


    system("dot -Tpng g.dot -o g.png");
    return 0;
}
