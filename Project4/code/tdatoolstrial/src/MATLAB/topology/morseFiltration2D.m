function [D0,D1] = morseFiltration2D(F)
%MORSEFILTRATION2D Performs the Morse filtration to compute the 0D and 1D
%   INPUTS:
%       F -- 2D array, represents values of a function on a rectangle
%   OUTPUTS:
%       D0 -- K0 by 2 array, persistence diagram for 0D homology
%       D1 -- K1 by 2 array, persistence diagram for 1D homology
%   
%Author: Nate Strawn, 2014

    dims = size(F); % Dimension of the function domain
    
    N = numel(F); % Total number of points
    [X,indices] = sort(F(:)); % Sort the values, indices are "unravelled"
    [I,J] = ind2sub(size(F),indices); % Turn the unravelled indices into array indices
    
    indicator = -ones(size(F)); % Indicators for class membership, -1 = not yet in sublevel set 
    D0 = zeros(N,2); % Initialize diagram for components
    D1 = zeros(N,2); % Initialize diagram for loops
    
    count = 0;
    difference = [-1 0; 1 0; 0 -1; 0 1]; % Difference vectors to neighbor indices
    for k = 1:N % Add each index pair in order of ascending value in F
        
        i = I(k);
        j = J(k);
        
        
        % Determine the neighbors of (i,j) in the graph
        neighbors_ = zeros(1,4);
        
        if i > 1
            neighbors_(1) = 1;
        end
        
        if i < dims(1)
            neighbors_(2) = 1;
        end
        
        if j > 1
            neighbors_(3) = 1;
        end
        
        if j < dims(2)
            neighbors_(4) = 1;
        end
        
        % Calculate the indices of the neighbors
        neighbors = bsxfun(@plus,difference(logical(neighbors_),:),[i j]);
        
        % Find the indicators of the neighbors
        nhbrIndicators = zeros(size(neighbors,1),1);
        for l = 1:size(neighbors,1)
            nhbrIndicators(l) = indicator(neighbors(l,1),neighbors(l,2));
        end
        
        % Find the unique values in the list of indicators
        uniqueIndicators = unique(nhbrIndicators)';
        
        % If the only unique indicator is -1, we activate an indicator
        if (numel(uniqueIndicators) == 1 && uniqueIndicators(1) == -1) 
            indicator(i,j) = k;
        end
        
        % Remove the -1 indicators
        uniqueIndicators = uniqueIndicators(uniqueIndicators > 0);
        
        % If only one indicator, just absorb
        if numel(uniqueIndicators) == 1
            indicator(i,j) = uniqueIndicators(1);
        end
        
        % If there are more than two such indicators, classes will need to
        % die
        
        if numel(uniqueIndicators) > 1
            oldest = min(uniqueIndicators);
            uniqueIndicators = uniqueIndicators(uniqueIndicators > oldest);
            
            for ind = uniqueIndicators
                count = count + 1;
                D0(count,:) = [X(ind) X(k)]; % add the birth-death pair for this class
                indicator(indicator == ind) = oldest; % change the indicators of the dead class
            end
            
            indicator(i,j) = oldest;
        end
        
    end
    
    D0 = D0(1:count,:); % Get rid of unused space
    
    % Use duality to compute D1...
    indicator = -ones(size(F)); % reset indicators
    indicator(1,:) = numel(F) + 1;
    indicator(size(F,1),:) = numel(F) + 1;
    indicator(:,1) = numel(F) + 1;
    indicator(:,size(F,2)) = numel(F) + 1; % the boundary absorbs all
    
    count = 0;
    difference = [-1 0; 1 0; 0 -1; 0 1; -1 -1; -1 1; 1 -1; 1 1];
    for k = fliplr(1:N)
        
        i = I(k);
        j = J(k);
        
        neighbors_ = zeros(1,8);
        
        if i > 1
            neighbors_(1) = 1;
            
            if j > 1
                neighbors_(5) = 1;
            end
            
            if j < dims(2)
                neighbors_(6) = 1;
            end
            
        end
        
        if i < dims(1)
            neighbors_(2) = 1;
            
            if j > 1
                neighbors_(7) = 1;
            end
            
            if j < dims(2)
                neighbors_(8) = 1;
            end
            
        end
        
        if j > 1
            neighbors_(3) = 1;
        end
        
        if j < dims(2)
            neighbors_(4) = 1;
        end
        
        neighbors = bsxfun(@plus,difference(logical(neighbors_),:),[i j]);
        
        % find the indicators of the neighbors
        nhbrIndicators = zeros(size(neighbors,1),1);
        for l = 1:size(neighbors,1)
            nhbrIndicators(l) = indicator(neighbors(l,1),neighbors(l,2));
        end
        
        % find the unique values in the list of indicators
        uniqueIndicators = unique(nhbrIndicators)';
        
        % if the only unique indicator is -1, we activate an indicator
        if (numel(uniqueIndicators) == 1 && uniqueIndicators(1) == -1) 
            indicator(i,j) = k;
        end
        
        % remove the -1 indicators
        uniqueIndicators = uniqueIndicators(uniqueIndicators > 0);
        
        % if only one indicator, just absorb
        if numel(uniqueIndicators) == 1
            indicator(i,j) = uniqueIndicators(1);
        end
        
        % if there are more than two such indicators, classes will need to
        % die
        
        if numel(uniqueIndicators) > 1
            oldest = max(uniqueIndicators);
            uniqueIndicators = uniqueIndicators(uniqueIndicators < oldest);
            for ind = uniqueIndicators
                count = count + 1;
                D1(count,:) = [X(k+1) X(ind)]; % add the birth-death pair for this class
                indicator(indicator == ind) = oldest; % change the indicators of the dead class
            end
            indicator(i,j) = oldest;
        end
        
    end
    
    D1 = D1(1:count,:); % Remove unused space
 
end

