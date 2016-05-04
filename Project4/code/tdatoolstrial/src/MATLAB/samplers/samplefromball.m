function [ ballpts ] = samplefromball( numpts, dim, rad )
%SAMPLEFROMBALL This function samples numpts points uniformly from the ball of radius rad
%in dimension dim.  Since this uses the discard method, it could
%theoretically loop forever, though this is extremely unlikely.

i=0;
while i<numpts
    pt = 2*rand(dim,1)-1;
    if sum(pt.*pt,1)<=1
        i=i+1;
        ballpts(i,:)=pt;
    end
end
    
end

