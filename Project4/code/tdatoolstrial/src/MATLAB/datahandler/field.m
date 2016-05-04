classdef field
    %FIELD abstract class for data field
    %   Detailed explanation goes here
    
    properties
        name % name of the field
        entry  % values for the entry
    end
    
    methods
        
        function FObj = field(name,entry)
            FObj.name = name;
            FObj.entry = entry;
        end
        
    end
    
end

