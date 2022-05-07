import matplotlib.pyplot as plt
import networkx as nx
import pydot
from networkx.drawing.nx_pydot import graphviz_layout

from networkx.readwrite import json_graph
import json

def save_json(filename, graph):
    g = graph
    g_json = json_graph.node_link_data(g)
    json.dump(g_json, open(filename, 'w'), indent=2)

def read_json(filename):
    with open(filename) as f:
        js_graph = json.load(f)
    return json_graph.node_link_graph(js_graph)

#try:
T = read_json("grafo.json")
pos = graphviz_layout(T, prog="dot")
nx.draw(T, pos)
plt.show()
    #plt.pause(0.001)
    #plt.clf()
        
#except KeyboardInterrupt:
#    pass
