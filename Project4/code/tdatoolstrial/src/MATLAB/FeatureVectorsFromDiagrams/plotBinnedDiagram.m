function plotBinnedDiagram(bD,extent,res)
%PLOTBINNEDDIAGRAM Simple plotting function for illustrating binning
%   INPUTS:
%       bD -- 2D array, the binned diagram
%       extent -- see the binDiagram function
%       res -- see the binDiagram function
%
%Author: Nate Strawn, 2014

m1 = sprintf('Birth < %.2f',extent(2));
m2 = sprintf('Birth > %.2f',extent(3));
xlabs = {m1, m2};
ylab = sprintf('Lifetime > %.2f',extent(1));

imagesc(bD)
colormap(gray);
colorbar
set(gca,'XTick',[1; res(2)+2],'XTickLabel',xlabs,'YTick',[extent(1)-1],'YTickLabel',ylab);

hold on
% Plot threshold lines for binning regions...
plot([1.5 1.5],[0.75 res(1)+1.5],'--r','LineWidth',3);
plot([res(2)+1.5 res(2)+1.5],[0.75 res(1)+1.5],'--r','LineWidth',3);
plot([0.6 res(2)+2.5],[1.5 1.5],'--r','LineWidth',3);

hold off



end

