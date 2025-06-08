import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

sns.set()
sns.set_context("paper")

def probabilidad(datos):
    try:
        return np.mean(datos[:,0])
    except:
        return np.nan

def tamanomax(datos):
    try:
        datos = datos[datos[:, 1] > 0, 1]
        return np.mean(datos)
    except:
        return np.nan
    
def sumatoria(datos, columna):
    try:
        return np.sum(datos[:, columna])
    except:
        return np.nan
    
def main():
    L = np.array([32, 64, 128, 256, 512])
    P = np.array([0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 
         0.55, 0.56, 0.57, 0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 
         0.65, 0.7, 0.73, 0.76, 0.79, 0.82, 0.85, 0.88, 0.91, 0.94, 0.97])
    
    OPT = ["O0", "O1", "O2", "O3", "Ofast"]

    fig1, ax1 = plt.subplots(figsize=(10,5))
    fig2, ax2 = plt.subplots(figsize=(10,5))
    fig3, ax3 = plt.subplots(figsize=(10,5))

    for j, l in enumerate(L):
        prob = np.zeros(len(P))
        tam = np.zeros(len(P))
        for i, p in enumerate(P):
            datos = np.loadtxt(f"./resultados/datos_{l}_{p}_O3.txt")
            prob[i] = probabilidad(datos)
            tam[i] = tamanomax(datos)
        ax1.plot(P, prob, label=f"L = {l}")
        ax2.plot(P, tam / (l * l), label=f"L = {l}")

    for o in OPT:
        WT = np.zeros(len(L))
        CT = np.zeros(len(L))

        for j, l in enumerate(L):
            wt = 0
            ct = 0
            for p in P:
                datos = np.loadtxt(f"./resultados/datos_{l}_{p}_{o}.txt")
                wt += sumatoria(datos, 2)
                ct += sumatoria(datos, 3)
            WT[j] = wt
            CT[j] = ct
        ax3.plot(L, WT, label=f"Wall time - {o}")
        ax3.plot(L, CT, label=f"CPU time - {o}")



    ax1.set_xlabel(r"Probabilidad de ocupacion $p$")
    ax1.set_ylabel(r"Probabilidad de cluster percolante $P(p,L)$")
    ax1.set_title("Probabilidad de cluster percolante")
    ax1.legend()
    ax1.grid(True)
    fig1.tight_layout()
    fig1.savefig("ProbabilidadCluster.pdf")

    ax2.set_xlabel(r"Probabilidad de ocupacion $p$")
    ax2.set_ylabel(r"Tamano promedio cluster percolante mas grande $s(p,L)$")
    ax2.set_title("Tamano promedio cluster percolante mas grande" )
    ax2.legend()
    ax2.grid(True)
    fig2.tight_layout()
    fig2.savefig("TamanoCluster.pdf")

    ax3.set_xlabel(r"Tamano del lado de la malla")
    ax3.set_ylabel(r"Tiempo")
    ax3.set_title("Tiempo de computo en funcion del tamano del sistema" )
    ax3.set_yscale("log")
    ax3.legend()
    ax3.grid(True)
    fig3.tight_layout()
    fig3.savefig("Tiempos.pdf")

    plt.close("all")
    
main()

        

