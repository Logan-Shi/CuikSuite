function [t,file]=loadtensegrity(t,file)
% loads the tensegrity topology from a file
% this functions loads all the information concerning the topology of a
% tensegrity structure from a file specified by filename. 
% 
% [t,file]=loadtensegrity(t,file) returns a modified version of a
% tensegrity object updated with the topological information read from the
% file and also the modified version of the tenfile object after reading
% all the information.
%
% Both the tensegrity (t) and the tenfile object (file) must be initialized
% before calling this function.
%
% See also tenfile,tensegrity

%file tag txt
DimTxt='Dim:';
ClassTxt='Class:';
NumNodesTxt='Num. Nodes:';
NumStrutsTxt='Num. Struts:';
NumCablesTxt='Num. Cables:';
if ~isa(file,'tenfile')
    error('tensegrity - Invalid tensegrity file');
end
if ~isa(t,'tensegrity')
    error('tensegrity - Invalid tensegrity structure');
end
try
    % read the dimension of the work space
    [t.dimension,file]=readfieldint(file,DimTxt);
    % read the class of the tensegrity structure
    [t.class,file]=readfieldint(file,ClassTxt);
    % read the number of nodes
    [num_nodes,file]=readfieldint(file,NumNodesTxt);
    % read the number of struts
    [num_struts,file]=readfieldint(file,NumStrutsTxt);
    % read the number of cables
    [num_cables,file]=readfieldint(file,NumCablesTxt);
    % total number of edges
    num_edges=num_struts+num_cables;
    % read the information of each node
    for num=1:1:num_nodes
        n=node();
        [n,file]=readnodeinfo(file,n);
        t=addnode(t,n);
    end
    % read the information of each edge
    for num=1:1:num_edges
        e=edge();
        [e,file]=readedgeinfo(file,e);
        t=addedge(t,e);
    end
catch
    rethrow(lasterror);
end
t.filename=file.filename;
