function [ p ] = samplefromcross( corner1,corner2,corner3,corner4,noiseamp )
% SAMPLEFROMCROSS This function returns a point sampled from a cross with
% its four endpoints specified, uniformly on each line segment, and with a 0.5 probability from each one.  
% The ends of the two segments of the cross are corner1/corner2 and corner3/corner4 resp.  Optionally, it
% adds noise (i.e. shifts each point randomly within a circle of radius
% noiseamp from its original position on the cross).


length1=norm(corner2-corner1);
length2=norm(corner4-corner3);

%proportion1=length1/(length1+length2); % figure out what proportions each of the lines are out of the total length

coin=rand(); % which line segment to sample from

if coin<0.5
    p=samplepointfromlinesegment(corner1,corner2);
    
else
    p=samplepointfromlinesegment(corner3,corner4);
end

p=addnoisetopoint(p,noiseamp);

end

