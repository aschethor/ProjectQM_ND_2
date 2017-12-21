clear all

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
dx = 0.02;
x = -3:dx:3;
subplot(1,2,1)
data = csvread('data/product_interaction_cl.csv');
histogram(data(:,1), x,'LineStyle','none')
hold on
histogram(data(:,2), x,'LineStyle','none')
title('classical product interaction')
subplot(1,2,2)
data = csvread('data/product_interaction_cl_adv_naive.csv');
histogram(data(:,1), x,'LineStyle','none')
hold on
histogram(data(:,2), x,'LineStyle','none')
title('... advanced naive')

%% histogram - quantum product interaction
figure(2)
clf
dx = 0.02;
x = -3:dx:3;
subplot(1,2,1)
data_qm = csvread('data/product_interaction_qm.csv');
histogram(data_qm(:,1), x,'LineStyle','none')
hold on
histogram(data_qm(:,2), x,'LineStyle','none')
title('quantum product interaction')
subplot(1,2,2)
data_qm = csvread('data/product_interaction_qm_adv_naive.csv');
histogram(data_qm(:,1), x,'LineStyle','none')
hold on
histogram(data_qm(:,2), x,'LineStyle','none')
title('... advanced naive')

% TODO: make 2d plot
% CECAM visp paper: 2 morse potetial compare
