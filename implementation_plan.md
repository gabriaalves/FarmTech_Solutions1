# Plano de Implementação - FarmTech Solutions (Fase 7)

Este plano descreve a consolidação de todas as etapas (Fases 1 a 6) do projeto **FarmTech Solutions** em um único ecossistema digital integrado, desenvolvido em Python, com interface interativa em **Streamlit**. O projeto inclui a dashboard final, simulação de IoT e banco de dados relacional, machine learning, computação em nuvem, visão computacional, serviço de mensageria da AWS e uma solução otimizada usando Algoritmos Genéticos ("Ir Além").

O projeto será desenvolvido em uma nova pasta estruturada: `C:\Users\GO UP\.gemini\antigravity\scratch\goup_farmtech_fase7`.

---

## User Review Required

> [!IMPORTANT]
> **Compatibilidade do Ambiente Local:**
> O ambiente local não possui `tensorflow`, `torch` ou `opencv-python` instalados. Portanto, a modelagem de rede neural YOLOv5 e CNN da Fase 6 será apresentada via:
> 1. Um painel interativo de inferência simulada de alta fidelidade para classificação de tratores e colheitadeiras com métricas reais obtidas nos notebooks de treinamento.
> 2. Visualização das métricas de treino (Matriz de Confusão, curvas de perda e precisão) compiladas do Jupyter Notebook original.
> 3. O código original da Fase 6 estará incluído e disponível na pasta do projeto para portabilidade completa.

> [!TIP]
> **Simulação AWS SNS/SES:**
> Como não há credenciais AWS ativas no ambiente local para disparo em tempo real de SMS/E-mail via SDK `boto3`, implementaremos um **simulador de mensageria de alta fidelidade da AWS**. Ele exibirá em tempo real os payloads JSON gerados, o fluxo da fila de mensageria e o envio fictício de e-mail e SMS utilizando um smartphone virtual estilizado na interface Streamlit. Adicionalmente, forneceremos o script Python com suporte completo a `boto3` para uso com chaves AWS válidas.

---

## Open Questions

> [!NOTE]
> Não há perguntas em aberto restritivas. A arquitetura de integração proposta cobre todos os requisitos das fases de maneira completa e robusta. A otimização com Algoritmo Genético resolverá o problema de alocação de insumos e recursos hídricos (Mochila Binária e Contínua) e será totalmente integrada ao painel de controle.

---

## Proposed Changes

Os arquivos serão criados dentro de uma nova estrutura de diretórios em `C:\Users\GO UP\.gemini\antigravity\scratch\goup_farmtech_fase7`.

```
goup_farmtech_fase7/
├── app.py                     # Dashboard principal integradora em Streamlit
├── requirements.txt           # Dependências de bibliotecas Python
├── README.md                  # Documentação completa e detalhada do repositório
├── database/
│   ├── db_manager.py          # Gerenciamento SQLite (Fase 2)
│   └── schema.sql             # Definição do banco de dados relacional (DDL)
├── iot/
│   ├── esp32_simulator.py     # Simulação lógica dos sensores IoT (Fase 3)
│   └── esp32_sensor.ino       # Código C++ embarcado para ESP32 (Fase 3/5)
├── ml/
│   ├── model_trainer.py       # Treinamento e avaliação dos modelos de ML (Fase 4)
│   └── crop_yield.csv         # Base de dados original de rendimento de safras
├── vision/
│   └── cv_simulator.py        # Módulo de visão computacional e inferência (Fase 6)
├── optimization/
│   ├── genetic_algorithm.py   # Algoritmo Genético de otimização de insumos ("Ir Além")
│   └── otimizacao_algoritmo_genetico.ipynb # Notebook Jupyter documentando os testes de GA
└── alerts/
    └── aws_alerts.py          # Simulador de mensagens e lógica de integração AWS SNS/SES (Fase 5/7)
```

---

### Componente 1: Base de Dados e Backend Relacional (Fases 1 e 2)

O backend utilizará SQLite para o armazenamento estruturado dos dados da fazenda. Ele representará o MER/DER da Fase 2.

#### [NEW] [schema.sql](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/database/schema.sql)
- Criará tabelas estruturadas:
  - `culturas`: informações das culturas de plantio (Arroz, Trigo, Milho, etc.).
  - `leituras_sensores`: umidade do ar, umidade do solo, temperatura, pH e luminosidade (LDR).
  - `operacoes_campo`: registro de plantio, fertilização, irrigação e colheita.
  - `alertas`: logs de alertas de emergência disparados.

#### [NEW] [db_manager.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/database/db_manager.py)
- Abstração em Python das operações CRUD de banco de dados.
- Conexão e população inicial de dados sintéticos realistas para testes.

---

### Componente 2: IoT e Simulação Física (Fase 3)

Integrará as lógicas físicas do ESP32 na dashboard e disponibilizará o código do microcontrolador.

#### [NEW] [esp32_sensor.ino](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/iot/esp32_sensor.ino)
- Códigoembarcado C++ contendo a lógica de Wi-Fi, leitura do DHT22 (temperatura/umidade), LDR (para pH/luz), umidade do solo, e envio via HTTP POST.
- Lógica de acionamento automático do relé da bomba de água com base em limites de umidade.

#### [NEW] [esp32_simulator.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/iot/esp32_simulator.py)
- Simula o envio de telemetria IoT do ESP32 diretamente para o banco de dados.
- Lógica automatizada para ligar/desligar bomba no painel da dashboard.

---

### Componente 3: Data Science e Inteligência Preditiva (Fase 4)

Execução do pipeline de machine learning para previsão de produtividade de safras e detecção de anomalias climáticas.

#### [NEW] [model_trainer.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/ml/model_trainer.py)
- Treinará os 5 modelos de regressão: Regressão Linear, Decision Tree, Random Forest, SVR e Gradient Boosting.
- Calculará R², MAE e RMSE para comparação de desempenho.
- Executará clustering K-Means e PCA para agrupar dados climáticos e apontar outliers (anomalias de produtividade/clima).
- Fornecerá função de inferência rápida para prever produtividade com base em sliders do Streamlit.

#### [NEW] [crop_yield.csv](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/ml/crop_yield.csv)
- Cópia da base de dados de rendimento para execução local e reprodutibilidade do ML.

---

### Componente 4: Visão Computacional (Fase 6)

Mapeamento visual e classificação de maquinário agrícola com visualização de métricas e inferência interativa.

#### [NEW] [cv_simulator.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/vision/cv_simulator.py)
- Carregamento de imagens de exemplo da base local de tratores/colheitadeiras.
- Execução de inferência simulada (desenho de caixas delimitadoras YOLOv5 com classes 'Trator' e 'Colheitadeira' e confiança na imagem selecionada).
- Apresentação comparativa dos modelos: YOLOv5 customizado (30 e 60 épocas), CNN própria e VGG16 (Transfer Learning).

---

### Componente 5: Alertas AWS e Mensageria (Fases 5 e 7)

Serviço de alerta integrado aos dados climáticos e computação visual da fazenda.

#### [NEW] [aws_alerts.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/alerts/aws_alerts.py)
- Implementação de regras de disparo de alertas:
  - Solo seco demais (Umidade < 30%) -> Sugere irrigação imediata.
  - Temperatura excessiva (> 38°C) -> Risco de estresse térmico na plantação.
  - Equipamento identificado como quebrado/parado (via CV) -> Envio de manutenção.
- Geração de payloads AWS SNS/SES para e-mail/SMS.
- Integração com um painel interativo de logs de disparos.

---

### Componente 6: Otimização por Algoritmos Genéticos (Ir Além 3.2)

Otimização de recursos da fazenda (água e fertilizantes) buscando maximizar a produtividade e minimizar custos.

#### [NEW] [genetic_algorithm.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/optimization/genetic_algorithm.py)
- Modelagem do problema de alocação de insumos como uma mochila multidimensional (recursos hídricos e adubo limitados por talhão, maximizando o rendimento estimado).
- Salvamento de parâmetros de entrada em `ga_data.json` para reprodutibilidade.
- Estruturação de múltiplos métodos de:
  - Seleção: Roleta (Roulette) e Torneio (Tournament).
  - Cruzamento: Ponto Único (Single Point) e Uniforme (Uniform).
  - Mutação: Mutação por Inversão (Bit Flip) e Mutação de Troca (Swap).
- Interface de comparação live no Streamlit (gráfico de evolução de fitness e tempo de execução).

#### [NEW] [otimizacao_algoritmo_genetico.ipynb](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/optimization/otimizacao_algoritmo_genetico.ipynb)
- Notebook Jupyter documentando as equações matemáticas, o modelo de otimização de insumos, a justificativa das taxas de mutação e cruzamento, a comparação empírica de desempenho e as conclusões críticas sobre as heurísticas utilizadas.

---

### Componente 7: Dashboard Streamlit Integrada (Fase 7)

#### [NEW] [app.py](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/app.py)
- Interface web construída em Streamlit.
- Design premium com cores HSL adequadas (estética de alta qualidade para agronegócio: tons de verde floresta, cinza escuro, dourado e azul água).
- Menu lateral para navegação pelas diferentes Fases (1 a 7 e Ir Além).
- Gráficos responsivos usando Plotly / Matplotlib / Seaborn.
- Exibição de um smartphone virtual interativo que mostra os alertas de SMS/E-mail recebidos em tempo real.
- Integração de botões para rodar os testes, treinar os modelos ou simular telemetria.

---

### Documentação e Configurações de Deploy

#### [NEW] [README.md](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/README.md)
- Explicação robusta de cada Fase do projeto.
- Esquemas de arquitetura do sistema e diagrama do banco de dados (MER/DER em Mermaid).
- prints simulados de console e configurações da AWS (EC2, precificação e segurança ISO 27001).
- Justificativa das tomadas de decisão técnicas de infraestrutura e algoritmos.
- Seção exclusiva detalhando os resultados do "Ir Além" (YOLOv5 no Learner Lab e Otimização Genética).
- Link fictício para o vídeo do Youtube e entrega final.

#### [NEW] [requirements.txt](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/requirements.txt)
- Contém: `streamlit`, `pandas`, `numpy`, `scikit-learn`, `matplotlib`, `seaborn`, `ipykernel` (e outros necessários para rodar o notebook de GA).

---

## Verification Plan

### Automated Tests
Para validar que o sistema executa corretamente sem quebras de imports:
1. Executar o script de treinamento de ML:
   `python ml/model_trainer.py`
2. Testar o motor do Algoritmo Genético:
   `python optimization/genetic_algorithm.py`
3. Executar o dashboard Streamlit localmente:
   `streamlit run app.py`

### Manual Verification
- Acessar o dashboard Streamlit em `http://localhost:8501`.
- Navegar por cada aba de fase para verificar a renderização de gráficos, carregamento de tabelas SQLite e formulários de CRUD.
- Alterar valores de sensores na aba IoT e testar se a bomba de irrigação liga/desliga automaticamente.
- Inserir um e-mail/celular e disparar alertas críticos na aba Central de Alertas AWS, observando se a notificação aparece no smartphone virtual.
- Executar a otimização com algoritmo genético selecionando diferentes métodos (ex: Torneio + Cruzamento Uniforme) e conferindo o gráfico de convergência do fitness.
