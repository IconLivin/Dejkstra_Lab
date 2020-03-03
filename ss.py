import matplotlib.pyplot as plt
import networkx as nx
import random

var = int(open("../../graph.txt",'r').read())


G = nx.connected_watts_strogatz_graph(var,4,1)

for(u,v,w) in G.edges(data=True):
    w['weight'] = random.randint(0,100)

nx.write_weighted_edgelist(G,"graph.txt")


pos = nx.spring_layout(G)  # positions for all nodes
# nodes
nx.draw_networkx_nodes(G, pos, node_size=700)

# edges
labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edges(G, pos, width = 6)
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
# labels
nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif')

plt.axis('off')
plt.savefig('graph.png')


