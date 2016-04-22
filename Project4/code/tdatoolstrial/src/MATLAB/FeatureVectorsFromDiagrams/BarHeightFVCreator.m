function [barHeightFVPer,barHeightFVPerBirth] = BarHeightFVCreator(MTX,n,N)

% This function takes a persistence diagram (MTX) and returns two vectors
% in Euclidean space.
% The first (barHeightFVPer) is obtained by first sorting the persistence
% points in MTX by persistence (death minus birth), and then extracting the
% n to N largest persistences as coordinates.
% The second (barHeightFVPerBirth) also incorporates birth information, by
% taking (persistence,birth) of each point as two coordinates, thus
% resulting in a vector twice the length of the other one.

%Default settings for n and N are 1 and 100.

%%%% Programmed by Alex Pieloch, Duke Univeristy- Department of Mathematics

%% Check that input data is formatted correctly
[rows,cols] = size(MTX);

if nargin == 1
    n = 1;
    N = 100;
end

if MTX(1,1)>MTX(1,2)
    error('a time of death is before a time of birth for a particular cycle. Are your columns mixed up?')
end

if cols ~= 2
    error('Incorrect Input: please read comment in function to understand correct input format')
end

if rows < N
    N = rows;
end



%% Create the first feature vector
Rn                      = MTX(:,2) - MTX(:,1);
Rn                      = sort(Rn,'descend');
R100                    = (Rn(n:N))';
barHeightFVPer(1,:)     = (R100);

%% Create the second feature vector
Rn(:,1)                 = MTX(:,2) - MTX(:,1);
Rn(:,2)                 = MTX(:,1);
Rn                      = sortrows(Rn);
Rn                      = flipdim(Rn,1);

iter1 = 0;
R200  = zeros(N-n+1,1);
for i = n:N
    for j = 1:2
        iter1        = iter1 + 1;
        R200(iter1)  = Rn(i,j);
    end
end
barHeightFVPerBirth(1,:) = R200;
end
