function [ p ] = samplepointfromrectangle( p1,p2,p3 )
%SAMPLEPOINTFROMRECTANGLE Given three points in any dimension, this
%function returns a random point on the 'rectangle' (actually a parallogram) defined by the three
%points, uniformly distributed.

if (length(p1)~=length(p2) || length(p1)~=length(p2) || length(p1)~=length(p2))
    err = MException('ResultChk:OutOfRange', 'points do not have the same dimension!');
    throw(err);
end

v1 = p3-p1;
v2 = p2-p1;  % compute the two vectors

t = rand(1,2); % How far along each vector should our point be?


p = p1 + t(1)*v1 + t(2)*v2;

end

