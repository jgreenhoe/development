#============================================================================
# R script file
# setwd("c:/jj/stats/");
# source("mmp.R");
#============================================================================
#---------------------------------------
# install packages (perform once)
#---------------------------------------
#install.packages("bspec");
#install.packages("ramify");
#---------------------------------------
# load add-on packages
#---------------------------------------
 rm(list=objects());
 require(stats);
 require(graphics);
 require(datasets);
 require(ramify);
 require(bspec);     # https://www.rdocumentation.org/packages/bspec/
#---------------------------------------
# load data
#---------------------------------------
 x    = read.csv("mmp.csv", comment.char = "#");
 bins=seq(from=0.5,to=12.5,by=1)
 Open = x$Open;
 Close = x$Close;
 Date = x$Date;
 N = length(Close)
 Time = c(0:(N-1))
 a = 0;
 Approx = 20;
 #plot( bins,Red, col="red", type='o' );
 #lines( bins,Blue, col="blue", type='o' );
 X = fft(Close)
 #hist(Close)
Approx = 0
 for(i in c(1:500)){
   a = (1/N)*(abs(X[i])*cos(2*pi*(i-1)*Time/N))
#   a = sqrt((Re(X[i])*cos(2*pi*(i-1)*Time/N)/N)^2 + (Im(X[i])*sin(2*pi*(i-1)*Time/N)/N)^2)
  Approx = Approx + a;
 }
 plot(Close, type = 'l', col = 'blue')
 lines(Approx, type = 'l', col = 'red')
#---------------------------------------
# plot data
#---------------------------------------
# mydata(x);
# estT = mypsd(x, numSegments=3, dataDump=FALSE);
# print(sprintf("estimated period = %.16f years", estT));


#mypdf(x);
#pdfr(x);
#---------------------------------------
# process data
#---------------------------------------
