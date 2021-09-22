function display(t)

disp(['filename:        ',t.filename]);
disp(['name:            ',t.name]);
disp(['dimension:       ',num2str(t.dimension)]);
disp(['class:           ',num2str(t.class)]);
disp(['number of nodes: ',num2str(t.num_nodes)]);
for i=1:1:t.num_nodes
    display(t.nodes(i));
end
disp(['number of edges: ',num2str(t.num_edges),'(cables: ',num2str(t.num_cables),',struts: ',num2str(t.num_struts),')']);
for i=1:1:t.num_edges
    display(t.edges(i));
end
