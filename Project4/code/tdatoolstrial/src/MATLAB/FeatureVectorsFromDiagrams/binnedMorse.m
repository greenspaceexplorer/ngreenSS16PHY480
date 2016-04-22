function bD = binnedMorse(f,extent,resolution)
%BINNEDMORSE Compute binned Morse filtration (wrapper for
%   binDiagram(morseFiltration)
%
%   INPUTS:
%       f -- a 1 by N array, valuse of a 1D function
%       extent -- an array of the form [height,lbound,ubound]
%           o height -- any lifetime value above this will go into an 
%               overflow bin, below is partitioned according to vertRes
%           o lbound, ubound -- below lbound and above ubound are two
%               overflow regions, the interval between is partitioned into
%               horzRes many regions
%       resolution -- an array of the form [vertRes, horzRes]
%           o vertRes -- integer indicating number of vertical partitions
%           o horzRes -- integer indicating number of horizontal partitions
%           NOTE: the dimensions of the binned diagram are
%           vertRes+1 by horzRes+2 because of overflow bins
%   OUTPUTS:
%       bD -- 2D array of size vertRes+1 by horzRes+2, takes integer values
%           indicating the number of birth-lifetime pairs in corresponding
%           partition elements determined by the extent and resolution
%           parameters
%
%Author: Nate Strawn, 2014

% First compute the augmented and skewed Morse filtration
    D = morseFiltration(f,true,true);
    
% Bin the diagram
   bD = binDiagram(D,extent,resolution);

end

