% Temperature compensation for CO2 sensor

close all;
clear all;
clc;
% Code starts here
temp1 = [8, 11.9, 16, 20.1, 25.7, 29.2, 33.6, 37.8, 42, 46.1];
errA1 = [-2.5, 4.09, 9.98, 16.48, 23.02, 21.48, 14.52, 6.81, 7.88, 10.31];
errB1 = [-5.63, -1.08, 4.16, 10.67, 20.98, 23.59, 22.77, 21.25, 25.34, 37.79];
temp2 = [8, 12, 15.1, 20.1, 24.6, 29.3, 33.61, 37.8, 42, 46];
errA2 = [0, 5.63, 6.73, 9.47, 9.78, 6.67, 8.9, 10.77, 11.96, 16.33];
errB2 = [-1.52, 1.39, 3.5, 8.37, 11.52, 12.3, 16.67, 23.59, 29.77, 37.91];
testo1 = [799, 832, 842, 825, 834, 903, 1054, 1440, 1484, 1503];
sensA1 = [779, 860, 926, 961, 1026, 1097, 1207, 1538, 1601, 1658];
sensB1 = [754, 823, 877, 913, 1009, 1116, 1294, 1746, 1860, 2071];

testo2 = [788, 888, 936, 971, 1012, 1125, 1135, 1133, 1137, 1102];
sensA2 = [788, 938, 999, 1063, 1111, 1200, 1236, 1255, 1273, 1282];
sensB2 = [776, 901, 971, 1060, 1140, 1273, 1341, 1429, 1516, 1588];

err = (errA1+errA2+errB1+errB2)/4;
temp = (temp1+temp2)/2;

err1 =err(1:5);
err2= err(6:8);
err3= err(9:10);
temp1 =temp(1:5);
temp2= temp(6:8);
temp3= temp(9:10);
coef1 =polyfit(temp1,err1,1);
coef2 =polyfit(temp2,err2,1);
coef3 =polyfit(temp3,err3,1);

tempGiven=42
reading =1860

if tempGiven<25.15
    errFrml = coef1(1)*tempGiven+coef1(2)
%     disp(1);
elseif tempGiven<37.8
    errFrml = coef2(1)*tempGiven+coef2(2)
%     disp(2);
else
    errFrml = coef3(1)*tempGiven+coef3(2)
%     disp(3);
end

required =reading*100/(errFrml+100)


% Three section upto 25.15, 25.15 to 37.8 and more than 37.8



% figure;
% scatter(temp,err,'ok','MarkerFaceColor','r');
% 
% len =length(errA1);
% % delA1 =zeros(len);
% 
% for i=1:len-1
%     delA1(i)=(errA1(i+1)-errA1(i))/(temp1(i+1)-temp1(i));
% end
% 
% newError = (temp1(3)-temp1(2))*delA1(1)+errA1(2)
% 
% figure;
% hold on;
% scatter(temp1,errA1,'ok','MarkerFaceColor','r');
% scatter(temp1,errB1,'b');
% scatter(temp2,errA2,'y');
% scatter(temp2,errB2,'g');
% 
% a1= polyfit(temp1,errA1,1);
% b1= polyfit(temp1,errB1,1);
% a2= polyfit(temp2,errA2,1);
% b2= polyfit(temp2,errB2,1);
% 
% figure;
% 
% plot(temp1,abs(testo1-sensA1));
% hold on;
% % plot(temp1,sensA1,'r');
% plot(temp1,abs(testo1-sensB1),'y');
% grid on;
% hold off;
% 
% figure;
% % grid on;
% plot(temp2,abs(testo2-sensA2));
% hold on;
% % plot(temp2,sensA2,'r');
% plot(temp2,abs(sensB2-testo2),'y');
% grid on;