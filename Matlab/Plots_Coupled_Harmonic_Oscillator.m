clear all
clc

% constants
H_BAR = 1;
K_B = 1;
T = 0.1;
BETA = 1/K_B/T;
M = 1;

%% load data

data = csvread('data/coupled_harmonic_oscillator_k3_cl.csv');
data_naive = csvread('data/coupled_harmonic_oscillator_k3_cl_adv_naive.csv');
data_qm = csvread('data/coupled_harmonic_oscillator_k3_qm.csv');
data_qm_adv_naive = csvread('data/coupled_harmonic_oscillator_k3_qm_adv_naive.csv');

%% plot 2d for correlation

figure(1)
clf
set(gcf,'color','w');
subplot(1,2,1)
dx = 0.1;
hist_grid = -1.5:dx:1.5;
grid = 0.5*(hist_grid(1:end-1)+hist_grid(2:end));
[xx, yy] = meshgrid(grid, grid);
surf(xx,yy,histcounts2(data_qm(:,2),data_qm(:,1),hist_grid,hist_grid)/length(data_qm)/dx/dx);%,'LineStyle','none');
xlabel('x_1')
ylabel('x_2')
colorbar
view(2)
title('coupled oscillator - quantum numeric')
fprintf('quantum corr: %f\n',corr(data_qm(:,1),data_qm(:,2)))

subplot(1,2,2)
surf(xx,yy,histcounts2(data(:,2),data(:,1),hist_grid,hist_grid)/length(data)/dx/dx);%,'LineStyle','none');
xlabel('x_1')
ylabel('x_2')
colorbar
view(2)
title('coupled oscillator - classical numeric')
fprintf('classical corr: %f\n',corr(data(:,1),data(:,2)))
% CECAM visp paper: 2 morse potetial compare

%% analytic solution
xp = (xx+yy)/sqrt(2);
xm = (yy-xx)/sqrt(2);
wp = sqrt(1);
wm = sqrt(1+2*3);
y = exp(-M*wp*2/(2*H_BAR*sinh(BETA*H_BAR*wp))*(cosh(BETA*H_BAR*wp)-1)*xp.*xp);
y = y.*exp(-M*wm*2/(2*H_BAR*sinh(BETA*H_BAR*wm))*(cosh(BETA*H_BAR*wm)-1)*xm.*xm);
y = y/sum(sum(y));

figure(2)
clf
set(gcf,'color','w');
surf(xx,yy,y)
xlabel('x_1')
ylabel('x_2')
colorbar
view(2)
title('coupled oscillator - quantum analytic solution')

%% convergence
k=1;
kappa = 3;
wp = sqrt(k);
wm = sqrt(k+2*kappa);

normalize = @(x)x/sum(sum(x));
rho = @(xx,yy)normalize(exp(-M*wp*2/(2*H_BAR*sinh(BETA*H_BAR*wp))*(cosh(BETA*H_BAR*wp)-1)*(xx+yy)/sqrt(2).*(xx+yy)/sqrt(2)).*...
    exp(-M*wm*2/(2*H_BAR*sinh(BETA*H_BAR*wm))*(cosh(BETA*H_BAR*wm)-1).*(yy-xx)/sqrt(2).*(yy-xx)/sqrt(2)));

nsamples = 0:100000:length(data_qm);
convergence_qm = L2_convergence_2D(rho,data_qm,hist_grid,nsamples);
convergence_adv_naive = L2_convergence_2D(rho,data_qm_adv_naive,hist_grid,nsamples);

figure(3)
clf
set(gcf,'color','w');

semilogy(nsamples,convergence_qm)
hold on
semilogy(nsamples,convergence_adv_naive)
semilogy(nsamples,1./sqrt(nsamples),'--')
title('convergence of density distribution in L^2 norm')
legend('mode','adv naive','1/sqrt(N)')
