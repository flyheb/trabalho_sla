const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8" />
  <title>Monitoramento Agrícola</title>
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <style>
body {
  font-family: Arial, sans-serif;
  background: #121212;
  color: #fff;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  min-height: 100vh;
  margin: 0;
  padding: 10px;
}
h1 {
  font-size: 2.2rem;
  color: #0f0;
  margin: 20px 0;
  text-align: center;
}
.container {
  display: flex;
  gap: 20px;
  flex-wrap: wrap;
  justify-content: center;
}
.card {
  background: #1f1f1f;
  padding: 20px;
  border-radius: 12px;
  box-shadow: 0 0 8px #00ffcc33;
  width: 220px;
  text-align: center;
}
.card.alert {
  border: 2px solid #ff6b6b;
}
.icon {
  font-size: 1.5rem;
  margin-bottom: 8px;
}
.label {
  font-size: 1.1rem;
  color: #ccc;
  margin-bottom: 8px;
}
.value {
  font-size: 2.5rem;
  color: #0fa;
  font-weight: bold;
}
.footer {
  margin-top: 30px;
  font-size: 0.8rem;
  color: #666;
  text-align: center;
}
#btnAtualizar {
  margin: 20px;
  padding: 10px 25px;
  font-size: 1rem;
  cursor: pointer;
  border: none;
  border-radius: 6px;
  background-color: #00cc99;
  color: #121212;
  font-weight: bold;
}
#btnAtualizar:hover {
  background-color: #00aa77;
}
@media (max-width: 768px) {
  .container {
    flex-direction: column;
    align-items: center;
  }
  .card {
    width: 90%;
    max-width: 300px;
  }
}
  </style>
</head>
<body>
  <h1>🌱 Monitoramento Agrícola</h1>
  
  <div class="container">
    <div class="card" id="cardSolo">
      <div class="icon">🌱</div>
      <div class="label">Umidade do Solo</div>
      <div class="value" id="umidadeSolo">--%</div>
    </div>
    <div class="card" id="cardAr">
      <div class="icon">💧</div>
      <div class="label">Umidade do Ar</div>
      <div class="value" id="umidadeAr">--%</div>
    </div>
    <div class="card" id="cardTemp">
      <div class="icon">🌡️</div>
      <div class="label">Temperatura do Ar</div>
      <div class="value" id="temperaturaAr">--°C</div>
    </div>
  </div>

  <button id="btnAtualizar">Atualizar Agora</button>

  <div class="footer">
    Atualizando a cada 3 segundos
  </div>

  <script>
function atualizarDados() {
  fetch('/dados?t=' + Date.now())
    .then(res => res.json())
    .then(data => {
      console.log(data);
      document.getElementById('umidadeSolo').textContent = data.umidade_solo + '%';
      document.getElementById('umidadeAr').textContent = data.umidade_ar + '%';
      document.getElementById('temperaturaAr').textContent = data.temperatura_ar + '°C';
      
      // Alertas simples
      const cardSolo = document.getElementById('cardSolo');
      const cardAr = document.getElementById('cardAr');
      const cardTemp = document.getElementById('cardTemp');
      
      cardSolo.className = data.umidade_solo < 20 || data.umidade_solo > 80 ? 'card alert' : 'card';
      cardAr.className = data.umidade_ar < 30 || data.umidade_ar > 70 ? 'card alert' : 'card';
      cardTemp.className = data.temperatura_ar < 15 || data.temperatura_ar > 35 ? 'card alert' : 'card';
    })
    .catch(err => console.error('Erro:', err));
}

setInterval(atualizarDados, 4000);
atualizarDados();

document.getElementById('btnAtualizar').addEventListener('click', atualizarDados);
  </script>
</body>
</html>
)rawliteral";