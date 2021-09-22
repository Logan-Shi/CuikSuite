function savetensegrity(t,filename)
% saves the tensegrity topology into a file
% this functions saves all the information concerning the topology of a
% tensegrity structure into a file specified by filename. This function
% also creates a default constraints file associated with the topology to
% be used by the Constraints.m script.
% 
% savetensegrity(t,filename) opens the file or create it if it does not
% exists and writes all the topological information of the structure.
%
% The tensegrity object must be initialized before calling this function
% and the filename must be a string terminated by .ten
%
% See also tenfile,tensegrity

% file tag txt
DimTxt='Dim:';
ClassTxt='Class:';
NumNodesTxt='Num. Nodes:';
NumStrutsTxt='Num. Struts:';
NumCablesTxt='Num. Cables:';
if ~isa(t,'tensegrity')
    error('tensegrity - Invalid tensegrity structure');
end
% create a default constraints file
const_filename=strtok(filename,'.');
const_filename=[const_filename,'.cst'];
try
    tc_file=constfile(const_filename,'w');
    % write the topology filename
    tc_file=writetopologyfile(tc_file,filename);
    % open or create the topology file
    file=tenfile(filename,'w');
    % write the dimension of the work space
    file=writefieldint(file,DimTxt,t.dimension);
    % write the class of the tensegrity structure
    file=writefieldint(file,ClassTxt,t.class);
    % write the number of nodes
    file=writefieldint(file,NumNodesTxt,t.num_nodes);
    % write the number of struts
    file=writefieldint(file,NumStrutsTxt,t.num_struts);
    % write the number of cables
    file=writefieldint(file,NumCablesTxt,t.num_cables);
    % write the default center of mass constraints in the constraints file
    cm.num_nodes=0;
    cm.position=[];
    cm.orientation=[];
    tc_file=writecmconstraints(tc_file,cm);
    % write the default coplanar sets constraints in the constraints file
    cop_sets.num_nodes=0;
    cop_sets.name=[];
    cop_sets.nodes=[];
    cop_sets.normal=[tenvar(),tenvar(),tenvar()];
    cop_sets.dist=tenvar();
    tc_file=writecoplanarsets(tc_file,cop_sets,0);
    nc=nodeconst();
    % write the topological information of each node
    for i=1:1:t.num_nodes
        file=writenodeinfo(file,t.nodes(i));
        nc(i)=nodeconst(t.nodes(i));
        nc(i).position=[tenvar('passive',[t.nodes(i).name,'_x']),tenvar('passive',[t.nodes(i).name,'_y']),tenvar('passive',[t.nodes(i).name,'_z'])];
        tc_file=writenodeconst(tc_file,nc(i));
    end
    ec=edgeconst();
    % write the topological information of each edge
    for i=1:1:t.num_edges
        file=writeedgeinfo(file,t.edges(i));
        ec(i)=edgeconst(t.edges(i));
        ec(i).stiffness=tenvar('passive',[t.edges(i).name,'_k']);
        ec(i).rest_length=tenvar('passive',[t.edges(i).name,'_d0'],[0,0]);
        ec(i).length=tenvar('passive',[t.edges(i).name,'_d']);
        tc_file=writeedgeconst(tc_file,ec(i));
    end
    % write the default cost function generation file
    tc_file=writecostfunc(tc_file,'MinimumEnergy');
    file=close(file);
    tc_file=close(tc_file);
catch
    rethrow(lasterror);
end