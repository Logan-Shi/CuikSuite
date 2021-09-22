function ec=edgeconst(varargin)
% constructor for the edgeconst class
% this function is the constructor for the edgeconst class. This class
% encapsulates the constraints for each edge, which consist of:
%   * the stiffness constant,
%   * the rest length
%   * the real length.
%
% ec=edgeconst() returns a new object initialized by default.
%
% ec=edgeconst(edgeconst) if edgeconst is an other edgeconst object, this function 
% returns a copy of that object
%
% ec=edgeconst(edge) builds a new edgeconst object on top of an already
% initialized edge object
%
% See also tenconst,constfile

switch nargin
    case 0
        ec.stiffness=tenvar();
        ec.rest_length=tenvar();
        ec.length=tenvar();
        ec=class(ec,'edgeconst',edge);
    case 1
        if isa(varargin{1},'edgeconst')
            ec=varargin{1};
        else
            if isa(varargin{1},'edge')
                ec.stiffness=tenvar();
                ec.rest_length=tenvar();
                ec.length=tenvar();
                ec=class(ec,'edgeconst',varargin{1});
            else
                error('edgeconst - Invalid parameter value');
            end
        end
    otherwise
        error('edgeconst - Invalid number of parameters');
end