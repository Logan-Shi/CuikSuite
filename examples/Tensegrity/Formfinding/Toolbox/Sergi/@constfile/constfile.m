function constfile_obj=constfile(varargin)
% constructor for the tenconst class
% this function is the constructor for the constfile class. It uses the
% default constructor of the base class file to initialize the base class 
% attributes.
%
% constfile_obj=constfile() returns a new object initialized by default.
%
% constfile_obj=constfile(tc_file) if tc_file is an other constfile object,
% this function returns a copy of that object
%
% constfile_obj=constfile(filename) if filename is the name of a constraint
% file (*.cst), this function returns a new object associated to the file 
% which is openend in read and write mode.
%
% constfile_obj=constfile(filename,mode) if filename is the name of a 
% constraint file (*.cst), this function returns a new object associated to
% the file which is openend as mode.
%
% The format of the constraint file (*.cst) is
%
% Topology File: <topology file>
% # center of mass constraints
% Num. CM Nodes:<num. nodes>
% [CM Nodes:<node list separated by comma>]
% xcm:<either fixed parameter or none>[,value for fixed type only]
% ycm:<either fixed parameter or none>[,value for fixed type only]
% zcm:<either fixed parameter or none>[,value for fixed type only]
% rxcm:<either fixed parameter or none>[,value for fixed type only]
% rycm:<either fixed parameter or none>[,value for fixed type only]
% rzcm:<either fixed parameter or none>[,value for fixed type only]
% # coplanar nodes
% Num. Coplanar Sets:<num. of coplanar node sets>
% # for each set
% <name of the set>
% Num. Coplanar Nodes:<num. of node in the set>
% Coplanar Nodes:<node list separated by comma>
% nx:<either fixed, passive or parameter>[,value for fixed type only]
% ny:<either fixed, passive or parameter>[,value for fixed type only]
% nz:<either fixed, passive or parameter>[,value for fixed type only]
% dist:<either fixed, passive or parameter>[,value for fixed type only]
% # node constraints
% # for each node
% <node name: equal to that of the topology>
% x:<either fixed,passive,parameter or actuated>[,default value for fixed type only]
% y:<either fixed,passive,parameter or actuated>[,default value for fixed type only]
% z:<either fixed,passive,parameter or actuated>[,default value for fixed type only]
% Num. Ext. Forces:<num. of external forces applied to the node>
% [Fx:<either fixed or parameter>,[value for fixed type only]
% [Fy:<either fixed or parameter>,[value for fixed type only]
% [Fz:<either fixed or parameter>,[value for fixed type only]
% # edge constraints
% # for each edge
% <edge name: equal to that of the topology>
% k:<either fixed, passive or parameter>[,the default stiffness constant for fixed type only]
% d0:<either fixed, passive, parameter or actuated>[, the default rest length for fixed type only or (maximum,minimum) value for passive and actuated type only]
% Cost Func.:<cost function m file>
%
% where <> indicates a required field and [] indicates a conditional field.
% # indicate commentaries.

switch nargin
    case 0
        % default constructor
        constfile_obj=class(struct([]),'constfile',file);
        inferiorto('file');
    case 1
        if isa(varargin{1},'constfile')
            % copy constructor
            constfile_obj=varargin{1};
        else
            % constructor associated to a file
            if ischar(varargin{1})
                constfile_obj=class(struct([]),'constfile',file(varargin{1}));
            else
                error('constfile - Invalid parameter value');
            end
        end
    case 2
        % constructor associated to a file
        if ischar(varargin{1}) && ischar(varargin{2})
            constfile_obj=class(struct([]),'constfile',file(varargin{1},varargin{2}));
        else
            error('constfile - Invalid parameter value');
        end
    otherwise
        error('constfile - Invalid number of arguments');
end