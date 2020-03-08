#####################################################################
# This function takes error codes from the growthloop and returns a 
# dataframe with the meaning of the error.  It also includes a 
# listing of the parameter sets containing the error and an option
# for running a function to remove the erroneous output from the
# data that was returned from the function
#
# binerror - a vector of errors in integer form
# nsets - the number of parameter sets processed
#
# Created the week of May 20th 2013
#####################################################################

#####################################################################
#' ACGCA error function
#'
#' This function reports error codes.
#' 
#' @param binerror a vector of errors in integer form
#' @param nsets the number of parameter sets processed
#####################################################################

errorcode <- function(binerror, nsets){

	len <- length(binerror)/nsets
	sel <- binerror > 0
	index <- which(binerror > 0)
	errors <- binerror[sel]

	# this is a list of errors from the C code
	error.list <- c(
		"Error_in_growthloop_at_line_311", #1, 0
		"Error in growthloop: r or h is negative or nan", #2, 1
		"Error in excessgrowingon at line 87", #4, 2
		"Error in excessgrowingon at line 102", #8, 3
		"Error in excessgrowingon at line 120", #16, 4
		"Error in excessgrowingon at line 161", #32, 5
		"Error in excessgrowingon at line 195", #64, 6
		"Error in excessgrowingon at line 214", #128, 7
		"Error in excessgrowingon at line 232", #256, 8
		"Error in excessgrowingon at line 244", #512, 9
		"Problem w/ allocation fraction in excessgrowingon or putonallometry 309 excessgrowingon", #1024, 10
		"Error in excessgrowingon at line 302", #2048, 11
		"Problem in excessgrowingoff or on translocation at line 336 excessgrowingon", #4096, 12
		"Error in excessgrowingon at line 354", #8192, 13
		"Error in excessgrowingoff line 419", #16384, 14
		"Error in excessgrowingoff line 429", #32768, 15
		"Error in excessgrowingoff line 467", #65536, 16
		"Error in excessgrowingoff or on translocation", #131072, 17
		"Error in excessgrowingoff line 495", #262144, 18
		"Error in excessgrowingoff line 516" #524288, 19
	)
	x <- as.numeric(intToBits(errors))
	# Create an error matrix
	errormatrix <- matrix(x, ncol=length(errors), nrow=(length(intToBits(errors))/length(errors)))
	# Create row names
	row.names(errormatrix) <- c(1:length(error.list), numeric(dim(errormatrix)[1]-length(error.list)))

	sets <- unique(floor(index/len))
	
	# put all the information into a list
	errorout <- list("error.list"=error.list, "errormatrix"=errormatrix, "sets"=sets)
	# return the list
	return(errorout)
}
