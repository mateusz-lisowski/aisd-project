#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>


template<typename T>
struct vector
{
    vector()
        :data(nullptr), size(0), cap(0) {
    }

    ~vector() {
        if (data != nullptr)
            delete[] data;
    }

    vector(const vector& o) = delete;

    vector& operator=(const vector& o) = delete;

    vector(vector&& o) {
        data = o.data;
        size = o.size;
        cap = o.cap;
        o.data = nullptr;
        o.size = 0;
        o.cap = 0;
    }

    vector& operator=(vector&& o) {
        data = o.data;
        size = o.size;
        cap = o.cap;
        o.data = nullptr;
        o.size = 0;
        o.cap = 0;
        return *this;
    }

    void push_back(const T& t) {
        push_back(std::move(T(t)));
    }

    void push_back(T&& t) {
        if (size + 1 > cap) {
            cap = (cap + 1) * 2;
            T* new_data = new T[cap];
            for (int i = 0; i < size; i++)
                new_data[i] = std::move(data[i]);
            if (data)
                delete[] data;
            data = new_data;
        }
        data[size] = std::move(t);
        size++;
    }

    T* begin() const {
        return data;
    }

    T* end() const {
        return data + size;
    }

    size_t get_size() const {
        return size;
    }

    T& at(size_t i) const {
        return data[i];
    }

    T* data;
    size_t size;
    size_t cap;
};

struct Node;

struct City {

    char name[100];

    int pos_x;
    int pos_y;

    Node* node;
};

struct Edge {

    Node* node;
    int cost;

};

struct Node {

    vector<Edge> neighbours;

    int pos_x;
    int pos_y;

};

struct Data {


};

void swap(City& c1, City& c2) {
    char tmp[100];
    memcpy(tmp, c1.name, 100);
    memcpy(c1.name, c2.name, 100);
    memcpy(c2.name, tmp, 100);
}

int partition(City* arr, int low, int high) {

    char* pivot = arr[high].name;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].name, pivot) < 0) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort(City* arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

int binary_search(City* arr, int l, int r, char* x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (strcmp(arr[m].name, x) == 0)
            return m;

        if (strcmp(arr[m].name, x) < 0)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}


void read_city_name_right(char* map, int pos, char* city_name) {
    int i = 0;
    while (isalpha(map[pos])) {
        city_name[i] = map[pos];
        map[pos] = '.';
        i++;
        pos++;
    }
    city_name[i] = '\0';
}

void read_city_name_left(char* map, int pos, char* city_name) {
    int i = 0;
    while (isalpha(map[pos])) {
        city_name[i] = map[pos];
        map[pos] = '.';
        i++;
        pos--;
    }
    for (int j = 0; j < i / 2; j++) {
        char tmp = city_name[j];
        city_name[j] = city_name[i - j - 1];
        city_name[i - j - 1] = tmp;
    }
    city_name[i] = '\0';
}

void read_city_name(char* map, int pos, int map_width, char* city_name) {

    if (isalpha(map[pos - map_width]) && isalpha(map[pos - map_width - 1])) {
        // zacznij wczytywa� od pozycji: pos - map_width -> na lewo
        read_city_name_left(map, pos - map_width, city_name);
    }

    else if (isalpha(map[pos - map_width - 1])) {
        // zacznij wczytywa� od pozycji: pos - map_width - 1 -> na lewo
        read_city_name_left(map, pos - map_width - 1, city_name);
    }

    else if (isalpha(map[pos - 1])) {
        // zacznij wczytywa� od pozycji: pos - 1 -> na lewo
        read_city_name_left(map, pos - 1, city_name);
    }

    else if (isalpha(map[pos + map_width]) && isalpha(map[pos + map_width - 1])) {
        // zacznij wczytywa� od pozycji: pos + map_width -> na lewo
        read_city_name_left(map, pos + map_width, city_name);
    }

    else if (isalpha(map[pos + map_width - 1])) {
        // zacznij wczytywa� od pozycji: pos + map_width - 1 -> na lewo
        read_city_name_left(map, pos + map_width - 1, city_name);
    }

    else if (isalpha(map[pos - map_width]) && isalpha(map[pos - map_width + 1])) {
        // zacznij wczytywa� od pozycji: pos - map_width -> na prawo
        read_city_name_right(map, pos - map_width, city_name);
    }

    else if (isalpha(map[pos - map_width + 1])) {
        // zacznij wczytywa� od pozycji: pos - map_width + 1 -> na prawo
        read_city_name_right(map, pos - map_width + 1, city_name);
    }

    else if (isalpha(map[pos + 1])) {
        // zacznij wczytywa� od pozycji: pos + 1 -> na prawo
        read_city_name_right(map, pos + 1, city_name);
    }

    else if (isalpha(map[pos + map_width]) && isalpha(map[pos + map_width + 1])) {
        // zacznij wczytywa� od pozycji: pos + map_width -> na prawo
        read_city_name_right(map, pos + map_width, city_name);
    }

    else if (isalpha(map[pos + map_width + 1])) {
        // zacznij wczytywa� od pozycji: pos + map_width + 1 -> na prawo
        read_city_name_right(map, pos + map_width + 1, city_name);
    }
}

char* parse_cities(vector<City>& cities, int map_size_x, int map_size_y) {
    
    size_t size = map_size_x * map_size_y;

    char* map = new char[size + 1];

    for (int i = 0; i < map_size_y; i++) {
        char line[1024];
        fgets(line, 1024, stdin);
        for (int j = 0; j < map_size_x; j++) {
            map[i * map_size_x + j] = line[j];
        }
    }
    map[size] = '\0';

    for (int i = 0; i < size; i++) {
        if (map[i] == '*') {
            struct City city;
            city.pos_y = i / map_size_x;
            city.pos_x = i - city.pos_y * map_size_x;
                
            read_city_name(map, i, map_size_x, city.name);

            cities.push_back(city);
            
        }
    }

    return map;
}

void show_map(char* map, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            putchar(map[i * width + j]);
        }
        putchar('\n');
    }
}

void create_nodes(char* map, int map_size_x, vector<Node>& nodes, vector<City>& cities) {

    int i = 0;
    while (map[i]) {
        if (map[i] == '#' || map[i] == '*') {
            struct Node node;
            node.pos_x = i / map_size_x;
            node.pos_y = i - node.pos_y * map_size_x;
            nodes.push_back(std::move(node));
        }
        i++;
    }

    // Search for neighbours and add them to the neighbours list
    for (auto& n1 : nodes) {
        struct Edge edge;
        for (auto& n2 : nodes) {
            if (n1.pos_x == n2.pos_x && n1.pos_y == n2.pos_y - 1 ||
                n1.pos_x == n2.pos_x - 1 && n1.pos_y == n2.pos_y ||
                n1.pos_x == n2.pos_x && n1.pos_y == n2.pos_y + 1 ||
                n1.pos_x == n2.pos_x + 1 && n1.pos_y == n2.pos_y) 
            {
                edge.node = &n2; 
                edge.cost = 1;
                n1.neighbours.push_back(edge);
            }
        }
    }

    // Interlink cities to their nodes
    for (auto& c : cities) {
        for (auto& n : nodes) {
            if (n.pos_x == c.pos_x && n.pos_y == c.pos_y) {
                c.node = &n;
                break;
            }
        }
    }

    // Sort array of cities
    quick_sort(cities.data, 0, cities.size);

    // Parse airports
    int aiports_num;
    scanf("%d\n", &aiports_num);
    for (int i = 0; i < aiports_num; i++) {

        char from_city[100];
        char to_city[100];
        int cost;

        char line[1024];
        fgets(line, 1024, stdin);
        sscanf(line, "%s %s %d", from_city, to_city, &cost);

        int from_city_index = binary_search(cities.data, 0, cities.size - 1, from_city);
        int to_city_index = binary_search(cities.data, 0, cities.size - 1, to_city);

        cities.data[from_city_index].node = cities.data[to_city_index].node;

    }
}

void parse_input(vector<Node>& nodes, vector<City>& cities) {
    int map_size_x;
    int map_size_y;

    scanf("%d %d\n", &map_size_x, &map_size_y);

    char* m = parse_cities(cities, map_size_x, map_size_y);
    create_nodes(m, map_size_x, nodes, cities);
}


int main() {
  
    vector<Node> nodes;
    vector<City> cities;

    parse_input(nodes, cities);
    
}