function [ varargout ] = rca1mfscm( mfscm, distanceBoundOnEdges, BirthDeathGivers )
%rca1mfscm(mfscm, distanceBoundOnEdges) This code computes the 1- and 0-D 
%persistence diagrams associated to a simplex-constant function F on a simplicial complex K.
%
%It relies on the Java TDA set.  The output
%is both the 0 and 1-D persistence diagrams, as well as the number of edges
%and the number of columns in the reduction matrix:
%
%If only one object is captured in output, it is the 1-D diagram.  
%
%If two, they are the 1-D and 0-D diagrams.  
%
%If four, the are the 1-D and 0-D diagrams, followed by the number of edges
%and the number of columns in the reduction matrix.
%
% More precisely:
% - The F-values on the vertices may be arbitrary.
%
% - The F-values on an edge must not be smaller than the F-value of its two vertices.
%
% - The F-value on a higher simplex must be the maximum F-value
%   on any of its boundary edges.
%
% The input to this code is a distance bound distanceBoundOnEdges, and an N by 3 array mfscm.
%
% The rows in mfscm are of two forms, subject to conditions 1 and 3 below
%
% The code attempts to aggressively fix the matrix so that condition 2 is
% fulfilled.  The user should not have to think about vertex numbering...
%
% Condition 1: For each vertex i, S must have a row of the form 
%
%               i   i   F(i)
%
% Condition 2: The vertices must be indexed from 0 to (n-1), where n is the
% number of vertices.  Additionally, F(i) <= F(i+1) for all i.
%
% Condition 3: The other rows in S are of the form
%
%               i  j  F(i,j)
%
% where F(i,j) is defined to be the F-value on the edge between vertex i and vertex j.
% F(i,j) must be greater than or equal to F(i) and F(j).

%Written by Rann Bar-On, Department of Mathematics, Duke University

if nargin < 3
  BirthDeathGivers = false;
end


if nargout==3
    err = MException('OutputChk:OutOfRange', 'You may not call this function with 3 output variables!  Use 1, 2, or 4!');
    throw(err);
end

if isempty(mfscm) 
    err = MException('ResultChk:OutOfRange', 'Array is empty!');
    throw(err);
end

if size(mfscm,2) ~= 3
    err = MException('ResultChk:OutOfRange', 'Matrix is not an n x 3 matrix!');
    throw(err);
end    

s=size(mfscm,1);          % Edges + vertices

coords = mfscm(:,1:2);
numverts=max(coords(:))+1;  % total number of vertices
numedges=s-numverts;


diags=zeros(numverts,3);          % initialize diagonal part of array
offdiags=zeros(numedges,3);      % initialize off diagonal part of array

j=1;                   % counter of diagonal entries (i.e. vertices)
k=1;                   % counter for off diagonals

for i=1:s              % create valid array for TDA Java
    if mfscm(i,1)==mfscm(i,2)
        diags(j,:)=mfscm(i,:);  % this is a diagonal entry, so put it in diags
        j=j+1;           % next diagonal
    else
        offdiags(k,:)=mfscm(i,:);  % Non-diagonal entry, put it in offdiags
        k=k+1;          % next off diagonal
    end
end

diags = sortrows(diags,1); % put diagonal entries in order of original vertex numbering

% Condition 1: check if we have function values for all vertices
if ~(isequal(diags(:,1)' + 1, 1:numverts))
    err = MException('ResultChk:OutOfRange', 'Matrix does not contain function values for all vertices! See condition 1 in documentation for rca1sm!');
    throw(err);
end

% Condition 2: fix matrix to make sure it's fulfiled.  No need for use to
% do this manually!
[sorteddiags,ind]=sortrows(diags,3); % sort diagonal entries in order of F value, storing the permutation from the previous sort

m=vertcat(sorteddiags,offdiags); % Create an initial matrix with the sorted diagonals and the off-diagonal entries

m(:,1:2)=changem(m(:,1:2),0:(numverts-1),ind-1);   % renumber the vertices using the sort index.  
                                                   % This ensures condition 2 is fulfiled without
                                                   % requiring it from the user.


% Condition 3: check if function value on edges is at least the function value on their vertices.                                                   
diags=m(1:numverts,:); % get new diagonal entries
offdiags=m(numverts+1:end,:); % get new off-diagonal entries

for i=1:numedges
    
    r=offdiags(i,1);        % row number
    c=offdiags(i,2);        % column number
    
    if offdiags(i,3)<diags(r+1,3) || offdiags(i,3)<diags(c+1,3)  % check if function on this edge is at least the function value on its vertices.
        err = MException('ResultChk:OutOfRange', 'Value on edge is less than value of vertices!  This is not a monotonic function on a simplex!  See condition 3 in documentation for rca1sm!');
        throw(err);
    end
    
end

% We got here without error, so the matrix m should be correct.  Pass it on.

tda = initializejavaTDA();  % create a new Java TDA object

param2 = strcat( 'distanceBoundOnEdges=', num2str( distanceBoundOnEdges ) ); % set distancebound as string

    
tda.RCA1( { 'taskChoice=M12', 'supplyDataAs=monotonicFunctionOnSimplicialComplexMatrix', param2 }, m);  % compute 1-D persistence, using supplied parameters


% hjs 10/21/2014 Add expanded I1 results, and tie them to zeroGen input parameter
if BirthDeathGivers
	I0 = tda.getResults(0).getIntervalsAndBirthDeathGiversDim0;  % 0-D intervals with extra info
	I1 = tda.getResults(1).getIntervalsAndBirthDeathGiversDim1;  % 1-D intervals with extra info
else 
	I0 = tda.getResults(0).getIntervals;  % 0-D intervals
	I1 = tda.getResults(1).getIntervals;  % 1-D intervals
end


edges = tda.getResults(2); % number of edges
redcols = tda.getResults(3); % number of columns in the reduction matrix

varargout{1}=I1;

if nargout>1
    varargout{2}=I0;
end

if nargout==4
    varargout{3}=edges;
    varargout{4}=redcols;
end

end

