import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import sys

sns.set()
sns.set_context("paper")

def probabilidad(datos):
    try:
        return np.mean(datos[:,0]), np.std(datos[:,0])
    except:
        return np.nan, np.nan

def tamanomax(datos):
    try:
        datos = datos[datos[:, 1] > 0, 1]
        return np.mean(datos), np.std(datos)
    except:
        return np.nan, np.nan
    
def sumatoria(datos, columna):
    try:
        return np.sum(datos[:, columna])
    except:
        return np.nan
    
def main():
    L_entrada = sys.argv[1].split()
    p_entrada = sys.argv[2].split()
    OPT = sys.argv[3].split()

    L = np.array([int(i) for i in L_entrada])
    P = np.array([float(i) for i in p_entrada])

    fig1, ax1 = plt.subplots(figsize=(10,5))
    fig2, ax2 = plt.subplots(figsize=(10,5))
    fig3, ax3 = plt.subplots(figsize=(10,5))
    fig4, ax4 = plt.subplots(figsize=(10,5))

    for j, l in enumerate(L):
        prob = np.zeros(len(P))
        desv = np.zeros(len(P))
        tam = np.zeros(len(P))
        desvtam = np.zeros(len(P))
        for i, p in enumerate(P):
            datos = np.loadtxt(f"./resultados/datos_{l}_{p}_O3.txt")
            prob[i], desv[i] = probabilidad(datos)
            tam[i], desvtam[i] = tamanomax(datos)
        ax1.errorbar(P, prob, yerr=desv, label=f"L = {l}")
        ax2.errorbar(P, tam / (l * l), yerr=desvtam / (l * l),label=f"L = {l}")

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

    for o in OPT:
        WT = np.zeros(len(L))
        CT = np.zeros(len(L))
        desvWT = np.zeros(len(L))
        desvCT = np.zeros(len(L))

        for j, l in enumerate(L):
            wt = np.zeros(len(P))
            ct = np.zeros(len(P))
            for i, p in enumerate(P):
                datos = np.loadtxt(f"./resultados/datos_{l}_{p}_{o}.txt")
                wt[i] = sumatoria(datos, 2)
                ct[i] = sumatoria(datos, 3)
            WT[j] = np.mean(wt)
            desvWT = np.std(wt)
            CT[j] = np.mean(ct)
            desvCT = np.std(ct)
        ax4.errorbar(L, WT, yerr= desvWT,label=f"Wall time - {o}")
        ax4.errorbar(L, CT, yerr= desvCT,label=f"CPU time - {o}")

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
    ax3.set_xscale("log")
    ax3.set_yscale("log")
    ax3.legend()
    ax3.grid(True)
    fig3.tight_layout()
    fig3.savefig("Tiempos.pdf")

    ax4.set_xlabel(r"Tamano del lado de la malla")
    ax4.set_ylabel(r"Tiempo")
    ax4.set_title("Tiempo de computo en funcion del tamano del sistema" )
    ax4.set_xscale("log")
    ax4.set_yscale("log")
    ax4.legend()
    ax4.grid(True)
    fig4.tight_layout()
    fig4.savefig("Tiempos(errorbar).pdf")

    plt.close("all")
    
main()

        

