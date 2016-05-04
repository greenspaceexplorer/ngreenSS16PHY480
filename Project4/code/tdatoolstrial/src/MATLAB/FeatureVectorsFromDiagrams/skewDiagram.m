function D = skewDiagram(D)
%SKEWDIAGRAM Turns birth-death diagrams into birth-lifetime diagrams
% 
    D(:,2) = D(:,2) - D(:,1);

end

