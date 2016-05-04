function [ pcloud ] = spheresampler( dim,rad,samplesize,noisemultiplier )
%spheresample Generates point clouds from spheres
%   This function will return a size samplesize point cloud, sampled
%   uniformly from a sphere of dimension dim and radius rad.

    A=rad*randn([samplesize dim]);
    B=noisemultiplier*randn([samplesize 1]);
    scaled=bsxfun(@rdivide,A,sqrt(sum(A.^2,2)));
    pcloud=bsxfun(@times,scaled,1+B);
    
end

