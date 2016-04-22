function [  ] = plotpersistencecell( pcell )
%PLOTPERSISTENCECELL This function takes a cell array consisting of
%persistence diagrams and plots them all in an array of subfigures.  It
%attempts to keep the array as square as possible.

%Written by Rann Bar-On, Department of Mathematics, Duke University.

f=length(pcell);
r=ceil(sqrt(f));
c=ceil(f/r);

n=repmat(cumsum(ones(1,r*c)),1,f);
h=ceil( (1:f*r*c)/(r*c) );

for i=1:f
    figure(h(i))
    subplot(r,c,n(i))
    plotpersistencediagram(pcell{i})
end

