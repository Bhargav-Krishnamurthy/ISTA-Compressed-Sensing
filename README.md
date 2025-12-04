# ISTA-Compressed-Sensing


This project implements the **Iterative Soft Thresholding Algorithm (ISTA)** for **compressed sensing reconstruction** in Python.  
This repository contains the full software reference, test vectors, evaluation results, and final report materials.

---

## 📌 Project Overview

Compressed sensing allows recovery of a **sparse signal x** from a set of **compressed measurements y** obtained via:

```
y = A x
```

where  
- **x** = original sparse vector (unknown),  
- **A** = measurement/compression matrix,  
- **y** = compressed measurements.

The goal of this project is to reconstruct **x** from **y** using ISTA.

