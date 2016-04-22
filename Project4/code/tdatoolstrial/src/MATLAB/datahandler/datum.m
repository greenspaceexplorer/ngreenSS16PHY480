classdef datum < handle
    %DATUM abstract singleton data class
    % 
    
    properties
        fields
        numFields
    end
    
    methods
        
        function DObj = datum(fieldNames, fieldEntries)
            DObj.numFields = size(fieldNames,2);
            DObj.fields = cell(1, DObj.numFields);
            
            for i = 1:DObj.numFields
                DObj.fields{i} = field(fieldNames{i},fieldEntries{i});
            end
        end
        
        % Function for appending new fields to the data
        function appendFields(obj,fieldNames,fieldEntries)
            numNewFields = size(fieldNames,2);
            newFields = cell(1, numNewFields);
            
            for i = 1:numNewFields
                newFields{i} = field(fieldNames{i},fieldEntries{i});
            end
            
            obj.fields = [obj.fields, newFields];
            obj.numFields = obj.numFields + numNewFields;
            
        end
        
        % Get function for named field value
        function fieldEntry = getFieldEntry(obj,fieldName)
            
            for i = 1:obj.numFields
                if strcmp(obj.fields{i}.name, fieldName)
                    fieldEntry = obj.fields{i}.entry;
                end
            end
            
        end
        
        % Set function fo field values
        function setFieldEntry(obj,fieldName, newFieldEntry)
            
            for i = 1:obj.numFields
                if strcmp(obj.fields{i}.name, fieldName)
                    obj.fields{i}.entry = newFieldEntry;
                end
            end
            
        end
        
    end
    
end

