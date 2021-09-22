function t_file=tenfile(varargin)
% the constructor for the tenfile class
% this function is the constructor for the tenfile class. It uses the
% default constructor of the base class file to initialize the base class 
% attributes. 
%
% t_file=tenfile() returns a new object initialized by default.
%
% t_file=tenfile(tenfile) if tenfile is an other tenfile object, this 
% function returns a copy of that object
%
% t_file=tenfile(filename) if filename is the name of an existing file, this 
% function returns a new object associated to the file which is openend in
% read and write mode.
%
% t_file=tenfile(filename.mode) if filename is the name of an existing file, this
% function returns a new object associated to the file which is openend as 
% mode.
% 
% the file format for the tensegrity topology files (*.ten) is
%
% # general information
% Dim:<dimension of the work space, either 2 or 3>
% Class:<the maximum number of rigid edges at each node>
% Num. Nodes:<number of nodes>
% Num. Struts:<number of struts>
% Num. Cables:<number of cables>
% # node information
% #for each node
% <name of the node>
% Num. Edges:<number of incident edges>
% Edges:<list of the incident edges to the node>
% # edge information
% # for each edge
% <name of the edge>
% Type:<either cable or strut>
% Origin:<name of the origin node for the edge>
% End:<name of the end node for the edge>
%
% where <> indicates a required parameter and [] indicates a conditional
% parameter. # indicated commentaries and are ignored.

switch nargin
    case 0
        % default constructor
        t_file=class(struct([]),'tenfile',file);
    case 1
        % copy constructor
        if isa(varargin{1},'tenfile')
            t_file=varargin{1};
        else
            % creates an object associated to a file
            if ischar(varargin{1})
                t_file=class(struct([]),'tenfile',file(varargin{1}));
            else
                error('tenfile - Invalid parameter value');
            end
        end
    case 2        
        % creates an object associated to a file        
        if ischar(varargin{1}) && ischar(varargin{2})
            t_file=class(struct([]),'tenfile',file(varargin{1},varargin{2}));
        else
            error('tenfile - Invalid parameter value');
        end
    otherwise
        error('tenfile - Invalid number of arguments');
end