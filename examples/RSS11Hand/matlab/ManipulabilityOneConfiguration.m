function [index1 index2 index3 u]=ManipulabilityOneConfiguration(J,G,H1,H2,H3)
% MANIPULABILITY SCRIPT
 % write in workspace index1, index2 and index3, and ellipsoid axes in u, as 
 % well as all variables related to configuration i, e.g. object origin o

  % CONTACT MODELS
  %free model
  %Hn = zeros(6,6);
  %frictionless model
  %Hpwof = [ [1 0 0 ; zeros(2,3)] zeros(3,3); zeros(3,6) ];
  %hard friction model
  Hhf = [eye(3) zeros(3,3); zeros(3,6)];
  %soft friction model
  %Hsf = [eye(3) zeros(3,3); zeros(3,3) [1 0 0 ; zeros(2,3)] ];
  %rigid model
  %Hr = eye(6);
  
  % model in contact 1
  H1 = Hhf;
  
  % model in contact 2
  H2 = Hhf;
  
  % model in contact 3
  H3 = Hhf;

  % full selection matrix
  H = blkdiag(H1,H2,H3); 
  Gt=G';
    
    % MANIPULABILITY MATRIX ---------------------
    M = H*[-Gt J];

    
    % available motions
    C = null(M);

    % mobility
    n = rank(C);

    % dimensions
    [p,no] = size(Gt);
    [q,ni] = size(J);

    % internal motion matrix: when object and passive joints are locked
    A23 = null(H*J);
    Nr = rank(A23); % degree of redundancy
    Or = zeros(no,Nr);
    Ar = [Or ; A23];

    % uncontrollable motion matrix: when active joints are locked
    A11 = null(H*Gt); 
    Ni = rank(A11); % degree of indetermincay
    Oi = zeros(ni,Ni);
    Ai = [A11 ; Oi];
    
    % connectivity
    Nc = n-Nr-Ni;
    
    % gram-smith orthogonalization using the two previous matrices as starting basis
    A = [Ar Ai];
    for t=1:n,
        [ms,ns] = size(A);
        v = C(:,t);
        for j=1:ns,
            v = v-dot(v,A(:,j))*A(:,j);
        end
        if norm(v)>1e-6
            v = v/norm(v);
            A = [A v];
        end
    end

    Ac = A(:,Ni+Nr+1:n); % the new coordinated motions matrix
    A12 = Ac(1:no,:); % output space coordinated motions
    A22 = Ac(no+1:no+ni,:); % input space coordinated motions
    
    % the new available motions matrix, the C before
    A = [Ai Ac Ar];
    
    % MANIPULABILITY EVALUATION -----------

    % weight matrices for the output and input spaces
    Wu = eye(no);
    Wq = eye(ni);

    % projector matrices in the case of internal or uncontrollable motions
    P1w = projmatrix(A11,Wu);
    P2w = projmatrix(A23,Wq);

    B1 = A12'*P1w'*Wu*P1w*A12;
    B2 = A22'*P2w'*Wq*P2w*A22;

    % eigenvalues and eigenvectors
    [U,V,X,Ce,Se] = gsvd(B1,B2);
    
    % egigenvalues in the case of using gsvd 
    % ORDER: lower to bigger when top to bottom
    SIGMA = sqrt(diag(Ce'*Ce)./diag(Se'*Se)); 
      
    
    % Index 1: inverse of the condition number of the ratio matrix
    index1 = inv(max(SIGMA)/min(SIGMA));

    % Index 2: determinant of the ratio matrix
    index2 = prod(SIGMA);

    % Index 3: the minimum of the sngular values
    index3 = min(SIGMA);
    
    % ellipsoid propagation to output space
    u = (A12*P1w)*(B2\B1)*(A12*P1w)';
    
