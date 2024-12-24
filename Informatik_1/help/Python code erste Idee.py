import matplotlib.pyplot as plt
import numpy as np

# CSV-Daten laden
data = np.loadtxt("C:\\Users\\andre\Documents\\Git\\H-BRS\\Informatik_1\\help\\output.csv", delimiter=',')
# Bild erstellen
plt.imshow(data, cmap='viridis', origin='upper')
plt.colorbar(label='Höhe (Skala)')
plt.title('10H-Regel Diagramm')
plt.savefig('diagramm.png')  # Speichere als PNG-Bild
plt.show()
