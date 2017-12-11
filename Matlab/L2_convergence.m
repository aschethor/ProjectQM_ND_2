function [ L2 ] = L2_convergence( func, samples, bins, nsamples)

L2 = zeros(length(nsamples),1);
mid_points = (bins(1:end-1)+bins(2:end))/2;
for i=1:length(nsamples)
    L2(i) = sqrt(sum((histcounts(samples(1:nsamples(i)),bins)/nsamples(i)-func(mid_points)).^2));
end

end