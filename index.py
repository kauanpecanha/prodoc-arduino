
'''importação das bibliotecas'''
import matplotlib.pyplot as plt
import pandas as pd

x = []
y1 = []
y2 = []

"""leitura dos dados com sua delimitação e colunas"""
df = pd.read_csv("dados.TXT", sep=";", header=None, names=["Umidade 1", "Umidade 2"])

"""delimitação das colunas"""
df = df[["Umidade 1", "Umidade 2"]]

""" titulação, rotulação dos eixos x e y, e ativação das linhas de grid """
plt.title( "Gráfico Umidade x Tempo" )
plt.xlabel( "Tempo(s)" )
plt.ylabel( "Umidade(%)" )
plt.grid()

for i in range( len(df["Umidade 1"]) ):

    x.append( i )
    y1.append( df["Umidade 1"][i] )
    y2.append( df["Umidade 2"][i] )

plt.plot( x, y1, color="blue", label="Sensor 1" )
plt.plot( x, y2, color="orange", label="Sensor 2" )
plt.legend( loc="upper left" )
plt.show()
