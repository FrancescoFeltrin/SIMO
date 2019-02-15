% Post processing of RW data acuired during static /steady state tests.
% It reads all csv in 'SSdata' and uses them to provide:
% - Time Vs RPM 
% - Time Vs mAmp
% - Control input Vs terminal RPM
% - Terminal RPM Vs terminal mAmp

dataFolderName = 'SSdata';
CSVlist = dir(dataFolderName);
nTests = size(CSVlist,1)-2;
for test=1:nTests % The first 2 ar '.' and '..'
   path = strcat(dataFolderName,'/',CSVlist(test+2).name);
   DataIn = csvread(path,2,0); %Skip first 3 rows, as they are headers for humans
   % Do your stuff
   DataIn = resetTime(DataIn);
   
   subplot(1,2,1); 
   plot(DataIn(:,1)./1000,DataIn(:,2));
   hold on 
   grid on 
   xlabel('Time [s]'); ylabel('RPM');
   subplot(1,2,2); 
  
   plot(DataIn(:,1)./1000,DataIn(:,4));
   hold on 
   grid on 
   xlabel('Time [s]'); ylabel('mAmp');
   
   %-> Reformat time ->microseconds from first item 
    RPM_avg(test) = mean(DataIn(:,2));
    RPM_std(test) = std(DataIn(:,2));
    AMP_avg(test) = mean(DataIn(:,4));
    AMP_std(test) = std(DataIn(:,4)); 
end

figure 
errorbar(RPM_avg(:),AMP_avg(:),AMP_std(:),'o','LineWidth',2);
grid on 
xlabel('RPM [s]'); ylabel('mAmp');
