function [ relTimeDS ] = resetTime( DataSet )
%RESETTIME All times are referenced to the first datapoint (time is assumed
%to be the first column.
t0 = DataSet(1,1);
for i = 1:size(DataSet,1)
    if DataSet(i,1)>=t0
        DataSet(i,1) = (DataSet(i,1)-t0)/1000;
    else
        break
    end
end
relTimeDS = DataSet(1:i,:);

