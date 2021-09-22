function t=generateprism(t,sides,stages)
% generates a regular prism tensegrity
% this function generates a tensegrity prisms of multiple stages (stages)
% and variable number of faces for each stage (sides).
%
% t=generateprism(t,sides,stages) returns a modified version of a
% tensegrity object equivalent to tensegrity regular prism of multiple
% stages and 'sides' faces each stage.
%
% The tensegrity (t) object must be initialized before calling this 
% function and the rows and columns parameters must be positive integers.
%
% See also tensegrity

num_nodes=0;
num_edges=0;
try
    t.dimension=3;
    t.class=1;
    n1=node();
    n2=node();
    n3=node();
    e1=edge();
    e2=edge();
    e3=edge();
    e4=edge();
    e5=edge();
    e6=edge();
    for j=1:1:stages
        for i=1:1:sides
            if j==1
                num_nodes=num_nodes+1;
                n1(j,i)=node(['node',num2str(num_nodes)],0,[]);
                num_nodes=num_nodes+1;
                n2(j,i)=node(['node',num2str(num_nodes)],0,[]);
                num_edges=num_edges+1;
                e1(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                num_edges=num_edges+1;
                e2(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                num_edges=num_edges+1;
                e3(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                num_edges=num_edges+1;
                e4(j,i)=edge(['edge',num2str(num_edges)],'strut','none','none');
                if stages>1
                    num_nodes=num_nodes+1;                
                    n3(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_edges=num_edges+1;                
                    e5(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;                                
                    e6(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                end
                % ralitzar les connexions
                [n1(j,i),e1(j,i)]=addincidentedge(n1(j,i),e1(j,i));
                [n1(j,i),e2(j,i)]=addincidentedge(n1(j,i),e2(j,i));
                [n1(j,i),e4(j,i)]=addincidentedge(n1(j,i),e4(j,i));
                if stages>1
                    [n1(j,i),e6(j,i)]=addincidentedge(n1(j,i),e6(j,i));
                end
                if i>1
                    [n1(j,i),e1(j,i-1)]=addincidentedge(n1(j,i),e1(j,i-1));
                end
                if i==sides
                    [n1(j,1),e1(j,i)]=addincidentedge(n1(j,1),e1(j,i));
                end
                [n2(j,i),e2(j,i)]=addincidentedge(n2(j,i),e2(j,i));
                [n2(j,i),e3(j,i)]=addincidentedge(n2(j,i),e3(j,i));
                if i>1
                    if stages>1
                        [n2(j,i),e5(j,i-1)]=addincidentedge(n2(j,i),e5(j,i-1));
                    else
                        [n2(j,i),e3(j,i-1)]=addincidentedge(n2(j,i),e3(j,i-1));
                    end
                    [n2(j,i),e4(j,i-1)]=addincidentedge(n2(j,i),e4(j,i-1));
                end
                if i==sides
                    if stages>1
                        [n2(j,1),e5(j,i)]=addincidentedge(n2(j,1),e5(j,i));
                    else
                        [n2(j,1),e3(j,i)]=addincidentedge(n2(j,1),e3(j,i));
                    end
                    [n2(j,1),e4(j,i)]=addincidentedge(n2(j,1),e4(j,i));
                end
                if stages>1
                    [n3(j,i),e3(j,i)]=addincidentedge(n3(j,i),e3(j,i));
                    [n3(j,i),e5(j,i)]=addincidentedge(n3(j,i),e5(j,i));
                    [n3(j,i),e6(j,i)]=addincidentedge(n3(j,i),e6(j,i));
                end
            else
                if j>1 && j<stages
                    num_nodes=num_nodes+1;
                    n1(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_nodes=num_nodes+1;
                    n2(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_edges=num_edges+1;
                    e1(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e2(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e3(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e4(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e5(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e6(j,i)=edge(['edge',num2str(num_edges)],'strut','none','none');
                    if mod(j,2)%imparells
                        [n1(j-1,i),e1(j,i)]=addincidentedge(n1(j-1,i),e1(j,i));
                        [n2(j-1,i),e2(j,i)]=addincidentedge(n2(j-1,i),e2(j,i));
                        [n2(j-1,i),e3(j,i)]=addincidentedge(n2(j-1,i),e3(j,i));
                        [n2(j-1,i),e6(j,i)]=addincidentedge(n2(j-1,i),e6(j,i));
                        [n1(j,i),e1(j,i)]=addincidentedge(n1(j,i),e1(j,i));
                        [n1(j,i),e2(j,i)]=addincidentedge(n1(j,i),e2(j,i));
                        [n1(j,i),e4(j,i)]=addincidentedge(n1(j,i),e4(j,i));
                        if i>1
                            [n1(j,i),e5(j,i-1)]=addincidentedge(n1(j,i),e5(j,i-1));
                            [n1(j,i),e6(j,i-1)]=addincidentedge(n1(j,i),e6(j,i-1));
                        end
                        if i==sides
                            [n1(j,1),e5(j,i-1)]=addincidentedge(n1(j,1),e5(j,i-1));
                            [n1(j,1),e6(j,i-1)]=addincidentedge(n1(j,1),e6(j,i-1));
                        end
                        [n2(j,i),e4(j,i-1)]=addincidentedge(n2(j,i),e4(j,i-1));
                        [n2(j,i),e5(j,i-1)]=addincidentedge(n2(j,i),e5(j,i-1));
                        [n2(j,i),e2(j,i-1)]=addincidentedge(n2(j,i),e2(j,i-1));
                    else%parells
                        [n2(j-1,i),e2(j,i)]=addincidentedge(n2(j-1,i),e2(j,i));
                        if i>1
                            [n2(j-1,i),e6(j,i-1)]=addincidentedge(n2(j-1,i),e6(j,i-1));
                        end
                        if i==sides
                            [n2(j-1,1),e6(j,i)]=addincidentedge(n2(j-1,1),e6(j,i));
                        end
                        [n3(j-1,i),e1(j,i)]=addincidentedge(n3(j-1,i),e1(j,i));
                        [n3(j-1,i),e3(j,i)]=addincidentedge(n3(j-1,i),e3(j,i));
                        [n3(j-1,i),e6(j,i)]=addincidentedge(n3(j-1,i),e6(j,i));
                        [n1(j,i),e2(j,i)]=addincidentedge(n1(j,i),e2(j,i));
                        [n1(j,i),e6(j,i)]=addincidentedge(n1(j,i),e6(j,i));
                        [n1(j,i),e4(j,i)]=addincidentedge(n1(j,i),e4(j,i));
                        if i>1
                            [n1(j,i),e1(j,i-1)]=addincidentedge(n1(j,i),e1(j,i-1));
                            [n1(j,i),e5(j,i-1)]=addincidentedge(n1(j,i),e5(j,i-1));
                        end
                        if i==sides
                            [n1(j,1),e1(j,i)]=addincidentedge(n1(j,1),e1(j,i));
                            [n1(j,1),e5(j,i)]=addincidentedge(n1(j,1),e5(j,i));
                        end
                        [n2(j,i),e4(j,i)]=addincidentedge(n2(j,i),e4(j,i));
                        [n2(j,i),e5(j,i)]=addincidentedge(n2(j,i),e5(j,i));
                        [n2(j,i),e3(j,i)]=addincidentedge(n2(j,i),e3(j,i));
                    end
                else
                    num_nodes=num_nodes+1;
                    n1(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_edges=num_edges+1;
                    e1(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e2(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e3(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    num_edges=num_edges+1;
                    e4(j,i)=edge(['edge',num2str(num_edges)],'strut','none','none');
                    if j==2
                        [n2(j-1,i),e1(j,i)]=addincidentedge(n2(j-1,i),e1(j,i));
                        [n3(j-1,i),e4(j,i)]=addincidentedge(n3(j-1,i),e4(j,i));
                        [n3(j-1,i),e2(j,i)]=addincidentedge(n3(j-1,i),e2(j,i));
                    else
                        [n1(j-1,i),e1(j,i)]=addincidentedge(n1(j-1,i),e1(j,i));
                        [n2(j-1,i),e4(j,i)]=addincidentedge(n2(j-1,i),e4(j,i));
                        [n2(j-1,i),e2(j,i)]=addincidentedge(n2(j-1,i),e2(j,i));
                    end
                    if mod(j,2)%imparells
                        [n1(j,i),e1(j,i)]=addincidentedge(n1(j,i),e1(j,i));
                        [n1(j,i),e2(j,i)]=addincidentedge(n1(j,i),e2(j,i));
                        [n1(j,i),e3(j,i)]=addincidentedge(n1(j,i),e3(j,i));
                        if i>1
                            [n1(j,i),e4(j,i-1)]=addincidentedge(n1(j,i),e4(j,i-1));
                            [n1(j,i),e3(j,i-1)]=addincidentedge(n1(j,i),e3(j,i-1));
                        end
                        if i==sides
                            [n1(j,1),e4(j,i)]=addincidentedge(n1(j,1),e4(j,i));
                            [n1(j,1),e3(j,i)]=addincidentedge(n1(j,1),e3(j,i));
                        end
                    else%parells
                        [n1(j,i),e1(j,i)]=addincidentedge(n1(j,i),e1(j,i));
                        [n1(j,i),e4(j,i)]=addincidentedge(n1(j,i),e4(j,i));
                        [n1(j,i),e3(j,i)]=addincidentedge(n1(j,i),e3(j,i));
                        if i>1
                            [n1(j,i),e2(j,i-1)]=addincidentedge(n1(j,i),e2(j,i-1));
                            [n1(j,i),e3(j,i-1)]=addincidentedge(n1(j,i),e3(j,i-1));
                        end
                        if i==sides
                            [n1(j,1),e2(j,i)]=addincidentedge(n1(j,1),e2(j,i));
                            [n1(j,1),e3(j,i)]=addincidentedge(n1(j,1),e3(j,i));
                        end
                    end
                end
            end
        end
    end
    % afegir els nodes i arestes al tensegrity
    for j=1:1:stages
        for i=1:1:sides
            if j==1
                t=addnode(t,n1(j,i));
                t=addnode(t,n2(j,i));
                t=addedge(t,e1(j,i));
                t=addedge(t,e2(j,i));
                t=addedge(t,e3(j,i));
                t=addedge(t,e4(j,i));
                if stages>1
                    t=addedge(t,e5(j,i));
                    t=addedge(t,e6(j,i));
                    t=addnode(t,n3(j,i));
                end
            else
                if j>1 && j<stages
                    t=addnode(t,n1(j,i));
                    t=addnode(t,n2(j,i));
                    t=addedge(t,e1(j,i));
                    t=addedge(t,e2(j,i));
                    t=addedge(t,e3(j,i));
                    t=addedge(t,e4(j,i));
                    t=addedge(t,e5(j,i));
                    t=addedge(t,e6(j,i));
                else
                    t=addnode(t,n1(j,i));
                    t=addedge(t,e1(j,i));
                    t=addedge(t,e2(j,i));
                    t=addedge(t,e3(j,i));
                    t=addedge(t,e4(j,i));
                end
            end
        end
    end
catch
    rethrow(lasterror);
end