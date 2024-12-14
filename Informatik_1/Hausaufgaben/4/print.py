import numpy as np
import matplotlib.pyplot as plt
import os

print("Aktuelles Arbeitsverzeichnis:", os.getcwd())


# CSV-Datei laden
file_path = r"H-BRS\Informatik_1\Hausaufgaben\4\heatmap.csv"
data = np.loadtxt(file_path, delimiter=",")

# Heatmap anzeigen
plt.imshow(data, cmap='hot', interpolation='nearest')
plt.colorbar(label="Höhe in 100m Schritten")
plt.title("max erlaubte Höhe von Windrädern")
plt.xlabel("X-Achse")
plt.ylabel("Y-Achse")

# Heatmap als PNG speichern
output_path = r"H-BRS\Informatik_1\Hausaufgaben\4\heatmap.png"  # Speicherort
plt.savefig(output_path, format='png', dpi=300, bbox_inches='tight')

plt.show()
