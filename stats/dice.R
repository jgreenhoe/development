#============================================================================
# Daniel J. Greenhoe
# R script file
# setwd("c:/jj/stats/");
# source("dice.R");
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
 x    = read.csv("dice_fair.csv", comment.char = "#");
 bins=seq(from=0.5,to=12.5,by=1)
 Red = x$Red;
 Blue = x$Blue;
 All = c(Red,Blue)
 #plot( bins,Red, col="red", type='o' );
 #lines( bins,Blue, col="blue", type='o' );
 hist(All,breaks=bins)
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
