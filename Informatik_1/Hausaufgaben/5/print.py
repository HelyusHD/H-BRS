import matplotlib.pyplot as plt

# Daten aus der Datei lesen
x = [] # hight [m]
y1 = [] # power [J]
y2 = [] # volume derivative [m^3/s]

file_path = r"H-BRS\Informatik_1\Hausaufgaben\5\data.txt"

with open(file_path, "r") as file:
    for line in file:
        xi, y1i, y2i = map(float, line.split())  # x, y1 und y2 extrahieren
        x.append(xi)
        y1.append(y1i / 1000)
        y2.append(y2i)

# Daten plotten
plt.figure(figsize=(10, 6))

# Erste Funktion: y1 = x^2
plt.plot(x, y1, label="power of water turbine depending on water levels", color="blue", marker="o")

# Zweite Funktion: y2 = x^3
plt.plot(x, y2, label="liters per second depending on water levels", color="red", marker="o")

plt.title("power")
plt.xlabel("hight [m]")
plt.ylabel("power [kW] | m^3/s")
plt.legend()
plt.grid(True)
plt.show()
