function pts = generate_harmonic( a,b,numpts,periods,amps,noiseamp )
% generate_harmonic generates numpts from a (mixed) harmonic with a and
% b input, and a given list of periods and amplitudes.  Optionally, add noise of
% amplitude noiseamp
%
% Example: generate_harmonic(-5,5,100,[1,2],0.1) generates 100 points
% sampled from sin(2*pi*x)+sin(pi*x), on domain (-5,5), with added noise of amplitude 0.1.

intlength=b-a;

%A=sort(intlength*rand(numpts,1)+a); % sorted list of numpts randomly uniformly distributed points from (a,b)
A=linspace(a,b,numpts)'; % numpts evenly distributed on (a,b)


freq = 2*pi./periods; % convert periods to frequencies

tmp = repmat(freq,size(A,1),1); % matrix with numpts rows.  Each row is (the same) list of frequencies.

repA = repmat(A,1,size(freq,2)); % A repeated (in columns) as many times as there are periods.

C = sin(tmp.*repA); % generate data for each of the frequencies

for i=1:size(amps,2)
    C(:,i)=C(:,i)*amps(i);
end


C = sum(C,2)+noiseamp*(2*rand(numpts,1)-1); % add frequencies and noise


%C = C/sqrt(sum(C.*C)); % normalize C


pts=[A,C]; % combine x and y values

end

