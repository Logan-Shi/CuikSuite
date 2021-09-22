function tc=loadconstraints(tc,filename)
% loads the constraints from a file to an object
% this functions reads all the constraints associated to a tensegrity
% topology and initializes a tenconst object. See the documentation for the
% constfile class for information about the file format.
%
% tc=loadconstraints(tc,filename) returns a modified version of the
% tensegrity constraint object with the constraints loaded from the file.
%
% The tenconst object must be initialized before calling this function and
% the filename must be a string terminated by .cst.
% 
% See also tenconst,constfile
try
    % create the tensegrity constraint file object
    tc_file=constfile(filename,'r');
    % read the topology file
    [topology_filename,tc_file]=readfieldstring(tc_file,'Topology File: ');
    % create the tensegrity topology file object
    t_file=tenfile(topology_filename,'r');
    % load the topology
    [tc,t_file]=loadtensegrity(tc,t_file);
    % read the constraints of the center of mass
    [tc.cm,tc_file]=readcmconstraints(tc_file);
    % read the constraints of the coplnar sets
    [tc.cop_sets,tc.num_cop_sets,tc_file]=readcoplanarsets(tc_file);
    % read the symmetry constraints
    [tc.sym,tc_file]=readsymmetryconstraints(tc_file);
    % read the constraints of each node
    for i=1:1:tc.tensegrity.num_nodes
        [node_name,tc_file]=readline(tc_file);
        index=getnodeindex(tc.tensegrity,node_name);
        [tc_file,tc.tensegrity.nodes(index)]=readnodeconst(tc_file,tc.tensegrity.nodes(index));
    end
    % read the constraints of each node    
    for i=1:1:tc.tensegrity.num_edges
        [edge_name,tc_file]=readline(tc_file);
        index=getedgeindex(tc.tensegrity,edge_name);
        [tc_file,tc.tensegrity.edges(index)]=readedgeconst(tc_file,tc.tensegrity.edges(index));
    end
    % read the cost function
    [cost_func,tc_file]=readcostfunc(tc_file);
    tc.cost_func_h=str2func(cost_func);
    % update the internal variable list
    [tc,num,vars]=getvariables(tc);
    tc.const_file=filename;
    close(t_file);
    close(tc_file);
catch
    rethrow(lasterror);
end