function tcol=tencol(varargin)

switch nargin
    case 0
        % equacions de les restriccions
        tcol.num_env_eq=0;
        tcol.env_eq_const=sym('0');
        tcol.num_env_ineq=0;
        tcol.env_ineq_const=sym('0');
        tcol.env=tenenv();
        tcol=class(tcol,'tencol',tenopt);
    case 1
        if isa(varargin{1},'tencol')
            tcol=varargin{1};
        else
            error('tencol - Invalid tensegrity collision object');
        end
    otherwise
        error('tencol - Invalid number of parameters');
end