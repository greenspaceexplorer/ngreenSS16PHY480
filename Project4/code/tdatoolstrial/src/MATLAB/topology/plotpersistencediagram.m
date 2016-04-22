function [  ] = plotpersistencediagram( plotpts )
%plotpersistencediagram This function takes set of persistence intervals
%(as outputed by RCA1, morseFiltration, etc, and plots the persistence
%diagram, including the diagonal.

%plotpts = morseFiltration(data(:,2),false,false); % compute intervals

%Written by Rann Bar-On, Department of Mathematics, Duke University

M=max(plotpts(:));
m=min(plotpts(:));

M=max(M,0);
m=min(m,0);  % Ensure that the plot includes the origin.

diagonal=linspace(1.2*m,1.2*M,2);
plot(diagonal,diagonal);  % plot the diagonal
hold on

axis([1.2*m 1.2*M 1.2*m 1.2*M]); % set axes to include all points, with a bit of space on both sides


scatter(plotpts(:,1),plotpts(:,2),40, 'fill'); % plot the points on the persistence diagram
hold off

end

