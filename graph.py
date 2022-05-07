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


T = nx.balanced_tree(2, 5)
pos = graphviz_layout(T, prog="dot")
save_json("grafo.json", T)
nx.draw(T, pos)
plt.show()
