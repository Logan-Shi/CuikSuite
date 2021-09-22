function nc=addexternalforce(varargin)
% adds an external force applied to a node
% this function adds an extrenal force applied to a node (nc),
% automatically updating the number of external forces.
%
% nc=addexternalforce(nodeconst) return a modifeid version of the
% nodeconst object with a new default force added.
%
% nc=addexternalforce(nodeconst,tenvar) return a modifeid version of the
% nodeconst object with an added force initialized with the tenvar 
% information.
% 
% The node constraint object must be initialized before calling this
% function.
%
% See also nodeconst

if nargin==1
    if isa(varargin{1},'nodeconst')
        varargin{1}.num_forces=varargin{1}.num_forces+1;
        varargin{1}.forces(varargin{1}.num_forces,:)=[tenvar('passive',[varargin{1}.node.name,'_force_Fx_',num2str(varargin{1}.num_forces)]),tenvar('passive',[varargin{1}.node.name,'_force_Fy_',num2str(varargin{1}.num_forces)]),tenvar('passive',[varargin{1}.node.name,'_force_Fz_',num2str(varargin{1}.num_forces)])];
        nc=varargin{1};
    else
        error('nodeconst - Invalid node constraint structure');
    end
else
    if nargin==2
        if isa(varargin{1},'nodeconst')
            if isa(varargin{2},'tenvar')
                varargin{1}.num_forces=varargin{1}.num_forces+1;
                varargin{1}.forces(varargin{1}.num_forces,:)=varargin{2};
                nc=varargin{1};
            else
                error('nodeconst - Invalid variable structure');
            end
        else
            error('nodeconst - Invalid node constraint structure');
        end
    else
        error('nodeconst - Invalid number of parameters');
    end
end