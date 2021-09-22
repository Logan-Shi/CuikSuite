function [J, G, n1, n2, n3] = GetMatrices(i,vc,va,axes,object,object_R,contacts,e)

%-------------- Computing the values required for the force closure evaluation
    % which axis influence a given contact 
    % needs to be done manually.-
    
    % object origin
    o = transpose(object(i,:));
    % object rotation
    Ro = [transpose(object_R(i,1:3)) transpose(object_R(i,4:6)) cross(transpose(object_R(i,1:3)),transpose(object_R(i,4:6)))];
    % object transformation
    To = [Ro o; [0 0 0 1]];
    
    c=0;
    % contact 1
    c1 = To*[transpose(contacts(i,1+vc*c:3+vc*c)); 1];
    c1 = c1(1:3);
    n1 = -1*Ro*transpose(contacts(i,4+vc*c:6+vc*c))/contacts(i,7+vc*c);
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
    c2 = To*[transpose(contacts(i,1+vc*c:3+vc*c)); 1];
    c2 = c2(1:3);
    n2 = -1*Ro*transpose(contacts(i,4+vc*c:6+vc*c))/contacts(i,7+vc*c);
    R2 = [n2 ortonormalvector(n2,0.1) cross(n2,ortonormalvector(n2,0.1))]; 
    R2 = blkdiag(R2,R2);
  
    a=a+1;
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
    c3 = To*[transpose(contacts(i,1+vc*c:3+vc*c)); 1];
    c3 = c3(1:3);
    n3 = -1*Ro*transpose(contacts(i,4+vc*c:6+vc*c))/contacts(i,7+vc*c);
    R3 = [n3 ortonormalvector(n3,0.1) cross(n3,ortonormalvector(n3,0.1))]; 
    R3 = blkdiag(R3,R3);
    
    a=a+1;
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

     % now we can write the matrices in the contact reference frame
    
    % JACOBIAN MATRIX
    
    % jacobian for contact 1
    Z1 = [skew(c1-j21)'*r21 skew(c1-j22)'*r22 skew(c1-j23)'*r23 skew(c1-j24)'*r24 zeros(3,9); r21 r22 r23 r24 zeros(3,9)];
 
    % jacobian for contact 2
    Z2 = [zeros(3,4) skew(c2-j31)'*r31 skew(c2-j32)'*r32 skew(c2-j33)'*r33 skew(c2-j34)'*r34 zeros(3,5); zeros(3,4) r31 r32 r33 r34 zeros(3,5)];
    
    % jacobian for contact 3
    Z3 = [zeros(3,8) skew(c3-j40)'*r40 skew(c3-j41)'*r41 skew(c3-j42)'*r42 skew(c3-j43)'*r43 skew(c3-j44)'*r44; zeros(3,8) r40 r41 r42 r43 r44];
    
    % full jacobian in the contact frame
    J = [ R1'*Z1 ; R2'*Z2 ; R3'*Z3 ];
    
    
    % GRASP MATRIX

    % grasp matrix for contact 1
    P1 = [eye(3) zeros(3,3);skew(c1-o) eye(3)]; 
    
    % grasp matrix for contact 2
    P2 = [eye(3) zeros(3,3);skew(c2-o) eye(3)]; 
    
    % grasp matrix for contact 3
    P3 = [eye(3) zeros(3,3);skew(c3-o) eye(3)]; 

    % full grasp matrix
    Gt = [R1'*P1' ; R2'*P2' ; R3'*P3']; % the "t" is for transposed, just to keep nomenclature

    G = transpose(Gt);

