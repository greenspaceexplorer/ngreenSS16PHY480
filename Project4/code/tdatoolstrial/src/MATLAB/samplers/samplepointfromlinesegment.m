function [ p ] = samplepointfromlinesegment( p1,p2 )
%SAMPLEPOINTFROMLINESEGMENT Given two points in any dimension, this
%function returns a random point on the line segment connecting the two
%points, uniformly distributed.

if length(p1)~=length(p2)
    err = MException('ResultChk:OutOfRange', 'p1 and p2 do not have the same dimension!');
    throw(err);
end

t=rand(); % How far along the line should our point be?

p=p1+t*(p2-p1);

end

