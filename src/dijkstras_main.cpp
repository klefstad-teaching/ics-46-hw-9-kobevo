#include "dijkstras.cpp"

int main(int argc, char *argv[]) {
    string file_name = get_arg(argc, argv, "src/small.txt");
    Graph G;
    file_to_graph(file_name, G);
}