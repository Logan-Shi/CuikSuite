function to=tenopt(varargin)
% constructor for the tenopt class
% this function is a constructor for the tenopt class. This class
% encapsulates all the information associated to an optimization process
% for a tensegrity structure, which consists of the tensegrity constraint
% object, the optimization parameters for the penalty based newton method
% (penalty, beta, sigma, s and tolerance), the function to minimize as well
% as its gradient and the name of the c files to compute the value of the
% functions, its gradient and the constraint equations.
% 
% The first step after creating an object of this class is initialize its
% attributes by loading an optimization file (*.opt) whose format is
% described in the optfile class documentation.
%
% The optimization method used in this class is based on a penalty method, 
% which consists in generating a new function made from the cost function
% and penalty terms, thus transforming the constrained optimization problem
% into an unconstrained one.
%
% The penalty terms are build from the constraint equations, squaring the
% equality constraints (h(i)*h(i)) and applying exp(g(i))-1 to the
% inequality constraints. The parameters used in this algorithm are:
%
%   * beta, s and sigma are used to compute the next step in the iteration,
%   and have a constant value.
%   * penalty is an increasing value which weight the constraints in the
%   function to be optimized.
%   * tolerance is the precision required for the solution.
%
% In order to speed up the optimization process, this class generates three
% c files with the source code to evaluate the optimization function, its
% gradient and the constraint equations.
%
% tc=tenopt() returns a new object initialized by default.
%
% tc=tenopt(tenopt) if tenopt is an other tenopt object, this 
% function returns a copy of that object
%
% See also tenconst,constfile,tensegrity,tenfile,optfile

switch nargin
    case 0
        to.const=[];
        % paràmetres de l'algorisme
        to.penalty=[0 0];
        to.penalty_update_h=[];
        to.beta=0;
        to.s=0;
        to.sigma=0;
        to.tolerance=0;
        % equacions de les restriccions
        to.num_eq=0;
        to.eq_const=sym('0');
        to.num_ineq=0;
        to.ineq_const=sym('0');
        % funció a optimitzar
        to.function=[];
        to.gradient=[];
        to.solution=[];
        % fitxers de c
        to.const_file=[];
        to.grad_file=[];
        to.func_file=[];
        to=class(to,'tenopt');
    case 1
        if isa(varargin{1},'tenopt')
            to=varargin{1};
        else
            error('tenopt - Invalid optimization object');
        end
end