clear all
clc

% constants
H_BAR = 1;
K_B = 1;
T = 0.1;
BETA = 1/K_B/T;
M = 1;

% TODO: plot exact results

%% histogram - classical product interaction
figure(1)
clf
set(gcf,'color','w');
dx = 0.02;
x = -3:dx:3;
subplot(1,2,1)
data = csvread('data/product_interaction_cl.csv');
histogram(data(:,1), x,'LineStyle','none')
hold on
histogram(data(:,2), x,'LineStyle','none')
title('classical product interaction')
subplot(1,2,2)
data_naive = csvread('data/product_interaction_cl_adv_naive.csv');
histogram(data_naive(:,1), x,'LineStyle','none')
hold on
histogram(data_naive(:,2), x,'LineStyle','none')
title('... advanced naive')

%% histogram - quantum product interaction
figure(2)
clf
set(gcf,'color','w');
dx = 0.02;
x = -3:dx:3;
subplot(1,2,1)
data_qm = csvread('data/product_interaction_qm.csv');
histogram(data_qm(:,1), x,'LineStyle','none')
hold on
histogram(data_qm(:,2), x,'LineStyle','none')
title('quantum product interaction')
subplot(1,2,2)
data_qm_adv_naive = csvread('data/product_interaction_qm_adv_naive.csv');
histogram(data_qm_adv_naive(:,1), x,'LineStyle','none')
hold on
histogram(data_qm_adv_naive(:,2), x,'LineStyle','none')
title('... advanced naive')

%% plot 2d for correlation

figure(3)
clf
set(gcf,'color','w');
%subplot(1,2,1)
dx = 0.1;
% surf(histcounts2(data_qm(:,1),data_qm(:,2),-1.5:dx:1.5,-1.5:dx:1.5));
hist_grid = -1.5:dx:1.5;
grid = 0.5*(hist_grid(1:end-1)+hist_grid(2:end));
[xx, yy] = meshgrid(grid, grid);
surf(xx,yy,histcounts2(data_qm(:,2),data_qm(:,1),hist_grid,hist_grid)/length(data_qm)/dx/dx);%,'LineStyle','none');
xlabel('x_1')
ylabel('x_2')
colorbar
view(2)
title('product interaction - quantum')
fprintf('quantum corr: %f\n',corr(data_qm(:,1),data_qm(:,2)))

% subplot(1,2,2)
% surf(xx,yy,histcounts2(data(:,2),data(:,1),hist_grid,hist_grid)/length(data)/dx/dx);%,'LineStyle','none');
% xlabel('x_1')
% ylabel('x_2')
% colorbar
% view(2)
% title('product interaction - classical')
% fprintf('classical corr: %f\n',corr(data(:,1),data(:,2)))
% TODO: make 2d plot
% CECAM visp paper: 2 morse potetial compare
