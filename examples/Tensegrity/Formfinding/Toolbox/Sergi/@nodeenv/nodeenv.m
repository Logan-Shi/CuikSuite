function nenv=nodeenv(varargin)

switch nargin
    case 0
        nenv.friction=0;
        nenv=class(nenv,'nodeenv',nodeconst);
    case 1
        if isa(varargin{1},'nodeenv')
            nenv=varargin{1};
        else
            error('nodeenv - Invalid node environment object');
        end
end