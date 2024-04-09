""" importação das bibliotecas """

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

""" leitura dos dados """
df = pd.read_csv("dados1.TXT", sep=";", header=None, names=["Umidade 1", "Umidade 2"])
df = df[["Umidade 1", "Umidade 2"]]
size = len(df["Umidade 1"])

""" declaração dos vetores que serão utilizados """
x = []
x_horas = []
y1 = []
y2 = []
yf = []
r = []

""" estrutura iterativa para armazenar os valores lidos, bem como converter o tempo para horas """
for i in range(size):
    x.append(i)
    y1.append(df["Umidade 1"][i])
    y2.append(df["Umidade 2"][i])
    yf.append(y1[i] - y2[i])
    if (i * 10) % 3600 == 0:
        x_horas.append((i * 10) // 3600)

""" determinação da reta de mínimos quadrados """
y_r = np.polyfit(x, yf, 1)

""" releitura dos valores de x depois de se transformar para horas """
pace = len(x_horas) / size
newX = []

""" armazenamento dos valores de x convertidos para horas e desenho da reta dos mínimos quadrados adaptada para hora """
for i in range(size):
    newX.append(i * pace)
    r.append(y_r[1] + y_r[0] * newX[i])

""" configuração do gráfico para exibição das informações """
plt.title("Umidade x Tempo")
plt.xlabel("Tempo(h)")
plt.ylabel("Umidade(%)")
plt.grid()
plt.plot(newX, y1, color="blue", label="Sensor 1")
plt.plot(newX, y2, color="orange", label="Sensor 2")
plt.plot(newX, yf, color="purple", linestyle="--", label="Diferença")
plt.plot(newX, r, color="red", label=f"({y_r[1]:.6f}) + ({y_r[0]:.6f}) * x")
plt.legend(loc="lower right")
plt.show()
