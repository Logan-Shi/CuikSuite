% MANIPULABILITY SCRIPT
 % write in workspace index1, index2 and index3, and ellipsoid axes in u, as 
 % well as all variables related to configuration i, e.g. object origin o
    
 
 %----------------------------------------
    % which axis influence a given contact 
    % needs to be done manually.-
    
    c=0;
    % contact 1
    c1 = transpose(contacts(i,1+vc*c:3+vc*c));
    n1 = transpose(contacts(i,4+vc*c:6+vc*c))/contacts(i,7+vc*c);
    R1 = [n1 ortonormalvector(n1,0.1) cross(n1,ortonormalvector(n1,0.1))]; 
    R1 = blkdiag(R1,R1);
    
    a=0;
    % axes affecting contact 1
    j21 = transpose(axes(i,1+va*a:3+va*a));
    r21 = transpose(axes(i,4+va*a:6+va*a));
    
    a=a+1;
    j22 = transpose(axes(i,1+va*a:3+va*a));
    r22 = transpose(axes(i,4+va*a:6+va*a));

    a=a+1;
    j23 = transpose(axes(i,1+va*a:3+va*a));
    r23 = transpose(axes(i,4+va*a:6+va*a));    

    a=a+1;
    j24 = transpose(axes(i,1+va*a:3+va*a));
    r24 = transpose(axes(i,4+va*a:6+va*a));

    c=c+1;
    % contact 2
    c2 = transpose(contacts(i,1+vc*c:3+vc*c));
    n2 = transpose(contacts(i,4+vc*c:6+vc*c))/contacts(i,7+vc*c);
    R2 = [n2 ortonormalvector(n2,0.1) cross(n2,ortonormalvector(n2,0.1))]; 
    R2 = blkdiag(R2,R2);
  
    a=0;
    % axes affecting contact 2
    j31 = transpose(axes(i,1+va*a:3+va*a));
    r31 = transpose(axes(i,4+va*a:6+va*a));
    
    a=a+1;
    j32 = transpose(axes(i,1+va*a:3+va*a));
    r32 = transpose(axes(i,4+va*a:6+va*a));

    a=a+1;
    j33 = transpose(axes(i,1+va*a:3+va*a));
    r33 = transpose(axes(i,4+va*a:6+va*a));    

    a=a+1;
    j34 = transpose(axes(i,1+va*a:3+va*a));
    r34 = transpose(axes(i,4+va*a:6+va*a));
    
    c=c+1;
    % contact 3
    c3 = transpose(contacts(i,1+vc*c:3+vc*c));
    n3 = transpose(contacts(i,4+vc*c:6+vc*c))/contacts(i,7+vc*c);
    R3 = [n3 ortonormalvector(n3,0.1) cross(n3,ortonormalvector(n3,0.1))]; 
    R3 = blkdiag(R3,R3);
    
    a=0;
    % axes affecting contact 3
    j40 = transpose(axes(i,1+va*a:3+va*a));
    r40 = transpose(axes(i,4+va*a:6+va*a));
    
    a=a+1;
    j41 = transpose(axes(i,1+va*a:3+va*a));
    r41 = transpose(axes(i,4+va*a:6+va*a));
    
    a=a+1;
    j42 = transpose(axes(i,1+va*a:3+va*a));
    r42 = transpose(axes(i,4+va*a:6+va*a));

    a=a+1;
    j43 = transpose(axes(i,1+va*a:3+va*a));
    r43 = transpose(axes(i,4+va*a:6+va*a));    

    a=a+1;
    j44 = transpose(axes(i,1+va*a:3+va*a));
    r44 = transpose(axes(i,4+va*a:6+va*a));
    
    % object origin
    o = transpose(object(i,:));
    
%--------------------------------------------
    
    % now we can write the matrices 
    
    
    % JACOBIAN MATRIX
    % jacobian for contact 1
    Z1 = [skew(c1-j21)'*r21 skew(c1-j22)'*r22 skew(c1-j23)'*r23 skew(c1-j24)'*r24 zeros(3,9); r21 r22 r23 r24 zeros(3,9)];
    
    %only translation
    %Z1 = [skew(c1-j21)'*r21 skew(c1-j22)'*r22 skew(c1-j23)'*r23 skew(c1-j24)'*r24 zeros(3,9)];
  
    % jacobian for contact 2
    Z2 = [zeros(3,4) skew(c2-j31)'*r31 skew(c2-j32)'*r32 skew(c2-j33)'*r33 skew(c2-j34)'*r34 zeros(3,5); zeros(3,4) r31 r32 r33 r34 zeros(3,5)];

    %only translation
    %Z2 = [zeros(3,4) skew(c2-j31)'*r31 skew(c2-j32)'*r32 skew(c2-j33)'*r33 skew(c2-j34)'*r34 zeros(3,5)];
    
    % jacobian for contact 3
    Z3 = [zeros(3,8) skew(c3-j40)'*r40 skew(c3-j41)'*r41 skew(c3-j42)'*r42 skew(c3-j43)'*r43 skew(c3-j44)'*r44; zeros(3,8) r40 r41 r42 r43 r44];
    
    %only translation
    %Z3 = [zeros(3,8) skew(c3-j40)'*r40 skew(c3-j41)'*r41 skew(c3-j42)'*r42 skew(c3-j43)'*r43 skew(c3-j44)'*r44];
      
    % full jacobian in the contact frame
    J = [ R1'*Z1 ; R2'*Z2 ; R3'*Z3 ];
    
    % GRASP MATRIX
    % grasp matrix for contact 1
    P1 = [eye(3) zeros(3,3);skew(c1-o) eye(3)]; 
    
    %only translation
    %P1 = [eye(3) skew(c1-o)]'; 
    
    % grasp matrix for contact 2
    P2 = [eye(3) zeros(3,3);skew(c2-o) eye(3)]; 
    
    %only translation
    %P2 = [eye(3) skew(c2-o) ]'; 
    
    % grasp matrix for contact 3
    P3 = [eye(3) zeros(3,3);skew(c3-o) eye(3)]; 
    
    %only translation
    %P3 = [eye(3) skew(c3-o) ]'; 
    
    % full grasp matrix
    Gt = [R1'*P1' ; R2'*P1' ; R3'*P3']; % the "t" is for transposed, just to keep nomenclature
    
    
    % MANIPULABILITY MATRIX ---------------------
    M = H*[-Gt J];
%    M = cleanzeros(H*[-Gt J]);
    
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
    [U,SIGMA,V] = svd(B2\B1);
    
    % egigenvalues in the case of using gsvd 
    % ORDER: lower to bigger when top to bottom
    SIGMA = sqrt(diag(Ce'*Ce)./diag(Se'*Se)); 
    %SIGMA=sort(SIGMA,'descend');
    %s = length(SIGMA);
    
   
    
    % Index 1: inverse of the condition number of the ratio matrix
    index1 = inv(max(SIGMA)/min(SIGMA));

    % Index 2: determinant of the ratio matrix
    index2 = prod(SIGMA);

    % Index 3: the minimum of the sngular values
    index3 = min(SIGMA);
    
    % map the ellipsoid axes to the output space
    u = diag(1./sqrt(SIGMA))*U;
    %u = P1w*A12*( sqrt(SIGMA)*U );
    %u = U*Ce;
    
