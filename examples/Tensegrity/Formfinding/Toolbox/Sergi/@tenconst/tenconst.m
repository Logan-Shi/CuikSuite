function tc=tenconst(varargin)
% constructor for the tenconst class
% this function is a constructor for the tenconst class. This class
% encapsulates all the constraints associated to a tensegrity structure as
% a whole, which consist of:
%   * the position and orientation of the center of mass
%   * the number of sets of coplanar nodes.
%   * a list of the constraints for each node
%   * a list of the constraints for each edge
%   * a list of internal variables and user variables
%   * the reference to a cost function
% 
% the structure for the center of mass constraints is as follows:
%   * num_nodes: number of nodes to compute the center of mass
%   * nodes: list of node names to compute the center of mass
%   * position: a vector with the euclidean position of the center of mass
%   * orientation: a vector with the orientation of the centerof mass
%
% the structure for the coplanar node sets is as follows
%   * num_nodes: number of nodes included in the set
%   * nodes: list of the names of the nodes included in the set
%   * name: name of the set
%   * normal: vector normal to the plane
%   * dist: diatnce of the plane from the origin
%
% The list of internal veriables consists of an ordered list of internal
% variables of the problem and it is updated each time the number of
% variables changes. The user can also define variables for additional
% constraints of optimization parameters.
%
% The reference to a cost function is used to generate the cost function in
% an optimization problem from the constraint information available inside
% a tenconst object.
%
% tc=tenconst() returns a new object initialized by default.
%
% tc=tenconst(tenconst) if tenconst is an other tenconst object, this 
% function returns a copy of that object
%
% See also tensegrity,tenconst

switch nargin
    case 0
        tc.const_file='none';
        tc.num_var=0;
        tc.variables=tenvar();
        tc.num_user_var=0;
        tc.user_variables=tenvar();
        % center of mass constraints
        tc.cm.num_nodes=0;
        tc.cm.nodes=[];
        tc.cm.position=[tenvar(),tenvar(),tenvar()];
        tc.cm.orientation=[tenvar(),tenvar(),tenvar()];
        % coplanar nodes sets
        tc.num_cop_sets=0;
        tc.cop_sets.num_nodes=0;
        tc.cop_sets.name=[];
        tc.cop_sets.nodes=[];
        tc.cop_sets.normal=[tenvar(),tenvar(),tenvar()];
        tc.cop_sets.dist=tenvar();
        % symmetry constraints
        tc.sym.num_sets=0;
        tc.sym.sets.num_edges=0;
        tc.sym.sets.names=[];
        % cost function
        tc.cost_func_h=[];
        tc=class(tc,'tenconst',tensegrity);
    case 1
        if isa(varargin{1},'tenconst')
            tc=varargin{1};
        else
            error('tenconst - Invalid parameter value');
        end
end