#' ACGCA model function
#'
#' This function provides an easy interface for running the ACGCA model.
#'
#' @param sparms A vector containing the parameters for the simulationl.
#' @param gparms A vector containing values that control simulation behavior.
#' @param r0 The starting radius. Defaults to 0.05.
#' @keywords IBM
#' @export
# @examples
#' @useDynLib ACGCA
#' @importFrom Rcpp sourceCpp

ACGCA <- function(){
 
  output <- .C("Rgrowthloop")
  return(output)

} #end of growthloop function