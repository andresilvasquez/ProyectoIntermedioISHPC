import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

# Cargar el archivo .txt donde se encuentran las etiquetas de los clusters percolantes
malla = np.loadtxt("malla_etiquetada.txt")
colores = plt.cm.tab10.colors
nc = int(malla.max())

cmap = ListedColormap([(0, 0, 0), (1, 1, 1)] + list(colores[:nc - 1]))

plt.imshow(malla, cmap=cmap, vmin=0, vmax=nc)
plt.axis('on')
plt.xticks([])  
plt.yticks([])
plt.box(True)
plt.savefig("malla.pdf", pad_inches=0.2)