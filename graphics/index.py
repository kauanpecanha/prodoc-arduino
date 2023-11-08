import numpy as np # numpy
import matplotlib.pyplot as plt # matplotlib
import pandas as pd # pandas

x = [] # inicialização do array responsável pelos valores dos segundos, no eixo x
y1 = [] # inicialização do array responsável pelo armazenamento dos valores do sensor 1
y2 = [] # inicialização do array responsável pelo armazenamento dos valores do sensor 2

df = pd.read_csv("index.TXT", sep = ";", header=None, names=["Umidade 1", "Umidade 2"]) # leitura dos dados através da biblioteca pandas

df = df[["Umidade 1", "Umidade 2"]] # a variável df(dataframe) é composta por duas colunas com os valores advindos de umidade 1 e 2

size = len(df["Umidade 1"]) # definição da quantidade de linhas de dados composta pelo arquivo

plt.title("Gráfico Umidades x Tempo") # titulação do gráfico
plt.xlabel("Tempo(s)") # titulação do eixo x
plt.ylabel("Umidades") # titulação do eixo y
plt.grid() # função de ativação das linhas grid de gráfico

for i in range(size): # cada i representa um segundo
    
    x.append(i) # array x armazena o valor do segundo de cada linha
    y1.append(df["Umidade 1"][i]) # array y1 armazena o valor do primeiro sensor de cada linha
    y2.append(df["Umidade 2"][i]) # array y2 armazena o valor do segundo sensor de cada linha

plt.plot(x, y1, color="blue", label="Sensor 1") # plotagem da linha que cruza todos os dados do primeiro sensor
plt.plot(x, y2, color="orange", label="Sensor 2") # plotagem da linha que cruza todos os dados do segundo sensor
plt.legend(loc="upper left") # plotagem da legenda que diz o que cada linha condiz
plt.show() # plotagem do gráfico na interface de usuário