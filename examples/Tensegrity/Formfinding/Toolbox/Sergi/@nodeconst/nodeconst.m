function nc=nodeconst(varargin)
% constructor for the nodeconst class
% this function is the constructor for the nodeconst class. This class
% encapsulates the constraints for each node, which consist of:
%   * the position of the node
%   * the number of external applied forces
%   * the values of these forces.
%
% nc=nodeconst() returns a new object initialized by default.
%
% nc=nodeconst(nodeconst) if nodeconst is an other nodeconst object, this 
% function returns a copy of that object
%
% nc=nodeconst(node) builds a new nodeconst object on top of an already
% initialized node object
%
% See also tenconst,constfile

switch nargin
    case 0
        nc.position=[tenvar(),tenvar(),tenvar()];
        nc.num_forces=0;
        nc.forces=[tenvar(),tenvar(),tenvar()];
        nc=class(nc,'nodeconst',node);
    case 1
        if isa(varargin{1},'nodeconst')
            nc=varargin{1};
        else
            if isa(varargin{1},'node')
                nc.position=[tenvar(),tenvar(),tenvar()];
                nc.num_forces=0;
                nc.forces=[tenvar(),tenvar(),tenvar()];
                nc=class(nc,'nodeconst',varargin{1});
            else
                error('nodeconst - Invalid parameter value');
            end
        end
end