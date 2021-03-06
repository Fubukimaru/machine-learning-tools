% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/wrapper.R
\name{pass_through.cnn}
\alias{pass_through.cnn}
\title{Pass data forth and back through a Convolutional Network or MultiLayer
Perceptron Function}
\usage{
pass_through.cnn(cnn, newdata, rand_seed = as.integer(floor(runif(1) * 1000)))
}
\arguments{
\item{cnn}{A trained CNN or MLP.}

\item{newdata}{A matrix/array with data, one example per row.}
}
\description{
This function predicts and reconstructs a dataset using a trained CNN (or
MLP). Admits as parameters the testing dataset, and a trained CNN/MLP.
Returns a list with the predicted outputs matrix and the reconstructed matrix
or array.
}
\examples{
## The MNIST example with MLPs
data(mnist)

train <- mnist$train;
training_x <- train$x / 255;
training_y <- binarization(train$y);

test <- mnist$test;
testing_x <- test$x / 255;
testing_y <- binarization(test$y);

dataset <- training_x[1:1000,, drop=FALSE];
targets <- training_y[1:1000,, drop=FALSE];

newdata <- testing_x[1:1000,, drop=FALSE];

layers <- list(
   c('type' = "LINE", 'n_visible' = 784, 'n_hidden' = 10, 'scale' = 0.1)
);
eval <- c('type' = "RBML", 'n_visible' = 10, 'n_hidden' = 5, 'scale' = 0.1, 'n_gibbs' = 4);

mnist_dbn <- train.cnn(dataset, targets, layers, evaluator = eval, batch_size = 10,
                       training_epochs = 3, learning_rate = 1e-3, rand_seed = 1234);

rebuild <- pass_through.cnn(mnist_dbn, newdata);
}
\keyword{CNN}
\keyword{MLP}

