function ef=envfile(varargin)

switch nargin
    case 0
        % default constructor
        ef=class(struct([]),'envfile',file);
        inferiorto('file');
    case 1
        if isa(varargin{1},'envfile')
            % copy constructor
            ef=varargin{1};
        else
            % constructor associated to a file
            if ischar(varargin{1})
                ef=class(struct([]),'envfile',file(varargin{1}));
            else
                error('envfile - Invalid parameter value');
            end
        end
    case 2
        % constructor associated to a file
        if ischar(varargin{1}) && ischar(varargin{2})
            ef=class(struct([]),'envfile',file(varargin{1},varargin{2}));
        else
            error('envfile - Invalid parameter value');
        end
    otherwise
        error('envfile - Invalid number of arguments');
end