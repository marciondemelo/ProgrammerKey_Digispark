
#include <DigiKeyboard.h>
#include <TinyWireM.h>
#define pinLed01 1
#define qtdeCi  1
byte enderecosPCF8574[qtdeCi] = {32};
bool bt01 = false, bt02 = false, bt03 = false, bt04 = false, bt05 = false, bt06 = false, bt07 = false, bt08 = false;
bool ciPCF8574Read(byte pino);
int paginaSelecionada = 1;

void setup() {
  TinyWireM.begin();

  DigiKeyboard.sendKeyStroke(0);
  pinMode(pinLed01, OUTPUT);
  digitalWrite(pinLed01, HIGH);
}

void loop() {
  activeButton();
  delay(50);
  executeButton();
  delay(50);
}

void executeButton() {
  for (int bt = 1; bt <= 8; bt++) {
    switch (bt) {
      case 6: {
          //(01)PRIMEIRO BOTAO
          if (!ciPCF8574Read(bt) && bt06) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1)
              DigiKeyboard.print("a\n");
            else {
              DigiKeyboard.sendKeyStroke(KEY_F6, MOD_SHIFT_LEFT);             
            }
            bt06 = false;
          }
          break;
        }
      case 5: {
          //(02)SEGUNDO BOTAO
          if (!ciPCF8574Read(bt) && bt05) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1) {
              DigiKeyboard.print("b");
            }
            else {
              DigiKeyboard.sendKeyStroke(KEY_F8);
            }
            bt05 = false;
          }
          break;
        }
      case 4: {
          //(03)TERCEIRO BOTAO
          if (!ciPCF8574Read(bt) && bt04) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1) {
              DigiKeyboard.print("c\t");
              DigiKeyboard.print("d\t");
            }
            else {               
              DigiKeyboard.sendKeyStroke(KEY_F2);             
            }
            bt04 = false;
          }
          break;
        }
      case 7: {
          //(04)QUARTO BOTAO
          if (!ciPCF8574Read(bt) && bt07) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1) {
              DigiKeyboard.print("e");
            }
            else {
              DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
              DigiKeyboard.delay(300);
              DigiKeyboard.print("f\n");
            }
            bt07 = false;
          }
          break;
        }
      case 8: {
          //(05)QUINTO BOTAO
          if (!ciPCF8574Read(bt) && bt08) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1) {
              DigiKeyboard.sendKeyStroke(KEY_S , MOD_GUI_LEFT | MOD_SHIFT_LEFT);
            }
            else {
              DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
              DigiKeyboard.delay(300);
              DigiKeyboard.print("calc\n");
            }

            bt08 = false;
          }
          break;
        }
      case 2: {
          //(06)SEXTO BOTAO
          if (!ciPCF8574Read(bt) && bt02) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1) {
              DigiKeyboard.print("g\t");
              DigiKeyboard.print("h\n");
            }
            else {
              DigiKeyboard.print("2-6");
            }
            bt02 = false;
          }
          break;
        }
      case 1: {
          //(07)SETIMO BOTAO
          if (!ciPCF8574Read(bt) && bt01) {
            DigiKeyboard.sendKeyStroke(0);
            if (paginaSelecionada == 1) {
              DigiKeyboard.print("i\t");
              DigiKeyboard.print("j\n");
            }
            else {
              byte tecla = 233;
              DigiKeyboard.sendKeyStroke(tecla);
            }
            bt01 = false;
          }
          break;
        }
      case 3: {
          //(08)OITAVO BOTAO
          if (!ciPCF8574Read(bt) && bt03) {
            if (paginaSelecionada == 1) {
              paginaSelecionada = paginaSelecionada + 1;
              digitalWrite(pinLed01, LOW);
            }
            else {
              paginaSelecionada = 1;
              digitalWrite(pinLed01, HIGH);
            }
            bt03 = false;
          }
          break;
        }
    }
  }
}

void activeButton() {
  for (int bt = 1; bt <= 8; bt++) {
    if (ciPCF8574Read(bt)) {
      switch (bt) {
        case 1: {
            bt01 = true;
            break;
          }
        case 2: {
            bt02 = true;
            break;
          }
        case 3: {
            bt03 = true;
            break;
          }
        case 4: {
            bt04 = true;
            break;
          }
        case 5: {
            bt05 = true;
            break;
          }
        case 6: {
            bt06 = true;
            break;
          }
        case 7: {
            bt07 = true;
            break;
          }
        case 8: {
            bt08 = true;
            break;
          }
      }
    }
  }
}

bool ciPCF8574Read(byte pino) {
  pino = pino - 1;
  byte lido;
  bool estado;
  TinyWireM.requestFrom(enderecosPCF8574[pino / 8], 1);
  if (TinyWireM.available()) {
    lido = TinyWireM.read();
  }

  estado = bitRead(lido, pino % 8);
  return estado;
}
