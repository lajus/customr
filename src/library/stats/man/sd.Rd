% File src/library/stats/man/sd.Rd
% Part of the R package, http://www.R-project.org
% Copyright 1995-2012 R Core Team
% Distributed under GPL 2 or later

\name{sd}
\alias{sd}
\title{Standard Deviation}
\description{
  This function computes the standard deviation of the values in
  \code{x}.
  If \code{na.rm} is \code{TRUE} then missing values are removed before
  computation proceeds.
}
\usage{
sd(x, na.rm = FALSE)
}
\arguments{
  \item{x}{a numeric vector or an \R object which is coercible to one
    by \code{as.vector(x, "numeric")}.}
  \item{na.rm}{logical.  Should missing values be removed?}
}
\details{
  Like \code{\link{var}} this uses denominator \eqn{n - 1}.

  The standard deviation of a zero-length vector (after removal of
  \code{NA}s if \code{na.rm = TRUE}) is not defined and gives an error.
  The standard deviation of a length-one vector is \code{NA}.

  Prior to \R 2.14.0, \code{sd(dfrm)} worked directly for a
  \link{data.frame} \code{dfrm}.  This is now deprecated and you are
  expected to use \code{\link{sapply}(dfrm, sd)}.
}
\seealso{
  \code{\link{var}} for its square, and \code{\link{mad}}, the most
  robust alternative.
}
\examples{
sd(1:2) ^ 2
}
\keyword{univar}
