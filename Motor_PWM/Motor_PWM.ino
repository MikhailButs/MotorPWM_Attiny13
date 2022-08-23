//Начальное значение ШИМ 0-255
int PWM = 120;
unsigned long Timer;
int buttonState = 0;
#define Period 180000

// the setup routine runs once when you press reset:
void setup() {
  // make the pushbutton's pin an input:
  //Пины ШИМ двигателя и индикаторного светодиода
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);
  //кнопки, светодиод МАХ мощности
  pinMode(PB4, INPUT);
  digitalWrite(PB4, HIGH);
  pinMode(PB2, INPUT);
  digitalWrite(PB2, HIGH);
  pinMode(PB3, INPUT);
  digitalWrite(PB3, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {

  //проверка кнопки ВКЛ, запуск
  if (!digitalRead(PB3)){
    //"старт двигателя", для нагрузики, которая спокойно запускается , можно убрать
    if (buttonState == 0){
       analogWrite(PB0, 255);
       delay(300);
       buttonState = 1;
    }
    analogWrite(PB0, PWM);
    Timer = millis();
  }

  //Мощность +
  int PWMHigh = digitalRead(PB4);
  if (!PWMHigh){
    PWM = PWM + 15;
    if (PWM > 255){
      PWM = 255;
      analogWrite(PB1, 0);
      delay(400);
      analogWrite(PB1, 255);
    }
    Timer = millis();
    delay(200);
  }

  //Мощность -
  int PWMLow = digitalRead(PB2);
  if (!PWMLow){
    PWM = PWM -15;
    if (PWM < 45){
      PWM = 45;
      //Индикация минимальной мощности
      analogWrite(PB1, 255);
      delay(400);
      analogWrite(PB1, 0);
    }
    Timer = millis();
    delay(200);
  }

  //Светодиод с ШИМ - индикатор мощности
  analogWrite(PB1, PWM-45);

  //Проверка кнопки ВКЛ, отключение
  if (digitalRead(PB3)){
    analogWrite(PB0, 0);
    //от дребезка, иначе включается "старт двигателя", тоже можно убрать
    if (buttonState == 1) {
      delay(200);
    }
    buttonState = 0;
    //Индикатор простоя
    if (millis()- Timer >= Period){
      Timer = millis();
      analogWrite(PB1, 0);
      delay(200);
      analogWrite(PB1, 255);
      delay(200);
      analogWrite(PB1, 0);
      delay(200);
      analogWrite(PB1, 255);
      delay(200);
      analogWrite(PB1, 0);
      delay(200);
      analogWrite(PB1, 255);
      delay(200);
      analogWrite(PB1, 0);
      delay(200);
      analogWrite(PB1, 255);
    }
  }
}
