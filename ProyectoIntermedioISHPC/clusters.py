import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

malla = np.loadtxt("malla_etiquetada.txt")
print(malla)
colores = plt.cm.tab10.colors
nc = int(malla.max())

cmap = ListedColormap([(0, 0, 0), (1, 1, 1)] + list(colores[:nc - 1]))

plt.imshow(malla, cmap=cmap, vmin=0, vmax=nc)
plt.axis('off')
plt.savefig("malla.pdf", bbox_inches='tight', pad_inches=0)