-- Definição de Schema Relacional - FarmTech Solutions (Fase 2)

-- Tabela de Culturas
CREATE TABLE IF NOT EXISTS culturas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT UNIQUE NOT NULL,
    tempo_crescimento_dias INTEGER NOT NULL,
    ideal_umidade_solo REAL NOT NULL,
    ideal_temperatura REAL NOT NULL
);

-- Tabela de Leituras de Sensores IoT
CREATE TABLE IF NOT EXISTS leituras_sensores (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    temperatura REAL NOT NULL,
    umidade_ar REAL NOT NULL,
    umidade_solo REAL NOT NULL,
    ph REAL NOT NULL,
    luminosidade REAL NOT NULL,
    timestamp TEXT DEFAULT CURRENT_TIMESTAMP
);

-- Tabela de Operações de Campo
CREATE TABLE IF NOT EXISTS operacoes_campo (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_operacao TEXT NOT NULL,
    tipo_operacao TEXT NOT NULL, -- Plantio, Irrigacao, Adubacao, Colheita
    cultura_id INTEGER,
    area_hectares REAL NOT NULL,
    insumos_usados TEXT, -- Ex: 'Adubo NPK: 150kg, Sementes: 50kg'
    FOREIGN KEY (cultura_id) REFERENCES culturas(id)
);

-- Tabela de Alertas de Mensageria AWS Simulação
CREATE TABLE IF NOT EXISTS alertas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sensor_leitura_id INTEGER,
    tipo_alerta TEXT NOT NULL, -- Crítico, Alerta, Info
    descricao TEXT NOT NULL,
    canal TEXT NOT NULL, -- SMS, Email, Ambos
    destinatario TEXT NOT NULL,
    status TEXT NOT NULL, -- Enviado, Falhou
    timestamp TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (sensor_leitura_id) REFERENCES leituras_sensores(id)
);
