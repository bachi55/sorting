require (ggplot2)

## compile filenames
scenarios <- c("sorted", "inv_sorted", "permuted", "repeated_elements")
# scenarios <- c("");
for (sce in scenarios) {

#   algorithms <- c("insertionSort", "quicksort", "mergesort", "insertionSort2", "quicksort2", "std::sort", "quicksort3", "quicksort4")
#   algorithms <- c("quicksort", "quicksort2", "quicksort3", "quicksort4")
  algorithms <- c("qsortVec", "quicksort2Vec", "quicksort3Vec", "quicksort6Vec")
#   algorithms <- c("default_random_engine", "minstd_rand", "minstd_rand0", "mt19937", "ranlux24")
#   algorithms <- c("default_random_engine", "minstd_rand", "minstd_rand0", "mt19937")
#   algorithms <- c("default_random_engine", "mt19937", "std::rand")
  filenames <- paste ("~/Documents/algorithm-exercises/sort/measurements/"
      , paste (algorithms)
      , sep=""
  )
  tmpStr <- paste (sce, "-time", sep="")
#   tmpStr <- paste (sce, "time", sep="")
  filenames.Times <- paste (filenames, tmpStr, sep="-")
#   tmpStr <- paste (sce, "-cycles", sep="")
#   tmpStr <- paste (sce, "cycles", sep="")
#   filenames.Cycles <- paste (filenames, tmpStr, sep="-")

  nAlgorithms <- length (algorithms)

  algorithmsNames <- algorithms
  algorithmsNames <- c("std::sort", "small inp. & rand. Pivot", "naive", "+ fat partition")

  ## extract data to plot (times)
  x.space <- 1:3000
#   x.space <- 1:10000
  nMeasurements <- max (x.space) - min (x.space) + 1

  mean <- vector()
  max <- vector()
  min <- vector()

  for (file in filenames.Times) {
    print (file)
    tmp <- read.table (file, header=F, comment.char="", skip=1) 
#     mean <- c(mean, c(tmp[, 5], rep (0, nMeasurements - nrow (tmp))))
#     min <- c(min, c(tmp[, 3], rep (0, nMeasurements - nrow (tmp))))
#     max <- c(max, c(tmp[, 4], rep (0, nMeasurements - nrow (tmp))))
    mean <- c(mean, c(tmp[x.space, 5]))
    min <- c(min, c(tmp[x.space, 3]))
    max <- c(max, c(tmp[x.space, 4]))
  }
  cbPalette <- c("#000000", "#E69F00", "#56B4E9", "#009E73", "#F0E442", "#0072B2", "#D55E00", "#CC79A7")

  df <- data.frame (cbind (rep(x.space, nAlgorithms), min, max, mean))
  df[, 5] <- gl (nAlgorithms, nMeasurements, nAlgorithms * nMeasurements, labels=algorithmsNames)
  colnames (df) <- c("n", "min", "max", "mean", "algorithm")

  ggplot (df, aes (x=n, y=mean)) +
#     ggtitle (sce) +	
    ggtitle (paste ("Quicksort (", sce, ")", sep="")) + 
    ylim(min (min), max (max)) + xlab ("n") + ylab ("times (us)") +
    geom_line (aes (group=algorithm, color=algorithm), alpha=0.75, size=0.3) +
    geom_ribbon (aes (ymin=min, ymax=max, color=algorithm, fill=algorithm), alpha=0.25, size=0.3) +
    scale_color_manual(values=cbPalette) + 
    scale_fill_manual(values=cbPalette)

  ggsave (paste ("~/Documents/algorithm-exercises/sort/measurements/plot-time-", sce, ".pdf", sep=""), width=8, height=4)  
    
  # dev.off()  

  ## extract data to plot (cycles)
#   mean <- vector()
#   max <- vector()
#   min <- vector()
# 
#   for (file in filenames.Cycles) {
#     tmp <- read.table (file, header=F, comment.char="", skip=1) 
#     mean <- c(mean, c(tmp[, 5], rep (0, nMeasurements - nrow (tmp))))
#     min <- c(min, c(tmp[, 3], rep (0, nMeasurements - nrow (tmp))))
#     max <- c(max, c(tmp[, 4], rep (0, nMeasurements - nrow (tmp))))
#   }
#   cbPalette <- c("#000000", "#E69F00", "#56B4E9", "#009E73", "#F0E442", "#0072B2", "#D55E00", "#CC79A7")
# 
#   df <- data.frame (cbind (rep(x.space, nAlgorithms), min, max, mean))
#   df[, 5] <- gl (nAlgorithms, nMeasurements, nAlgorithms * nMeasurements, labels=algorithmsNames)
#   colnames (df) <- c("n", "min", "max", "mean", "algorithm")
# 
#   ggplot (df, aes (x=n, y=mean)) +
#     ggtitle (sce) +
#     ylim(0, 4000000) + xlab ("n") + ylab ("cylces (#)") +
#     geom_line (aes (group=algorithm, color=algorithm)) +
# #     geom_ribbon (aes (ymin=min, ymax=max, color=algorithm, fill=algorithm), alpha=0.5) +
#     scale_color_manual(values=cbPalette) + 
# #     scale_fill_manual(values=cbPalette)  
#     
#   ggsave (paste ("~/Documents/algorithm-exercises/sort/measurements/plot-cycles-", sce, ".pdf", sep=""), width=8, height=4)    
  
}