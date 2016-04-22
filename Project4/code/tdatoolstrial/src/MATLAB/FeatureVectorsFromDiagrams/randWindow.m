function Y = randWindow(X, windowLength)
%RANDWINDOW returns a random window from the columns of X

M = size(X,2) - windowLength + 1;

k = randi(M,1);

Y = X(:,k:k+windowLength-1);

end

