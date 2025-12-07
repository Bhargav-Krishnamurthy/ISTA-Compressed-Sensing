import numpy as np
from scipy.io.wavfile import write
import matplotlib.pyplot as plt


f1 = 440
f2 = 500
duration = 2
Fs = 10000
N  = Fs * duration
t  = np.linspace(0, duration, N, endpoint=False)


signal = 0.5 * np.sin(2 * np.pi * f1 * t) + 0.8 * np.sin(2 * np.pi * f2 * t)

# Normalising based on 16 bit range for generating the audio signal
audio = np.int16(signal * 32767/ np.max(np.abs(signal)))


write("sample_audio.wav", 10000, audio)


from scipy.fft import fft, fftfreq, ifft

N = len(signal)
X = fft(signal)
freqs = fftfreq(N, 1/10000)

plt.plot(freqs[:N//2], np.abs(X[:N//2]))
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("Correct Frequency Spectrum")
plt.grid()
plt.savefig("./frequencies.png")

m = 4000

A = np.random.randn(m, N)
y = A @ signal




lambdaa=0.1
iters=100
# Step size = 1 / (largest singular value of A)^2
L = np.linalg.norm(A, 2)**2
alpha = 1.0 / L
X_est = np.zeros(N, dtype=complex)


for i in range(iters):

    residual = A @ np.real(ifft(X_est)) - y

   
    grad = fft(A.T @ residual)

  
    X_est = np.sign(X_est - alpha * grad) * np.maximum(np.abs(X_est - alpha * grad) - lambdaa, 0)


plt.figure()
plt.plot(freqs[:N//2], np.abs(X_est[:N//2]), label="Recovered FFT", linestyle='dashed')
plt.xlabel("Hz")
plt.ylabel("Magnitude")
plt.legend()
plt.grid()

for i in range(N//2):
    if(np.abs(X[i]) > 1):
        print(freqs[i])
        print()

plt.show()