function to_file=optfile(varargin)
% the constructor for the optfile class
% this function is the constructor for the optfile class. It uses the
% default constructor of the base class file to initialize the base class 
% attributes.
%
% to_file=optfile() returns a new object initialized by default.
%
% to_file=optfile(optfile) if optfile is an other optfile object, this 
% function returns a copy of that object
%
% to_file=optfile(filename) if filename is the name of an existing file, this 
% function returns a new object associated to the file which is openend in
% read and write mode.
%
% to_file=optfile(filename,mode) if filename is the name of an existing file,
% this function returns a new object associated to the file which is openend 
% as mode.
% 
% the file format for the optimization files (*.opt) is
%
% Min. penalty:<Minimum penalty value>
% Max. penalty:<Maximum penalty value>
% Beta:<beta value>
% S:<s value>
% Sigma:<sigma value>
% Tolerance:<desired tolerance>
% Penalty update function:<penalty update function m file> 
% Constraints:<constraint file (*.cst) or none
% Constarint file:<the name of the c compiled code for the constraints>
% Gradient file:<the name of the c compiled code for the gradient>
% Function file:<the name of the c compiled code for the optimization function>
% 
% where <> indicates a required parameter.

switch nargin
    case 0
        % default constructor
        to_file=class(struct([]),'optfile',file);
        inferiorto('file');
    case 1
        if isa(varargin{1},'optfile')
            % copy constructor
            to_file=varargin{1};
        else
            % creates an object associated to a file
            if ischar(varargin{1})
                to_file=class(struct([]),'optfile',file(varargin{1}));
            else
                error('optfile - Invalid parameter value');
            end
        end
    case 2
        % creates an object associated to a file        
        if ischar(varargin{1}) && ischar(varargin{2})
            to_file=class(struct([]),'optfile',file(varargin{1},varargin{2}));
        else
            error('optfile - Invalid parameter value');
        end
    otherwise
        error('optfile - Invalid number of arguments');
end