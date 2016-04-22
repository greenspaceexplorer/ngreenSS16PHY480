classdef datahandler < handle
    %DATAHANDLER class for managing data
    %   Includes subsampling methods
    
    properties
        
        data % Cell containing the data
        numData % Length of the cell containing the data
        
    end
    
    methods
        
        function DHObj = datahandler(data)
            DHObj.data = data;
            DHObj.numData = size(data,2);
        end
        
        % Append a new field to the each data member
        function map(obj, fcn, fcnName)
            
            for i = 1:obj.numData
                obj.data{i}.appendFields({fcnName}, {fcn(obj.data{i})});
            end
            
        end
        
        % Subset of the data using indices
        function dH = subset(obj,indices)
            
           subsetData = cell(1,numel(indices));
           
           for i = 1:numel(indices)
               subsetData{i} = obj.data{indices(i)};
           end
           
           dH = datahandler(subsetData);
           
        end
        
        % Merge two datahandlers
        function dH = merge(obj,mergingDH)
           
            mergedData = cell(1,obj.numData+mergingDH.numData);
            
            for i = 1:obj.numData
                mergedData{i} = obj.data{i};
            end
            
            for i = 1:mergingDH.numData
                mergedData{i+obj.numData} = mergingDH.data{i};
            end
            
            dH = datahandler(mergedData);
            
        end
            
        % Randomly subsample the data, keeping only derived information
        function newDHObj = randSubsample(obj, numSamples, fcns, fcnNames)
            
            newData = cell(1,numSamples);
            k = randi(obj.numData,numSamples);
            numFcns = size(fcns,2);
            
            for i = 1:numSamples
                fcnVals = cell(1,numFcns);
                
                for j = 1:numFcns
                    fcnVals{j} = fcns{j}(obj.data{k(i)});
                end
                
                newData{i} = datum(fcnNames, fcnVals);
                
            end
                
           newDHObj = datahandler(newData);
        end
        
        % Subsample the data based on some 0-1 criteria functional
        function newDHObj = subsample(obj, indicatorFcn)
            
            indicatorVals = zeros(1,obj.numData);
            
            for i = 1:obj.numData
                indicatorVals(i) = indicatorFcn(obj.data{i});
            end
            
            newNumData = sum(indicatorVals);
            newData = cell(1,newNumData);
            
            index = 1;
            
            for i = 1:obj.numData
                if indicatorVals(i) == 1
                    newData{index} = obj.data{i};
                    index = index + 1;
                end
            end
                
            newDHObj = datahandler(newData);
        end
        
                    
    end
    
end

