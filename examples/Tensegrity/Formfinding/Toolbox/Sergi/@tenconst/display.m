function display(tc)

disp(['Number of variables: ',tc.num_var]);
disp(['Constraint file: ',tc.const_file]);
disp('--- center of mass constraints ---');
nodes='';
for i=1:1:tc.cm.num_nodes
    nodes=[nodes,tc.cm.nodes(i).name];
    if i<tc.cm.num_nodes
        nodes=[nodes,','];
    end
end
disp(['Center of mass nodes (',num2str(tc.cm.num_nodes),'): ',nodes]);
disp('--- coplanar nodes constraints');
for i=1:1:tc.num_cop_sets
    disp(['set ',num2str(i)]);
    nodes='';
    for i=1:1:tc.cop_sets(i).num_nodes
        nodes=[nodes,tc.cop_sets(i).nodes(i).name];
        if i<tc.cm.num_nodes
            nodes=[nodes,','];
        end
    end
    disp(['Coplanar nodes (',num2str(tc.cm.num_nodes),': ',nodes]);
end
display(tc.tensegrity);