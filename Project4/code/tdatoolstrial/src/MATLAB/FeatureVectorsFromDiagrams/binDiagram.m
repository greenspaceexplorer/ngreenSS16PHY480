function bD = binDiagram(D,extent,resolution)
%BINDIAGRAM Compute "binned" diagram from birth-lifetime pairs
%   INPUTS:
%       D -- N by 2 array, birth-lifetime pairs
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

    
    % Compute the dimension of each bin inside of the region defined by the
    % extent parameter
    binSize = [extent(1)/resolution(1), (extent(3)-extent(2))/resolution(2)];
    res = resolution + [1,2]; % See NOTE above
    bD = zeros(res); % Initialize
    
    numPairs = size(D,1);
    
    for i = 1:numPairs % Add each pair to the appropriate "bin"
        
        vertIndex = res(1)+1 - min(res(1), max(1,ceil(D(i,2)/binSize(1))));
        horzIndex = min(res(2),max(1,ceil((D(i,1)-extent(2))/binSize(2))+1));
        
        bD(vertIndex,horzIndex) = bD(vertIndex,horzIndex) + 1;
        
    end

end

