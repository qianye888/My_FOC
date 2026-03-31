clear;
clc;
disp('本工程文件仅适用于FOC控制');
disp('若有任何问题请及时联系qianye');
% calin=[-9.96 -7.98 -5.98 -3.99 -1.994 0 1.995 3.992 5.99 7.98 9.97];
% calout=[-10 -8 -6 -4 -2 0 2 4 6 8 10];
% uiopen('D:\Matlab\QianXun_Prj\mdl\QIANXUN.sldd',1);
%load('E:\FOC\FOC_BLDC\mdl\R_100K.mat');
run('Y:\FOC\Git_FOC\FOC_BLDC\data\mat\x.m');
run('Y:\FOC\Git_FOC\FOC_BLDC\data\mat\y.m');

ts_IO612=0.01;