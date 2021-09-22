function te=loadenvironment(te,filename)

try
    % create the tensegrity constraint file object
    te_file=envfile(filename,'r');
    % read the topology file
    [constraint_filename,te_file]=readfieldstring(te_file,'Constraint File: ');
    % load the topology
    te=loadconstraints(te,constraint_filename);
    % read the environment planes
    [te.planes,te.num_planes,te_file]=readplanes(te_file);
    % read the environment cilinders
    [te.cilinders,te.num_cilinders,te_file]=readcilinders(te_file);
    % read the environment for each node
    for i=1:1:te.tenconst.tensegrity.num_nodes
        [node_name,te_file]=readline(te_file);
        index=getnodeindex(te.tenconst.tensegrity,node_name);
        [te.tenconst.tensegrity.nodes(index),te_file]=readnodeenv(te_file,te.tenconst.tensegrity.nodes(index));        
    end
    % read the environment for each node    
    for i=1:1:te.tenconst.tensegrity.num_edges
        [edge_name,te_file]=readline(te_file);
        index=getedgeindex(te.tenconst.tensegrity,edge_name);
        [te.tenconst.tensegrity.edges(index),te_file]=readedegeenv(te_file,te.tenconst.tensegrity.edges(index));
    end
    [te,num,vars]=getvariables(te);
    close(te_file);
catch
    rethrow(lasterror);
end