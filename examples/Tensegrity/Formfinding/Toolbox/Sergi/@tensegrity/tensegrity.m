function t=tensegrity(varargin)
% constructor for the tensegrity class
% this function is the constructor for the tensegrity class. This class
% encapsulates the topology of a tensegrity structure. Objects of this
% class contain the dimension of the work space, the class of the structure
% (maximum number of rigid elements attached to a single node) and the
% lists of nodes and edges.
%
% t=tensegrity(varargin) returns a new object initialized by default.
%
% t=tensegrity(tensegrity) if tensegrity is an other tensegrity object,
% this function returns a copy of that object
%
% t=tensegrity(filename) if filename is the name of a topology
% file (*.ten), this constructor builds a new tensegrity object with the
% information of the topology file.
%
% See also tenfile,loadtensegrity

switch nargin
    case 0
        % default constructor
        t.filename='none';
        t.name='none';
        t.dimension=[];
        t.class=[];
        t.num_nodes=0;
        t.num_edges=0;
        t.num_struts=0;
        t.num_cables=0;
        t.nodes=[];
        t.edges=[];
        t=class(t,'tensegrity');
    case 1
        % copy constructor
        if isa(varargin{1},'tensegrity')
            t=varargin{1};
        else
            % create an object taking the information from a file
            if ischar(varargin{1})
                t=tensegrity();
                try
                    t=loadtensegrity(t,varargin{1});
                catch
                    rethrow(lasterror);
                end
            else
                error('tensegrity - Invalid parameter value');
            end
        end
    otherwise
        error('tensegrity - Invalid number of parameters');
end
