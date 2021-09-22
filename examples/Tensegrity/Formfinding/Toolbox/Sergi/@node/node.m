function node_obj=node(varargin)
% constructor for the node class
% this function is the constructor for the node class. This class
% encapsulates the topological information of a node, which consists of:
%   * the number of incident edges
%   * the list incident edges
%
% node_obj=node() returns a new object initialized by default.
%
% node_obj=node(node) if node is an other node object, this function 
% returns a copy of that object
%
% node_obj=node(name,num_edges,edges_list) builds a new node object with the
% attributes specified as the parameters to the constructor.
%
% See also tensegrity,tenfile

switch nargin
    case 0
        node_obj.name=[];
        node_obj.num_edges=0;
        node_obj.inc_edges.name=[];
        node_obj=class(node_obj,'node');
    case 1
        if isa(varargin{1},'node')
            node_obj=varargin{1};
        else
            error('node - Invalid argument type');
        end
    case 3
        if ischar(varargin{1})
            node_obj.name=varargin{1};
            if isnumeric(varargin{2})
                node_obj.num_edges=varargin{2};
                node_obj.inc_edges=varargin{3};
                node_obj=class(node_obj,'node');
            else
                error('node - Invalid argument type');
            end
        else
            error('node - Invalid argument type');
        end
    otherwise
        error('node - Invalid number of arguments');
end
