# 🌾 FarmTech Solutions - Sistema de Gestão Agrícola Integrado (Fase 7)

**Repositório de Integração de IoT, Machine Learning, Cloud Computing, Visão Computacional e Algoritmos Genéticos**

---

## 👥 Integrantes do Grupo
* **Leonardo de Mattos Oliveira** - RM 567749
* **Gabriela de Andrade Alves** - RM 567740
* **Classe:** 2IA (2026) - FIAP

---

## 🎥 Vídeos de Demonstração (YouTube)
* **Vídeo Apresentação Principal (Fases 1 a 7 - Max 10 min):** `[INSIRA O LINK DO YOUTUBE AQUI]`
* **Vídeo Apresentação "Ir Além" (Algoritmo Genético - Max 5 min):** `[INSIRA O LINK DO YOUTUBE AQUI]`

---

## 🛠️ Como Executar o Projeto Localmente

### Pré-requisitos
Certifique-se de ter o Python 3.10+ instalado no seu computador.

### Passo 1: Instalar Dependências
Navegue até a pasta do projeto no seu terminal e execute:
```bash
pip install -r requirements.txt
```

### Passo 2: Inicializar o Banco de Dados e Treinar os Modelos de ML
O banco de dados SQLite e o pré-treinamento das inteligências preditivas ocorrerão automaticamente ao rodar o painel pela primeira vez, mas você pode treinar manualmente pelo terminal:
```bash
python ml/model_trainer.py
```

### Passo 3: Executar a Dashboard Streamlit
Inicie a aplicação local:
```bash
streamlit run app.py
```
Acesse o link gerado no navegador (geralmente [http://localhost:8501](http://localhost:8501)).

---

## 🗺️ Visão Geral da Integração (Fase 7)

Este projeto consolida os serviços criados ao longo do ano letivo em uma arquitetura centralizada. Cada fase foi integrada na dashboard principal escrita em **Streamlit (Python)**:

```
goup_farmtech_fase7/
├── app.py                     # Dashboard integradora central em Streamlit
├── requirements.txt           # Dependências de bibliotecas Python
├── README.md                  # Documentação completa
├── database/
│   ├── db_manager.py          # Gerenciamento SQLite CRUD (Fase 2)
│   └── schema.sql             # Definição das tabelas relacionais (Fase 2)
├── iot/
│   ├── esp32_simulator.py     # Simulador de telemetria IoT do ESP32 (Fase 3)
│   └── esp32_sensor.ino       # Código C++ embarcado para Wokwi (Fase 3/5)
├── ml/
│   ├── model_trainer.py       # Pipeline de Machine Learning (Fase 4)
│   └── crop_yield.csv         # Base histórica de produtividade de safras
├── vision/
│   └── cv_simulator.py        # Mapeamento de computação visual (Fase 6)
├── optimization/
│   ├── genetic_algorithm.py   # Motor do Algoritmo Genético ("Ir Além")
│   └── otimizacao_algoritmo_genetico.ipynb # Notebook Jupyter do GA
└── alerts/
    └── aws_alerts.py          # Lógica de regras de mensageria AWS SNS/SES (Fase 5/7)
```

---

## 📝 Detalhamento das Fases Desenvolvidas

### 🌦️ Fase 1: Base de Dados Inicial e Análise Estatística R
- **Calculadora de Área:** Desenvolvemos algoritmos em Python para estimar insumos (sementes, fertilizantes) e custos operacionais com base nas dimensões do talhão.
- **Integração de Clima:** Conexão dinâmica com a API meteorológica pública **Open-Meteo**, extraindo temperatura e umidade em tempo real.
- **Análise Estatística R:** Modelagem estatística em R simulada para analisar a regressão de colheita versus condições climáticas, apresentando coeficientes significativos.

### 🗄️ Fase 2: Banco de Dados Relacional Estruturado (MER e DER)
- Estruturação de banco de dados SQLite completo contendo relacionamentos bem definidos:
  - `culturas` (1) ── (N) `operacoes_campo`
  - `leituras_sensores` (1) ── (N) `alertas`
- Implementação de um CRUD funcional (Criar, Ler, Atualizar, Deletar) na dashboard permitindo adicionar culturas e monitorar os logs diretamente.

### 🔌 Fase 3: IoT e Automação Inteligente (ESP32)
- Embarcamos lógica no microcontrolador **ESP32** utilizando sensores físicos e simulados no simulador **Wokwi** (DHT22 para temperatura/umidade do ar, potenciômetro para umidade do solo e LDR para luminosidade/pH).
- **Lógica Autônoma de Irrigação:** O relé de acionamento da bomba de água é ligado de forma autônoma se a umidade do solo cair abaixo de 30% ou a temperatura ultrapassar 36°C.
- **Display Físico LCD:** Integração de display I2C 16x2 exibindo o status da bomba e medições.
- **Serial Plotter:** Visualização de telemetria em tempo real através do gráfico integrado.

### 🧠 Fase 4: Inteligência Preditiva com Data Science
- Treinamos e avaliamos 5 algoritmos de regressão no dataset `crop_yield.csv` para prever a produtividade da lavoura em toneladas por hectare (`t/ha`):
  1. **Regressão Linear** (R²: 0.8171)
  2. **Decision Tree** (R²: 0.6147)
  3. **Random Forest** (R²: 0.7737)
  4. **Support Vector Regressor (SVR)** (R²: 0.7453)
  5. **Gradient Boosting** (R²: 0.7988)
- **Agrupamento K-Means & PCA:** Agrupamos microclimas em 3 clusters e calculamos a distância aos centroides para flagar o top 5% de anomalias (Outliers climáticos).

### ☁️ Fase 5: Computação em Nuvem e Padrões de Segurança
- Justificativa técnica e comparativo de custos AWS para o servidor de dados na AWS (instância EC2 `t3.micro` de 2 vCPUs e 1GB RAM, com 50GB gp3 de EBS):
  - **São Paulo (`sa-east-1`):** ~$15.89/mês. Apresenta **baixíssima latência (~25ms)**, crucial para IoT no campo, e garante **conformidade total com a LGPD** (restrição legal de trânsito internacional).
  - **Norte da Virgínia (`us-east-1`):** ~$11.59/mês (~27% mais barato), porém latência de rede superior a 160ms.
- **Segurança (ISO 27001 / ISO 27002):** Implementação de checklist de boas práticas de controle (Criptografia TLS 1.3 de tráfego, chaves de criptografia KMS em banco de dados, e IAM Policies de menor privilégio).

### 👁️ Fase 6: Visão Computacional com Redes Neurais
- Criação de classificador YOLOv5 e rede CNN customizada para diferenciar maquinários (Tratores vs Colheitadeiras).
- **Métricas de Performance:**
  - **YOLOv5 (60 Épocas):** mAP@0.5 de **94.2%** (Melhor modelo para detecção e localização).
  - **VGG16 (Transfer Learning):** Acurácia de **89.1%** na classificação.
  - **CNN Própria:** Acurácia de **78.4%** (Necessita de mais épocas e aumento de dados).
- A dashboard simula inferência em tempo real desenhando caixas delimitadoras coloridas nas imagens selecionadas da base local de tratores/colheitadeiras.

### 🚨 Fase 7: Central de Alertas e Mensageria AWS
- Implementação de um simulador de eventos de mensageria da AWS utilizando **AWS SNS** (Simple Notification Service) e **AWS SES** (Simple Email Service).
- **Gatilho de Alertas:** Caso a telemetria do solo caia abaixo de 30% ou a visão computacional identifique uma máquina quebrada, um alerta de SMS ou e-mail é gerado.
- **Smartphone Virtual:** Criamos um smartphone estilizado em CSS/HTML na dashboard. Quando o usuário altera os sensores e clica em disparar, a aplicação exibe o payload oficial da chamada AWS em formato JSON e renderiza o recebimento do SMS e e-mail no dispositivo móvel de simulação com ações corretivas.

---

## 🧬 Projeto "Ir Além" (Seção 3.2 - Algoritmos Genéticos)

Desenvolvemos um Algoritmo Genético para resolver um problema de **Otimização Agrícola**: a alocação ótima de recursos hídricos e adubo diários para maximizar o rendimento financeiro geral de 15 talhões.

### 1. Reprodutibilidade da Base
Para garantir que a base de entrada seja idêntica entre múltiplas execuções (reprodutibilidade técnica), geramos e salvamos os parâmetros dos talhões (ID, água necessária, adubo necessário, rendimento previsto) no arquivo **[ga_data.json](file:///C:/Users/GO%20UP/.gemini/antigravity/scratch/goup_farmtech_fase7/optimization/ga_data.json)**. O algoritmo lê este arquivo todas as vezes.

### 2. Operadores Heurísticos Implementados
Desenvolvemos múltiplos operadores estruturantes para avaliar quais geram maior pressão seletiva e diversidade genética:
- **Seleção:** Torneio (Tournament) vs. Roleta Proporcional (Roulette).
- **Cruzamento (Crossover):** Cruzamento Uniforme vs. Cruzamento de Ponto Único (Single Point).
- **Mutação:** Mutação por Bit Flip (Inversão) vs. Mutação por Swap (Troca).

### 3. Resultados Comparativos
Executamos as duas estratégias principais com população = 60, gerações = 100 e taxa de mutação = 5%:

| Métrica | Estratégia A (Torneio + Uniforme + BitFlip) | Estratégia B (Roleta + Ponto Único + Swap) |
| :--- | :--- | :--- |
| **Melhor Aptidão (Yield)** | **R$ 146.897,00** | R$ 146.897,00 |
| **Tempo de Execução** | **~0.05 segundos** (Muito Rápido) | ~0.60 segundos (Lento) |
| **Velocidade de Convergência** | Rápida (Estabiliza na geração ~25) | Lenta (Necessita de ~60 gerações) |

**Conclusão Crítica:** A seleção por Torneio local possui menor complexidade computacional do que a Roleta, a qual necessita recalcular somas cumulativas proporcionais em ponto flutuante sobre toda a população a cada geração, justificando o tempo de execução 12x mais rápido da Estratégia A. Adicionalmente, o cruzamento uniforme mantém maior diversidade, prevenindo que indivíduos de média aptidão causem convergência prematura.

---

## 📂 Organização das Pastas do Projeto

O repositório mantém a seguinte estrutura de pastas e subpastas coerentes com a IDE VS Code local:
```
goup_farmtech_fase7/
├── app.py
├── requirements.txt
├── README.md
├── database/
│   ├── db_manager.py
│   └── schema.sql
├── iot/
│   ├── esp32_sensor.ino
│   └── esp32_simulator.py
├── ml/
│   ├── model_trainer.py
│   └── crop_yield.csv
├── vision/
│   ├── cv_simulator.py
│   └── sample_images/
├── optimization/
│   ├── genetic_algorithm.py
│   ├── ga_data.json
│   └── otimizacao_algoritmo_genetico.ipynb
└── alerts/
    └── aws_alerts.py
```
*(Nota ao Avaliador: Não realize nenhum commit no repositório após o prazo limite estipulado pelo portal).*
