function display(n)

for i=1:1:size(n,2)
    disp(['--- node ',n(i).name,' ---']);
    disp(['number of incident edges:    ',num2str(n(i).num_edges)]);
    edges=['incident edges:              '];
    for j=1:1:n(i).num_edges
        edges=[edges,n(i).inc_edges(j).name];
        if i<n(i).num_edges
            edges=[edges,','];
        end
    end
    disp(edges);
end
