function te=tenenv(varargin)

switch nargin
    case 0
        te.num_env_var=0;
        te.env_var=tenvar();
        % planes in the environment
        te.num_planes=0;
        te.planes.name=[];
        te.planes.normal=[tenvar(),tenvar(),tenvar()];
        te.planes.offset=[tenvar(),tenvar(),tenvar()];
        % cilinders in the environment
        te.num_cilinders=0;
        te.cilinders.name=[];
        te.cilinders.radius=tenvar();
        te.cilinders.length=tenvar();
        te.cilinders.origin=[tenvar(),tenvar(),tenvar()];
        te.cilinders.orientation=[tenvar(),tenvar(),tenvar()];
        te=class(te,'tenenv',tenconst);
    case 1
        if isa(varargin{1},'tenenv')
            out=varargin{1};
        else
            error('tenenv - Invalid tensegrity environment object');
        end
    otherwise
        error('tenenv - Invalid number of arguments');
end