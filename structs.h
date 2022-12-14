#ifndef LAB1V2_STRUCTS_H
#define LAB1V2_STRUCTS_H
#include <vector>
#include <iostream>
#include <list>
#define OBSTACLE 1
#define TRAVERSABLE 0
#define PATH 2

struct Node
{
    double g;
    double h;
    double f;
    int i;
    int j;
    const Node* parent;
    Node(int _i=-1, int _j=-1, double _g=0, double _h=0, Node* _parent=nullptr):i(_i), j(_j), g(_g), h(_h), f(_h+_g), parent(_parent){}
    bool operator ==(const Node& other) const
    {
        return this->i == other.i && this->j == other.j;
    }
    bool operator <(const Node& other) const
    {
        return this->i < other.i || (this->i == other.i && this->j < other.j);
    }
};

struct CompareHeuristic {
    bool operator()(Node const& n1, Node const& n2)
    {
        return n1.f > n2.f;
    }
};

struct Result
{
    std::list<Node> path; //путь
    double cost; //стоимость пути
    double runtime; //время работы алгоритма
    int steps; //число итераций работы алгоритма
    int nodes_created; //число созданных вершин
};

struct Map
{
    int width;
    int height;
    std::vector<std::vector<int>> grid;
    Map(int _width=0, int _height=0):width(_width), height(_height)
    {
        grid = std::vector<std::vector<int>>(height, std::vector<int>(width, TRAVERSABLE));
    }
    void add_obstacle(int i, int j)
    {
        grid[i][j] = OBSTACLE;
    }
    bool cell_on_grid(int i, int j)
    {
        return (i >= 0 && j >=0 && i < height && j < width);
    }
    bool cell_is_obstacle(int i, int j)
    {
        return grid[i][j] == OBSTACLE;
    }
    double get_cost(Node current, Node neighbor, double hw) {
        if ((current.i != neighbor.i) && (current.j != neighbor.j))
            return sqrt(2);
        else
            return 1;
    }
    std::vector<Node> get_neighbors(Node s, int connections)
    {
  
        std::vector<std::pair<int, int>> deltas = {{0,1}, {1,0}, {-1,0}, {0,-1}};
        std::vector<Node> neighbors;
        for(auto d:deltas)
        {
            Node n(s.i + d.first, s.j + d.second);
            if(cell_on_grid(n.i, n.j) && !cell_is_obstacle(n.i, n.j))
                neighbors.push_back(n);
        }
        if (connections == 8)
        {
            std::list<std::pair<int, int>> deltas2 = { {1, 1}, {-1, -1}, {1, -1},  {-1, 1} };
            for (auto d : deltas2) {
                Node n(s.i+d.first, s.j+d.second);
                if (cell_on_grid(n.i, n.j) && !cell_is_obstacle(n.i, n.j) && !cell_is_obstacle(n.i-d.first, n.j) && !cell_is_obstacle(n.i, n.j-d.second))
                {
                        neighbors.push_back(n);
                }
            }
        }
        return neighbors;
    }
    void print(std::list<Node> path={})
    {
        for(auto n:path)
            grid[n.i][n.j] = PATH;
        for(int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                if (grid[i][j] == OBSTACLE)
                    std::cout << "# ";
                else if (grid[i][j] == TRAVERSABLE)
                    std::cout << ". ";
                else
                    std::cout << "@ ";
            std::cout<<std::endl;
        }
        for(auto n:path)
            grid[n.i][n.j] = TRAVERSABLE;
    }
};
#endif //LAB1V2_STRUCTS_H
