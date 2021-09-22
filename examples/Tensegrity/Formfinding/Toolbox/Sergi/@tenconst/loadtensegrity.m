function [tc,file]=loadtensegrity(tc,file)
% overloads the loadtensegrity function of the base class
% this function overloads the loadtensegrity function of the base class to
% build lists of nodeconst and edgeconst objects instead of the node and
% edge objects of the base class.
%
% [t,file]=loadtensegrity(t,file) returns a modified version of a
% tensegrity constraint object updated with the topological information 
% read from the file and also the modified version of the tenfile object
% after reading all the information.
%
% Both the tensegrity (t) and the tenfile object (file) must be initialized
% before calling this function.
%
% See also tenfile,tensegrity

%file tags txt
DimTxt='Dim:';
ClassTxt='Class:';
NumNodesTxt='Num. Nodes:';
NumStrutsTxt='Num. Struts:';
NumCablesTxt='Num. Cables:';
if ~isa(file,'tenfile')
    error('tenconst - Invalid tensegrity file');
end
if ~isa(tensegrity,'tensegrity')
    error('tenconst - Invalid tensegrity structure');
end
try
    % read the dimension of the work space
    [tc.tensegrity.dimension,file]=readfieldint(file,DimTxt);
    % read the class of the tensegrity structure
    [tc.tensegrity.class,file]=readfieldint(file,ClassTxt);
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
        n=nodeconst();
        [n,file]=readnodeinfo(file,n);
        tc.tensegrity=addnode(tc.tensegrity,n);
    end
    % read the information of each edge
    for num=1:1:num_edges
        e=edgeconst();
        [e,file]=readedgeinfo(file,e);
        tc.tensegrity=addedge(tc.tensegrity,e);
    end
    tc.tensegrity=setfilename(tc.tensegrity,file.filename);    
catch
    rethrow(lasterror);
end
