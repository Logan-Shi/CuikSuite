function t=generatesnelsonx(t,rows,columns)
% generates a mesh of Snelson's X
% this function generates a mesh of Snelson's X with the dimensions specified
% by the parameters rows and columns, attaching them through the nodes.
%
% t=generatesnelsonx(t,rows,columns) returns a modified version of a
% tensegrity object equivalent to a mesh of Snelson's X.
%
% The tensegrity (t) object must be initialized before calling this 
% function and the rows and columns parameters must be positive integers.
%
% See also tensegrity

num_nodes=0;
num_edges=0;
try
    t.dimension=2;
    class=1;
    if rows>1
        if columns>1
            class=class+2;
        else
            class=class+1;
        end
    else
        if columns>1
            class=class+1;
        end
    end
    t.class=class;
    n1=node();
    n2=node();
    n3=node();
    n4=node();
    e1=edge();
    e2=edge();
    e3=edge();
    e4=edge();
    e5=edge();
    e6=edge();
    for j=1:1:rows
        for i=1:1:columns
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
                num_edges=num_edges+1;
                e5(j,i)=edge(['edge',num2str(num_edges)],'strut','none','none');
                if i==columns
                    num_nodes=num_nodes+1;
                    n3(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_nodes=num_nodes+1;
                    n4(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_edges=num_edges+1;
                    e6(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                end
                [n1(j,i),e1(j,i)]=addincidentedge(n1(j,i),e1(j,i));
                [n1(j,i),e2(j,i)]=addincidentedge(n1(j,i),e2(j,i));
                [n1(j,i),e5(j,i)]=addincidentedge(n1(j,i),e5(j,i));
                if i>1
                    [n1(j,i),e1(j,i-1)]=addincidentedge(n1(j,i),e1(j,i-1));
                    [n1(j,i),e4(j,i-1)]=addincidentedge(n1(j,i),e4(j,i-1));
                end
                [n2(j,i),e2(j,i)]=addincidentedge(n2(j,i),e2(j,i));
                [n2(j,i),e3(j,i)]=addincidentedge(n2(j,i),e3(j,i));
                [n2(j,i),e4(j,i)]=addincidentedge(n2(j,i),e4(j,i));
                if i>1
                    [n2(j,i),e3(j,i-1)]=addincidentedge(n2(j,i),e3(j,i-1));
                    [n2(j,i),e5(j,i-1)]=addincidentedge(n2(j,i),e5(j,i-1));
                end
                if i==columns
                    [n3(j,i),e1(j,i)]=addincidentedge(n3(j,i),e1(j,i));
                    [n3(j,i),e4(j,i)]=addincidentedge(n3(j,i),e4(j,i));
                    [n3(j,i),e6(j,i)]=addincidentedge(n3(j,i),e6(j,i));
                    [n4(j,i),e3(j,i)]=addincidentedge(n4(j,i),e3(j,i));
                    [n4(j,i),e5(j,i)]=addincidentedge(n4(j,i),e5(j,i));
                    [n4(j,i),e6(j,i)]=addincidentedge(n4(j,i),e6(j,i));
                end
            else
                num_nodes=num_nodes+1;
                n1(j,i)=node(['node',num2str(num_nodes)],0,[]);
                num_edges=num_edges+1;
                e1(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                num_edges=num_edges+1;
                e2(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                num_edges=num_edges+1;
                e3(j,i)=edge(['edge',num2str(num_edges)],'strut','none','none');
                num_edges=num_edges+1;
                e4(j,i)=edge(['edge',num2str(num_edges)],'strut','none','none');
                if i==columns
                    num_nodes=num_nodes+1;
                    n2(j,i)=node(['node',num2str(num_nodes)],0,[]);
                    num_edges=num_edges+1;
                    e5(j,i)=edge(['edge',num2str(num_edges)],'cable','none','none');
                end
                if j==2
                    [n2(j-1,i),e1(j,i)]=addincidentedge(n2(j-1,i),e1(j,i));
                    [n2(j-1,i),e4(j,i)]=addincidentedge(n2(j-1,i),e4(j,i));
                else
                    [n1(j-1,i),e1(j,i)]=addincidentedge(n1(j-1,i),e1(j,i));
                    [n1(j-1,i),e4(j,i)]=addincidentedge(n1(j-1,i),e4(j,i));
                end
                if i>1
                    if j==2
                        [n2(j-1,i),e3(j,i-1)]=addincidentedge(n2(j-1,i),e3(j,i-1));
                    else
                        [n1(j-1,i),e3(j,i-1)]=addincidentedge(n1(j-1,i),e3(j,i-1));
                    end
                end
                if i==columns
                    if j==2
                        [n4(j-1,i),e3(j,i)]=addincidentedge(n4(j-1,i),e3(j,i));
                        [n4(j-1,i),e5(j,i)]=addincidentedge(n4(j-1,i),e5(j,i));
                    else
                        [n2(j-1,i),e3(j,i)]=addincidentedge(n2(j-1,i),e3(j,i));
                        [n2(j-1,i),e5(j,i)]=addincidentedge(n2(j-1,i),e5(j,i));
                    end
                end
                [n1(j,i),e1(j,i)]=addincidentedge(n1(j,i),e1(j,i));
                [n1(j,i),e2(j,i)]=addincidentedge(n1(j,i),e2(j,i));
                [n1(j,i),e3(j,i)]=addincidentedge(n1(j,i),e3(j,i));
                if i>1
                    [n1(j,i),e2(j,i-1)]=addincidentedge(n1(j,i),e2(j,i-1));
                    [n1(j,i),e4(j,i-1)]=addincidentedge(n1(j,i),e4(j,i-1));
                end
                if i==columns
                    [n2(j,i),e2(j,i)]=addincidentedge(n2(j,i),e2(j,i));
                    [n2(j,i),e5(j,i)]=addincidentedge(n2(j,i),e5(j,i));
                    [n2(j,i),e4(j,i)]=addincidentedge(n2(j,i),e4(j,i));
                end
            end
        end
    end
    for j=1:1:rows
        for i=1:1:columns
            if j==1
                t=addnode(t,n1(j,i));
                t=addnode(t,n2(j,i));
                t=addedge(t,e1(j,i));
                t=addedge(t,e2(j,i));
                t=addedge(t,e3(j,i));
                t=addedge(t,e4(j,i));
                t=addedge(t,e5(j,i));
                if i==columns
                    t=addnode(t,n3(j,i));
                    t=addnode(t,n4(j,i));
                    t=addedge(t,e6(j,i));
                end
            else
                t=addnode(t,n1(j,i));
                t=addedge(t,e1(j,i));
                t=addedge(t,e2(j,i));
                t=addedge(t,e3(j,i));
                t=addedge(t,e4(j,i));
                if i==columns
                    t=addnode(t,n2(j,i));
                    t=addedge(t,e5(j,i));
                end
            end
        end
    end
catch
    rethrow(lasterror);
end
