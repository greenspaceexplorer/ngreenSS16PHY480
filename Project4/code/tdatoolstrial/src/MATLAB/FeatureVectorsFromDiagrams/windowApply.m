function y = windowApply(x,fcn,fcnDim,windowLength)
%WINDOWAPPLY Applies a function to all "windows" of a particular length
%   INPUTS:
%       x -- 1 by N array, list of squential values
%       fcn -- function handle, to be applied to all windows; must return a
%           column.
%       fcnDim -- specifies the dimension of the function output
%       windowLength -- integer specifying length of the window
%   OUTPUTS:
%       y -- fcnDim by M array, the value of the function on all windows of
%           x
%
%Author: Nate Strawn, 2014

    M = size(x,2) - windowLength +1; % number of columns of y
    y = zeros(fcnDim,M);

    for i=1:M
        y(:,i) = fcn(x(:,i:i+windowLength-1));
    end

end

