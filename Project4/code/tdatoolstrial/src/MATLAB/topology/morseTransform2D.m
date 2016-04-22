function Y = morseTransform2D(X,extent,resolution)
%MORSETRANFORM2D 1D Morse filtration on all rows and columns of an image
%   INPUTS:
%       X -- 2D array, function values
%       extent -- see binDiagram function
%       resolution -- see binDiagram function
%   OUTPUTS:
%       Y -- 3 dimensional array, with 1 binned diagram for each fixed 3-
%           index. That is, each Y(:,:,c) is a binned diagram
%
%Author: Nate Strawn, 2014

Y = zeros(resolution(1)+1,resolution(2)+2,size(X,1)+size(X,2));

for i=1:size(X,1)
    Y(:,:,i) = binnedMorse(X(i,:),extent,resolution);
end

for j=1:size(X,2)
   Y(:,:,size(X,1)+j) = binnedMorse(X(:,j),extent,resolution); 
end

end

