import numpy as np
import ctypes

def soft_threshold(z, lambdaa):
    """
    Soft-thresholding operator:
    S_lambda(z) = sign(z) * max(|z| - lambda, 0)
    """
    return np.sign(z) * np.maximum(np.abs(z) - lambdaa, 0)


def ista(A, y, lambdaa=0.1, iters=100):
    """
    Floating-point ISTA implementation:
    x_{k+1} = S_lambda(x_k - alpha * A^T(Ax_k - y))
    """

    col = A.shape[1]
    x = np.zeros(col)

    # Step size = 1 / (largest singular value of A)^2
    L = np.linalg.norm(A, 2)**2
    alpha = 1.0 / L

    for i in range(iters):
        grad = A.T @ (A @ x - y)
        x = soft_threshold(x - alpha * grad, lambdaa)

    return x


