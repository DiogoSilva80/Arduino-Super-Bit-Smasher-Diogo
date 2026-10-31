const int AND_PIN = 4;
const int OR_PIN = 3;
const int XOR_PIN = 2;
const int LED1 = 12;
const int LED2 = 11;
const int LED3 = 10;
const int LED4 = 9;



int target, current, inputNumber = -1;
unsigned long startTime;
unsigned long timeLimit = 30000;
bool gameRunning = true;


const unsigned long debounceDelay = 50;
const unsigned long holdTime = 2000; 
unsigned long buttonPressStart = 0; 
bool orButtonPressed = false;


int generateRandom8Bit() {
  return random(0, 256);
}


void resetLeds() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}


bool isButtonPressed(int pin, int index) {
  bool buttonState = digitalRead(pin);
  unsigned long currentMillis = millis();
  
  if (buttonState == LOW && (currentMillis - buttonPressStart > debounceDelay)) {
    buttonPressStart = currentMillis;
    return true;
  }
  return false;
}


void updateLeds() {
  unsigned long elapsedTime = millis() - startTime;
  int elapsedSections = (elapsedTime * 4 / timeLimit);

  if (elapsedSections < 0) elapsedSections = 0;
  if (elapsedSections > 4) elapsedSections = 4;

  digitalWrite(LED1, elapsedSections > 0 ? HIGH : LOW);
  digitalWrite(LED2, elapsedSections > 1 ? HIGH : LOW);
  digitalWrite(LED3, elapsedSections > 2 ? HIGH : LOW);
  digitalWrite(LED4, elapsedSections > 3 ? HIGH : LOW);

  if (elapsedTime >= timeLimit) {
    Serial.println("Tempo esgotado!");
    gameRunning = false;
    delay(2000);
    startGame();
  }
}


void startGame() {
  resetLeds(); 

  target = generateRandom8Bit(); 
  target &= ~1; 
  current = generateRandom8Bit(); 
  startTime = millis(); 
  gameRunning = true;
  inputNumber = -1;

 
  Serial.println("****NOVA RONDA****");
  Serial.print("Valor Target: ");
  Serial.println(target, BIN); 
  Serial.print("Valor Base: ");
  Serial.println(current, BIN); 
  Serial.println("Introduza um valor:");
}


void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  pinMode(AND_PIN, INPUT_PULLUP);
  pinMode(OR_PIN, INPUT_PULLUP);
  pinMode(XOR_PIN, INPUT_PULLUP);

  randomSeed(analogRead(A0));
  startGame();
}


void loop() {
  if (!gameRunning) return;


  updateLeds();


  if (digitalRead(OR_PIN) == LOW) {
    if (!orButtonPressed) {
      orButtonPressed = true;
      buttonPressStart = millis();
    } else {
      if (millis() - buttonPressStart > holdTime) {
        Serial.println("Botão OR pressionado por 2 segundos. Reiniciando o jogo...");
        orButtonPressed = false;
        startGame();
        return;
      }
    }
  } else {
    orButtonPressed = false;
  }


  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n'); 
    inputNumber = inputString.toInt(); 

    Serial.print("Valor lido (BIN): ");
    Serial.println(inputNumber, BIN);


    Serial.println("Prima um operador:");
    Serial.print("Operacoes permitidas: OR - azul ");
    if (target & 1) {
      Serial.println("AND - vermelho");
    } else {
      Serial.println("XOR - verde");
    }
    return; 
  }


  if (inputNumber != -1) { 
    int alignedInput = inputNumber & 0xFF; 

    if (isButtonPressed(AND_PIN, 0)) {
      if (target & 1) { 
        current &= alignedInput;
        Serial.println("Operação: AND aplicada");
      } else {
        Serial.println("Operador indisponível");
        Serial.println("Por favor, insira um novo valor.");
        inputNumber = -1; 
        return;
      }
    } else if (isButtonPressed(XOR_PIN, 2)) {
      if (!(target & 1)) { 
        current ^= alignedInput;
        Serial.println("Operação: XOR aplicada");
      } else {
        Serial.println("Operador indisponível");
        Serial.println("Por favor, insira um novo valor.");
        inputNumber = -1; 
        return;
      }
    } else if (isButtonPressed(OR_PIN, 1)) {
      current |= alignedInput;
      Serial.println("Operação: OR aplicada");
    } else {
      return; 
    }


    Serial.print("Novo valor: ");
    Serial.println(current, BIN);


    if (current == target) {
      Serial.println("Parabéns! Você atingiu o valor alvo!");
      gameRunning = false;
      delay(2000); 
      startGame();
    }

    Serial.println("Por favor, insira um novo valor.");
  inputNumber = -1; 
}
}








  
  








  
  


