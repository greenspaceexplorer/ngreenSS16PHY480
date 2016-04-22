function isSame = typeCompare(var1, var2)
%TYPECOMPARE Compare strings and numbers
%   var1, var2 are strings or numbers to be compared

if ischar(var1)
    isSame = strcmp(var1,var2);
elseif isnumeric(var1)
    if size(var1) == [1 1]
        isSame = (var1 == var2);
    end
else
    error('typeCMPerr','Comparison types are not compatible');
end


end

