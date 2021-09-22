function eenv=edgeenv(varargin)

switch nargin
    case 0
        eenv.radius=0;
        eenv=class(eenv,'edgeenv',edgeconst);
    case 1
        if isa(varargin{1},'edgeenv')
            eenv=varargin{1};
        else
            error('edgeenv - Invalid edge environment object');
        end
end