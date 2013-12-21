function [output left] = block_average(input, len)
% [output left] = block_average(input, len)
% Computes the block average of input, taking blocks of width len, starting
% with the beginning. left is the width of the final block, if
% length(input) is not divisible by len. Otherwise, left is zero.

if(mod(len,1) ~= 0)
    error('len must be an integer');
end

   left = mod(length(input),len);
   output = zeros(1,floor(length(input)/len));
   if(left > 0)
      leftover = input(end-left+1:end);
      input = input(1:end-left);
      output = [output mean(leftover)];
   end
   
   starts = 1:len:length(input);
   for i = 1:length(starts)
       output(i) = mean(input(starts(i):(starts(i)+len-1)));
   end
   
end