rng = 1:90000;

data = load('0total_energy.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))
hold all;

data = load('1total_energy.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

data = load('10total_energy.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

data = load('100total_energy.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

data = load('1000total_energy.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

hold off;
legend('seed 0','seed 1', 'seed 10', 'seed 100', 'seed 1000');
title('Average total energy over time.');
ylabel('Performance Statistic');
xlabel('Time (seconds)');

print energyPlot.svg

data = load('0latency.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))
hold all;

data = load('1latency.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

data = load('10latency.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

data = load('100latency.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

data = load('1000latency.csv');
plot(data(rng,1),cumsum(data(rng,2))./((rng)'))

hold off;
legend('seed 0','seed 1', 'seed 10', 'seed 100', 'seed 1000');
title('Average latency over time.');
ylabel('Performance Statistic');
xlabel('Time (seconds)');

print latencyPlot.svg
