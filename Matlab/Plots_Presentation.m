clear all

% constants
H_BAR = 1;
K_B = 1;
T = [0.1, 1];
T_str = ['0.100000';'1.000000'];
N_BEAD = [1,2,4,8,16,32,64];
BETA = 1/K_B./T;
M = 1;

% space discretization
dx = 0.1;% 0.02
x = -5:dx:5;
x_mid = (x(1:end-1)+x(2:end))/2;

%% show harmonic potential

% potential
w = 1;
V = @(x)w*w/2*x.^2;

figure(1)
clf
set(gcf,'color','w');
plot(x,V(x))
xlabel('x')
ylabel('V(x)')
title('harmonic oscillator')

%% plot different density distributions

figure(2)
clf
set(gcf,'color','w');
for i = 1:2
    subplot(1,2,i)
    exact_clasical_density = exp(-BETA(i)*V(x));
    exact_clasical_density = exact_clasical_density / sum(exact_clasical_density);
    exact_quantum_density = exp(-M*w*2/(2*H_BAR*sinh(BETA(i)*H_BAR*w))*(cosh(BETA(i)*H_BAR*w)-1)*x.*x);
    exact_quantum_density = exact_quantum_density / sum(exact_quantum_density);
    plot(x,exact_clasical_density/dx,'Color',[0.85 0.85 0.85],'LineWidth',3)
    hold on
    plot(x,exact_quantum_density/dx,'Color',[0.65 0.65 0.65],'LineWidth',3)
    for n = 1:7
        filename = strcat('data/presentation/harmonic_oscillator_qm_T_',T_str(i,:),'_N_',string(N_BEAD(n)),'.csv');
        data = csvread(filename);
        plot(x_mid,histcounts(data,x)/length(data)/dx)
    end
    title(strcat('Temperature = ',T_str(i,:)))
    xlabel('X')
    ylabel('\rho')
    legend('exact classical','exact quantum','1 bead','2 beads','4 beads','8 beads','16 beads','32 beads','64 beads')
end

%% show free energies

figure(3)
clf
set(gcf,'color','w');
for i = 1:2
    subplot(1,2,i)
    exact_clasical_density = exp(-BETA(i)*V(x));
    exact_clasical_density = exact_clasical_density / sum(exact_clasical_density);
    exact_quantum_density = exp(-M*w*2/(2*H_BAR*sinh(BETA(i)*H_BAR*w))*(cosh(BETA(i)*H_BAR*w)-1)*x.*x);
    exact_quantum_density = exact_quantum_density / sum(exact_quantum_density);
    plot(x,-K_B*T(i)*log(exact_clasical_density),'Color',[0.85 0.85 0.85],'LineWidth',3)
    hold on
    plot(x,-K_B*T(i)*log(exact_quantum_density),'Color',[0.65 0.65 0.65],'LineWidth',3)
    for n = 1:7
        filename = strcat('data/presentation/harmonic_oscillator_qm_T_',T_str(i,:),'_N_',string(N_BEAD(n)),'.csv');
        data = csvread(filename);
        plot(x_mid,-K_B*T(i)*log(histcounts(data,x)/length(data)))
    end
    title(strcat('Temperature = ',T_str(i,:)))
    xlabel('X')
    ylabel('F')
    legend('exact classical','exact quantum','1 bead','2 beads','4 beads','8 beads','16 beads','32 beads','64 beads')
end
%% show double well

% potential
w = 1;
V = @(x)w*w*(x-1).^2.*(x+1).^2;

figure(4)
clf
set(gcf,'color','w');
plot(x,V(x))
xlabel('x')
ylabel('V(x)')
title('double well potential')

%% plot different density distributions

figure(5)
clf
set(gcf,'color','w');
for i = 1:2
    subplot(1,2,i)
    exact_clasical_density = exp(-BETA(i)*V(x));
    exact_clasical_density = exact_clasical_density / sum(exact_clasical_density);
    plot(x,exact_clasical_density/dx,'Color',[0.85 0.85 0.85],'LineWidth',3)
    hold on
    for n = 1:7
        filename = strcat('data/presentation/double_well_qm_T_',T_str(i,:),'_N_',string(N_BEAD(n)),'.csv');
        data = csvread(filename);
        plot(x_mid,histcounts(data,x)/length(data)/dx)
    end
    title(strcat('Temperature = ',T_str(i,:)))
    xlabel('X')
    ylabel('\rho')
    legend('exact classical','1 bead','2 beads','4 beads','8 beads','16 beads','32 beads','64 beads')
end

%% free energy

figure(6)
clf
set(gcf,'color','w');
for i = 1:2
    subplot(1,2,i)
    exact_clasical_density = exp(-BETA(i)*V(x));
    exact_clasical_density = exact_clasical_density / sum(exact_clasical_density);
    plot(x,-K_B*T(i)*log(exact_clasical_density),'Color',[0.85 0.85 0.85],'LineWidth',3)
    hold on
    for n = 1:7
        filename = strcat('data/presentation/double_well_qm_T_',T_str(i,:),'_N_',string(N_BEAD(n)),'.csv');
        data = csvread(filename);
        plot(x_mid,-K_B*T(i)*log(histcounts(data,x)/length(data)))
    end
    title(strcat('Temperature = ',T_str(i,:)))
    xlabel('X')
    ylabel('F')
    legend('exact classical','1 bead','2 beads','4 beads','8 beads','16 beads','32 beads','64 beads')
end
