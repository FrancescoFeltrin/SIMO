% It takes the data flow from the arduino and chopps it up in indidual 
% csv files (test by test)

targetFile = 'test2.txt'; % with path
outputFolder = 'SSdata/';
prefixName = 'SS';
bigfileID = fopen(targetFile,'r');

%Scan the file for a specific string
 Str   = strsplit(fileread(targetFile), '\n');
 Key   = ' Command: ';
 match = strncmp(Str, Key, length(Key));
 
 % Cut between the 'match' indexes
 j=1;
 lineIdx(1)= 0;
 for i = 1:size(match,2)
     if match(i)==1
         lineIdx(j) = i;
         j = j+1;
     end
 end
 lineIdx(j)= size(match,2); % add the last line
 
%Copy content in another file
for idx = 1:size(lineIdx,2)-1
    name = strcat(outputFolder,prefixName,num2str(idx),'.txt');
    newFileID = fopen(name,'w');
    for line = lineIdx(idx):lineIdx(idx+1)-2
        csvFormat   = strsplit(strcat(Str{line}) ); %Read the line and adds the commas 
        towrite = csvFormat{2};
        for l=3:size(csvFormat,2)
            towrite = strcat(towrite,' , ',csvFormat{l});
        end
        towrite = strcat(towrite,' , \n'); 
        fprintf(newFileID,towrite); %line by line
    end
    fclose(newFileID);
end