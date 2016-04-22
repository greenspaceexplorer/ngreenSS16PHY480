% Machine learning for the master set

loadmasterset % Load the masterset cell array

% masterset is "raw" data that must be processed before we can use it to
% train and test a model. Most of the processing involves just reorganizing
% data, but we will also transform the raw data to get a feature. In this
% case, our feature function is going to ingest the functional data for
% each of the 120 examples, and then return a "binned" diagram.

extent = [2 -2 2]; % Parameters for the feature function
res = [7,6]; % Parameters for the feature function
featureFcn = @(x) binnedMorse(x,extent,res); % Handle for the feature transform

% The master set includes 120 examples. We'll use 100 for training a model
% and 20 for testing the model. The different "types" of functions in the
% data set are P, N, NP, and MP

numTrain = 100;
types = {'P','N','NP','MP'};

trainingDatums = cell(1,numTrain); % Cell for holding onto training datum
testingDatums = cell(1,120 - numTrain); % Cell for testing datum

for i = 1:numTrain
    
    trainingDatums{i} = datum({'type','binned diagram'},{masterset{i,2}, featureFcn(masterset{i,1})});
    
end

for i = (numTrain+1):120
    
    testingDatums{i-100} = datum({'type','binned diagram'},{masterset{i,2}, featureFcn(masterset{i,1})});
    
end

trainingDataHandler = datahandler(trainingDatums); % Initialize a handler for the training data
testingDataHandler = datahandler(testingDatums); % For the testing data

% Now, we'll train a simple Poisson model on all of the entries of the
% diagrams.
PoissonModel = gridPoisson(res + [1,2],trainingDataHandler,types,'binned diagram');

% We can now compute the confusion matrix for the model, or the proportions
% of (true,guess) pairs that our classifier presents.
confusionMTX = PoissonModel.classify(testingDataHandler,'binned diagram')/(120 - numTrain)

% The trace of the confusion matrix is the proportion of examples upon
% which the classifier is exactly correct
fprintf('Trained classifier is correct %.2f percent of the time.\n', 100 * trace(confusionMTX));
fprintf('Pure guessing classifier would be correct approximately %.2f percent of the time.\n', 100 / numel(types));


    