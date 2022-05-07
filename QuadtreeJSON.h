#ifndef QUADTREEJSON_H
#define QUADTREEJSON_H

#include "Quadtree.h"
#include <nlohmann/json.hpp>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>

/*struct jsonQuadtree{
    
    std::vector<std::pair<const char*, int>, std::pair<const char*, int>> edges; 
    std::vector<int> nodes;
    
    jsonQuadtree(Quadtree* root){
        addEverything(root);
    }
    
    void addEverything(Quadtree* q){
        nodes.push_back(q->getId());
        if(q->getfather()){
            edges.push_back(std::make_pair(std::make_pair("source", q->getfather()->getId()),std::make_pair("target", q->getId())));
        }
        if(q->getnoreste()){
            addEverything(q->getnoreste());
            addEverything(q->getnoroeste());
            addEverything(q->getsureste());
            addEverything(q->getsuroeste());
        }
    }

    void createJson(){
        nlohmann::json j;
        j = nlohmann::json{{"directed", false}, {"multigraph", false}, {"graph", nlohmann::json::object()}, {"nodes", nodes}, {"links", edges}};
        std::cout<<j<<std::endl;
    }

};*/
using json = nlohmann::ordered_json;
static int id = 0;

void serialize (Quadtree* q, json &nodes, json& edges) {
    if (!q) return;
    if (q->getnoreste()) {
        for(int i = id; i <= id+3; i++) {
            nodes += {{"id", i}};
            edges += {{"source", id}, {"target", i}};
        }
        id += 4;
    }
    serialize(q->getnoreste(), nodes, edges);
    serialize(q->getnoroeste(), nodes, edges);
    serialize(q->getsureste(), nodes, edges);
    serialize(q->getsuroeste(), nodes, edges);
}

void makeJSON (Quadtree* q) {
    json nodes, edges, j;
    nodes = json::array({});
    edges = json::array({});
    serialize(q, nodes, edges);
    j = json{{"directed", false}, {"multigraph", false}, {"graph", json({})}, {"nodes", nodes}, {"links", edges}};
    std::ofstream file("grafo.json");
    file << j;
    id = 0;
}

#endif

