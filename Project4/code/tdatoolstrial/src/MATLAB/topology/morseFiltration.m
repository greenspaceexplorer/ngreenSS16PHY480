function D = morseFiltration(f,aug,skew)
%MORSEFILTRATION compute Morse filtration
%   INPUTS:
%       f -- 1 by N array, representing values of a 1D function.
%   OPTIONAL INPUTS:
%       aug (default = false) Boolean, indicating whether classes that are 
%           immediately absorbed are included in the diagram. This leads to
%           many additional points along the diagonal of the persistence
%           diagram.
%       skew (default = false) Boolean, indicating whether the diagram
%           should be transformed from birth-death pairs to birth-lifetime
%           pairs.
%   OUTPUTS:
%       D -- K by 2 array, persistence diagram
%
%Author: Nate Strawn, 2014

    % Set defaults for aug and skew 
    if nargin < 3
        skew = false;
    end

    if nargin < 2
        aug = false;        
    end

    N = numel(f); % Length of f
    [x,index] = sort(f); % Sort values of f in ascending order
    indicator = -ones(1,N); % Array for tracking class indicators, -1 = not in sublevel set
    D=[]; % Initialize the diagram

    for i=1:N
    
        k = index(i);

        % Deal with the endpoints
        if k == 1
            if indicator(2) == -1
                indicator(1) = i;
            else
                indicator(1) = indicator(2);
                
                if aug
                    D = [D; x(i),x(i)];
                end
            end

        elseif k == N
            if indicator(N-1) == -1
                indicator(N) = i;
            else
                indicator(N) = indicator(N-1);
                
                if aug
                    D = [D; x(i),x(i)];
                end
            end

        else % The general case

            if indicator(k+1) == -1
                if indicator(k-1) == -1
                    indicator(k) = i; % case of isolated point
                else % killed by the left only
                    indicator(k) = indicator(k-1);
                    
                    if aug
                        D = [D; x(i),x(i)];
                    end
                end
            else % killed by the right
                if indicator(k-1) == -1
                    indicator(k) = indicator(k+1);
                    
                    if aug
                        D = [D; x(i),x(i)];
                    end
                else % left and right classes merge
                    a = indicator(k-1);
                    b = indicator(k+1);
                    if a < b % left kills right
                        
                        D = [D; x(b),x(i)];
                        if aug
                            D = [D; x(i),x(i)];
                        end
                        % change all class indicators
                        indicator(k) = b;
                        while k <= N && indicator(k) == b
                            indicator(k) = a;
                            k = k+1;
                        end
                    else % right kills left
                        
                        D = [D; x(a),x(i)];
                        if aug
                            D = [D; x(i),x(i)];
                        end
                        % change all class indicators
                        indicator(k) = a;
                        while k >= 1 && indicator(k) == a
                            indicator(k) = b;
                            k = k-1;
                        end   
                    end

                end

            end          
        
        end
        
    end
    
% Now compute the birth/lifetime diagram if skew = true
    if skew
        D(:,2) = D(:,2) - D(:,1);
    end
end

