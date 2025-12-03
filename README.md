# ISTA-Accelerator-Compressed-Sensing


This project implements the **Iterative Soft Thresholding Algorithm (ISTA)** for **compressed sensing reconstruction** in both software (Python) and hardware (HLS).  
This repository contains the full software reference, hardware accelerator, test vectors, evaluation results, and final report materials.

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

The goal of this project is to reconstruct **x** from **y** using ISTA, and then accelerate the computation using hardware-implemented fixed-point arithmetic via **Vitis HLS**.

---

```
ISTA-Accelerator-Compressed-Sensing/
│
├── python/
│   ├── generate_data.py
│   ├── ista_float.py
│   ├── ista_fixed.py
│   └── utils.py
│
├── hls/
│   ├── ista_top.cpp
│   ├── tb_ista.cpp
│   ├── directives.tcl
│   └── reports/
│
├── data/
│   ├── x_true.npy
│   ├── A.npy
│   ├── y.npy
│   ├── A_flat.txt
│   └── y_in.txt
│
├── results/
│   ├── plots/
│   └── tables/
│
├── report/
│   ├── final_report.pdf
│   └── figures/
│
└── README.md
