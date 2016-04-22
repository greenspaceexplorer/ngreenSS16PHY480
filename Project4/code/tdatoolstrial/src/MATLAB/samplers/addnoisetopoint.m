function [ p ] = addnoisetopoint( point, noiseamp )
%ADDNOISETOPOINT This function takes a point, detects its dimension and
%adds a bit of noise to it.  The noise is uniformly distributed in a sphere
%of radius noiseamp around the point.

dim = length(point);
noise = noiseamp*(2*rand(1,dim)-1);

p = point + noise;


end

