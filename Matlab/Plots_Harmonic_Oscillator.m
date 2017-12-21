clear all

% constants
H_BAR = 1;
K_B = 1;
T = 0.1;
BETA = 1/K_B/T;
M = 1;

%% histogram - classical harmonic oscillator
figure(1)
clf
data = csvread('data/harmonic_oscillator_cl.csv');
n = length(data);
dx = 0.02;
x = -3:dx:3;
hist(data, x)
hold on
w = 1;
y = exp(-BETA*w*w/2*x.*x);
y = y/sum(y)*n;
plot(x,y,'r');
title('classical harmonic oscillator')

%% histograms - quantum harmonic oscillator (different approaches)
figure(2)
clf
subplot(1,3,1)
data_qm = csvread('data/harmonic_oscillator_qm.csv');
n = length(data_qm);
dx = 0.02;
x = -3:dx:3;
hist(data_qm, x)
hold on
w = 1;
V = @(x)w*x.^2;
y = exp(-M*w*2/(2*H_BAR*sinh(BETA*H_BAR*w))*(cosh(BETA*H_BAR*w)-1)*x.*x);
y = y/sum(y)*n;
plot(x,y,'r');
title('quantum harmonic oscillator - mode approach')
subplot(1,3,2)
data_adv_naive = csvread('data/harmonic_oscillator_qm_adv_naive.csv');
hist(data_adv_naive,x)
hold on
plot(x,y,'r')
title('... and advanced naive approach')
subplot(1,3,3)
data_naive = csvread('data/harmonic_oscillator_qm_naive.csv');
hist(data_naive,x)
hold on
plot(x,y,'r')
title('quantum harmonic oscillator - naive approach')

%% running averages - convergency of different approaches
figure(3)
clf
x = (1:length(data_qm))';
subplot(2,1,1)
plot(cumsum(data_qm)./x,'r')
hold on
plot(cumsum(data_naive)./x,'g')
plot(cumsum(data_adv_naive)./x,'b')
plot(0*x,'k')
legend('mode','naive','advanced naive','exact')
title('running average of <x>')

subplot(2,1,2)
plot(cumsum(data_qm.^2)./x,'r')
hold on
plot(cumsum(data_naive.^2)./x,'g')
plot(cumsum(data_adv_naive.^2)./x,'b')
plot(0*x+M*w/(2*H_BAR*sinh(BETA*H_BAR*w))*(cosh(BETA*H_BAR*w)-1),'k')
legend('mode','naive','advanced naive','exact')
title('running average of <x^2>')

%% convergence in L2 norm

w = 1;
V = @(x)w*x.^2;
V2 = @(x)exp(-M*w*2/(2*H_BAR*sinh(BETA*H_BAR*w))*(cosh(BETA*H_BAR*w)-1)*x.*x);
rho = @(x)V2(x)/sum(V2(x));
dx = 0.02;
x = -3:dx:3;

figure(4)
clf

data_optimal = normrnd(0,sqrt(M*w/(2*H_BAR*sinh(BETA*H_BAR*w))*(cosh(BETA*H_BAR*w)-1)),n,1);

nsamples = 0:10000:length(data_qm);
convergence_qm = L2_convergence(rho,data_qm,x,nsamples);
convergence_adv_naive = L2_convergence(rho,data_adv_naive,x,nsamples);
convergence_naive = L2_convergence(rho,data_naive,x,nsamples);
convergence_optimal = L2_convergence(rho,data_optimal,x,nsamples);
semilogy(nsamples,convergence_qm)
hold on
semilogy(nsamples,convergence_adv_naive)
semilogy(nsamples,convergence_naive)
semilogy(nsamples,convergence_optimal)
semilogy(nsamples,1./sqrt(nsamples),'--')
title('convergence of density distribution in L^2 norm')
legend('mode','adv naive','naive','optimal','1/sqrt(N)')
