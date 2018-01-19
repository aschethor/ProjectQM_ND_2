function [ L2 ] = L2_convergence_2D( func, samples, bins, nsamples)

grid = 0.5*(bins(1:end-1)+bins(2:end));
[xx, yy] = meshgrid(grid, grid);

L2 = zeros(length(nsamples),1);
for i=1:length(nsamples)
    fprintf("%i done out of %i\n",i,length(nsamples));
    L2(i) = sqrt(sum(sum((histcounts2(samples(1:nsamples(i),2),samples(1:nsamples(i),1),...
        bins,bins)/nsamples(i)-func(xx,yy)).^2)));
end

end