function edge_obj=edge(varargin)
% constructor for the edge class
% this function is the constructor for the edge class. This class
% encapsulates the topological information of an edge, which consists of:
%   * the name of the edge
%   * the type of the edge (either cable or strut)
%   * the name of the origin node
%   * the name of the end node.
%
% An edge obect can be initialized at construction time or also by using
% the member functions to change its name, type, origin node and end node.
% To add an edge to a tensegrity structure use the function addedge from
% the rensegrity class.
%
% edge_obj=edge() returns a new object initialized by default.
%
% edge_obj=edge(edge) if edge is an other edge object, this function 
% returns a copy of that object
%
% edge_obj=edge(name,type,origin,end) builds a new node object with the
% attributes specified as the parameters to the constructor. Both the
% origin and end node must be existing node names.
%
% See also tensegrity,tenfile

switch nargin
    case 0
        edge_obj.name=[];
        edge_obj.type=[];
        edge_obj.origin='none';
        edge_obj.end='none';
        edge_obj=class(edge_obj,'edge');
    case 1
        if isa(varargin{1},'edge')
            edge_obj=varargin{1};
        else
            error('edge - Invalid argument type');
        end
    case 4
        if ischar(varargin{1})
            try
                edge_obj=edge();
                edge_obj.name=varargin{1};
                edge_obj=settype(edge_obj,varargin{2});
                if (ischar(varargin{3}) && ischar(varargin{4}))
                    edge_obj.origin=varargin{3};
                    edge_obj.end=varargin{4};
                else
                    error('edge - Invalid argument type');
                end
            catch
                rethrow(lasterror);
            end
        else
            error('edge - Invalid argument type');
        end
    otherwise
        error('edge - Invalid number of arguments');
end
