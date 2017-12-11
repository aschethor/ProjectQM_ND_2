clear all

figure(1)
clf
data_cl = csvread('data/morse_3d_cl.csv');
scatter3(data_cl(1:100000,1),data_cl(1:100000,2),data_cl(1:100000,3),'b+')
hold on
scatter3([-1 1],[0 0],[0 0],'ro')
title('classical density cloud')

figure(2)
clf
data_qm = csvread('data/morse_3d_qm.csv');
scatter3(data_qm(1:100000,1),data_qm(1:100000,2),data_qm(1:100000,3),'b+')
hold on
scatter3([-1 1],[0 0],[0 0],'ro')
title('quantum density cloud')